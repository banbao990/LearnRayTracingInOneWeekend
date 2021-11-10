#include <omp.h>  // TODO 加入并行
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include <camera.hpp>
#include <color.hpp>
#include <dielectric.hpp>
#include <hit_record.hpp>
#include <hittable.hpp>
#include <hittable_list.hpp>
#include <iomanip>
#include <iostream>
#include <lambertian.hpp>
#include <material.hpp>
#include <memory>
#include <metal.hpp>
#include <ray.hpp>
#include <rtweekend.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <vec3.hpp>

using std::string;
using std::to_string;

hittable_list random_scene();

string left_append(int a, int num = 2, char c = '0') {
    string str = to_string(a);
    int len = str.length();
    if (len < num) {
        str = string(num - len, c) + str;
    }
    return str;
}

double get_second() {
    time_t nowtime;
    struct tm* p;
    time(&nowtime);
    p = localtime(&nowtime);
    return p->tm_sec + p->tm_min * 60.0 + p->tm_hour * 3600.0;
}

string get_file_name() {
    // 今天日期
    time_t nowtime;
    struct tm* p;
    time(&nowtime);
    p = localtime(&nowtime);
    string dir =
        "../ppm/" + left_append(p->tm_mon + 1) + left_append(p->tm_mday) + "/";
    //判断该文件夹是否存在
    if (access(dir.c_str(), 0) == -1) {
        mkdir(dir.c_str(), S_IRWXU);
    }
    for (int i = 0; i < 1000; ++i) {
        string path = dir + left_append(i, 3) + ".ppm";
        if (access(path.c_str(), 0) != F_OK) {
            return path;
        }
    }
    return dir + "a.ppm";
}

// ray 没有归一化
color ray_color_background(const ray& r);
color ray_color_world(const ray& r, const hittable_list& world, int depth);

int main(int argc, char** argv) {
    // 渲染结果
    string file_name;
    if (argc == 2) {
        file_name = argv[1];
    } else {
        file_name = get_file_name();
    }

    // 时间
    double t1 = get_second();

    // 重定向输出
    freopen(file_name.c_str(), "w", stdout);

    // Image

    const int spp = 1000;
    const int max_depth = 100;
    const double aspect_ratio = 16.0 / 9.0;
    // 图像分辨率
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World

    hittable_list world = random_scene();
    // auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0));
    // auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    // auto material_left = make_shared<dielectric>(1.5);
    // auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    // world.add(
    //     make_shared<sphere>(point3(0, -100.5, -1.0), 100.0,
    //     material_ground));
    // world.add(make_shared<sphere>(point3(0, 0, -1.0), 0.5, material_center));
    // world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5,
    // material_left));
    // // trick, 半径设置为负数, 这样可以让法相反向
    // // (因为我们在计算法相的时候, 有一个除以半径的操作)
    // world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), -0.4,
    // material_left)); world.add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5,
    // material_right));

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.5;

    camera cam(20, aspect_ratio, lookfrom, lookat, vup, aperture,
               dist_to_focus);

    // Render

    // 为了并行服务
    vec3** image_to_render = new vec3*[image_height];
    for (int i = 0; i < image_height; ++i) {
        image_to_render[i] = new vec3[image_width];
    }

    // 一次性设置域宽
    // std::cerr << "\rScanlines remaining: " << std::setw(3) <<
    // std::setfill('0') << std::right << 1 << std::flush;
    string ok_str = string(image_height, '<');
    std::cerr << "Start Rendering!\nOK Progress:\n|" << ok_str
              << "|\nNow Progress:\n|" << std::flush;

#pragma omp parallel for schedule(dynamic)
    for (int i = image_height - 1; i >= 0; --i) {
        std::cerr << "<" << std::flush;
        for (int j = 0; j < image_width; ++j) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < spp; ++s) {
                double u = (j + random_double()) / (image_width - 1);
                double v = (i + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color_world(r, world, max_depth);
            }
            image_to_render[i][j] = pixel_color;
        }
    }

    // 输出结果
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int i = image_height - 1; i >= 0; --i) {
        for (int j = 0; j < image_width; ++j) {
            write_color(std::cout, image_to_render[i][j], spp);
        }
    }

    std::cerr << "|\nDone.\n" << std::flush;

    // 释放
    for (int i = 0; i < image_height; ++i) {
        delete[] image_to_render[i];
    }
    delete[] image_to_render;

    std::cerr << "It cost " << (get_second() - t1) << " seconds.\n"
              << std::flush;
}

color ray_color_background(const ray& r) {
    vec3 unit_direction = r.get_direction_unit();
    double t = 0.5 * (unit_direction.y() + 1.0);
    // 线性混合两种颜色
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color_world(const ray& r, const hittable_list& world, int depth) {
    // 限制深度, 避免无止境递归下去
    if (depth <= 0) {
        return vec3(0, 0, 0);
    }

    hit_record rec;
    // shadow acne problem
    // 由于浮点数精度问题, 可能会出现发射出去的和自己相交的问题
    // 因此我们设置 min_v = 0.001 而不是 0
    if (world.hit(r, 0.001, infinity, rec)) {
        // (1) 命中球体则直接返回法线
        // return 0.5 * (rec.normal + 1.0);  // [-1, 1] => [0, 1]

        // (2) 根据材质返回光线
        ray scattered_ray;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered_ray)) {
            return attenuation *
                   ray_color_world(scattered_ray, world, depth - 1);
        }
        return color(0, 0, 0);
    }
    return ray_color_background(r);
}

// 一个场景
hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2,
                          b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}
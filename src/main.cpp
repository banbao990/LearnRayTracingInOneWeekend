#include <sys/stat.h>
#include <unistd.h>

#include <camera.hpp>
#include <color.hpp>
#include <hit_record.hpp>
#include <hittable.hpp>
#include <hittable_list.hpp>
#include <iomanip>
#include <iostream>
#include <lambertian.hpp>
#include <metal.hpp>
#include <material.hpp>
#include <memory>
#include <ray.hpp>
#include <rtweekend.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <vec3.hpp>

using std::string;

string get_file_name() {
    string dir = "ppm/";
    //判断该文件夹是否存在
    if (access(dir.c_str(), 0) == -1) {
        mkdir(dir.c_str(), S_IRWXU);
    }
    for (int i = 0; i < 1000; ++i) {
        string path = std::to_string(i);
        path = dir + string(3 - path.length(), '0') + path + ".ppm";
        if (access(path.c_str(), 0) != F_OK) {
            return path;
        }
    }
    return "ppm/a.ppm";
}

// ray 没有归一化
color ray_color_background(const ray& r);
color ray_color_world(const ray& r, const hittable_list& world, int depth);

// color write_color()

int main(int argc, char** argv) {
    // 渲染结果
    string file_name;
    if (argc == 2) {
        file_name = argv[1];
    } else {
        file_name = get_file_name();
    }

    // 重定向输出
    freopen(file_name.c_str(), "w", stdout);

    // Image

    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int spp = 10;
    const int max_depth = 10;

    // World

    hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.7, 0.3));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.6));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3(0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5, material_right));

    // Camera

    camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        // 一次性设置域宽
        std::cerr << "\rScanlines remaining: " << std::setw(3)
                  << std::setfill('0') << std::right << j << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < spp; ++s) {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color_world(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, spp);
        }
    }
    std::cerr << "\nDone.\n";
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
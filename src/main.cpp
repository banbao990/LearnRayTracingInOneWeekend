#include <omp.h>
#include <sys/stat.h>
#include <time.h>
#include <toyrender/All.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <toyrender/utils/rtweekend.h>

hittable_list random_scene();

// 获取当前时间(距离 0 点的秒数)
double get_second() {
    time_t nowtime;
    struct tm* p;
    time(&nowtime);
    p = localtime(&nowtime);
    return p->tm_sec + p->tm_min * 60.0 + p->tm_hour * 3600.0;
}

// 获取一个文件名
string get_file_name();

// ray 没有归一化
color ray_color_background(const ray& r,
                           const shared_ptr<scene_config>& config);
color ray_color_world(const ray& r, const shared_ptr<scene_config>& config,
                      int depth);

// 输出一张 perlin 噪声图
void write_out_the_whole_noise() {
    int H = 256;
    perlin p;
    std::cout << "P3\n" << H << ' ' << H << "\n255\n";
    for (int i = H - 1; i >= 0; --i) {
        for (int j = 0; j < H; ++j) {
            write_color(std::cout, p.noise(vec3(i, j, 0)), 1);
        }
    }
}

int main(int argc, char** argv) {
    // std::cout << a << std::endl;
    // return 0;

    // 参数
    double t0, t1, t2;
    t0 = get_second();

    // 渲染结果
    string file_name;
    if (argc == 2) {
        file_name = argv[1];
    } else {
        file_name = get_file_name();
    }

    // 重定向输出
    auto fret = freopen(file_name.c_str(), "w", stdout);
    if (fret == NULL) {
        std::cerr << "redirect the std::cout failed!\n" << std::flush;
    }

    //
    // World & Camera
    //

    shared_ptr<scene_config> config = make_shared<scene_config>();
    config->aspect_ratio = 16.0 / 9.0;
    config->image_width = 400;

    // basis_scene1(config);
    // random_scene1(config);
    // two_spheres(config);
    // two_perlin_spheres(config);
    // earth(config);
    // simple_light(config);
    // simple_light2(config);
    cornell_box(config);

    shared_ptr<camera> cam = config->cam;

    // BVH
    // (小场景) 构造 BVH 并不会加速
    // t1 = get_second();
    // std::cerr << "Constructing BVH!" << std::endl;
    // auto cc = world.get_count();
    // shared_ptr<bvh_node> w_bvh_t = make_shared<bvh_node>(world, t_min,
    // t_max);

    // hittable_list world_bvh;
    // world_bvh.add(w_bvh_t);
    // t2 = get_second();

    // std::cerr << "Constructing BVH End!\n    BVH Cost : " << (t2 - t1)
    //           << " Seconds!\n"
    //           << std::flush;

    //
    // Image
    //

    const int spp = 25;
    const int max_depth = 50;
    const double aspect_ratio = config->aspect_ratio;
    // 图像分辨率
    const int image_width = config->image_width;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //
    // Render
    //

    // 为了并行服务
    vec3** image_to_render = new vec3*[image_height];
    for (int i = 0; i < image_height; ++i) {
        image_to_render[i] = new vec3[image_width];
    }

    // 一次性设置域宽
    // std::cerr << "\rScanlines remaining: " << std::setw(3) <<
    // std::setfill('0') << std::right << 1 << std::flush;
    t1 = get_second();
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
                ray r = cam->get_ray(u, v);
                pixel_color += ray_color_world(r, config, max_depth);
                // pixel_color += ray_color_world(r, world_bvh, max_depth);
            }
            image_to_render[i][j] = pixel_color;
        }
    }
    t2 = get_second();
    std::cerr << "|\nRedering Done!\n    Rendering Cost: " << (t2 - t1)
              << " Seconds!\nWrite to the target file: " << file_name << '\n'
              << std::flush;

    // 输出结果
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int i = image_height - 1; i >= 0; --i) {
        for (int j = 0; j < image_width; ++j) {
            write_color(std::cout, image_to_render[i][j], spp);
        }
    }

    // 释放
    for (int i = 0; i < image_height; ++i) {
        delete[] image_to_render[i];
    }
    delete[] image_to_render;

    std::cerr << "    Total cost " << (get_second() - t0) << " Seconds!\n"
              << std::flush;
}

color ray_color_background(const ray& r,
                           const shared_ptr<scene_config>& config) {
    // 1. 线性混合两种颜色
    // vec3 unit_direction = r.get_direction_unit();
    // double t = 0.5 * (unit_direction.y() + 1.0);
    // return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);

    // 2. 直接返回一种背景色
    return config->background_color;
}

color ray_color_world(const ray& r, const shared_ptr<scene_config>& config,
                      int depth) {
    // 限制深度, 避免无止境递归下去
    if (depth <= 0) {
        return vec3(0, 0, 0);
    }

    hit_record rec;

    // 没有击中任何物体, 直接返回背景色
    // shadow acne problem
    // 由于浮点数精度问题, 可能会出现发射出去的和自己相交的问题
    // 因此我们设置 min_v = 0.001 而不是 0
    if (!config->world->hit(r, 0.001, infinity, rec)) {
        // return ray_color_background(r, config);
        return config->background_color;
    }

    // (1) 命中球体则直接返回法线
    // return 0.5 * (rec.normal + 1.0);  // [-1, 1] => [0, 1]

    // (2) 根据材质返回光线
    ray scattered_ray;
    color attenuation;
    color emitted;

    emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
    // 暂时的材质实现, 光源和非光源是完全分开的(光源不散射)
    // 光源(不进行散射的光源)
    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered_ray)) {
        return emitted;
    }
    // 非光源(可能发光)
    return emitted +
           attenuation * ray_color_world(scattered_ray, config, depth - 1);
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
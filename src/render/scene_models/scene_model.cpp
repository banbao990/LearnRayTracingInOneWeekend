#include <toyrender/All.h>
#include <toyrender/scene_models/scene_config.h>

#include <toyrender/util/rtweekend.hpp>

// 中间一个蓝色的小球, 左边是要给两层的玻璃球, 右边一个磨砂金属球
hittable_list basis_scene1(shared_ptr<scene_config> config) {
    // Camera
    config->cam = make_shared<camera>();

    // World
    hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(
        make_shared<sphere>(point3(0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_left));
    // trick, 半径设置为负数, 这样可以让法相反向
    // (因为我们在计算法向的时候, 有一个除以半径的操作)
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), -0.4, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5, material_right));

    return world;
}

// 底部一个大球作为地板, 上面有 3 个大球和若干小球
hittable_list random_scene1(shared_ptr<scene_config> config) {
    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    double t_min = 0.0, t_max = 1.0;

    config->cam =
        make_shared<camera>(20, config->aspect_ratio, lookfrom, lookat, vup,
                            aperture, dist_to_focus, t_min, t_max);

    // World
    hittable_list world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1),
                                                color(0.9, 0.9, 0.9));
    auto ground_material = make_shared<lambertian>(checker);
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
                    if (choose_mat < 0.4) {
                        // 移动的小球
                        auto center2 =
                            center + vec3(0, random_double(0, 0.5), 0);
                        world.add(make_shared<moving_sphere>(
                            center, center2, 0.0, 1.0, 0.2, sphere_material));
                    } else {
                        // 静止的小球
                        world.add(
                            make_shared<sphere>(center, 0.2, sphere_material));
                    }
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
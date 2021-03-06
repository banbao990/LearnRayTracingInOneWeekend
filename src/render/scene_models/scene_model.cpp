#include <toyrender/All.h>
#include <toyrender/texture/image_texture.h>
#include <toyrender/utils/rtweekend.h>

// 中间一个蓝色的小球, 左边是要给两层的玻璃球, 右边一个磨砂金属球
void basis_scene1(shared_ptr<scene_config> &config) {
  // Background Color
  config->background_color = color(0.70, 0.80, 1.00);

  // Camera
  config->cam = make_shared<camera>();

  // World
  shared_ptr<hittable_list> world = make_shared<hittable_list>();
  config->world = make_shared<hittable_list>();
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<dielectric>(1.5);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

  world->add(
      make_shared<sphere>(point3(0, -100.5, -1.0), 100.0, material_ground));
  world->add(make_shared<sphere>(point3(0, 0, -1.0), 0.5, material_center));
  world->add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_left));
  // trick, 半径设置为负数, 这样可以让法相反向
  // (因为我们在计算法向的时候, 有一个除以半径的操作)
  world->add(make_shared<sphere>(point3(-1.0, 0, -1.0), -0.4, material_left));
  world->add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5, material_right));

  config->world = world;
}

// 底部一个大球作为地板, 上面有 3 个大球和若干小球
void random_scene1(shared_ptr<scene_config> &config) {
  // Background Color
  config->background_color = color(0.70, 0.80, 1.00);

  // Camera
  point3 lookfrom(13, 2, 3);
  point3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;
  double t_min = 0.0, t_max = 1.0;

  config->cam = make_shared<camera>(20, config->aspect_ratio, lookfrom, lookat,
                                    vup, aperture, dist_to_focus, t_min, t_max);

  // World
  shared_ptr<hittable_list> world = make_shared<hittable_list>();
  auto checker =
      make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
  auto ground_material = make_shared<lambertian>(checker);
  world->add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = make_shared<lambertian>(albedo);
          if (choose_mat < 0.4) {
            // 移动的小球
            auto center2 = center + vec3(0, random_double(0, 0.5), 0);
            world->add(make_shared<moving_sphere>(center, center2, 0.0, 1.0,
                                                  0.2, sphere_material));
          } else {
            // 静止的小球
            world->add(make_shared<sphere>(center, 0.2, sphere_material));
          }
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = make_shared<metal>(albedo, fuzz);
          world->add(make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<dielectric>(1.5);
          world->add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  world->add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
  world->add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  world->add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  config->world = world;
}

// 一个小球在大球上面, 柏林噪声纹理
void two_spheres(shared_ptr<scene_config> &config) {
  // Background Color
  config->background_color = color(0.70, 0.80, 1.00);

  // Camera
  double vfov = 20.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(13, 2, 3);
  point3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);
  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();
  auto checker =
      make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
  world->add(make_shared<sphere>(point3(0, -10, 0), 10,
                                 make_shared<lambertian>(checker)));
  world->add(make_shared<sphere>(point3(0, 10, 0), 10,
                                 make_shared<lambertian>(checker)));

  config->world = world;
}

// 两个柏林噪声的小球
void two_perlin_spheres(shared_ptr<scene_config> &config) {
  // Background Color
  config->background_color = color(0.70, 0.80, 1.00);

  // Camera
  double vfov = 20.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(13, 2, 3);
  point3 lookat(0, 2, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();
  auto perlin_texture = make_shared<perlin_noise_texture>(4.0);

  world->add(make_shared<sphere>(point3(0, -1000, 0), 1000,
                                 make_shared<lambertian>(perlin_texture)));
  world->add(make_shared<sphere>(point3(0, 2, 0), 2,
                                 make_shared<lambertian>(perlin_texture)));

  config->world = world;
}

// 一个地球场景, 测试 image_texture
void earth(shared_ptr<scene_config> &config) {
  // Background Color
  config->background_color = color(0.70, 0.80, 1.00);

  // Camera
  double vfov = 20.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(13, 2, 3);
  point3 lookat = point3(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto earth_texture = make_shared<image_texture>("images/earthmap.jpg");
  auto earth_surface = make_shared<lambertian>(earth_texture);
  auto globe = make_shared<sphere>(point3(0, 0, 0), 2, earth_surface);

  world->add(globe);

  config->world = world;
}

// 有一个简单的 xy 面光源, 中间一个小球, 顶上一个球面光源
void simple_light(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  double vfov = 20.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(26, 3, 6);
  point3 lookat = point3(0, 2, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto pertext = make_shared<perlin_noise_texture>(4);
  world->add(make_shared<sphere>(point3(0, -1000, 0), 1000,
                                 make_shared<lambertian>(pertext)));
  world->add(make_shared<sphere>(point3(0, 2, 0), 2,
                                 make_shared<lambertian>(pertext)));

  auto difflight = make_shared<diffuse_light>(color(4, 4, 4));
  world->add(make_shared<sphere>(point3(0, 7, 0), 2, difflight));
  world->add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));

  config->world = world;
}

// 3 个面光源, 中间一个小球
// 用于测试平面有没有写错(发现并测不出来)
void simple_light2(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  double vfov = 20.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(26, 3, 6);
  point3 lookat = point3(0, 2, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto pertext = make_shared<perlin_noise_texture>(4);
  world->add(make_shared<sphere>(point3(0, -1000, 0), 1000,
                                 make_shared<lambertian>(pertext)));
  world->add(make_shared<sphere>(point3(0, 2, 0), 2,
                                 make_shared<lambertian>(pertext)));

  world->add(make_shared<xy_rect>(3, 5, 1, 3, -2,
                                  make_shared<diffuse_light>(color(4, 0, 0))));
  world->add(make_shared<yz_rect>(1, 3, 3, 5, -2,
                                  make_shared<diffuse_light>(color(0, 4, 0))));
  world->add(make_shared<xz_rect>(1, 3, 1, 3, 6,
                                  make_shared<diffuse_light>(color(0, 0, 4))));

  config->world = world;
}

// Cornell Box
void cornell_box_origin(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  config->aspect_ratio = 1.0;
  double vfov = 40.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(278, 278, -800);
  point3 lookat = point3(278, 278, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  config->image_width = 400;
  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
  auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
  auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
  auto light = make_shared<diffuse_light>(color(15, 15, 15));

  world->add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
  world->add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
  // 光源稍微隔开一点距离
  auto light_object = make_shared<flip_face>(
      make_shared<xz_rect>(213, 343, 227, 332, 554, light));
  world->add(light_object);
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
  world->add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

  shared_ptr<hittable> box1 =
      make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
  box1 = make_shared<rotate_y>(box1, 15);
  box1 = make_shared<translate>(box1, vec3(265, 0, 295));
  world->add(box1);

  shared_ptr<hittable> box2 =
      make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white);
  box2 = make_shared<rotate_y>(box2, -18);
  box2 = make_shared<translate>(box2, vec3(130, 0, 65));
  world->add(box2);

  auto important_item = make_shared<hittable_list>();
  important_item->add(light_object);
  config->important_item = important_item;

  config->world = world;
}

// Cornell Box
void cornell_box(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  config->aspect_ratio = 1.0;
  double vfov = 40.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(278, 278, -800);
  point3 lookat = point3(278, 278, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  config->image_width = 400;
  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
  auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
  auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
  auto light = make_shared<diffuse_light>(color(15, 15, 15));

  world->add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
  world->add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
  // 光源稍微隔开一点距离
  // world->add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
  auto light_object = make_shared<flip_face>(
      make_shared<xz_rect>(213, 343, 227, 332, 554, light));
  world->add(light_object);
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
  world->add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

  // 两个小盒子
  // world->add(make_shared<box>(
  // point3(265, 0, 295), point3(430, 330, 460), white));
  // world->add(make_shared<box>(
  // point3(130, 0, 65), point3(295, 165, 230), white));

  shared_ptr<hittable> box1 =
      make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
  box1 = make_shared<rotate_y>(box1, 15);
  box1 = make_shared<translate>(box1, vec3(265, 0, 295));
  world->add(box1);

  // shared_ptr<hittable> box2 =
  //     make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white);
  // box2 = make_shared<rotate_y>(box2, -18);
  // box2 = make_shared<translate>(box2, vec3(130, 0, 65));
  // world->add(box2);

  // 箱子换为球体
  auto glass = make_shared<dielectric>(1.5);
  auto ball = make_shared<sphere>(point3(190, 90, 190), 90, glass);
  world->add(ball);

  auto important_item = make_shared<hittable_list>();
  important_item->add(light_object);
  important_item->add(ball);
  config->important_item = important_item;

  config->world = world;
}

// Cornell Box (加了镜面)
void cornell_box_specular(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  config->aspect_ratio = 1.0;
  double vfov = 40.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(278, 278, -800);
  point3 lookat = point3(278, 278, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  config->image_width = 400;
  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
  auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
  auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
  auto light = make_shared<diffuse_light>(color(15, 15, 15));

  world->add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
  world->add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
  // 光源稍微隔开一点距离
  config->important_item = make_shared<flip_face>(
      make_shared<xz_rect>(213, 343, 227, 332, 554, light));
  world->add(config->important_item);
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
  world->add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

  // 两个小盒子
  // world->add(make_shared<box>(
  // point3(265, 0, 295), point3(430, 330, 460), white));
  // world->add(make_shared<box>(
  // point3(130, 0, 65), point3(295, 165, 230), white));

  // 铝
  auto aluminum = make_shared<metal>(color(0.8, 0.85, 0.88));

  shared_ptr<hittable> box1 =
      make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), aluminum);
  box1 = make_shared<rotate_y>(box1, 15);
  box1 = make_shared<translate>(box1, vec3(265, 0, 295));
  world->add(box1);

  shared_ptr<hittable> box2 =
      make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white);
  box2 = make_shared<rotate_y>(box2, -18);
  box2 = make_shared<translate>(box2, vec3(130, 0, 65));
  world->add(box2);

  // auto glass = make_shared<dielectric>(1.5);
  // world->add(make_shared<sphere>(point3(190, 90, 190), 90, glass));

  config->world = world;
}

// Cornell Box 加上参与介质的效果(烟雾)
void cornell_box_smoke(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  config->aspect_ratio = 1.0;
  double vfov = 40.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(278, 278, -800);
  point3 lookat = point3(278, 278, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto red = make_shared<lambertian>(color(.65, .05, .05));
  auto white = make_shared<lambertian>(color(.73, .73, .73));
  auto green = make_shared<lambertian>(color(.12, .45, .15));
  auto light = make_shared<diffuse_light>(color(7, 7, 7));

  world->add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
  world->add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
  world->add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
  world->add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

  shared_ptr<hittable> box1 =
      make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
  box1 = make_shared<rotate_y>(box1, 15);
  box1 = make_shared<translate>(box1, vec3(265, 0, 295));

  shared_ptr<hittable> box2 =
      make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white);
  box2 = make_shared<rotate_y>(box2, -18);
  box2 = make_shared<translate>(box2, vec3(130, 0, 65));

  world->add(make_shared<constant_medium>(box1, 0.01, color(0, 0, 0)));
  world->add(make_shared<constant_medium>(box2, 0.01, color(1, 1, 1)));

  config->world = world;
}

// 教程中给的 Ray Tracing: The Next Week 的最终场景
void rtnw_final_scene(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  config->aspect_ratio = 1.0;
  double vfov = 40.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(478, 278, -600);
  point3 lookat(278, 278, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  config->image_width = 400;

  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  hittable_list boxes1;
  auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

  const int boxes_per_side = 20;
  for (int i = 0; i < boxes_per_side; i++) {
    for (int j = 0; j < boxes_per_side; j++) {
      auto w = 100.0;
      auto x0 = -1000.0 + i * w;
      auto z0 = -1000.0 + j * w;
      auto y0 = 0.0;
      auto x1 = x0 + w;
      auto y1 = random_double(1, 101);
      auto z1 = z0 + w;

      boxes1.add(
          make_shared<box>(point3(x0, y0, z0), point3(x1, y1, z1), ground));
    }
  }

  world->add(make_shared<bvh_node>(boxes1, 0, 1));

  auto light = make_shared<diffuse_light>(color(7, 7, 7));
  world->add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

  auto center1 = point3(400, 400, 200);
  auto center2 = center1 + vec3(30, 0, 0);
  auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
  world->add(make_shared<moving_sphere>(center1, center2, 0, 1, 50,
                                        moving_sphere_material));

  world->add(make_shared<sphere>(point3(260, 150, 45), 50,
                                 make_shared<dielectric>(1.5)));
  world->add(make_shared<sphere>(
      point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)));

  auto boundary = make_shared<sphere>(point3(360, 150, 145), 70,
                                      make_shared<dielectric>(1.5));
  world->add(boundary);
  world->add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
  boundary =
      make_shared<sphere>(point3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
  world->add(make_shared<constant_medium>(boundary, .0001, color(1, 1, 1)));

  auto emat = make_shared<lambertian>(
      make_shared<image_texture>("images/earthmap.jpg"));
  world->add(make_shared<sphere>(point3(400, 200, 400), 100, emat));
  auto pertext = make_shared<perlin_noise_texture>(0.1);
  world->add(make_shared<sphere>(point3(220, 280, 300), 80,
                                 make_shared<lambertian>(pertext)));

  hittable_list boxes2;
  auto white = make_shared<lambertian>(color(.73, .73, .73));
  int ns = 1000;
  for (int j = 0; j < ns; j++) {
    boxes2.add(make_shared<sphere>(point3::random(0, 165), 10, white));
  }

  world->add(make_shared<translate>(
      make_shared<rotate_y>(make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
      vec3(-100, 270, 395)));

  config->world = world;
}

void toy_scene1(shared_ptr<scene_config> &config) {
  // Background Color
  // Camera
  config->aspect_ratio = 1.0;
  double vfov = 40.0;
  auto aperture = 0.0; // 没有模糊
  point3 lookfrom(278, 278, -800);
  point3 lookat = point3(278, 278, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  double t_min = 0.0, t_max = 1.0;

  config->cam =
      make_shared<camera>(vfov, config->aspect_ratio, lookfrom, lookat, vup,
                          aperture, dist_to_focus, t_min, t_max);

  config->image_width = 400;
  // World
  config->world = make_shared<hittable_list>();
  shared_ptr<hittable_list> world = make_shared<hittable_list>();

  auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
  auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
  auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
  auto blue = make_shared<lambertian>(color(0.26, 0.57, 0.84));
  auto light = make_shared<diffuse_light>(color(15));
  auto small_light = make_shared<diffuse_light>(color(7));
  auto aluminum = make_shared<metal>(color(0.8, 0.85, 0.88));
  auto glass = make_shared<dielectric>(1.5);

  world->add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
  world->add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
  world->add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
  world->add(make_shared<xy_rect>(0, 555, 0, 555, 555, aluminum));

  world->add(
      make_shared<box>(point3(100, 350, 295), point3(455, 400, 400), blue));

  shared_ptr<sphere> ball;
  shared_ptr<material> mat_ptr[] = {red, glass, aluminum};
  const int size = sizeof(mat_ptr) / sizeof(mat_ptr[0]);
  const int delta_x = (550 - 100) / size;
  {
    const int r = 60;
    int i = 0;
    for (const auto &m : mat_ptr) {
      ball = make_shared<sphere>(point3(100 + (i++) * delta_x, r, 190), r, m);
      world->add(ball);
    }
  }

  auto important_item = make_shared<hittable_list>();
  std::shared_ptr<hittable> light_object;
  {
    // 光源
    const int size = 3;
    for (int i = 0; i < size; ++i) {
      light_object = make_shared<sphere>(
          point3(100 + (455 / size) * i, 100, 455), 10, small_light);
      world->add(light_object);
      important_item->add(light_object);
    }
    light_object = make_shared<flip_face>(
        make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    world->add(light_object);
    important_item->add(light_object);
  }

  config->important_item = important_item;
  config->world = world;
}
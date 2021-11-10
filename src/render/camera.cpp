#include <camera.hpp>

camera::camera(point3 _origin) : origin(_origin) {
    // 相机的朝向, 视图的长宽比、大小写死
    double aspect_ratio = 16.0 / 9.0;
    double view_point_height = 2.0;
    double view_point_width = view_point_height * aspect_ratio;
    double focal_length = 1.0;

    // 参数设置
    horizontal = vec3(view_point_width, 0, 0);
    vertical = vec3(0, view_point_height, 0);
    lower_left_corner =
        origin - horizontal / 2.0 - vertical / 2.0 - vec3(0, 0, focal_length);
}

camera::camera() : camera(point3(0, 0, 0)) {}

camera::~camera() {}

ray camera::get_ray(double u, double v) const {
    return ray(origin,
               lower_left_corner + u * horizontal + v * vertical - origin);
}

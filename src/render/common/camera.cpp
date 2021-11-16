#include <toyrender/common/camera.h>

#include <toyrender/util/rtweekend.hpp>

camera::camera() : camera(90.0, 16.0 / 9) {}

camera::camera(double _vfov, double _aspect_ratio)
    : camera(_vfov, _aspect_ratio, vec3(0, 0, 0), vec3(0, 0, -1),
             vec3(0, 1, 0)) {}

camera::camera(double _vfov, double _aspect_ratio, point3 _lookfrom,
               point3 _lookat, vec3 _vup, double _aperture,
               double _focus_distance, double _time1, double _time2)
    : aspect_ratio(_aspect_ratio), time1(_time1), time2(_time2) {
    double theta = degrees_to_radians(_vfov);
    double h = std::tan(theta / 2.0);
    double view_point_height = 2.0 * h;
    double view_point_width = view_point_height * aspect_ratio;

    // 坐标系(右手坐标系)
    w = (_lookfrom - _lookat).unit_vector();
    u = _vup.cross(w).unit_vector();
    v = w.cross(u);

    // 参数设置
    origin = _lookfrom;
    // 为啥要乘 _focus_distance: 等比例放缩
    horizontal = _focus_distance * view_point_width * u;
    vertical = _focus_distance * view_point_height * v;
    // 成像位置还是在相机坐标系的 z=-1 平面
    lower_left_corner =
        origin - horizontal / 2.0 - vertical / 2.0 - _focus_distance * w;
    lens_radius = _aperture / 2;
}

camera::~camera() {}

ray camera::get_ray(double _u, double _v) const {
    vec3 offset;
    // 光圈大小为 0 的时候不采样(0 可以精确表达)
    if (lens_radius != 0) {
        // 在透镜上均匀采样
        vec3 rd = lens_radius * vec3::random_in_unit_disk();
        offset = u * rd.x() + v * rd.y();
    }
    return ray(
        origin + offset,
        lower_left_corner + _u * horizontal + _v * vertical - origin - offset,
        random_double(time1, time2));
}

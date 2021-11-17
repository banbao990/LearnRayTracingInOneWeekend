#include <toyrender/object/moving_sphere.h>
#include <toyrender/object/sphere.h>

#include <cmath>

moving_sphere::moving_sphere(point3 _center1, point3 _center2, double _time1,
                             double _time2, double _radius,
                             shared_ptr<material> _matrial_ptr)
    : center1(_center1),
      center2(_center2),
      time1(_time1),
      time2(_time2),
      radius(_radius),
      mat_ptr(_matrial_ptr) {}

moving_sphere::~moving_sphere() {}

point3 moving_sphere::get_center(double t) const {
    // 只是考虑简单的线性插值(运动是匀速直线运动)
    return center1 + (t - time1) / (time2 - time1) * (center2 - center1);
}

bool moving_sphere::hit(const ray& r, double t_min, double t_max,
                        hit_record& rec) const {
    point3 center = get_center(r.get_time());
    vec3 oc = r.get_origin() - center;
    double a = r.get_direction().length_squared();
    double half_b = r.get_direction().dot(oc);
    double c = oc.length_squared() - radius * radius;
    double delta = half_b * half_b - a * c;
    // 擦边不算相交
    if (delta <= 0) {
        return false;
    } else {
        // 比较接近的点
        double t = (-half_b - std::sqrt(delta)) / (a);
        if (t <= t_min || t >= t_max) {
            // 另外一个点
            t = (-half_b + std::sqrt(delta)) / (a);
            if (t <= t_min || t >= t_max) {
                return false;
            }
        }
        rec.t = t;
        rec.p = r.at(t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;
        sphere::get_sphere_uv(outward_normal, rec.u, rec.v);
        return true;
    }
}

bool moving_sphere::bounding_box(double time0, double time1,
                                 aabb& output_box) const {
    aabb box0(get_center(time0) - radius, get_center(time0) + radius);
    aabb box1(get_center(time1) - radius, get_center(time1) + radius);
    output_box = box0 + box1;
    return true;
}
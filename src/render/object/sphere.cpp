#include <toyrender/object/sphere.h>

#include <cmath>

sphere::sphere() {}
sphere::sphere(double _radius) : radius(_radius) {}
sphere::sphere(point3 _center, double _radius, shared_ptr<material> _mat_ptr)
    : center(_center), radius(_radius), mat_ptr(_mat_ptr) {}
sphere::~sphere() {}

vec3 sphere::get_center() const { return center; }
double sphere::get_radius() const { return radius; }

bool sphere::hit(const ray& r, double t_min, double t_max,
                 hit_record& rec) const {
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
        return true;
    }
}

bool sphere::bounding_box(double time0, double time1, aabb& output_box) const {
    // 不会动
    output_box = aabb(center - radius, center + radius);
    return true;
}
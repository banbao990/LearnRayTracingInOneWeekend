#include <toyrender/object/sphere.h>

#include <cmath>
#include <toyrender/utils/rtweekend.h>
#include <toyrender/common/onb.h>

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
        get_sphere_uv(outward_normal, rec.u, rec.v);
        return true;
    }
}

bool sphere::bounding_box(double time0, double time1, aabb& output_box) const {
    // 不会动
    output_box = aabb(center - radius, center + radius);
    return true;
}



vec3 sphere::random(const vec3 &origin) const {
    vec3 direction = center - origin;
    double distance_squared = direction.length_squared();
    onb uvw;
    uvw.build_from_w(direction);
    return uvw.local(vec3::random_to_sphere(radius, distance_squared));
}

double sphere::pdf_value(const point3 &origin, const vec3 &direction) const {
    hit_record rec;
    if(!this->hit(ray(origin, direction), 0.001, infinity, rec)) {
        return 0.0;
    }

    double cosine_max = sqrt(1-radius*radius/(center - origin).length_squared());
    double pdf = 1/(pi2*(1 - cosine_max));

    return pdf;
}

//
// static
//

void sphere::get_sphere_uv(const point3& p, double& u, double& v) {
    double theta = std::acos(-p.y());
    double phi = std::atan2(-p.z(), p.x()) + pi;
    u = phi / pi2;
    v = theta / pi;
}
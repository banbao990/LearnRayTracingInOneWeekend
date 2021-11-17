#include <toyrender/material/lambertian.h>
#include <toyrender/texture/solid_color.h>
using std::make_shared;

// 默认吸收一半, 反射一半
lambertian::lambertian() : lambertian(color(0.5, 0.5, 0.5)) {}
lambertian::lambertian(color _albedo)
    : albedo(make_shared<solid_color>(_albedo)) {}
lambertian::lambertian(shared_ptr<texture> _albebo) : albedo(_albebo) {}
lambertian::~lambertian() {}

bool lambertian::scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const {
    vec3 dir = rec.normal + vec3::random_in_unit_sphere_to_surface();
    // vec3 dir = rec.normal + vec3::random_on_unit_sphere_surface();
    // vec3 dir = rec.normal + vec3::random_in_unit_sphere();
    // vec3 dir = vec3::random_in_unit_hemisphere(rec.normal);

    // 如果新的方向近似为 0(新生成的方向和法线方向相反), 会出现问题
    if (dir.near_zero()) {
        dir = rec.normal;  // 不太懂为什么可以这样处理
    }

    scattered = ray(rec.p, dir, r_in.get_time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
}
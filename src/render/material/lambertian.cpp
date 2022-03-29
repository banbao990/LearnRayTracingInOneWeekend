#include <toyrender/common/onb.h>
#include <toyrender/material/lambertian.h>
#include <toyrender/pdf/cosine_pdf.h>
#include <toyrender/texture/solid_color.h>
#include <toyrender/utils/h_help.h>
#include <toyrender/utils/rtweekend.h>

// 默认吸收一半, 反射一半
lambertian::lambertian() : lambertian(color(0.5, 0.5, 0.5)) {}
lambertian::lambertian(color _albedo)
    : albedo(make_shared<solid_color>(_albedo)) {}
lambertian::lambertian(shared_ptr<texture> _albebo) : albedo(_albebo) {}
lambertian::~lambertian() {}

bool lambertian::scatter(const ray& r_in,
                         const hit_record& rec,
                         color& attenuation,
                         ray& scattered) const {
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

bool lambertian::scatter(const ray& r_in,
                         const hit_record& rec,
                         scatter_record& srec) const {
    srec.is_specular = false;
    srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
    srec.pdf_ptr = make_shared<cosine_pdf>(rec.normal);
    return true;
}

double lambertian::scattering_pdf(const ray& r_in,
                                  const hit_record& rec,
                                  ray& scattered) const {
    double cosine = rec.normal.dot(scattered.get_direction_unit());
    return (cosine < 0) ? 0 : (cosine / pi);
}
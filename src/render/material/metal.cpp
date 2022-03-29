#include <toyrender/material/metal.h>

// 默认吸收一半, 反射一半
metal::metal() : albedo(color(0.5, 0.5, 0.5)) {}
metal::metal(color _albodo, double _fuzz) : albedo(_albodo), fuzz(_fuzz) {}
metal::~metal() {}
bool metal::scatter(const ray& r_in,
                    const hit_record& rec,
                    color& attenuation,
                    ray& scattered) const {
    vec3 reflected = vec3::reflect(r_in.get_direction_unit(), rec.normal);
    attenuation = albedo;
    scattered = ray(rec.p, reflected + fuzz * vec3::random_in_unit_sphere(),
                    r_in.get_time());
    return reflected.dot(rec.normal) > 0;  // TODO 暂时没有理解, 感觉一定成立啊
}

bool metal::scatter(const ray& r_in,
                    const hit_record& rec,
                    scatter_record& srec) const {
    vec3 reflected = vec3::reflect(r_in.get_direction_unit(), rec.normal);

    srec.attenuation = albedo;
    srec.is_specular = true;
    srec.pdf_ptr = nullptr;
    srec.specular_ray =
        ray(rec.p, reflected + fuzz * vec3::random_in_unit_sphere());

    return true;
}

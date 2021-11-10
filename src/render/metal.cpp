#include <metal.hpp>

// 默认吸收一半, 反射一半
metal::metal() : albedo(color(0.5, 0.5, 0.5)) {}
metal::metal(color _albodo) : albedo(_albodo) {}
metal::~metal() {}
bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                    ray& scattered) const {
    vec3 reflected = vec3::reflect(r_in.get_direction_unit(), rec.normal);
    attenuation = albedo;
    scattered = ray(rec.p, reflected);
    return reflected.dot(rec.normal) > 0;  // TODO 暂时没有理解, 感觉一定成立啊
}

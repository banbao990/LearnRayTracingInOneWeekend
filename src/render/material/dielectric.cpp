#include <toyrender/material/dielectric.h>

#include <toyrender/utils/rtweekend.h>

dielectric::dielectric() : ir(1.0) {}
dielectric::dielectric(double _ir) : ir(_ir) {}
dielectric::~dielectric() {}

bool dielectric::scatter(const ray &r_in, const hit_record &rec,
                         color &attenuation, ray &scattered) const {
  // 不衰减
  attenuation = color(1.0, 1.0, 1.0);

  vec3 ray_in_unit = r_in.get_direction_unit();
  double cos_theta = std::fmin(-ray_in_unit.dot(rec.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  // 折射率(默认交界面中有一个是空气)
  double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
  bool cannot_refract = sin_theta * refraction_ratio > 1.0;

  vec3 dir_out;
  // 计算反射的概率
  double reflection_rate =
      dielectric::reflectance_rate_schlick(cos_theta, refraction_ratio);
  if (cannot_refract || reflection_rate > random_double()) {
    // 全反射 + 反射
    dir_out = vec3::reflect(ray_in_unit, rec.normal);
  } else {
    // 折射
    dir_out = vec3::refract(ray_in_unit, rec.normal, refraction_ratio);
  }
  scattered = ray(rec.p, dir_out, r_in.get_time());
  return true;
}

bool dielectric::scatter(const ray &r_in, const hit_record &rec,
                         scatter_record &srec) const {
  // 不衰减
  srec.attenuation = color(1.0, 1.0, 1.0);
  srec.is_specular = true;
  srec.pdf_ptr = nullptr;

  vec3 ray_in_unit = r_in.get_direction_unit();
  double cos_theta = std::fmin(-ray_in_unit.dot(rec.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  // 折射率(默认交界面中有一个是空气)
  double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
  bool cannot_refract = sin_theta * refraction_ratio > 1.0;

  vec3 dir_out;
  // 计算反射的概率
  double reflection_rate =
      dielectric::reflectance_rate_schlick(cos_theta, refraction_ratio);
  if (cannot_refract || reflection_rate > random_double()) {
    // 全反射 + 反射
    dir_out = vec3::reflect(ray_in_unit, rec.normal);
  } else {
    // 折射
    dir_out = vec3::refract(ray_in_unit, rec.normal, refraction_ratio);
  }

  srec.specular_ray = ray(rec.p, dir_out, r_in.get_time());
  return true;
}

//
// static
//
double dielectric::reflectance_rate_schlick(double cosine, double ref_idx) {
  double r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 *= r0;
  return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}
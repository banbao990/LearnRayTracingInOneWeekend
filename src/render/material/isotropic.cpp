#include <toyrender/material/isotropic.h>
#include <toyrender/texture/solid_color.h>

isotropic::isotropic() {}
isotropic::isotropic(shared_ptr<texture> _albedo) : albedo(_albedo) {}
isotropic::isotropic(color _albedo)
    : albedo(make_shared<solid_color>(_albedo)) {}
isotropic::~isotropic() {}

bool isotropic::scatter(const ray &r_in, const hit_record &rec,
                        color &attenuation, ray &scattered) const {
  scattered = ray(rec.p, vec3::random_in_unit_sphere(), r_in.get_time());
  attenuation = albedo->value(rec.u, rec.v, rec.p);
  return true;
}
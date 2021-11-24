#include <toyrender/material/diffuse_light.h>

diffuse_light::diffuse_light()
    : emit(make_shared<solid_color>(1.0, 1.0, 1.0)) {}
diffuse_light::diffuse_light(shared_ptr<texture> _emit) : emit(_emit) {}
diffuse_light::diffuse_light(color c) : emit(make_shared<solid_color>(c)) {}
diffuse_light::~diffuse_light() {}

bool diffuse_light::scatter(const ray& r_in,
                            const hit_record& rec,
                            color& attenuation,
                            ray& scattered) const {
    return false;
}

color diffuse_light::emitted(double u, double v, const point3& p) const {
    return emit->value(u, v, p);
}
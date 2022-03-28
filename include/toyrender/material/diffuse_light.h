#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "..//utils/h_help.h"
#include "../texture/solid_color.h"
#include "../texture/texture.h"
#include "material.h"

class diffuse_light : public material {
   private:
    shared_ptr<texture> emit;

   public:
    // 默认发白光
    diffuse_light();
    diffuse_light(shared_ptr<texture> _emit);
    diffuse_light(color c);
    ~diffuse_light();

    // 光源不反射光, 返回 false
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         color& attenuation,
                         ray& scattered) const override;

    // 发光根据纹理坐标 (u,v) 以及点的位置 p 返回发光的颜色
    // 某些纹理的颜色和位置 p 有关(例如之前实现的 perlin_texture)
    virtual color emitted(double u, double v, const point3& p) const override;
    virtual color emitted(const ray& ray_in,
                          const hit_record& rec,
                          double u,
                          double v,
                          const point3& p) const override;
};

#endif
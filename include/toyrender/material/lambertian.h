#ifndef LABERTIAN_H
#define LABERTIAN_H

#include "../common/color.h"
#include "../texture/texture.h"
#include "material.h"

// 朗伯材质, 反射方向满足余弦定律
class lambertian : public material {
   private:
    shared_ptr<texture> albedo;

   public:
    lambertian();
    lambertian(color _albebo);
    lambertian(shared_ptr<texture> _albebo);
    ~lambertian();

    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const override;
};

#endif
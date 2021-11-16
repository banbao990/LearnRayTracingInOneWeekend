#ifndef LABERTIAN_H
#define LABERTIAN_H

#include "color.hpp"
#include "material.hpp"

// 朗伯材质, 反射方向满足余弦定律
class lambertian : public material {
   private:
    color albedo;

   public:
    lambertian();
    lambertian(color _albebo);
    ~lambertian();

    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const override;
};

#endif
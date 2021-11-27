#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "../texture/texture.h"
#include "../utils/h_help.h"
#include "material.h"

// 各向同性散射材质
class isotropic : public material {
   private:
    shared_ptr<texture> albedo;

   public:
    isotropic();
    isotropic(shared_ptr<texture> _albedo);
    isotropic(color _albedo);
    ~isotropic();

    // 整个球面均匀采样
    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const override;
};

#endif
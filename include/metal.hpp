#ifndef METAL_H
#define METAL_H

#include "color.hpp"
#include "material.hpp"

class metal : public material {
   private:
    color albedo;
    double fuzz;  // 粗糙程度, 值越大越粗糙

   public:
    metal();
    metal(color _albedo, double _fuzz = 0);
    ~metal();

    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const override;
};

#endif
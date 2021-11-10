#ifndef METAL_H
#define METAL_H

#include "color.hpp"
#include "material.hpp"

class metal : public material {
   private:
    color albedo;

   public:
    metal();
    metal(color _albedo);
    ~metal();

    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const override;
};

#endif
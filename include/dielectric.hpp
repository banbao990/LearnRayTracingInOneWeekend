#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.hpp"
#include "vec3.hpp"

// 半反半透材质
class dielectric : public material {
   private:
    double ir;  // 折射系数
   public:
    dielectric();
    dielectric(double _ir);
    ~dielectric();

    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const override;

    // Schlick's 估计反射的概率, 近似菲涅尔项
    static double reflectance_rate_schlick(double cosine, double ref_idx);
};

#endif
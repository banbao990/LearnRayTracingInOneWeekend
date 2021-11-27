#ifndef MATERIAL_H
#define MATERIAL_H

#include "../common/color.h"
#include "../common/ray.h"
#include "../object/hit_record.h"

struct hit_record;

// 材质抽象类
class material {
   public:
    // 给定一条入射光线, 返回一条出射光线(BRDF), 设置 attenuation
    // 如果是是不散射的材质(例如只发光而不散射的材质), 则返回 false
    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const = 0;

    // 根据纹理坐标以及
    // 默认材质不发光
    virtual color emitted(double u, double v, const point3& p) const {
        return color(0);
    };
};

#endif
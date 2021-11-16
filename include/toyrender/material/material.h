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
    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const = 0;
};

#endif
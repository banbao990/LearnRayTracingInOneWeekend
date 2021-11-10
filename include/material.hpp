#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.hpp"
#include "hit_record.hpp"
#include "ray.hpp"

struct hit_record;

// 材质抽象类
class material {
   public:
    // 给定一条入射光线, 返回一条出射光线(BRDF), 设置 attenuation
    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const = 0;
};

#endif
#ifndef HITTABLE_H
#define HITTABLE_H

#include "../common/ray.h"
#include "aabb.h"
#include "hit_record.h"
#include "../utils/h_help.h"

// 场景中的物体
class hittable {
   public:
    virtual bool hit(const ray& r,
                     double t_min,
                     double t_max,
                     hit_record& rec) const = 0;
    virtual bool bounding_box(double time0,
                              double time1,
                              aabb& output_box) const = 0;

    // 采样, 朝着这个物体采样
    virtual vec3 random(const point3& origin) const { 
         CHECK_OVERRIDE("hittable", "random");
         return vec3(1, 0, 0); 
    }
    
    virtual double pdf_value(const point3& origin,
                             const vec3& direction) const {
        CHECK_OVERRIDE("hittable", "pdf_value");
        return 0.0;
    };
};

#endif
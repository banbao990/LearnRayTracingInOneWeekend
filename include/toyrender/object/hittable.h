#ifndef HITTABLE_H
#define HITTABLE_H

#include "../common/ray.h"
#include "aabb.h"
#include "hit_record.h"

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
    virtual vec3 random(const point3& origin) const { return vec3(1, 0, 0); }
    virtual double pdf_value(const point3& origin,
                             const vec3& direction) const {
        static volatile int ccc = 0;
        if (ccc++ < 3) {
            std::cout << "hittable: " << ccc << std::endl;
        }
        return 0.0;
    };
};

#endif
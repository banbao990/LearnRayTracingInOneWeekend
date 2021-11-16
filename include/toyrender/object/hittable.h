#ifndef HITTABLE_H
#define HITTABLE_H

#include "../common/ray.h"
#include "hit_record.h"

// 场景中的物体
class hittable {
   public:
    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const = 0;
};

#endif
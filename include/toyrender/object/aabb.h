#ifndef AABB_H
#define AABB_H

#include "../common/ray.h"
#include "../common/vec3.h"

class aabb {
   private:
    point3 mininum, maxinum;

   public:
    aabb();
    // 只是简单复制, 不会对 _min,_max 进行大小对比
    aabb(point3 _min, point3 _max);
    ~aabb();

    // 两个包围盒求更大的包围盒
    aabb operator+(const aabb& box) const;
    aabb& operator+=(const aabb& box);

    point3 get_min() const;
    point3 get_max() const;

    bool hit(const ray& r, double t_min, double t_max) const;
};

#endif
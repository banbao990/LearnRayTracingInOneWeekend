#ifndef SPHERE_H
#define SPHERE_H

#include "../common/vec3.h"
#include "../material/material.h"
#include "hit_record.h"
#include "hittable.h"
#include "aabb.h"

// 球体
class sphere : public hittable {
   private:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;

   public:
    sphere();
    sphere(double _radius);
    sphere(point3 _center, double _radius, shared_ptr<material> _mat_ptr);
    ~sphere();

    vec3 get_center() const;
    double get_radius() const;

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1,
                              aabb& output_box) const override;
};

#endif
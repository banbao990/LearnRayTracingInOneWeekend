#ifndef SPHERE_H
#define SPHERE_H

#include "../common/vec3.h"
#include "../material/material.h"
#include "hit_record.h"
#include "hittable.h"

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

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;

    vec3 get_center() const;
    double get_radius() const;
};

#endif
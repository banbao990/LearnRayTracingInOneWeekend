#ifndef SPHERE_H
#define SPHERE_H

#include "../common/vec3.h"
#include "../material/material.h"
#include "aabb.h"
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

    vec3 get_center() const;
    double get_radius() const;

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1,
                              aabb& output_box) const override;
    //
    // static
    //

    // p: 单位球上的一个点
    // u: [0,1], 方向从 (-x, z, x, -z, -x)
    // v: [0,1], 方向从 (-y, +y)
    // 例子
    //     < 1  0  0> => <0.50 0.50>
    //     <-1  0  0> => <0.00 0.50>
    //     < 0  1  0> => <0.50 1.00>
    //     < 0 -1  0> => <0.50 0.00>
    //     < 0  0  1> => <0.25 0.50>
    //     < 0  0 -1> => <0.75 0.50>
    static void get_sphere_uv(const point3& p, double& u, double& v);
};

#endif
#ifndef ZX_RECT_H
#define ZX_RECT_H

#include "hittable.h"

// xy 平面长方形
class zx_rect : public hittable {
   private:
    shared_ptr<material> mat_ptr;
    double z0, z1, x0, x1, k;  // y = k

   public:
    zx_rect();
    zx_rect(double _z0,
            double _z1,
            double _x0,
            double _x1,
            double _k,
            shared_ptr<material> mat);
    ~zx_rect();

    virtual bool hit(const ray& r,
                     double t_min,
                     double t_max,
                     hit_record& rec) const override;
    virtual bool bounding_box(double time0,
                              double time1,
                              aabb& output_box) const override;
};

#endif
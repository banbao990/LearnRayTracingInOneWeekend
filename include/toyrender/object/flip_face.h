#ifndef FLIP_FACE_H
#define FLIP_FACE_H

#include "hittable.h"

class flip_face : public hittable {
   public:
    flip_face(shared_ptr<hittable> p);
    virtual bool hit(const ray& r,
                     double t_min,
                     double t_max,
                     hit_record& rec) const override;
    virtual bool bounding_box(double time0,
                              double time1,
                              aabb& output_box) const override;

   public:
    shared_ptr<hittable> ptr;
};

#endif
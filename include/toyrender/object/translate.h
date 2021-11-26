#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "..//utils/h_help.h"
#include "hittable.h"

class translate : public hittable {
   private:
    shared_ptr<hittable> ptr;
    point3 offset;

   public:
    translate();
    translate(shared_ptr<hittable> _ptr, point3 _offset);
    ~translate();

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1,
                              aabb& output_box) const override;
};

#endif
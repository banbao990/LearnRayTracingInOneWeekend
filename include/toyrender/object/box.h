#ifndef BOX_H
#define BOX_H

#include "../common/vec3.h"
#include "..//utils/h_help.h"
#include "hittable.h"
#include "hittable_list.h"
#include "xy_rect.h"
#include "xz_rect.h"
#include "yz_rect.h"

class box : public hittable {
   private:
    point3 box_min, box_max;
    hittable_list sides;  // 面的集合

   public:
    box();
    box(const point3 p_min, const point3 p_max, shared_ptr<material> mtr);
    ~box();

    virtual bool hit(const ray& r,
                     double t_min,
                     double t_max,
                     hit_record& rec) const override;
    virtual bool bounding_box(double time0,
                              double time1,
                              aabb& output_box) const override;
};

#endif
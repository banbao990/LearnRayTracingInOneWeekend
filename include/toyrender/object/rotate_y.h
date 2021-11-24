#ifndef ROTATE_Y_H
#define ROTATE_Y_H

#include "../util/h_help.h"
#include "hittable.h"
#include "hittable_list.h"

// 绕着 y 轴逆时针旋转 angle 度(角度制)
// xOz 平面的逆时针
// 多次旋转会导致包围盒不紧致!!!
// TODO 如果既有 x 轴的旋转然后再复合 y 轴的旋转会出问题吗?(似乎没啥问题)
class rotate_y : public hittable {
   private:
    shared_ptr<hittable> ptr;
    double sin_theta, cos_theta;
    bool has_box;
    aabb bbox;

   public:
    rotate_y();
    // 逆时针旋转 angle 度(角度制)
    rotate_y(shared_ptr<hittable> _ptr, double angle);
    ~rotate_y();

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1,
                              aabb& output_box) const override;
};

#endif
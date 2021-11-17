#ifndef BOX_COMPARE_H
#define BOX_COMPARE_H

#include "aabb.h"
#include "hittable.h"

// 两个包围盒的比较器
bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b,
                 int axis);

// 按照 x 轴比较
bool box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b);
// 按照 y 轴比较
bool box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b);
// 按照 z 轴比较
bool box_z_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b);
#endif
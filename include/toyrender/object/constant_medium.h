#ifndef constant_medium_H
#define constant_medium_H

#include "../material/isotropic.h"
#include "../texture/texture.h"
#include "../utils/h_help.h"
#include "hittable.h"

// 参与介质, 内部散射是各向同性的
// 要求 boundary 必须是一个立体结构(不能是平面结构)
// 纹理最好还是使用 solid_color, 其他没有什么意义,
// 而且因为 hit 没有设置 uv, 可能会有 bug
class constant_medium : public hittable {
   private:
    shared_ptr<hittable> boundary;        // 散射介质的边界
    shared_ptr<material> phase_function;  // 就是 texture, 一般是 isotropic
    double neg_inv_density;  // -1/density, 负号因为随机数修正

   public:
    constant_medium();
    constant_medium(shared_ptr<hittable> _boundary, double density,
                    shared_ptr<texture> a);
    constant_medium(shared_ptr<hittable> _boundary, double density,
                    color _albedo);
    ~constant_medium();

    // 这部分是实现参与介质的重点(如何用表面模拟参与介质)
    // 要求 boundary 必须是一个立体结构(不能是平面结构)
    // TODO 只能处理凸几何体
    // 1. 求出光线和该物体的两个交点 (-infty, infty), (rec1.t, infty)
    // 2. 求出光线在物体内部的距离, 在这段距离中都有可能发生散射
    // 3. 概率散射
    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;

    // 返回包含的物体(boundary)的包围盒
    virtual bool bounding_box(double time0, double time1,
                              aabb& output_box) const override;
};

#endif
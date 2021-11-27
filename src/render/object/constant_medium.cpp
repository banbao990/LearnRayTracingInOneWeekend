#include <toyrender/object/constant_medium.h>
#include <toyrender/utils/rtweekend.h>

constant_medium::constant_medium() {}
constant_medium::constant_medium(shared_ptr<hittable> _boundary, double density,
                               shared_ptr<texture> a)
    : boundary(_boundary),
      neg_inv_density(-1 / density),
      phase_function(make_shared<isotropic>(a)) {}
constant_medium::constant_medium(shared_ptr<hittable> _boundary, double density,
                               color _albedo)
    : boundary(_boundary),
      neg_inv_density(-1 / density),
      phase_function(make_shared<isotropic>(_albedo)) {}
constant_medium::~constant_medium() {}

bool constant_medium::hit(const ray& r, double t_min, double t_max,
                         hit_record& rec) const {
    hit_record rec1, rec2;
    // 第一个交点
    if (!boundary->hit(r, -infinity, infinity, rec1)) {
        return false;
    }
    // 第二个交点
    if (!boundary->hit(r, rec1.t + eps, infinity, rec2)) {
        return false;
    }

    // 计算边界时间
    if (rec1.t < t_min) {
        rec1.t = t_min;
    }
    if (rec2.t > t_max) {
        rec2.t = t_max;
    }
    if (rec1.t >= rec2.t) {
        return false;
    }

    // 光源可能在参与介质内部
    if (rec1.t < 0) {
        rec1.t = 0;
    }

    // 计算出光线在参与介质中的长度(ray 没有归一化)
    const auto ray_length = r.get_direction().length();
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    // 概率
    const auto hit_distance = neg_inv_density * log(random_double(1e-8, 1));
    if (hit_distance > distance_inside_boundary) {
        return false;
    }

    rec.t = rec1.t + hit_distance / ray_length;
    rec.p = r.at(rec.t);

    // TODO rec.u/v 没有意义, 没有设置
    // TODO 感觉法向也没有用, 还在内部的化就不需要(因为现在只实现了 solid_color)
    // rec.normal = vec3(1, 0, 0);  // arbitrary
    // rec.front_face = true;       // also arbitrary
    rec.mat_ptr = phase_function;

    return true;
}

bool constant_medium::bounding_box(double time0, double time1,
                                  aabb& output_box) const {
    return boundary->bounding_box(time0, time1, output_box);
}

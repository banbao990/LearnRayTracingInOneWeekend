#include <toyrender/object/box.h>

box::box() {}
box::box(const point3 p_min, const point3 p_max, const shared_ptr<material> mtr)
    : box_min(p_min), box_max(p_max) {
    // 构建面的集合
    sides.add(make_shared<xy_rect>(p_min.x(), p_max.x(), p_min.y(), p_max.y(),
                                   p_min.z(), mtr));
    sides.add(make_shared<xy_rect>(p_min.x(), p_max.x(), p_min.y(), p_max.y(),
                                   p_max.z(), mtr));

    sides.add(make_shared<yz_rect>(p_min.y(), p_max.y(), p_min.z(), p_max.z(),
                                   p_min.x(), mtr));
    sides.add(make_shared<yz_rect>(p_min.y(), p_max.y(), p_min.z(), p_max.z(),
                                   p_max.x(), mtr));

    sides.add(make_shared<xz_rect>(p_min.x(), p_max.x(), p_min.z(), p_max.z(),
                                   p_min.y(), mtr));
    sides.add(make_shared<xz_rect>(p_min.x(), p_max.x(), p_min.z(), p_max.z(),
                                   p_max.y(), mtr));
}
box::~box() {}

bool box::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    return sides.hit(r, t_min, t_max, rec);
}

bool box::bounding_box(double time0, double time1, aabb& output_box) const {
    output_box = aabb(box_min, box_max);
    return true;
}
#include <toyrender/object/box_compare.h>

bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b,
                 int axis) {
    aabb box_a, box_b;
    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b)) {
        // TODO: ERROR
        std::cerr << "No Bounding Box in bvh_node constructor." << std::flush;
    }
    // 按照包围盒在这个轴上的最小值比较
    return box_a.get_min().e[axis] < box_b.get_min().e[axis];
}

bool box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
    return box_compare(a, b, 2);
}
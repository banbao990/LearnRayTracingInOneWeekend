#include <toyrender/object/box_compare.h>
#include <toyrender/object/bvh_node.h>

#include <algorithm>
#include <toyrender/utils/rtweekend.hpp>

bvh_node::bvh_node() {}

bvh_node::bvh_node(const hittable_list list, double time0, double time1)
    : bvh_node(list.get_objects(), 0, list.get_count(), time0, time1) {}

bvh_node::bvh_node(const std::vector<shared_ptr<hittable>> src_object,
                   size_t start,
                   size_t end,
                   double time0,
                   double time1) {
    // (1) naive 策略
    // 找到包围盒最大的轴方向
    // TODO 这里是随机选择一个方向
    // 按照这个轴的方向排序, 按照个数等分

    // 复制一份, 避免将原来的修改
    auto objects = src_object;
    int axis = random_int(0, 3);

    // 选择比较器, 是按照哪一个轴进行比较
    auto comparator = (axis == 0)
                          ? box_x_compare
                          : ((axis == 1) ? box_y_compare : box_z_compare);

    // object 个数
    size_t object_span = end - start;

    // 保证小的放置在左边
    if (object_span == 1) {
        // TODO 优化
        // 一个物体的话, 直接左右各放置一个复制品, 这样就不需要判断 null
        left = right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        } else {
            left = objects[start + 1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        size_t mid = start + object_span / 2;
        left = make_shared<bvh_node>(objects, start, mid, time0, time1);
        right = make_shared<bvh_node>(objects, mid, end, time0, time1);
    }

    aabb box_left, box_right;
    if (!left->bounding_box(0, 0, box_left) ||
        !right->bounding_box(0, 0, box_right)) {
        // TODO: ERROR
        std::cerr << "No Bounding Box in bvh_node constructor." << std::flush;
    }
    box = box_left + box_right;
}

bvh_node::~bvh_node() {}

bool bvh_node::hit(const ray& r,
                   double t_min,
                   double t_max,
                   hit_record& rec) const {
    // 没有击中包围盒, 则 miss
    if (!box.hit(r, t_min, t_max)) {
        return false;
    }

    // 判断是否击中左右子结点(两个子结点都需要遍历, 为了保证 rec 有效)
    // 感觉更好的一种设计方法是分为两个函数, 区分如下两种目的
    // (1) 只返回可见性的 occusion ray
    // (2) 需要返回交点的 radiance ray
    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);
    return hit_left || hit_right;
}

bool bvh_node::bounding_box(double time0,
                            double time1,
                            aabb& output_box) const {
    output_box = box;
    return true;
}

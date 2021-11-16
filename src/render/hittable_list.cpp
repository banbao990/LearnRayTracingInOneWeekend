#include <toyrender/object/hittable_list.h>

hittable_list::hittable_list() { objects.clear(); }
hittable_list::hittable_list(shared_ptr<hittable> obj) { add(obj); }
hittable_list::~hittable_list() {}

void hittable_list::clear() { objects.clear(); }
void hittable_list::add(shared_ptr<hittable> obj) { objects.push_back(obj); }

bool hittable_list::hit(const ray& r, double t_min, double t_max,
                        hit_record& rec) const {
    hit_record temp_rec;
    bool hit_annythig = false;
    double closest_so_far = t_max;

    // 这里的逻辑保证了找到的接触点是最近的
    for (const auto& obj : objects) {
        if (obj->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_annythig = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_annythig;
}
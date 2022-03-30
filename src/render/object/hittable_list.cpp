#include <toyrender/object/hittable_list.h>
#include <toyrender/utils/rtweekend.h>

hittable_list::hittable_list() { objects.clear(); }
hittable_list::hittable_list(shared_ptr<hittable> obj) { add(obj); }
hittable_list::~hittable_list() {}

void hittable_list::clear() { objects.clear(); }
void hittable_list::add(shared_ptr<hittable> obj) { objects.push_back(obj); }
std::vector<shared_ptr<hittable>> hittable_list::get_objects() const {
  return objects;
}
int hittable_list::get_count() const { return objects.size(); }

bool hittable_list::hit(const ray &r, double t_min, double t_max,
                        hit_record &rec) const {
  hit_record temp_rec;
  bool hit_anythig = false;
  double closest_so_far = t_max;

  // 这里的逻辑保证了找到的接触点是最近的
  for (const auto &obj : objects) {
    if (obj->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anythig = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anythig;
}

bool hittable_list::bounding_box(double time0, double time1,
                                 aabb &output_box) const {
  aabb temp_box;
  bool first_box = true;
  for (const auto &object : objects) {
    if (!object->bounding_box(time0, time1, temp_box)) {
      return false;
    }
    // 哪个速度快?
    // output_box = first_box ? temp_box : output_box + temp_box;
    // first_box = false;
    if (first_box) {
      output_box = temp_box;
      first_box = false;
    } else {
      output_box += temp_box;
    }
  }
  return true;
}

// PDF
vec3 hittable_list::random(const point3 &origin) const {
  int idx = random_int(0, objects.size());
  return objects[idx]->random(origin);
}

double hittable_list::pdf_value(const point3 &origin,
                                const vec3 &direction) const {
  double weight = 1.0 / objects.size();
  double sum = 0.0;
  for (const auto &o : objects) {
    sum += o->pdf_value(origin, direction);
  }
  return weight * sum;
}
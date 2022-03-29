#include <toyrender/object/flip_face.h>

flip_face::flip_face(shared_ptr<hittable> p) : ptr(p) {}
bool flip_face::hit(const ray& r,
                    double t_min,
                    double t_max,
                    hit_record& rec) const {
    if (!ptr->hit(r, t_min, t_max, rec)) {
        return false;
    }
    rec.front_face = !rec.front_face;
    return true;
}

bool flip_face::bounding_box(double time0,
                             double time1,
                             aabb& output_box) const {
    return ptr->bounding_box(time0, time1, output_box);
}


vec3 flip_face::random(const vec3& origin) const {
    return ptr->random(origin);
}

double flip_face::pdf_value(const point3& origin, const vec3& direction) const {
    return ptr->pdf_value(origin, direction);
}
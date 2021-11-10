#include <hit_record.hpp>

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = r.get_direction().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}
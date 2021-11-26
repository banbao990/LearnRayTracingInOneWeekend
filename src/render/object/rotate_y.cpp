#include <toyrender/object/rotate_y.h>

#include <toyrender/utils/rtweekend.h>

rotate_y::rotate_y() {}
rotate_y::rotate_y(shared_ptr<hittable> _ptr, double angle) : ptr(_ptr) {
    double theta = degrees_to_radians(angle);
    sin_theta = std::sin(theta);
    cos_theta = std::cos(theta);
    // TODO 直接默认 time 只会是 0-1
    std::cerr << "Rotate Bounding Box: Assume Time is 0~1!\n" << std::flush;
    has_box = ptr->bounding_box(0, 1, bbox);

    if (!has_box) {
        return;
    }

    point3 vmin(infinity, infinity, infinity);
    point3 vmax(-infinity, -infinity, -infinity);

    // 遍历八个顶点, 求出旋转后的包围盒
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                auto x = i * bbox.get_max().x() + (1 - i) * bbox.get_min().x();
                auto y = j * bbox.get_max().y() + (1 - j) * bbox.get_min().y();
                auto z = k * bbox.get_max().z() + (1 - k) * bbox.get_min().z();

                // 逆时针旋转 theta 角度之后得到的点
                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                // 更新最值
                vec3 tester(newx, y, newz);
                for (int c = 0; c < 3; c++) {
                    vmin[c] = std::fmin(vmin[c], tester[c]);
                    vmax[c] = std::fmax(vmax[c], tester[c]);
                }
            }
        }
    }
    bbox = aabb(vmin, vmax);
}

rotate_y::~rotate_y() {}

bool rotate_y::hit(const ray& r, double t_min, double t_max,
                   hit_record& rec) const {
    // 光线的起点和方向
    auto origin = r.get_origin();
    auto direction = r.get_direction();

    // 光线的起点旋转 -theta 度(相当于物体旋转 theta 度)
    origin[0] = cos_theta * r.get_origin()[0] - sin_theta * r.get_origin()[2];
    origin[2] = sin_theta * r.get_origin()[0] + cos_theta * r.get_origin()[2];

    // 光线的方向也需要旋转 -theta 度
    direction[0] =
        cos_theta * r.get_direction()[0] - sin_theta * r.get_direction()[2];
    direction[2] =
        sin_theta * r.get_direction()[0] + cos_theta * r.get_direction()[2];

    // 判断是否击中
    ray rotated_r(origin, direction, r.get_time());
    if (!ptr->hit(rotated_r, t_min, t_max, rec)) {
        return false;
    }

    // 修正位置和法线
    auto p = rec.p;
    auto normal = rec.normal;

    // 注意这里是旋转 theta 度(而不是 -theta), 和上面的操作是相反的
    // 物体是旋转 theta 度
    p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    // 旋转不改变模长(正交保范)
    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.normal = normal;
    rec.set_face_normal(rotated_r, normal);

    return true;
}

bool rotate_y::bounding_box(double time0, double time1,
                            aabb& output_box) const {
    output_box = bbox;
    return has_box;
}
#include <toyrender/object/xy_rect.h>
#include <toyrender/utils/h_help.h>

xy_rect::xy_rect() {}
xy_rect::xy_rect(double _x0, double _x1, double _y0, double _y1, double _k,
                 shared_ptr<material> mat)
    : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat_ptr(mat) {}
xy_rect::xy_rect::~xy_rect() {}

bool xy_rect::hit(const ray& r, double t_min, double t_max,
                  hit_record& rec) const {
    // 求出和 z=k 平面的交点
    // 可能是 inf
    // 0.0/0.0, nan(任意比较都返回 false)
    double t = (k - r.get_origin().z()) / r.get_direction().z();
    if (t < t_min || t > t_max) {
        return false;
    }

    double x = r.get_origin().x() + t * r.get_direction().x();
    double y = r.get_origin().y() + t * r.get_direction().y();

    // 边界上、边界外都不算相交
    if (x <= x0 || x >= x1 || y <= y0 || y >= y1) {
        return false;
    }

    // 击中, 保存 hit_record
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    vec3 outward_normal(0, 0, 1.0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.p = r.at(t);

    return true;
}

bool xy_rect::bounding_box(double time0, double time1, aabb& output_box) const {
    // 在 z 方向上增加一段小的包围
    output_box = aabb(point3(x0, y0, k - eps), point3(x1, y1, k + eps));
    return true;
}

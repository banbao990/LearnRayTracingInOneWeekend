#ifndef VEC3_H
#define VEC3_H

#include <iostream>

// 向量类
class vec3 {
   public:
    // 方便修改设置为 public
    double e[3];

   public:
    // 构造函数
    vec3();
    vec3(double e0, double e1, double e2);
    vec3(double e0);

    // 析构函数
    ~vec3();

    // 取元素
    double x() const;
    double y() const;
    double z() const;

    // 功能函数: 自身
    double length() const;
    double length_squared() const;

    vec3 operator-() const;
    double operator[](int i) const;  // const 修饰成员函数: 不会修改被对象的值
    double& operator[](int i);

    vec3& operator+=(const vec3& v);
    vec3& operator-=(const vec3& v);
    vec3& operator*=(const double t);
    vec3& operator/=(const double t);

    // 功能函数: 其他
    vec3 operator+(const vec3& v) const;
    vec3 operator-(const vec3& v) const;
    vec3 operator*(const vec3& v) const;

    double dot(const vec3& v) const;
    vec3 cross(const vec3& v) const;

    friend vec3 operator+(double t, const vec3& v);
    vec3 operator+(double t) const;
    vec3 operator-(double t) const;
    friend vec3 operator*(double t, const vec3& v);
    vec3 operator*(double t) const;
    vec3 operator/(double t) const;

    vec3 unit_vector() const;
    bool near_zero() const;

    friend std::ostream& operator<<(std::ostream& out, const vec3& v);

    //
    // static
    //

    // 返回一个随机向量, 0 <= x,y,z < 1
    static vec3 random();
    // 返回一个随机向量, min_v <= x,y,z < max_v
    static vec3 random(int min_v, int max_v);
    // 返回一个长度小于 1 的向量(顶点在球体内部均匀采样)
    static vec3 random_in_unit_sphere();
    // 返回一个长度为 1 的向量(顶点在球体表面均匀采样)
    static vec3 random_on_unit_sphere_surface();
    // 返回一个长度为 1 的向量(顶点在球体内部均匀采样, 然后归一化)
    // (等价于在表面均匀采样, 相当于无数层球壳, 体积压到表面)
    static vec3 random_in_unit_sphere_to_surface();
    // 返回一个长度为 1 的向量(顶点在法向半球内均匀采样)
    static vec3 random_in_unit_hemisphere(const vec3& normal);
    // 均匀圆盘采样
    // 返回平面 xOy 上, 原点为 (0,0,0), 半径为 1 的圆盘内部的均匀采样
    static vec3 random_in_unit_disk();
    // 余弦采样
    static vec3 random_cosine_direction();
    // 反射函数, 要求输入为两个单位向量, ray_in 指向交点, normal 从交点指向外面
    static vec3 reflect(const vec3& ray_in, const vec3& normal);
    // 折射函数, 要求输入为两个单位向量, ray_in 指向交点, normal 从交点指向外面
    // refraction_ratio = ray_in 所在平面折射率/ 折射光线所在平面折射率;
    static vec3 refract(const vec3& ray_in,
                        const vec3& normal,
                        double refraction_ratio);
};

// 声明别名
using point3 = vec3;  // 3D point

#endif
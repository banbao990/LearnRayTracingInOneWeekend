#ifndef PERLIN_H
#define PERLIN_H

#include "../common/vec3.h"

class perlin {
private:
  static const int POINT_COUNT = 256;
  vec3 *ranvec;
  int *perm_x, *perm_y, *perm_z;

public:
  perlin();
  ~perlin();

  // 根据给定的 3 维坐标返回噪声值(返回值可能有负数)
  double noise(const point3 &p) const;
  // 叠加不同频率的柏林噪声(返回值可能大于1)
  double turb(const point3 &p, int depth = 7) const;

private:
  // 生成随机排列表 [0, POINT_COUNT)
  static int *perlin_generate_perm(int n);
  // 对一个大小为 n 的数组 p 进行打乱
  static void permute(int *p, int n);
  // perlin 插值(可能返回负值)
  // c: 保存 8 个周围的整数点的值
  // u,v,w 表示3个轴 (x, y, z) 距离上一个整数点的距离
  static double perlin_interpolation(vec3 c[2][2][2], double u, double v,
                                     double w);
};

#endif
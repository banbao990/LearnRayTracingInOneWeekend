#include <toyrender/texture/perlin.h>

#include <toyrender/utils/rtweekend.h>

perlin::perlin() {
  // 生成一组 [0, 1) 随机向量
  ranvec = new vec3[POINT_COUNT];
  for (int i = 0; i < POINT_COUNT; ++i) {
    ranvec[i] = vec3::random(-1, 1).unit_vector();
  }
  // 生成随机排列表
  perm_x = perlin_generate_perm(POINT_COUNT);
  perm_y = perlin_generate_perm(POINT_COUNT);
  perm_z = perlin_generate_perm(POINT_COUNT);
}

perlin::~perlin() {
  delete[] ranvec;
  delete[] perm_x;
  delete[] perm_y;
  delete[] perm_z;
}

double perlin::noise(const point3 &p) const {
  int i = static_cast<int>(floor(p.x()));
  int j = static_cast<int>(floor(p.y()));
  int k = static_cast<int>(floor(p.z()));

  double u = p.x() - i;
  double v = p.y() - j;
  double w = p.z() - k;

  // 周围 8 个整数点返回的噪声值(随机向量)
  vec3 c[2][2][2];

  for (int di = 0; di < 2; ++di) {
    for (int dj = 0; dj < 2; ++dj) {
      for (int dk = 0; dk < 2; ++dk) {
        // & 操作保证下标不越界
        c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^
                               perm_z[(k + dk) & 255]];
      }
    }
  }

  // perlin 插值
  return perlin_interpolation(c, u, v, w);
}

double perlin::turb(const point3 &p, int depth) const {
  double ret = 0;
  point3 temp_p = p;
  // 起始为什么是 1.0 而不是 0.5 呢?
  // 那不是有可能大于 1 吗?
  // 经过测试 noise 返回值肯定小于 0.5!!!
  double weight = 1.0;
  for (int i = 0; i < depth; ++i) {
    ret += weight * noise(temp_p);
    weight *= 0.5;
    temp_p *= 2;
  }
  return fabs(ret);
}

//
// static
//

int *perlin::perlin_generate_perm(int n) {
  int *p = new int[n];
  for (int i = 0; i < n; ++i) {
    p[i] = i;
  }
  permute(p, n);
  return p;
}

void perlin::permute(int *p, int n) {
  for (int i = n - 1; i > 0; i--) {
    int target = random_int(0, i);
    std::swap(p[i], p[target]);
  }
}

double perlin::perlin_interpolation(vec3 c[2][2][2], double u, double v,
                                    double w) {
  // 修改插值函数
  // 原来 (1-t)x0 + tx1 = x0 + t(x1-x0)
  // 修改                 x0 + (3t^2-2t^3)(x1-x0)

  double uu = (3 - 2 * u) * u * u;
  double vv = (3 - 2 * v) * v * v;
  double ww = (3 - 2 * w) * w * w;

  double ret = 0;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        // 权重向量
        vec3 weight_v(u - i, v - j, w - k);
        // 每一个点的系数为 3 个数相乘
        // c[0][0][0]: (1-u)*(1-v)*(1-w)
        // c[1][1][1]: u*v*w
        ret += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) *
               (k * ww + (1 - k) * (1 - ww)) * (c[i][j][k].dot(weight_v));
      }
    }
  }

  return ret;
}
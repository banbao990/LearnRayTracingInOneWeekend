#include <toyrender/common/color.h>

#include <toyrender/utils/rtweekend.h>

void write_color(std::ostream &out, color pixel_color, int spp) {
  // 除以样本数
  double scale = 1.0 / spp;
  pixel_color *= scale;

  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // gamma 校正
  // y = x^{1/gamma}
  // gamma = 2
  r = sqrt(r);
  g = sqrt(g);
  b = sqrt(b);

  // 输出
  out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
  // << static_cast<int>(b * 255.999) << '\n';
}
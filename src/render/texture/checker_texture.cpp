#include <toyrender/texture/checker_texture.h>

#include <cmath>

checker_texture::checker_texture() : checker_texture(color(0), color(1.0)) {}
checker_texture::checker_texture(color _odd, color _even)
    : odd(make_shared<solid_color>(_odd)),
      even(make_shared<solid_color>(_even)) {}
checker_texture::checker_texture(shared_ptr<texture> _odd,
                                 shared_ptr<texture> _even)
    : odd(_odd), even(_even) {}
checker_texture::~checker_texture() {}

color checker_texture::value(double u, double v, const point3 &p) const {
  double sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
  if (sines < 0) {
    return odd->value(u, v, p);
  } else {
    return even->value(u, v, p);
  }
}

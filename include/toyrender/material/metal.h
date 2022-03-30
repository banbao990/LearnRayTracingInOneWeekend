#ifndef METAL_H
#define METAL_H

#include "../common/color.h"
#include "material.h"

// 金属材质(纯镜面, 磨砂)
class metal : public material {
private:
  color albedo;
  double fuzz; // 粗糙程度, 值越大越粗糙

public:
  metal();
  metal(color _albedo, double _fuzz = 0);
  ~metal();

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       color &attenuation, ray &scattered) const override;

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       scatter_record &srec) const override;
};

#endif
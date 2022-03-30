#ifndef SCATTER_RECORD_H
#define SCATTER_RECORD_H

#include "../common/color.h"
#include "../common/ray.h"
#include "../pdf/pdf.h"
#include "../utils/h_help.h"

struct scatter_record {
  ray specular_ray;
  bool is_specular;
  shared_ptr<pdf> pdf_ptr;
  color attenuation;
};

#endif
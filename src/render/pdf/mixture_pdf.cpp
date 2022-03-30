#include <toyrender/pdf/mixture_pdf.h>
#include <toyrender/utils/rtweekend.h>

mixture_pdf::mixture_pdf(shared_ptr<pdf> p1, shared_ptr<pdf> p2) {
  p[0] = p1;
  p[1] = p2;
}

mixture_pdf::~mixture_pdf() {}

vec3 mixture_pdf::generate() const {
  if (random_double() < 0.5) {
    return p[0]->generate();
  } else {
    return p[1]->generate();
  }
}

double mixture_pdf::value(const vec3 &direction) const {
  return 0.5 * (p[0]->value(direction) + p[1]->value(direction));
  // double a = p[0]->value(direction) ;
  // double b = p[1]->value(direction) ;
  // return 0.5*(a+b);
}

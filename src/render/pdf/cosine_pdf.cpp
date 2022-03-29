#include <toyrender/utils/rtweekend.h>
#include <toyrender/pdf/cosine_pdf.h>

cosine_pdf::cosine_pdf(const vec3& w) {
    uvw.build_from_w(w);
}

cosine_pdf::~cosine_pdf() {}

vec3 cosine_pdf::generate() const {
    return uvw.local(vec3::random_cosine_direction());
}

double cosine_pdf::value(const vec3& direction) const {
    double cosine = direction.unit_vector().dot(uvw.w());
    return (cosine <= 0) ? 0 : cosine / pi;
}

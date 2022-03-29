#ifndef COSINE_PDF_H
#define COSINE_PDF_H

#include "../common/onb.h"
#include "pdf.h"

class cosine_pdf : public pdf {
   public:
    cosine_pdf(const vec3& w);
    ~cosine_pdf();
    virtual vec3 generate() const override;
    virtual double value(const vec3& direction) const override;

   public:
    onb uvw;
};

#endif
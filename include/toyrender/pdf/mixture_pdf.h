#ifndef MIXTURE_PDF_H
#define MIXTURE_PDF_H

#include "../utils/h_help.h"
#include "pdf.h"

class mixture_pdf : public pdf {
   public:
    mixture_pdf(shared_ptr<pdf> p1, shared_ptr<pdf> p2);
    ~mixture_pdf();
    virtual vec3 generate() const override;
    virtual double value(const vec3& direction) const override;

   public:
    shared_ptr<pdf> p[2];
};

#endif
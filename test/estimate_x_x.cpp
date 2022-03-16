#include <cmath>
#include "toyrender/common/vec3.h"
#include "toyrender/utils/rtweekend.h"

void estimate_x_x();
void estimate_x_x_pdf();
void estimate_cos_sphere();

int main() {
    // estimate_x_x();
    // estimate_x_x_pdf();
    estimate_cos_sphere();
    return 0;
}

// I = \int_{\Omega}\cos^2\theta
void estimate_cos_sphere() {
    const int N = 20000000;
    double ans = 0.0, ans1 = 0.0;
    long long num = 0;
    double const pi4 = pi * 4;
    double const pi22 = 2 * pi * pi;
    double const result = pi4 / 3;
    while (true) {
        ++num;
        // p(x) = 0.5, 0<=x<=2
        vec3 x = vec3::random_on_unit_sphere_surface();
        // p(X) = 1/(4*pi)
        ans += x.z() * x.z() * pi4;

        double theta = random_double(0, pi);
        double phi = random_double(0, pi2);
        double t = cos(theta);
        // p(X) = 1/(2*pi*pi)
        ans1 += t * t * sin(theta) * pi22;
        if (num % N == 0) {
            printf(
                "standard                :   %.10lf\n"
                "dS uniform              :   %.10lf\n"
                "d(theta), d(phi) uniform:   %.10lf\n",
                result, ans / num, ans1 / num);
        }
    }
}

// I=\int_{0}^{2}x^2\mathrm{d}x
void estimate_x_x() {
    double ans = 0.0;
    long long num = 0;
    while (true) {
        ++num;
        double x = random_double(0, 2);
        ans += x * x;
        if (num % 100000 == 0) {
            printf("%.10lf\r", 2 * ans / num);
        }
        if (num % 100000000 == 0) {
            printf("\n");
        }
    }
}

// I=\int_{0}^{2}x^2\mathrm{d}x
void estimate_x_x_pdf() {
    const int N = 20000000;
    double ans = 0.0, ans_pdf = 0.0, ans_pdf2 = 0.0;
    long long num = 0;
    const float et = 8.0F / 3.0F;
    const float ot = 1.0F / 3.0F;
    while (true) {
        ++num;
        // p(x) = 0.5, 0<=x<=2
        double x = random_double(0, 2);
        ans += 2 * x * x;

        x = 2 * sqrt(random_double(0, 1));
        // p(x) = x/2, 0<=x<=2
        // x*x/p(x) = x*x*2/x = x*2
        ans_pdf += x * 2;

        x = 2 * pow(random_double(0, 1), ot);
        // p(x) = 3x*x/8, 0<=x<=2
        // x*x/p(x) = x*x*8/(3*x*x) = 8/3
        ans_pdf2 += et;
        if (num % N == 0) {
            printf(
                "uniform:   %.10lf\n"
                "pdf=x/2:   %.10lf\n"
                "pdf=x^3/8: %.10lf\n\n",
                ans / num, ans_pdf / num, ans_pdf2 / num);
        }
    }
}
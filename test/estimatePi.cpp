#include <limits.h>

#include "toyrender/utils/rtweekend.h"

void estimate_pi();
void estimate_pi_jitter();

int main() {
    // estimate_pi();
    estimate_pi_jitter();
    return 0;
}

void estimate_pi_jitter() {
    int circle = 0;
    int circle_j = 0;
    const int sqrt_N = 10000;
    const int S = 1;
    const double N = 1.0 * sqrt_N * sqrt_N * S;
    for (int s = 0; s < S; ++s) {
        for (int i = 0; i < sqrt_N; ++i) {
            for (int j = 0; j < sqrt_N; ++j) {
                // 常规的 MC
                double x = random_double(-1, 1);
                double y = random_double(-1, 1);
                if (x * x + y * y < 1) {
                    ++circle;
                }

                // 分层 MC
                // 分成了 sqrt_N * sqrt_N 个
                x = 2 * ((i + random_double()) / sqrt_N) - 1;
                y = 2 * ((j + random_double()) / sqrt_N) - 1;
                if (x * x + y * y < 1) {
                    ++circle_j;
                }
            }
        }
    }
    printf(
        "Samples: %g\n"
        "Regular    Estimate of PI: %.10lf\n"
        "Stratified Estimate of PI: %.10lf\n",
        N, 4.0 * circle / N, 4.0 * circle_j / N);
}

void estimate_pi() {
    long long num = 0LL;
    long long circle = 0LL;
    while (true) {
        ++num;
        double x = random_double(-1, 1);
        double y = random_double(-1, 1);
        if (x * x + y * y < 1) {
            ++circle;
        }
        if (num % 100000 == 0) {
            printf("%.10lf\r", 4.0 * circle / num);
        }
    }
}
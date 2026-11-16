#ifndef DW4_NEWLIB_MATH_H
#define DW4_NEWLIB_MATH_H

/* newlib's fdlibm internals: the __ieee754_* cores the w_* wrappers call, the __kernel_* polynomial
 * kernels on [-pi/4, pi/4] and the argument reductions by pi/2. The f forms are the float versions. */

double __ieee754_acos(double x);
double __ieee754_asin(double x);
double __ieee754_atan2(double y, double x);
double __ieee754_exp(double x);
double __ieee754_fmod(double x, double y);
double __ieee754_log(double x);
double __ieee754_log10(double x);
double __ieee754_pow(double x, double y);
double __ieee754_sqrt(double x);
int __ieee754_rem_pio2(double x, double *y);

float __ieee754_acosf(float x);
float __ieee754_asinf(float x);
float __ieee754_atan2f(float y, float x);
float __ieee754_fmodf(float x, float y);
float __ieee754_logf(float x);
float __ieee754_log10f(float x);
float __ieee754_sqrtf(float x);
int __ieee754_rem_pio2f(float x, float *y);

double __kernel_sin(double x, double y, int iy);
double __kernel_cos(double x, double y);
double __kernel_tan(double x, double y, int iy);
int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec, const int *ipio2);
float __kernel_sinf(float x, float y, int iy);
float __kernel_cosf(float x, float y);
float __kernel_tanf(float x, float y, int iy);
int __kernel_rem_pio2f(float *x, float *y, int e0, int nx, int prec, const int *ipio2);

#endif

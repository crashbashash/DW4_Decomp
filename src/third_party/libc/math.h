#ifndef DW4_LIBC_MATH_H
#define DW4_LIBC_MATH_H
#ifdef __cplusplus
extern "C" {
#endif
double fabs(double);
double sin(double);
double cos(double);
double tan(double);
double asin(double);
double acos(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double floor(double);
double fmod(double, double);
double sqrt(double);
double pow(double, double);
double log(double);
double log10(double);
double exp(double);
double frexp(double, int *);
double ldexp(double, int);
float sinf(float);
float cosf(float);
float tanf(float);
float asinf(float);
float atanf(float);
float atan2f(float, float);
float sqrtf(float);
#ifdef __cplusplus
}
#endif
#endif

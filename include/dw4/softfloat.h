#ifndef DW4_SOFTFLOAT_H
#define DW4_SOFTFLOAT_H

/* libgcc's software floating-point and 64-bit integer routines, for the callers that name them.
 * fptodp is called by name where retail calls it directly (a `(double)` cast compiles to a different
 * sequence). */
#ifdef __cplusplus
extern "C" {
#endif

double fptodp(float value);
float dptofp(double value);
double dpadd(double a, double b);
double dpsub(double a, double b);
double dpmul(double a, double b);
double dpdiv(double a, double b);
int dpcmp(double a, double b);
double litodp(int value);

/* The 64-bit routines; `long` is redefined by the Lua units, which call none of them. */
#ifndef long
long long __divdi3(long long u, long long v);
long long __moddi3(long long u, long long v);
unsigned long long __udivdi3(unsigned long long n, unsigned long long d);
unsigned long long __umoddi3(unsigned long long u, unsigned long long v);
double __floatdidf(long long u);
float __floatdisf(long long u);
long long __fixdfdi(double a);
long long __fixsfdi(float a);
unsigned long long __fixunsdfdi(double a);
unsigned long long __fixunssfdi(float a);
#endif

#ifdef __cplusplus
}
#endif

#endif

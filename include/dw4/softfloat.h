#ifndef DW4_SOFTFLOAT_H
#define DW4_SOFTFLOAT_H

/* libgcc's software float-to-double conversion, called by name where retail calls it directly (a
 * `(double)` cast compiles to a different sequence). */
#ifdef __cplusplus
extern "C" {
#endif

double fptodp(float value);

#ifdef __cplusplus
}
#endif

#endif

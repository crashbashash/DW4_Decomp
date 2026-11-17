#ifndef DW4_IGRAY_H
#define DW4_IGRAY_H

struct igRay;

#ifdef __cplusplus
extern "C" {
#endif
void igRay_EnsureRegistered(void);
struct igRay *igRay_CreateInstance(int allocator);
void igRay_Transform(struct igRay *ray, const float *matrix);
/* The ray from `from` towards `to`: unit direction, length the distance. */
void igRay_SetFromPoints(struct igRay *ray, const float *from, const float *to);
#ifdef __cplusplus
}
#endif

#endif

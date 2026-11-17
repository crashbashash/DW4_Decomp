#ifndef DW4_IGRAY_H
#define DW4_IGRAY_H

struct igRay;

#ifdef __cplusplus
extern "C" {
#endif
void igRay_EnsureRegistered(void);
void igRay_Transform(struct igRay *ray, const void *matrix);
#ifdef __cplusplus
}
#endif

#endif

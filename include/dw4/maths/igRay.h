#ifndef DW4_IGRAY_H
#define DW4_IGRAY_H

struct igRay;

#ifdef __cplusplus
/* The kit's igRay::ISET_SIDES (alchemy-kit_202309 igMath/igRay.h): which faces a ray test counts. DW4's igRay is
 * still the flat struct, which cannot nest it, so it is declared beside it. */
enum ISET_SIDES { FRONT_SIDE, BACK_SIDE, BOTH_SIDES };
#endif

#ifdef __cplusplus
extern "C" {
#endif
void igRay_EnsureRegistered(void);
struct igRay *igRay_CreateInstance(int allocator);
void igRay_Transform(struct igRay *ray, const float *matrix);
/* The ray from `from` towards `to`: unit direction, length the distance. */
void igRay_SetFromPoints(struct igRay *ray, const float *from, const float *to);
struct igMetaObject *igRay_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

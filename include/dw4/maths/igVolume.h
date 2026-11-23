#ifdef __cplusplus
/* reflected.h comes first, outside the guard: it reads this header itself, right after igObject's class. */
#include "dw4/support/reflected.h"
#endif
#ifndef DW4_IGVOLUME_H
#define DW4_IGVOLUME_H


#ifdef __cplusplus
/* igVolume (alchemy-kit_202309 igMath/igVolume.h): abstract and without fields, so retail's registration records
 * only the object header. igMath is not converted; this flat view is what igNode's `_bound` points at. */
struct igVolume : public igObject {
};
#endif

#ifdef __cplusplus
extern "C" {
#endif
void igVolume_ExtendBy(void **volume, void **other);
void igVolume_EnsureRegistered(void);
struct igMetaObject *igVolume_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

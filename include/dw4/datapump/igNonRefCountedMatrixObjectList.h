#ifndef DW4_IGNONREFCOUNTEDMATRIXOBJECTLIST_H
#define DW4_IGNONREFCOUNTEDMATRIXOBJECTLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igNonRefCountedMatrixObjectList_EnsureRegistered(void);
struct igMetaObject *igNonRefCountedMatrixObjectList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

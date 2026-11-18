#ifndef DW4_IGMATRIXOBJECTLIST_H
#define DW4_IGMATRIXOBJECTLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igMatrixObjectList_EnsureRegistered(void);
struct igMetaObject *igMatrixObjectList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGMODELVIEWMATRIXATTRLIST_H
#define DW4_IGMODELVIEWMATRIXATTRLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igModelViewMatrixAttrList_EnsureRegistered(void);
struct igMetaObject *igModelViewMatrixAttrList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

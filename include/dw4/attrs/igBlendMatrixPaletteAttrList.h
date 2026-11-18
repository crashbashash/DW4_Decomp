#ifndef DW4_IGBLENDMATRIXPALETTEATTRLIST_H
#define DW4_IGBLENDMATRIXPALETTEATTRLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igBlendMatrixPaletteAttrList_EnsureRegistered(void);
struct igMetaObject *igBlendMatrixPaletteAttrList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

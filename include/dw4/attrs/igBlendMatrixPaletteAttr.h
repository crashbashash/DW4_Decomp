#ifndef DW4_IGBLENDMATRIXPALETTEATTR_H
#define DW4_IGBLENDMATRIXPALETTEATTR_H

struct igMetaObject;
struct igBlendMatrixPaletteAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igBlendMatrixPaletteAttr_metaObject;
struct igBlendMatrixPaletteAttr *igBlendMatrixPaletteAttr_Create(struct igMemoryPoolView *pool);

void igBlendMatrixPaletteAttr_EnsureRegistered(void);
struct igMetaObject *igBlendMatrixPaletteAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

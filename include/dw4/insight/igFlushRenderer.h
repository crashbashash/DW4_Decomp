#ifndef DW4_IGFLUSHRENDERER_H
#define DW4_IGFLUSHRENDERER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igFlushRenderer_EnsureRegistered(void);
struct igMetaObject *igFlushRenderer_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

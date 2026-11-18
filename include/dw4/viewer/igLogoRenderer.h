#ifndef DW4_IGLOGORENDERER_H
#define DW4_IGLOGORENDERER_H

struct igMetaObject;

struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif
struct igObject *igLogoRenderer_Create(struct igMemoryPoolView *pool);

extern struct igMetaObject *g_igLogoRenderer_metaObject;

#ifdef __cplusplus
}
#endif

#endif

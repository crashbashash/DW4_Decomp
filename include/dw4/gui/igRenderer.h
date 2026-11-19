#ifndef DW4_IGRENDERER_H
#define DW4_IGRENDERER_H

struct igMetaObject;
struct CallbackArray;
struct igRenderer;
struct igVisualContext;

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igRenderer_vtable[4];

struct igRenderer *igRenderer_Destroy(struct igRenderer *self, short deleteFlag);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGRENDERER_H
#define DW4_IGRENDERER_H

struct igMetaObject;
struct CallbackArray;
struct igRenderer;
struct igVisualContext;

#ifdef __cplusplus
#include "dw4/gui/igRendererDispatchView.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igRenderer_vtable[4];

extern struct igMetaObject *g_igRenderer_metaObject;
struct CallbackArray *igRenderer_Register(void);
struct igMetaObject *igRenderer_GetPublishedMetaObject(void);
struct igRenderer *igRenderer_Destroy(struct igRenderer *self, short deleteFlag);
#ifdef __cplusplus
void igRenderer_SetVisualContext(igRendererDispatchView *renderer, struct igVisualContext *context);
#endif

#ifdef __cplusplus
}
#endif

#endif

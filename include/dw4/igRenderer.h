#ifndef DW4_IGRENDERER_H
#define DW4_IGRENDERER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igRenderer_vtable[4];

extern struct igMetaObject *g_igRenderer_metaObject;
struct CallbackArray *igRenderer_Register(void);

#ifdef __cplusplus
}
#endif

#endif

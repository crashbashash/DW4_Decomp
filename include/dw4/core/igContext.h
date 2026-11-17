#ifndef DW4_IGCONTEXT_H
#define DW4_IGCONTEXT_H

/* igContext: class registration. */
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igContext_metaObject;

struct igMetaObject *igContext_GetPublishedMetaObject(void);
struct CallbackArray *igContext_Register(void);

#ifdef __cplusplus
}
#endif

#endif

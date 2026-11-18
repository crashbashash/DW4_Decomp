#ifndef DW4_IGCONTEXTEXT_H
#define DW4_IGCONTEXTEXT_H

/* igContextExt: the context-extension class's metaobject. */
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igContextExt_metaObject;
struct CallbackArray *igContextExt_Register(void);
void igContextExt_MakeCurrent(void);
int igContextExt_IsCurrent(void);
#ifdef __cplusplus
}
#endif

#endif

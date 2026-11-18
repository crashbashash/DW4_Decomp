#ifndef DW4_IGATTR_H
#define DW4_IGATTR_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igAttr_metaObject;
struct igMetaObject *igAttr_GetMetaObject(void);

struct igMetaObject *igAttr_GetOrCreateMetaObject(void);
void igAttr_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif

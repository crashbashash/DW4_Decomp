#ifndef DW4_IGLIGHTATTR_H
#define DW4_IGLIGHTATTR_H

struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaField *g_igLightAttr_directionMetaField;
extern struct igMetaObject *g_igLightAttr_metaObject;

struct igMetaObject *igLightAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

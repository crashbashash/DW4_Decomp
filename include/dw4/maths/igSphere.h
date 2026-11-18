#ifndef DW4_IGSPHERE_H
#define DW4_IGSPHERE_H

/* igSphere: the bounding-sphere class's metaobject. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igSphere_metaObject;
void igSphere_EnsureRegistered(void);
struct igMetaObject *igSphere_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

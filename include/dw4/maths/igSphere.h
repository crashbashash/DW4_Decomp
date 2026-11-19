#ifndef DW4_IGSPHERE_H
#define DW4_IGSPHERE_H

/* igSphere: the bounding-sphere class's metaobject. */
struct igMetaObject;
struct igSphere;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igSphere_metaObject;
void igSphere_EnsureRegistered(void);
struct igMetaObject *igSphere_GetOrCreateMetaObject(void);
/* Grows `sphere` to enclose `other`. */
void FUN_0018de10(struct igSphere *sphere, const struct igSphere *other);

#ifdef __cplusplus
}
#endif

#endif

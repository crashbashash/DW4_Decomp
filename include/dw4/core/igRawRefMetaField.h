#ifndef DW4_IGRAWREFMETAFIELD_H
#define DW4_IGRAWREFMETAFIELD_H

/* igRawRefMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igRawRefMetaField_metaObject;
struct igMetaField *igRawRefMetaField_Create(struct igMemoryPoolView *pool);
void igRawRefMetaField_EnsureRegistered(void);
struct igMetaObject *igRawRefMetaField_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

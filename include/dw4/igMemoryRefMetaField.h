#ifndef DW4_IGMEMORYREFMETAFIELD_H
#define DW4_IGMEMORYREFMETAFIELD_H

/* igMemoryRefMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMemoryRefMetaField;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMemoryRefMetaField_metaObject;
struct igMetaField *igMemoryRefMetaField_Create(struct igMemoryPoolView *pool);
void igMemoryRefMetaField_SetDefaultWord(struct igMetaField *self, int value);
void igMemoryRefMetaField_SetAlignmentType(struct igMemoryRefMetaField *self, const char *name);
void igMemoryRefMetaField_SetPoolName(struct igMemoryRefMetaField *self, const char *name);
int igMemoryRefMetaField_GetDefaultDescriptor(void);

#ifdef __cplusplus
}
#endif

#endif

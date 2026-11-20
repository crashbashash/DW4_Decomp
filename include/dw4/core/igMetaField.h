#ifndef DW4_IGMETAFIELD_H
#define DW4_IGMETAFIELD_H

/* igMetaField, the base of every metafield type: initialising and naming a field, and the registered descriptor list. */
struct igMemoryPoolView;
struct igMemoryRefMetaField;
struct igMetaField;
struct igMetaObject;
struct __internalObjectList;
struct CallbackArray;
struct igMetaFieldView;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igMetaField_GetPublishedMetaObject(void);
struct igMetaField *igMetaField_Init(struct igMetaField *field);
void igMetaField_Destruct(struct igMetaField *self);
extern int g_igMetaField_vtable[4];
void igMetaField_AllocateArray(int *outStatus, struct igMemoryRefMetaField *field, void *object, int count, struct igMemoryPoolView *allocator);

#ifdef __cplusplus
}
#endif

#endif

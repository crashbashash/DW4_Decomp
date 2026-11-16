#ifndef DW4_IGMETAFIELD_H
#define DW4_IGMETAFIELD_H

/* igMetaField, the base of every metafield type: initialising and naming a field, and the registered descriptor list. */
struct igMetaField;
struct igMetaObject;
struct __internalObjectList;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMetaField_metaObject;

struct CallbackArray *igMetaField_Register(void);
struct igMetaObject *igMetaField_GetPublishedMetaObject(void);
void igMetaField_EnsureRegistered(void);
struct igMetaField *igMetaField_Init(struct igMetaField *field);
void igMetaField_SetFieldName(struct igMetaField *self, void **newName);
void igMetaField_FinalizeDescriptor(struct igMetaField *field);
struct __internalObjectList *igMetaField_GetMetaFieldList(void);
extern int g_igMetaField_vtable[4];

#ifdef __cplusplus
}
#endif

#endif

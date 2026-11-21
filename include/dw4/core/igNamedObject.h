#ifndef DW4_IGNAMEDOBJECT_H
#define DW4_IGNAMEDOBJECT_H

/* igNamedObject: an igObject with a name. Gap::Core::igNamedObject::k_name is its `_name` field, the key the property lookups search on. */
struct igNamedObject;
struct igMetaObject;
struct igMetaField;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

extern int g_igNamedObject_vtable[4];

struct igMetaObject *igNamedObject_GetPublishedMetaObject(void);
struct igNamedObject *igNamedObject_Destroy(struct igNamedObject *self, short deleteFlag);

#ifdef __cplusplus
}
#endif

#endif

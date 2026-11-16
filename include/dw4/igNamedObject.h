#ifndef DW4_IGNAMEDOBJECT_H
#define DW4_IGNAMEDOBJECT_H

/* igNamedObject: an igObject with a name. g_propertyNameField is its `_name` field, the key the property lookups search on. */
struct igNamedObject;
struct igMetaObject;
struct igMetaField;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igNamedObject_metaObject;
extern struct igMetaField *g_propertyNameField;
extern int g_igNamedObject_vtable[4];

struct CallbackArray *igNamedObject_Register(void);
void igNamedObject_EnsureRegistered(void);
void igNamedObject_SetName(struct igNamedObject *self, const char *name);
struct igMetaObject *igNamedObject_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

#ifndef DW4_IGMETAOBJECT_H
#define DW4_IGMETAOBJECT_H

/* Class registration and the metaobject services.
 *
 * Each class X has an X_Register function that calls igMetaObject_RegisterClass and returns the
 * callback array it builds; igMetaObject_RunStaticInit calls a Register function, runs the callbacks
 * in that array and frees it. RegisterClass is handed the parent class's Register function, which
 * it calls first, and the parent's published-metaobject accessor. */
struct igMetaObject;
struct igMetaField;
struct igObject;
class igMemoryPoolView;
template <class T> struct igSmartPointer;

/* The growable callback array of the class-registration protocol (data pointer, count, capacity).
 * The growth rule is retail's, not a conventional 1.5x: the first capacity is 4 and every later
 * growth multiplies the capacity by (capacity * 3) / 2, so ordinary capacities advance 4 -> 24 ->
 * 864. Do not "fix" it. */
struct CallbackArray {
    int *data;
    int count;
    int capacity;
};

typedef CallbackArray *(*igMetaObjectRegisterFunction)(void);
typedef igMetaObject *(*igMetaObjectGetFunction)(void);
typedef int (*igMetaObjectGetVTableFunction)(void);
typedef void (*igMetaObjectCallback)(void);
/* A metafield type's Create function, given the metadata pool. */
typedef igMetaField *(*FieldFactory)(igMemoryPoolView *pool);

extern "C" {
CallbackArray *igMetaObject_RegisterClass(bool abstract, igMetaObject **metaObject,
    igMetaObjectRegisterFunction registerParent, igMetaObjectGetFunction getParentMetaObject,
    igMetaObjectCallback getMetaObjectFunction, const char *className, int instanceSize,
    igMetaObjectGetVTableFunction getVTable, igMetaObjectCallback initFields,
    igMetaObjectCallback staticInitCallback, igMetaObjectCallback *callbacks);
void igMetaObject_RunStaticInit(igMetaObjectRegisterFunction registerClass);

igMetaObject *igMetaObject_Create(igMemoryPoolView *pool);
igObject *igMetaObject_CreateInstance(igMetaObject *self, igMemoryPoolView *pool);
igObject *igMetaObject_CreateInstanceDefault(igMetaObject *meta);
/* A new instance held by the returned pointer, from the default pool or from `pool`. */
igSmartPointer<igObject> igMetaObject_CreateInstanceDefaultRef(igMetaObject *meta);
igSmartPointer<igObject> igMetaObject_CreateInstanceRef(igMetaObject *meta, igMemoryPoolView *pool);
void igMetaObject_CreateFields(igMetaObject *meta, FieldFactory *factories, int count);
void igMetaObject_NameFields(igMetaObject *meta, const char **names, igMetaField ***handles,
    int *offsets, int start);
igMetaField *igMetaObject_GetFieldAt(igMetaObject *self, int index);
int igMetaObject_GetFieldCount(igMetaObject *self);
igMetaField *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name);
void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta, int index, igMetaField *field);
int igMetaObject_CountInstances(igMetaObject *self, int recursive);
int igMetaObject_IsOfType(igMetaObject *self, igMetaObject *type);
igMetaObject *igMetaObject_GetOrCreateMetaObject(void);
void igMetaObject_EnsureRegistered(void);
void *igMetaObject_GetTreeNode(igMetaObject *self, int index);
int igMetaObject_CountTree(igMetaObject *self);
void igMetaObject_AddExitCallback(int callback);
void igMetaObject_AddRegistrationCallback(int callback);
int igObjectSystem_FindMetaByNameDefault(const char *name);
extern struct igMetaObject *g_igMetaObject_metaObject;
void igMetaObject_AddFieldAndFinalize(struct igMetaObject *self, void *field);
}

#endif

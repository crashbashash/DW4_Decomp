#ifndef DW4_IGOBJECT_H
#define DW4_IGOBJECT_H

/* igObject services. igObject_InitHeader is Gap::Core::igObject's constructor under its retail name: it writes
 * an object's igObject header (vtable and a reference count of 1), and a class still written as a flat struct
 * calls it by that name for the stack probe its GetVTable runs. The slot defaults declared here by their retail
 * names are Gap::Core::igObject's virtual functions, called directly (never through the vtable) by the
 * overrides of classes not yet converted. The storage calls allocate from and free to the pool the object came
 * from. */
struct igObjectDispatchView;
struct igObject;
struct igMetaObject;
struct igMemoryPoolView;
struct CallbackArray;
/* igObject::traverseFields' callback: (object, field or 0 for the object itself, context); a 1 for the object
 * ends the walk, a 1 for a field skips that field's elements. */
typedef int (*Visitor)(void *, void *, void *);

#ifdef __cplusplus
extern "C" {
#endif

struct igObject *igObject_InitHeader(struct igObject *p);
void igObject_Destroy(struct igObject *object);
/* Class-membership test: 1 when `kind` is the object's own class or one of its ancestors, else 0. */
int igObject_IsKindOf(struct igObject *object, struct igMetaObject *kind);
/* The published-metaobject accessor class registrations pass for an igObject parent. */
struct igMetaObject *igObject_GetMetaObject_ParentAccessor(void);

/* igObject's virtual-slot defaults, which derived classes' vtables share. */
void Gap__Core__igObject__constructFields(struct igObject *self, int flags);
void Gap__Core__igObject__destructFields(struct igObject *self);
void Gap__Core__igObject__userConstruct(struct igObject *self);
void Gap__Core__igObject__userDestruct(struct igObject *self);
void Gap__Core__igObject__resetFields(struct igObject *self, int flags);
void igObject_InitDefaults(struct igObject *self);
void igObject_ReleaseDefaults(struct igObject *self);
void igObject_UserPostLoad(void);

int Memory_FreeBufferAliasC(void *block);

int igObject_GetFieldValueByName(void **self, int name);
void igObject_ResetFields(struct igObjectDispatchView *object);

#ifdef __cplusplus
}
#endif

#endif

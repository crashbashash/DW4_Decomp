#ifndef DW4_IGOBJECT_H
#define DW4_IGOBJECT_H

/* igObject services. igObject_InitHeader writes a stack object's igObject header (vtable and a
 * reference count of 1), the probe every class's GetVTable runs. The storage calls allocate from
 * and free to the pool the object came from. */
struct igObject;
struct igMetaObject;
struct igMemoryPoolView;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

struct igObject *igObject_InitHeader(struct igObject *p);
void igObject_Destroy(struct igObject *object);
/* Class-membership test: 1 when `kind` is the object's own class or one of its ancestors, else 0. */
int igObject_IsKindOf(struct igObject *object, struct igMetaObject *kind);
struct CallbackArray *igObject_Register(void);
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

struct igMemoryPoolView *igObject_GetAllocator(struct igObject *object);
void *igObject_AllocateStorage(struct igObject *object, int size);
void *igObject_Callocate(struct igObject *object, int count, int size);
void *igObject_Reallocate(struct igObject *object, void *storage, int size);
void *igObject_ReallocateAligned(struct igObject *object, void *storage, int size, unsigned short alignment);
void *igObject_MallocAligned(struct igObject *object, int size, unsigned short alignment);
void igObject_FreeMemory(struct igObject *object, void *storage);
void igObject_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif

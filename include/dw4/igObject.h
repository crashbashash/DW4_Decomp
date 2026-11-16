#ifndef DW4_IGOBJECT_H
#define DW4_IGOBJECT_H

/* igObject services. The storage calls allocate from and free to the pool the object came from. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

/* Class-membership test: 1 when `kind` is the object's own class or one of its ancestors, else 0. */
int igObject_IsKindOf(void *object, struct igMetaObject *kind);
int igObject_MallocAligned(int object, int size, unsigned short alignment);
void igObject_FreeMemory(int object, int storage);

#ifdef __cplusplus
}
#endif

#endif

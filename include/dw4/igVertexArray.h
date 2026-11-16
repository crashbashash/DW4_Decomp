#ifndef DW4_IGVERTEXARRAY_H
#define DW4_IGVERTEXARRAY_H

struct igMetaObject;
struct igVertexArray;

#ifdef __cplusplus
extern "C" {
#endif

struct igVertexArray *igVertexArray_Create(int allocator);
void igVertexArray_EnsureRegistered(void);
struct igMetaObject *igVertexArray_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

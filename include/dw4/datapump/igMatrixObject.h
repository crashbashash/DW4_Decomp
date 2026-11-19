#ifndef DW4_IGMATRIXOBJECT_H
#define DW4_IGMATRIXOBJECT_H


struct igObject;
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif
/* The meta field of igMatrixObject's matrix `_m`; its _offset locates the matrix in an instance. */
extern struct igMetaField *g_igMatrixObject_mMetaField;

struct igObject *igMatrixObject_Create(struct igMemoryPoolView *pool);

void igMatrixObject_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif

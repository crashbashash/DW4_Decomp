#ifndef DW4_IGMATRIXOBJECT_H
#define DW4_IGMATRIXOBJECT_H


struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif
struct igObject *igMatrixObject_Create(struct igMemoryPoolView *pool);

void igMatrixObject_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif

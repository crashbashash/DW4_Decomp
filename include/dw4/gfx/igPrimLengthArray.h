#ifndef DW4_IGPRIMLENGTHARRAY_H
#define DW4_IGPRIMLENGTHARRAY_H

struct igMetaObject;

struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif
struct igObject *igPrimLengthArray_Create(struct igMemoryPoolView *pool);

void igPrimLengthArray_EnsureRegistered(void);
struct igMetaObject *igPrimLengthArray_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif

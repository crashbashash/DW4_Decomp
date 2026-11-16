#ifndef DW4_IGVISUALCONTEXT_H
#define DW4_IGVISUALCONTEXT_H

struct igMetaObject;
struct igVisualContext;

#ifdef __cplusplus
extern "C" {
#endif

struct igVisualContext *igVisualContext_CreateInstance(int allocator);
void igVisualContext_EnsureRegistered(void);
struct igVisualContext *igVisualContext_FindFirst(void);
struct igMetaObject *igVisualContext_GetOrCreateMetaObject(void);
void igVisualContext_SetImageMemoryPool(int allocator);

#ifdef __cplusplus
}
#endif

#endif

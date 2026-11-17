#ifndef DW4_IGRENDERERORDEREDLIST_H
#define DW4_IGRENDERERORDEREDLIST_H

struct igRendererOrderedList;
struct igDependencyOrderedList;
struct igObject;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igRendererOrderedList *igRendererOrderedList_CreateInstance(int allocator);
struct igMetaObject *igRendererOrderedList_GetOrCreateMetaObject(void);
void igRendererOrderedList_EnsureRegistered(void);
void igRendererOrderedList_Clear(struct igDependencyOrderedList *list);
void igRendererOrderedList_Append(struct igDependencyOrderedList *list, struct igObject *object, int unique);

#ifdef __cplusplus
}
#endif

#endif

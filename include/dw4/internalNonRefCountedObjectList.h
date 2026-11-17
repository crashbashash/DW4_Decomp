#ifndef DW4_INTERNALNONREFCOUNTEDOBJECTLIST_H
#define DW4_INTERNALNONREFCOUNTEDOBJECTLIST_H
struct __internalNonRefCountedObjectList;

#ifdef __cplusplus
extern "C" {
#endif
/* The index of the first entry equal to `object`, or -1. */
int ObjectPointerList_FindIndex(struct __internalNonRefCountedObjectList *list, int object);
#ifdef __cplusplus
}
#endif

#endif

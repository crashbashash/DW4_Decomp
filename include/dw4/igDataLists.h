#ifndef DW4_IGDATALISTS_H
#define DW4_IGDATALISTS_H

#include "dw4/igTDataList.h"
struct igDataList;
struct igIntList;
struct igStringRefList;
struct igObjectList;
struct igObject;
struct igMetaField;
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

struct igIntList *igIntList_Create(int allocator);
struct igStringRefList *igStringRefList_Create(int allocator);
/* Removes the word-sized element at `index`, moving the later ones down. */
void List_RemoveWordAt(struct igDataList *list, int index);
void List_Reserve(struct igDataList *list, int capacity, int elementSize);
int List_Resize(void *list, int count, int elementSize);
void List_InsertWords(struct igDataList *list, int index, int count, const void *src);
/* Binary searches over a sorted list of words: the index of `key`, or where it would go. */
int List_BinarySearchWords(struct igDataList *list, int key, int (*compare)(int, int));
int List_LowerBound(struct igDataList *list, void *key, int (*compare)(int *, void *));
/* Retains `object` (reference count +1) and appends it. */
int ObjectList_AppendRetained(struct igObjectList *list, struct igObject *object);
int igProperty_FindByName(struct igObjectList *list, struct igMetaField *field, const char *name);
struct CallbackArray *igDataList_Register(void);
struct igMetaObject *igDataList_GetPublishedMetaObject(void);
extern struct igMetaObject *g_igDataList_metaObject;
void ObjectList_ClearRetainedPreserveCount(igTDataList<struct igObject *> *list);
void List_InsertBytes(struct igDataList *list, int index, int count, const void *src, int stride);
void List_RemoveAt(struct igDataList *l, int i, int sz);
int igDataList_GetCount(struct igDataList *list);

#ifdef __cplusplus
}
#endif

#endif

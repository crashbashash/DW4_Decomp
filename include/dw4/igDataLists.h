#ifndef DW4_IGDATALISTS_H
#define DW4_IGDATALISTS_H

struct igDataList;
struct igIntList;
struct igStringRefList;

#ifdef __cplusplus
extern "C" {
#endif

struct igIntList *igIntList_Create(int allocator);
struct igStringRefList *igStringRefList_Create(int allocator);
/* Removes the word-sized element at `index`, moving the later ones down. */
void List_RemoveWordAt(struct igDataList *list, int index);

#ifdef __cplusplus
}
#endif

#endif

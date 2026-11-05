/* src/engine/list-services.c — shared list and retained-reference primitive matches
 *
 * One translation unit: 3 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time.  Behaviour: docs/engine/object-lists.md. */
#include "dw4/reflected.h"
extern void List_Resize(void *, int, int);
void List_AppendWord(igDataList *, int);

/* 0x001c64e0
 * Copies the string pointer at `index` of a string-reference list into *out and
 * takes a reference on it.  The reference count is the word just before the
 * characters, so a non-null string gains one use. */
void StringList_CopyRetained(int *out, igStringRefList *list, int index) {
    *out = (*(int **)&list->_data)[index];
    if (*out) ++*(int *)(*out - 4);
}

/* 0x002d6b20
 * Appends one 4-byte word, growing the list by one element through the shared
 * resize helper (element size 4). */
void List_AppendWord(igDataList *list, int value) {
    int index = list->_count;
    List_Resize(list, index + 1, 4);
    (*(int **)&list->_data)[index] = value;
}

/* 0x00301e30
 * Appends an object, retaining it (reference count +1) first.  Fast path when
 * the list still has spare capacity; otherwise the generic word append grows
 * it.  The fast path does no bounds growth itself. */
void ObjectList_AppendRetained(igObjectList *list, igObject *object) {
    int count;

    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    count = list->_count;
    if (count < list->_capacity) {
        list->_count = count + 1;
        (*(int **)&list->_data)[count] = (int)(object);
        return;
    }
    List_AppendWord((igDataList *)list, (int)object);
}

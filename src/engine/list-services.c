#include "dw4/reflected.h"
extern void List_Resize(void *, int, int);
void List_AppendWord(igDataList *, int);

/* Copies the string pointer at `index` into *out and takes a reference on it. The reference count
 * is the word just before the characters. */
void StringList_CopyRetained(int *out, igStringRefList *list, int index) {
    *out = (*(int **)&list->_data)[index];
    if (*out) ++*(int *)(*out - 4);
}

void List_AppendWord(igDataList *list, int value) {
    int index = list->_count;
    List_Resize(list, index + 1, 4);
    (*(int **)&list->_data)[index] = value;
}

/* Retains the object (reference count +1), then appends it. Appends directly while capacity
 * remains, otherwise falls back to the generic word append. */
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

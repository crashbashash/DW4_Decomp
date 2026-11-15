#ifndef DW4_LISTSET_H
#define DW4_LISTSET_H

/* The list's inline `set`: stores `value` at `index` when the index is inside the list. The value is
   a `const T &`, so a constant argument (0, false, 0.0f) becomes an unnamed `.data`/`.sdata` temporary
   (the retail zero data) instead of a named global. `List` is any list class with `_count` and `_data`. */
template <class List, class T> static inline void ListSet(List *list, int index, const T &value) {
    if (list->_count != 0 && index >= 0 && index < list->_count) ((T *)list->_data)[index] = value;
}

/* Stores `value` in a list's storage at `index`, unchecked (a loop over a list's storage). */
template <class T> static inline void ListStoreAt(T *data, int index, const T &value) { data[index] = value; }

/* The same for an int list whose storage is read through the list's data accessor (a call, as the game's
   code makes it). */
extern "C" int DataList_GetData_003e9090(...);
template <class List> static inline void IntListSet(List *list, int index, const int &value) {
    int count = list->_count;
    if (count != 0 && index >= 0 && index < count) ((int *)DataList_GetData_003e9090(list))[index] = value;
}

#endif

#include "dw4/reflected.h"

/* Copies the string pointer at `index` into *out and takes a reference on it. The reference count
 * is the word just before the characters. */
void StringList_CopyRetained(int *out, igStringRefList *list, int index) {
    *out = (*(int **)&list->_data)[index];
    if (*out) ++*(int *)(*out - 4);
}

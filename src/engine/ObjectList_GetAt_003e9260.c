/* Object-reference word at an unchecked list index. Object lists and lists of lists share the
 * declaring base igDataList::_data. */
#include "dw4/reflected.h"
int ObjectList_GetAt_003e9260(igDataList *list, int index)
{
    return *(int *)(list->_data + index * 4);
}

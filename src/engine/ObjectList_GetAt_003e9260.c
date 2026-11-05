/* Object-reference word at an unchecked list index, 0x003e9260.
 * Object lists and lists of lists share the declaring base igDataList::_data.
 */
#include "dw4/reflected.h"
int ObjectList_GetAt_003e9260(igDataList *list, int index)
{
    return *(int *)(list->_data + index * 4);
}

/* Unchecked guest-word list access; declaring base is igDataList. */
#include "dw4/reflected.h"
int DataList_GetWordAt_003e9240(igDataList *list, int index)
{
    return *(int *)(list->_data + index * 4);
}

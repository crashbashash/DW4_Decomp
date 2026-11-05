/* Return the data address as a guest word, preserving the original ABI. */
#include "dw4/reflected.h"
int DataList_GetData_003e9090(igDataList *list)
{
    return list->_data;
}

/* Grows the list capacity (minimum 4, doubling below 1024, then +1024) until it holds count
 * elements, reserves it, and records the new element count. */
#include "dw4/reflected.h"

void List_Reserve(igDataList *list, int capacity);

void List_Resize(igDataList *list, int count)
{
    int capacity = list->_capacity > 4 ? list->_capacity : 4;
    while (capacity < count) {
        capacity = capacity < 1024 ? capacity * 2 : capacity + 1024;
    }
    List_Reserve(list, capacity);
    list->_count = count;
}

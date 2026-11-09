#include "dw4/reflected.h"
extern "C" {
int List_RemoveWordAt(void *, int);
int igObject_Destroy(void *);
}
#include "dw4/igTDataList.h"
extern "C" int ObjectList_RemoveAllRetained(igTDataList<igObject *> *list, igObject *object, int start) {
    int removed = 0;
    int i = list->find(object, start);
    while (i >= 0) {
        igObject *element = list->_data[i];
        if (element != 0) {
            element->_refCount = element->_refCount - 1;
            if ((element->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(element);
            }
        }
        List_RemoveWordAt(list, i);
        list->_data[list->_count] = 0;
        removed++;
        i = list->find(object, i);
    }
    return removed;
}

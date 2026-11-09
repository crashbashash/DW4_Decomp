#include "dw4/reflected.h"
extern "C" int ObjectList_AppendRetained(void *, igObject *);
#include "dw4/igTDataList.h"
extern "C" int ObjectList_AppendUniqueRetained(igTDataList<igObject *> *list, igObject *object) {
    int index = list->find(object);
    if (index == -1) {
        index = list->count();
        ObjectList_AppendRetained(list, object);
    }
    return index;
}

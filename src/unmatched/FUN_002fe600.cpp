#include "dw4/igTDataList.h"
extern "C" void List_InsertWords(void *, int, int, ...);
struct M { char p[4]; int refs; char p8[48]; M *parent; };
struct Ref { M *p; Ref(M *o) : p(o) { if (p != 0) { p->refs = p->refs + 1; } } };
extern "C" int FUN_002fe600(igTDataList<M *> *list, M *object) {
    int i = list->find(object);
    if (i != -1) {
        return i;
    }
    int n = list->count();
    while (i == -1 && object != 0) {
        Ref retained(object);
        List_InsertWords(list, n, 1, &retained);
        object = object->parent;
        i = list->find(object);
    }
    return list->_count - 1;
}

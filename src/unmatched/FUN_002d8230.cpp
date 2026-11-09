#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(void *);
int List_RemoveWordAt(void *, int);
}
#include "dw4/igTDataList.h"
struct RemovableList : igTDataList<igObject *> {
    void removeAt(int index) {
        igObject *o = _data[index];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(this, index);
        _data[_count] = 0;
    }
};
struct RemovableListHolder { char pad[28]; RemovableList *list; };
extern "C" void FUN_002d8230(RemovableListHolder *h, igObject *object) {
    int idx;
    RemovableList *f;
    f = h->list;
    idx = f->find(object);
    if (-1 < idx) {
        h->list->removeAt(idx);
    }
}

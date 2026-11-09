#include "dw4/igTDataList.h"
struct Shape { char pad[472]; igTDataList<void *> *list; };
struct Links {
    char pad[32];
    igTDataList<void *> *targets;
    igTDataList<int> *indices;
    igTDataList<void **> *slots;
};
extern "C" void FUN_001bd6b0(Links *links, Shape *shape) {
    int index;
    igTDataList<int> *indices;
    int n;
    int i;
    int j;
    void **slot;
    void *target;
    int index2;
    igTDataList<void **> *slots;
    n = shape->list->count();
    for (i = 0; i < n; i++) {
        target = shape->list->_data[i];
        j = links->targets->find(target);
        while (j != -1) {
            indices = links->indices;
            index = indices->_count;
            if (index < indices->_capacity) {
                indices->_count = indices->count() + 1;
            } else {
                List_Resize(indices, index + 1, 4);
            }
            indices->_data[index] = i;
            slot = links->targets->_data + j;
            slots = links->slots;
            index2 = slots->_count;
            if (index2 < slots->_capacity) {
                slots->_count = slots->count() + 1;
            } else {
                List_Resize(slots, index2 + 1, 4);
            }
            slots->_data[index2] = slot;
            j = links->targets->find(target, j + 1);
        }
    }
}

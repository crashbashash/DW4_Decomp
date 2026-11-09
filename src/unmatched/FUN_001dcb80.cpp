#include "dw4/reflected.h"
extern "C" int igObject_ResetFields(igObject *);
#include "dw4/igTDataList.h"
struct ObjectPool : igTDataList<igObject *> {
    int _activeCount;
    int _pad24;
    unsigned char _resetOnRelease;
};
extern "C" void FUN_001dcb80(ObjectPool *pool, igObject *object) {
    int index = pool->find(object);
    if (index >= 0) {
        if (pool->_resetOnRelease != 0) {
            igObject_ResetFields(object);
        }
        pool->_activeCount = pool->_activeCount - 1;
        int last = pool->_activeCount;
        if (last != index) {
            int count = pool->_count;
            if (count != 0 && last >= 0 && last < count && index >= 0 && index < count) {
                igObject **data = pool->_data;
                igObject *t = data[last];
                data[last] = data[index];
                data[index] = t;
            }
        }
    }
}

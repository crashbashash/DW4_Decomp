#include "dw4/reflected.h"

class SchedulerManager {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void update();
};

struct ManagerArray {
    int _pad0[2];
    int _count;
    int _capacity;
    SchedulerManager **_data;
};

struct ManagerListView : igObject {
    ManagerArray *_list;
};

extern "C" {
int igObject_Destroy(void *object);
void ObjectList_ResizeRetained(ManagerArray *list, int count);
/* matching construct: 4 variants, the inline parameter order */
void Gap__Insight__igSerialScheduler__vfunc_23(igSerialScheduler *scheduler);
}

static inline void setRetained(SchedulerManager *manager, ManagerArray *list, int index) {
    igObject *previous;

    if (manager != 0) {
        ((igObject *)manager)->_refCount = ((igObject *)manager)->_refCount + 1;
    }
    previous = (igObject *)list->_data[index];
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        list->_data[index] = manager;
    }
}

void Gap__Insight__igSerialScheduler__vfunc_23(igSerialScheduler *scheduler) {
    unsigned int count = ((ManagerListView *)scheduler->_managerList)->_list->_count;
    int i;

    ObjectList_ResizeRetained((ManagerArray *)scheduler->_cachedManagerList, count);
    for (i = 0; i < count; i++) {
        setRetained(((ManagerListView *)scheduler->_managerList)->_list->_data[i], (ManagerArray *)scheduler->_cachedManagerList, i);
    }
    for (i = 0; i < count; i++) {
        ((ManagerArray *)scheduler->_cachedManagerList)->_data[i]->update();
    }
    ObjectList_ResizeRetained((ManagerArray *)scheduler->_cachedManagerList, 0);
}

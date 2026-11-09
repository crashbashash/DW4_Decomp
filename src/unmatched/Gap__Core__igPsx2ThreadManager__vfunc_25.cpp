extern "C" {
int ChangeThreadPriority(int, int);
int GetThreadId();
int List_RemoveWordAt(void *, int);
}
#include "dw4/igTDataList.h"
struct ManagedThread;
struct Psx2ThreadTable { char pad[8]; igTDataList<ManagedThread *> *_threads; };
extern "C" void Gap__Core__igPsx2ThreadManager__vfunc_25(Psx2ThreadTable *self, ManagedThread *thread) {
    int i;
    int old;
    igTDataList<ManagedThread *> *list;
    int tid;
    tid = GetThreadId();
    old = ChangeThreadPriority(tid, 1);
    i = (list = self->_threads)->find(thread);
    if (i >= 0) {
        List_RemoveWordAt(list, i);
    }
    ChangeThreadPriority(tid, old);
}

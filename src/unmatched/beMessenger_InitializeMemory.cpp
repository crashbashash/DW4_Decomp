#include "dw4/reflected.h"

extern "C" {
int List_Reserve(void *, int, int);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_ResizeRetained(void *, int);
igObject *beMessengerArgData_Create(void *);
igObject *beMessengerDelay_Create(void *);
igObject *beMessengerWork_Create(void *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void beMessenger_InitializeMemory(beMessenger *arg0);
}

#define RETAIN_REF(q) { igObject *rr = (q); if (rr) ++rr->_refCount; }
#define RELEASE_REF(q) { igObject *rr = (q); \
    if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }

class ArgDataRef {
public:
    igObject *p;
    ArgDataRef(igObject *o) : p(o) {}
    ~ArgDataRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class WorkRef {
public:
    igObject *p;
    WorkRef(igObject *o) : p(o) {}
    ~WorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DelayRef {
public:
    igObject *p;
    DelayRef(igObject *o) : p(o) {}
    ~DelayRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

#define ALLOC(var) \
    { var = igObject_GetAllocator(arg0); var = GPR_00554c14 ? var : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

template <class Ref> static inline void storeAt(const int &list, int i, const Ref &slot) {
    igObject *cur = slot.p;
    igObjectList *l = (igObjectList *)list;
    RETAIN_REF(cur)
    RELEASE_REF(((igObject **)l->_data)[i])
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) ((igObject **)l->_data)[i] = cur;
}
#define GROUP(field, CNT, factory, Ref) { \
    igObjectList *list = (igObjectList *)arg0->field; \
    if (list->_count < (CNT) + 1) List_Reserve(list, CNT, 4); \
    ObjectList_ResizeRetained((void *)arg0->field, CNT); \
    int i; \
    for (i = 0; i < (CNT); i += 1) { \
        void *alloc; \
        ALLOC(alloc) \
        Ref slot(factory(alloc)); \
        storeAt(arg0->field, i, slot); \
    } }

void beMessenger_InitializeMemory(beMessenger *arg0)
{
    void *alloc0;

    ALLOC(alloc0)
    {
        ArgDataRef argData(beMessengerArgData_Create(alloc0));
        igObject *cur0 = argData.p;
        RETAIN_REF(cur0)
        RELEASE_REF((igObject *)arg0->_argData)
        arg0->_argData = (int)cur0;
    }
    GROUP(_workStack, 0x40, beMessengerWork_Create, WorkRef)
    GROUP(_delayStack, 0x20, beMessengerDelay_Create, DelayRef)
    GROUP(_pushPopStack, 4, beMessengerArgData_Create, ArgDataRef)
    arg0->_pushPopCount = 0;
    arg0->_isMemoryAssign = 1;
}

#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int Gap__Core__igObject__vfunc_08__002ff0f0(...);
int igMetaObject_CountInstances(...);
}
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };

struct Obj {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual void a6();
    virtual void a7();
    virtual void a8();
    virtual void a9();
    virtual void a10();
    virtual void a11();
    virtual void a12();
    virtual void a13();
    virtual void a14();
    virtual void a15();
    virtual void a16();
    virtual void a17();
    virtual void a18();
    virtual void a19();
    virtual int v88();
};
/* matching construct: the dummy-virtual slots only provide the vtable call at +88; data is read through the reflected class */
extern "C" void Gap__Bec__beNDMWLoadSlotPlayer__vfunc_08(Obj *arg0);
void Gap__Bec__beNDMWLoadSlotPlayer__vfunc_08(Obj *arg0) {
    beNDMWLoadSlotPlayer *self = (beNDMWLoadSlotPlayer *)arg0;
    beNDMWDegiDataList *l = (beNDMWDegiDataList *)self->_saveDataList;
    int n;
    /* matching construct: const read forces the early count load */
    if (((const beNDMWDegiDataList *)l)->_count > 0) {
    n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            Rel::go(((igObject **)l->_data)[i]);
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                ((int *)(l->_data + off3))[0] = 0;
                ((int *)(l->_data + off3))[1] = 0;
                ((int *)(l->_data + off3))[2] = 0;
                ((int *)(l->_data + off3))[3] = 0;
                ((int *)(l->_data + off3))[4] = 0;
                ((int *)(l->_data + off3))[5] = 0;
                ((int *)(l->_data + off3))[6] = 0;
                ((int *)(l->_data + off3))[7] = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                ((int *)(l->_data + off4))[0] = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    }
    {
        igIntList *l2 = (igIntList *)self->_accessPlList;
        if (l2->_count > 0) {
            l2->_count = 0;
        }
    }
    igMetaObject_CountInstances(arg0->v88(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

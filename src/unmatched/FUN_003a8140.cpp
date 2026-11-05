#include "dw4/reflected.h"
/* igProperty has no reflected struct: its fields stay a local layout */
struct Prop { char pad40[40]; long long f40; long long f48; float f56; };
typedef igObject Rc;
typedef beAction2InfoRam A;
extern "C" {
float __floatdisf(long long);
void *beBaseInfoDataList_Create(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
Prop *igProperty_FindByName(...);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
long long FUN_003a7fd0(A *arg0, int arg1);
float FUN_003a8140(A *arg0, int arg1);
}
struct Ref {
    igObject *p;
    Ref(igObject *x) : p(x) {}
    ~Ref() {
        Rc *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
float FUN_003a8140(A *arg0, int arg1) {
    Prop *temp_v0;
    long long temp_s0;
    long long temp_v0_2;
    float var_f0;
    if (arg0->_dataList == 0) {
        int base = igObject_GetAllocator();
        int var_v0;
        if (GPR_00554c14 != 0) {
            var_v0 = base;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        Ref sp5C((Rc *)beBaseInfoDataList_Create(var_v0));
        Rc *o = sp5C.p;
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        Rc *temp_a0 = (Rc *)arg0->_dataList;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_dataList = (int)o;
    }
    temp_v0 = igProperty_FindByName(arg0->_dataList, DAT_00585be0[0], arg1);
    temp_s0 = ((igInsightCore *)((beAction2 *)arg0->_parentManager)->_insight)->_worldTime;
    if (temp_s0 != temp_v0->f40) {
        temp_v0_2 = FUN_003a7fd0(arg0, arg1);
        long long d = temp_v0_2 - temp_v0->f48;
        if (d != 0) {
            var_f0 = __floatdisf(d) / 1.6666667e7f;
            if (!(var_f0 <= 3.0f)) {
                var_f0 = 3.0f;
            }
            temp_v0->f56 = var_f0;
            temp_v0->f48 = temp_v0_2;
        } else {
            temp_v0->f56 = 0.0f;
        }
        temp_v0->f40 = temp_s0;
    }
    return temp_v0->f56;
}

#include "dw4/reflected.h"
extern "C" {
long long FUN_00230110(float);
void *beBaseInfoDataList_Create(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
beBaseInfoRamTimer *igProperty_FindByName(...);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
long long FUN_003a7fd0(beBaseInfoRam *arg0, int arg1);
}
/* owning reference to the freshly created data list; the destructor (retail cleanup 0x33e9c0) drops one reference and destroys at zero */
struct ObjectRef {
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() {
        igObject *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
long long FUN_003a7fd0(beBaseInfoRam *arg0, int arg1) {
    beBaseInfoRamTimer *temp_s0;
    if (arg0->_dataList == 0) {
        int base = igObject_GetAllocator();
        int var_v0;
        if (GPR_00554c14 != 0) {
            var_v0 = base;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef sp4C((igObject *)beBaseInfoDataList_Create(var_v0));
        igObject *o = sp4C.p;
        if (o != 0) {
            o->_refCount = (int)o->_refCount + 1;
        }
        igObject *temp_a0 = (igObject *)arg0->_dataList;
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
                asm { nop }
            }
        }
        arg0->_dataList = (int)o;
    }
    temp_s0 = igProperty_FindByName(arg0->_dataList, DAT_00585be0[0], arg1);
    int temp_v0 = (int)(((igInsightCore *)((beBaseInfoManager *)arg0->_parentManager)->_insight)->_worldTime >> 0x12);
    float var_f12 = (float)(unsigned int)temp_v0;
    var_f12 = var_f12 * temp_s0->_timeScale;
    long long sh = FUN_00230110(var_f12);
    return (sh << 0x12) + temp_s0->_timeBias;
}

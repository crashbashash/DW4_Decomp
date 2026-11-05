/* 0x003a82f0 - FUN_003a82f0: rescale a beBaseInfoRamTimer property of a ram object. The data list is created on
 * first use (held in an ObjectRef whose destructor the exception table names), then the timer's bias is rebased so
 * the elapsed world time stays continuous across the scale change. */
#include "dw4/reflected.h"
extern "C" {
long long FUN_00230110(float);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(int);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(beBaseInfoRam *);
beBaseInfoRamTimer *igProperty_FindByName(int, int, int);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the freshly created data list: constructed from the object and released on scope
 * exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception table names is the
 * retail body 0x0033e9c0 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_003a82f0(beBaseInfoRam *arg0, int arg1, float fparg0) {
    beBaseInfoRamTimer *prop;
    float scale;
    float cur;
    long long b;
    long long r;

    if (arg0->_dataList == 0) {
        int a = igObject_GetAllocator(arg0);
        ObjectRef created(beBaseInfoDataList_Create(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        igObject *p = created.p;
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
        igObject *old = (igObject *)arg0->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_dataList = (int)p;
    }
    prop = igProperty_FindByName(arg0->_dataList, DAT_00585be0[0], arg1);
    cur = prop->_timeScale;
    if (fparg0 != cur) {
        scale = (float)(unsigned int)(int)(((igInsightCore *)((beBaseInfoManager *)arg0->_parentManager)->_insight)->_worldTime >> 0x12);
        r = FUN_00230110(scale * cur);
        r <<= 0x12;
        r += prop->_timeBias;
        b = r;
        b -= FUN_00230110(scale * fparg0) << 0x12;
        prop->_timeBias = b;
        prop->_timeScale = fparg0;
        prop->_keikaFrame = 0.0f;
    }
}

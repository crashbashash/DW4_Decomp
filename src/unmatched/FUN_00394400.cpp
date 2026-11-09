#include "dw4/reflected.h"
/* Publishes a model-control event to the Lua side. arg0 is the beModelCtrl (_luaManager), arg1 a
 * beBaseInfoRam (_ramNo, _dataList = the property list, created lazily and installed through an
 * owning stack reference). The event arguments are staged in a fixed block, the chunk name is
 * formatted from arg2/arg4 and run; the second cell of the property is refreshed from the block
 * afterwards when the chunk left it untouched. */
typedef struct Cell { char pad12[12]; int value; } Cell;
typedef struct PropData { char pad8[8]; Cell *first; Cell *second; int third; } PropData;
typedef struct Prop { char pad16[16]; int base; PropData *data; } Prop;
extern "C" {
igObject *beBaseInfoDataList_Create(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
Prop *igProperty_FindByName(...);
int sprintf(...);
int beLua__RunNamedChunk(...);
extern int DAT_0050ef60[4];
extern int DAT_0050f110[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern beBaseInfoRam *DAT_0058a1e0[4];
extern int DAT_0058a1e4[4];
extern int DAT_0058a1e8[4];
extern int DAT_0058a1ec[4];
extern int DAT_0058a1f0[4];
extern int DAT_0058a1f4[4];
extern int DAT_0058a1f8[4];
extern int DAT_0058a1fc[4];
extern int DAT_0058a200[4];
extern int DAT_0058a204[4];
extern int DAT_0058a208[4];
extern int DAT_0058a20c[4];
extern char DAT_0058a210[16];
extern int DAT_0058a214[4];
extern unsigned char GPR_00554c14;
void FUN_00394400(beModelCtrl *arg0, beBaseInfoRam *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9);
}
/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_00394400(beModelCtrl *arg0, beBaseInfoRam *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9) {
    int spA0[11];
    int t;
    int var_v0;
    igObject *p;
    igObject *old;
    Prop *prop;
    PropData *q;
    int saved;
    Cell *h;

    if (arg1->_dataList == 0) {
        t = igObject_GetAllocator(arg1);
        if (GPR_00554c14 != 0) {
            var_v0 = t;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(var_v0));
        p = created.p;
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        arg1->_dataList = (int)p;
    }
    prop = igProperty_FindByName((igObject *)arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]);
    q = prop->data;
    DAT_0058a1e0[0] = arg1;
    DAT_0058a1e4[0] = arg1->_ramNo;
    DAT_0058a1e8[0] = prop->base + 0x20;
    DAT_0058a1ec[0] = q->first->value;
    DAT_0058a1f0[0] = q->second->value;
    DAT_0058a1f4[0] = q->third;
    DAT_0058a1f8[0] = arg4;
    DAT_0058a1fc[0] = arg5;
    DAT_0058a200[0] = arg6;
    DAT_0058a204[0] = arg7;
    DAT_0058a208[0] = arg8;
    DAT_0058a20c[0] = arg9;
    DAT_0058a210[0] = 1;
    DAT_0058a214[0] = arg3;
    saved = q->second->value;
    sprintf(spA0, &DAT_0050f110[0], arg2, arg4);
    beLua__RunNamedChunk(arg0->_luaManager, spA0, 0);
    h = q->second;
    if (saved == h->value) {
        h->value = DAT_0058a1f0[0];
    }
}

/* 0x003a7d80 - FUN_003a7d80: make sure the info ram has a property data list, then report whether a property of
 * the given name exists in it.  The lazily created list is owned by a stack reference while it is retained into
 * the ram and the previous list is released. */
#include "dw4/reflected.h"
extern "C" {
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(igObject *);
int igObject_GetAllocator();
int igProperty_FindByName(int, int, int);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int FUN_003a7d80(beBaseInfoRam *arg0, int arg1);
}
/* Owning stack reference to the freshly created data list: constructed from the object and released on
 * scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception
 * table names is the retail body 0x0033e9c0 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
int FUN_003a7d80(beBaseInfoRam *arg0, int arg1) {
    int t;
    int var_v0;
    igObject *p;
    igObject *old;

    if (arg0->_dataList == 0) {
        t = igObject_GetAllocator(); /* matching construct: a0 still holds arg0, retail passes it without a move */
        if (GPR_00554c14 != 0) {
            var_v0 = t;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        {
            ObjectRef r(beBaseInfoDataList_Create(var_v0));
            p = r.p;
            if (p != 0) {
                p->_refCount = p->_refCount + 1;
            }
            old = (igObject *)arg0->_dataList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(old);
                    /* asm-body: reason=retail pads this release with a second nop (0x003a7e24) that the unit's
                     * profile never schedules from C/C++ tried=same release spelling without the nop (268 of 272
                     * bytes), the stack-reference rewrite of this unit */
                    asm { nop }
                }
            }
            arg0->_dataList = (int)p;
        }
    }
    return igProperty_FindByName(arg0->_dataList, DAT_00585be0[0], arg1) != 0;
}

/* Binds a memory-card utility controller to its messenger and fills its slot list with 5, 2 or 9
 * slot windows according to arg2. Every new slot is retained by the list and released by its stack
 * reference at the end of the loop body (a for loop: the release precedes the index increment). */
#include "dw4/reflected.h"

extern "C" {
igObject *FUN_003c5aa0(int);
igObject *FUN_003c5cf0(int);
igObject *FUN_003c5ee0(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, igObject *);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(beNDMWMcUtilCtrl *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

/* Owning stack reference to a new slot window of one of the three slot classes (kind 0..2 follows
 * the arg2 case), released on scope exit (reference count in the low 23 bits of _refCount). */
template <int kind> class SlotRef {
public:
    igObject *p;
    SlotRef(igObject *o) : p(o) {}
    ~SlotRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

extern "C" void FUN_003f0ed0(beNDMWMcUtilCtrl *arg0, int arg1, int arg2);
void FUN_003f0ed0(beNDMWMcUtilCtrl *arg0, int arg1, int arg2) {
    int s0;
    int v;

    arg0->_messenger = arg1;
    arg0->_isRun = 0;
    arg0->_isResult = 0;
    arg0->_isRdy = 0;
    switch (arg2) {
    case 0:
        for (s0 = 0; s0 < 5; s0++) {
            v = igObject_GetAllocator(arg0);
            if (GPR_00554c14 != 0) {
                v = (int)v;
            } else {
                v = Memory_GetAllocatorBySelector(DAT_00587110[0]);
            }
            SlotRef<0> slot(FUN_003c5ee0(v));
            ObjectList_AppendRetained(arg0->_slot, slot.p);
        }
        return;
    case 1:
        for (s0 = 0; s0 < 2; s0++) {
            v = igObject_GetAllocator(arg0);
            if (GPR_00554c14 != 0) {
                v = (int)v;
            } else {
                v = Memory_GetAllocatorBySelector(DAT_00587110[0]);
            }
            SlotRef<1> slot(FUN_003c5cf0(v));
            ObjectList_AppendRetained(arg0->_slot, slot.p);
        }
        return;
    case 2:
        for (s0 = 0; s0 < 9; s0++) {
            v = igObject_GetAllocator(arg0);
            if (GPR_00554c14 != 0) {
                v = (int)v;
            } else {
                v = Memory_GetAllocatorBySelector(DAT_00587110[0]);
            }
            SlotRef<2> slot(FUN_003c5aa0(v));
            ObjectList_AppendRetained(arg0->_slot, slot.p);
        }
        break;
    }
}

/* Three-slot sibling of FUN_003de7a0: case 1 binds slots 0..2, case 0 builds a pooled value object
 * per slot from table entry (index-1 wrapped to f44-1 when below f48, index, index+1 wrapped to
 * f48 at f44) and binds it. Each object lives in a scoped ObjectRef whose destructor is the retail
 * reference-destructor duplicate 0x003832d0; exceptions off. Alternate compiler -O3,p. The last
 * wrap must be written as if/else on the unwrapped n (if (n >= f44) s0 = f48; else s0 = n;): the
 * if-without-else spelling pads the join label with a nop. */
#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(void *);
struct Obj { int word0; unsigned refs; int f8; unsigned short *f12; };
struct Rec { int mod; unsigned short v[32]; };
Obj *FUN_003614f0(int);
int beUnicodeObj_AllocateBuffer(Obj *, int);
int TextOrder_ClearFont(int, int *, int, int);
int FUN_003ec120(int, int *, int, int, Obj *, int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(beNDMWLoadIntf2NameSel *);
extern struct Rec DAT_004cc860[];
extern int DAT_00516f10[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the slot's text object: constructed from the freshly created object and
 * released on scope exit (reference count in the low 23 bits of refs).  The out-of-line copy the
 * exception table names is the retail body 0x003832d0 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv); the three slots share the one class, so the table names it three times. */
class ObjectRef {
public:
    Obj *p;
    ObjectRef(Obj *o) : p(o) {}
    ~ObjectRef() { Obj *o = p; if (o != 0) { --o->refs; if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_003de480(beNDMWLoadIntf2NameSel *arg0, int arg1) {
    int s0;
    int a;
    switch (arg1) {
    case 1:
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 2);
        return;
    case 0: {
        {
        s0 = arg0->_tatePoint - 1;
        if (s0 < arg0->_tateMin) s0 = arg0->_tateMax - 1;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ObjectRef r0(FUN_003614f0(a));
        beUnicodeObj_AllocateBuffer(r0.p, 1);
        *r0.p->f12 = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 0, r0.p, 1, 0);
        }
        {
        s0 = arg0->_tatePoint;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ObjectRef r1(FUN_003614f0(a));
        beUnicodeObj_AllocateBuffer(r1.p, 1);
        *r1.p->f12 = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 1, r1.p, 1, 0);
        }
        {
        int n = arg0->_tatePoint + 1;
        if (n >= arg0->_tateMax) s0 = arg0->_tateMin; else s0 = n;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ObjectRef r2(FUN_003614f0(a));
        beUnicodeObj_AllocateBuffer(r2.p, 1);
        *r2.p->f12 = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 2, r2.p, 1, 0);
        }
    }
    }
}

#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(void *);
struct Rec { int mod; unsigned short v[32]; };
beUnicodeObj *FUN_003614f0(int);
int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
int TextOrder_ClearFont(int, int *, int, int);
int FUN_003ec120(int, int *, int, int, beUnicodeObj *, int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(beNDMWLoadIntf2NameSel *);
extern struct Rec DAT_004cc860[];
extern int DAT_00516f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the slot's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */
class ObjectRef {
public:
    beUnicodeObj *p;
    ObjectRef(beUnicodeObj *o) : p(o) {}
    ~ObjectRef() { beUnicodeObj *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_003de7a0(beNDMWLoadIntf2NameSel *arg0, int arg1) {
    int s1;
    int s3;
    int i;
    int a;
    switch (arg1) {
    case 1:
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 2);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 3);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 4);
        return;
    case 0:
        s1 = arg0->_yokoPoint;
        for (i = 0; i < 5; i++) {
            s3 = (s1 + i) % DAT_004cc860[arg0->_tatePoint].mod;
            a = igObject_GetAllocator(arg0);
            a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            ObjectRef r(FUN_003614f0(a));
            beUnicodeObj_AllocateBuffer(r.p, 1);
            *(unsigned short *)r.p->_buffer = DAT_004cc860[arg0->_tatePoint].v[s3];
            FUN_003ec120(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, i, r.p, 1, 0);
        }
    }
}

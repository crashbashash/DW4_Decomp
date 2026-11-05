/* 0x003de990 - FUN_003de990. Slot-table fill, sibling of FUN_003de7a0 with six (mode 0) or eight (mode 1/default) slots and two bind tables: arg1 == 1 issues identical bind calls; arg1 == 0 builds a pooled value object per slot whose kind (1 or 2) selects the last flag, stops at the first empty 16-bit entry and binds the remaining slots plain. ObjectRef is the stack smart pointer holding each value object (its destructor is the compiler-emitted duplicate of the retail body 0x003832d0, config/SLUS-20836/unit-objects.json). Alternate compiler -O3,p, exceptions off. */
#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(void *);
struct Obj { int word0; unsigned refs; int f8; unsigned short *f12; };
/* The reflected beNDMWLoadIntf2NameSel registers 288 bytes; reflection lists its fields up to +100 and the per-cell
 * save area is the unlisted tail of the same object (+104..), so NameSelTail is laid over it (as in
 * src/game/beNDMWLoadIntf2NameSel__Update.c). */
struct NameSelTail { char _reflected[104]; int save[24]; int mode[9]; unsigned short name[9]; };
union NameSelRam { beNDMWLoadIntf2NameSel n; NameSelTail t; };
Obj *FUN_003614f0(int);
int beUnicodeObj_AllocateBuffer(Obj *, int);
int TextOrder_ClearFont(int, int *, int, int);
int FUN_003ec120(int, int *, int, int, Obj *, int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(NameSelRam *);
extern int DAT_00516f30[4];
extern int DAT_00516f40[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to a slot's value object: constructed from the freshly created object and
 * released on scope exit (reference count in the low 23 bits of refs).  The out-of-line copy the
 * exception table names is the retail body 0x003832d0 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv). */
class ObjectRef {
public:
    Obj *p;
    ObjectRef(Obj *o) : p(o) {}
    ~ObjectRef() { Obj *o = p; if (o != 0) { --o->refs; if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* create a value object for cell I (allocator chosen by the global selector flag), copy the cell's
 * 16-bit entry into it and bind it to table P with flag F; the object is released at the end of the block */
#define BIND(P, I, F) do { int a = igObject_GetAllocator(arg0); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); ObjectRef r(FUN_003614f0(a)); beUnicodeObj_AllocateBuffer(r.p, 1); *r.p->f12 = arg0->t.name[I]; FUN_003ec120(arg0->n._textOrder, P, arg0->n._ramNo, I, r.p, 1, F); } while (0)
extern "C" void FUN_003de990(NameSelRam *arg0, int arg1) {
    int i;
    int j;
    switch (arg0->n._langID) {
    case 0:
        switch (arg1) {
        case 1:
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 0);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 1);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 2);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 3);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 4);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 5);
            return;
        case 0:
            i = 0;
            do {
                if (arg0->t.name[i] == 0) break;
                switch (arg0->t.mode[i]) {
                case 0: break;
                default: break;
                case 1: BIND(DAT_00516f30, i, 1); break;
                case 2: BIND(DAT_00516f30, i, 0); break;
                }
                i++;
            } while (i < 6);
            for (; i < 6; i++) TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, i);
            return;
        }
        break;
    case 1:
    default:
        switch (arg1) {
        case 1:
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 0);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 1);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 2);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 3);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 4);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 5);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 6);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 7);
            return;
        case 0:
            j = 0;
            do {
                if (arg0->t.name[j] == 0) break;
                switch (arg0->t.mode[j]) {
                case 0: break;
                default: break;
                case 1: BIND(DAT_00516f40, j, 1); break;
                case 2: BIND(DAT_00516f40, j, 0); break;
                }
                j++;
            } while (j < 8);
            for (; j < 8; j++) TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, j);
            break;
        }
        break;
    }
}

#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
extern "C" {
/* reference-counted string-chunk header: refcount at +4, length at +12 */
struct RefCountedHeader : public igObject { int w8; int w12; };
RefCountedHeader *FUN_00236f80(...);
int strlen(...);
int FUN_0030b3c0(...);
int FUN_0030b460(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_SelectGroup(...);
int beNDMWItemBase_GetRecordString(...);
extern char *DAT_004c22f0[4];
extern int DAT_005199e0[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b50[4];
extern int DAT_00519b78[4];
extern int DAT_00519c28[4];
extern int DAT_00519f30[4];
extern int DAT_00519f40[4];
extern int DAT_00587d08[4];
extern int DAT_0058b028[4];
}
/* Slot record: digit byte at +24. */
struct Slot { char p0[24]; int f24; };
/* Element-buffer list header: buffer pointer at +16. */
struct SlotList { char p[16]; Slot **arr; };
/* Retained share of the system's global string object. */

extern "C" void Gap__Bec__beNDMWStatusMainSlot__vfunc_26(beNDMWStatusMainSlot *a);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_26(beNDMWStatusMainSlot *a) {
    Slot *s2 = 0;
    int temp; /* matching construct: one register serves the record string and then the held string's length */
    char buf[2];
    RefCountedHeader *p;
    RefCountedHeader *q;
    char *str;
    int *var;
    if (a->_retCode != -1) {
        s2 = ((SlotList *)a->_mainSlot)->arr[a->_retCode];
    }
    if (s2 != 0) {
        temp = beNDMWItemBase_GetRecordString(s2, FUN_00236f80(a->_insight, DAT_0058b028[0]), &DAT_00519f40[0]);
        buf[1] = 0;
        buf[0] = s2->f24 + 0x30;
        {
        igSmartPointer<RefCountedHeader> sp48((RefCountedHeader *)*(int *)((char *)FUN_00236f80(a->_insight, DAT_00587d08[0]) + 72), kRetainReference);
        FUN_0030b3c0(sp48.p, temp);
        q = sp48.p;
        temp = q->w12;
        FUN_0030b460(q, buf, temp, strlen(buf));
        p = sp48.p;
        str = (p->w8 == 0) ? DAT_004c22f0[0] : (char *)p->w8;
        }
        beMessenger_SelectGroup(a->_messenger, &DAT_00519c28[0]);
        beMessenger_AppendString(a->_messenger, &DAT_00519b50[0]);
        beMessenger_AppendString(a->_messenger, &DAT_005199e0[0]);
        beMessenger_AppendString(a->_messenger, str);
        beMessenger_DispatchSelected(a->_messenger, &DAT_00519f30[0]);
        var = &DAT_00519b78[0];
    } else {
        var = &DAT_00519b00[0];
    }
    beMessenger_SelectGroup(a->_messenger, &DAT_00519c28[0]);
    beMessenger_AppendString(a->_messenger, &DAT_00519b50[0]);
    beMessenger_AppendString(a->_messenger, &DAT_005199e0[0]);
    beMessenger_AppendString(a->_messenger, var);
    beMessenger_DispatchSelected(a->_messenger, &DAT_00519b08[0]);
}

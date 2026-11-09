#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
/* igObject-style string object: refcount, data pointer and length are not reflected fields */
struct Str : public igObject { int data; int len; };
extern "C" {
int strlen(...);
int FUN_00236f80(...);
int FUN_0030b3c0(...);
int FUN_0030b460(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_SelectGroup(...);
int beNDMWItemBase_GetRecordString(...);
extern int *DAT_004c22f0[4];
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
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_26(beNDMWStatusPowerSocket *a);
}
/* Retained share of the system's global string object. */

void Gap__Bec__beNDMWStatusPowerSocket__vfunc_26(beNDMWStatusPowerSocket *a) {
    int *temp_s1;
    int *var_s1_2;
    int temp_v1;
    int var_s1;
    int temp_v0; /* matching construct: one register serves the record string and then the held string's length */
    char sp4C[2];
    Str *t2;
    Str *t3;
    beNDMWItemBaseList *items;

    var_s1 = 0;
    temp_v1 = a->_retCode;
    if (temp_v1 != -1) {
        items = (beNDMWItemBaseList *)a->_powerSocket;
        var_s1 = *(int *)(items->_data + (temp_v1 * 4));
    }
    if (var_s1 != 0) {
        temp_v0 = beNDMWItemBase_GetRecordString(var_s1, FUN_00236f80(a->_insight, DAT_0058b028[0]), &DAT_00519f40[0]);
        sp4C[1] = 0;
        sp4C[0] = *(int *)(var_s1 + 24) + 0x30;
        {
        igSmartPointer<Str> sp48((Str *)((beSystem *)FUN_00236f80(a->_insight, DAT_00587d08[0]))->_globalStrObj, kRetainReference);
        FUN_0030b3c0(sp48.p, temp_v0);
        t2 = sp48.p;
        temp_v0 = t2->len;
        FUN_0030b460(t2, sp4C, temp_v0, strlen(sp4C));
        t3 = sp48.p;
        temp_s1 = (int *)t3->data;
        temp_s1 = (temp_s1 == 0) ? DAT_004c22f0[0] : temp_s1;
        }
        beMessenger_SelectGroup(a->_messenger, &DAT_00519c28[0]);
        beMessenger_AppendString(a->_messenger, &DAT_00519b50[0]);
        beMessenger_AppendString(a->_messenger, &DAT_005199e0[0]);
        beMessenger_AppendString(a->_messenger, temp_s1);
        beMessenger_DispatchSelected(a->_messenger, &DAT_00519f30[0]);
        var_s1_2 = (int *)(&DAT_00519b78[0]);
    } else {
        var_s1_2 = (int *)(&DAT_00519b00[0]);
    }
    beMessenger_SelectGroup(a->_messenger, &DAT_00519c28[0]);
    beMessenger_AppendString(a->_messenger, &DAT_00519b50[0]);
    beMessenger_AppendString(a->_messenger, &DAT_005199e0[0]);
    beMessenger_AppendString(a->_messenger, var_s1_2);
    beMessenger_DispatchSelected(a->_messenger, &DAT_00519b08[0]);
}

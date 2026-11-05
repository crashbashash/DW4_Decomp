#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct PropertyRecord { char header[12]; void *value; } PropertyRecord;
int FUN_002eb010(int);
PropertyRecord *FUN_003a9250(int, int *, ...); /* the third argument (a default list) is optional */
PropertyRecord *FUN_003a92e0(int, void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int beDataBase_GetRecordString(int, int, void *);
igObject *beMessenger_GetObject(int, int);
int beMessenger_SendNamed(int, void *, void *, int, void *);
int igObject_Destroy(void *);
#define A_(x) (x) /* matching construct: identity macro kept to hold the original expression shape */

PropertyRecord *igProperty_GetRecord(int, void *);
PropertyRecord *igProperty_GetRecordArray(int, void *);
extern int DAT_00518798[4];
extern int DAT_005187a0[4];
extern int DAT_005187b0[4];
extern int DAT_00518848[4];
extern int DAT_00518858[4];
extern int DAT_00518860[4];
extern int DAT_00518868[4];
extern int DAT_00518870[4];
extern int DAT_00518880[4];
extern int DAT_00518ae8[4];
extern int DAT_00518b00[4];
extern int DAT_00518b10[4];
extern int DAT_00518b30[4];
extern int DAT_00518b40[4];
extern int DAT_00518b50[4];
extern int DAT_00518b60[4];
extern int DAT_00518bc8[4];
extern int DAT_00519420[4];
extern int DAT_00519430[4];
extern int DAT_00519438[4];
extern int DAT_00586f20[4];

/* matching construct: inline release macro with block-local q */
#define RELO(X) { igObject *q = (X); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q); } }
void FUN_003f82a0(beNDMWGameRam *arg0, int arg1, int arg2) {
/* matching construct: local declaration order fixes register allocation */
//D<
    int var_s0b;
    igIntList *a0;
    int s4;
    igIntList *a2b;
    igIntList *a0b;
    PropertyRecord *s1c;
    int base9;
    igObject *o;
    int hd;
    int cnt2;
    PropertyRecord *s1b;
    int v0;
    int e1;
    int cnt1;
    igIntList *l1;
    igObject *s0b;
    igIntList *l2;
    int e2;
    PropertyRecord *s1a;
    PropertyRecord *s1;
    igObject *old;
    int base11;
    igObject *s0a;
    igObject *s0c;
    int var_s2;
    int e1L;
    int s0;
    int var_s0;
    igIntList *a2;
    int var_s2b;
    int s1i;
//D>
    s4 = A_(((int *)((igIntList *)arg0->_playerDataListList)->_data)[arg1]);
    igProperty_GetRecord(s4, &DAT_00518858[0]);
    igProperty_GetRecord(s4, &DAT_00518848[0])->value = (void *)arg2;
    if (arg0->_dBShinka == 0) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
        o = beMessenger_GetObject(arg0->_messenger, 0);
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)arg0->_dBShinka;
        RELO(old)
        arg0->_dBShinka = (int)o;
    }
    s0 = beDataBase_GetRecordString(arg0->_dBShinka, arg2, &DAT_00518bc8[0]);
    s1 = FUN_003a92e0(s4, &DAT_00518870[0]);
    if (DAT_00586f20[0] == 0) {
        v0 = FUN_002eb010(16);
        if (v0 != 0) v0 = StringPool_Construct(v0);
        DAT_00586f20[0] = v0;
    }
    s1i = StringPool_Intern(DAT_00586f20[0], s0);
    hd = (int)s1->value;
    if (hd != 0) {
        int *p = (int *)(hd - 8);
        int c = *(int *)(hd - 4) - 1;
        *(int *)(hd - 4) = c;
        if (c == 0) StringChunk_ReleaseHeader(*p, p);
    }
    s1->value = (void *)s1i;
    l1 = (igIntList *)FUN_003a9250(s4, &DAT_00518b30[0])->value;
    s0 = arg2 * 4;
    e1 = ((int *)l1->_data)[arg2];
    igProperty_GetRecord(s4, &DAT_00518858[0])->value = (void *)e1;
    l2 = (igIntList *)FUN_003a9250(s4, &DAT_00518b40[0])->value;
    e2 = ((int *)l2->_data)[arg2];
    igProperty_GetRecord(s4, &DAT_00518880[0])->value = (void *)e2;
    /* matching construct: base9/base11 hoisted into locals, else MWCC strength-reduces the index */
    base9 = arg2 * 9;
    var_s2 = 0;
    var_s0 = 0;
    do {
        a2 = (igIntList *)FUN_003a9250(s4, &DAT_00518b50[0])->value;
        e1L = ((int *)a2->_data)[base9 + var_s2];
        a0 = (igIntList *)FUN_003a9250(s4, &DAT_00518860[0], a2)->value;
        cnt1 = a0->_count;
        if (cnt1 != 0 && var_s2 >= 0 && var_s2 < cnt1) ((int *)(a0->_data + var_s0))[0] = e1L;
        var_s2 += 1;
        var_s0 += 4;
    } while (var_s2 < 9);
    base11 = arg2 * 11;
    var_s2b = 0;
    var_s0b = 0;
    do {
        a2b = (igIntList *)FUN_003a9250(s4, &DAT_00518b60[0])->value;
        e2 = ((int *)a2b->_data)[base11 + var_s2b];
        a0b = (igIntList *)FUN_003a9250(s4, &DAT_00518868[0], a2b)->value;
        cnt2 = a0b->_count;
        if (cnt2 != 0 && var_s2b >= 0 && var_s2b < cnt2) ((int *)(a0b->_data + var_s0b))[0] = e2;
        var_s2b += 1;
        var_s0b += 4;
    } while (var_s2b < 11);
    if (arg1 == 0) {
        s0a = (igObject *)igProperty_GetRecordArray(s4, &DAT_00518ae8[0])->value;
        s1a = igProperty_GetRecordArray(arg0->_commonDataList, &DAT_00518798[0]);
        if (s0a != 0) s0a->_refCount = s0a->_refCount + 1;
        old = (igObject *)s1a->value;
        RELO(old)
        s1a->value = s0a;
        s0b = (igObject *)igProperty_GetRecordArray(s4, &DAT_00518b00[0])->value;
        s1b = igProperty_GetRecordArray(arg0->_commonDataList, &DAT_005187a0[0]);
        if (s0b != 0) s0b->_refCount = s0b->_refCount + 1;
        old = (igObject *)s1b->value;
        RELO(old)
        s1b->value = s0b;
        s0c = (igObject *)FUN_003a9250(s4, &DAT_00518b10[0])->value;
        s1c = FUN_003a9250(arg0->_commonDataList, &DAT_005187b0[0]);
        if (s0c != 0) s0c->_refCount = s0c->_refCount + 1;
        old = (igObject *)s1c->value;
        RELO(old)
        s1c->value = s0c;
    }
}
} /* extern "C" */

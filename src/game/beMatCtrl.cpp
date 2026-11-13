#include "dw4/reflected.h"

extern "C" int igInsightCore_FindManager(int, int);
extern "C" int Gap__Bec__beMatCtrl__vfunc_30(void);
extern "C" int Gap__Bec__beMatCtrl__vfunc_20(void);
extern "C" int beMessenger_RegisterReceiver(int, int, int, int, int);
extern "C" int igSwitch_EnableAllChildren(int);
extern "C" int igSwitch_DisableAllChildren(int);
extern "C" int FUN_0035a6b0(...);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" bool beMatCtrl_IsPlayer(beMatCtrl *arg0);
/* beMatCtrl._wkPlExist (+32) is an igBoolArray; the reflected header declares only its first word, so the byte array is spelled by this view.
 * matching construct: an array member keeps retail's addu-then-lbu shape; the view carries the receiver, the other fields are read through beMatCtrl. */
struct beMatCtrlView { int pad[8]; unsigned char act[8]; int idx; int pad3[3]; int a; int b; };
extern "C" bool beMatCtrl_IsAllPlayer(beMatCtrlView *c);
extern "C" int beMatCtrl_GetPlayerNo(beMatCtrl *c);
extern "C" int beMatCtrl_IsRidePlayer(beMatCtrl *arg0, int arg1);
extern "C" int beMatCtrl_IsRideOffPlayer(beMatCtrl *arg0, int arg1);
extern "C" void beMatCtrl_SetRun(beMatCtrl *self, int value);
extern "C" int beMatCtrl_GetPlayerMatStat(beMatCtrl *m, int n);
extern "C" int igObject_Destroy(igDataList *);
extern "C" int g_beLua_metaObject[4];
extern "C" void Gap__Bec__beMatCtrl__vfunc_32(beMatCtrl *arg0);
extern "C" int g_beMatCtrlInfo_metaObject[4];
extern "C" int g_beMatCtrl_metaObject[4];
extern "C" int MATCTRL[4];
extern "C" void Gap__Bec__beMatCtrl__vfunc_29(beMatCtrl *self, int selector);
/* tree is a beMatCtrlSearchList (igObjectList): _count +8, _data +16 = beMatCtrlSearch *[]; node
 * is a beMatCtrlSearch: _minX +8, _maxX +12, _matNO +16, _memberList +24 = child list; cells is a
 * beMatCtrlDataList: _count +8, _data +16 = beMatCtrlData *[], cell->_chkBox +12 = box; flags is
 * an igIntList: _count +8, _data +16 = int[]. Arena references are 4-byte handles in the reflected
 * fields; the casts below widen them to the pointers the code dereferences. */
struct B;
struct V;
extern "C" int FUN_0018b630(struct B *arg0, struct V *arg1);
extern "C" void FUN_0038b080(int arg0, igIntList *flags, beMatCtrlSearchList *tree, int bit, float *pos, beMatCtrlDataList *cells);
extern "C" int Gap__Bec__beMatCtrl__vfunc_34(beMatCtrl *arg0, beMatCtrlInfoRam *arg1, beMatCtrlInfo *arg2);

bool beMatCtrl_IsPlayer(beMatCtrl *arg0)
{
    bool r = false;
    if (*(int *)(((igDataList *)arg0->_wkMatOnList)->_data + arg0->_wkChkMat * 4) != 0) {
        r = true;
    }
    return r;
}

bool beMatCtrl_IsAllPlayer(beMatCtrlView *c) {
    bool r = true;
    beMatCtrl *m = (beMatCtrl *)c;
    for (int i = 0; i < 4; i++) {
        if (c->act[i] != 0) {
            int bit = 1 << i;
            if (bit != (bit & ((unsigned int *)((igDataList *)m->_wkMatOnList)->_data)[m->_wkChkMat])) { r = false; break; }
        }
    }
    return r;
}

int beMatCtrl_GetPlayerNo(beMatCtrl *c) {
    unsigned char *p = (unsigned char *)c; /* matching construct: separate local byte base keeps the retail operand order of the byte index add; _wkPlExist (+32) is four inline bool bytes, reflected as one int */
    int k;
    int bit;
    int i;
    for (i = 0; i < 4; i++) {
        if (p[i + 32] != 0) {
            k = c->_wkChkMat * 4;
            bit = 1 << i;
            if (bit == (bit & *(unsigned int *)(((igDataList *)c->_wkMatOnList)->_data + k)) && bit != (bit & *(unsigned int *)(((igDataList *)c->_wkMatOldOnList)->_data + k))) return i;
        }
    }
    return 0;
}

int beMatCtrl_IsRidePlayer(beMatCtrl *arg0, int arg1) {
    int idx;
    int bit;

    idx = arg0->_wkChkMat * 4;
    bit = 1 << arg1;
    if ((bit == (bit & *(int *)((char *)((igDataList *)arg0->_wkMatOnList)->_data + idx))) && (bit != (bit & *(int *)((char *)((igDataList *)arg0->_wkMatOldOnList)->_data + idx)))) {
        return 1;
    }
    return 0;
}

int beMatCtrl_IsRideOffPlayer(beMatCtrl *arg0, int arg1) {
    int off = arg0->_wkChkMat * 4;
    int bit = 1 << arg1;
    int r;
    if (bit != (bit & *(int *)(((igDataList *)arg0->_wkMatOnList)->_data + off))
        && bit == (bit & *(int *)(((igDataList *)arg0->_wkMatOldOnList)->_data + off)))
        r = 1;
    else {
        r = 0;
    }
    return r;
}

/* Deferred material activation request. */

void beMatCtrl_SetRun(beMatCtrl *self, int value) {
    self->_wkChgFlagNO = self->_wkChkMat;
    self->_wkChgFlag = value;
}

int beMatCtrl_GetPlayerMatStat(beMatCtrl *m, int n) {
    igIntList *p56;
    igIntList *p60;
    int idx;
    int mask;
    unsigned char b;
    int x;
    int r;
    int a;
    idx = m->_wkChkMat;
    p60 = (igIntList *)m->_wkMatOldOnList;
    x = idx * 4;
    mask = 1 << n;
    b = mask == (mask & *(int *)((char *)p60->_data + x));
    p56 = (igIntList *)m->_wkMatOnList;
    a = mask == (mask & *(int *)((char *)p56->_data + x));
    r = 0;
    if (a == 1 && b == 1) r = 3;
    else if (a == 1 && b != 1) r = 2;
    else if (a != 1 && b == 1) r = 1;
    else if (a != 1 && b != 1) r = 0;
    return r;
}

void Gap__Bec__beMatCtrl__vfunc_32(beMatCtrl *arg0) {
    igDataList *temp_a0;
    igDataList *temp_a0_2;
    igDataList *temp_v1;
    igDataList *temp_v1_2;

    arg0->_lua = igInsightCore_FindManager(arg0->_insight, g_beLua_metaObject[0]);
    temp_v1 = (igDataList *)(arg0->_wkMatOnList);
    if (temp_v1 != 0) {
        temp_v1->_count = 0;
        temp_a0 = (igDataList *)(arg0->_wkMatOnList);
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_wkMatOnList = 0;
    }
    temp_v1_2 = (igDataList *)(arg0->_wkMatOldOnList);
    if (temp_v1_2 != 0) {
        temp_v1_2->_count = 0;
        temp_a0_2 = (igDataList *)(arg0->_wkMatOldOnList);
        if (temp_a0_2 != 0) {
            temp_a0_2->_refCount = temp_a0_2->_refCount - 1;
            if ((temp_a0_2->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->_wkMatOldOnList = 0;
    }
}

int Gap__Bec__beMatCtrl__vfunc_30(void)
{
    return g_beMatCtrlInfo_metaObject[0];
}

void Gap__Bec__beMatCtrl__vfunc_29(beMatCtrl *self, int selector)
{
    beMessenger_RegisterReceiver(self->_messenger, selector, (int)MATCTRL, 0, -1);
}

void FUN_0038b080(int arg0, igIntList *flags, beMatCtrlSearchList *tree, int bit, float *pos, beMatCtrlDataList *cells) {
    int n = tree->_count;
    int i;
    if (n != 0) {
        for (i = 0; i < n; i++) {
            float p = *pos;
            beMatCtrlSearch *b = ((beMatCtrlSearch **)tree->_data)[i];
            if (b->_minX <= p && !(b->_maxX < p)) {
                int slot = b->_matNO;
                if (slot != -1) {
                    if (FUN_0018b630((struct B *)((beMatCtrlData **)cells->_data)[slot]->_chkBox, (struct V *)pos) == 2) {
                        int *arr = (int *)flags->_data;
                        int v = arr[slot];
                        int fc = flags->_count;
                        v |= (1 << bit);
                        if (fc != 0 && slot >= 0 && slot < fc) arr[slot] = v;
                    }
                }
                FUN_0038b080(arg0, flags, (beMatCtrlSearchList *)((beMatCtrlSearch **)tree->_data)[i]->_memberList, bit, pos, cells);
            }
        }
    }
}

int Gap__Bec__beMatCtrl__vfunc_34(beMatCtrl *arg0, beMatCtrlInfoRam *arg1, beMatCtrlInfo *arg2) {
    unsigned int temp_v0;
    beMatCtrlInfo *temp_s0;
    temp_s0 = (beMatCtrlInfo *)arg1->_parentInfo;
    temp_v0 = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0035a6b0(), arg2->_dataList);
    switch (temp_v0) {
    case 0:
        igSwitch_EnableAllChildren(temp_s0->_switchgraph);
        goto L;
    case 1:
        igSwitch_DisableAllChildren(temp_s0->_switchgraph);
        goto L;
    case 2:
        arg0->_isLuaCallDisp = 1;
        goto L;
    case 3:
        arg0->_isLuaCallDisp = 0;
        goto L;
    case 4:
        arg1->_isRun = 0;
        goto L;
    case 5:
        arg1->_isRun = 1;
        goto L;
    default:
        return 0;
    }
L:
    return 1;
}

int Gap__Bec__beMatCtrl__vfunc_20(void)
{
    return g_beMatCtrl_metaObject[0];
}


#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_DispatchSelected(...);
int beMessenger_SelectGroup(...);
int igStrCmp(...);
extern int DAT_004cc6d0[4];
extern int DAT_004cc6e0[4];
extern int DAT_004cc720[4];
extern int DAT_00515950[4];
extern int DAT_00515958[4];
extern int DAT_00515960[4];
extern int DAT_00515968[4];
extern int DAT_00515970[4];
extern int DAT_00515978[4];
extern int DAT_00515980[4];
extern int DAT_00515988[4];
extern int DAT_00586f20[4];
extern float DAT_0058c180[12];
extern char GPR_00554e6c;
}

struct RecoveryString { void *p; RecoveryString() {} RecoveryString(void *q) { p = q; } ~RecoveryString() { if (p != 0) { int *t = (int *)((char *)p - 8); int v = *(int *)((char *)p - 4) - 1; *(int *)((char *)p - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*t, t); } } };
extern "C" RecoveryString StringList_CopyRetained(void *, int);
/* inline igStringRefList set: addref the new string, release the old, store */
struct SetOp { static inline void go(igStringRefList *L, int idx, const RecoveryString &r) { int cnt; int *slot; int *t; int *a1; int c; cnt = L->_count; if (cnt != 0 && idx >= 0 && idx < cnt) { slot = (int *)L->_data + idx; t = (int *)r.p; if (t != 0) t[-1] = t[-1] + 1; t = (int *)(*slot); if (t != 0) { a1 = t - 2; c = t[-1] - 1; t[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); } *slot = (int)r.p; } } };
extern "C" void FUN_003cdef0(beNDMWPanelObject *self, int g, int s, int *name, int val) {
    float v[3];
    int idx;
    int pool;
    int ref;
    int cnt;
    bool x;
    float *p;
    int *slot;
    int *t;

    if (GPR_00554e6c == 0) {
        DAT_0058c180[0] = 0.9f;
        DAT_0058c180[1] = 0.9f;
        DAT_0058c180[2] = 0.9f;
        DAT_0058c180[3] = 0.5f;
        DAT_0058c180[4] = 0.5f;
        DAT_0058c180[5] = 0.7f;
        DAT_0058c180[6] = 1.0f;
        DAT_0058c180[7] = 0.68f;
        DAT_0058c180[8] = 1.0f;
        DAT_0058c180[9] = 0.0f;
        DAT_0058c180[10] = 0.96f;
        DAT_0058c180[11] = 1.0f;
        GPR_00554e6c = 1;
    }
    idx = s + g * 16;
    if (name != 0) {
        if ((t = (int *)StringList_CopyRetained(((igStringRefList *)self->_textSetList), idx).p, x = true, t != 0) && (igStrCmp((int *)StringList_CopyRetained(((igStringRefList *)self->_textSetList), idx).p, name) == 0 ? (x = false, 1) : 0)) {}
        if (x) {
            if (name == 0) {
                ref = 0;
            } else {
                if (DAT_00586f20[0] == 0) {
                    pool = FUN_002eb010(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    DAT_00586f20[0] = pool;
                }
                ref = StringPool_Intern(DAT_00586f20[0], name);
            }
            SetOp::go(((igStringRefList *)self->_textSetList), idx, RecoveryString((void *)ref));
            beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
            beMessenger_AppendString(self->_messenger, name);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00515958[0]);
            if (g == 1) {
                beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
                beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
                beMessenger_AppendString(self->_messenger, &DAT_00515960[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00515968[0]);
            }
            beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
            beMessenger_AppendString(self->_messenger, &DAT_00515970[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00515978[0]);
        }
        slot = (int *)((igIntList *)self->_textColorList)->_data + idx;
        if (val != *slot) {
            cnt = ((igIntList *)self->_textColorList)->_count;
            if (cnt != 0 && idx >= 0 && idx < cnt) {
                *slot = val;
            }
            beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
            p = &DAT_0058c180[val * 3];
            v[0] = p[0]; v[1] = p[1]; v[2] = p[2];
            beMessenger_AppendVec3(self->_messenger, &v[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00515980[0]);
        }
    } else {
        SetOp::go(((igStringRefList *)self->_textSetList), idx, RecoveryString((void *)0));
        cnt = ((igIntList *)self->_textColorList)->_count;
        if (cnt != 0 && idx >= 0 && idx < cnt) {
            *((int *)((igIntList *)self->_textColorList)->_data + idx) = DAT_004cc720[0];
        }
        beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
        beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
        beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
        beMessenger_AppendString(self->_messenger, &DAT_00515988[0]);
        beMessenger_DispatchSelected(self->_messenger, &DAT_00515978[0]);
    }
}

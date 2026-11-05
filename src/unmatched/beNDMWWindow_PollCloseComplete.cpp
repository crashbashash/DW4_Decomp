#pragma opt_dead_assignments off
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringList_CopyRetained(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beMessenger_GetBool(...);
int beMessenger_GetBoolCount(...);
int beMessenger_SendNamed(...);
extern int DAT_00518738[4];
extern int DAT_00518748[4];
extern int DAT_00586f20[4];
int beNDMWWindow_PollCloseComplete(beNDMWWindow *self);
}
struct Clr { static inline void ClearList(igStringRefList *l) {
    int n = l->_count;
    int i;
    int **slot; int *ref; int *old; int pool; int *a1; int c;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = (int *)StringPool_Intern(DAT_00586f20[0], 0);
        old = *slot;
        if (old) { a1 = old - 2; c = old[-1] - 1; old[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        *slot = ref;
    }
    l->_count = 0;
} };
int beNDMWWindow_PollCloseComplete(beNDMWWindow *self) {
    int *sp1;
    int *sp2;
    int *a1;
    int c;
    int i;
    int v;
    int n;
    int *t1;
    int *t2;
    n = ((igStringRefList *)self->_modelCloseInfoNameList)->_count;
    for (i = 0; i < n; i++) {
        StringList_CopyRetained(&sp1, (igStringRefList *)self->_modelCloseInfoNameList, i);
        t1 = sp1;
        if (t1) { a1 = t1 - 2; c = t1[-1] - 1; t1[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        v = ((int *)((igStringRefList *)self->_modelCloseRamNoList)->_data)[i];
        StringList_CopyRetained(&sp2, (igStringRefList *)self->_modelCloseSeqNameList, i);
        t2 = sp2;
        if (t2) { a1 = t2 - 2; c = t2[-1] - 1; t2[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        beMessenger_SendNamed(self->_messenger, DAT_00518738, t1, v, DAT_00518748);
        if (beMessenger_GetBoolCount(self->_messenger) > 0 && beMessenger_GetBool(self->_messenger, 0)) return 0;
    }
    if (((igStringRefList *)self->_subWindow)->_count) return 0;
    Clr::ClearList((igStringRefList *)self->_modelCloseInfoNameList);
    ((igStringRefList *)self->_modelCloseRamNoList)->_count = 0;
    Clr::ClearList((igStringRefList *)self->_modelCloseSeqNameList);
    return 1;
}

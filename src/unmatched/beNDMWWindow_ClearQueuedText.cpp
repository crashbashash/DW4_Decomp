#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringList_CopyRetained(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beNDMWWindow_ClearTextElement(...);
extern int DAT_00586f20[4];
void beNDMWWindow_ClearQueuedText(beNDMWWindow *self);
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
void beNDMWWindow_ClearQueuedText(beNDMWWindow *self) {
    int *sp1;
    int *t2;
    int *sp2;
    int n;
    int *a1;
    int i;
    int *t1;
    int c;
    n = ((igStringRefList *)self->_textCloseTypeList)->_count;
    for (i = 0; i < n; i++) {
        StringList_CopyRetained(&sp1, (igStringRefList *)self->_textCloseTypeList, i);
        t1 = sp1;
        if (t1) { a1 = t1 - 2; c = t1[-1] - 1; t1[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        StringList_CopyRetained(&sp2, (igStringRefList *)self->_textCloseNameList, i);
        t2 = sp2;
        if (t2) { a1 = t2 - 2; c = t2[-1] - 1; t2[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        beNDMWWindow_ClearTextElement(self, t1, t2);
    }
    Clr::ClearList((igStringRefList *)self->_textCloseTypeList);
    Clr::ClearList((igStringRefList *)self->_textCloseNameList);
}

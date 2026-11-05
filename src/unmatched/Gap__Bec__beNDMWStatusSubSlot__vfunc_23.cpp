#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, int);
int beNDMWWindow_ClearQueuedText(beNDMWStatusSubSlot *);
int beNDMWWindow_PlayQueuedModelClose();
int beNDMWWindow_PresentModelAtOrigin(beNDMWStatusSubSlot *, int *, int, int *, int *);
extern int DAT_00519a58[4];
extern int DAT_00519e78[4];
extern int DAT_0051a008[4];
extern int DAT_00586f20[4];

void Gap__Bec__beNDMWStatusSubSlot__vfunc_23(beNDMWStatusSubSlot *w, int arg1)
{
    int *a1;
    int v1;
    int pool;
    int *old;
    igDataList *l;
    int n;
    int i;
    int **slot;
    int *nw;
    int *a12;
    int v12;
    int pool2;
    int *old2;
    igDataList *l2;
    int n2;
    int i2;
    int **slot2;
    int *nw2;

    if (arg1 != 0) {
        beNDMWWindow_PresentModelAtOrigin(w, DAT_00519e78, 0, DAT_0051a008, DAT_00519a58);
        return;
    }
    beNDMWWindow_PlayQueuedModelClose();
    l = (igDataList *)w->_modelCloseInfoNameList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            DAT_00586f20[0] = pool;
        }
        nw = (int *)StringPool_Intern(DAT_00586f20[0], 0);
        old = *slot;
        if (old != 0) {
            a1 = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        *slot = nw;
    }
    l->_count = 0;
    ((igDataList *)w->_modelCloseRamNoList)->_count = 0;
    l2 = (igDataList *)w->_modelCloseSeqNameList;
    n2 = l2->_count;
    for (i2 = 0; i2 < n2; i2++) {
        slot2 = &((int **)l2->_data)[i2];
        if (DAT_00586f20[0] == 0) {
            pool2 = FUN_002eb010(0x10);
            if (pool2 != 0) {
                pool2 = StringPool_Construct(pool2);
            }
            DAT_00586f20[0] = pool2;
        }
        nw2 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
        old2 = *slot2;
        if (old2 != 0) {
            a12 = old2 - 2;
            v12 = old2[-1] - 1;
            old2[-1] = v12;
            if (v12 == 0) {
                StringChunk_ReleaseHeader(*a12, a12);
            }
        }
        *slot2 = nw2;
    }
    l2->_count = 0;
    beNDMWWindow_ClearQueuedText(w);
}
} /* extern "C" */

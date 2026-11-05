#include "dw4/reflected.h"
int StringChunk_ReleaseHeader();
int StringList_CopyRetained();
int igStrCmp();
int FUN_002345b0(igStringRefList *arg0, int *arg1, int arg2, void **arg3) {
    void *sp5C;
    void *sp58;
    int eq;
    int v1;
    if (arg2 != 0) {
        StringList_CopyRetained(&sp5C, arg0, *arg1);
        eq = igStrCmp(sp5C, arg2) == 0;
        if (sp5C != 0) {
            int *a1 = (int *)((char *)sp5C - 8);
            int v0 = *(int *)((char *)sp5C - 4) - 1;
            *(int *)((char *)sp5C - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        if (eq != 0) {
            v1 = *arg1 + 1;
            if (v1 < arg0->_count) {
                *arg1 = v1;
                StringList_CopyRetained(&sp58, arg0, *arg1);
                *arg3 = sp58;
                if (sp58 != 0) {
                    int *a1 = (int *)((char *)sp58 - 8);
                    int v0 = *(int *)((char *)sp58 - 4) - 1;
                    *(int *)((char *)sp58 - 4) = v0;
                    if (v0 == 0) {
                        StringChunk_ReleaseHeader(*a1, a1);
                    }
                }
                v1 = *arg1;
                *arg1 = v1 + 1;
                return 1;
            }
        }
    }
    return 0;
}

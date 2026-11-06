#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int List_Reserve(igStringRefList *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
extern int DAT_00586f20[4];
extern be *DAT_0058a1d8[4]; 
void Gap__Bec__be__vfunc_26(void);
}

/* the Game this pointer */
void Gap__Bec__be__vfunc_26(void) {
    igStringRefList *s5;
    int s4;
    int i;
    int **slot;
    int *s1;
    int off;
    int *old;
    int v;
    s5 = (igStringRefList *)DAT_0058a1d8[0]->_stringRefList;
    s4 = s5->_count;
    i = 0;
    if (0 < s4) {
        off = 0;
        do {
            slot = (int **)((char *)s5->_data + off);
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(0x10);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20[0] = v;
            }
            s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
            old = *slot;
            if (old != 0) {
                int *hdr = old - 2;
                int r = old[-1] - 1;
                old[-1] = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*hdr, hdr);
                }
            }
            i += 1;
            *slot = s1;
            off += 4;
        } while (i < s4);
    }
    s5->_count = 0;
    {
        igStringRefList *l2 = (igStringRefList *)DAT_0058a1d8[0]->_stringRefList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
}

#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int StringChunk_ReleaseHeader(int, int *);
int Memory_FreeBuffer(int);
int FUN_002ed5c0(void *);
extern int DAT_00586f20[4];
}
struct T { unsigned short f0; short pad; unsigned short f4; short pad2; int f8; unsigned short *f12; int f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
extern "C" int FUN_0016ab80(igPsx2VisualContext *, int);
extern "C" void FUN_0016a9f0(igPsx2VisualContext *arg0, int arg1);
void FUN_0016a9f0(igPsx2VisualContext *arg0, int arg1) {
    int s0, s2, v, old;
    int *hd;
    T *t;
    s0 = ((T *)arg0->_pClutList)->f0 - 1;
    for (; s0 > -1; s0--) {
        if (((T *)arg0->_pClutList)->Chk(s0)) {
            FUN_0016ab80(arg0, s0);
        }
    }
    if (arg1 == 0) {
        t = (T *)arg0->_pClutList;
        if (t != 0) {
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(16);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20[0] = v;
            }
            s2 = StringPool_Intern(DAT_00586f20[0], 0);
            old = t->f8;
            if (old != 0) {
                hd = (int *)(old - 8);
                v = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader(*hd, hd);
                }
            }
            t->f8 = s2;
            Memory_FreeBuffer(t->f16);
            Memory_FreeBuffer((int)t->f12);
            if (&t->f8 != 0) {
                old = t->f8;
                if (old != 0) {
                    hd = (int *)(old - 8);
                    v = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = v;
                    if (v == 0) {
                        StringChunk_ReleaseHeader(*hd, hd);
                    }
                }
            }
            FUN_002ed5c0(t);
        }
        arg0->_pClutList = 0;
    }
}

#include "dw4/reflected.h"
/* Sibling of FUN_0016a9f0: the loop adds each unused index through the inlined Add (bounds check
 * and grow through virtual slot 232); inline bool Chk by early returns; alternate compiler. */
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void* v232(void*,int); };
extern "C" {
VM *Memory_FindBufferOwner(void *);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int StringChunk_ReleaseHeader(int, int *);
int Memory_FreeBuffer(int);
int FUN_002ed5c0(void *);
extern int DAT_00586f20[4];
}
struct T { unsigned short f0; unsigned short f2; unsigned short f4; short pad2; int f8; unsigned short *f12; int f16;
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
    void Add(int s0) {
        if (s0 < f0 && s0 >= 0) {
            if (f4 >= f2) {
                VM *o = Memory_FindBufferOwner(this);
                f2 = f2 + 8;
                f12 = (unsigned short *)o->v232(f12, f2 * 2);
            }
            f12[f4] = s0;
            f4 = f4 + 1;
        }
    }
};
/* matching construct: _pBufList is a 4-byte reference field; the cast gives the typed T view (no layout effect) */
extern "C" void FUN_00169260(igPsx2VisualContext *arg0, int arg1);
void FUN_00169260(igPsx2VisualContext *arg0, int arg1) {
    int s0, s2, v, old;
    int *hd;
    T *t;
    s0 = ((T *)arg0->_pBufList)->f0 - 1;
    for (; s0 > -1; s0--) {
        if (((T *)arg0->_pBufList)->Chk(s0)) {
            ((T *)arg0->_pBufList)->Add(s0);
        }
    }
    if (arg1 == 0) {
        t = ((T *)arg0->_pBufList);
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
        arg0->_pBufList = 0;
    }
    arg0->_currentBuf = -1;
}

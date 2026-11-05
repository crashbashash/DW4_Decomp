#include "dw4/reflected.h"
extern "C" {
int strcpy(int, int);
int strlen(int);
int FUN_0032e130(void *, int, int **);
int StringChunk_ReleaseHeader(int, int *);
extern char DAT_004fb410[];
extern int DAT_004fb418[4];
void FUN_0032e4d0(int *arg0, igPsx2Media *arg1, int arg2, int **arg3, unsigned int arg4);
}
struct R { int a; R() {} R(int x) { a = x; } };
extern "C" R FUN_0032d6d0(int, int, int, int, int *, int, int);
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R v124(); virtual void d30(); virtual R v132(int); };

struct Ent { int f0; unsigned int f4; int f8; };
void FUN_0032e4d0(int *arg0, igPsx2Media *arg1, int arg2, int **arg3, unsigned int arg4)
{
    int *s2p;
    int a0;
    int *a1;
    Ent *e;
    int s5;
    int s0;
    int t;
    int *p;

    R sp7C = ((V *)arg1->_sema)->v132(1);
    int *sp78;
    e = (Ent *)(*(char **)((char *)arg1->_handlePool + 12) + arg2 * 12);
    sp78 = *arg3;
    if (sp78 != 0) {
        sp78[-1] = sp78[-1] + 1;
    }
    FUN_0032e130((void *)arg1, arg2, &sp78);
    if (sp78 != 0) {
        a1 = sp78 - 2;
        t = sp78[-1] - 1;
        sp78[-1] = t;
        if (t == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    e->f4 = arg4;
    s0 = e->f0;
    t = strlen(s0) + 5;
    s5 = (t + 15) & -16;
    s2p = (int *)((char *)arg1->_commandBuffer + 16);
    a0 = 1;
    switch (e->f4) {
    case 0:
    case 4:
    case 8:
        break;
    case 1:
    case 5:
        a0 = 0x602;
        break;
    case 2:
    case 6:
        a0 = 0x302;
        break;
    case 3:
    case 7:
        a0 = 0x203;
        break;
    }
    *s2p = a0;
    strcpy((int)(s2p + 1), s0);
    {
        int *q = (int *)arg1->_commandBuffer;
        R sp74 = FUN_0032d6d0(arg1->_connection, 2, (int)s2p, s5, q, 16, 1);
        s0 = *q;
        e->f8 = s0;
    }
    R sp70 = ((V *)arg1->_sema)->v124();
    if (s0 < 0) {
        p = DAT_004fb418;
    } else {
        p = (int *)DAT_004fb410;
    }
    *arg0 = *p;
}

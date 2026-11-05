int FUN_001b1490();
int List_Resize();
typedef struct Ls { char p0[8]; volatile int cnt; int cap; int *data; int f20; int f24; } Ls;
typedef struct Tb { char p0[16]; Ls **data; } Tb;
typedef struct A { char p0[8]; short s8; short s10; } A;
typedef struct O { char p0[16]; Tb *f16; char p1[48]; int *f68; } O;
void FUN_001b12f0(O *arg0, A *arg1) {
    A *volatile sp5C;
    int s2;
    Ls *s1;
    int s0;
    A *t;
    s0 = arg1->s10 + arg0->f68[arg1->s8];
    s1 = arg0->f16->data[s0];
    if (s1->f24 < 0) {
        s1->f24 = s1->cnt;
    }
    sp5C = arg1;
    s2 = s1->cnt;
    if (s2 < s1->cap) {
        s1->cnt = s1->cnt + 1;
    } else {
        List_Resize(s1, s2 + 1, 4);
    }
    t = sp5C;
    s1->data[s2] = (int)t;
    FUN_001b1490(arg0, s1, s0, t);
}

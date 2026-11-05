int List_Resize();
typedef struct Ls { char p0[8]; int cnt; int cap; int *data; } Ls;
typedef struct Ob { char p0[8]; int cnt; int cap; int *data; int f20; int f24; int f28; char f32; char q[3]; int f36; } Ob;
typedef struct Tb { char p0[16]; Ob **data; } Tb;
typedef struct A { char p0[16]; Tb *f16; char q0[4]; Ls *f24; char p1[16]; Ls *f44; char p2[12]; unsigned char f60; } A;
#define SETCNT(l, n) if ((n) >= 0) { if ((n) <= (l)->cap) (l)->cnt = (n); else List_Resize((l), (n), 4); }
void FUN_001b0250(A *arg0, Ls *arg1) {
/*D*/
    Ls *ixl;
    int *a2;
    int s1;
    int s5;
    int c;
    int v;
    int s0;
    int *ix;
    Ob *o;
    Tb *tbl;
    Ob **tb;
    int k;
    int s4;
    int *src;
    int i;
/*E*/
    s4 = arg1->cnt;
    s0 = 0;
    s1 = arg0->f24->cnt;
    k = s1 + s4;
    if (arg0->f60 == 0) {
        SETCNT(arg1, k);
        a2 = arg1->data + s4;
    } else {
        s5 = arg0->f44->cnt;
        k = k + s5;
        SETCNT(arg1, k);
        a2 = arg1->data + s4;
        src = (int *)arg0->f44;
        src = ((Ls *)src)->data;
        for (; s0 < s5; s0++) a2[s0] = src[s0];
        arg0->f44->cnt = 0;
    }
    ixl = arg0->f24;
    ix = ixl->data;
    tbl = arg0->f16;
    tb = tbl->data;
    for (i = 0; i < s1; i++) {
        o = tb[ix[i]];
        if (o->f24 >= 0) v = o->data[o->f24];
        else if ((c = o->cnt) != 0) { c = c - 1; v = *(int *)((char *)o->data + c * 4); }
        else v = o->f20;
        o->f32 = 0;
        if (v != o->f36) { a2[s0++] = v; o->f36 = v; }
    }
    k = s0 + s4;
    SETCNT(arg1, k);
    arg0->f24->cnt = 0;
}

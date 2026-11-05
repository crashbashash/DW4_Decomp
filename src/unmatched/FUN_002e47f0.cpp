struct R { char p0[16]; int f16; int f20; char p1[4]; int f28; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual R *vX(); };
struct T { char p[8]; O **data; int cnt; };
class W { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
struct S { char p0[136]; int f136; int f140; char p1[24]; unsigned char f168; char p2[15]; int f184; char p3[16]; W *f204; char p4[72]; A *f280; };
extern "C" {
T *FUN_002fc250(...);
int strlen(...);
int strcpy(...);
extern int DAT_004fb410[4];
void FUN_002e47f0(int *arg0, S *arg1);
}
void FUN_002e47f0(int *arg0, S *arg1) {
/*D*/
    int i;
    int j;
    int s5;
    int *s4;
    int s2;
    O *p;
/*E*/
    arg1->f136 = FUN_002fc250()->cnt;
    arg1->f140 = arg1->f136 * 12;
    for (i = 0; i < arg1->f136; i++) {
        arg1->f140 = arg1->f140 + (strlen(FUN_002fc250()->data[i]->vX()->f28) + 1);
    }
    arg1->f184 = arg1->f280->vX(arg1->f140, 16);
    s5 = 0;
    s4 = (int *)arg1->f184;
    for (i = 0; i < arg1->f136; i++) {
        p = FUN_002fc250()->data[i];
        s4[s5] = strlen(p->vX()->f28) + 1;
        s5++;
        s4[s5] = p->vX()->f16;
        s5++;
        s4[s5] = p->vX()->f20;
        s5++;
    }
    s2 = arg1->f184 + arg1->f136 * 12;
    for (j = 0; j < arg1->f136; j++) {
        strcpy(s2, FUN_002fc250()->data[j]->vX()->f28);
        s2 += *(int *)(arg1->f184 + j * 12);
    }
    if (arg1->f168 != 0) arg1->f204->vX(arg1->f184, arg1->f136 * 3);
    *arg0 = DAT_004fb410[0];
}

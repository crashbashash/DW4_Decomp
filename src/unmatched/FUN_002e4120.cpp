extern "C" {
int memcpy(void *, int, int);
int strlen(int);
int FUN_002f8960(int);
extern int DAT_004fb410[4];
struct S;
void FUN_002e4120(int *arg0, S *arg1);
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int *v52(int); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void v50(int *, int); };
struct S { char p0[168]; unsigned char f168; char p1[35]; B *f204; char p2[72]; A *f280; char p3[12]; int f296; int *f300; };
void FUN_002e4120(int *arg0, S *o) {
    int i; int s; int j; char *p; int n; int a;
    o->f296 = 8;
    i = 0;
    do {
        a = strlen(FUN_002f8960(i)) + 1;
        i++;
        o->f296 = o->f296 + a;
    } while (i < 46);
    o->f300 = o->f280->v52(o->f296);
    j = 0;
    p = (char *)o->f300;
    ((int *)p)[0] = o->f296;
    ((int *)p)[1] = 46;
    p += 8;
    do {
        s = FUN_002f8960(j);
        n = strlen(s) + 1;
        memcpy(p, s, n);
        j++;
        p += n;
    } while (j < 46);
    if (o->f168) o->f204->v50(o->f300, 2);
    *arg0 = DAT_004fb410[0];
}

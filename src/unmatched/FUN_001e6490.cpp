extern "C" {
void *igMetaObject_FindFieldByName(int, void *);
int igObject_Destroy(void *);
int FUN_002fe290(int, int);
extern int DAT_004e4aa0[4];
extern void *DAT_00562c60[4];
extern int DAT_00585cc8[4];
}
struct Rc { int w0; int refs; int f8; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int v88(); };
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual Rc *v92(); virtual void v96(int); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int v88(); virtual void v92(); virtual void v96(int, int); };
struct Fd { int w0, w4; int f8; };
struct S { char pad[8]; int f8; VB *f12; char pad2[8]; VA *f24; };
extern "C" int FUN_001e6490(S *arg0, int arg1);
typedef void (*Fn)(int);
int FUN_001e6490(S *arg0, int arg1) {
    Rc * volatile sp4C;
    int s2;
    Rc *t;
    Fn fn;
    sp4C = arg0->f24->v92();
    t = sp4C;
    if (t != 0) {
        t->refs = t->refs + 1;
    }
    s2 = arg0->f12->v88();
    if (((FUN_002fe290(((VC *)(Rc *)sp4C)->v88(), s2) != 0) ^ 1) != 0) {
        t = sp4C;
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(t);
            }
        }
        return 0;
    }
    arg0->f24->v96(arg1);
    arg0->f12->v96(arg0->f8, (int)arg0->f24 + sp4C->f8);
    if (DAT_00562c60[0] == 0) {
        DAT_00562c60[0] = igMetaObject_FindFieldByName(DAT_00585cc8[0], &DAT_004e4aa0[0]);
    }
    fn = *(Fn *)((char *)arg0->f12 + ((Fd *)DAT_00562c60[0])->f8);
    if (fn != 0) {
        fn(arg0->f8);
    }
    t = sp4C;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    return 1;
}

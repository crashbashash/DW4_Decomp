extern "C" { int memcpy(int, int, int); int FUN_00158480(void *); }
class B {
public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); 
 virtual void v26(int); virtual void v27(int); virtual void v28(int); virtual void v29(); virtual void v30(int);
};
class C : public B {
public:
 int p[11];
 int f48, f52; char pad[4]; char f60;
};
extern "C" void FUN_0015a420(C *o, int a1, int a2, int a3, int a4, int a5) {
    o->v28(a2); o->v26(a4); o->v27(a5); o->v30(a3);
    if (a1 != o->f52) { o->v29(); int y = *(volatile int *)&o->f48; int x = *(volatile int *)&o->f52; memcpy(x, a1, y); } else { o->f60 = 1; FUN_00158480(o); }
}

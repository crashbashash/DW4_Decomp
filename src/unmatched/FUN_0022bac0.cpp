extern "C" {
int FUN_001d6340(void *, void *);
void igObject_Destroy(void *);
int FUN_0022bac0(void *arg0, void *arg1);
}
struct RT { int word0; int references;
    static void rel(RT *o) {
        if (o) {
            --o->references;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) igObject_Destroy(o);
        }
    }
};
class C132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(RT *); };
class C112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(RT **); };
struct Arg0 { char pad[20]; RT *ref; };
int FUN_0022bac0(void *arg0, void *arg1) {
    RT *r = ((Arg0 *)arg0)->ref;
    int res;
    if (r) ++r->references;
    if (((C132 *)arg1)->vX(r) != 0) {
        res = ((C112 *)arg1)->vX(&r) & 0xff;
        FUN_001d6340(arg0, r);
        RT::rel(r);
        return res;
    }
    RT::rel(r);
    return 0;
}

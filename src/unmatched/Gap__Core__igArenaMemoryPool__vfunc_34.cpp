struct R { int w; };
extern "C" {
void *FUN_002ba650(...);
int igArenaMemoryPool_SetPoolOptionFlags(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
}
extern int DAT_004fb410[4];
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual R v21(); virtual R v22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();  virtual R v31(int); int rc; };
struct P {
    char p[120]; C *f120; char q[68]; int f192;
    inline void relp() { C *x = f120; if (x) { x->rc = x->rc - 1; if (((unsigned long long)((long long)x->rc << 0x29) >> 0x29) == 0) igObject_Destroy(x); } }
};
struct Ref {
    C *o;
    ~Ref() {
        C *object = o;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_34(int *ret, P *p, int flag) {
    int fl;
    if (flag != 0) {
        fl = p->f192 | 8;
    } else {
        fl = p->f192 & ~8;
    }
    igArenaMemoryPool_SetPoolOptionFlags(p, fl);
    if ((unsigned char)flag == 0) {
        Ref a;
        a.o = p->f120;
        if (a.o) a.o->rc = a.o->rc + 1;
        p->relp();
        p->f120 = 0;
        if (a.o != 0) {
            a.o->v31(1);
            a.o->v22();
        }
    } else if ((unsigned char)flag == 1) {
        if (p->f120 != 0) { *ret = DAT_004fb410[0]; return; }
        Ref b;
        b.o = (C *)FUN_002ba650(igObject_GetAllocator(p));
        b.o->v21();
        C *t = b.o;
        if (t) t->rc = t->rc + 1;
        p->relp();
        p->f120 = t;
    }
    *ret = DAT_004fb410[0];
}

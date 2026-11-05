extern "C" {
int igObject_Destroy(...);
int igObject_GetAllocator(...);
}
struct S4 { int a; };
class T { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); 
    virtual S4 v21();
    virtual S4 v22();
    int references;
};
extern "C" T *FUN_002ba650(...);
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct A { char p[8]; T *m8; };
extern "C" void FUN_002dcaa0(A *arg0, int arg1);
void FUN_002dcaa0(A *arg0, int arg1) {
    T * volatile sp3C;
    T * volatile sp38;
    T *s0;
    if (arg1 != 0) {
        if (arg0->m8 == 0) {
            sp3C = FUN_002ba650(igObject_GetAllocator(arg0));
            sp3C->v21();
            s0 = sp3C;
            if (s0 != 0) s0->references++;
            Rel::go(arg0->m8);
            arg0->m8 = s0;
            Rel::go(s0 = sp3C);
        }
    } else {
        if (arg0->m8 != 0) {
            sp38 = arg0->m8;
            { T *t = sp38; if (t != 0) t->references++; }
            Rel::go(arg0->m8);
            arg0->m8 = 0;
            { T *t = sp38; if (t != 0) t->v22(); }
            { T *t = sp38; Rel::go(t); }
        }
    }
}

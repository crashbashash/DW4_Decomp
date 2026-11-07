extern "C" {
typedef struct R { int pad0; int refs; struct R *f8; } R;
typedef struct O { char pad[32]; R *f32; R *f36; char pad2[20]; R *f60; } O;
int igObject_Destroy(R *);
void *igObject_GetAllocator(O *);
R *FUN_00130020(void *);
R *FUN_00137ab0(void *);
R *FUN_00149c30(void *);
R *FUN_0014f2c0(void *);
int FUN_001b6f30(O *, R *, R *);
}
#define REL(x) do { R *r_ = (x); if (r_ != 0) { r_->refs = r_->refs - 1; if (((unsigned long long) ((long long) r_->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(r_); } } } while (0)
extern "C" void Gap__Sg__igCommonTraversal__vfunc_28(O *arg0, R *arg1) {
    R *volatile sp4C;
    R *volatile sp48;
    void *a;
    bool var_s1;
    R *t;

    if (arg1) { arg1->refs += 1; }
    t = arg0->f60;
    if (t != 0) { t->refs -= 1; if (0 == ((unsigned long long) ((long long) t->refs << 0x29) >> 0x29)) { igObject_Destroy(t); } }
    arg0->f60 = arg1;
    var_s1 = 0;
    if (arg1 == 0) {
        a = igObject_GetAllocator(arg0);
        t = arg0->f36;
        if (t != 0) { t->refs = t->refs - 1; if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(t); } }
        arg0->f36 = FUN_00137ab0(a);
        a = igObject_GetAllocator(arg0);
        t = arg0->f32;
        if (t != 0) { t->refs = t->refs - 1; if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(t); } }
        arg0->f32 = FUN_0014f2c0(a);
        var_s1 = 1;
    } else {
        if (arg0->f36 == 0) {
            sp4C = FUN_00130020(igObject_GetAllocator(arg0));
            t = sp4C;
            if (arg1 != 0) { arg1->refs = arg1->refs + 1; }
            { R *u = t->f8; if (u != 0) { u->refs -= 1; if (((unsigned long long) ((long long) u->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(u); } } }
            t->f8 = arg1;
            t = sp4C;
            if (t != 0) { t->refs = t->refs + 1; }
            { R *u = arg0->f36; if (u != 0) { u->refs = u->refs - 1; if (((unsigned long long) ((long long) u->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(u); } } }
            arg0->f36 = t;
            t = sp4C;
            var_s1 = 1;
            if (0 != t) { t->refs -= 1; if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(t); } }
        }
        if (arg0->f32 == 0) {
            sp48 = FUN_00149c30(igObject_GetAllocator(arg0));
            t = sp48;
            if (arg1 != 0) { arg1->refs = arg1->refs + 1; }
            { R *u = t->f8; if (u) { u->refs = u->refs - 1; if (((unsigned long long) ((long long) u->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(u); } } }
            t->f8 = arg1;
            t = sp48;
            if (0 != t) { t->refs = t->refs + 1; }
            { R *u = arg0->f32; if (u) { u->refs -= 1; if (((unsigned long long) ((long long) u->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(u); } } }
            arg0->f32 = t;
            var_s1 = 1;
            t = sp48;
            if (0 != t) { t->refs -= 1; if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(t); } }
        }
    }
    if (var_s1) {
        FUN_001b6f30(arg0, arg0->f36, arg0->f32);
    }
}

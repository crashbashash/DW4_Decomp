extern "C" {
struct T { int word0; int references; float f[8]; };
void igObject_Destroy(T *);
T *FUN_002332b0(...);
int FUN_00237ea0(...);
int igObject_GetAllocator(...);
extern float DAT_004e0fa0[4];
extern float DAT_004e0fa4[4];
}
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct O8 { char p[40]; int f40; };
struct O { char p[8]; O8 *f8; };
extern "C" int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(O *arg0, int arg1, int arg2);
int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(O *arg0, int arg1, int arg2) {
    T * volatile sp4C;
    T *t;
    sp4C = FUN_002332b0(igObject_GetAllocator());
    t = sp4C;
    t->f[0] = DAT_004e0fa0[0];
    t->f[1] = DAT_004e0fa4[0];
    t = sp4C;
    t->f[2] = (float)arg1;
    t->f[3] = (float)arg2;
    FUN_00237ea0(arg0->f8->f40, sp4C);
    Rel::go(t = sp4C);
    return 0;
}

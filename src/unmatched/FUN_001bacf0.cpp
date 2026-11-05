extern "C" {
int FUN_001904f0(...);
int FUN_001b1030(...);
int FUN_001b11b0(...);
int FUN_001dca40(...);
int FUN_001e07a0(...);
extern int DAT_0055efe8[4];
int FUN_001356b0();
}
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v(char *); };
struct Pool { int p0; int p4; int cap; int pc; V **data; int idx; };
struct Arr { int p0; int p4; int count; int pc; int *data; };
struct Q { char pad[52]; int f52; char pad2[16]; Pool *f72; char pad3[172]; Arr *f248; };
struct R { char pad[32]; int f32; };
extern "C" int FUN_001bacf0(Q *arg0, R *arg1);
int FUN_001bacf0(Q *arg0, R *arg1) {
    char buf[64];
    Pool *pool = arg0->f72;
    int x = arg0->f52;
    V *obj;
    Arr *a;
    int cnt;
    int idx;
    int base;
    int r;
    if (pool->idx >= pool->cap) {
        FUN_001dca40(pool, FUN_001356b0);
    }
    idx = pool->idx;
    pool->idx = idx + 1;
    a = arg0->f248;
    obj = pool->data[idx];
    cnt = a->count;
    idx = arg1->f32;
    if (cnt > 0) {
        int last = cnt - 1; base = a->data[last];
    } else {
        base = 0;
    }
    if (base == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    FUN_001904f0(buf, base + (idx << 6), base);
    obj->v(buf);
    FUN_001b1030(x, obj);
    r = FUN_001e07a0(arg0, arg1);
    FUN_001b11b0(x, DAT_0055efe8[0]);
    if (r == 2) {
        return 2;
    }
    return 0;
}

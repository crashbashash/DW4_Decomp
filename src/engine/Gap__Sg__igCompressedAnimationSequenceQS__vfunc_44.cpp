struct Lst { int w0; int references; int count; int cap; int *data; };
struct T { char pad0[8]; Lst *f8; Lst *f12; Lst *f16; float f20; float f24; float f28; float f32; char pad36[4]; long long f40; int f48; int f52; unsigned char f56; unsigned char f57; unsigned char f58; };
struct Src { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int v156(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void *v172(); virtual void d42(); virtual void d43(); virtual void *v184(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual int v224(int); virtual void d55(); virtual void d56(); virtual int v236(int); virtual int v240(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual long long v260(); char pad[32]; int f36;};
extern "C" {
int FUN_001bf400(T *, int, int);
int FUN_001e5f00(void *, int *, float *, float *);
int FUN_001e6130(void *, int *, float *, float *);
Lst *FUN_002c9ff0(int);
int List_Reserve(Lst *, int, int);
int List_Resize(Lst *, int, int);
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_44(T *arg0, Src *arg1);
}
void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_44(T *arg0, Src *arg1) {
    float sp7C;
    float sp78;
    int n = arg1->v156();
    unsigned char fl = arg1->v240();
    int s0;
    int s5;
    int al;
    Lst *old;
    Lst *l;
    sp7C = 0.0f;
    sp78 = 0.0f;
    arg0->f40 = arg1->v260();
    s0 = fl & 0xFF;
    s5 = s0 & 1;
    arg0->f48 = arg1->f36;
    arg0->f56 = fl;
    if (s5 != 0) arg0->f57 = arg1->v236(1);
    s0 = s0 & 2;
    if (s0 != 0) arg0->f58 = arg1->v236(2);
    if (s5 != 0) {
        if (arg0->f8 == 0) {
            al = igObject_GetAllocator(arg0);
            old = arg0->f8;
            if (old != 0) {
                old->references = old->references - 1;
                if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) igObject_Destroy(old);
            }
            arg0->f8 = FUN_002c9ff0(al);
        }
        int c = n * 3;
        l = arg0->f8;
        if (c >= 0) {
            if (c <= l->cap) l->count = c;
            else List_Resize(l, c, 2);
        }
        l = arg0->f8;
        c = l->count;
        if (c < l->cap) List_Reserve(l, c, 2);
        FUN_001e5f00(arg1->v172(), arg0->f8->data, &sp7C, &sp78);
        arg0->f20 = sp7C;
        arg0->f24 = 1.52590219e-05f * sp78;
    }
    if (s0 != 0) {
        if (arg0->f12 == 0) {
            al = igObject_GetAllocator(arg0);
            old = arg0->f12;
            if (old != 0) {
                old->references = old->references - 1;
                if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) igObject_Destroy(old);
            }
            arg0->f12 = FUN_002c9ff0(al);
        }
        int c = n * 4;
        l = arg0->f12;
        if (c >= 0) {
            if (c <= l->cap) l->count = c;
            else List_Resize(l, c, 2);
        }
        l = arg0->f12;
        c = l->count;
        if (c < l->cap) List_Reserve(l, c, 2);
        FUN_001e6130(arg1->v184(), arg0->f12->data, &sp7C, &sp78);
        arg0->f28 = sp7C;
        arg0->f32 = 1.52590219e-05f * sp78;
    }
    if (arg0->f16 == 0) {
        al = igObject_GetAllocator(arg0);
        old = arg0->f16;
        if (old != 0) {
            old->references = old->references - 1;
            if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) igObject_Destroy(old);
        }
        arg0->f16 = FUN_002c9ff0(al);
    }
    l = arg0->f16;
    if (n >= 0) {
        if (n <= l->cap) l->count = n;
        else List_Resize(l, n, 2);
    }
    l = arg0->f16;
    int c = l->count;
    if (c < l->cap) { List_Reserve(l, c, 2); }
    for (s0 = 0; s0 < n; s0++) FUN_001bf400(arg0, s0, arg1->v224(s0));
}

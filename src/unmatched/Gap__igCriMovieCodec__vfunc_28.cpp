extern "C" {
typedef struct { char pad[32]; unsigned int f20; unsigned int f24; } A;
typedef struct { char pad[4]; int f4; } R;
int FUN_002ed2b0(unsigned int, int, int);
int igObject_IsKindOf(R *, int);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(R *);
int igObject_GetAllocator();
extern int DAT_0055ff88[4];
extern int DAT_00587108[4];
extern int DAT_005878c0[4];
extern void * DAT_005878d8[4];
extern unsigned char GPR_00554c14;

int Gap__igCriMovieCodec__vfunc_28(int arg0, A *arg1, void **arg2) {
    int var_v0;
    int w;
    unsigned int temp_s2;
    unsigned int temp_s1;
    R *a;
    R *var_s0;
    R *d;

    temp_s2 = arg1->f20 >> 4;
    temp_s1 = arg1->f24 >> 4;
    var_v0 = igObject_GetAllocator();
    if (GPR_00554c14 != 0) {
        w = var_v0;
    } else {
        w = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    DAT_005878c0[0] = FUN_002ed2b0(((unsigned int) ((((temp_s2 * temp_s1 * 6) + 0xA) * 4) + 0x3F) >> 6) << 8, 0x40, w);
    a = (R *)(*arg2);
    if ((a != 0) && (igObject_IsKindOf(a, DAT_0055ff88[0]) != 0)) {
        var_s0 = a;
    } else {
        var_s0 = 0;
    }
    if (var_s0 != 0) {
        var_s0->f4 = var_s0->f4 + 1;
    }
    d = (R *)DAT_005878d8[0];
    if (d != 0) {
        d->f4 = d->f4 - 1;
        if (((unsigned long long) ((long long) d->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(d);
        }
    }
    DAT_005878d8[0] = (void *)(var_s0);
    return 1;
}
}

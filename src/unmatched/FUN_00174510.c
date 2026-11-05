/* 0x00174510 - 292 bytes. Per-slot change counters; clamp spelled as if/else, the call forwards arg0/arg3 (m2c had shifted the arguments), index arithmetic kept as off = n*4 plus a second n*4 inside the block. */
struct R { char pad[1036]; int a[16]; int b[16]; int c[16]; };
int FUN_00174640();
extern int DAT_00560928[8];
extern int DAT_00560948[8];
extern int DAT_00560968[8];
extern int DAT_00569330[4];
extern int DAT_00569340[4];
extern int * DAT_0056ad80[4];
void FUN_00174510(struct R *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    int n;
    int j;
    int off;
    char *p;
    if (arg4 < 15) {
        n = arg4;
    } else {
        n = 15;
    }
    off = n * 4;
    if (n < 8) {
        if (arg0->a[n] == arg1) {
            DAT_00560928[n] += 1;
        }
        if (arg0->b[n] == arg2) {
            DAT_00560968[n] += 1;
        }
        if (arg0->c[n] == (arg3 & 0xFF)) {
            DAT_00560948[n] += 1;
        }
    }
    off = n * 4;
    p = (char *)(off + (int)arg0);
    *(int *)(p + 1036) = arg1;
    *(int *)(p + 1100) = arg2;
    *(int *)(p + 1164) = arg3 & 0xFF;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    DAT_00569330[0] = n;
    DAT_0056ad80[0] = &DAT_00569340[j * 112];
    FUN_00174640(arg0, n, j, arg3);
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}

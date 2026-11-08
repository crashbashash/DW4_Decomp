typedef struct { char pad[16]; int f16; char pad2[8]; int n; int f32; } G;
extern G D_005855b0;
extern int D_005855d8[2];
extern int D_005855e0[16];
int FUN_002a7968(void) {
    int i;
    if ((unsigned)(D_005855b0.n - 1) >= 16) {
fail:
        return -1;
    }
    if (D_005855b0.f16 == 0 || D_005855b0.f32 == 0) {
        for (i = 0; i < 2; i++) {
            if (D_005855d8[i] == 0) goto fail;
        }
        for (i = 0; i < D_005855b0.n; i++) {
            if (D_005855e0[i] == 0) goto fail;
        }
    }
    return 0;
}

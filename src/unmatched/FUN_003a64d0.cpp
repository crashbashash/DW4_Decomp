typedef struct T { char p[8]; int f8; } T;
typedef struct O { char p[24]; T *f24; } O;
extern "C" {
int FUN_003a5b40(O *, T *, int, int *, int *);
int FUN_003a5cc0(O *, T *, int, float *, int *, int *, int *);
int FUN_003a5d70(O *, T *, int, float *, int *, int *, int *);
extern int DAT_0050ffe8[4];
extern int DAT_0050fff0[4];
extern int DAT_0058a5e0[4];
extern int DAT_0058a5f0[4];
extern int DAT_0058a5f8[4];
int FUN_003a64d0(O *arg0, float *arg1, int arg2);
}
int FUN_003a64d0(O *arg0, float *arg1, int arg2) {
    float va[4];
    float vb[4];
    if (arg0->f24->f8 == 0) {
        FUN_003a5b40(arg0, arg0->f24, 0, &DAT_0050ffe8[0], &DAT_0050fff0[0]);
        if (arg0->f24->f8 == 0) {
            return 0;
        }
    }
    if (arg2 != 0) {
        va[0] = arg1[0];
        va[1] = arg1[1];
        va[2] = arg1[2];
        FUN_003a5cc0(arg0, arg0->f24, 0, va, &DAT_0058a5e0[0], &DAT_0058a5f0[0], &DAT_0058a5f8[0]);
    } else {
        vb[0] = arg1[0];
        vb[1] = arg1[1];
        vb[2] = arg1[2];
        FUN_003a5d70(arg0, arg0->f24, 0, vb, &DAT_0058a5e0[0], &DAT_0058a5f0[0], &DAT_0058a5f8[0]);
    }
    return 1;
}

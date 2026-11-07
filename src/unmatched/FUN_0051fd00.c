int FUN_00100c20();
extern int DAT_0055f4a8[4];
extern void * DAT_0055f4b8[4];
extern int DAT_0055f4c8[4];
extern void * DAT_0055f4d8[4];
extern int DAT_0055f4e0[4];
extern void * DAT_0055f4f0[4];
extern int DAT_0055f4f8[4];
extern void * DAT_0055f508[4];
extern int DAT_0055f528[4];
extern void * DAT_0055f538[4];
int FUN_00142d10();
int FUN_00142d90();
int FUN_00142e10();
int FUN_00142e90();

void FUN_0051fd00(void) {
    DAT_0055f4b8[0] = (void *)(0);
    if (DAT_0055f4b8[0] != 0) {
        *(int *)((char *)(DAT_0055f4b8[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_0055f4b8[0]) + 4) + 1));
    }
    FUN_00100c20(&DAT_0055f4b8[0], &FUN_00142e90, &DAT_0055f4a8[0]);
    DAT_0055f4d8[0] = (void *)(0);
    if (DAT_0055f4d8[0] != 0) {
        *(int *)((char *)(DAT_0055f4d8[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_0055f4d8[0]) + 4) + 1));
    }
    FUN_00100c20(&DAT_0055f4d8[0], &FUN_00142e10, &DAT_0055f4c8[0]);
    DAT_0055f4f0[0] = (void *)(0);
    if (DAT_0055f4f0[0] != 0) {
        *(int *)((char *)(DAT_0055f4f0[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_0055f4f0[0]) + 4) + 1));
    }
    FUN_00100c20(&DAT_0055f4f0[0], &FUN_00142d90, &DAT_0055f4e0[0]);
    DAT_0055f508[0] = (void *)(0);
    if (DAT_0055f508[0] != 0) {
        *(int *)((char *)(DAT_0055f508[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_0055f508[0]) + 4) + 1));
    }
    FUN_00100c20(&DAT_0055f508[0], &FUN_00142d10, &DAT_0055f4f8[0]);
    DAT_0055f538[0] = (void *)(0);
    if (DAT_0055f538[0] != 0) {
        *(int *)((char *)(DAT_0055f538[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_0055f538[0]) + 4) + 1));
    }
    FUN_00100c20(&DAT_0055f538[0], &FUN_00142e10, &DAT_0055f528[0]);
}

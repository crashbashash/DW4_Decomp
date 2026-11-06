extern "C" {
int FUN_00100c20(void **, int (*)(), int *);
extern int DAT_005875d0[4];
extern void * DAT_005875e0[4];
extern int DAT_005875f8[4];
extern void * DAT_00587608[4];
extern int DAT_00587610[4];
extern void * DAT_00587620[4];
int FUN_001489a0();
int ObjectRef_Destruct_001c6460();
int FUN_00333760();

void FUN_00521600(void) {
    DAT_005875e0[0] = (void *)(0);
    if (DAT_005875e0[0] != 0) {
        *(int *)((char *)(DAT_005875e0[0]) + 4) = (int)((int) (*(int *)((char *)(DAT_005875e0[0]) + 4) + 1));
    }
    FUN_00100c20(&DAT_005875e0[0], &FUN_001489a0, &DAT_005875d0[0]);
    DAT_00587608[0] = (void *)(0);
    FUN_00100c20(&DAT_00587608[0], &ObjectRef_Destruct_001c6460, &DAT_005875f8[0]);
    DAT_00587620[0] = (void *)(0);
    FUN_00100c20(&DAT_00587620[0], &FUN_00333760, &DAT_00587610[0]);
}
}

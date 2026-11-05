extern int DAT_00587058[4];
int FUN_002b9500();
int FUN_002c8450();
int Memory_GetAllocatorBySelector();
extern int DAT_005305e8[4];
extern int DAT_00530618[4];
extern int DAT_00587028[4];
extern int DAT_00587048[4];
extern unsigned char GPR_00554c14;

void *FUN_002dc490(void *arg0, int arg1) {
    int var_v0;

    *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
    *(int *)((char *)(arg0) + 0) = 0;
    *(int *)((char *)(arg0) + 4) = (int)(&DAT_005305e8[0]);
    *(int *)((char *)(arg0) + 8) = arg1;
    *(int *)((char *)(arg0) + 20) = 0;
    *(int *)((char *)(arg0) + 24) = 0;
    *(int *)((char *)(arg0) + 12) = FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    if (GPR_00554c14 != 0) {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587058[0]);
    }
    *(int *)((char *)(arg0) + 16) = FUN_002c8450(var_v0);
    return arg0;
}

int FUN_002c5e10();
int Memory_GetAllocatorBySelector();
extern unsigned char DAT_00554bfc[4];
extern int DAT_00586590[4];
extern int DAT_00586df8[4];
extern int DAT_00587038[4];
int FUN_002dca20(void) {
    if ((DAT_00586df8[0] == 0) && (DAT_00586590[0] != 0) && (DAT_00554bfc[0] == 0)) {
        DAT_00586df8[0] = FUN_002c5e10(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    }
    return DAT_00586df8[0];
}

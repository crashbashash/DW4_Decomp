/* 0x001e0410 — FUN_001e0410. m2c draft, symbol; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern char DAT_004e4880[];
int FUN_0019a6e0();
int Memory_GetAllocatorBySelector();
int FUN_00306e50();
extern int DAT_00562a38[4];
extern void * DAT_00586dc8[4];
extern int DAT_00587038[4];
extern unsigned char GPR_00554bac;

void FUN_001e0410(void) {
    DAT_00562a38[0] = FUN_0019a6e0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    FUN_00306e50(*(int *)((char *)DAT_00586dc8[0] + 56), 7, DAT_004e4880, &GPR_00554bac, GPR_00554bac, 1);
}

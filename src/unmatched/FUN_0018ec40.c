/* 0x0018ec40 — FUN_0018ec40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00188920(int);
int FUN_00188a80(int);
int FUN_00188be0(int);
int FUN_00188d40(int);
int FUN_00188ea0(int);
int FUN_00189000(int);
int FUN_00189160(int);
int FUN_001892c0(int);
int FUN_00189420(int);
int FUN_00189580(int);
int FUN_001896e0(int);
int FUN_00189840(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00561118[4];
extern int DAT_00561120[4];
extern int DAT_00561128[4];
extern int DAT_00561130[4];
extern int DAT_00561138[4];
extern int DAT_00561140[4];
extern int DAT_00561148[4];
extern int DAT_00561150[4];
extern int DAT_00561158[4];
extern int DAT_00561160[4];
extern int DAT_00561168[4];
extern int DAT_00561170[4];
extern int DAT_00587038[4];
void FUN_0018ec40(void) {
    DAT_00561130[0] = FUN_00189420(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561138[0] = FUN_001892c0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561140[0] = FUN_00189160(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561148[0] = FUN_00189000(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561150[0] = FUN_00188ea0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561160[0] = FUN_00188be0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561168[0] = FUN_00188a80(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561158[0] = FUN_00188d40(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561170[0] = FUN_00188920(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561118[0] = FUN_00189840(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561120[0] = FUN_001896e0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561128[0] = FUN_00189580(Memory_GetAllocatorBySelector(DAT_00587038[0]));
}

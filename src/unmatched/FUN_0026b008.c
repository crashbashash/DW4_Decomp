/* 0x0026b008 — FUN_0026b008. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026f728();
int FUN_0026fa60();
int FUN_00270db0();
int FUN_00275310();
int FUN_00275340();
int FUN_00276ce8();
int FUN_00276d18();
extern int DAT_004ee4b0[4];
extern int DAT_004ee4b8[4];
int FUN_0026aff0();
int FUN_00275370();
int FUN_00277dd0();

void FUN_0026b008(void *arg0) {
    FUN_00270db0(&FUN_0026aff0, 0);
    FUN_0026f728(&DAT_004ee4b0[0], &FUN_00277dd0, 0);
    FUN_00270db0(&FUN_0026aff0, 0);
    FUN_0026f728(&DAT_004ee4b8[0], &FUN_00275370, 0);
    FUN_0026fa60(&DAT_004ee4b8[0]);
    if (arg0 != 0) {
        FUN_00276ce8(*(int *)((char *)(arg0) + 4));
        FUN_00276d18(*(int *)((char *)(arg0) + 0));
        if (*(int *)((char *)(arg0) + 8) == 0) {
            FUN_00275310(0);
        } else {
            FUN_00275310(1);
        }
        if (*(int *)((char *)(arg0) + 12) == 0) {
            FUN_00275340(0);
            return;
        }
        FUN_00275340(1);
        return;
    }
    FUN_00276ce8(0);
    FUN_00276d18(0);
    FUN_00275310(0);
    FUN_00275340(0);
}

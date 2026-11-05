/* 0x0010d460 — FUN_0010d460. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0010ba90();
int RemoveDmacHandler();
extern int DAT_00481e68[4];
extern int DAT_00555fd4[4];
void FUN_0010d460(void) {
    FUN_0010ba90(5);
    RemoveDmacHandler(5, DAT_00555fd4[0]);
    DAT_00481e68[0] = 0;
}

/* 0x0030b2c0 — FUN_0030b2c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRefMetaField_CopyConstruct();
extern int DAT_00533180[4];
void *FUN_0030b2c0(void *arg0, void *arg1) {
    igRefMetaField_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00533180[0]);
    *(unsigned char *)((char *)(arg0) + 56) = (unsigned char) *(unsigned char *)((char *)(arg1) + 56);
    return arg0;
}

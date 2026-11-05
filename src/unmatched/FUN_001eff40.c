/* 0x001eff40 - FUN_001eff40. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int FUN_00204240();
extern int DAT_005691c0[4];
void FUN_001eff40(void) {
    DAT_005691c0[0] = 0;
    FUN_00204240(8, &DAT_005691c0[0]);
}

/* 0x002e5ac0 — FUN_002e5ac0. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int FUN_002d8620();
extern int DAT_004fb410[4];
void FUN_002e5ac0(int *arg0, void *arg1) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(arg1) + 28));
    if (*(int *)((char *)(temp_a1) + 8) > 0) {
        *(int *)((char *)(arg1) + 220) = FUN_002d8620(arg1, temp_a1, 0, 0);
        *(char *)((char *)(arg1) + 212) = 1;
    }
    *arg0 = DAT_004fb410[0];
}

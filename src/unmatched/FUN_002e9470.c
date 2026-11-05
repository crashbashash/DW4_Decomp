/* 0x002e9470 — FUN_002e9470. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int FUN_002e8a10();
int FUN_002e8a40();

int FUN_002e9470(void *arg0) {
    FUN_002e8a40();
    *(char *)((char *)(arg0) + 48) = 0;
    *(char *)((char *)(arg0) + 49) = 0;
    FUN_002e8a10(arg0);
    return -1;
}

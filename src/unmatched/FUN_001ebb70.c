/* 0x001ebb70 - FUN_001ebb70. flag register set/clear with else-if (the draft's second symbol was the same global) Verified byte-identical by tools/verify.py. */
extern int DAT_00568e48[4];
void FUN_001ebb70(int arg0, int arg1) {
    if (arg0 == 1) { if (arg1 != 0) { DAT_00568e48[0] |= 1; } else { DAT_00568e48[0] &= ~1; } } else if (arg0 == 2) { if (arg1 != 0) { DAT_00568e48[0] |= 2; } else { DAT_00568e48[0] &= ~2; } }
}

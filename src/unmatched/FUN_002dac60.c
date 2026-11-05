/* 0x002dac60 — FUN_002dac60. hand-matched: the callee's address argument is the *second*
 * (the pass-through arg0 was missing from the draft); verified by tools/verify.py. */
int FUN_0030b3c0();
extern int DAT_004f96b8[4];

int FUN_002dac60(void *arg0) {
    FUN_0030b3c0(arg0, &DAT_004f96b8[0]);
    return 1;
}

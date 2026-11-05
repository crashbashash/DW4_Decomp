/* 0x0029f200 — FUN_0029f200 (176 bytes). Runs the state-update stages FUN_0029f310, FUN_0029f318, FUN_0029fd18, FUN_0029f880 and FUN_0029fb20, stopping at the first that reports a result. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0029f2b0();
int FUN_0029f310();
int FUN_0029f318();
int FUN_0029f880();
int FUN_0029fb20();
int FUN_0029fd18();

/* Runs the state-update stages in order and stops at the first one that reports a result. */
/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int FUN_0029f200(void *owner, int index, void *state) {
    FUN_0029f2b0(state);
    if (FUN_0029f310(owner, index, state) == 0 && FUN_0029f318(owner, index, state) == 0
        && FUN_0029fd18(owner, index, state) == 0 && FUN_0029f880(owner, index, state) == 0) {
        FUN_0029fb20(owner, index, state);
    }
}

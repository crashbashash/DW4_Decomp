/* 0x00296070 — FUN_00296070 (60 bytes). Dispatches on DAT_004be89c: FUN_002960e8 while it is clear, FUN_002960b0 otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_004be89c;
extern int FUN_002960e8(void);
extern int FUN_002960b0(void);

/* matching construct: manual — an int function that falls off the end; a void
 * function or `return f()` turns the two calls into tail jumps, retail keeps jal + return. */
int FUN_00296070(void) {
    if (DAT_004be89c == 0) {
        FUN_002960e8();
    } else {
        FUN_002960b0();
    }
}

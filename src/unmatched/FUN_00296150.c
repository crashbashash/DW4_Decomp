/* 0x00296150 — FUN_00296150 (60 bytes). Dispatches on DAT_004be89c: FUN_002961c0 while it is clear, FUN_00296190 otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_004be89c;
extern int FUN_002961c0(void);
extern int FUN_00296190(void);

/* matching construct: manual — an int function that falls off the end; a void
 * function or `return f()` turns the two calls into tail jumps, retail keeps jal + return. */
int FUN_00296150(void) {
    if (DAT_004be89c == 0) {
        FUN_002961c0();
    } else {
        FUN_00296190();
    }
}

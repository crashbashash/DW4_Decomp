/* 0x0029d330 — FUN_0029d330 (72 bytes). When option 6 is set, posts event (3, 6) through FUN_002b0338. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002adc40(void *handle, int option);
extern int FUN_002b0338(void *handle, int group, int event, int a, int b);

/* Declared int with no return statement: falling off the end keeps the call
   a plain jal, as retail has it, instead of a sibling tail call. */
int FUN_0029d330(void *handle) {
    if (FUN_002adc40(handle, 6) != 0) {
        FUN_002b0338(handle, 3, 6, 0, 0);
    }
}

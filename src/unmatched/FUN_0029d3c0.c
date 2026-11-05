/* 0x0029d3c0 — FUN_0029d3c0 (84 bytes). Issues FUN_002b0338(player, 3, 8, value, 0) once FUN_002adc40(player, 6) succeeds. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002adc40();
int FUN_002b0338();

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int FUN_0029d3c0(void *player, int value) {
    if (FUN_002adc40(player, 6) != 0) {
        FUN_002b0338(player, 3, 8, value, 0);
    }
}

/* 0x002a8690 — FUN_002a8690 (40 bytes). Moves a state word from 4 to 2; any other state becomes 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002a8690(int *state) {
    if (state != 0) {
        if (*state == 4) {
            *state = 2;
        } else {
            *state = 0;
        }
    }
}

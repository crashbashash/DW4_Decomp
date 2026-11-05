/* 0x002a8668 — FUN_002a8668 (40 bytes). Moves a state word from 4 to 3; any other state becomes 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002a8668(int *state) {
    if (state != 0) {
        if (*state == 4) {
            *state = 3;
        } else {
            *state = 0;
        }
    }
}

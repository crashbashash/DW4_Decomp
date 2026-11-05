/* 0x0025bac8 — FUN_0025bac8 (136 bytes). Returns 1 when the byte pair 0x0B,0x77 appears, in either order, at offset 0 or offset 16 of the buffer (the value of the AC-3 sync word; the meaning here is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0025bac8(const unsigned char *data) {
    if (data[0] == 0x0b && data[1] == 0x77) {
        return 1;
    }
    if (data[0] == 0x77 && data[1] == 0x0b) {
        return 1;
    }
    if (data[16] == 0x0b && data[17] == 0x77) {
        return 1;
    }
    if (data[16] == 0x77 && data[17] == 0x0b) {
        return 1;
    }
    return 0;
}

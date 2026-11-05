/* 0x00262b60 — FUN_00262b60 (28 bytes). Reads the big-endian 16-bit value at offset 2 of a header into the halfword at offset 14 of an info record. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00262b60(unsigned char *header, short *info) {
    unsigned char *field = header + 2;

    info[7] = field[1] | (field[0] << 8);
}

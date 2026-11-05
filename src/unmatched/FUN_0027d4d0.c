/* 0x0027d4d0 — FUN_0027d4d0 (148 bytes). Writes the low 28 bits of value as seven lower-case hex digits (most significant first) into text[0..6] using the digit table DAT_004ba2a0 ("0123456789abcdef"); no terminator is written. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern unsigned char DAT_004ba2a0[]; /* '0123456789abcdef' */

void FUN_0027d4d0(int value, unsigned char *text) {
    text[6] = DAT_004ba2a0[value & 15];
    value >>= 4;
    text[5] = DAT_004ba2a0[value & 15];
    value >>= 4;
    text[4] = DAT_004ba2a0[value & 15];
    value >>= 4;
    text[3] = DAT_004ba2a0[value & 15];
    value >>= 4;
    text[2] = DAT_004ba2a0[value & 15];
    value >>= 4;
    text[1] = DAT_004ba2a0[value & 15];
    value >>= 4;
    text[0] = DAT_004ba2a0[value & 15];
}


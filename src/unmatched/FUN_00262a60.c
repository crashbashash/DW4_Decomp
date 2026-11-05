/* 0x00262a60 — FUN_00262a60 (32 bytes). Stores a 32-bit value big-endian at bytes. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00262a60(unsigned char *bytes, unsigned int value) {
    bytes[0] = value >> 24;
    bytes[1] = value >> 16;
    bytes[2] = value >> 8;
    bytes[3] = value;
}

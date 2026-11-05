/* 0x00262a30 — FUN_00262a30 (24 bytes). Stores a 16-bit value big-endian at bytes. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00262a30(unsigned char *bytes, short value) {
    bytes[1] = value;
    bytes[0] = (unsigned short)value >> 8;
}

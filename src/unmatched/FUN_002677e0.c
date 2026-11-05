/* 0x002677e0 — FUN_002677e0 (48 bytes). Returns base + 4 + 18 * count * (bits rounded up to 32-bit words): an address past count 18-byte-per-word records. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002677e0(int count, int base, int bits) {
    return (bits + 31) / 32 * count * 18 + base + 4;
}

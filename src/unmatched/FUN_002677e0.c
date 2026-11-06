/* Returns base + 4 + 18 * count * (bits rounded up to 32-bit words): an address past count
 * 18-byte-per-word records. */
int FUN_002677e0(int count, int base, int bits) {
    return (bits + 31) / 32 * count * 18 + base + 4;
}

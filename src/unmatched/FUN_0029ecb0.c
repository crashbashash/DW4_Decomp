/* 0x0029ecb0 — FUN_0029ecb0 (52 bytes). Replaces the low word of a 64-bit counter, carrying into the high word when the new low word wrapped. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
long FUN_0029ecb0(long total, unsigned int low) {
    long high = total >> 32;
    unsigned int carry = low < (unsigned int)total;

    high += carry;
    return (high << 32) | low;
}

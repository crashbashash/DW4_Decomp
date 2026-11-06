/* Replaces the low word of a 64-bit counter, carrying into the high word when the new low word
 * wrapped. */
long FUN_0029ecb0(long total, unsigned int low) {
    long high = total >> 32;
    unsigned int carry = low < (unsigned int)total;

    high += carry;
    return (high << 32) | low;
}

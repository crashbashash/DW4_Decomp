/* Returns 1 when the double argument is a NaN. */
typedef union DoubleWords {
    double value;
    struct {
        unsigned int low;
        unsigned int high;
    } words;
} DoubleWords;

int FUN_001228d8(double x) {
    int high;
    int low;

    /* newlib's EXTRACT_WORDS macro: the union lives in its own do/while block */
    do {
        DoubleWords bits;
        bits.value = x;
        high = bits.words.high;
        low = bits.words.low;
    } while (0);
    high &= 0x7fffffff;
    high |= (unsigned int)(low | -low) >> 31;
    high = 0x7ff00000 - high;
    return (unsigned int)high >> 31;
}

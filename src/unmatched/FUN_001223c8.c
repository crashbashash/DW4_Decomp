/* Returns x with the sign bit of y (newlib copysign shape; name is a hypothesis). */
typedef union DoubleWords {
    double value;
    struct {
        unsigned int low;
        unsigned int high;
    } words;
} DoubleWords;

double FUN_001223c8(double x, double y) {
    unsigned int highX;
    unsigned int highY;

    /* newlib's GET_HIGH_WORD / SET_HIGH_WORD macros: each union lives in its own do/while block */
    do {
        DoubleWords bits;
        bits.value = x;
        highX = bits.words.high;
    } while (0);
    do {
        DoubleWords bits;
        bits.value = y;
        highY = bits.words.high;
    } while (0);
    do {
        DoubleWords bits;
        bits.value = x;
        bits.words.high = (highX & 0x7fffffff) | (highY & 0x80000000);
        x = bits.value;
    } while (0);
    return x;
}

/* Copies `count` 16-bit values from src to dst. */
void FUN_0025e120(unsigned short *dst, const unsigned short *src, int count) {
    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

/* Header probe: when size is at least 2 and the big-endian 16-bit word at data is 0x8001, stores
 * size and returns 1; otherwise 0. */
int FUN_0026d2e8(unsigned short *data, int size, int *out_size) {
    unsigned short word;

    if (size < 2) {
        return 0;
    }
    word = *data;
    if ((unsigned short)((word >> 8) | (word << 8)) != 0x8001) {
        return 0;
    }
    *out_size = size;
    return 1;
}


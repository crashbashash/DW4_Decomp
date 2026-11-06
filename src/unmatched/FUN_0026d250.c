/* Header probe: when size is at least 2 and the big-endian 16-bit word at data is 0x8000, decodes
 * the header with FUN_0025f588 and stores its first (16-bit) field; returns 1 on success, 0
 * otherwise. */
int FUN_0025f588(unsigned short *data, int size, short *out_a, char *out_b, char *out_c, char *out_d, char *out_e, int *out_f, int *out_g, int *out_h);

int FUN_0026d250(unsigned short *data, int size, int *out_value) {
    short value_a;
    char value_b;
    char value_c;
    char value_d;
    char value_e;
    int value_g;
    int value_h;
    int value_f;
    unsigned short word;

    if (size < 2) {
        return 0;
    }
    word = *data;
    if ((unsigned short)((word >> 8) | (word << 8)) != 0x8000) {
        return 0;
    }
    if (FUN_0025f588(data, size, &value_a, &value_b, &value_c, &value_d, &value_e, &value_f, &value_g, &value_h) < 0) {
        return 0;
    }
    *out_value = value_a;
    return 1;
}


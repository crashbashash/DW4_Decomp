/* 0x00267968 — FUN_00267968 (100 bytes). Decodes a header with FUN_0025f588, passing out_f/out_g through and passing back only its third and fifth byte fields (sign-extended) through out_c and out_e; returns the decoder result. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0025f588(unsigned short *data, int size, short *out_a, char *out_b, char *out_c, char *out_d, char *out_e, int *out_f, int *out_g, int *out_h);

int FUN_00267968(unsigned short *data, int size, int *out_c, int *out_e, int *out_f, int *out_g) {
    short value_a;
    char value_b;
    char value_c;
    char value_d;
    char value_e;
    int value_h;
    int result;

    result = FUN_0025f588(data, size, &value_a, &value_b, &value_c, &value_d, &value_e, out_f, out_g, &value_h);
    *out_e = value_e;
    *out_c = value_c;
    return result;
}

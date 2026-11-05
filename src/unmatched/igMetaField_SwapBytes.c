typedef struct F { char p[20]; unsigned short size; } F;
void igMetaField_SwapBytes(F *arg0, unsigned char *arg1, int arg2) {
    int size = arg0->size;
    int i;
    int j;
    int half;
    int lo;
    int last;
    unsigned char *a;
    unsigned char *b;
    unsigned char t;
    if (size != 1) {
        for (i = 0, half = size >> 1; i < arg2; i++) {
            lo = i * size;
            last = (i + 1) * size - 1;
            for (j = 0; j < half; j++) {
                a = arg1 + (j + lo);
                b = arg1 + (last - j);
                t = *a;
                *a = *b;
                *b = t;
            }
        }
    }
}

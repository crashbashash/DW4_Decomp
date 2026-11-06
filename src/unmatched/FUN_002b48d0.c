/* When FUN_002b4b98 accepts the decoder, converts 256 32-bit samples to 16-bit by dropping the low
 * 15 bits; otherwise reports through FUN_002b3b38 with the table DAT_004f58b0. */
extern char DAT_004f58b0[];

int FUN_002b4b98(void *dec);
void FUN_002b3b38(void *dec, int arg, void *table);

void FUN_002b48d0(void *dec, unsigned int *src, short *dst) {
    int i;

    if (FUN_002b4b98(dec) == 1) {
        for (i = 0; i < 256; i++) {
            dst[i] = src[i] >> 15;
        }
    } else {
        FUN_002b3b38(0, 0, DAT_004f58b0);
    }
}

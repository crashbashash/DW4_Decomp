/* Initialises a decoder object: binds its buffers (FUN_00290e88), copies the first 16 words of the
 * global descriptor at 0x573f18, resets its sub-records (FUN_0028ea30, FUN_00290f70), clears the
 * counters, empties the four 12-byte entries (FUN_0028f098), calls FUN_0028f0c0(dec, 0, 0), and
 * marks it ready (state 2, checked by FUN_002913f8); returns it. */
extern void FUN_00290e88(void *dec);
extern void FUN_0028b350(void *dst, const void *src, int words); /* word copy */
extern void FUN_0028ea30(void *rec);
extern void FUN_00290f70(void *rec);
extern void FUN_0028f098(void *dec, int index, int a, int b, int c);
extern void FUN_0028f0c0(void *dec, int a, int b);
extern char DAT_00573f18[]; /* global descriptor (FUN_00290ec8) */

typedef struct {
    char pad0[392];
    int state;          /* 392: 2 once initialised (FUN_002913f8) */
    int f396;
    char desc[28];      /* 400: copy of the global descriptor, 64 bytes */
    int f428;
    char descRest[32];
    char rec464[128];   /* 464 */
    char rec592[264];   /* 592 */
    int f856;
    int f860;
    int f864;
    int f868;
    char pad872[24];
    int f896;
    int f900;
    char pad904[12];
    int f916;
    char pad920[12];
    int f932;
} Dec2910f0;

Dec2910f0 *FUN_002910f0(Dec2910f0 *dec) {
    int i;

    FUN_00290e88(dec);
    dec->f396 = 0;
    FUN_0028b350(dec->desc, DAT_00573f18, 16);
    FUN_0028ea30(dec->rec592);
    FUN_00290f70(dec->rec464);
    dec->f896 = 0;
    dec->f900 = 0;
    dec->f932 = dec->f428;
    dec->f856 = 0;
    dec->f860 = 0;
    dec->f864 = 0;
    dec->f868 = 0;
    dec->f916 = 0;
    for (i = 0; i < 4; i++) {
        FUN_0028f098(dec, i, 0, 0, 0);
    }
    FUN_0028f0c0(dec, 0, 0);
    dec->state = 2;
    return dec;
}

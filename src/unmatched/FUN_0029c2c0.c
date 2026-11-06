/* Looks up the current entry via FUN_0029e370; when present, folds its two FUN_0029eaf8 values and
 * those of the second table's entry into the four 64-bit accumulators at +2480..+2512 with
 * FUN_0029ecb0. */
int FUN_0029e370();
int FUN_0029eaf8();
long FUN_0029ecb0();

struct Sub1ff4 {
    char pad0[8];
    int *f8;                              /* +8188 in the owner */
    char pad12[16 - 12];
    int f16;                              /* +8196 in the owner */
};
struct Decoder {
    char pad0[2480];
    long f2480;
    long f2488;
    char pad2496[2504 - 2496];
    long f2504;
    long f2512;
    char pad2520[8180 - 2520];
    struct Sub1ff4 sub;
};

void FUN_0029c2c0(struct Decoder *dec) {
    struct Sub1ff4 *sub = &dec->sub;
    int *other = sub->f8;
    int entry;
    int a;
    int b;

    FUN_0029e370(dec, sub->f16, &entry);
    if (entry != 0) {
        FUN_0029eaf8(entry, &a, &b);
        dec->f2480 = FUN_0029ecb0(dec->f2480, a);
        dec->f2488 = FUN_0029ecb0(dec->f2488, b);
        FUN_0029eaf8(other[1], &a, &b);
        dec->f2504 = FUN_0029ecb0(dec->f2504, a);
        dec->f2512 = FUN_0029ecb0(dec->f2512, b);
    }
}

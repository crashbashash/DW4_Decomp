/* Resets a record: three 64-bit fields to 0, INT64_MAX, 0 and the word at +24 to 0. */

/* Members are 64-bit (long is 64-bit under EE GCC). */
struct Rec1C {
    long f0;
    long f8;                              /* reset to the largest positive 64-bit value */
    long f16;
    int f24;
};

void FUN_002afba8(struct Rec1C *rec) {
    rec->f0 = 0;
    rec->f8 = 0x7FFFFFFFFFFFFFFFL;
    rec->f16 = 0;
    rec->f24 = 0;
}

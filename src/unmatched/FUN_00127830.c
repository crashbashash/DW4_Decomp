/* Allocates a one-word big integer through FUN_001273e0 and sets it to `value`. The shape of
 * newlib's _i2b over Balloc (hypothesis). */
typedef struct BigInt127830 {
    struct BigInt127830 *next;  /* +0 */
    int k;                      /* +4 */
    int maxwds;                 /* +8 */
    int sign;                   /* +12 */
    int wds;                    /* +16: words in use */
    unsigned int x[1];          /* +20 */
} BigInt127830;

BigInt127830 *FUN_001273e0(void *state, int k);

BigInt127830 *FUN_00127830(void *state, int value) {
    BigInt127830 *b;

    b = FUN_001273e0(state, 1);
    b->x[0] = value;
    b->wds = 1;
    return b;
}

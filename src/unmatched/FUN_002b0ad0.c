/* Subtracts delta from each of the `count` samples at +24, then stores their mean (FUN_002b0b30)
 * at +424. */
int FUN_002b0b30();

struct Samples {
    char pad[16];
    int count;                            /* +16 */
    int f20;
    int values[100];                      /* +24; bounded by `average` at +424 */
    int average;                          /* +424 */
};

void FUN_002b0ad0(struct Samples *samples, int delta) {
    int i;

    for (i = 0; i < samples->count; i++) {
        samples->values[i] -= delta;
    }
    samples->average = FUN_002b0b30(samples);
}

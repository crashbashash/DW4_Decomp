/* 0x002b0b30 — FUN_002b0b30 (76 bytes). Returns the integer mean of the `count` samples at +24 (the divide traps on a zero count, as GCC emits it). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Samples {
    char pad[16];
    int count;                            /* +16 */
    int f20;
    int values[100];                      /* +24; bounded by `average` at +424 */
    int average;                          /* +424 */
};

int FUN_002b0b30(struct Samples *samples) {
    int count = samples->count;
    int sum = 0;
    int i;

    for (i = 0; i < count; i++) {
        sum += samples->values[i];
    }
    return sum / count;
}

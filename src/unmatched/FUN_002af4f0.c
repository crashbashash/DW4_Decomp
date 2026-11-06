/* Scales the block's own rate (+0xD28+736) by pos/rate (FUN_002916f8) and, under the FUN_002a0e70
 * guard, adds it to the decoded position (+0xD28+732). */
int FUN_002916f8(int value, int scale, int divisor);
void FUN_002a0e70(void *guard);
void FUN_002a0e88(void *guard);

struct TimingBlock {
    char pad0[732];
    int decoded_pos; /* +732 */
    int rate;        /* +736 */
};

void FUN_002af4f0(int obj, int pos, int rate) {
    struct TimingBlock *timing = (struct TimingBlock *)(obj + 0xD28);
    char guard[16];
    int delta;

    delta = FUN_002916f8(timing->rate, pos, rate);
    FUN_002a0e70(guard);
    timing->decoded_pos += delta;
    FUN_002a0e88(guard);
}

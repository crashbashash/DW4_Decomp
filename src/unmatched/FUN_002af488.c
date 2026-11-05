/* 0x002af488 — FUN_002af488 (100 bytes). Scales the global rate DAT_004bea90 by pos/rate (FUN_002916f8) and, under the FUN_002a0e70 guard, adds it to the stream position (+0xD28+680) and the counter at +0xD28+716. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002916f8(int value, int scale, int divisor);
void FUN_002a0e70(void *guard);
void FUN_002a0e88(void *guard);

/* matching construct: volatile — the clock fields are updated under the FUN_002a0e70 guard and the retail code keeps each read-modify-write in order */
struct TimingBlock {
    char pad0[680];
    volatile int stream_pos; /* +680 */
    char pad684[716 - 684];
    volatile int count;      /* +716 */
};

extern int DAT_004bea90;

void FUN_002af488(int obj, int pos, int rate) {
    struct TimingBlock *timing = (struct TimingBlock *)(obj + 0xD28);
    char guard[16];
    int delta;

    delta = FUN_002916f8(DAT_004bea90, pos, rate);
    FUN_002a0e70(guard);
    timing->stream_pos += delta;
    timing->count += delta;
    FUN_002a0e88(guard);
}

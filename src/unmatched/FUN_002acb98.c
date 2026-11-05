/* 0x002acb98 — FUN_002acb98 (112 bytes). Resets a 0xDD8-byte record: clears its head through FUN_0028b530, runs FUN_002acc08 and sets the value/divisor/scale triples to 0/-8/1 and the ids to -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0028b530(void *dst, int value, int size);
void FUN_002acc08(void *record);

/* One 3544-byte (0xDD8) record; members as read by FUN_002ad2e0..FUN_002ad870. */
struct Rec0DD8 {
    int state;                            /* +0; 1 = running (FUN_002ace48) */
    int f4;
    char pad8[3496 - 8];
    int f3496;                            /* derived value (FUN_002ad870) */
    int f3500, f3504, f3508;              /* default value / divisor / scale */
    int f3512, f3516;
    int f3520;                            /* non-zero: calls are forwarded to it */
    int f3524, f3528, f3532;              /* value / divisor / scale */
    int f3536;                            /* explicit value, used when positive */
    int f3540;
    char pad3544[0xDD8 - 3544];
};

void FUN_002acb98(struct Rec0DD8 *record) {
    FUN_0028b530(record, 0, 886);
    FUN_002acc08(record);
    record->f3496 = 0;
    record->f3500 = 0;
    record->f3504 = -8;
    record->f3508 = 1;
    record->f3512 = -1;
    record->f3516 = -1;
    record->f3520 = 0;
    record->f3524 = 0;
    record->f3528 = -8;
    record->f3532 = 1;
    record->f3536 = 0;
    record->f3540 = -1;
}

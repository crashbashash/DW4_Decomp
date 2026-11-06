/* Sets *ready to 1 when the record exists, is running (FUN_002ace48) and either forwards to a
 * delegate (+3520) or has a positive derived value (+3496); otherwise 0. */
/* matching construct: declared void here — an int prototype moves the flag load from v0 to v1 */
void FUN_002ace48(void *record, int *running);

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

void FUN_002ad1d0(struct Rec0DD8 *record, int *ready) {
    int running;

    *ready = 0;
    if (record == 0) {
        return;
    }
    FUN_002ace48(record, &running);
    if (running != 0) {
        if (record->f3520 != 0 || record->f3496 > 0) {
            *ready = 1;
        }
    }
}

/* Runs FUN_002acb98 over each of `count` consecutive 0xDD8-byte records. */
int FUN_002acb98();

/* One 3544-byte (0xDD8) record; members as read by FUN_002ad2e0..FUN_002ad870. */
struct Rec0DD8 {
    int f0;
    int f4;                               /* fallback value (FUN_002ad870) */
    char pad8[3496 - 8];
    int f3496;                            /* value derived by FUN_002ad870 */
    int f3500, f3504, f3508;              /* default value / divisor / scale */
    char pad3512[3520 - 3512];
    int f3520;                            /* non-zero: calls are forwarded to it (FUN_002ad2e0, FUN_002ad3e0) */
    int f3524, f3528, f3532;              /* value / divisor / scale */
    int f3536;                            /* explicit value, used when positive */
    char pad3540[0xDD8 - 3540];
};

void FUN_002acb50(struct Rec0DD8 *records, int count) {
    int i;

    for (i = 0; i < count; i++) {
        FUN_002acb98(&records[i]);
    }
}

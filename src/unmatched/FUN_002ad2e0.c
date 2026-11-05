/* 0x002ad2e0 — FUN_002ad2e0 (76 bytes). Forwards to FUN_002ad330 when the record carries a delegate at +3520; otherwise stores record+3496 * scale / divisor (FUN_002916f8, a 64-bit multiply-divide) through out. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002916f8();
int FUN_002ad330();

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

void FUN_002ad2e0(struct Rec0DD8 *record, int scale, int divisor, int *out) {
    int delegate = record->f3520;

    if (delegate != 0) {
        FUN_002ad330(delegate);
        return;
    }
    *out = FUN_002916f8(record->f3496, scale, divisor);
}

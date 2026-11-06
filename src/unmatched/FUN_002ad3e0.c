/* Forwards to FUN_002ad468 when the record carries a delegate at +3520; otherwise reports value *
 * 1000 / record+3496 (FUN_002916f8, a 64-bit multiply-divide) (0 when that is not positive) and a
 * scale of 1000. */
int FUN_002916f8();
int FUN_002ad468();

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

void FUN_002ad3e0(struct Rec0DD8 *record, int value, int *out, int *outScale) {
    int delegate = record->f3520;
    int divisor;

    if (delegate != 0) {
        /* matching construct: manual — forwarding all arguments keeps a2/a3 live, so value is copied to t0 as in retail */
        FUN_002ad468(delegate, value, out, outScale);
        return;
    }
    divisor = record->f3496;
    if (divisor <= 0) {
        *out = 0;
    } else {
        *out = FUN_002916f8(value, 1000, divisor);
    }
    *outScale = 1000;
}

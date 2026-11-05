/* 0x002ad870 — FUN_002ad870 (132 bytes). Recomputes the record's value at +3496: an explicit value at +3536 wins; else value*scale/divisor (FUN_002916f8) from +3524/+3532/+3528, falling back to +4 and then to the defaults at +3500/+3508/+3504. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002916f8();

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

struct Owner3628 {
    char pad[13864];
    struct Rec0DD8 *record;               /* +13864 (0x3628) */
};

/* Returns the stored value; the int return keeps v0 live and gives retail's epilogue order. */
int FUN_002ad870(struct Owner3628 *owner) {
    struct Rec0DD8 *record = owner->record;
    int value = record->f3536;
    int numerator, scale, divisor;

    if (value <= 0) {
        numerator = record->f3524;
        divisor = record->f3528;
        scale = record->f3532;
        if (numerator <= 0 || divisor <= 0) {
            value = record->f4;
            if (value > 0) {
                goto store;
            }
            if (numerator <= 0) {
                numerator = record->f3500;
            }
            if (divisor <= 0) {
                divisor = record->f3504;
                scale = record->f3508;
            }
            if (numerator <= 0 || divisor <= 0) {
                goto store;
            }
        }
        value = FUN_002916f8(numerator, scale, divisor);
    }
store:
    record->f3496 = value;
    return value;
}

/* 0x002ad570 — FUN_002ad570 (112 bytes). Stores a value at +3524 of the owner's record (if any) and calls FUN_002ad870 on the owner; reports error 0xFF000159 when FUN_002a0dd8 refuses. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();
int FUN_002a0dd8(owner);
int FUN_002ad870();

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

int FUN_002ad570(struct Owner3628 *owner, int value) {
    struct Rec0DD8 *record;

    if (FUN_002a0dd8(owner) != 0) {
        return FUN_002a0bb8(0, 0xFF000159);
    }
    record = owner->record;
    if (record == 0) {
        return 0;
    }
    record->f3524 = value;
    FUN_002ad870(owner);
    return 0;
}

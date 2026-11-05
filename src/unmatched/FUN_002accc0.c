/* 0x002accc0 — FUN_002accc0 (88 bytes). Stores the record pointer at owner+13864, or reports error 0xFF000151 when FUN_002a0dd8 refuses. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();
int FUN_002a0dd8();

struct Rec0DD8;

struct Owner3628 {
    char pad[13864];
    struct Rec0DD8 *record;               /* +13864 (0x3628) */
};

int FUN_002accc0(struct Owner3628 *owner, struct Rec0DD8 *record) {
    if (FUN_002a0dd8(owner) != 0) {
        return FUN_002a0bb8(0, 0xFF000151);
    }
    owner->record = record;
    return 0;
}

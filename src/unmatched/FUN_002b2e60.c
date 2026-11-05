/* 0x002b2e60 — FUN_002b2e60 (64 bytes). True when FUN_002b2ea0(arg0) reports 0xE0 and the byte at +32 of the record is exactly 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b2ea0();

struct Rec20 {
    char pad[32];
    unsigned char f32;
};

int FUN_002b2e60(int arg0, struct Rec20 *rec) {
    unsigned char value;

    if (FUN_002b2ea0(arg0) != 0xE0) {
        return 0;
    }
    value = rec->f32;
    /* matching construct: manual — the range-then-nonzero ternary (value == 1) is the shape that gives retail's sltu/sltiu/movz */
    return (value < 2) ? (value != 0) : 0;
}

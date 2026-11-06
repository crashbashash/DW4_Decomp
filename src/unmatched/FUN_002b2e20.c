/* True when FUN_002b2ea0(arg0) reports 0xC0 and the byte at +32 of the record is exactly 1. */
int FUN_002b2ea0();

struct Rec20 {
    char pad[32];
    unsigned char f32;
};

int FUN_002b2e20(int arg0, struct Rec20 *rec) {
    unsigned char value;

    if (FUN_002b2ea0(arg0) != 0xC0) {
        return 0;
    }
    value = rec->f32;
    /* matching construct: manual — the range-then-nonzero ternary (value == 1) is the shape that gives retail's sltu/sltiu/movz */
    return (value < 2) ? (value != 0) : 0;
}

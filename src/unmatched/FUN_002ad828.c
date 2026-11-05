/* 0x002ad828 — FUN_002ad828 (72 bytes). Two-level table lookup: the current index at ctx+7996 picks a 0x74-byte entry, whose word at +4952 picks a 0x44-byte entry of the table at ctx+7976; returns its word at +32, clamped to -1 when negative. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* Views of one 0x74-byte entry (indexed from ctx) and one 0x44-byte entry (indexed from ctx+7976);
 * only the members read here are known. */
struct Entry74 {
    char pad[4952];
    int slot;                             /* +4952: index into the 0x44-byte table */
};

struct Entry44 {
    char pad[32];
    int f32;
};

struct Table1F28 {
    char pad[20];
    int current;                          /* +20: index into the 0x74-byte table */
};

int FUN_002ad828(char *ctx) {
    char *table = ctx + 7976;
    int value;

    /* matching construct: manual — advancing the two base pointers in place reproduces retail's register reuse */
    ctx += ((struct Table1F28 *)table)->current * 0x74;
    table += ((struct Entry74 *)ctx)->slot * 0x44;
    value = ((struct Entry44 *)table)->f32;
    if (value < 0) {
        value = -1;
    }
    return value;
}

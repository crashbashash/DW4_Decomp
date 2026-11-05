/* 0x002b1160 — FUN_002b1160 (124 bytes). Sets the state word (+4) of 0x44-byte entry 8 to 1 through FUN_002b03b8 when FUN_002b03d0 reads it as not 1, FUN_0029ea88(obj, obj+8536) reports 1 and FUN_002b11e0 agrees. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0029ea88();
int FUN_002b03b8();
int FUN_002b03d0();
int FUN_002b11e0();

struct EntryOwner {
    char pad[8400];
    int f8400;                            /* +8400 (0x20D0): argument for entry 6 */
    char pad8404[8536 - 8404];
    int f8536;                            /* +8536 (0x2158): argument for entry 8 */
};

void FUN_002b1160(struct EntryOwner *obj) {
    if (FUN_002b03d0(obj, 8) != 1 && FUN_0029ea88(obj, obj->f8536) == 1 && FUN_002b11e0(obj) != 0) {
        FUN_002b03b8(obj, 8, 1);
    }
}

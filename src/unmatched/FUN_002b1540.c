/* 0x002b1540 — FUN_002b1540 (124 bytes). Sets the first word (+0) of 0x44-byte entry 6 to 1 through FUN_002b0388 when FUN_002b03a0 reads it as not 1, FUN_0029ea48(obj, obj+8400) reports 1 and FUN_002b15c0 agrees. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0029ea48();
int FUN_002b0388();
int FUN_002b03a0();
int FUN_002b15c0();

struct EntryOwner {
    char pad[8400];
    int f8400;                            /* +8400 (0x20D0): argument for entry 6 */
    char pad8404[8536 - 8404];
    int f8536;                            /* +8536 (0x2158): argument for entry 8 */
};

void FUN_002b1540(struct EntryOwner *obj) {
    if (FUN_002b03a0(obj, 6) != 1 && FUN_0029ea48(obj, obj->f8400) == 1 && FUN_002b15c0(obj) != 0) {
        FUN_002b0388(obj, 6, 1);
    }
}

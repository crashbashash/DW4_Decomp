/* 0x002b16b8 — FUN_002b16b8 (28 bytes). Forwards to FUN_0029e9b8(obj, obj+8400 word, value). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0029e9b8();

struct EntryOwner {
    char pad[8400];
    int f8400;                            /* +8400 (0x20D0): argument for entry 6 */
    char pad8404[8536 - 8404];
    int f8536;                            /* +8536 (0x2158): argument for entry 8 */
};

void FUN_002b16b8(struct EntryOwner *obj, int value) {
    FUN_0029e9b8(obj, obj->f8400, value);
}

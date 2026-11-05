/* 0x002b2ff0 — FUN_002b2ff0 (60 bytes). Initialises an entry handed out by FUN_002b2f48: parameter words (0, 31, 100) at +8, word +4 = 1 and the byte triple at +20 = (0, 64, 128). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct EntryParams {
    int f0;
    int f4;
    int f8;
};

/* Layout shared with FUN_002b2f48 (first word = in use), FUN_002b3058 (params) and FUN_002b3098/FUN_002b30c0 (bytes). */
struct Entry18 {
    int inUse;
    int f4;
    struct EntryParams params;            /* +8 */
    unsigned char bytes[3];               /* +20 */
};

void FUN_002b2ff0(struct Entry18 *entry) {
    /* matching construct: manual — taking the byte pointer first gives retail's v1/v0 order */
    unsigned char *bytes = entry->bytes;
    struct EntryParams *params = &entry->params;

    params->f0 = 0;
    params->f4 = 31;
    params->f8 = 100;
    entry->f4 = 1;
    bytes[0] = 0;
    bytes[1] = 64;
    bytes[2] = 128;
}

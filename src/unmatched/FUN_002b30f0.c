/* Sets the entry's three parameter words (+8: third argument, +12: first, +16: second) and its
 * word at +4 to 1. */
struct EntryParams {
    int f0;
    int f4;
    int f8;
};

/* Layout shared with FUN_002b2ff0, which initialises it. */
struct Entry18 {
    int inUse;
    int f4;
    struct EntryParams params;            /* +8 */
    unsigned char bytes[3];               /* +20 */
};

void FUN_002b30f0(struct Entry18 *entry, int param4, int param8, int param0) {
    struct EntryParams *params = &entry->params;

    params->f0 = param0;
    params->f4 = param4;
    params->f8 = param8;
    entry->f4 = 1;
}

/* Calls FUN_00284b68(value, bytes[0], bytes[1], bytes[2]) with the entry's byte triple at +20. */
int FUN_00284b68();

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

void FUN_002b30c0(struct Entry18 *entry, int unused, int value) {
    FUN_00284b68(value, entry->bytes[0], entry->bytes[1], entry->bytes[2]);
}

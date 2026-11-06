/* Gets a resource from FUN_00267bb8 and claims the first free entry of the 16-entry table
 * DAT_004a75f0 for it (owner at 20, resource at 136); returns the entry, or 0 when the resource is
 * missing or no entry is free. */
typedef struct Entry_267d00 {
    char used;          /* 0x00 */
    char pad1[19];
    int owner;          /* 0x14 */
    char pad24[112];
    void *resource;     /* 0x88 */
    char pad140[4];
} Entry_267d00;

extern Entry_267d00 DAT_004a75f0[16];
void *FUN_00267bb8(int owner);

Entry_267d00 *FUN_00267d00(int owner) {
    void *resource = FUN_00267bb8(owner);
    Entry_267d00 *entry;
    int i;

    if (resource == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        entry = &DAT_004a75f0[i];
        if (entry->used == 0) {
            break;
        }
    }
    /* Retail writes these even when the table is full (into the last entry). */
    entry->owner = owner;
    entry->resource = resource;
    if (i < 16) {
        entry->used = 1;
        return entry;
    }
    return 0;
}

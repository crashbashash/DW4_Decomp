/* 0x002b1c20 — FUN_002b1c20 (72 bytes). Finds the first of the 26 64-byte entries at +384 whose byte at +24 equals key; returns it, or null. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Entry40 {
    char pad[24];
    unsigned char key;                    /* +24 */
    char pad25[64 - 25];
};

struct Obj0180 {
    char pad[384];
    struct Entry40 entries[26];           /* +384 (0x180) */
};

struct Entry40 *FUN_002b1c20(struct Obj0180 *obj, int key) {
    struct Entry40 *entry = &obj->entries[0];
    struct Entry40 *found = 0;
    int entryKey = entry->key;
    int i = 0;

    /* matching construct: manual — a goto loop: retail recomputes &entries[i] each pass (no
     * loop strength reduction) and loads the key at the end of the body, which a for/while loop does not give */
    goto test;
next:
    i++;
    if (i >= 26) {
        goto done;
    }
    entry = &obj->entries[i];
    entryKey = entry->key;
test:
    if (entryKey != key) {
        goto next;
    }
    found = entry;
done:
    return found;
}

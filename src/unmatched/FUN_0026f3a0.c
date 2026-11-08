/* Returns the entry of the pool DAT_0056dfd4 (DAT_0056dfd8 16-byte entries) whose name matches
 * name in its first 12 characters (strncmp returning 0), or 0 for an empty name or no match. */
typedef struct Slot_26f3a0 {
    char name[16];  /* 0x00 */
} Slot_26f3a0;

extern Slot_26f3a0 *DAT_0056dfd4;
extern int DAT_0056dfd8;
int strncmp(const char *a, const char *b, int length);

Slot_26f3a0 *FUN_0026f3a0(const char *name) {
    Slot_26f3a0 *slot;
    int i;

    if (name[0] == 0) {
        return 0;
    }
    slot = DAT_0056dfd4;
    for (i = 0; i < DAT_0056dfd8; i++, slot++) {
        if (strncmp(slot->name, name, 12) == 0) {
            return slot;
        }
    }
    return 0;
}

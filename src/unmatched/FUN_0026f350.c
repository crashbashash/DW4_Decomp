/* Returns the first unused entry (byte 0 clear) of the handle pool DAT_0056dfd4 (DAT_0056dfd8
 * 16-byte entries), or 0 when the pool is full. */
typedef struct Slot_26f350 {
    signed char used;   /* 0x00 */
    char pad1[15];
} Slot_26f350;

extern Slot_26f350 *DAT_0056dfd4;
extern int DAT_0056dfd8;

Slot_26f350 *FUN_0026f350(void) {
    Slot_26f350 *slot = DAT_0056dfd4;
    int i;

    for (i = 0; i < DAT_0056dfd8; i++, slot++) {
        if (slot->used == 0) {
            return slot;
        }
    }
    return 0;
}

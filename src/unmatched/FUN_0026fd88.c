/* Returns the first free entry (word +4 clear) of the 40-entry table DAT_0056e0e0 (8-byte
 * entries), or 0 when it is full. */
typedef struct Entry_26fd88 {
    int key;    /* 0x00 */
    int value;  /* 0x04 */
} Entry_26fd88;

extern Entry_26fd88 DAT_0056e0e0[40];

Entry_26fd88 *FUN_0026fd88(void) {
    int i;

    for (i = 0; i < 40; i++) {
        if (DAT_0056e0e0[i].value == 0) {
            break;
        }
    }
    if (i == 40) {
        return 0;
    }
    return &DAT_0056e0e0[i];
}

/* Stores value under name in a free slot of the DAT_0056dfd4 table; returns 0, -1 without a table,
 * or -2 when no slot is free. */
/* A 16-byte named slot of the table DAT_0056dfd4 points at (FUN_0026f350 finds a free one, FUN_0026f3a0 one by name). */
typedef struct NamedValue_26f438 {
    char name[12];      /* 0x00: empty when name[0] == 0 */
    int value;          /* 0x0c */
} NamedValue_26f438;

extern NamedValue_26f438 *DAT_0056dfd4;
NamedValue_26f438 *FUN_0026f350(void);
char *strncpy(char *dst, const char *src, unsigned int size);

int FUN_0026f438(const char *name, int value) {
    NamedValue_26f438 *slot;

    if (DAT_0056dfd4 == 0) {
        return -1;
    }
    slot = FUN_0026f350();
    if (slot == 0) {
        return -2;
    }
    strncpy(slot->name, name, 12);
    slot->value = value;
    return 0;
}

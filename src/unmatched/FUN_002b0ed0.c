/* Checked setter (error 0xFF000192; 0xFF000602 in mode 8): sets list item `index` with
 * FUN_002b1348(item, a, 0, b, c) and re-registers it through FUN_0029dcc8. */
void FUN_0029dcc8();
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002b1348();

/* The three-item list reset by FUN_002b12a8 and its header at obj+8520 (FUN_002b1278). */
struct ListItem {
    int f0, f4, f8, f12;
};

struct ItemList {
    int count;
    struct ListItem items[3];
};

struct ListHeader {
    char pad[8];
    struct ItemList *list;                /* +8 */
    int f12;
    int mode;                             /* +16: 8 rejects changes; passed to FUN_0029dcc8 */
};

/* FUN_002a0dd8(handle) records the handle in a global and returns -1 when it is null or its word at +72 is clear (asm/FUN_002a0dd8.s). */
int FUN_002b0ed0(char *obj, int index, int a, int b, int c) {
    struct ListHeader *header = (struct ListHeader *)(obj + 8520);
    int mode;
    struct ListItem *item;
    struct ItemList *list;
    long status;

    /* matching construct: permuter — holding the guard's result in a 64-bit local changes scheduling of the error block to retail's order */
    status = FUN_002a0dd8(obj);
    if (status != 0) {
        return FUN_002a0bb8(0, 0xFF000192);
    }
    /* The list pointer is read before the mode test, as retail does. */
    mode = header->mode;
    list = header->list;
    if (mode == 8) {
        return FUN_002a0bb8(obj, 0xFF000602);
    }
    item = &list->items[index];
    FUN_002b1348(item, a, 0, b, c);
    FUN_0029dcc8(obj, mode, index, item);
    return 0;
}

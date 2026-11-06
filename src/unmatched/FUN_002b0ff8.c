/* Checked setter (error 0xFF000191; 0xFF000602 in mode 8): sets list item `index` with
 * FUN_002b1348(item, a, b, 0, 0) and re-registers it through FUN_0029dcc8. */
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

/* FUN_002a0dd8(handle) records the handle in a global and returns -1 when it is null or its word
 * at +72 is clear. */
int FUN_002b0ff8(char *obj, int index, int a, int b) {
    struct ListHeader *header = (struct ListHeader *)(obj + 8520);
    int mode;
    struct ListItem *item;
    struct ItemList *list;

    if (FUN_002a0dd8(obj) != 0) {
        return FUN_002a0bb8(0, 0xFF000191);
    }
    /* The list pointer is read before the mode test, as retail does. */
    mode = header->mode;
    list = header->list;
    if (mode == 8) {
        return FUN_002a0bb8(obj, 0xFF000602);
    }
    item = &list->items[index];
    FUN_002b1348(item, a, b, 0, 0);
    FUN_0029dcc8(obj, mode, index, item);
    return 0;
}

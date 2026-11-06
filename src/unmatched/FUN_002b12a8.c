/* Empties a three-item list: clears its count, resets each 16-byte item with FUN_002b1320 and
 * registers it with FUN_0029dcc8(owner, arg2, index, item). */
void FUN_0029dcc8();
int FUN_002b1320();

struct ListItem {
    int f0, f4, f8, f12;
};

struct ItemList {
    int count;
    struct ListItem items[3];
};

/* matching construct: permuter — FUN_0029dcc8 declared void (its result is unused) leaves v0 free for the loop test, as in retail */
void FUN_002b12a8(int owner, struct ItemList *list, int arg2) {
    int i;

    list->count = 0;
    for (i = 0; i < 3; i++) {
        FUN_002b1320(&list->items[i]);
        FUN_0029dcc8(owner, arg2, i, &list->items[i]);
    }
}

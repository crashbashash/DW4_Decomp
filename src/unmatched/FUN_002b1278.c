/* Points the header at +8520 at the item list at +13808 and resets that list with FUN_002b12a8;
 * returns 0. */
int FUN_002b12a8();

struct ListHeader {
    char pad[8];
    int list;                             /* +8: address of the list at obj+13808 */
    int f12;
    int f16;                              /* passed through to FUN_002b12a8 */
};

int FUN_002b1278(char *obj) {
    /* matching construct: permuter — declaring header before list gives retail's v0 copy of obj */
    struct ListHeader *header = (struct ListHeader *)(obj + 8520);
    char *list = obj + 13808;

    header->list = (int)list;
    FUN_002b12a8(obj, list, header->f16);
    return 0;
}

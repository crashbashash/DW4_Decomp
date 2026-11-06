/* If the entry at +8200 is not yet in state 1 while the one at +8196 is, and FUN_0029c090 agrees,
 * calls FUN_0029ea28(obj, entry, 1). */
extern int FUN_0029c090(void *obj);
extern void FUN_0029ea28(void *obj, int entry, int state);
extern int FUN_0029ea48(void *obj, int entry);

void FUN_0029bfe8(char *obj) {
    char *block = obj + 8180;
    int entry20 = *(int *)(block + 20);
    int entry16 = *(int *)(block + 16);

    if (FUN_0029ea48(obj, entry20) != 1 && FUN_0029ea48(obj, entry16) == 1 && FUN_0029c090(obj) != 0) {
        FUN_0029ea28(obj, entry20, 1);
    }
}

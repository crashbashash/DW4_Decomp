/* Lazily creates the singleton when it is missing or its ready flag (bit 2 of the word at +36) is
 * clear, then returns it. */
extern "C" {
int FUN_0036b6e0();
extern void * DAT_00589e30[4];
void *FUN_0036b650(void);
}

void *FUN_0036b650(void) {
    unsigned char b;
    if (DAT_00589e30[0] != 0) {
        b = (*(int *)((char *)(DAT_00589e30[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0036b6e0();
done:
    return DAT_00589e30[0];
}

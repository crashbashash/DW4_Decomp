/* Lazily creates the singleton when it is missing or its ready flag (bit 2 of the word at +36) is
 * clear, then returns it. */
extern "C" {
int FUN_00360620();
extern void * DAT_00589590[4];
void *FUN_003604f0(void);
}

void *FUN_003604f0(void) {
    unsigned char b;
    if (DAT_00589590[0] != 0) {
        b = (*(int *)((char *)(DAT_00589590[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00360620();
done:
    return DAT_00589590[0];
}

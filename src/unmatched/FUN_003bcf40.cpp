/* Lazily creates the singleton when it is missing or its ready flag (bit 2 of the word at +36) is
 * clear, then returns it. */
extern "C" {
int FUN_003bd000();
extern void * DAT_0058b180[4];
void *FUN_003bcf40(void);
}
void *FUN_003bcf40(void) {
    unsigned char b;
    if (DAT_0058b180[0] != 0) {
        b = (*(int *)((char *)(DAT_0058b180[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003bd000();
done:
    return DAT_0058b180[0];
}

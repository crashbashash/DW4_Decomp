/* Lazily creates the singleton when it is missing or its ready flag (bit 2 of the word at +36) is
 * clear, then returns it. */
extern "C" {
int FUN_0036d740();
extern void * DAT_00589fe8[4];
void *FUN_0036d5e0(void);
}

void *FUN_0036d5e0(void) {
    unsigned char b;
    if (DAT_00589fe8[0] != 0) {
        b = (*(int *)((char *)(DAT_00589fe8[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0036d740();
done:
    return DAT_00589fe8[0];
}

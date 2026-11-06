/* Lazily creates the singleton when it is missing or its ready flag (bit 2 of the word at +36) is
 * clear, then returns it. */
extern "C" {
int FUN_00364ea0();
extern void * DAT_00589888[4];
void *FUN_00364d70(void);
}

void *FUN_00364d70(void) {
    unsigned char b;
    if (DAT_00589888[0] != 0) {
        b = (*(int *)((char *)(DAT_00589888[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00364ea0();
done:
    return DAT_00589888[0];
}

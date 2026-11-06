/* FUN_0034a050 (0x0034a050): lazily creates the singleton when it is missing or its ready flag
 * (bit 2 of the word at +36) is clear, then returns it. Needs the pinned alternate compiler with
 * -O3,p: its branch-target alignment gives the extra nop of the retail body. */
extern "C" {
int FUN_0034a0a0();
extern void * DAT_00588298[4];
void *FUN_0034a050(void);
}

void *FUN_0034a050(void) {
    unsigned char b;
    if (DAT_00588298[0] != 0) {
        b = (*(int *)((char *)(DAT_00588298[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0034a0a0();
done:
    return DAT_00588298[0];
}

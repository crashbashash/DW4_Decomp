/* FUN_00355a40 (0x00355a40): lazily creates the singleton when it is missing or its ready flag
 * (bit 2 of the word at +36) is clear, then returns it. Needs the pinned alternate compiler with
 * -O3,p: its branch-target alignment gives the extra nop of the retail body. */
extern "C" {
int FUN_00355b20();
extern void * DAT_00588df0[4];
void *FUN_00355a40(void);
}

void *FUN_00355a40(void) {
    unsigned char b;
    if (DAT_00588df0[0] != 0) {
        b = (*(int *)((char *)(DAT_00588df0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00355b20();
done:
    return DAT_00588df0[0];
}

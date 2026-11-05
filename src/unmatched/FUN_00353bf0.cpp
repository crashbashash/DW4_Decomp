/* FUN_00353bf0 (0x00353bf0): lazily creates the singleton when it is missing or its
 * ready flag (bit 2 of the word at +36) is clear, then returns it.  Needs the
 * pinned alternate compiler with -O3,p (config/SLUS-20836/unit-compilers.tsv): its
 * branch-target alignment gives the extra nop of the retail body. */
extern "C" {
int FUN_00353cd0();
extern void * DAT_00588c30[4];
void *FUN_00353bf0(void);
}

void *FUN_00353bf0(void) {
    unsigned char b;
    if (DAT_00588c30[0] != 0) {
        b = (*(int *)((char *)(DAT_00588c30[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00353cd0();
done:
    return DAT_00588c30[0];
}

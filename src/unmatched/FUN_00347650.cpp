extern "C" {
/* FUN_00347650 (0x00347650): lazily creates the singleton when it is missing or its
 * ready flag (bit 2 of the word at +36) is clear, then returns it.  Needs the
 * pinned alternate compiler with -O3,p (config/SLUS-20836/unit-compilers.tsv): its
 * branch-target alignment gives the extra nop of the retail body. */
int FUN_003476e0();
extern void * DAT_00588070[4];
void *FUN_00347650(void) {
    unsigned char b;
    if (DAT_00588070[0] != 0) {
        b = (*(int *)((char *)(DAT_00588070[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003476e0();
done:
    return DAT_00588070[0];
}
}

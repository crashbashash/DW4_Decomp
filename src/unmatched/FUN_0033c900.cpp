extern "C" {
/* FUN_0033c900 (0x0033c900): lazily creates the singleton when it is missing or its
 * ready flag (bit 2 of the word at +36) is clear, then returns it.  Needs the
 * pinned alternate compiler with -O3,p (config/SLUS-20836/unit-compilers.tsv): its
 * branch-target alignment gives the extra nop of the retail body. */
int FUN_0033e350();
extern void * DAT_005878e0[4];
void *FUN_0033c900(void) {
    unsigned char b;
    if (DAT_005878e0[0] != 0) {
        b = (*(int *)((char *)(DAT_005878e0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0033e350();
done:
    return DAT_005878e0[0];
}
}

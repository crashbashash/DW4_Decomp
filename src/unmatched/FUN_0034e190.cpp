/* FUN_0034e190 (0x0034e190): lazily creates the singleton when it is missing or its
 * ready flag (bit 2 of the word at +36) is clear, then returns it.  Needs the
 * pinned alternate compiler with -O3,p (config/SLUS-20836/unit-compilers.tsv): its
 * branch-target alignment gives the extra nop of the retail body. */
extern "C" {
int FUN_0034e250();
extern void * DAT_005886d0[4];
void *FUN_0034e190(void);
}

void *FUN_0034e190(void) {
    unsigned char b;
    if (DAT_005886d0[0] != 0) {
        b = (*(int *)((char *)(DAT_005886d0[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0034e250();
done:
    return DAT_005886d0[0];
}

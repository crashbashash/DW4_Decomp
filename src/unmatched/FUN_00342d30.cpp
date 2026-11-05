extern "C" {
/* FUN_00342d30 (0x00342d30): lazily creates the singleton when it is missing or its
 * ready flag (bit 2 of the word at +36) is clear, then returns it.  Needs the
 * pinned alternate compiler with -O3,p (config/SLUS-20836/unit-compilers.tsv): its
 * branch-target alignment gives the extra nop of the retail body. */
int FUN_00342f30();
extern void * DAT_00587d08[4];
void *FUN_00342d30(void) {
    unsigned char b;
    if (DAT_00587d08[0] != 0) {
        b = (*(int *)((char *)(DAT_00587d08[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00342f30();
done:
    return DAT_00587d08[0];
}
}

/* FUN_00362c00 (0x00362c00): lazily creates the singleton when it is missing or its
 * ready flag (bit 2 of the word at +36) is clear, then returns it.  Needs the
 * pinned alternate compiler with -O3,p (config/SLUS-20836/unit-compilers.tsv): its
 * branch-target alignment gives the extra nop of the retail body. */
extern "C" {
int FUN_00362ce0();
extern void * DAT_00589760[4];
void *FUN_00362c00(void);
}

void *FUN_00362c00(void) {
    unsigned char b;
    if (DAT_00589760[0] != 0) {
        b = (*(int *)((char *)(DAT_00589760[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00362ce0();
done:
    return DAT_00589760[0];
}

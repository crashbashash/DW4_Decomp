extern "C" {
/* FUN_00334a00 (0x00334a00): lazily creates the singleton when it is missing or its ready flag
 * (bit 2 of the word at +36) is clear, then returns it. Needs the pinned alternate compiler with
 * -O3,p: its branch-target alignment gives the extra nop of the retail body. */
int FUN_00334a90();
extern void * DAT_00587650[4];
void *FUN_00334a00(void) {
    unsigned char b;
    if (DAT_00587650[0] != 0) {
        b = (*(int *)((char *)(DAT_00587650[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00334a90();
done:
    return DAT_00587650[0];
}
}

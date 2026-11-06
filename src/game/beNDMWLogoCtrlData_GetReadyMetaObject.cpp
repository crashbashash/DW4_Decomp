/* Lazily creates the singleton when it is missing or its ready flag (bit 2 of the word at +36) is
 * clear, then returns it. */
extern "C" {
int FUN_003c2120();
extern void * DAT_0058b530[4];
void *beNDMWLogoCtrlData_GetReadyMetaObject(void);
}
void *beNDMWLogoCtrlData_GetReadyMetaObject(void) {
    unsigned char b;
    if (DAT_0058b530[0] != 0) {
        b = (*(int *)((char *)(DAT_0058b530[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003c2120();
done:
    return DAT_0058b530[0];
}

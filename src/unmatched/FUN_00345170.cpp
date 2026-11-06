extern "C" {
int FUN_00345230();
extern void * DAT_00587f28[4];
void *FUN_00345170(void) {
    unsigned char b;
    if (DAT_00587f28[0] != 0) {
        b = (*(int *)((char *)(DAT_00587f28[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00345230();
done:
    return DAT_00587f28[0];
}
}

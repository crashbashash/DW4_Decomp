extern "C" {
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

int FUN_0028eb38(void *handle, int error);

extern int DAT_004f2a90;
extern unsigned char DAT_004f2aa0;

int FUN_00290ca8(void) {
    if (DAT_004f2a90 != 0x5a5a5a5a) {
        return FUN_0028eb38(0, 0xff03ff02);
    }
    if (DAT_004f2aa0 != 4) {
        for (;;) {
            ((void (*)(void))-1)();
        }
    }
    return 0;
}

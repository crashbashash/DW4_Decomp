/* 0x002d31d0 - FUN_002d31d0. byte stores, forwarded second argument (dropped argument) Verified byte-identical by tools/verify.py. */
int strncpy();
extern void * DAT_004c1eb8[4];
void FUN_002d31d0(void *arg0, char *arg1) {
    if (arg1 != 0) {
        strncpy((char *)arg0 + 0x90, arg1, 0x7F);
        *((char *)arg0 + 271) = 0;
    } else {
        *((char *)arg0 + 144) = 0;
    }
    if ((arg1 != 0) && (*arg1 != 0)) {
        DAT_004c1eb8[0] = (void *)((char *)arg0 + 0x90);
    }
}

int Memory_FreeBufferAliasB();
extern int DAT_00530618[4];
void *FUN_002da940(void *arg0, long long arg1) {
    if (arg0 != 0) {
        *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasB();
        }
    }
    return arg0;
}

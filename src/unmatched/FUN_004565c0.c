/* 0x004565c0 - FUN_004565c0. Recursive walk to the first node whose entry has the flag byte set. Verified byte-identical by tools/verify.py. */
void *FUN_004565c0(int arg0, void *arg1) {
    if (arg1 == 0) {
        return 0;
    }
    if (*(unsigned char *)(*(int *)((char *)arg1 + 16) + 28) != 0) {
        return arg1;
    }
    return FUN_004565c0(arg0, *(void **)((char *)arg1 + 24));
}

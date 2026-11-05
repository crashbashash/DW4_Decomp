void FUN_00337410(unsigned long long *arg0, unsigned arg1, unsigned arg2, unsigned arg3, unsigned arg4, unsigned arg5, unsigned arg6) {
    *arg0 = (unsigned long long)arg6 | (((unsigned long long)arg5 << 26) | (((unsigned long long)arg4 << 28) | (((unsigned long long)arg3 << 31) | (((unsigned long long)arg1 << 63) | ((unsigned long long)(arg2 & ~0xFU) << 32)))));
}

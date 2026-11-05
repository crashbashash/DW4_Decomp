extern char DAT_004f7910[];

int Gap__Core__igMemoryPoolContextInfo__vfunc_54(int arg0, int arg1) {
    if ((arg1 >= 0) && (arg1 < 0x2E)) {
        return arg0 + (arg1 * 0x90) + 0x18;
    }
    return (int)&DAT_004f7910[0];
}

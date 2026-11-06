extern char DAT_00562dac[];
int FUN_001eb3f0(int arg0) {
    return *(int *)(DAT_00562dac + (arg0 << 6)) & 1;
}

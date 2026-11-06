int FUN_00102d08();

int FUN_001033f8(void *arg0, unsigned int arg1, int arg2, int arg3) {
    if (arg2 == 1) {
        return (unsigned int) *(int *)((char *)arg0 + 16) < arg1;
    }
    FUN_00102d08(arg0, arg1, arg3);
    return 0;
}

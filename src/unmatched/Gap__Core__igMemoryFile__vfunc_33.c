typedef struct S { char pad44[44]; unsigned char f2C; char pad[3]; int f30; int f34; int f38; } S;
char Gap__Core__igMemoryFile__vfunc_33(S *arg0) {
    int temp_a1;
    char r;

    if (arg0->f2C == 0) {
        return -1;
    }
    temp_a1 = arg0->f38;
    if ((arg0->f34 - temp_a1) <= 0) {
        return -1;
    }
    r = *(char *)(temp_a1 + arg0->f30);
    arg0->f38 = temp_a1 + 1;
    return r;
}

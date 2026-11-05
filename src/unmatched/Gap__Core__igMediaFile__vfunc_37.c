struct S { char pad[44]; unsigned char f44; char pad2[7]; int f52; int f56; int f60; };
int memcpy();
int strlen();
int FUN_002ec570();
int Gap__Core__igMediaFile__vfunc_37(struct S *arg0, int arg1) {
    int temp_a1;
    int temp_v0;

    if (arg1 == 0) {
        return -1;
    }
    if (arg0->f44 != 0) {
        return -1;
    }
    temp_v0 = strlen(arg1);
    temp_a1 = arg0->f56 + temp_v0;
    if (temp_a1 >= arg0->f52) {
        FUN_002ec570(arg0, temp_a1);
    }
    memcpy(arg0->f60 + arg0->f56, arg1, temp_v0);
    arg0->f56 = arg0->f56 + temp_v0;
    return temp_v0;
}

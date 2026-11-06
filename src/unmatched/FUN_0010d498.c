extern char DAT_00555fd8[];
int FUN_0010d498(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = (int)*(int *)((char *)(DAT_00555fd8) + 20);
    *(int *)((char *)(DAT_00555fd8) + 24) = arg1;
    *(int *)((char *)(DAT_00555fd8) + 20) = arg0;
    return temp_v0;
}

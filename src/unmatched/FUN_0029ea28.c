/* Returns the scaled index so the scratch chain uses v0. */
int FUN_0029ea28(int arg0, int arg1, int arg2) {
    arg1 = arg1 * 0x74;
    arg0 = arg0 + arg1;
    *(int *)((char *)arg0 + 4880) = arg2;
    return arg1;
}

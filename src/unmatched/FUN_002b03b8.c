/* Returns the scaled index so the scratch chain uses v0. */
int FUN_002b03b8(int arg0, int arg1, int arg2) {
    arg1 = arg1 * 0x44;
    arg0 = arg0 + arg1;
    *(int *)((char *)arg0 + 7980) = arg2;
    return arg1;
}

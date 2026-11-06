/* Matched with tools/dispatcher/regalloc.py: retail loads *arg0 before *arg1, so the unsigned
 * comparison is written `(*arg0 - 8) > (*arg1 - 8)`. */
int FUN_00229f70(int *arg0, int *arg1) {
    return (unsigned int) (*arg0 - 8) > (unsigned int) (*arg1 - 8);
}

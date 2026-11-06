/* The parameter is reused for the loaded index and then for the scaled index, which fills the
 * branch delay slot. */
extern int *DAT_00561168[4];
void FUN_0018fed0(int arg0, int arg1) {
    int *list = DAT_00561168[0];
    int n = list[2];
    arg0 = *(int *)(arg0 + 8);
    if (n != 0 && arg0 >= 0 && arg0 < n) {
        arg0 = arg0 * 4;
        *(int *)(list[4] + arg0) = arg1;
    }
}

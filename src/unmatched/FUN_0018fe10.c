/* 0018fe10 — bounds-checked store of arg1 into slot [arg0->+8] of the global list's data table (list->+8 is the count, +16 the data). The parameter is reused for the loaded index and then for the scaled index, which fills the branch delay slot and keeps a0 as retail. */
extern int *DAT_00561150[4];
void FUN_0018fe10(int arg0, int arg1) {
    int *list = DAT_00561150[0];
    int n = list[2];
    arg0 = *(int *)(arg0 + 8);
    if (n != 0 && arg0 >= 0 && arg0 < n) {
        arg0 = arg0 * 4;
        *(int *)(list[4] + arg0) = arg1;
    }
}

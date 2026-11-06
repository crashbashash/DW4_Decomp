struct It { int cur; int key; unsigned int idx; };
extern unsigned int DAT_004986a8[4];
extern int DAT_0056dea0[4];
extern int *DAT_0056dea8[4];
extern int DAT_0056deb0[4];
struct It *FUN_00244650(struct It *arg0) {
    int *tbl;
    arg0->cur = DAT_0056dea0[0];
    DAT_0056deb0[0] += 1;
    arg0->key = 0;
    arg0->idx = 0;
    while (arg0->key == 0 && arg0->idx < DAT_004986a8[0] && (tbl = DAT_0056dea8[0]) != 0) {
        arg0->key = tbl[arg0->idx++];
    }
    return arg0;
}

struct E { char p[92]; int n; };
int FUN_00304430();
int FUN_00304680();
int FUN_00320f70();
int FUN_00322240();
extern int DAT_004fe6c0[4];
void Gap__Core__igElfFile__vfunc_32(struct E *arg0) {
    int temp_a1;
    int i;

    temp_a1 = arg0->n;
    FUN_00304430(&DAT_004fe6c0[0], temp_a1, temp_a1);
    FUN_00304680();
    for (i = 0; i < arg0->n; i++) {
        FUN_00322240(arg0, i, FUN_00320f70(arg0, i));
    }
}

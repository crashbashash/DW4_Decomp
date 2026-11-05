int FUN_00300490();
int FUN_00304430();
int FUN_00304680();
extern int DAT_004faef0[4];
struct O { int p0; int p1; int f8; int f12; };
void FUN_003039b0(struct O *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;
    FUN_00304430(&DAT_004faef0[0], arg3, arg0->f12, *(int *)(arg1 + arg0->f8));
    FUN_00304680();
    if (arg2 != 0) {
        temp_a0 = *(int *)(arg1 + arg0->f8);
        if (temp_a0 != 0) {
            FUN_00300490(temp_a0, arg2, arg3);
        }
    }
}

struct S { char pad[1544]; long long v; };
int FUN_001e8b40(long long);
extern int DAT_00560a00[4];
void FUN_00175790(struct S *arg0, long long arg1) {
    if (arg0->v == arg1) {
        DAT_00560a00[0] += 1;
    }
    arg0->v = arg1;
    FUN_001e8b40(arg1);
}

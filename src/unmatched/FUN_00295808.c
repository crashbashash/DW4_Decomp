int FUN_00277278();
int FUN_00294ef8();
int FUN_00299a90();
int FUN_0029a320();
int FUN_0029b018();
int FUN_0029b340();
int FUN_002abe98();
extern int DAT_004f3818[4];
void FUN_00295808(void *arg0) {
    int temp_s1;
    int temp_v0;

    temp_s1 = *(int *)((char *)(arg0) + 64);
    if (temp_s1 == 0) {
        return;
    }
    FUN_0029b018();
    *(int *)((char *)(arg0) + 8) = 0;
    if (FUN_002abe98(temp_s1) != 0) {
        FUN_00294ef8(-0x134);
        FUN_0029a320(&DAT_004f3818[0]);
    }
    FUN_00299a90((char *)arg0 + 0x294);
    *(int *)((char *)(arg0) + 692) = 0;
    temp_v0 = *(int *)((char *)(arg0) + 68);
    if (temp_v0 != 0) {
        FUN_0029b340(temp_v0);
    }
    FUN_00277278(*(int *)((char *)(arg0) + 76));
}

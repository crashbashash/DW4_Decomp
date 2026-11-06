int FUN_00277278();
int FUN_00295808();
int FUN_002968c0();
int FUN_002995e0();
int FUN_0029a320();
extern int DAT_004f3838[4];
void FUN_002958a0(void *arg0) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f3838[0]);
        return;
    }
    FUN_00295808(arg0);
    FUN_002995e0(arg0, 0);
    *(int *)((char *)(arg0) + 120) = 0;
    FUN_00277278(*(int *)((char *)(arg0) + 76));
}

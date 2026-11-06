int FUN_00277278();
int FUN_002968c0();
int FUN_00298f80();
int FUN_00299010();
int FUN_00299310();
int FUN_0029a320();
extern int DAT_004f4888[4];
void FUN_00299398(void *arg0, int arg1, int arg2, int arg3) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f4888[0]);
        return;
    }
    FUN_00277278(*(int *)((char *)(arg0) + 76));
    FUN_00299310(arg0, arg1, arg2, arg3);
    FUN_00299010(arg0, 1);
    FUN_00298f80(arg0);
}

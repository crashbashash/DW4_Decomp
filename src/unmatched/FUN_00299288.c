int FUN_00277278();
int FUN_002968c0();
int FUN_00298f80();
int FUN_00299010();
int FUN_002991c8();
int FUN_0029a320();
extern int DAT_004f4820[4];
void FUN_00299288(void *arg0, int arg1, int arg2) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f4820[0]);
        return;
    }
    FUN_00277278(*(int *)((char *)(arg0) + 76));
    FUN_002991c8(arg0, arg1, arg2);
    FUN_00299010(arg0, 1);
    FUN_00298f80(arg0);
}

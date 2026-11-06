int FUN_00267540();
int FUN_00267580();
extern int DAT_004a5d58[4];
extern int DAT_004ee3e8[4];
int FUN_00267738(int arg0, int arg1, int arg2) {
    if (DAT_004a5d58[0] == 0) {
        FUN_00267540();
    }
    FUN_00267580(&DAT_004ee3e8[0], 6, arg0, arg1, arg2);
    return 0;
}

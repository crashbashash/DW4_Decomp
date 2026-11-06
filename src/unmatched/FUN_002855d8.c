int FUN_00285628();
extern int DAT_004bcc50[4];
int FUN_002855d8(int arg0, int arg1) {
    if (arg0 == 0) {
        FUN_00285628(&DAT_004bcc50[0]);
    } else {
        FUN_00285628(arg0 + 4);
    }
    return arg1;
}

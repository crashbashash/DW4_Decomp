extern int DAT_0048ac40[];
extern int DAT_0048acb0[];
int FUN_0017a2b0(int arg0) {
    if (arg0 & 0x10000) {
        return DAT_0048acb0[arg0 & 0xFFFF];
    }
    return DAT_0048ac40[arg0];
}

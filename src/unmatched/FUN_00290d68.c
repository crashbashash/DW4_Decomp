int FUN_0028b350();
int FUN_00290db8();
extern int DAT_004bccd4[4];
extern int DAT_004bcce0[4];
void FUN_00290d68(int arg0) {
    FUN_00290db8();
    if (arg0 != 0) {
        FUN_0028b350(arg0, &DAT_004bcce0[0], 0x100);
        DAT_004bccd4[0] = arg0 + 0x180;
    }
}

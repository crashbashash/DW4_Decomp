int FUN_001198a8();
extern int DAT_00485190[4];
int FUN_001199d0(int p0, int p1, int p2) {
    int temp_v0;

    temp_v0 = FUN_001198a8(p0, p1, p2, 0x40);
    if (temp_v0 == 0) {
        DAT_00485190[0] = 0xB;
    }
    return temp_v0;
}

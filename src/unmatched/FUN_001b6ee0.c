int Matrix44_Copy(int);
int FUN_00191f30(int *, int, int);

void FUN_001b6ee0(int arg0, int arg1) {
    int sp3C;

    Matrix44_Copy(arg0 + 0x64);
    FUN_00191f30(&sp3C, arg0 + 0xA4, arg1);
}

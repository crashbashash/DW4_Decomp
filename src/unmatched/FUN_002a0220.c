int FUN_002a0150();
int FUN_002a0288();
int FUN_002a02d8();
int FUN_002a08f8();

void FUN_002a0220(int arg0) {
    int temp_s0;
    int temp_v0;

    temp_s0 = arg0 + 0x78;
    temp_v0 = FUN_002a0288();
    if (temp_v0 != 0) {
        FUN_002a0150(temp_s0, temp_v0);
        FUN_002a02d8(temp_s0);
        FUN_002a08f8(arg0);
    }
}

int memcpy(int, int, int);
int FUN_00330730(int, int);

int FUN_001eeed0(int arg0) {
    int temp_v0;

    temp_v0 = FUN_00330730(0x38, 0xB);
    memcpy(temp_v0, arg0, 0x38);
    return temp_v0;
}

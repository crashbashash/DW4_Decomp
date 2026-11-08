int sceCdSync();
int FUN_002725a0();

int FUN_00272380(void) {
    int temp_s0;

    FUN_002725a0(0x2300);
    temp_s0 = sceCdSync(1);
    FUN_002725a0(0x2301);
    return temp_s0;
}

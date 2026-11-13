int _ipuFlushBits();
int FUN_00106c88();

void FUN_001073e0(int arg0) {
    while (FUN_00106c88(arg0, 1) != 0) {
        _ipuFlushBits(arg0, 8);
    }
}

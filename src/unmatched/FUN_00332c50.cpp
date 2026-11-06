extern "C" {
int FUN_002632c0();
int FUN_002648f8(void (*)(void), int);
int FUN_00264910(int);
int FUN_00280d48();
int FUN_00332860();
int FUN_00332c40();
void FUN_003327b0(void);
int FUN_00332c50(int arg0) {
    int var_s0;

    var_s0 = FUN_00332860() & 0xFF;
    if ((var_s0 != 0) && (arg0 != 0)) {
        var_s0 = FUN_00332c40() & 0xFF;
    }
    FUN_00264910(0);
    FUN_002648f8(FUN_003327b0, 0);
    FUN_002632c0();
    FUN_00280d48();
    return var_s0;
}
}

/* 0x001916b0 - FUN_001916b0. Near-miss sweep fix, verified byte-identical to retail by tools/verify.py. */
int FUN_001904f0();
int FUN_00190e50();
void FUN_001916b0(int arg0) {
    int sp20[14];
    FUN_00190e50(sp20);
    FUN_001904f0(arg0, arg0, sp20);
}

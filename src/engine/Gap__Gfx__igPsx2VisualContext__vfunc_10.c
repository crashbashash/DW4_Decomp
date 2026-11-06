typedef struct { char pad0[80]; int f50; char pad84[238]; unsigned char f142; } S_arg0;
int FUN_00169260();
int FUN_0016a9f0();
int FUN_0016c650();
int FUN_00170510();
int FUN_001788e0();
int FUN_0017a540();
int FUN_001edf20();
int FUN_00165bb0();
int Memory_FreeBuffer();

void Gap__Gfx__igPsx2VisualContext__vfunc_10(S_arg0 *arg0) {
    int temp_a0;

    temp_a0 = arg0->f50;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        arg0->f50 = 0;
    }
    FUN_00169260(arg0, 0);
    FUN_0017a540(arg0, 0);
    FUN_0016a9f0(arg0, 0);
    FUN_00170510(arg0, 0);
    FUN_0016c650(arg0, 0);
    FUN_001788e0(arg0, 0);
    if (arg0->f142 != 0) {
        FUN_001edf20();
    }
    FUN_00165bb0(arg0);
}

/* 0x0020cc50 — FUN_0020cc50. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int DeleteSema();
int FUN_0010b9c0();
int RemoveIntcHandler();
int SignalSema();
extern int DAT_00490c04[4];
extern int DAT_00490c08[4];
extern int * DAT_0056c290[4];
extern int DAT_0056c298[4];
void FUN_0020cc50(void) {
    FUN_0010b9c0(9);
    FUN_0010b9c0(0xA);
    RemoveIntcHandler(9, DAT_00490c04[0]);
    RemoveIntcHandler(0xA, DAT_00490c08[0]);
    while (DAT_0056c290[0] != 0) {
        SignalSema(*DAT_0056c290[0]);
        DAT_0056c290[0] = (int *)(DAT_0056c290[0][2]);
    }
    DeleteSema(DAT_0056c298[0]);
}

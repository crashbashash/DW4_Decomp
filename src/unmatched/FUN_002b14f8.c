/* True when SFD_GetCond(obj, 15) is clear, else whether FUN_002afb00(obj) is set. */
int SFD_GetCond();
int FUN_002afb00();

int FUN_002b14f8(int obj) {
    if (SFD_GetCond(obj, 15) == 0) {
        return 1;
    }
    return FUN_002afb00(obj) != 0;
}

int FUN_00113990();
int GetMemorySize();
int _InitTLB();

void FUN_00113950(void) {
    if (GetMemorySize() == 0x02000000) {
        FUN_00113990();
        return;
    }
    _InitTLB();
}

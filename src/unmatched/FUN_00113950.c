int FUN_00113990();
int GetMemorySize();
int _InitTLB();

int FUN_00113950(void)
{
    int r;
    if (GetMemorySize() == 0x02000000) {
        r = FUN_00113990();
    } else {
        r = _InitTLB();
    }
    return r;
}

void thunk_InitTLB(void);
void _Exit(int status);

void FUN_001145c8(int status)
{
    thunk_InitTLB();
    _Exit(status);
}

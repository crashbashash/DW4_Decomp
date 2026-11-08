int InitTLB32MB();
int GetMemorySize();
int _InitTLB();

int InitTLB(void)
{
    int r;
    if (GetMemorySize() == 0x02000000) {
        r = InitTLB32MB();
    } else {
        r = _InitTLB();
    }
    return r;
}

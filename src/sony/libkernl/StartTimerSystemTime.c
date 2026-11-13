int DIntr(void);
int EIntr(void);
void FUN_00114800(int mode);
unsigned long long iGetTimerSystemTime(void);
void SetNextComp(unsigned long long now);

int StartTimerSystemTime(void)
{
    int state = DIntr();
    int mode = *(volatile int *)0x10001010;
    if (mode & 0x80) {
        if (state) {
            EIntr();
        }
        return 1;
    }
    FUN_00114800((mode & 0xFFFFF3FF) | 0x80);
    SetNextComp(iGetTimerSystemTime());
    if (state) {
        EIntr();
    }
    return 0;
}

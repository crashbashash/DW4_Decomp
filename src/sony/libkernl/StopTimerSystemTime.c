int DIntr(void);
int EIntr(void);
void FUN_00114800(int mode);

int StopTimerSystemTime(void)
{
    int state = DIntr();
    int mode = *(volatile int *)0x10001010;
    if (!(mode & 0x80)) {
        if (state) {
            EIntr();
        }
        return 0;
    }
    FUN_00114800(mode & 0xFFFFF37F);
    if (state) {
        EIntr();
    }
    return 1;
}

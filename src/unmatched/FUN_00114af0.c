int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_00114800(int mode);

int FUN_00114af0(void)
{
    int state = FUN_00113f20();
    int mode = *(volatile int *)0x10001010;
    if (!(mode & 0x80)) {
        if (state) {
            FUN_00113f78();
        }
        return 0;
    }
    FUN_00114800(mode & 0xFFFFF37F);
    if (state) {
        FUN_00113f78();
    }
    return 1;
}

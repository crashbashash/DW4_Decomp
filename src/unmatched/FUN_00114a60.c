int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_00114800(int mode);
unsigned long long FUN_00115060(void);
void FUN_00114b70(unsigned long long now);

int FUN_00114a60(void)
{
    int state = FUN_00113f20();
    int mode = *(volatile int *)0x10001010;
    if (mode & 0x80) {
        if (state) {
            FUN_00113f78();
        }
        return 1;
    }
    FUN_00114800((mode & 0xFFFFF3FF) | 0x80);
    FUN_00114b70(FUN_00115060());
    if (state) {
        FUN_00113f78();
    }
    return 0;
}

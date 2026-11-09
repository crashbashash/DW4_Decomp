typedef unsigned int u_int;
int FUN_00113f20(void);
int FUN_00113f78(void);
void _sceSDC(u_int start, u_int end);
void FUN_0010b7d8(u_int start, u_int end)
{
    u_int stat;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    if (stat) FUN_00113f20();
    _sceSDC(start & 0xffffffc0, end & 0xffffffc0);
    if (stat) FUN_00113f78();
}

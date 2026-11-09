typedef unsigned int u_int;
int FUN_00113f20(void);
int FUN_00113f78(void);
int _DisableDmac(int ch);
int FUN_0010ba90(int ch)
{
    u_int stat;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    if (stat) FUN_00113f20();
    ret = _DisableDmac(ch);
    __asm__ volatile("sync");
    if (stat) FUN_00113f78();
    return ret;
}

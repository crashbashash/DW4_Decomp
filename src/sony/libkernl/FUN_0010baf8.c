typedef unsigned int u_int;
int DIntr(void);
int EIntr(void);
int _EnableDmac(int ch);
int FUN_0010baf8(int ch)
{
    u_int stat;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    if (stat) DIntr();
    ret = _EnableDmac(ch);
    __asm__("sync");
    if (stat) EIntr();
    return ret;
}

typedef unsigned int u_int;
int DIntr(void);
int EIntr(void);
int _DisableIntc(int ch);
int FUN_0010b9c0(int ch)
{
    u_int stat;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    if (stat) DIntr();
    ret = _DisableIntc(ch);
    __asm__("sync");
    if (stat) EIntr();
    return ret;
}

typedef unsigned int u_int;
int DIntr(void);
int EIntr(void);
void _sceSDC(u_int start, u_int end);
void FUN_0010b7d8(u_int start, u_int end)
{
    u_int stat;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    if (stat) DIntr();
    _sceSDC(start & 0xffffffc0, end & 0xffffffc0);
    if (stat) EIntr();
}

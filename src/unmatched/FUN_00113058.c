void _sceSifLoadModule(int, int, int, int, int);
void FUN_00113058(int, int, int, int, int);
void FUN_00113058(int p0, int p1, int p2, int p3, int p4)
{
    _sceSifLoadModule(p0, p1, p2, p3, 0);
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

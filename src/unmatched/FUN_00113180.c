void _sceSifLoadElfPart(int, int, int, int);
void FUN_00113180(int, int, int, int);
void FUN_00113180(int p0, int p1, int p2, int p3)
{
    _sceSifLoadElfPart(p0, p1, p2, 1);
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

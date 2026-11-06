void FUN_001067e8(int, int);
void FUN_001054e8(int, int);
void FUN_001054e8(int p0, int p1)
{
    FUN_001067e8(p0, 3);
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

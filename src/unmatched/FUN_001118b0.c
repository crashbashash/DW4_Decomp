void FUN_001103e8(int, int);
void FUN_001118b0(int, int);
void FUN_001118b0(int p0, int p1)
{
    FUN_001103e8(p0, 21);
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

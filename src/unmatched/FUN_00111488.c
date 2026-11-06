void FUN_001103e8(int, int);
void FUN_00111488(int, int);
void FUN_00111488(int p0, int p1)
{
    FUN_001103e8(p0, 18);
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

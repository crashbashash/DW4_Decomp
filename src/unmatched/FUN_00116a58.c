void FUN_00116740(int, int, int);
void FUN_00116a58(int, int, int);
void FUN_00116a58(int p0, int p1, int p2)
{
    FUN_00116740(p0, p1, 0);
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

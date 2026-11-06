void FUN_00267378(int);
void FUN_0026c6f8(char *);
void FUN_0026c6f8(char * p0)
{
    FUN_00267378(*(int *)((char *)p0 + 4));
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

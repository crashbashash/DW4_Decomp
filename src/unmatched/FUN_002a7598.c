void FUN_0029de70(int, int, char *);
void FUN_002a7598(int, char *, int);
void FUN_002a7598(int p0, char * p1, int p2)
{
    FUN_0029de70(p0, *(int *)((char *)p0 + 8128), p1);
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

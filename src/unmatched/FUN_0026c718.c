void FUN_002673d0(int);
void FUN_0026c718(char *);
void FUN_0026c718(char * p0)
{
    FUN_002673d0(*(int *)((char *)p0 + 4));
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

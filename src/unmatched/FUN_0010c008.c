/* 0x0010c008 — FUN_0010c008: a call followed by a memory barrier (sync). */
void FUN_0010af10(int);
int FUN_0010c008(int, int, int, int);
int FUN_0010c008(int a0, int a1, int a2, int a3)
{
    FUN_0010af10(a3);
    __asm__ volatile ("sync");
    __asm__ volatile ("ei");
    return 0;
}

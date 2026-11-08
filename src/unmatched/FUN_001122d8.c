void sceSifFreeSysMemory(void);
void FUN_001122d8(void);
void FUN_001122d8(void)
{
    sceSifFreeSysMemory();
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

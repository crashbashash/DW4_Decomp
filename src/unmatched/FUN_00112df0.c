void _sceSifLoadModuleBuffer(void);
void FUN_00112df0(void);
void FUN_00112df0(void)
{
    _sceSifLoadModuleBuffer();
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

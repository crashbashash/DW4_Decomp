void FUN_0027b2b0(void);
void FUN_00277798(void);
void FUN_00277798(void)
{
    FUN_0027b2b0();
    __asm__ volatile (""); /* matching construct: tail-call barrier — ee-gcc -O2 would turn the call into a jump (`j`); retail keeps `jal` + return */
}

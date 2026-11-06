/* A call followed by a memory barrier (sync). */
void FUN_0010ac90(void);
void FUN_0010bb80(void);
void FUN_0010bb80(void)
{
    FUN_0010ac90();
    __asm__ volatile ("sync");
}

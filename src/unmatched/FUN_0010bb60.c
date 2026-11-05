/* 0x0010bb60 — FUN_0010bb60: a call followed by a memory barrier (sync). */
void FUN_0010ac80(void);
void FUN_0010bb60(void);
void FUN_0010bb60(void)
{
    FUN_0010ac80();
    __asm__ volatile ("sync");
}

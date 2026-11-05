/* 0x0010bbc0 — FUN_0010bbc0: a call followed by a memory barrier (sync). */
void FUN_0010acb0(void);
void FUN_0010bbc0(void);
void FUN_0010bbc0(void)
{
    FUN_0010acb0();
    __asm__ volatile ("sync");
}

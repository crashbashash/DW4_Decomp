void RFU086_WaitEvnetFlag(void)
{
    __asm__ volatile("li $3, 86\n\tsyscall");
}

void RFU086_WaitEvnetFlag(void)
{
    __asm__("li $3, 86\n\tsyscall");
}

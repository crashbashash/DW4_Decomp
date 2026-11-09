void RFU116_SetSyscall(void)
{
    __asm__ volatile("li $3, 116\n\tsyscall");
}

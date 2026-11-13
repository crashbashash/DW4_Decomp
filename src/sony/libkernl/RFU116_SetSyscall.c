void RFU116_SetSyscall(void)
{
    __asm__("li $3, 116\n\tsyscall");
}

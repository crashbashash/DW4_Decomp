extern unsigned long DAT_00483508;
int FUN_00113f20(void);
int FUN_00113f78(void);
static inline unsigned long readHardCounter(void) {
    unsigned long now;
    __asm__ volatile(
        ".set push\n.set noreorder\n"
        "lwu %0,0(%1)\n"
        "lw $8,0x10(%1)\n"
        "ld $10,%2\n"
        "andi $9,$8,0x800\n"
        "beq $9,$0,1f\n"
        "addiu $9,$0,2\n"
        "lwu %0,0(%1)\n"
        "daddiu $10,$10,1\n"
        "1:\n"
        "andi $8,$8,3\n"
        "dsll $10,$10,16\n"
        "movz $9,$0,$8\n"
        "or %0,%0,$10\n"
        "dsllv $9,$9,$8\n"
        "dsllv %0,%0,$9\n"
        ".set pop"
        : "=&r"(now)
        : "r"(0x10001000), "m"(DAT_00483508)
        : "$8", "$9", "$10", "memory");
    return now;
}
unsigned long GetTimerSystemTime(void) {
    unsigned long now;
    int interrupts = FUN_00113f20();
    now = readHardCounter();
    if (interrupts) FUN_00113f78();
    return now;
}

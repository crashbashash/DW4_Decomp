/* diei.c - turning interrupts off and on, reporting whether they were on. */

typedef unsigned int u_int;

/* Status.EIE */
#define SR_EIE 0x10000

int DIntr(void)
{
    u_int eie;
    u_int stat;
    __asm__("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    if (eie) {
        do {
            __asm__ volatile(".p2align 3\n"
                             "di\n"
                             "sync.p\n"
                             "mfc0 %0, $12" : "=r"(stat));
        } while (stat & SR_EIE);
    }
    return eie != 0;
}

int EIntr(void)
{
    u_int eie;
    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    __asm__("ei");
    return eie != 0;
}

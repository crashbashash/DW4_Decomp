#include "dw4/eekernel_intr.h"
extern char *D_00481e54;
int *__errno(void);
void *EndOfHeap(void);
void *sbrk(int incr)
{
    u_int stat;
    char *prev;
    char *next;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    if (stat) DI();
    next = D_00481e54 + incr;
    if ((char *)EndOfHeap() < next) {
        *__errno() = 12;
        if (stat) EI();
        return (void *)-1;
    }
    prev = D_00481e54;
    D_00481e54 = next;
    if (stat) EI();
    return prev;
}

/* eekernel_intr.h - Sony eekernel.h's EI() and DI() macros, its exact text (SDK 3.0.3 eekernel.h).
 * Kept apart from eekernel.h so its asm statements sit in one small header of their own. */
#ifndef DW4_EEKERNEL_INTR_H
#define DW4_EEKERNEL_INTR_H

typedef unsigned int u_int;

#ifndef EI
#define EI()                    __asm__ volatile("ei")
#endif
#ifndef DI
#define DI() \
{ \
      u_int stat; \
      do { \
        __asm__ volatile (".p2align 3"); \
        __asm__ volatile ("di"); \
        __asm__ volatile ("sync.p"); \
        __asm__ volatile ("mfc0 %0, $12" : "=r"(stat):); \
      } while (stat & 0x00010000); \
}
#endif

#endif

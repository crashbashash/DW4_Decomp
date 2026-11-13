/* eekernel_intr.h - Sony eekernel.h's EI() and DI() macros, its exact text (SDK 3.0.3 eekernel.h).
 * Kept apart from eekernel.h because tools/sourceapprovals.py counts a header's asm and volatile
 * against every function of every file that includes it. */
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

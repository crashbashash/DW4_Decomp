/* eekernel_gp.h - Sony eekernel.h's GetGp() and SetGp(), its exact text (SDK 3.0.3 eekernel.h).
 * Kept apart from eekernel.h because tools/sourceapprovals.py counts a header's asm and volatile
 * against every function of every file that includes it. */
#ifndef DW4_EEKERNEL_GP_H
#define DW4_EEKERNEL_GP_H

extern __inline__ void *GetGp(void);
extern __inline__ void *GetGp(void)
{
        void *gp;
        __asm__ volatile (
                "move           %0, $28\n"
                : "=r"(gp)
                :
                : "memory"
        );
        return(gp);
}
extern __inline__ void *SetGp(void *newgp);
extern __inline__ void *SetGp(void *newgp)
{
        void *oldgp;
        __asm__ volatile (
                "move           %0, $28\n"
                "move           $28, %1\n"
                : "=&r"(oldgp)
                : "r"(newgp)
                : "memory"
        );
        return(oldgp);
}

#endif

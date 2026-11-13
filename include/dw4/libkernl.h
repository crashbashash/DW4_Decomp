/* libkernl.h - what Sony libkernl's files share: the kernel patch tables and the interrupt switches. */
#ifndef DW4_LIBKERNL_H
#define DW4_LIBKERNL_H

/* One row of a patch file's system-call table: the call number and the kernel-side handler that
 * `setup` installs for it; a row whose handler is 0 is restored to the kernel's own entry. */
typedef struct {
    int number;
    void *handler;
} SyscallEntry;

int DIntr(void);
int EIntr(void);
void FlushCache(int mode);

#endif

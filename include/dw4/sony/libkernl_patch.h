/* libkernl_patch.h - the system-call table row libkernl's kernel patches and the EE-side files that
 * install them share. The patches run in the kernel and name kernel routines (InitTimer, ...) that
 * the EE library also defines, so they include this, not libkernl.h. */
#ifndef DW4_LIBKERNL_PATCH_H
#define DW4_LIBKERNL_PATCH_H

/* One row of a patch file's system-call table: the call number and the kernel-side handler that
 * `setup` installs for it; a row whose handler is 0 is restored to the kernel's own entry. */
typedef struct {
    int number;
    void *handler;
} SyscallEntry;

#endif

/* libkernl.h - what Sony libkernl's files share and export: the kernel patch tables, the interrupt
 * and DMA-channel switches, data-cache maintenance and the kernel printf. */
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
int DisableIntc(int cause);
int EnableIntc(int cause);
int DisableDmac(int channel);
int EnableDmac(int channel);
/* Write back (Sync) or discard (Invalid) the data-cache lines covering [start, end]; the i form is
 * for interrupt handlers. */
void SyncDCache(void *start, void *end);
void iSyncDCache(void *start, void *end);
void InvalidDCache(void *start, void *end);
void scePrintf(const char *format, ...);
void kprintf(const char *format, ...);

#endif

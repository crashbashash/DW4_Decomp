/* cache.c - libkernl's data-cache maintenance by address range. The EE data cache is 8 KB, two ways
 * of 64 lines of 64 bytes; each walk reads every line's tag (TagLo, COP0 $28) and writes back or
 * invalidates the lines whose address falls in [start, end]. */

typedef unsigned int u_int;

#define DCACHE_WAY_SIZE 4096
#define DCACHE_LINE_SIZE 64
#define DCACHE_LINE_MASK 0xffffffc0
#define DCACHE_TAG_MASK 0xfffff000
#define STATUS_EIE 0x10000

int DIntr(void);
int EIntr(void);

/* write back and invalidate */
void _sceSDC(u_int start, u_int end)
{
    int i;
    u_int tag;
    for (i = 0; i < DCACHE_WAY_SIZE; i += DCACHE_LINE_SIZE) {
        __asm__("sync\n\tcache 0x10, 0(%1)\n\tsync\n\tmfc0 %0, $28" : "=r"(tag) : "r"(i));
        tag = (tag & DCACHE_TAG_MASK) + i;
        if (!(tag < start) && !(end < tag)) {
            __asm__("sync\n\tcache 0x14, 0(%0)\n\tsync" : : "r"(i));
        }
        __asm__("sync\n\tcache 0x10, 1(%1)\n\tsync\n\tmfc0 %0, $28" : "=r"(tag) : "r"(i));
        tag = (tag & DCACHE_TAG_MASK) + i;
        if (!(tag < start) && !(end < tag)) {
            __asm__("sync\n\tcache 0x14, 1(%0)\n\tsync" : : "r"(i));
        }
        __asm__("sync");
    }
}

void SyncDCache(u_int start, u_int end)
{
    u_int stat;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= STATUS_EIE;
    if (stat) DIntr();
    _sceSDC(start & DCACHE_LINE_MASK, end & DCACHE_LINE_MASK);
    if (stat) EIntr();
}

void iSyncDCache(u_int start, u_int end)
{
    _sceSDC(start & DCACHE_LINE_MASK, end & DCACHE_LINE_MASK);
}

/* invalidate without write-back */
void _sceIDC(u_int start, u_int end)
{
    int i;
    u_int tag;
    for (i = 0; i < DCACHE_WAY_SIZE; i += DCACHE_LINE_SIZE) {
        __asm__("sync\n\tcache 0x10, 0(%1)\n\tsync\n\tmfc0 %0, $28" : "=r"(tag) : "r"(i));
        tag = (tag & DCACHE_TAG_MASK) + i;
        if (!(tag < start) && !(end < tag)) {
            __asm__("sync\n\tcache 0x16, 0(%0)\n\tsync" : : "r"(i));
        }
        __asm__("sync\n\tcache 0x10, 1(%1)\n\tsync\n\tmfc0 %0, $28" : "=r"(tag) : "r"(i));
        tag = (tag & DCACHE_TAG_MASK) + i;
        if (!(tag < start) && !(end < tag)) {
            __asm__("sync\n\tcache 0x16, 1(%0)\n\tsync" : : "r"(i));
        }
        __asm__("sync");
    }
}

void InvalidDCache(u_int start, u_int end)
{
    u_int stat;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= STATUS_EIE;
    if (stat) DIntr();
    _sceIDC(start & DCACHE_LINE_MASK, end & DCACHE_LINE_MASK);
    if (stat) EIntr();
}

void iInvalidDCache(u_int start, u_int end)
{
    _sceIDC(start & DCACHE_LINE_MASK, end & DCACHE_LINE_MASK);
}

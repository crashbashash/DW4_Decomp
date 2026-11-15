/* tlbsrc.c - the TLB kernel patch. Linked to run at 0x80075000, where tlbfunc.c copies it, it adds the TLB
 * system calls to the kernel. COP0 registers: 0 Index, 2 EntryLo0, 3 EntryLo1, 5 PageMask, 6 Wired,
 * 10 EntryHi. */
#include "dw4/libkernl.h"

typedef unsigned int u_int;

#define TLB_ENTRIES 48
#define SCRATCHPAD_VADDR 0x70004000
#define SCRATCHPAD_MIN_ADDR 0x100000

int kPutTLBEntry(u_int pagemask, u_int hi, u_int lo0, u_int lo1);
int kSetTLBEntry(int index, u_int pagemask, u_int hi, u_int lo0, u_int lo1);
int kGetTLBEntry(int index, u_int *pagemask, u_int *hi, u_int *lo0, u_int *lo1);
int kProbeTLBEntry(u_int hi, u_int *pagemask, u_int *lo0, u_int *lo1);
int kExpandScratchPad(u_int addr);

/* the argument area Exit and the ExecPS2 calls fill, just past the patch (the link script defines it) */
extern char kExecArg[];

SyscallEntry kSysEntry[6] = {
    {0x55, kPutTLBEntry},
    {0x56, kSetTLBEntry},
    {0x57, kGetTLBEntry},
    {0x58, kProbeTLBEntry},
    {0x59, kExpandScratchPad},
    {3, kExecArg},
};

/* system call 91 while the patch is installed: what tlbfunc.c installs for each call number */
void *kGetEntryAddress(int number)
{
    u_int i;
    for (i = 0; i < 6; i++) {
        if (number == kSysEntry[i].number) {
            return kSysEntry[i].handler;
        }
    }
    return 0;
}

/* Writes a random TLB entry for a user-segment address; returns the entry's index. */
int kPutTLBEntry(u_int pagemask, u_int hi, u_int lo0, u_int lo1)
{
    int index;
    switch ((hi >> 24) & 0xf0) {
    case 0x00:
    case 0x20:
    case 0x30:
    case 0x40:
        break;
    case 0x10:
    case 0x50:
    case 0x70:
    default:
        return -1;
    }
    __asm__("mtc0 %1, $5\n\tmtc0 %2, $10\n\tmtc0 %3, $2\n\tmtc0 %4, $3\n\tsync.p\n\ttlbwr\n\tsync.p\n\ttlbp\n\tsync.p\n\tmfc0 %0, $0"
            : "=r"(index)
            : "r"(pagemask), "r"(hi), "r"(lo0), "r"(lo1));
    return index;
}

int kSetTLBEntry(int index, u_int pagemask, u_int hi, u_int lo0, u_int lo1)
{
    if ((u_int)index >= TLB_ENTRIES) {
        return -1;
    }
    __asm__("mtc0 %0, $0\n\tmtc0 %1, $5\n\tmtc0 %2, $10\n\tmtc0 %3, $2\n\tmtc0 %4, $3\n\tsync.p\n\ttlbwi\n\tsync.p"
            : : "r"(index), "r"(pagemask), "r"(hi), "r"(lo0), "r"(lo1));
    return index;
}

int kGetTLBEntry(int index, u_int *pagemask, u_int *hi, u_int *lo0, u_int *lo1)
{
    if ((u_int)index >= TLB_ENTRIES) {
        return -1;
    }
    __asm__ volatile("mtc0 %1, $0\n\tsync.p\n\ttlbr\n\tsync.p\n\tmfc0 %0, $5" : "=r"(*pagemask) : "r"(index));
    __asm__("mfc0 %0, $10" : "=r"(*hi));
    __asm__("mfc0 %0, $2" : "=r"(*lo0));
    __asm__("mfc0 %0, $3" : "=r"(*lo1));
    return index;
}

/* Looks up the entry mapping `hi`; returns its index, or -1 when none does. */
int kProbeTLBEntry(u_int hi, u_int *pagemask, u_int *lo0, u_int *lo1)
{
    int index;
    __asm__("mtc0 %1, $10\n\tsync.p\n\ttlbp\n\tsync.p\n\tmfc0 %0, $0" : "=r"(index) : "r"(hi));
    if (index < 0) {
        index = -1;
    } else {
        __asm__ volatile("tlbr\n\tsync.p\n\tmfc0 %0, $5" : "=r"(*pagemask));
        __asm__("mfc0 %0, $2" : "=r"(*lo0));
        __asm__("mfc0 %0, $3" : "=r"(*lo1));
    }
    return index;
}

/* Maps 8 KB of main memory at `addr` behind the scratchpad through a wired entry, or with `addr` 0 removes
 * that entry; returns the entry's index (0 after a removal). */
int kExpandScratchPad(u_int addr)
{
    u_int pagemask, lo0, lo1;
    int index, wired;
    u_int hi;

    if ((addr & 0xfff) != 0 || (addr != 0 && addr < SCRATCHPAD_MIN_ADDR)) {
        return -1;
    }
    index = kProbeTLBEntry(SCRATCHPAD_VADDR, &pagemask, &lo0, &lo1);
    if (index < 0) {
        if (addr == 0) {
            return 0;
        }
        __asm__("mfc0 %0, $6" : "=r"(index));
        wired = index + 1;
        __asm__("mtc0 %0, $6\n\tsync.p" : : "r"(wired));
    } else if (addr == 0) {
        /* park the entry on an unmapped kernel address of its own */
        hi = ((index - 1) << 13) + 0xe0010000;
        __asm__ volatile("mfc0 %0, $6" : "=r"(wired));
        wired--;
        __asm__("mtc0 %0, $6\n\tmtc0 %1, $0\n\tmtc0 $0, $5\n\tmtc0 %2, $10\n\tmtc0 $0, $2\n\tmtc0 $0, $3\n\tsync.p\n\ttlbwi\n\tsync.p"
                : : "r"(wired), "r"(index), "r"(hi));
        return 0;
    }
    pagemask = 0;
    hi = SCRATCHPAD_VADDR;
    lo0 = ((addr & 0xfffff000) >> 6) | 0x1f;
    lo1 = (((addr + 0x1000) & 0xfffff000) >> 6) | 0x1f;
    __asm__("mtc0 %0, $0" : : "r"(index));
    __asm__("mtc0 %0, $5\n\tmtc0 %1, $10\n\tmtc0 %2, $2\n\tmtc0 %3, $3\n\tsync.p\n\ttlbwi\n\tsync.p"
            : : "r"(pagemask), "r"(hi), "r"(lo0), "r"(lo1));
    return index;
}

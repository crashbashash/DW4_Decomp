typedef unsigned int u_int;
void _sceSDC(u_int start, u_int end)
{
    int i;
    u_int tag;
    for (i = 0; i < 4096; i += 64) {
        __asm__ volatile("sync\n\tcache 0x10, 0(%1)\n\tsync\n\tmfc0 %0, $28" : "=r"(tag) : "r"(i));
        tag = (tag & 0xfffff000) + i;
        if (!(tag < start) && !(end < tag)) {
            __asm__ volatile("sync\n\tcache 0x14, 0(%0)\n\tsync" : : "r"(i));
        }
        __asm__ volatile("sync\n\tcache 0x10, 1(%1)\n\tsync\n\tmfc0 %0, $28" : "=r"(tag) : "r"(i));
        tag = (tag & 0xfffff000) + i;
        if (!(tag < start) && !(end < tag)) {
            __asm__ volatile("sync\n\tcache 0x14, 1(%0)\n\tsync" : : "r"(i));
        }
        __asm__ volatile("sync");
    }
}

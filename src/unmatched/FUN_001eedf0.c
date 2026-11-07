typedef struct MemoryChunk { char pad0[12]; int f12; int f16; struct MemoryChunk *f20; } MemoryChunk;
int FUN_001eedf0(MemoryChunk *arg0) {
    int sz = arg0->f16 - arg0->f12;
    while ((arg0 = arg0->f20) != 0) {
        sz -= 16;
        sz += arg0->f16 - arg0->f12;
    }
    return sz;
}

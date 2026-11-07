class ThreadStackOwner { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual int GetStackSize(); };
struct ThreadMemoryMap {
    unsigned stackTop; int p4; int p8; int p12; int p16;
    unsigned stackBottom;
    unsigned textStart;
    unsigned textSize;
    unsigned dataStart;
    unsigned dataSize;
    unsigned bssStart;
    unsigned bssSize;
    unsigned gp;
    unsigned sbssSize;
    unsigned stackRegion;
    unsigned stackRegionSize;
    unsigned scratchpad;
    unsigned scratchpadSize;
    int p72;
    int reserved;
    int stackSize;
};
extern "C" {
extern char DAT_00100000[];
extern char DAT_000ffff0[];
extern char Gap__Bec__beFont__vfunc_32[];
extern char DAT_00481c00[];
extern char DAT_0058d280[];
extern char DAT_000d2c64[];
extern char DAT_00554e81[];
extern char DAT_000383ff[];
extern char DAT_70000000[];
extern char DAT_00004000[];
extern int DAT_00587320;
void FUN_003295d0(ThreadStackOwner *, ThreadMemoryMap *);
void FUN_0032f380(ThreadStackOwner *self, ThreadMemoryMap *map);
}
void FUN_0032f380(ThreadStackOwner *self, ThreadMemoryMap *map) {
    unsigned top;
    unsigned marker;
    unsigned bottom;
    int size;
    unsigned regionSize;
    unsigned end;
    end = (unsigned)DAT_0058d280;
    marker = end;
    regionSize = (unsigned)DAT_00100000;
    top = (unsigned)&marker;
    top -= top % regionSize;
    bottom = top - regionSize;
    size = self->GetStackSize();
    if (size == -1) {
        size = DAT_00587320;
    }
    FUN_003295d0(self, map);
    map->stackTop = top;
    map->stackBottom = bottom - size;
    map->stackSize = size;
    map->textStart = (unsigned)(DAT_000ffff0 + 16);
    map->textSize = (unsigned)(Gap__Bec__beFont__vfunc_32 + 0x90);
    map->dataStart = (unsigned)DAT_00481c00;
    map->dataSize = end - (unsigned)DAT_00481c00;
    map->bssStart = (unsigned)DAT_00481c00;
    map->bssSize = (unsigned)DAT_000d2c64;
    map->gp = (unsigned)DAT_00554e81;
    map->sbssSize = (unsigned)DAT_000383ff;
    map->stackRegion = top;
    map->stackRegionSize = regionSize;
    map->scratchpad = (unsigned)DAT_70000000;
    map->scratchpadSize = (unsigned)DAT_00004000;
    map->reserved = 0;
}

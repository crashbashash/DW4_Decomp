extern "C" {
void FUN_002ce3c0();
void *FUN_00323600(void *, void *);
void *FUN_002f0040(int, int, void *);
void *Memory_GetDefaultAllocator();
void *igObject_CloneViaMetadata(void *, void *);
extern unsigned char *DAT_00586dc8[4];
void *Gap__Core__igMallocMemoryPool__vfunc_21(void *self, void *src) {
    void *o;
    if (*DAT_00586dc8[0] != 0) {
        FUN_002ce3c0();
        return igObject_CloneViaMetadata(self, src);
    }
    o = FUN_002f0040(0xA0, 0, Memory_GetDefaultAllocator());
    if (o != 0) {
        o = FUN_00323600(o, self);
    }
    return o;
}
}

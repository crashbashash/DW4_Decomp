/* Unused vtable slots, declared only so the used ones land at their real offsets. */
#define PAD(n) virtual void pad##n();

class igMemoryPool {
public:
    PAD(0) PAD(1) PAD(2) PAD(3) PAD(4) PAD(5) PAD(6) PAD(7) PAD(8) PAD(9)
    PAD(10) PAD(11) PAD(12) PAD(13) PAD(14) PAD(15) PAD(16) PAD(17) PAD(18) PAD(19)
    PAD(20) PAD(21) PAD(22) PAD(23) PAD(24) PAD(25) PAD(26) PAD(27) PAD(28) PAD(29)
    PAD(30) PAD(31) PAD(32) PAD(33) PAD(34) PAD(35) PAD(36) PAD(37) PAD(38) PAD(39)
    PAD(40) PAD(41) PAD(42) PAD(43) PAD(44) PAD(45) PAD(46) PAD(47) PAD(48) PAD(49)
    PAD(50) PAD(51)
    virtual void *Allocate(unsigned int size);                                        /* +216 */
    virtual void *AllocateAligned(unsigned int size, unsigned int alignment);         /* +220 */
    virtual void *vfunc_54(unsigned int size, unsigned int alignment);                /* +224 */
    PAD(55)
    virtual void *Reallocate(void *block, unsigned int size);                         /* +232 */
    virtual void *ReallocateAligned(void *block, unsigned int size, unsigned int alignment); /* +236 */
    virtual int vfunc_58(void *block);                                                /* +240 */
    PAD(59) PAD(60) PAD(61) PAD(62) PAD(63)
    virtual void Free(void *block);                                                   /* +264 */
    PAD(65) PAD(66) PAD(67) PAD(68) PAD(69) PAD(70) PAD(71) PAD(72) PAD(73) PAD(74)
    PAD(75) PAD(76) PAD(77) PAD(78) PAD(79) PAD(80) PAD(81)
    virtual unsigned int GetSize(void *block);                                        /* +336 */
};

class DumpFile {
public:
    PAD(0) PAD(1) PAD(2) PAD(3) PAD(4) PAD(5) PAD(6) PAD(7) PAD(8) PAD(9)
    PAD(10) PAD(11) PAD(12) PAD(13) PAD(14) PAD(15) PAD(16) PAD(17) PAD(18) PAD(19)
    PAD(20) PAD(21) PAD(22)
    virtual int Open(const char *name, const char *mode); /* +100 */
    virtual void Close();                                 /* +104 */
    PAD(27) PAD(28) PAD(29) PAD(30)
    virtual void Print(const char *fmt, ...);             /* +124 */
    int refs; /* +4 */
};

class SystemAllocator {
public:
    PAD(0) PAD(1)
    virtual void *Allocate(unsigned int size); /* +16 */
    PAD(3) PAD(4) PAD(5) PAD(6)
    virtual void Free(void *block);            /* +36 */
};

extern "C" {
igMemoryPool *Memory_GetDefaultAllocator();
igMemoryPool *Memory_FindOwningAllocator(void *block);
int Memory_GetAllocatorBySelector(int);
void *memcpy(void *, const void *, unsigned int);
void *malloc(unsigned int size);
void free(void *block);
void FUN_0032f300(void);
int FUN_00304430(...);   /* console printf */
int FUN_00304680();      /* console flush after each print */
void *igFile_Create(int);
void igObject_Destroy(void *);
extern char DAT_004f92f0[], DAT_004f95c8[], DAT_004f9ca0[], DAT_004f9cb0[], DAT_004f9cc0[],
    DAT_004f9cc8[], DAT_004f9cd0[], DAT_004f9cd8[], DAT_004f9ce0[], DAT_004f9ce8[],
    DAT_004f9cf0[], DAT_004f9cf8[];
extern unsigned char g_useOwnerAllocator;
extern int DAT_00587028[], g_temporaryAllocatorSelector[];
extern SystemAllocator *DAT_00587218[4];

void *FUN_002ed1e0(int, unsigned int size, igMemoryPool *pool);
}

extern "C" void *Memory_AllocateBufferViaSharedTail(unsigned int size, igMemoryPool *pool);

extern "C" void *FUN_002ed1e0(int, unsigned int size, igMemoryPool *pool);

extern "C" void *Memory_AllocateDefaultBuffer(unsigned int size);

extern "C" void *Memory_AllocateBufferDirect(unsigned int size, igMemoryPool *pool);

extern "C" void *FUN_002ed260(unsigned int size, unsigned int alignment);

extern "C" void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned int alignment, igMemoryPool *pool);

extern "C" void *FUN_002ed2e0(unsigned int size, unsigned int alignment);

extern "C" void *Memory_ReallocateBuffer(void *buffer, unsigned int size);

extern "C" void *FUN_002ed3b0(void *buffer, unsigned int size, unsigned int alignment);

extern "C" void *thunk_Memory_ReallocateBuffer(void *buffer, unsigned int size);

extern "C" void *thunk_FUN_002ed3b0(void *buffer, unsigned int size, unsigned int alignment);

extern "C" void Memory_FreeBuffer(void *buffer);

extern "C" void Memory_FreeBufferAliasA(void *buffer);

extern "C" void Memory_FreeBufferWithAllocator(void *block, igMemoryPool *pool);

extern "C" unsigned int Memory_GetBufferSize(void *buffer);

extern "C" igMemoryPool *Memory_FindBufferOwner(void *buffer);

extern "C" void *Memory_DuplicateBuffer(void *source);

extern "C" int FUN_002ed5a0(void *block, igMemoryPool *pool);

extern "C" void Memory_FreeBufferAliasB(void *buffer);

extern "C" void Memory_FreeOwnedBufferUnchecked(void *buffer);

#define EMIT(...) \
    do { \
        if (file) { file->Print(__VA_ARGS__); } \
        else { FUN_00304430(__VA_ARGS__); FUN_00304680(); } \
    } while (0)

extern "C" void FUN_002ed610(unsigned int size, unsigned int perLine, unsigned int digits,
                             unsigned int addr, long long length, const char *name)
{
    bool showAddr = digits;
    unsigned char more = 1;
    DumpFile *file = 0;
    unsigned long long end;
    if (!size) size = 1;
    else if (size > 8) size = 8;
    if (0 != name) {
        int alloc;
        if (g_useOwnerAllocator) alloc = Memory_GetAllocatorBySelector(DAT_00587028[0]);
        else alloc = Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]);
        file = (DumpFile *)igFile_Create(alloc);
        if (0 == file->Open(name, DAT_004f92f0)) goto done;
    }
    {
        unsigned int mask;
        end = (unsigned long long)addr + length;
        unsigned int i;
#define DUMP_CASE(N, FMT, VALUE) \
        mask = (1 << (digits * 4)) - 1; \
        while (more) { \
            if (showAddr) { \
                if (digits < 8) { EMIT(DAT_004f9ca0, digits, addr & mask); } \
                else { EMIT(DAT_004f9cb0, addr); } \
            } \
            for (i = 0; i < perLine; i++) { \
                EMIT(FMT, VALUE); \
                addr = addr + N; \
                if ((unsigned long long)addr >= end) { more = 0; break; } \
            } \
            EMIT(DAT_004f95c8); \
        } \
        break;
        switch (size) {
        case 1: DUMP_CASE(1, DAT_004f9cc0, *(unsigned char *)addr)
        case 2: DUMP_CASE(2, DAT_004f9cc8, *(unsigned short *)addr)
        case 3: DUMP_CASE(3, DAT_004f9cd0, *(unsigned int *)addr & 0xFFFFFF)
        case 4: DUMP_CASE(4, DAT_004f9cd8, *(unsigned int *)addr)
        case 5: DUMP_CASE(5, DAT_004f9ce0, *(unsigned long long *)addr & 0xFFFFFFFFFFULL)
        case 6: DUMP_CASE(6, DAT_004f9ce8, *(unsigned long long *)addr & 0xFFFFFFFFFFFFULL)
        case 7: DUMP_CASE(7, DAT_004f9cf0, *(unsigned long long *)addr & 0xFFFFFFFFFFFFFFULL)
        default: DUMP_CASE(8, DAT_004f9cf8, *(unsigned long long *)addr)
        }
    }
    if (file) {
        file->Close();
        if (--file->refs, 0 == (0x7FFFFF & file->refs)) igObject_Destroy(file);
    }
done:;
}

extern "C" void *FUN_002ee430(unsigned int size);

extern "C" void FUN_002ee4a0(void *block);

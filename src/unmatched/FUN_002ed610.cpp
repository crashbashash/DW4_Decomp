/* 0x002ed610 - FUN_002ed610: hex dump of a memory range (hypothesis name: Memory_HexDump).
 * Parameters: size = bytes per element (clamped to 1..8), perLine = elements per row,
 * digits = address digits shown in the row prefix (0 = no prefix), addr/length = range,
 * name = optional output file name; the dump goes to a file object (open mode "w") when a
 * name is given and to the console otherwise.
 * Evidence: format strings at 0x4f9ca0..0x4f9cf8 ("0x%0*x: ", "0x%08x: ", "%02x ",
 * "%04x ", "%06x ", "%08x ", "%010lx", "%012lx", "%014lx", "%016lx"), a "\n" row
 * terminator at 0x4f95c8 and the open mode "w" at 0x4f92f0. */
extern "C" {
int FUN_00304430(...);   /* console printf */
int FUN_00304680();      /* console flush after each print */
void *FUN_002c4ca0(int); /* creates the file object for an allocator */
int Memory_GetAllocatorBySelector(int);
void igObject_Destroy(void *);
extern char DAT_004f92f0[], DAT_004f95c8[], DAT_004f9ca0[], DAT_004f9cb0[], DAT_004f9cc0[],
    DAT_004f9cc8[], DAT_004f9cd0[], DAT_004f9cd8[], DAT_004f9ce0[], DAT_004f9ce8[],
    DAT_004f9cf0[], DAT_004f9cf8[];
extern unsigned char GPR_00554c14;
extern int DAT_00587028[], DAT_00587060[];
}

/* Unused vtable slots, declared only so the used ones land at their retail offsets. */
#define PAD(n) virtual void pad##n();
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

/* Print through the file object when one was opened, else to the console. */
#define EMIT(...) \
    do { \
        if (file) { file->Print(__VA_ARGS__); } \
        else { FUN_00304430(__VA_ARGS__); FUN_00304680(); } \
    } while (0)

extern "C" void FUN_002ed610(unsigned int size, unsigned int perLine, unsigned int digits,
                             unsigned int addr, long long length, const char *name);
void FUN_002ed610(unsigned int size, unsigned int perLine, unsigned int digits,
                  unsigned int addr, long long length, const char *name) {
    DumpFile *file = 0;
    unsigned char more = 1;
    unsigned long long end;
    bool showAddr = digits != 0;
    if (size == 0) size = 1;
    else if (size > 8) size = 8;
    if (name != 0) {
        int alloc;
        if (GPR_00554c14 != 0) alloc = Memory_GetAllocatorBySelector(DAT_00587028[0]);
        else alloc = Memory_GetAllocatorBySelector(DAT_00587060[0]);
        file = (DumpFile *)FUN_002c4ca0(alloc);
        if (file->Open(name, DAT_004f92f0) == 0) goto done;
    }
    {
        end = (unsigned long long)addr + length;
        unsigned int mask;
        unsigned int i;
/* One case of the element-size switch: print one row per pass (address prefix, then
 * perLine elements of N bytes each) until the cursor reaches the end of the range. */
#define DUMP_CASE(N, FMT, VALUE) \
        mask = (1 << (digits * 4)) - 1; \
        while (more) { \
            if (showAddr) { \
                if (digits < 8) { EMIT(DAT_004f9ca0, digits, addr & mask); } \
                else { EMIT(DAT_004f9cb0, addr); } \
            } \
            for (i = 0; i < perLine; i++) { \
                EMIT(FMT, VALUE); \
                addr += N; \
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
        if (--file->refs, (file->refs & 0x7FFFFF) == 0) igObject_Destroy(file);
    }
done:;
}

#ifndef DW4_IGMEMORYPOOLVIEW_H
#define DW4_IGMEMORYPOOLVIEW_H
/* igMemoryPoolView is a local view of the Alchemy pool (the reflected layout is igMemoryPool in
 * dw4/reflected.h) that adds the virtuals its callers use. The dummies place them at their retail
 * vtable bytes: MWCC keeps two header words ahead of the slots, so slot N sits at 8 + 4 * N and is
 * the pool classes' vfunc_(N + 2). The list covers the whole igMemoryPool table (slots 0-96); the
 * pool classes append their own slots from 97 on. */
class igResult;
struct igMetaObject;
struct igMemoryPoolInfo;
class igMemoryPoolView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6();
    virtual void userConstruct(int flag);                                        /* slot 7, byte 36: igObject's */
    virtual void d8();
    virtual void InitDefaults();                                                     /* slot 9, byte 44: igObject's */
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual igMetaObject *GetMeta();                                             /* slot 20, byte 88 */
    virtual int HandleOutOfMemory(unsigned int size, int attempt);                        /* slot 21, byte 92: out-of-memory hook */
#ifndef long
    virtual igResult SetRawMemory(int buffer, long long size, int owned);            /* slot 22, byte 96 */
#else
    virtual void SetRawMemory();
#endif
    virtual void d23();
    virtual int GetRawMemory(...);                                                   /* slot 24, byte 104: the raw memory block; callers pass a stray argument or none */
    virtual int Trim(int);                                                       /* slot 25, byte 108 */
    virtual int vfunc_28(int level);                                             /* slot 26, byte 112: asked for memory back when the system has none; nonzero when it freed some */
    virtual int vfunc_29();                                                      /* slot 27, byte 116 */
    virtual void Activate();                                                     /* slot 28, byte 120 */
    virtual void Reset();                                                     /* slot 29, byte 124 */
    virtual int Deactivate();                                                      /* slot 30, byte 128 */
    virtual int IsActive();                                                      /* slot 31, byte 132 */
    virtual igResult EnableAllocationLock(int);                                              /* slot 32, byte 136 */
    virtual igResult SetSize(int size);                                            /* slot 33, byte 140 */
#ifndef long
    virtual long long GetSize();                                                /* slot 34, byte 144 */
#else
    virtual void GetSize();
#endif
    virtual void d35();
    virtual unsigned short GetAlignment();                                           /* slot 36, byte 152 */
    virtual void d37(); virtual void d38();
#ifndef long
    virtual igResult SetMaxSize(long long maxSize);                                /* slot 39, byte 164 */
#else
    virtual void SetMaxSize();
#endif
    virtual int GetMaxSize();                                                      /* slot 40, byte 168 */
    virtual igResult SetPreSize(int size);                                         /* slot 41, byte 172 */
    virtual unsigned int GetPreSize();                                             /* slot 42, byte 176 */
    virtual igResult Configure(igMemoryPoolInfo *info);                           /* slot 43, byte 180 */
    virtual void d44();
    virtual int GetLocalNetAllocated();                                                      /* slot 45, byte 188 */
#ifndef long
    virtual long long GetLocalNetAllocatedWithOverhead();                                                /* slot 46, byte 192 */
    virtual long long GetFreeSize();                                                /* slot 47, byte 196 */
#else
    /* The Lua units build with -Dlong=int, which cannot spell the 64-bit return; they never call these. */
    virtual void GetLocalNetAllocatedWithOverhead(); virtual void GetFreeSize();
#endif
    virtual void UpdateStatistics(int, int, int);                                        /* slot 48, byte 200 */
    virtual void ResetStatistics();                                                     /* slot 49, byte 204 */
#ifndef long
    virtual void UpdateLocalStatistics(long long, long long, int);                            /* slot 50, byte 208: global statistics update */
#else
    virtual void UpdateLocalStatistics(int, int, int);
#endif
    virtual void *AllocateElement();                                                    /* slot 51, byte 212: allocate one element */
    virtual void *Allocate(unsigned int size);                                   /* slot 52, byte 216 */
    virtual void *AllocateAligned(unsigned int size, unsigned short alignment);  /* slot 53, byte 220 */
    virtual void *Callocate(int count, int size);                                 /* slot 54, byte 224 */
    virtual void *CallocateAligned(int count, int size, unsigned short alignment);       /* slot 55, byte 228 */
    virtual void *Reallocate(void *block, unsigned int size);                    /* slot 56, byte 232 */
    virtual void *ReallocateAligned(void *block, unsigned int size, unsigned short alignment); /* slot 57, byte 236 */
    virtual int StrDup(void *block);
    virtual void *StrDupAligned(const char *string, unsigned short alignment);        /* slot 59, byte 244: aligned string copy */
    virtual igResult GangAlloc(int count, unsigned int *sizes, void **blocks);                                  /* slot 60, byte 248 */
    virtual igResult GangAllocAligned(int count, unsigned int *sizes, void **blocks, unsigned short *alignments); /* slot 61, byte 252 */
    virtual void GangFree(int count, void **blocks);                                                            /* slot 62, byte 256 */
    virtual int vfunc_65(int);                                                   /* slot 63, byte 260 */
    virtual void Free(void *block);                                              /* slot 64, byte 264 */
    virtual void TrackEvent(void *, int, int);                                     /* slot 65, byte 268 */
    virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72();
    virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80();
    virtual void d81();
    virtual unsigned int GetAllocationSize(void *block);                         /* slot 82, byte 336 */
    virtual int OwnsAllocation(void *block);                                     /* slot 83, byte 340 */
    virtual void d84();
    virtual int PrintStatistics(int);                                                   /* slot 85, byte 348 */
    virtual void DisplayOutstandingAllocations();                                                     /* slot 86, byte 352 */
    virtual void *GetEventTracker();                                             /* slot 87, byte 356 */
    virtual void SetEventTracker(void *tracker);                                        /* slot 88, byte 360 */
    virtual int GetPoolIndex();                                                  /* slot 89, byte 364 */
    virtual void SetPoolIndex(int index);                                        /* slot 90, byte 368 */
    virtual igResult TransferAllocation(char *block, igMemoryPoolView *pool);              /* slot 91, byte 372 */
    virtual unsigned char CanTransferTo(igMemoryPoolView *pool);                      /* slot 92, byte 376: may `pool` alias this pool */
    virtual void d93();
    virtual void CollectMemoryRegions(int list);                                             /* slot 94, byte 384 */
    virtual void SetDefaults();                                                     /* slot 95, byte 388: prepares a new pool before activate */
    virtual void Shutdown();                                                     /* slot 96, byte 392 */
};
#endif

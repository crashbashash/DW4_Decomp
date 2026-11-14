#ifndef DW4_IGMEMORYPOOLVIEW_H
#define DW4_IGMEMORYPOOLVIEW_H
/* igMemoryPoolView is a local view of the Alchemy pool (the reflected layout is igMemoryPool in
 * dw4/reflected.h) that adds the virtuals its callers use. The dummies place them at their retail
 * vtable bytes: MWCC keeps two header words ahead of the slots, so slot N sits at 8 + 4 * N and is
 * the pool classes' vfunc_(N + 2). The list covers the whole igMemoryPool table (slots 0-96); the
 * pool classes append their own slots from 97 on. */
class igResult;
class igMemoryPoolView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24();
    virtual int Trim(int);                                                       /* slot 25, byte 108 */
    virtual void d26(); virtual void d27();
    virtual void activate();                                                     /* slot 28, byte 120 */
    virtual void vfunc_31();                                                     /* slot 29, byte 124 */
    virtual void d30();
    virtual int isActive();                                                      /* slot 31, byte 132 */
    virtual void d32(); virtual void d33();
    virtual int vfunc_36();                                                      /* slot 34, byte 144 */
    virtual void d35();
    virtual unsigned short vfunc_38();                                           /* slot 36, byte 152 */
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual int vfunc_42();                                                      /* slot 40, byte 168 */
    virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45();
#ifndef long
    virtual long long vfunc_48();                                                /* slot 46, byte 192 */
    virtual long long vfunc_49();                                                /* slot 47, byte 196 */
#else
    /* The Lua units build with -Dlong=int, which cannot spell the 64-bit return; they never call these. */
    virtual void vfunc_48(); virtual void vfunc_49();
#endif
    virtual void vfunc_50(int, int, int);                                        /* slot 48, byte 200 */
    virtual void vfunc_51();                                                     /* slot 49, byte 204 */
    virtual void d50(); virtual void d51();
    virtual void *Allocate(unsigned int size);                                   /* slot 52, byte 216 */
    virtual void *AllocateAligned(unsigned int size, unsigned int alignment);    /* slot 53, byte 220 */
    virtual void d54(); virtual void d55();
    virtual void *Reallocate(void *block, unsigned int size);                    /* slot 56, byte 232 */
    virtual void d57();
    virtual int vfunc_58(void *block);
    virtual void d59();
    virtual igResult gangAlloc(int count, unsigned int *sizes, void **blocks);                                  /* slot 60, byte 248 */
    virtual igResult gangAllocAligned(int count, unsigned int *sizes, void **blocks, unsigned short *alignments); /* slot 61, byte 252 */
    virtual void gangFree(int count, void **blocks);                                                            /* slot 62, byte 256 */
    virtual int vfunc_65(int);                                                   /* slot 63, byte 260 */
    virtual void Free(void *block);                                              /* slot 64, byte 264 */
    virtual void vfunc_67(void *, int, int);                                     /* slot 65, byte 268 */
    virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72();
    virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80();
    virtual void d81();
    virtual unsigned int GetAllocationSize(void *block);                         /* slot 82, byte 336 */
    virtual int OwnsAllocation(void *block);                                     /* slot 83, byte 340 */
    virtual void d84(); virtual void d85(); virtual void d86();
    virtual void *getEventTracker();                                             /* slot 87, byte 356 */
    virtual void d88();
    virtual int GetPoolIndex();                                                  /* slot 89, byte 364 */
    virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
    virtual void vfunc_98();                                                     /* slot 96, byte 392 */
};
#endif

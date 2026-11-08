/* newlib _calloc_r(reent, n, elem_size). */
#include "dw4/newlib_mallocr.h"

extern void *memset(void *, int, unsigned int);

#define MALLOC_ZERO(charp, nbytes) \
    do { \
        INTERNAL_SIZE_T mzsz = (nbytes); \
        if (mzsz <= 9 * sizeof(mzsz)) { \
            INTERNAL_SIZE_T *mz = (INTERNAL_SIZE_T *)(charp); \
            if (mzsz >= 5 * sizeof(mzsz)) { \
                *mz++ = 0; \
                *mz++ = 0; \
                if (mzsz >= 7 * sizeof(mzsz)) { \
                    *mz++ = 0; \
                    *mz++ = 0; \
                    if (mzsz >= 9 * sizeof(mzsz)) { \
                        *mz++ = 0; \
                        *mz++ = 0; \
                    } \
                } \
            } \
            *mz++ = 0; \
            *mz++ = 0; \
            *mz = 0; \
        } else \
            memset((charp), 0, mzsz); \
    } while (0)

void *FUN_00123798(Reent *reent_ptr, unsigned int n, unsigned int elem_size)
{
    mchunkptr p;
    INTERNAL_SIZE_T csz;
    INTERNAL_SIZE_T sz = n * elem_size;
    void *mem;

    mem = FUN_00126600(reent_ptr, sz);
    if (mem == 0) {
        return 0;
    } else {
        p = mem2chunk(mem);
        csz = chunksize(p);
        MALLOC_ZERO(mem, csz - SIZE_SZ);
        return mem;
    }
}

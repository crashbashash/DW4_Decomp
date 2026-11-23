#ifndef DW4_IGPSX2HANDLEPOOL_H
#define DW4_IGPSX2HANDLEPOOL_H

#include "dw4/core/igMemory.h"
#include "dw4/core/igMemoryPoolView.h"
#include "dw4/core/igStringRef.h"

/* The 20-byte record behind igPsx2VisualContext's light list (_pLightList): a handle pool of T elements. It
 * hands out indices into `elements` and takes them back through a stack of free indices, the scheme of the
 * kit's igTHandlePool (alchemy-kit_202309, igCore/igHandlePool.h: getFreeElement, freeElement,
 * isIndexAllocated). DW4's pool is a plain record, not an igDataList: the context allocates it from its list
 * memory pool, named by the registry value that sized it (IG_GFX_VC_LIGHT_ARRAY_SIZE). */
template <class T> struct igPsx2HandlePool {
    unsigned short capacity;      /* elements allocated in `elements` */
    unsigned short freeCapacity;  /* room in `freeHandles` */
    unsigned short freeCount;     /* indices in `freeHandles` */
    short pad6;
    igStringRef name;
    unsigned short *freeHandles;  /* the free indices, last in first out */
    T *elements;

    igPsx2HandlePool(int count, const char *poolName) {
        int i;
        igMemoryPoolView *owner;
        name = poolName;
        if (count == 0) count = 1;
        owner = Memory_FindBufferOwner(this);
        elements = (T *)owner->CallocateAligned(count, sizeof(T), 0x10);
        freeHandles = (unsigned short *)owner->Callocate(count, 2);
        freeCapacity = count;
        capacity = count;
        freeCount = count;
        for (i = 0; i < count; i++) freeHandles[i] = i;
    }
    ~igPsx2HandlePool() {
        name = (const char *)0;
        Memory_FreeBuffer(elements);
        Memory_FreeBuffer(freeHandles);
    }
    static void *operator new(unsigned size, igMemoryPoolView *pool) { return Memory_AllocateBufferDirect(size, pool); }
    static void operator delete(void *block) { Memory_FreeBufferAliasB(block); }

    /* Takes a free index, growing the elements and the free stack by four when none is left. */
    int getFreeElement() {
        int handle;
        if (freeCount <= 0) {
            elements = (T *)Memory_ReallocateAlignedAlias(elements, (capacity + 4) * sizeof(T), 0x10);
            memset(elements + capacity, 0, 4 * sizeof(T));
            if (freeCapacity < 4) {
                igMemoryPoolView *owner = Memory_FindBufferOwner(this);
                freeHandles = (unsigned short *)owner->Reallocate(freeHandles, 8);
                freeCapacity = 4;
            }
            int i = 0;
            do {
                freeHandles[i] = capacity + i;
                i++;
            } while (i < 4);
            freeCount = 4;
            capacity = capacity + 4;
        }
        handle = freeHandles[freeCount - 1];
        freeCount = freeCount - 1;
        return handle;
    }

    /* Gives an index back, growing the free stack by eight when it is full. */
    void freeElement(int handle) {
        if (handle < capacity && handle >= 0) {
            if (freeCount >= freeCapacity) {
                igMemoryPoolView *owner = Memory_FindBufferOwner(this);
                freeCapacity = freeCapacity + 8;
                freeHandles = (unsigned short *)owner->Reallocate(freeHandles, freeCapacity * 2);
            }
            freeHandles[freeCount] = handle;
            freeCount = freeCount + 1;
        }
    }

    bool isIndexAllocated(int handle) {
        int i;
        if (handle < capacity && handle >= 0) {
            for (i = 0; i < freeCount; i++) {
                if (handle == freeHandles[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

#endif

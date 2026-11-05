/* 0x002f2180 — Memory_InitializeAllocatorRegistries.
 * Creates the two allocator registries the engine keeps as empty
 * igMemoryPoolInfoList-style lists (docs/engine/registry-bootstrap.md,
 * finding #896): the primary list at 0x586f58 receives the root allocator,
 * the secondary list at 0x586f60 starts empty.  The root allocator's encoded
 * index (the byte at object +7, read by igObject_GetAllocator) is cleared so
 * it resolves to slot 0 of the primary list (docs/engine/object-storage.md). */
#include "dw4/reflected.h"
int igMemoryPoolInfoList_Allocate();
int igMemoryPoolInfoList_Append();
int igMemoryPoolInfoList_Init();
extern int g_primaryAllocatorList_00586f58[4];
extern int g_secondaryAllocatorList_00586f60[4];
void Memory_InitializeAllocatorRegistries(igObject *rootAllocator) {
    int secondaryList;
    int primaryList;

    primaryList = igMemoryPoolInfoList_Allocate(0xC);
    if (primaryList != 0) {
        primaryList = igMemoryPoolInfoList_Init(primaryList);
    }
    g_primaryAllocatorList_00586f58[0] = primaryList;
    igMemoryPoolInfoList_Append(primaryList, rootAllocator);
    ((char *)&rootAllocator->_refCount)[3] = 0;
    secondaryList = igMemoryPoolInfoList_Allocate(0xC);
    if (secondaryList != 0) {
        secondaryList = igMemoryPoolInfoList_Init(secondaryList);
    }
    g_secondaryAllocatorList_00586f60[0] = secondaryList;
}

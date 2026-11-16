#ifndef DW4_IGMEMORYPOOLCONTEXT_H
#define DW4_IGMEMORYPOOLCONTEXT_H

class igMemoryPoolView;

/* The allocator selector of each memory context, in the order of g_memoryContextNames: the program
 * constructs every one at start-up. */
struct igMemoryPoolHandle {
    int value;
    igMemoryPoolHandle(int v) : value(v) {}
    operator int() const { return value; }
};
extern "C" {
extern igMemoryPoolHandle kIGMemoryPoolHandleBootstrap;
extern igMemoryPoolHandle kIGMemoryPoolHandleDefault;
extern igMemoryPoolHandle kIGMemoryPoolHandleCurrent;
extern igMemoryPoolHandle kIGMemoryPoolHandleNonTracked;
extern igMemoryPoolHandle kIGMemoryPoolHandleSystem;
extern igMemoryPoolHandle kIGMemoryPoolHandleMetaData;
extern igMemoryPoolHandle kIGMemoryPoolHandleString;
extern igMemoryPoolHandle kIGMemoryPoolHandleFast;
extern igMemoryPoolHandle kIGMemoryPoolHandleList;
extern igMemoryPoolHandle kIGMemoryPoolHandleTemporary;
extern igMemoryPoolHandle kIGMemoryPoolHandleVertex;
extern igMemoryPoolHandle kIGMemoryPoolHandleRenderList;
extern igMemoryPoolHandle kIGMemoryPoolHandleTexture;
extern igMemoryPoolHandle kIGMemoryPoolHandleApplication;
extern igMemoryPoolHandle kIGMemoryPoolHandleWorld;
extern igMemoryPoolHandle kIGMemoryPoolHandleActor;
extern igMemoryPoolHandle kIGMemoryPoolHandleLevel;
extern igMemoryPoolHandle kIGMemoryPoolHandleFrame;
extern igMemoryPoolHandle kIGMemoryPoolHandlePhysics;
extern igMemoryPoolHandle kIGMemoryPoolHandleAI;
extern igMemoryPoolHandle kIGMemoryPoolHandleDriverData;
extern igMemoryPoolHandle kIGMemoryPoolHandleClut;
extern igMemoryPoolHandle kIGMemoryPoolHandleDMA;
extern igMemoryPoolHandle kIGMemoryPoolHandleAudio;
extern igMemoryPoolHandle kIGMemoryPoolHandleVideo;
extern igMemoryPoolHandle kIGMemoryPoolHandleHandles;
extern igMemoryPoolHandle kIGMemoryPoolHandleImage;
extern igMemoryPoolHandle kIGMemoryPoolHandleImageObject;
extern igMemoryPoolHandle kIGMemoryPoolHandleAttribute;
extern igMemoryPoolHandle kIGMemoryPoolHandleNode;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser0;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser1;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser2;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser3;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser4;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser5;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser6;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser7;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser8;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser9;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser10;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser11;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser12;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser13;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser14;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser15;

extern int g_bootstrapPoolPreSize;
extern int g_systemPoolPreSize;
extern int g_metaDataPoolPreSize;
extern int g_stringPoolPreSize;
extern unsigned char g_useOwnerAllocator;

igMemoryPoolView *Memory_GetAllocatorBySelector(int selector);
igMemoryPoolView *Memory_GetCurrentAllocator(void);
void *Memory_SystemAllocate(unsigned int size);
}

#endif

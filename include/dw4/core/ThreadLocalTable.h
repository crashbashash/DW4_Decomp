#ifndef DW4_THREADLOCALTABLE_H
#define DW4_THREADLOCALTABLE_H
#include "dw4/lua/lua.h"

struct ThreadLocalEntry;

extern "C" {

void ThreadLocalTable_Insert(ThreadLocalEntry *entry);
void ThreadLocalTable_Link(ThreadLocalEntry *entry, ThreadLocalEntry **buckets, unsigned int bucketCount, unsigned int shift);
void ThreadLocalTable_Resize(void);
void ThreadLocalTable_Remove(ThreadLocalEntry *entry);
extern unsigned int g_threadLocalBucketShift;
extern unsigned int g_threadLocalBucketCount;
extern unsigned int g_threadLocalCount;
extern ThreadLocalEntry **g_threadLocalBuckets;
extern int g_threadLocalTableBusy;

}

#endif

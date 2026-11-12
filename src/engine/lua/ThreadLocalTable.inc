static inline unsigned int ThreadLocalTable_Bucket(unsigned int key, unsigned int bucketCount, unsigned int shift)
{
    return (bucketCount - 1) & (key ^ (key >> shift));
}

void ThreadLocalTable_Insert(ThreadLocalEntry *entry) {
    ThreadLocalTable_Resize();
    ThreadLocalTable_Link(entry, g_threadLocalBuckets, g_threadLocalBucketCount, g_threadLocalBucketShift);
    g_threadLocalCount++;
}

void ThreadLocalTable_Link(ThreadLocalEntry *entry, ThreadLocalEntry **buckets,
                           unsigned int bucketCount, unsigned int shift) {
    ThreadLocalEntry **bucket = &buckets[ThreadLocalTable_Bucket(entry->key, bucketCount, shift)];

    entry->next = *bucket;
    if (*bucket != 0) {
        (*bucket)->prev = entry;
    }
    entry->prev = 0;
    *bucket = entry;
}

/* Allocates the buckets on first use, frees them when the table empties, and otherwise doubles
 * the table when it holds more entries than buckets or halves it (down to 16 buckets) when it
 * holds fewer than half, unless a lookup is walking the chains. */
void ThreadLocalTable_Resize(void) {
    unsigned int oldShift;
    unsigned int shift;
    unsigned int bucketCount;
    unsigned int size;
    ThreadLocalEntry **buckets;
    unsigned int index;
    ThreadLocalEntry *entry;
    ThreadLocalEntry *next;

    if (g_threadLocalBuckets == 0) {
        g_threadLocalBuckets = (ThreadLocalEntry **)Memory_AllocateDefaultBuffer(g_threadLocalBucketCount * 4);
        memset(g_threadLocalBuckets, 0, g_threadLocalBucketCount * 4);
        return;
    }
    if (g_threadLocalTableBusy == 0) {
        if (g_threadLocalCount == 0) {
            Memory_FreeBufferAliasA(g_threadLocalBuckets);
            g_threadLocalBuckets = 0;
            g_threadLocalBucketCount = 16;
            return;
        }
        oldShift = g_threadLocalBucketShift;
        shift = oldShift;
        if (g_threadLocalBucketCount < g_threadLocalCount) {
            shift = oldShift + 1;
        } else if (g_threadLocalCount < (g_threadLocalBucketCount >> 1) && oldShift > 4) {
            shift = oldShift - 1;
        }
        if (shift != oldShift) {
            bucketCount = 1 << shift;
            size = bucketCount * 4;
            buckets = (ThreadLocalEntry **)Memory_AllocateDefaultBuffer(size);
            memset(buckets, 0, size);
            for (index = 0; index < g_threadLocalBucketCount; index++) {
                for (entry = g_threadLocalBuckets[index]; entry != 0; entry = next) {
                    next = entry->next;
                    ThreadLocalTable_Link(entry, buckets, bucketCount, shift);
                }
            }
            g_threadLocalBucketCount = bucketCount;
            g_threadLocalBucketShift = shift;
            Memory_FreeBufferAliasA(g_threadLocalBuckets);
            g_threadLocalBuckets = buckets;
        }
    }
}

void ThreadLocalTable_Remove(ThreadLocalEntry *entry) {
    ThreadLocalEntry **bucket;

    if (entry->next != 0) {
        entry->next->prev = entry->prev;
    }
    if (entry->prev != 0) {
        entry->prev->next = entry->next;
    } else {
        bucket = &g_threadLocalBuckets[ThreadLocalTable_Bucket(entry->key, g_threadLocalBucketCount, g_threadLocalBucketShift)];
        if (*bucket == entry) {
            *bucket = entry->next;
        } else {
            return;
        }
    }
    g_threadLocalCount--;
    ThreadLocalTable_Resize();
}

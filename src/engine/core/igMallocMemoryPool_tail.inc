igResult igMallocMemoryPool_Configure(igMallocMemoryPool *self, igMemoryPoolInfo *info) {
    igResult result;
    result = igMemoryPool_Configure((void **)self, (void *)info);
    const char *messages = igMemoryPoolInfo_messages(info);
    if (messages != 0) {
        int level = self->_messageLevel;
        if (strstr(messages, (char *)"NoMessages") != 0) {
            level = 0;
        } else if (strstr(messages, (char *)"ErrorMessages") != 0) {
            level = 1;
        } else if (strstr(messages, (char *)"WarningMessages") != 0) {
            level = 2;
        } else if (strstr(messages, (char *)"Notifications") != 0) {
            level = 3;
        }
        self->_messageLevel = level;
    }
    return result;
}

/* Empties the pool and marks it active: the 64-bit _size (+136) is cleared and _isActive (+112)
 * set. */
void igMallocMemoryPool_Activate(igMallocMemoryPool *self) {
    self->_size = 0;
    self->_isActive = 1;
}

igResult igMallocMemoryPool_EnableAllocationLock(igMallocMemoryPoolView *self, unsigned char enable) {
    igResult waited;
    igResult destroyed;
    igResult created;
    if (enable == 0) {
        igSmartPointer<igSemaphoreView> held(self->_allocationLock);
        self->_allocationLock.clear();
        if (held.p != 0) {
            waited = held.p->Wait(1);
            destroyed = held.p->Destroy();
        }
        self->_allocationLock.clear();
    } else if (enable == 1) {
        if (self->_allocationLock.p != 0) return igResult(g_resultSuccess.v);
        igSmartPointer<igSemaphoreView> semaphore((igSemaphoreView *)igSemaphore_Create((int)(((void *)igObject_GetAllocator((int)self)))));
        created = semaphore.p->Create();
        self->_allocationLock = semaphore;
    }
    return igResult(g_resultSuccess.v);
}

void igMallocMemoryPool_SetSize(int *outStatus, igMallocMemoryPool *self, long long size) {
    self->_size = size;
    *outStatus = g_resultSuccess.v;
}

/* Accessor: the pool's reflected _size field (igUnsignedLongMetaField, +136). */
long long igMallocMemoryPool_GetSize(igMallocMemoryPool *self) {
    return self->_size;
}

void igMallocMemoryPool_SetMaxSize(int *status, igMallocMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_resultSuccess.v;
}

/* Accessor: the pool's reflected _maxSize field (igUnsignedLongMetaField, +128). */
long long igMallocMemoryPool_GetMaxSize(igMallocMemoryPool *self) {
    return self->_maxSize;
}

void igMallocMemoryPool_SetAlignment(int *outStatus, igMallocMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_resultSuccess.v;
}

/* Returns the pool's allocation alignment, _alignment (+144). */
unsigned short igMallocMemoryPool_GetAlignment(igMallocMemoryPool *self) {
    return self->_alignment;
}

void igMallocMemoryPool_SetElementSize(int *status, igMallocMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_resultSuccess.v;
}

int igMallocMemoryPool_GetElementSize(igMallocMemoryPool *self) {
    return self->_elementSize;
}

long long Gap__Core__igMallocMemoryPool__vfunc_46(igMallocMemoryPool *self) {
    return self->_maxSize - self->_localNetAllocatedWithOverhead;
}

/* Slot 47 getter: returns the pool's _localNetAllocated field (bytes currently allocated from this
 * pool). */
long long igMallocMemoryPool_GetLocalNetAllocated(igMallocMemoryPool *self) {
    return self->_localNetAllocated;
}

/* Slot 48 getter: returns the pool's _localNetAllocatedWithOverhead field (bytes currently
 * allocated from this pool, overhead included). */
long long igMallocMemoryPool_GetLocalNetAllocatedWithOverhead(igMallocMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long igMallocMemoryPool_GetLocalNetAllocatedHigh(void *pool) {
    return ((igMallocMemoryPool *)pool)->_localNetAllocatedHigh;
}

long long igMallocMemoryPool_GetLocalNetAllocatedWithOverheadHigh(void *pool) {
    return ((igMallocMemoryPool *)pool)->_localNetAllocatedWithOverheadHigh;
}

long long igMallocMemoryPool_GetFreeSize(igMallocMemoryPool *self) {
    return self->_maxSize - self->_localNetAllocatedWithOverhead;
}

void *igMallocMemoryPool_AllocateElement(igMallocMemoryPoolView *self)
{
    return self->Allocate(self->_elementSize);
}

void igMallocMemoryPool_Lock(void *pool) {
    igResult result;
    void **lock;

    lock = (void **)((igMallocMemoryPool *)pool)->_allocationLock;
    if (lock != 0) {
        result = ((igSemaphoreView *)(lock))->Wait(1);
    }
}

void igMallocMemoryPool_Unlock(void *pool) {
    igResult result;
    void **lock;

    lock = (void **)((igMallocMemoryPool *)pool)->_allocationLock;
    if (lock != 0) {
        result = ((igSemaphoreView *)(lock))->Signal();
    }
}

int igMallocMemoryPool_UnlockAndReturn(void *pool, int value) {
    igResult result;
    void **lock;

    lock = (void **)((igMallocMemoryPool *)pool)->_allocationLock;
    if (lock != 0) {
        result = ((igSemaphoreView *)(lock))->Signal();
    }
    return value;
}

void *igMallocMemoryPool_Allocate(igMallocMemoryPoolView *self, unsigned int size)
{
    return self->MemoryOperation(0, size, self->_alignment);
}

void *igMallocMemoryPool_AllocateAligned(igMallocMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->MemoryOperation(0, size, alignment);
}

void *igMallocMemoryPool_Callocate(igMallocMemoryPool *self, int count, int size) {
    int total = count * size;
    void *p = ((igMallocMemoryPoolView *)self)->MemoryOperation(0, total, self->_alignment);
    if (p != 0) {
        if (total != 0) {
            if (hasPoolOption(self->_poolOptionFlags, 2) || !hasPoolOption(self->_poolOptionFlags, 4)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

int igMallocMemoryPool_CallocateAligned(igMallocMemoryPool *self, int count, int size) {
    int bytes;
    void *block;
    int options;

    bytes = count * size;
    block = ((igMallocMemoryPoolView *)self)->MemoryOperation(0, bytes);
    if (block != 0) {
        if (bytes != 0) {
            options = self->_poolOptionFlags;
            if (hasPoolOption(options, 2) || !hasPoolOption(options, 4)) {
                memset(block, 0, bytes);
            }
        }
    }
    return (int)block;
}

void *igMallocMemoryPool_Reallocate(igMallocMemoryPoolView *self, void *block, unsigned int size)
{
    return self->MemoryOperation(block, size, self->_alignment);
}

void *igMallocMemoryPool_ReallocateAligned(igMallocMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->MemoryOperation(block, size, alignment);
}

/* Gang allocation: one system block carries every requested block. The block starts with its own
 * byte count; each member is a GangRecord followed by a tagged header and the payload. */
igResult igMallocMemoryPool_GangAlloc(igMallocMemoryPoolView *self, int count, unsigned int *sizes, void **blocks) {
    int guard = 0;
    char *block;
    unsigned total;
    unsigned i;
    if (hasPoolOption(self->_poolOptionFlags, 1)) {
        guard = 12;
    }
    total = guard + 4;
    if (self->_alignment > 8) {
        unsigned short *alignments = (unsigned short *)self->Allocate((unsigned short)count * 2);
        for (i = 0; i < (unsigned short)count; i++) {
            alignments[i] = self->_alignment;
        }
        igResult result = self->GangAllocAligned(count, sizes, blocks, alignments);
        self->Free(alignments);
        return result;
    }
    {
        for (i = 0; i < (unsigned short)count; i++) {
            unsigned size = guard + sizes[i];
            unsigned overhead;
            unsigned chunk;
            overhead = headerBytesFor(size, (unsigned)self->_poolIndex >> 1);
            chunk = (size + overhead + 3) & ~3;
            if (chunk < 4) {
                chunk = 4;
            }
            /* A member's size with its record, set in two steps: the variable then has a register
             * of its own, as in retail. */
            unsigned entry;
            entry = chunk + 12;
            entry = roundUp8(entry);
            total += entry;
        }
    }
    block = 0;
    for (;;) {
        if ((unsigned)(total + (int)self->_localNetAllocated) <= self->_maxSize) {
            block = (char *)self->Allocate(total);
            if (block != 0) {
                /* The write position is declared ahead of `first`, which lives on the stack. */
                char *cursor;
                GangRecord *first;
                TaggedBlockHeader *h;
                self->_localAllocationCount += (unsigned short)count;
                self->_localNetAllocationCount += (unsigned short)count;
                block += 4;
            if (self->_localNetAllocationCountHigh < self->_localNetAllocationCount) {
                    self->_localNetAllocationCountHigh = self->_localNetAllocationCount;
                }
                    *(unsigned *)block = total;
                first = (GangRecord *)(block + 4);
                cursor = block + 12;
                first->offset = 0;
                first->count = (unsigned short)count;
                h = (TaggedBlockHeader *)cursor;
                initBlockHeader(self, h, sizes[0] + guard, 0, true, false);
                blocks[0] = (char *)h + (h->big == 0 ? 4 : 12);
                cursor += chunkBytes(h);
                if (guard != 0) {
                    ((unsigned *)blocks[0])[1] = 0xAAAAAAAF;
                    ((unsigned *)blocks[0])[0] = 8;
                    blocks[0] = (char *)blocks[0] + 8;
                    *(unsigned *)((char *)h + signedChunkBytes(h) - 4) = 0xBBBBBBBF;
                    cursor += guard;
                }
                for (i = 1; i < (unsigned short)count; i++) {
                    if ((unsigned)cursor & 7) {
                        cursor += 4;
                    }
                    ((GangRecord *)cursor)->offset = cursor - (char *)first;
                    ((GangRecord *)cursor)->count = 0;
                    cursor += 8;
                    h = (TaggedBlockHeader *)cursor;
                    initBlockHeader(self, h, guard + sizes[i], 0, true, false);
                    blocks[i] = (char *)h + (h->big == 0 ? 4 : 12);
                    cursor += chunkBytes(h);
                    if (guard != 0) {
                        ((unsigned *)blocks[i])[1] = 0xAAAAAAAF;
                        ((unsigned *)blocks[i])[0] = 8;
                        blocks[i] = (char *)blocks[i] + 8;
                        *(unsigned *)((char *)h + signedChunkBytes(h) - 4) = 0xBBBBBBBF;
                        cursor += guard;
                    }
                }
            }
            break;
        }
        if (self->HandleOutOfMemory(total, 1) == 0) {
            if (hasPoolOption(self->_poolOptionFlags, 0x40)) {
                if (self->_messageLevel > 0) {
                    if ((unsigned)(total + (int)self->_localNetAllocated) > self->_maxSize && self->_messageLevel > 0) {
                        igReportError((const char *)"igMallocMemoryPool(E98): Maximum memory size limit of %d bytes reached.  %d bytes already allocated.", (int)self->_maxSize, (int)self->_localNetAllocated);
                    }
                }
            } else if (self->_messageLevel >= 3) {
                igReportNotice((const char *)"igMallocMemoryPool[%d](E100) - refused request of %d bytes\nPool has already allocated %u bytes of maximum %u bytes\n", self->_poolIndex, sizes, (int)self->_localNetAllocated, (int)self->_maxSize);
            }
            break;
        }
    }
    if (block == 0) {
        for (i = 0; i < (unsigned short)count; i++) {
            blocks[i] = 0;
        }
        return g_resultFailure;
    }
    return g_resultSuccess;
}

void igMallocMemoryPool_GangAllocAligned(int *result) {
    *result = g_resultFailure.v;
}

void igMallocMemoryPool_GangFree(igMallocMemoryPoolView *self, unsigned int size, char **block) {
    char *q = padRecord(blockHeader(*block));
    self->_localFreeCount += *(unsigned short *)(q + 2);
    self->_localNetAllocationCount -= size;
    self->Free((char *)((int)q - 4) - 4);
}

void Gap__Core__igMallocMemoryPool__resetFields(igMallocMemoryPool *self, int extra1) {
    Gap__Core__igObject__resetFields((int)self, extra1);
    self->_poolOptionFlags = (int) g_igMallocMemoryPool_defaultPoolOptionFlags;
}

void igMallocMemoryPool_SetDefaults(igMallocMemoryPool *self) {
    igObject *r;
    self->_refCount = 0;
    ((igRefCountWord *)&self->_refCount)->bits.count = 1;
    ((igRefCountWord *)&self->_refCount)->bytes.poolIndex = 0;
    self->_poolIndex = 0;
    ((igMemoryPoolView *)self)->ResetStatistics();
    self->_elementSize = 0;
    self->_maxSize = (long long)(unsigned __int128)(unsigned long long)-1LL;
    self->_size = 0;
    self->_alignment = 1;
    r = (igObject *)self->_eventTracker;
    if (r != 0) {
        r->_refCount = r->_refCount - 1;
        if ((r->_refCount & 0x7fffff) == 0) igObject_Destroy(r);
    }
    self->_eventTracker = 0;
    self->_isActive = 0;
    g_igMallocMemoryPool_instanceCount += 1;
    r = (igObject *)self->_allocationLock;
    if (r != 0) {
        r->_refCount = r->_refCount - 1;
        if ((r->_refCount & 0x7fffff) == 0) igObject_Destroy(r);
    }
    self->_allocationLock = 0;
    self->_messageLevel = 1;
    self->_poolOptionFlags = 12;
}

void *igMallocMemoryPool_Initialize(igMallocMemoryPool *self) {
    igMemoryPool_Initialize((int **)self);
    *(int *)self = (int)(&g_igMallocMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    return self;
}

void *igMallocMemoryPool_CopyConstruct(igMallocMemoryPool *self, int source) {
    igMemoryPool_CopyConstruct((igMemoryPool *)self, (igMemoryPool *)source);
    *(int *)self = (int)(&g_igMallocMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    return self;
}

void igMallocMemoryPool_Destruct(igMallocMemoryPool *self) {
    ((igMemoryPoolView *)self)->Shutdown();
    igMemoryPool_Destruct((int)self);
}

void igMallocMemoryPool_Free(igMallocMemoryPoolView *self, void *block)
{
    self->MemoryOperation(block, -1, self->_alignment);
}

/* The malloc pool's allocate / reallocate / free core: size -1 frees `block`; otherwise the block is
 * (re)allocated from the system allocator, with the out-of-memory hook given a chance to make room
 * before the maximum size refuses the request. With the sentinel option every block carries a head
 * sentinel after `headBytes` of padding (the padding's size is kept in the word before it) and a
 * tail sentinel in the last word of its chunk. */
void *igMallocMemoryPool_MemoryOperation(igMallocMemoryPoolView *self, char *block, int size, unsigned short alignment) {
    int newBytes;
    int total;
    bool moved;
    int oldHeadBytes;
    int oldSize;
    int oldBytes;
    int sentinelBytes;
    int oldSentinelBytes;
    int headBytes;
    TaggedBlockHeader *h;
    char *result;
    char *fresh;
    TaggedBlockHeader *newHeader;

    oldSize = 0;
    oldBytes = 0;
    oldHeadBytes = 0;
    sentinelBytes = 0;
    oldSentinelBytes = 0;
    headBytes = 0;
    h = 0;
    moved = false;
    if (hasPoolOption(self->_poolOptionFlags, 0x100)) {
        if (self->_messageLevel >= 2) {
            igReport_Warning("igMallocMemoryPool(E110): Assert-on-memory-operation is in effect and %s was requested.", (size == -1 && block == 0) ?"a deallocation" :"an allocation");
        }
        if (self->HandleOutOfMemory(size, 4) == 0) {
            return 0;
        }
    }
    igMallocMemoryPool_Lock(self);
    if (self->_alignment > alignment) {
        alignment = self->_alignment;
    }
    if (alignment < 8) {
        alignment = 8;
    }
    if (hasPoolOption(self->_poolOptionFlags, 1)) {
        headBytes = alignment;
        sentinelBytes = headBytes + 4;
        oldHeadBytes = headBytes;
        oldSentinelBytes = sentinelBytes;
    }
    for (;;) {
        if (size == -1) {
            result = 0;
            if (block != 0) {
                if (sentinelBytes != 0) {
                    unsigned head = ((unsigned *)block)[-1];
                    if (head == 0xAAAAAAAF) {
                        int offset = ((int *)block)[-2];
                        block -= offset;
                        oldSentinelBytes = offset + 4;
                        h = (TaggedBlockHeader *)blockHeader(block);
                        unsigned tail = *(unsigned *)((char *)h + chunkBytes(h) - 4);
                        if (tail != 0xBBBBBBBF && self->_messageLevel >= 1) {
                            igReportError("igMallocMemoryPool::free(E88): Bad tail sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", block + 8, 0xBBBBBBBF, tail);
                        }
                    } else if (self->_messageLevel >= 1) {
                        igReportError("igMallocMemoryPool::free(E89): Bad head sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", block, 0xAAAAAAAF, head);
                    }
                } else if (((unsigned *)block)[-1] == 0xAAAAAAAF) {
                    int offset = ((int *)block)[-2];
                    if (offset > 0x100010) {
                        if (self->_messageLevel >= 1) {
                            igReportError("igMallocMemoryPool::free(E107): Bad head sentinel off.  Offset 0x%x.", block + 8, offset);
                        }
                        igMallocMemoryPool_Unlock(self);
                        return 0;
                    }
                    block -= offset;
                    oldSentinelBytes = offset + 4;
                    h = (TaggedBlockHeader *)blockHeader(block);
                    unsigned tail = *(unsigned *)((char *)h + chunkBytes(h) - 4);
                    if (tail != 0xBBBBBBBF && self->_messageLevel >= 1) {
                        igReportError("igMallocMemoryPool::free(E108): Bad tail sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", block + 8, 0xBBBBBBBF, tail);
                    }
                } else {
                    h = (TaggedBlockHeader *)blockHeader(block);
                }
            } else {
                igMallocMemoryPool_Unlock(self);
                return 0;
            }
            if (h != 0) {
                oldSize = payloadSize(h) - oldSentinelBytes;
                oldBytes = chunkBytes(h);
                if (self->_poolIndex != chunkPoolIndex(h) && self->_messageLevel >= 1) {
                    igReportError("igMallocMemoryPool::free(E112): Attempt to free user block 0x%08x from pool[%d] with pool[%d].", block, chunkPoolIndex(h), self->_poolIndex);
                }
                if (hasPoolOption(self->_poolOptionFlags, 2)) {
                    memset(block, 0xFD, payloadSize(h));
                }
                if (h->marked) {
                    GangRecord *record = (GangRecord *)padRecord(blockHeader(block));
                    GangRecord *first = record;
                    unsigned short offset = record->offset;
                    if (offset) {
                        first = (GangRecord *)((char *)record - offset);
                    }
                    if (first->count == 0 && self->_messageLevel >= 3) {
                        igReportNotice("free() call on gang alloced memory that was already free (0x%08x)", block);
                    }
                    self->_localFreeCount++;
                    self->_localNetAllocationCount--;
                    if (--first->count == 0) {
                        unsigned *gang = (unsigned *)first - 1;
                        if (self->_updateStatistics) {
                            self->UpdateStatistics(*gang, *gang + 4, 0);
                        }
                        igMallocMemoryPool_FreeBlock(self, (unsigned char *)(gang - 1));
                    }
                } else {
                    if (self->_updateStatistics) {
                        self->UpdateStatistics(oldSize, oldBytes, 0);
                    }
                    igMallocMemoryPool_FreeBlock(self, (unsigned char *)block);
                }
            } else if (self->_messageLevel >= 3) {
                igReportNotice("igMallocMemoryPool::free(E90) - Invalid memory block 0x%x.\n", self->_poolIndex, block);
            }
            break;
        }
        if ((unsigned int)(size + (int)self->_localNetAllocated) > self->_maxSize) {
            if (self->HandleOutOfMemory(size, 1) != 0) {
                continue;
            }
            if (hasPoolOption(self->_poolOptionFlags, 0x40)) {
                if (self->_messageLevel >= 1) {
                    if ((unsigned int)(size + (int)self->_localNetAllocated) > self->_maxSize && self->_messageLevel >= 1) {
                        igReportError("igMallocMemoryPool(E101): Maximum memory size limit of %d bytes reached.  %d bytes already allocated.", (int)self->_maxSize, (int)self->_localNetAllocated);
                    }
                }
            } else if (self->_messageLevel >= 3) {
                igReportNotice("igMallocMemoryPool::memoryOperation[%d](E91) - Operation refused request of %d bytes\nPool has already allocated %u bytes of maximum %u bytes\n", self->_poolIndex, size, (int)self->_localNetAllocated, (int)self->_maxSize);
            }
            result = 0;
            break;
        }
        total = size + sentinelBytes;
        if (block != 0) {
            if (sentinelBytes != 0) {
                if (((unsigned *)block)[-1] == 0xAAAAAAAF) {
                    oldHeadBytes = ((int *)block)[-2];
                    block -= oldHeadBytes;
                    oldSentinelBytes = oldHeadBytes + 4;
                    h = (TaggedBlockHeader *)blockHeader(block);
                    unsigned tail = *(unsigned *)((char *)h + chunkBytes(h) - 4);
                    if (tail != 0xBBBBBBBF && self->_messageLevel >= 1) {
                        igReportError("igMallocMemoryPool::realloc(E92): Bad tail sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", block + oldHeadBytes, 0xBBBBBBBF, tail);
                    }
                } else {
                    h = (TaggedBlockHeader *)blockHeader(block);
                    if (igAllocator_ResolveEncodedIndex(chunkPoolIndex(h)) != self) {
                        if (self->_messageLevel >= 1) {
                            igReportError("igMallocMemoryPool::realloc(E109): Invalid memory block header.  Address 0x%x.", block);
                        }
                        igMallocMemoryPool_Unlock(self);
                        return 0;
                    }
                }
            } else {
                h = (TaggedBlockHeader *)blockHeader(block);
            }
            if (self->_poolIndex != chunkPoolIndex(h) && self->_messageLevel >= 1) {
                igReportError("igMallocMemoryPool::free(E113): Attempt to free user block 0x%08x from pool[%d] with pool[%d].", block, chunkPoolIndex(h), self->_poolIndex);
            }
            oldSize = payloadSize(h) - oldSentinelBytes;
            oldBytes = chunkBytes(h);
            if (alignment <= 8 && oldSentinelBytes == sentinelBytes && (unsigned)block % alignment == 0 && !h->relocated) {
                fresh = (char *)igMallocMemoryPool_ReallocateBlock(self, block, total);
            } else {
                fresh = (char *)igMallocMemoryPool_AllocateAlignedBlock(self, alignment, total);
                moved = true;
            }
        } else {
            if (alignment != 8) {
                fresh = (char *)igMallocMemoryPool_AllocateAlignedBlock(self, alignment, total);
            } else {
                fresh = (char *)igMallocMemoryPool_AllocateBlock(self, total);
            }
        }
        if (fresh != 0) {
            newHeader = (TaggedBlockHeader *)blockHeader(fresh);
            newBytes = chunkBytes(newHeader);
            if (self->_messageLevel >= 1) {
                if (total != payloadSize(newHeader) && self->_messageLevel >= 1) {
                    igReportError("igMallocMemoryPool: Invalid or corrupted block at 0x%x - %s", newHeader,"(E65) Software error - unexpected block size.");
                }
            }
            if (alignment) {
                if (self->_messageLevel >= 1) {
                    if (((unsigned)fresh & (alignment - 1)) != 0 && self->_messageLevel >= 1) {
                        igReportError("(E1) Software error - igMallocMemoryPool::memoryOperation(0x%x, 0x%x) didn't align:  0x%x\n", alignment, total, fresh);
                    }
                }
            }
            if (block != 0) {
                if (moved) {
                    memcpy(fresh + headBytes, block + oldHeadBytes, oldSize > size ? size : oldSize);
                    if (hasPoolOption(self->_poolOptionFlags, 2)) {
                        memset(block, 0xFD, payloadSize(h));
                    }
                    if (self->_updateStatistics) {
                        self->UpdateStatistics(oldSize, oldBytes, 0);
                    }
                    igMallocMemoryPool_FreeBlock(self, (unsigned char *)block);
                } else if (self->_updateStatistics) {
                    self->UpdateStatistics(oldSize, oldBytes, 0);
                }
            }
            if (sentinelBytes != 0) {
                *(unsigned *)(fresh + (headBytes - 4)) = 0xAAAAAAAF;
                *(int *)(fresh + (headBytes - 8)) = headBytes;
                fresh += headBytes;
                *(unsigned *)((char *)newHeader + newBytes - 4) = 0xBBBBBBBF;
            }
            if (self->_updateStatistics) {
                self->UpdateStatistics(size, newBytes, 1);
            }
            result = fresh;
        } else {
            if (self->_messageLevel >= 3) {
                igReportNotice("igMallocMemoryPool::memoryOperation[%d](E94) - Operation failed on request of %d bytes\n", self->_poolIndex, size);
            }
            result = 0;
        }
        if (result != 0 && block == 0) {
            if (hasPoolOption(self->_poolOptionFlags, 2)) {
                memset(result, 0xCD, size);
            } else if (hasPoolOption(self->_poolOptionFlags, 4)) {
                memset(result, 0, size);
            }
        }
        break;
    }
    return (void *)igMallocMemoryPool_UnlockAndReturn(self, (int)result);
}

int igMallocMemoryPool_OwnsAllocation(int pool, char *memory) {
    TaggedBlockHeader *h;
    int index;
    int owner;
    int self;

    self = pool;
    h = (TaggedBlockHeader *)(memory - 4);
    if (((TaggedTailByte *)(memory - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(memory - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        index = h->poolLow * 2;
    } else {
        index = (h->poolLow + (h->poolHigh << 5)) * 2;
    }
    owner = (int)igAllocator_ResolveEncodedIndex(index);
    return owner == self;
}

int Gap__Core__igMallocMemoryPool__vfunc_83(void) {
    return 1;
}

unsigned int igMallocMemoryPool_GetAllocationSize(int pool, char *memory) {
    TaggedBlockHeader *hdr;

    hdr = (TaggedBlockHeader *)(memory - 4);
    if (hdr->big == 1) {
        hdr = (TaggedBlockHeader *)(memory - 0xC);
    }
    if (hdr == 0) {
        return 0;
    }
    if (hdr->big == 0) {
        return hdr->size;
    }
    return hdr->size + (hdr->sizeHigh << 0x13);
}

void igMallocMemoryPool_PrintStatistics(igMallocMemoryPool *self, char *title) {
    char buf[64];
    char *name;
    if (title != 0 && title[0] != 0) {
        igReport_Printf("%s:\n");
        igReport_Flush();
    }
    if (((struct Ctx { char p[36]; int on; } * *)&g_objectSystem)[0]->on != 0) {
        name = igMetaEnum_GetValueName(buf, 64, self->_messageLevel, igMallocMemoryPool_GetMessageLevelMetaEnum());
    } else {
        name = ((char *)"");
    }
    {
        long long netCountHigh = self->_localNetAllocationCountHigh;
        long long netCount = self->_localNetAllocationCount;
        long long freeCount = self->_localFreeCount;
        long long allocationCount = self->_localAllocationCount;
        long long netWithOverheadHigh = self->_localNetAllocatedWithOverheadHigh;
        long long netWithOverhead = self->_localNetAllocatedWithOverhead;
        long long freedWithOverhead = self->_localFreedWithOverhead;
        long long allocatedWithOverhead = self->_localAllocatedWithOverhead;
        long long netAllocatedHigh = self->_localNetAllocatedHigh;
        long long netAllocated = self->_localNetAllocated;
        long long freed = self->_localFreed;
        long long allocated = self->_localAllocated;
        igReport_Printf("    Total allocated:                      %u\n    Total freed:                          %u\n    Net allocated:                        %u\n    Net allocated high:                   %u\n    Total allocated with overhead:        %u\n    Total freed with overhead:            %u\n    Net allocated with overhead:          %u\n    Net allocated high with overhead:     %u\n    Total allocation count:               %u\n    Total free count:                     %u\n    Net allocation count:                 %u\n    Net allocation count high:            %u\n    Max size limit:                       %u\n    Message Level:                        %s\n", (int)allocated, (int)freed, (int)netAllocated, (int)netAllocatedHigh, (int)allocatedWithOverhead, (int)freedWithOverhead, (int)netWithOverhead, (int)netWithOverheadHigh, (int)allocationCount, (int)freeCount, (int)netCount, (int)netCountHigh, (int)((igMemoryPoolView *)self)->GetSize(), name);
    }
    igReport_Flush();
}

int igMallocMemoryPool_GetEventTracker(void *pool) {
    return ((igMallocMemoryPool *)pool)->_eventTracker;
}

void igMallocMemoryPool_SetEventTracker(igMallocMemoryPool *self, igObject *tracker) {
    igObject *old;
    if ((tracker == 0) || (((void *)igObject_GetAllocator((int)tracker)) != self)) {
        if (tracker != 0) {
            tracker->_refCount = tracker->_refCount + 1;
        }
        old = (igObject *)self->_eventTracker;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        self->_eventTracker = (int)tracker;
    }
}

void igMallocMemoryPool_Dump(void *self, int unused1, int unused2, int unused3, int fileName) {
    const char *message;
    igMallocMemoryPool_Lock(self);
    message = "The method dump() has no meaning for an igMallocMemoryPool\n";
    if (fileName != 0) {
        igSmartPointer<igFileView> file((igFileView *)igFile_Create((int)(((void *)igObject_GetAllocator((int)self)))));
        if (file.p->Open((const char *)fileName, (const char *)"w") == 0) {
            if (((igMallocMemoryPool *)self)->_messageLevel >= 2) {
                igReport_Warning("igMallocMemoryPool::dump() Could not open file (%s) for output\n", fileName);
            }
            igMallocMemoryPool_Unlock(self);
            return;
        }
        file.p->Print((const char *)message);
        file.p->Close();
    } else {
        printf(message);
    }
    igMallocMemoryPool_Unlock(self);
}

int igMallocMemoryPool_GetPoolIndex(void *pool) {
    return ((igMallocMemoryPool *)pool)->_poolIndex;
}

void igMallocMemoryPool_SetPoolIndex(void *pool, int index) {
    ((igMallocMemoryPool *)pool)->_poolIndex = index;
}

static inline int poolIndexAccepts(igMallocMemoryPool *p, int y) { if (p->_poolIndex < 64 && y >= 64) return 0; return 1; }

void igMallocMemoryPool_TransferAllocation(int *result, igMallocMemoryPool *self, char *memory, igMemoryPoolView *target) {
    int targetIndex = target->GetPoolIndex();
    int ok;
    TaggedBlockHeader *h;
    int index;
    ok = poolIndexAccepts(self, targetIndex);
    if (ok != 0) {
        h = (TaggedBlockHeader *)(memory - 4);
        if (((TaggedTailByte *)(memory - 1))->extended == 1) {
            h = (TaggedBlockHeader *)(memory - 12);
        }
        index = target->GetPoolIndex() >> 1;
        h->poolLow = index;
        if (h->big == 1) {
            h->poolHigh = index >> 5;
        }
        *result = g_resultSuccess.v;
    } else {
        *result = g_resultFailure.v;
    }
}

int igMallocMemoryPool_CanTransferTo(void *pool, void **target) {
    int targetIndex;
    int allowed;

    targetIndex = ((igMemoryPoolView *)(target))->GetPoolIndex();
    if ((((igMallocMemoryPool *)pool)->_poolIndex < 0x40) && (targetIndex >= 0x40)) {
        allowed = 0;
    } else {
        allowed = 1;
    }
    if (allowed != 0) {
        return 1;
    }
    return 0;
}

int igMallocMemoryPool_GetAllocationPoolIndex(int pool, char *memory) {
    TaggedBlockHeader *h;

    if (memory == 0) {
        return -1;
    }
    h = (TaggedBlockHeader *)(memory - 4);
    if (((TaggedTailByte *)(memory - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(memory - 12);
    }
    if (h == 0) {
        return -1;
    }
    if (h->big == 0) {
        return h->poolLow * 2;
    }
    return (h->poolLow + (h->poolHigh << 5)) * 2;
}

/* Reports whether the pool is active: returns _isActive (+112), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char igMallocMemoryPool_IsActive(igMallocMemoryPool *self) {
    return self->_isActive;
}

static inline int usesAligned(igMallocMemoryPoolView *p) { return (p->_poolOptionFlags & 0x20) != 0; }

static inline int usesSized(igMallocMemoryPoolView *p) { return (p->_poolOptionFlags & 0x10) != 0; }

void *igMallocMemoryPool_AllocateBlock(igMallocMemoryPoolView *self, unsigned size) {
    unsigned overhead;
    unsigned total;
    void *block;
    TaggedBlockHeader *h;
    int id;
    unsigned end;
    unsigned aligned;
    unsigned slot = (unsigned)self->_poolIndex >> 1;
    if (size >= 0x80000 || slot >= 32) {
        overhead = 12;
    } else {
        overhead = 4;
    }
    total = overhead + size;
    if (usesAligned(self)) {
        block = (g_activeSystemAllocator)->AllocateAligned(total + 4);
    } else if (usesSized(self)) {
        block = (g_activeSystemAllocator)->AllocateSized(total + 4);
    } else {
        block = (g_activeSystemAllocator)->Allocate(total + 4);
    }
    if (block != 0) {
    h = (TaggedBlockHeader *)&((int *)block)[1];
    id = self->GetPoolIndex() >> 1;
    h->poolLow = id;
    h->relocated = 0;
    h->marked = 0;
    h->used = 0;
    if (size >= 0x80000 || id >= 32) {
        h->sizeHigh = size >> 19;
        h->poolHigh = id >> 5;
        h->big = 1;
        h->extraBig = 1;
        h->extraUsed = 0;
        h->extraMarked = 0;
        h->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        h->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    h->words = ((end - aligned) >> 2) - 1;
    h->size = size;
    return (char *)h + (h->big == 0 ? 4 : 12);
    }
    return 0;
}

void igMallocMemoryPool_FreeBlock(igMallocMemoryPoolView *self, unsigned char *p) {
    TaggedBlockHeader *h = (TaggedBlockHeader *)(p - 4);
    unsigned size;
    if (((TaggedTailByte *)(p - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(p - 12);
    }
    size = h->size;
    if (h->big == 1) {
        size = size + (h->sizeHigh << 19);
    }
    size = (size + 3) & ~3;
    size = size + (h->words + 1) * 4;
    if (h->relocated != 0) {
        int off = *(unsigned short *)((char *)h - 2);
        char *base = (char *)h - off;
        size = size + ((char *)h - base);
        if (usesAligned(self)) {
            g_activeSystemAllocator->FreeAligned(base, size);
        } else if (usesSized(self)) {
            g_activeSystemAllocator->FreeSized(base, size);
        } else {
            g_activeSystemAllocator->Free(base);
        }
    } else {
        char *base = (char *)h - 4;
        if (usesAligned(self)) {
            g_activeSystemAllocator->FreeAligned(base, size + 4);
        } else if (usesSized(self)) {
            g_activeSystemAllocator->FreeSized(base, size + 4);
        } else {
            g_activeSystemAllocator->Free(base);
        }
    }
}

void *igMallocMemoryPool_ReallocateBlock(igMallocMemoryPoolView *self, char *p, unsigned size) {
    TaggedBlockHeader *h;
    unsigned end;
    unsigned aligned;
    int big;
    char *base;
    char *block;
    unsigned kept;
    unsigned total;
    unsigned index;
    unsigned newOverhead;
    unsigned slot;
    unsigned newSize;
    unsigned oldOverhead;
    unsigned used;
    TaggedBlockHeader *fresh;
    h = (TaggedBlockHeader *)(p - 4);
    if (((TaggedTailByte *)(p - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(p - 12);
    }
    big = h->big;
    if (big == 0) {
        used = h->size;
        kept = used;
    } else {
        used = h->size;
        kept = used + (h->sizeHigh << 19);
    }
    if (big == 1) {
        used += h->sizeHigh << 19;
    }
    used = (used + 3) & ~3;
    total = used + (h->words + 1) * 4;
    oldOverhead = big == 0 ? 4 : 12;
    slot = (unsigned)self->_poolIndex >> 1;
    if (size >= 0x80000 || slot >= 32) {
        newOverhead = 12;
    } else {
        newOverhead = 4;
    }
    base = (char *)h - 4;
    newSize = size + (newOverhead + 4);
    if (newOverhead + 4 < oldOverhead + 4) {
        newSize += oldOverhead - newOverhead;
    }
    if (h->relocated != 0) {
        char *moved = (char *)igMallocMemoryPool_AllocateBlock(self, size);
        if (moved != 0) {
            memcpy(moved, p, kept < size ? kept : size);
            igMallocMemoryPool_FreeBlock(self, (unsigned char *)p);
        }
        return moved;
    }
    if (usesAligned(self)) {
        block = (char *)g_activeSystemAllocator->ReallocateAligned(base, newSize, total + 4);
    } else if (usesSized(self)) {
        block = (char *)g_activeSystemAllocator->ReallocateSized(base, newSize, total + 4);
    } else {
        block = (char *)g_activeSystemAllocator->Reallocate(base, newSize);
    }
    if (block == 0) {
        return 0;
    }
    if (newOverhead + 4 != oldOverhead + 4) {
        memmove(block + (newOverhead + 4), block + (oldOverhead + 4), kept < size ? kept : size);
    }
    fresh = (TaggedBlockHeader *)(block + 4);
    index = (unsigned)self->_poolIndex >> 1;
    fresh->poolLow = index;
    fresh->relocated = 0;
    fresh->marked = 0;
    fresh->used = 0;
    if (size >= 0x80000 || index >= 32) {
        fresh->sizeHigh = size >> 19;
        fresh->poolHigh = index >> 5;
        fresh->big = 1;
        fresh->extraBig = 1;
        fresh->extraUsed = 0;
        fresh->extraMarked = 0;
        fresh->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        fresh->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    fresh->words = ((end - aligned) >> 2) - 1;
    fresh->size = size;
    return (char *)fresh + (fresh->big == 0 ? 4 : 12);
}



void *igMallocMemoryPool_AllocateAlignedBlock(igMallocMemoryPoolView *self, unsigned alignment, unsigned size) {
    unsigned overhead;
    unsigned total;
    char *block;
    char *p;
    TaggedBlockHeader *h;
    int id;
    unsigned end;
    unsigned aligned;
    unsigned slot;
    unsigned minimum = self->_alignment;
    alignment = minimum < alignment ? alignment : minimum;
    if (alignment <= 3) {
        alignment = 4;
    }
    slot = (unsigned)self->_poolIndex >> 1;
    total = size + alignment;
    if (size >= 0x80000 || slot >= 32) {
        overhead = 12;
    } else {
        overhead = 4;
    }
    total += overhead;
    if (usesAligned(self)) {
        block = (char *)(g_activeSystemAllocator)->AllocateAligned(total);
    } else if (usesSized(self)) {
        block = (char *)(g_activeSystemAllocator)->AllocateSized(total);
    } else {
        block = (char *)(g_activeSystemAllocator)->Allocate(total);
    }
    if (block == 0) {
        return 0;
    }
    p = (char *)((unsigned)(block + alignment) & ~(alignment - 1)) - overhead;
    if (!(p > block)) {
        p += alignment;
    }
    ((short *)p)[-1] = p - block;
    h = (TaggedBlockHeader *)p;
    id = self->GetPoolIndex() >> 1;
    h->poolLow = id;
    h->relocated = alignment != 0;
    h->marked = 0;
    h->used = 0;
    if (size >= 0x80000 || id >= 32) {
        h->sizeHigh = size >> 19;
        h->poolHigh = id >> 5;
        h->big = 1;
        h->extraBig = 1;
        h->extraUsed = 0;
        h->extraMarked = 0;
        h->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        h->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    h->words = ((end - aligned) >> 2) - 1;
    h->size = size;
    return (char *)h + (h->big == 0 ? 4 : 12);
}


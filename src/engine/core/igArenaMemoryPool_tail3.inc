/* Print the pool's statistics: the igMemoryPool block, then the arena's sizes, address range, arena
 * counts and option names. */
void igArenaMemoryPool_PrintStatistics(igArenaMemoryPoolView *self, char *title) {
    char flagsText[256];
    char heapCheckText[64];
    char messageLevelText[64];
    char *messageLevel;
    char *heapCheck;
    char *flags;
    int named;
    igMemoryPool_PrintStatistics((igMemoryPool *)self, title);
    named = ((ObjectSystemView *)g_objectSystem[0])->auxObjectList != 0;
    messageLevel = named ? FUN_00312140(messageLevelText, 64, self->_messageLevel, igArenaMemoryPool_GetMessageLevelMetaEnum()) : (char *)DAT_004f7910;
    heapCheck = named ? FUN_00312140(heapCheckText, 64, self->_heapIntegrityCheckLevel, igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum()) : (char *)DAT_004f7910;
    flags = named ? FUN_00312020(flagsText, 256, self->_poolOptionFlags, igArenaMemoryPool_GetArenaMemoryPoolFlagsMetaEnum()) : (char *)DAT_004f7910;
    igReport_Printf(DAT_004fc1e0, self->vfunc_44(), (int)self->vfunc_36(), self->vfunc_26(), self->getLowestAddress(), self->getHighestAddress(),
                 igArenaMemoryPool_GetArenaCount(self), igArenaMemoryPool_GetArenaHighCount(self), self->GetPoolIndex(), flags, heapCheck, messageLevel);
    igReport_Flush();
}

/* Add one memory-dump region per arena block (blocks holds start/end pairs), sorted into `list`. */
void igArenaMemoryPool_CollectMemoryRegions(igArenaMemoryPoolView *self, igDataList *list) {
    char annotation[140];
    ArenaState *arena = self->_arenaState;
    int i;
    const char *poolName;
    DumpRegion *entry;
    DumpRegion *created;
    int *block;

    if (self->isActive() != 0) {
        i = 0;
        if (arena->blockCount) {
            while (i < arena->blockCount) {
                poolName = (const char *)Memory_GetPoolName((int)self);
                sprintf(annotation, text_Pool_d_of_d_tot_0x_06x, i / 2 + 1, arena->blockCount / 2, (long long)(int)self->vfunc_36());
                created = DumpRegion_Allocate(sizeof(DumpRegion));
                if (created != 0) {
                    created = DumpRegion_Init(created);
                }
                entry = created;
                created->start = arena->blocks[i];
                block = i + arena->blocks;
                entry->size = block[1] - block[0];
                DumpRegion_SetAnnotation(entry, annotation);
                DumpRegion_SetPoolName(entry, poolName);
                List_InsertWords(list, List_LowerBound(list, &entry, (Cmp)DumpRegion_CompareStart), 1, &entry);
                i = i + 2;
            }
        }
    }
}

void igArenaMemoryPool_CheckHeapLocked(int *arg0, igArenaMemoryPoolView *arg1) {
    igArenaMemoryPool_Lock(arg1);
    igResult r = arg1->vfunc_103();
    igArenaMemoryPool_Unlock(arg1);
    *arg0 = r.v;
}

void igArenaMemoryPool_VerifyHeap(int *status, igArenaMemoryPoolView *self) {
    igResult r = igArenaMemoryPool_CheckHeap(self);
    FUN_00310c00(self);
    *status = r.v;
}

igResult igArenaMemoryPool_CheckHeap(igArenaMemoryPoolView *self) {
    ArenaState *arena = self->_arenaState;
    igResult result;
    int i;
    int r;

    result = g_resultSuccess;
    if (arena->blockCount == 0) {
        return g_resultSuccess;
    }
    if (arena->blocks == 0 || arena->blockCapacity == 0) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cec == 0) {
                r = igReportNotice(text_igArenaMemoryPool_checkHeap_E69);
                if (r != 1 && r == 2) {
                    GPR_00554cec = 1;
                }
            }
        }
        result = g_resultFailure;
    }
    if (arena->blockCount < 0 || arena->blockCapacity < 0 || arena->blockCount > arena->blockCapacity) {
        if (self->_messageLevel >= 3 && GPR_00554cf0 == 0) {
            r = igReportNotice(text_igArenaMemoryPool_checkHeap_E70);
            if (r != 1 && r == 2) {
                GPR_00554cf0 = 1;
            }
        }
        return g_resultFailure;
    }
    for (i = 0; i < arena->blockCount; i += 2) {
        int *p = &arena->blocks[i];
        if (FUN_00312790(self, i, (char *)p[0], (char *)p[1]) == g_resultFailure) {
            result = g_resultFailure;
            break;
        }
    }
    return result;
}

igResult FUN_00312790(igArenaMemoryPoolView *self, int index, char *cur, char *end) {
    char *hi = self->getHighestAddress();
    char *lo = self->getLowestAddress();
    /* Declared with the walk's other pointers, ahead of the flag: `n` and `ok` are the two values kept in
     * argument registers, and the later-numbered one, `ok`, takes a0. */
    TaggedBlockHeader *n;
    unsigned int size = 0;
    int count = 0;
    bool ok = false;
    if (cur < lo || hi < cur) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cf4 == 0) {
                int r = igReportNotice(DAT_004fc490, index, cur, lo, hi);
                if (r != 1 && r == 2) {
                    GPR_00554cf4 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < lo || hi < end) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cf8 == 0) {
                int r = igReportNotice(DAT_004fc500, index, end, lo, hi);
                if (r != 1 && r == 2) {
                    GPR_00554cf8 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < cur) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cfc == 0) {
                int r = igReportNotice(DAT_004fc570, index, end, cur);
                if (r != 1 && r == 2) {
                    GPR_00554cfc = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (!((TaggedBlockHeader *)cur)->used) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554d00 == 0) {
                int r = igReportNotice(DAT_004fc5e0);
                if (r != 1 && r == 2) {
                    GPR_00554d00 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    while (cur < end) {
        TaggedBlockHeader *h = (TaggedBlockHeader *)cur;
        unsigned int sz = h->size;
        if (h->big == 1) {
            sz += h->sizeHigh << 19;
        }
        sz = (sz + 3) & ~3;
        size = sz + (h->words + 1) * 4;
        int min = self->_smallestChunkSize;
        n = (TaggedBlockHeader *)(cur + size);
        if (size < min) {
            if (end - cur <= min) {
                ok = true;
                break;
            }
            unsigned int nsz;
            if (n->big == 0) {
                nsz = n->size;
            } else {
                nsz = n->size + (n->sizeHigh << 19);
            }
            if (nsz < min) {
                if (end - (char *)n <= min * 2) {
                    ok = true;
                    break;
                }
            }
            goto bad;
        }
        if ((char *)n > end || (char *)n < cur) {
            goto bad;
        }
        cur = (char *)n;
        count++;
    }
    if (cur != end && !ok) {
bad:
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554d04 == 0) {
                int r = igReportNotice(DAT_004fc660, cur, index, count, size);
                if (r != 1 && r == 2) {
                    GPR_00554d04 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    return g_resultSuccess;
}

/* dlmalloc's sYSTRIm: gives the pages at the end of the top chunk back to the system, keeping `pad`
 * bytes and, unless forced, the pool's pre-size. */
int FUN_00314510(igArenaMemoryPoolView *self, unsigned int pad, int force) {
    ArenaState *state = self->_arenaState;
    unsigned int topSize;
    int extra;
    char *released;
    unsigned int pageSize = state->pageSize;
    if (state->top != state->bins[1] && self->_size == 0) {
        TaggedBlockHeader *top = (TaggedBlockHeader *)state->top;
        unsigned int payload = alignedPayloadSize(top);
        topSize = payload + (top->words + 1) * 4;
        extra = ((topSize - pad - ((self->_smallestChunkSize + 7) & ~7) + (pageSize - 1)) / pageSize - 1) * pageSize;
        if (self->_preSize != 0 && !force) {
            if (self->_systemAllocated - extra < self->_preSize) {
                unsigned int surplus = (int)self->_systemAllocated - self->_preSize;
                extra = ((surplus + (pageSize - 1)) / pageSize - 1) * pageSize;
            }
        }
        if (force) {
            self->_poolPreSized = 0;
        }
        if (extra > 0) {
            released = state->top + topSize - extra;
            self->vfunc_106(released, extra);
            state->f2044 -= extra;
            initChunkHeader((TaggedBlockHeader *)state->top, (unsigned int)-1, topSize - extra, (unsigned int)self->_poolIndex >> 1, 0);
            ((TaggedBlockHeader *)state->top)->used = 1;
            self->vfunc_111(released, -extra);
            if (self->_heapIntegrityCheckLevel >= 2) {
                FUN_00310c00(self);
            }
            return 1;
        }
    }
    return 0;
}

bool igArenaMemoryPool_Trim(igArenaMemoryPoolView *self, int pad) {
    int count;
    int cap;
    ArenaState *a;
    int i;
    bool trimmed;
    a = self->_arenaState;
    trimmed = false;
    FUN_00318b40(self);
    if (self->_size != 0) {
        return false;
    }
    count = a->blockCount;
    if (count < 0 || (cap = a->blockCapacity) < 0 || count > cap) {
        if (self->_messageLevel >= 3) {
            if (GPR_00554d1c == 0) {
                int r = igReportNotice(text_igArenaMemoryPool_trim_E76_Arena);
                if (r != 1 && r == 2) {
                    GPR_00554d1c = 1;
                }
            }
        }
        return false;
    }
    for (i = a->blockCount - 2; i >= 0; i -= 2) {
        if (igArenaMemoryPool_TrimArenaBlock(self, i, a->blocks[i], a->blocks[i + 1]) == g_resultSuccess) {
            if (i < a->blockCount - 2) {
                memcpy(a->blocks + i, a->blocks + (i + 2), (a->blockCount - (i + 2)) * 4);
            }
            trimmed = true;
            a->blocks[a->blockCount - 1] = 0;
            a->blocks[a->blockCount - 2] = 0;
            a->blockCount = a->blockCount - 2;
        }
    }
    FUN_00314510(self, a->f1992, pad);
    return trimmed;
}

void igArenaMemoryPool_RemoveFreeChunksInRange(int *arg0, igArenaMemoryPool *arg1, unsigned int arg2, unsigned int arg3) {
    char *base;
    int i;
    char *head;
    unsigned int cur;
    int prev;
    base = (char *)arg1->_arenaState;
    head = base + 72;
    for (i = 1; i < 96; i++, head += 20) {
        cur = NEXT(head);
        while (cur != (unsigned)head) {
            if (cur >= arg2 && cur < arg3) {
                prev = PREV(cur);
                cur = NEXT(cur);
                NEXT(prev) = cur;
                PREV(cur) = prev;
            } else {
                cur = NEXT(cur);
            }
        }
    }
    cur = *(unsigned *)(base + 48);
    if (cur != 0 && cur >= arg2 && cur < arg3) {
        *(int *)(base + 48) = 0;
    }
    *arg0 = g_resultSuccess.v;
}

/* dlmalloc's malloc_consolidate: empties the fast bins, merging each chunk with its free neighbours
 * and putting the result on the unsorted list or into the top chunk. A state not yet set up is
 * initialised instead. */
void FUN_00318b40(igArenaMemoryPoolView *self) {
    ArenaState *state;
    TaggedBlockHeader **fb;
    TaggedBlockHeader **maxfb;
    TaggedBlockHeader *p;
    unsigned int size;
    TaggedBlockHeader *nextp;
    TaggedBlockHeader *unsortedBin;
    TaggedBlockHeader *firstUnsorted;
    TaggedBlockHeader *nextchunk;
    unsigned int nextsize;
    unsigned int prevsize;
    int nextinuse;
    if (self->_heapIntegrityCheckLevel >= 3) {
        ArenaHeapCheck check(self);
    }
    state = self->_arenaState;
    if (state->maxFast != 0) {
        state->maxFast &= ~2;
        unsortedBin = (TaggedBlockHeader *)state->bins[1];
        maxfb = &state->fastBins[(state->maxFast >> 3) - 2];
        fb = &state->fastBins[0];
        do {
            if ((p = *fb) != 0) {
                *fb = 0;
                do {
                    if (self->_heapIntegrityCheckLevel > 0) {
                        igArenaMemoryPool_CheckInUseChunk(self, p);
                    }
                    nextp = chunkLinks(p)->forward;
                    {
                        unsigned int payload = alignedPayloadSize(p);
                        size = payload + (p->words + 1) * 4;
                    }
                    nextchunk = (TaggedBlockHeader *)((char *)p + size);
                    {
                        unsigned int payload = alignedPayloadSize(nextchunk);
                        nextsize = payload + (nextchunk->words + 1) * 4;
                    }
                    if (!p->used) {
                        prevsize = ((unsigned int *)p)[-1];
                        size += prevsize;
                        p = (TaggedBlockHeader *)((char *)p - prevsize);
                        unlinkChunk(p);
                    }
                    if ((char *)nextchunk != state->top) {
                        nextinuse = ((TaggedBlockHeader *)((char *)nextchunk + nextsize))->used;
                        nextchunk->used = 0;
                        if (!nextinuse) {
                            size += nextsize;
                            unlinkChunk(nextchunk);
                        }
                        firstUnsorted = chunkLinks(unsortedBin)->forward;
                        chunkLinks(unsortedBin)->forward = p;
                        chunkLinks(firstUnsorted)->back = p;
                        setChunkBytes(p, size);
                        p->used = 1;
                        chunkLinks(p)->back = unsortedBin;
                        chunkLinks(p)->forward = firstUnsorted;
                        {
                            unsigned int payload = alignedPayloadSize(p);
                            *(unsigned int *)((char *)p + (payload + (p->words + 1) * 4) - 4) = size;
                        }
                    } else {
                        size += nextsize;
                        setChunkBytes(p, size);
                        p->used = 1;
                        state->top = (char *)p;
                    }
                } while ((p = nextp) != 0);
            }
        } while (fb++ != maxfb);
    } else {
        FUN_0030f220(self);
        if (self->_heapIntegrityCheckLevel >= 2) {
            FUN_00310c00(self);
        }
    }
}

/* dlmalloc's mEMALIGn: allocates with room to spare, then gives back the part before the aligned
 * address and, when it is big enough to stand as a chunk, the part after the request. */
void *FUN_0031b5d0(igArenaMemoryPoolView *self, unsigned int alignment, unsigned int bytes) {
    unsigned int nb;
    char *m;
    TaggedBlockHeader *p;
    char *brk;
    TaggedBlockHeader *newp;
    unsigned int newsize;
    unsigned int leadsize;
    TaggedBlockHeader *remainder;
    unsigned int remainderSize;
    unsigned int size;
    int r;
    if (self->_heapIntegrityCheckLevel >= 3) {
        ArenaHeapCheck check(self);
    }
    nb = 0;
    if (alignment <= 8) {
        return FUN_00315170(self, bytes);
    }
    if (alignment < ((self->_smallestChunkSize + 7) & ~7)) {
        alignment = (self->_smallestChunkSize + 7) & ~7;
    }
    if ((alignment & (alignment - 1)) != 0) {
        unsigned int a = 16;
        while (a < alignment) {
            a <<= 1;
        }
        alignment = a;
    }
    if (bytes >= (unsigned int)-32) {
        if (self->vfunc_23(bytes, 1) == 0) {
            return 0;
        }
    } else {
        nb = (bytes + headerBytesFor(bytes, (unsigned int)self->_poolIndex >> 1) + 7) & ~7;
        if (nb < self->_smallestChunkSize) {
            nb = self->_smallestChunkSize;
        }
    }
    m = (char *)FUN_00315170(self, nb + alignment + ((self->_smallestChunkSize + 7) & ~7));
    if (m == 0) {
        return 0;
    }
    p = (TaggedBlockHeader *)(m - 4);
    if (((TaggedTailByte *)(m - 1))->extended == 1) {
        p = (TaggedBlockHeader *)(m - 12);
    }
    size = chunkBytes(p);
    if ((unsigned int)m % alignment != 0) {
        brk = (char *)(((unsigned int)m + alignment - 1) & -(int)alignment) - headerBytesFor(bytes, (unsigned int)self->_poolIndex >> 1);
        if ((unsigned int)(brk - (char *)p) < ((self->_smallestChunkSize + 7) & ~7)) {
            brk += alignment;
        }
        newp = (TaggedBlockHeader *)brk;
        leadsize = brk - (char *)p;
        newsize = size - leadsize;
        remainderSize = newsize - nb;
        if (remainderSize >= self->_smallestChunkSize) {
            newsize -= remainderSize;
        } else {
            remainderSize = 0;
        }
        remainder = (TaggedBlockHeader *)(brk + newsize);
        if (chunkIsMapped(p)) {
            ((unsigned int *)newp)[-1] = leadsize + ((unsigned int *)p)[-1];
            initChunkHeader(newp, (unsigned int)-1, newsize, (unsigned int)self->_poolIndex >> 1, 1);
            newp->used = 0;
            return chunkMemory(newp);
        }
        initChunkHeader(newp, bytes, newsize, (unsigned int)self->_poolIndex >> 1, 0);
        newp->used = 1;
        remainder->used = 1;
        if (remainderSize != 0) {
            initChunkHeader(remainder, (unsigned int)-1, remainderSize, (unsigned int)self->_poolIndex >> 1, 0);
            remainder->used = 1;
            ((TaggedBlockHeader *)((char *)remainder + remainderSize))->used = 1;
        }
        {
            int used = chunkUsedBit(p);
            initChunkHeader(p, (unsigned int)-1, leadsize, (unsigned int)self->_poolIndex >> 1, 0);
            p->used = used;
        }
        FUN_00318110(self, chunkMemory(p));
        if (remainderSize != 0) {
            FUN_00318110(self, chunkMemory(remainder));
        } else {
            igReport_Printf(DAT_004fd2c0);
            igReport_Flush();
        }
        p = newp;
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(newsize >= nb && (unsigned int)chunkMemory(p) % alignment == 0) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554d4c == 0) {
                r = igReportNotice(text_igArenaMemoryPool_Invalid_or_cor_2, p, DAT_004fd2e0);
                if (r != 1 && r == 2) {
                    GPR_00554d4c = 1;
                }
            }
        }
    } else if (!chunkIsMapped(p)) {
        if (size >= nb + self->_smallestChunkSize) {
            remainder = (TaggedBlockHeader *)((char *)p + nb);
            remainderSize = size - nb;
            initChunkHeader(remainder, (unsigned int)-1, remainderSize, (unsigned int)self->_poolIndex >> 1, 0);
            remainder->used = 1;
            newsize = size - remainderSize;
            setChunkPayload(p, bytes, newsize);
            FUN_00318110(self, chunkMemory(remainder));
        } else {
            setChunkPayload(p, bytes, size);
        }
    }
    if (self->_heapIntegrityCheckLevel > 0) {
        igArenaMemoryPool_CheckInUseChunk(self, p);
    }
    return chunkMemory(p);
}

igResult igArenaMemoryPool_Configure(igArenaMemoryPool *pool, igMemoryPoolInfo *info) {
    igResult result;
    result = igMemoryPool_Configure((void **)pool, (void *)info);
    const char *options = igMemoryPoolInfo_options(info);
    const char *integrityCheck = igMemoryPoolInfo_checking(info);
    const char *messages = igMemoryPoolInfo_messages(info);
    if (options) {
        int flags = 0;
        if (strstr(options, ((char *)text_Fill))) flags |= 2;
        if (strstr(options, ((char *)text_Zero))) flags |= 4;
        if (strstr(options, text_Sentinels)) flags |= 1;
        if (strstr(options, text_Contiguous)) flags |= 0x10;
        if (strstr(options, ((char *)text_AutoLock))) flags |= 8;
        if (strstr(options, ((char *)text_SystemMemoryExhausted))) flags |= 0x80;
        if (strstr(options, text_PreSizeReached)) flags |= 0x40;
        if (strstr(options, ((char *)text_MaxSizeReached))) flags |= 0x20;
        if (pool == (igArenaMemoryPool *)((ObjectSystemView **)g_objectSystem)[0]->bootstrapPool && (flags & 1) != (pool->_poolOptionFlags & 1)) {
            flags ^= 1;
        }
        igArenaMemoryPool_SetPoolOptionFlags(pool, flags);
    }
    if (integrityCheck) {
        int level = pool->_heapIntegrityCheckLevel;
        if (strstr(integrityCheck, text_NoChecking)) {
            level = 0;
        } else if (strstr(integrityCheck, text_LightChecking)) {
            level = 1;
        } else if (strstr(integrityCheck, text_ModerateChecking)) {
            level = 2;
        } else if (strstr(integrityCheck, text_HeavyChecking)) {
            level = 3;
        }
        pool->_heapIntegrityCheckLevel = level;
    }
    if (messages) {
        int level = pool->_messageLevel;
        if (strstr(messages, ((char *)text_NoMessages))) {
            level = 0;
        } else if (strstr(messages, ((char *)text_ErrorMessages))) {
            level = 1;
        } else if (strstr(messages, ((char *)text_WarningMessages))) {
            level = 2;
        } else if (strstr(messages, ((char *)text_Notifications))) {
            level = 3;
        }
        pool->_messageLevel = level;
    }
    return result;
}

void igArenaMemoryPool_Activate(igArenaMemoryPoolView *arg0) {
    igResult sp2C;
    if (arg0->_isActive == 0) {
        arg0->vfunc_51();
        arg0->_systemAllocated = 0;
        arg0->_isActive = 1;
        arg0->_poolPreSized = 0;
        if (arg0->_poolOptionFlags & 8) {
            sp2C = arg0->vfunc_34(1);
        }
        if (arg0->_preSize != 0) {
            arg0->Free(arg0->Allocate(0x10));
        }
    }
}

void igArenaMemoryPool_Reset(igArenaMemoryPool *self) {
    int arenaState;

    if (self->_size != 0) {
        ((igMemoryPoolView *)self)->vfunc_51();
        self->_systemAllocated = 0;
        arenaState = self->_arenaState;
        if (arenaState != 0) {
            memset(arenaState, 0, 0x814);
        }
    } else {
        ((igMemoryPoolView *)self)->Trim(1);
    }
}

void igArenaMemoryPool_Deactivate(igArenaMemoryPoolView *p) {
    if (p->_isActive != 0) {
        p->_isActive = 0;
        p->vfunc_31();
    }
}

/* Getter for the reflected `_isActive` member (igBoolMetaField at +116). */

unsigned char igArenaMemoryPool_IsActive(igArenaMemoryPool *self) {
    return self->_isActive;
}

/* IgArenaMemoryPool slot 26, returns the reflected _rawMemory block pointer (+124). */
int igArenaMemoryPool_GetRawMemory(igArenaMemoryPool *self) {
    return self->_rawMemory;
}

void igArenaMemoryPool_SetRawMemory(int *out, igArenaMemoryPoolView *p, int rawMemory, long long size, unsigned char isAlchemyMemory) {
    if (p->_isActive == 0) {
        p->_rawMemory = rawMemory;
        p->_arenaState->rawMemory = rawMemory;
        unsigned long long usable = size & 0xFFFFFFFFFFFFFFFCULL;
        p->_size = usable;
        p->_isAlchemyMemory = isAlchemyMemory;
        p->_arenaState->f2044 = (int)usable;
        p->_arenaState->f2048 = (int)usable;
        p->_arenaState->systemBytes = (int)usable;
        p->vfunc_51();
        p->_systemAllocated = 0;
        p->_updateGlobalStatistics = isAlchemyMemory;
        *out = g_resultSuccess.v;
    } else {
        *out = g_resultFailure.v;
    }
}

/* Getter for the reflected `_isAlchemyMemory` member (igBoolMetaField at +128). */

unsigned char igArenaMemoryPool_IsAlchemyMemory(igArenaMemoryPool *self) {
    return self->_isAlchemyMemory;
}

/* igMemoryPool slot 29 (vtable +116): constant 0 for the arena pool. This is the predicate
 * igAllocator_EncodeIndex calls on an allocator: zero selects the primary allocator list (even
 * encoded index), nonzero the secondary list. igMallocMemoryPool also returns 0; igPageMemoryPool
 * and igStackMemoryPool return 1. The receiver is not read. */
int Gap__Core__igArenaMemoryPool__vfunc_29(void) {
    return 0;
}

static inline void releaseAllocationLock(igArenaMemoryPool *p) {
    igSemaphoreView *x = (igSemaphoreView *)p->_allocationLock;
    if (x) {
        x->_refCount = x->_refCount - 1;
        if (((unsigned long long)((long long)(int)x->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(x);
    }
}

void igArenaMemoryPool_EnableAllocationLock(int *ret, igArenaMemoryPool *p, int flag) {
    int fl;
    if (flag != 0) {
        fl = p->_poolOptionFlags | 8;
    } else {
        fl = p->_poolOptionFlags & ~8;
    }
    igArenaMemoryPool_SetPoolOptionFlags(p, fl);
    if ((unsigned char)flag == 0) {
        igSmartPointer<igSemaphoreView> lock((igSemaphoreView *)p->_allocationLock, kRetainReference);
        releaseAllocationLock(p);
        p->_allocationLock = 0;
        if (lock.p != 0) {
            lock->wait(1);
            lock->destroy();
        }
    } else if ((unsigned char)flag == 1) {
        if (p->_allocationLock != 0) { *ret = g_resultSuccess.v; return; }
        igSmartPointer<igSemaphoreView> created((igSemaphoreView *)igSemaphore_Create((int)(((void *)igObject_GetAllocator((int)p)))));
        created->create();
        igSemaphoreView *t = created.p;
        if (t) t->_refCount = t->_refCount + 1;
        releaseAllocationLock(p);
        p->_allocationLock = (int)t;
    }
    *ret = g_resultSuccess.v;
}

/* igArenaMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (set to 1 by the engine init) through the output-first argument; same leaf as
 * igMemoryPool_TransferAllocation and igMallocMemoryPool slot 24. */
void igArenaMemoryPool_SetSize(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

long long igArenaMemoryPool_GetSize(igArenaMemoryPool *arg0) {
    long long temp_v0;

    temp_v0 = arg0->_size;
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return arg0->_systemAllocated;
}

/* The comparison is written `arg2 <= lim`, not `lim >= arg2`, and the store is repeated in both
 * arms. */
void igArenaMemoryPool_SetMaxSize(int *arg0, char *arg1, unsigned long long arg2) {
    unsigned long long lim = *(unsigned long long *)(arg1 + 160);
    if (lim == 0 || arg2 <= lim) {
        *(unsigned long long *)(arg1 + 152) = arg2;
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

/* Accessor: the arena's reflected _maxSize field (igUnsignedLongMetaField, +152). */
long long igArenaMemoryPool_GetMaxSize(igArenaMemoryPool *self) {
    return self->_maxSize;
}

void igArenaMemoryPool_SetPreSize(int *arg0, void *arg1, int arg2) {
    *(int *)((char *)(arg1) + 168) = arg2;
    *(int *)((char *)(arg1) + 196) = 0;
    if (((igMemoryPoolView *)arg1)->isActive() != 0) {
        ((igMemoryPoolView *)arg1)->Free(((igMemoryPoolView *)arg1)->Allocate(0x10));
    }
    *arg0 = g_resultSuccess.v;
}

/* IgArenaMemoryPool virtual getter 44. Returns the reflected `_preSize` field
 * (igUnsignedIntMetaField, +168). */
int igArenaMemoryPool_GetPreSize(igArenaMemoryPool *self) {
    return self->_preSize;
}

/* Setter for the pool's _alignment (a 16-bit field at +172). It reports through a status word,
 * always the "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
void igArenaMemoryPool_SetAlignment(int *outStatus, igArenaMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_resultSuccess.v;
}

/* Getter for the reflected `_alignment` member (igUnsignedShortMetaField at +172). */

unsigned short igArenaMemoryPool_GetAlignment(igArenaMemoryPool *self) {
    return self->_alignment;
}

/* Setter for the pool's _elementSize (+144). It reports through a status word, always the
 * "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
void igArenaMemoryPool_SetElementSize(int *outStatus, igArenaMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *outStatus = g_resultSuccess.v;
}

/* IgArenaMemoryPool slot 40, returns the reflected _elementSize (+144). */
int igArenaMemoryPool_GetElementSize(igArenaMemoryPool *self) {
    return self->_elementSize;
}

long long Gap__Core__igArenaMemoryPool__vfunc_46(igArenaMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

/* Accessor: the arena's reflected _localNetAllocated statistic (igLongMetaField, +24). */
long long igArenaMemoryPool_GetLocalNetAllocated(igArenaMemoryPool *self) {
    return self->_localNetAllocated;
}

/* Accessor: the arena's reflected _localNetAllocatedWithOverhead statistic (igLongMetaField, +56). */
long long igArenaMemoryPool_GetLocalNetAllocatedWithOverhead(igArenaMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long igArenaMemoryPool_GetLocalNetAllocatedHigh(void *arg0) {
    return *(long long *)((char *)arg0 + 32);
}

long long igArenaMemoryPool_GetLocalNetAllocatedWithOverheadHigh(void *arg0) {
    return *(long long *)((char *)arg0 + 64);
}

int igArenaMemoryPool_GetArenaCount(void *arg0) {
    int temp_v1;
    int var_v0;

    temp_v1 = *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2028);
    var_v0 = temp_v1 >> 1;
    if (temp_v1 < 0) {
        var_v0 = (int) (temp_v1 + 1) >> 1;
    }
    return var_v0;
}

int igArenaMemoryPool_GetArenaHighCount(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2032);
}

long long Gap__Core__igArenaMemoryPool__vfunc_101(void *arg0) {
    long long temp_v0;

    temp_v0 = *(long long *)((char *)(arg0) + 160);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return *(long long *)((char *)(arg0) + 136);
}

long long igArenaMemoryPool_GetFreeSize(igArenaMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

void *igArenaMemoryPool_AllocateElement(igArenaMemoryPoolView *self)
{
    return self->Allocate(self->_elementSize);
}

void igArenaMemoryPool_Lock(void *arg0) {
    igResult sp1C;
    void **temp_a1;

    temp_a1 = (void **)((igArenaMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp1C = ((igSemaphoreView *)(temp_a1))->wait(1);
    }
}

void igArenaMemoryPool_Unlock(void *arg0) {
    igResult sp1C;
    void **temp_a1;

    temp_a1 = (void **)((igArenaMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp1C = ((igSemaphoreView *)(temp_a1))->signal();
    }
}

int igArenaMemoryPool_UnlockAndReturn(void *arg0, int arg1) {
    igResult sp2C;
    void **temp_a1;

    temp_a1 = (void **)((igArenaMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp2C = ((igSemaphoreView *)(temp_a1))->signal();
    }
    return arg1;
}

void *igArenaMemoryPool_Allocate(igArenaMemoryPoolView *self, unsigned int size)
{
    return self->MemoryOperation(0, size, self->_alignment);
}

void *igArenaMemoryPool_AllocateAligned(igArenaMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->MemoryOperation(0, size, alignment);
}

static inline int flag2(igArenaMemoryPoolView *p) { return (p->_poolOptionFlags & 2) != 0; }

static inline int flag4(igArenaMemoryPoolView *p) { return (p->_poolOptionFlags & 4) != 0; }

void *igArenaMemoryPool_Callocate(igArenaMemoryPoolView *self, int count, int size) {
    int total = count * size;
    void *p = self->MemoryOperation(0, total, self->_alignment);
    if (p != 0) {
        if (total != 0) {
            if (flag2(self) || !flag4(self)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

int igArenaMemoryPool_CallocateAligned(igArenaMemoryPoolView *t, int n, int m, unsigned int alignment) {
    int total = n * m;
    int p = (int)t->MemoryOperation(0, total, alignment);
    if (p != 0) {
        if (total != 0) {
            int f = t->_poolOptionFlags;
            if (((f & 2) ? 1 : 0) || !((f & 4) ? 1 : 0)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

void *igArenaMemoryPool_Reallocate(igArenaMemoryPoolView *self, void *block, unsigned int size)
{
    return self->MemoryOperation(block, size, self->_alignment);
}

void *igArenaMemoryPool_ReallocateAligned(igArenaMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->MemoryOperation(block, size, alignment);
}

void igArenaMemoryPool_GangAllocAligned(int *arg0) {
    *arg0 = g_resultFailure.v;
}

static inline char *blockHeader(char *p) {
    char *h = p - 4;
    if (((TaggedTailByte *)(p - 1))->extended == 1) h = p - 12;
    return h;
}

static inline char *padRecord(char *h) {
    if (((TaggedBlockHeader *)h)->relocated) return h - 10;
    return h - 8;
}

void Gap__Core__igArenaMemoryPool__freeSized(igArenaMemoryPoolView *self, unsigned int size, char **block) {
    char *q = padRecord(blockHeader(*block));
    self->_localFreeCount += *(unsigned short *)(q + 2);
    self->_localNetAllocationCount -= size;
    self->Free((char *)((int)q - 4) - 4);
}

void igArenaMemoryPool_SetDefaults(igArenaMemoryPoolView *self) {
    int v;
    igMemoryPool_SetDefaults(self);
    self->_refCount = 0;
    ((igRefCountWord *)&self->_refCount)->bits.count = 1;
    ((char *)self)[7] = 0;
    self->_arenaState = (ArenaState *)g_activeSystemAllocator[0]->Allocate(0x814);
    if (self->_arenaState == 0 && GPR_00554d64 == 0) {
        v = igReportError(text_Unable_to_allocate_memory_for_ar);
        if (v != 1) {
            if (v == 2)
                GPR_00554d64 = 1;
        }
    }
    memset(self->_arenaState, 0, 0x814);
    self->_rawMemory = 0;
    self->_isAlchemyMemory = 0;
    self->_systemAllocated = 0;
    self->vfunc_51();
    self->_maxSize = 0xFFFFFFFFFFFFFFFFULL;
    self->_size = 0;
    self->_preSize = 0;
    self->_alignment = 1;
    releaseRefObject(self->_eventTracker);
    self->_eventTracker = 0;
    self->_isActive = 0;
    DAT_00587200[0] = DAT_00587200[0] + 1;
    releaseRefObject(self->_allocationLock);
    self->_allocationLock = 0;
    self->_poolIndex = 0;
    self->_heapIntegrityCheckLevel = 0;
    self->_messageLevel = 1;
    self->_poolOptionFlags = DAT_004c2370[0] & ~8;
    self->_poolPreSized = 0;
    self->_smallestChunkSize = 16;
    if (self->_arenaState->blocks == 0) {
        self->_arenaState->blocks = (int *)g_activeSystemAllocator[0]->AllocateAligned(0x200, 4);
        if (self->_arenaState->blocks == 0 && GPR_00554d68 == 0) {
            v = igReportError(text_Unable_to_allocate_memory_for_ar);
            if (v != 1) {
                if (v == 2)
                    GPR_00554d68 = 1;
            }
        }
        self->_arenaState->blockCapacity = 0x200;
        self->_arenaState->blockCount = 0;
        self->_arenaState->maxBlockPairs = 0;
        self->_arenaState->lowestAddress = -1;
        self->_arenaState->highestAddress = 0;
    }
}

void igArenaMemoryPool_Shutdown(igArenaMemoryPoolView *arg0) {
    int *name;
    int r;
    ArenaState *state;
    int *blocks;

    if (arg0->_size == 0) {
        FUN_00318b40(arg0);
    }
    if ((int)arg0->_localNetAllocated != 0) {
        name = ((int *)Memory_GetPoolName((int)arg0));
        arg0->vfunc_102();
        if ((arg0->_messageLevel >= 3) && (GPR_00554d6c == 0)) {
            long long netAllocated = arg0->_localNetAllocated;
            name = name ? name : &DAT_004f7910[0];
            r = igReportNotice(DAT_004fd670, name, arg0->_poolIndex, (int)netAllocated);
            if ((r != 1) && (r == 2)) {
                GPR_00554d6c = 1;
            }
        }
        arg0->vfunc_88();
    } else if (arg0->_localNetAllocationCount != 0) {
        name = ((int *)Memory_GetPoolName((int)arg0));
        if ((arg0->_messageLevel >= 3) && (GPR_00554d70 == 0)) {
            long long netAllocationCount = arg0->_localNetAllocationCount;
            name = name ? name : &DAT_004f7910[0];
            r = igReportNotice(DAT_004fd6d0, name, arg0->_poolIndex, (int)netAllocationCount);
            if ((r != 1) && (r == 2)) {
                GPR_00554d70 = 1;
            }
        }
        arg0->vfunc_88();
    }
    int t = (arg0->_poolOptionFlags & 0x200) != 0;
    if (!t && igArenaMemoryPool_GetArenaHighCount(arg0) > 1U) {
        name = ((int *)Memory_GetPoolName((int)arg0));
        if ((arg0->_messageLevel >= 3) && (GPR_00554d74 == 0)) {
            name = name ? name : &DAT_004f7910[0];
            r = igReportNotice(DAT_004fd730, name, arg0->_poolIndex, igArenaMemoryPool_GetArenaHighCount(arg0));
            if ((r != 1) && (r == 2)) {
                GPR_00554d74 = 1;
            }
        }
    }
    DAT_00587208[0] += (int)arg0->_localNetAllocated;
    DAT_00587210[0] += (int)arg0->_localNetAllocatedWithOverhead;
    if (arg0->_size == 0) {
        arg0->Trim(0);
    }
    state = arg0->_arenaState;
    if (state != 0) {
        blocks = state->blocks;
        if (blocks != 0) {
            g_activeSystemAllocator[0]->Free(blocks);
            arg0->_arenaState->blockCapacity = 0;
            arg0->_arenaState->blockCount = 0;
            arg0->_arenaState->maxBlockPairs = 0;
        }
        g_activeSystemAllocator[0]->Free((void *)arg0->_arenaState);
        arg0->_arenaState = 0;
    }
    arg0->_arenaState = 0;
    DAT_00587200[0] -= 1;
}

void *igArenaMemoryPool_Initialize(igArenaMemoryPool *arg0) {
    igMemoryPool_Initialize((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void *igArenaMemoryPool_Construct(igArenaMemoryPool *arg0, int extra1) {
    igMemoryPool_Construct((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    if (arg0 != 0) {
        igArenaMemoryPool_Initialize(arg0);
    }
    return arg0;
}

void *igArenaMemoryPool_CopyConstruct(igArenaMemoryPool *arg0, int extra1) {
    igMemoryPool_CopyConstruct((igMemoryPool *)arg0, (igMemoryPool *)extra1);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void igArenaMemoryPool_Destruct(void **self) {
    ((igMemoryPoolView *)(self))->vfunc_98();
    igMemoryPool_Destruct((int)self);
}

void igArenaMemoryPool_Free(igArenaMemoryPoolView *self, void *block)
{
    self->MemoryOperation(block, -1, self->_alignment);
}

int igArenaMemoryPool_OwnsAllocation(void *self, unsigned char *p) {
    TaggedBlockHeader *h;
    unsigned off;
    unsigned idx;
    if (p == 0) {
        return 0;
    }
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        if (off < 0x100011) {
            p = p - off;
        } else {
            return 0;
        }
    }
    h = (TaggedBlockHeader *)(p - 4);
    if (((TaggedTailByte *)(p - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(p - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        idx = h->poolLow;
    } else {
        idx = h->poolLow + (h->poolHigh << 5);
    }
    return ((void *)igAllocator_ResolveEncodedIndex(idx * 2)) == self;
}

int Gap__Core__igArenaMemoryPool__vfunc_83(void) {
    return 1;
}

int igArenaMemoryPool_GetAllocationSize(int arg0, unsigned char *p) {
    unsigned int off;
    unsigned int v;
    TaggedBlockHeader *h;
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        p = p - off;
        h = (TaggedBlockHeader *)(p - 4);
        if (((TaggedTailByte *)(p - 1))->extended == 1) {
            h = (TaggedBlockHeader *)(p - 12);
        }
        if (h == 0) {
            return 0;
        }
        if (h->big == 0) {
            v = h->size;
        } else {
            v = h->size + (h->sizeHigh << 19);
        }
        return v - (off + 4);
    }
    h = (TaggedBlockHeader *)(p - 4);
    if (((TaggedTailByte *)(p - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(p - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        return h->size;
    }
    return h->size + (h->sizeHigh << 19);
}

void igArenaMemoryPool_SetPoolOptionFlags(igArenaMemoryPool *p, int f) {
    int r;
    if ((f & 1) != (p->_poolOptionFlags & 1)) {
        if (((igMemoryPoolView *)p)->isActive() != 0) {
            if (p->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, p);
                if (GPR_00554d78 == 0) {
                    r = igReportNotice(DAT_004fd7a0);
                    if (r != 1) { if (r == 2) { GPR_00554d78 = 1; } }
                }
            }
            return;
        }
    }
    p->_poolOptionFlags = f;
}

int igArenaMemoryPool_GetEventTracker(void *arg0) {
    return *(int *)((char *)(arg0) + 176);
}

void igArenaMemoryPool_SetEventTracker(int *arg0, igObject *arg1) {
    igObject *o;
    if (arg1 == 0 || (int *)((void *)igObject_GetAllocator((int)arg1)) != arg0) {
        if (arg1 != 0) {
            arg1->_refCount++;
        }
        o = (igObject *)arg0[44];
        if (o != 0) {
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0[44] = (int)arg1;
    }
}

void igArenaMemoryPool_Dump(void) {

}

int igArenaMemoryPool_GetPoolIndex(void *arg0) {
    return *(int *)((char *)(arg0) + 180);
}

void igArenaMemoryPool_SetPoolIndex(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 180) = arg1;
    if (*(int *)((char *)(arg0) + 180) >= 0x40) {
        *(int *)((char *)(arg0) + 200) = 0x18;
    } else {
        *(int *)((char *)(arg0) + 200) = 0x10;
    }
}

static inline int acceptsPoolIndex(igArenaMemoryPoolView *pool, int index) {
    if (pool->_poolIndex < 64 && index >= 64) return 0;
    return 1;
}

void igArenaMemoryPool_TransferAllocation(int *arg0, igArenaMemoryPoolView *arg1, char *arg2, igMemoryPoolView *arg3) {
    int v = arg3->GetPoolIndex();
    int ok;
    TaggedBlockHeader *h;
    int a;
    ok = acceptsPoolIndex(arg1, v);
    if (ok != 0) {
        if (*(unsigned int *)(arg2 - 4) == 0xAAAAAAAF) {
            unsigned int off = *(unsigned int *)(arg2 - 8);
            if (off < 0x100011) {
                arg2 = arg2 - off;
            } else {
                *arg0 = g_resultFailure.v;
                return;
            }
        }
        h = (TaggedBlockHeader *)(arg2 - 4);
        if (((TaggedTailByte *)(arg2 - 1))->extended == 1) {
            h = (TaggedBlockHeader *)(arg2 - 12);
        }
        a = arg3->GetPoolIndex() >> 1;
        h->poolLow = a;
        if (h->big == 1) {
            h->poolHigh = a >> 5;
        }
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

int igArenaMemoryPool_CanTransferTo(void *arg0, void **arg1) {
    int temp_v0;
    int var_v0;

    temp_v0 = ((igMemoryPoolView *)(arg1))->GetPoolIndex();
    if ((*(int *)((char *)(arg0) + 180) < 0x40) && (temp_v0 >= 0x40)) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        return 1;
    }
    return 0;
}

int igArenaMemoryPool_GetAllocationPoolIndex(int arg0, unsigned char *p) {
    TaggedBlockHeader *a0; unsigned int off, v;
    if (p == 0) return -1;
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        if (off < 0x100011) { p = p - off; } else { return -1; }
    }
    a0 = (TaggedBlockHeader *)(p - 4);
    if (((TaggedTailByte *)(p - 1))->extended == 1) { a0 = (TaggedBlockHeader *)(p - 12); }
    if (a0 == 0) return -1;
    if (a0->big == 0) { v = a0->poolLow; } else { v = a0->poolLow + (a0->poolHigh << 5); }
    return v * 2;
}

void Gap__Core__igArenaMemoryPool__constructFields(igArenaMemoryPoolView *arg0, int arg1) {
    int t;
    arg0->_arenaState = (ArenaState *)g_activeSystemAllocator[0]->Allocate(0x814);
    memset(arg0->_arenaState, 0, 0x814);
    if (arg0->_arenaState->blocks == 0) {
        arg0->_arenaState->blocks = (int *)g_activeSystemAllocator[0]->AllocateAligned(0x200, 4);
        if (arg0->_arenaState->blocks == 0 && GPR_00554d7c == 0) {
            t = igReportError(text_Unable_to_allocate_memory_for_ar);
            if (t != 1 && t == 2) {
                GPR_00554d7c = 1;
            }
        }
        arg0->_arenaState->blockCapacity = 0x200;
        arg0->_arenaState->blockCount = 0;
        arg0->_arenaState->maxBlockPairs = 0;
        arg0->_arenaState->lowestAddress = -1;
        arg0->_arenaState->highestAddress = 0;
    }
    DAT_00587200[0] += 1;
    Gap__Core__igObject__constructFields((int)arg0, arg1);
}

void Gap__Core__igArenaMemoryPool__destructFields(igArenaMemoryPool *self) {
    ((igMemoryPoolView *)self)->vfunc_98();
    Gap__Core__igObject__destructFields((int)self);
}

void Gap__Core__igArenaMemoryPool__resetFields(igArenaMemoryPool *self, int extra1) {
    Gap__Core__igObject__resetFields((int)self, extra1);
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c2370[0];
}

unsigned int igArenaMemoryPool_SystemAllocate(igArenaMemoryPool *arg0, int arg1, int arg2) {
    unsigned int temp_a1;
    unsigned int temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    if (arg0->_size != 0) {
        return -1U;
    }
    temp_v0 = g_activeSystemAllocator[0]->vfunc_17(arg1, arg2);
    if (temp_v0 != -1U) {
        arg0->_systemAllocated = arg0->_systemAllocated + arg2;
        temp_v1 = (void *)(arg0->_arenaState);
        if (temp_v0 < (unsigned int) *(int *)((char *)(temp_v1) + 2060)) {
            *(int *)((char *)(temp_v1) + 2060) = temp_v0;
        }
        temp_v1_2 = (void *)(arg0->_arenaState);
        temp_a1 = temp_v0 + arg2;
        if ((unsigned int) *(int *)((char *)(temp_v1_2) + 2064) < temp_a1) {
            *(int *)((char *)(temp_v1_2) + 2064) = temp_a1;
        }
    }
    return temp_v0;
}

igResult igArenaMemoryPool_SystemFree(void *arg1, int arg2, long long arg3) {
    igArenaMemoryPool *f = (igArenaMemoryPool *)arg1;
    if (f->_size != 0) {
        igResult r;
        r.v = g_resultFailure.v;
        return r;
    }
    long long d = (long long)(int)arg3;
    if ((unsigned long long)d < f->_systemAllocated) {
        f->_systemAllocated = f->_systemAllocated - d;
    } else {
        f->_systemAllocated = 0;
    }
    return g_activeSystemAllocator[0]->vfunc_18(arg2, arg3);
}

void igArenaMemoryPool_GetStackSize(igArenaMemoryPoolView *self)
{
    g_activeSystemAllocator[0]->GetStackSize();
}

void Gap__Core__igArenaMemoryPool__vfunc_108(void) {

}

int igArenaMemoryPool_GetLowestAddress(void *arg0) {
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 124);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2060);
}

int igArenaMemoryPool_GetHighestAddress(void *arg0) {
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg0) + 124);
    if (temp_v1 != 0) {
        return temp_v1 + *(int *)((char *)(arg0) + 160);
    }
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2064);
}


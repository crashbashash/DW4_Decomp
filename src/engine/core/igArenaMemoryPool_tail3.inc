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
    named = ((ObjectSystemView *)g_objectSystem)->metaEnumList != 0;
    messageLevel = named ? igMetaEnum_GetValueName(messageLevelText, 64, self->_messageLevel, igArenaMemoryPool_GetMessageLevelMetaEnum()) : (char *)"";
    heapCheck = named ? igMetaEnum_GetValueName(heapCheckText, 64, self->_heapIntegrityCheckLevel, igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum()) : (char *)"";
    flags = named ? igMetaEnum_GetNamesByMask(flagsText, 256, self->_poolOptionFlags, igArenaMemoryPool_GetArenaMemoryPoolFlagsMetaEnum()) : (char *)"";
    igReport_Printf("    Pre size:                             %d\n    Raw size:                             %d\n    Raw address:                          0x%08x\n    Lowest address:                       0x%08x\n    Highest address:                      0x%08x\n    Arena count:                          %d\n    Arena count high:                     %d\n    Pool index:                           %d\n    Pool flags:                           %s\n    Check level:                          %s\n    Message Level:                        %s\n", self->GetPreSize(), (int)self->GetSize(), self->GetRawMemory(), self->GetLowestAddress(), self->GetHighestAddress(),
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

    if (self->IsActive() != 0) {
        i = 0;
        if (arena->blockCount) {
            while (i < arena->blockCount) {
                poolName = (const char *)Memory_GetPoolName((int)self);
                sprintf(annotation,"Pool %d of %d tot 0x%06x", i / 2 + 1, arena->blockCount / 2, (long long)(int)self->GetSize());
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

void igArenaMemoryPool_CheckHeapLocked(int *status, igArenaMemoryPoolView *self) {
    igArenaMemoryPool_Lock(self);
    igResult result = self->VerifyHeap();
    igArenaMemoryPool_Unlock(self);
    *status = result.v;
}

void igArenaMemoryPool_VerifyHeap(int *status, igArenaMemoryPoolView *self) {
    igResult r = igArenaMemoryPool_CheckHeap(self);
    igArenaMemoryPool_CheckMallocState(self);
    *status = r.v;
}

unsigned char g_igArenaMemoryPool_ignoreE69Notice;
unsigned char g_igArenaMemoryPool_ignoreE70Notice;

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
            if (g_igArenaMemoryPool_ignoreE69Notice == 0) {
                r = igReportNotice("igArenaMemoryPool::checkHeap(E69): No arena block list.");
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE69Notice = 1;
                }
            }
        }
        result = g_resultFailure;
    }
    if (arena->blockCount < 0 || arena->blockCapacity < 0 || arena->blockCount > arena->blockCapacity) {
        if (self->_messageLevel >= 3 && g_igArenaMemoryPool_ignoreE70Notice == 0) {
            r = igReportNotice("igArenaMemoryPool::checkHeap(E70): Arena block list data corrupted.");
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE70Notice = 1;
            }
        }
        return g_resultFailure;
    }
    for (i = 0; i < arena->blockCount; i += 2) {
        int *p = &arena->blocks[i];
        if (igArenaMemoryPool_CheckHeapBlock(self, i, (char *)p[0], (char *)p[1]) == g_resultFailure) {
            result = g_resultFailure;
            break;
        }
    }
    return result;
}

unsigned char g_igArenaMemoryPool_ignoreE71Notice;
unsigned char g_igArenaMemoryPool_ignoreE72Notice;
unsigned char g_igArenaMemoryPool_ignoreE73Notice;
unsigned char g_igArenaMemoryPool_ignoreE74Notice;
unsigned char g_igArenaMemoryPool_ignoreE75Notice;

igResult igArenaMemoryPool_CheckHeapBlock(igArenaMemoryPoolView *self, int index, char *cur, char *end) {
    char *hi = self->GetHighestAddress();
    char *lo = self->GetLowestAddress();
    /* Declared with the walk's other pointers, ahead of the flag: `n` and `ok` are the two values kept in
     * argument registers, and the later-numbered one, `ok`, takes a0. */
    TaggedBlockHeader *n;
    unsigned int size = 0;
    int count = 0;
    bool ok = false;
    if (cur < lo || hi < cur) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE71Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::checkHeap(E71): At index %d, block (0x%x) is not in a valid range (0x%x-0x%x).", index, cur, lo, hi);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE71Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < lo || hi < end) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE72Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::checkHeap(E72): At index %d, block end (0x%x) is not in a valid range (0x%x-0x%x).", index, end, lo, hi);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE72Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < cur) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE73Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::checkHeap(E73): At index %d, the end block (0x%x) is less than the start block (0x%x).", index, end, cur);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE73Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (!((TaggedBlockHeader *)cur)->used) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE74Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::checkHeap(E74): Arena (0x%x) corrupted.  First block should have had previous in use bit set.");
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE74Notice = 1;
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
            if (g_igArenaMemoryPool_ignoreE75Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::checkHeap(E75): The block at 0x%x at block index %d chunk index %d has an invalid chunk size 0x%x.", cur, index, count, size);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE75Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    return g_resultSuccess;
}

unsigned char g_arenaNoticeE102Silenced;
unsigned char g_arenaNoticeE66Silenced;
unsigned char g_arenaNoticeE105Silenced;
unsigned char g_arenaNoticeE106Silenced;
unsigned char g_arenaNoticeE103Silenced;

/* dlmalloc's sYSMALLOc: the top chunk cannot hold `nb` bytes, so the arena asks the system for
 * more. It first tries to extend the top in place, to the page after the new top plus one smallest
 * chunk; failing that it takes a separate block, closes the old top off with two fenceposts and
 * frees what is left of it. A pre-sized pool asks for all of its pre-size at once. When the system
 * has nothing, the pool is asked to give memory back and the request is retried. */
void *igArenaMemoryPool_SystemMalloc(igArenaMemoryPoolView *self, unsigned int nb, unsigned int bytes) {
    ArenaState *state;
    unsigned int pageMask;
    int tries;
    TaggedBlockHeader *oldTop;
    unsigned int oldSize;
    char *oldEnd;
    char *newEnd;
    char *newTop;
    int size;
    unsigned int preSize;
    unsigned int room;
    unsigned int brk;
    TaggedBlockHeader *p;
    int r;
    state = self->_arenaState;
    pageMask = state->pageSize - 1;
    tries = 0;
    if (self->_poolPreSized == 1 && hasPoolOption(self->_poolOptionFlags, 0x40)) {
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(self->_poolPreSized == 1) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_arenaNoticeE102Silenced == 0) {
                r = igReportNotice("igArenaMemoryPool(E102): Pre size value of %d bytes reached.  %d bytes already allocated.", self->_preSize, (unsigned int)self->_localNetAllocated);
                if (r != 1 && r == 2) {
                    g_arenaNoticeE102Silenced = 1;
                }
            }
        }
        self->_poolPreSized = 2;
    }
    for (;;) {
        oldTop = state->top;
        oldSize = chunkBytes(oldTop);
        if (oldTop == &state->bins[1].header) {
            oldSize = 0;
        } else if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !IS_ARENA_CHUNK(self, oldTop) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_arenaNoticeE66Silenced == 0) {
                r = igReportNotice("igArenaMemoryPool::%s - Possibly corrupt memory block at: 0x%x","igArenaSystemMalloc (E66)", oldTop);
                if (r != 1 && r == 2) {
                    g_arenaNoticeE66Silenced = 1;
                }
            }
        }
        oldEnd = (char *)oldTop + oldSize;
        newEnd = (char *)(((unsigned int)oldTop + nb + ((self->_smallestChunkSize + 7) & ~7) + pageMask) & ~pageMask);
        newTop = (char *)oldTop + nb;
        size = newEnd - oldEnd;
        preSize = self->_preSize;
        if (preSize != 0) {
            if (size + self->_systemAllocated < preSize) {
                room = preSize - (int)self->_localNetAllocatedWithOverhead;
                size = (room + pageMask) & ~pageMask;
                self->_poolPreSized = 1;
                newEnd = oldEnd + size;
            } else {
                if (self->_poolPreSized == 0 && hasPoolOption(self->_poolOptionFlags, 0x40)) {
                    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(self->_poolPreSized == 1) && self->_messageLevel > 0) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_arenaNoticeE105Silenced == 0) {
                            r = igReportNotice("igArenaMemoryPool(E105): Pre size value of %d bytes reached.  %d bytes already allocated.", self->_preSize, (unsigned int)self->_localNetAllocated);
                            if (r != 1 && r == 2) {
                                g_arenaNoticeE105Silenced = 1;
                            }
                        }
                    }
                }
                self->_poolPreSized = 2;
            }
        }
        brk = self->SystemAllocate((int)oldEnd, size);
        if (brk != (unsigned int)-1) {
            state->top = (TaggedBlockHeader *)newTop;
            initChunkHeader(self, state->top, (unsigned int)-1, newEnd - newTop, 0);
            state->top->used = 1;
            self->UpdateBlockList(oldEnd, size);
            initChunkHeader(self, oldTop, bytes, nb, 0);
            oldTop->used = 1;
            if (self->_heapIntegrityCheckLevel > 0) {
                igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)oldTop, nb);
            }
            return chunkMemory(oldTop);
        }
        size = (nb + ((self->_smallestChunkSize + 7) & ~7) + 4 + pageMask) & ~pageMask;
        preSize = self->_preSize;
        if (preSize != 0) {
            if (size + self->_systemAllocated < preSize) {
                room = preSize - (int)self->_localNetAllocatedWithOverhead;
                size = (room + pageMask) & ~pageMask;
                self->_poolPreSized = 1;
            } else {
                if (self->_poolPreSized == 0 && hasPoolOption(self->_poolOptionFlags, 0x40)) {
                    if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(self->_poolPreSized == 1) && self->_messageLevel > 0) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_arenaNoticeE106Silenced == 0) {
                            r = igReportNotice("igArenaMemoryPool(E106): Pre size value of %d bytes reached.  %d bytes already allocated.", self->_preSize, (unsigned int)self->_localNetAllocated);
                            if (r != 1 && r == 2) {
                                g_arenaNoticeE106Silenced = 1;
                            }
                        }
                    }
                }
                self->_poolPreSized = 2;
            }
        }
        brk = self->SystemAllocate(0, size);
        if (brk != (unsigned int)-1) {
            newEnd = (char *)brk + size;
            p = (TaggedBlockHeader *)brk;
            if ((brk & 7) != 4) {
                p = (TaggedBlockHeader *)(((brk + 4) | 4) & ~3);
            }
            newTop = (char *)p + nb;
            state->top = (TaggedBlockHeader *)newTop;
            initChunkHeader(self, state->top, (unsigned int)-1, newEnd - newTop, 0);
            state->top->used = 1;
            self->UpdateBlockList((char *)p, newEnd - (char *)p);
            initChunkHeader(self, p, bytes, nb, 0);
            p->used = 1;
            if (self->_heapIntegrityCheckLevel > 0) {
                igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)p, nb);
            }
            if ((oldSize & 7) != 0) {
                oldSize &= ~7;
            }
            if (oldSize >= ((self->_smallestChunkSize + 7) & ~7) + 8) {
                unsigned int trimThreshold;
                unsigned int shortened = oldSize - 8;
                setChunkBytes(oldTop, shortened);
                initFencepost((TaggedBlockHeader *)((char *)oldTop + (oldSize - 8)));
                ((TaggedBlockHeader *)((char *)oldTop + (oldSize - 8)))->used = 1;
                initFencepost((TaggedBlockHeader *)((char *)oldTop + (oldSize - 4)));
                ((TaggedBlockHeader *)((char *)oldTop + (oldSize - 4)))->used = 1;
                trimThreshold = state->trimThreshold;
                state->trimThreshold = (unsigned int)-1;
                igArenaMemoryPool_FreeChunk(self, chunkMemory(oldTop));
                state->trimThreshold = trimThreshold;
            } else if (oldSize != 0) {
                initFencepost(oldTop);
                oldTop->used = 1;
                initFencepost(chunkAtOffset(oldTop, 4));
                chunkAtOffset(oldTop, 4)->used = 1;
            }
            return chunkMemory(p);
        }
        if (tries < 2) {
            tries++;
            if (self->TrimAllPools(0) != 0) {
                continue;
            }
            if (self->TrimAllPools(1) != 0) {
                continue;
            }
        }
        if (self->HandleOutOfMemory(bytes, 3) != 0) {
            continue;
        }
        if (hasPoolOption(self->_poolOptionFlags, 0x80)) {
            SystemMemoryStatistics stats;
            g_activeSystemAllocator->GetStatistics(&stats);
            Memory_PrintPoolStatistics(0, self);
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_arenaNoticeE103Silenced == 0) {
                    r = igReportNotice("igArenaMemoryPool(E103): %s memory exhausted.\nThis pool's (index %d) statistics:\n    Total allocated:                      %u\n    Total freed:                          %u\n    Net allocated:                        %u\n    Net allocated high:                   %u\n    Total allocated with overhead:        %u\n    Total freed with overhead:            %u\n    Net allocated with overhead:          %u\n    Net allocated high with overhead:     %u\n    Total allocation count:               %u\n    Total free count:                     %u\n    Net allocation count:                 %u\n    Net allocation count high:            %u\nThe system pool's statistics:\n    totalSystemMemorySize:                %d\n    allocationSpan:                       %d\n    maximumSpan:                          %d\n    allocatedAndInUse:                    %d\n    allocatedAndAvailable:                %d\n    freeFromTop:                          %d\n", self->_size != 0 ?"Raw" :"System", self->_poolIndex,
                                       (unsigned int)self->getLocalAllocated(), (unsigned int)self->getLocalFreed(), (unsigned int)self->getLocalNetAllocated(),
                                       (unsigned int)self->getLocalNetAllocatedHigh(), (unsigned int)self->getLocalAllocatedWithOverhead(),
                                       (unsigned int)self->getLocalFreedWithOverhead(), (unsigned int)self->getLocalNetAllocatedWithOverhead(),
                                       (unsigned int)self->getLocalNetAllocatedWithOverheadHigh(), (unsigned int)self->getLocalAllocationCount(),
                                       (unsigned int)self->getLocalFreeCount(), (unsigned int)self->getLocalNetAllocationCount(),
                                       (unsigned int)self->getLocalNetAllocationCountHigh(), stats.totalSystemMemorySize,
                                       stats.allocationSpan, stats.maximumSpan, stats.allocatedAndInUse,
                                       stats.allocatedAndAvailable, stats.freeFromTop);
                    if (r != 1 && r == 2) {
                        g_arenaNoticeE103Silenced = 1;
                    }
                }
            }
        }
        return 0;
    }
}

/* dlmalloc's sYSTRIm: gives the pages at the end of the top chunk back to the system, keeping `pad`
 * bytes and, unless forced, the pool's pre-size. */
int igArenaMemoryPool_SystemTrim(igArenaMemoryPoolView *self, unsigned int pad, int force) {
    ArenaState *state = self->_arenaState;
    unsigned int topSize;
    int extra;
    char *released;
    unsigned int pageSize = state->pageSize;
    if (state->top != &state->bins[1].header && self->_size == 0) {
        TaggedBlockHeader *top = state->top;
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
            released = (char *)state->top + topSize - extra;
            self->SystemFree(released, extra);
            state->sbrkedMem -= extra;
            initChunkHeader(self, state->top, (unsigned int)-1, topSize - extra, 0);
            state->top->used = 1;
            self->UpdateBlockList(released, -extra);
            if (self->_heapIntegrityCheckLevel >= 2) {
                igArenaMemoryPool_CheckMallocState(self);
            }
            return 1;
        }
    }
    return 0;
}

unsigned char g_igArenaMemoryPool_ignoreE76Notice;

bool igArenaMemoryPool_Trim(igArenaMemoryPoolView *self, int pad) {
    int count;
    int cap;
    ArenaState *a;
    int i;
    bool trimmed;
    a = self->_arenaState;
    trimmed = false;
    igArenaMemoryPool_MallocConsolidate(self);
    if (self->_size != 0) {
        return false;
    }
    count = a->blockCount;
    if (count < 0 || (cap = a->blockCapacity) < 0 || count > cap) {
        if (self->_messageLevel >= 3) {
            if (g_igArenaMemoryPool_ignoreE76Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::trim(E76): Arena block list data corrupted.");
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE76Notice = 1;
                }
            }
        }
        return false;
    }
    for (i = a->blockCount - 2; i >= 0; i -= 2) {
        if (igArenaMemoryPool_TrimArenaBlock(self, i, (char *)a->blocks[i], (char *)a->blocks[i + 1]) == g_resultSuccess) {
            if (i < a->blockCount - 2) {
                memcpy(a->blocks + i, a->blocks + (i + 2), (a->blockCount - (i + 2)) * 4);
            }
            trimmed = true;
            a->blocks[a->blockCount - 1] = 0;
            a->blocks[a->blockCount - 2] = 0;
            a->blockCount = a->blockCount - 2;
        }
    }
    igArenaMemoryPool_SystemTrim(self, a->topPad, pad);
    return trimmed;
}

unsigned char g_igArenaMemoryPool_ignoreE77Notice;
unsigned char g_igArenaMemoryPool_ignoreE78Notice;
unsigned char g_igArenaMemoryPool_ignoreE79Notice;
unsigned char g_igArenaMemoryPool_ignoreE80Notice;
unsigned char g_igArenaMemoryPool_ignoreE81Notice;

/* Walks one system block of the arena. When every chunk in it is free it unlinks them, moves the top
 * pointer off the block if it was there, and gives the block's pages back to the system. */
igResult igArenaMemoryPool_TrimArenaBlock(igArenaMemoryPoolView *self, int index, char *cur, char *end) {
    char *top = (char *)self->_arenaState->top;
    char *walk = cur;
    char *hi = self->GetHighestAddress();
    char *lo = self->GetLowestAddress();
    TaggedBlockHeader *n;
    unsigned int size = 0;
    int count = 0;
    int inUse = 0;
    bool ok = false;
    if (cur < lo || hi < cur) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE77Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::trimArenaBlock(E77): At index %d, block (0x%x) is not in a valid range (0x%x-0x%x).", index, cur, lo, hi);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE77Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < lo || hi < end) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE78Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::trimArenaBlock(E78): At index %d, block end (0x%x) is not in a valid range (0x%x-0x%x).", index, end, lo, hi);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE78Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < cur) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE79Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::trimArenaBlock(E79): At index %d, the end block (0x%x) is less than the start block (0x%x).", index, end, cur);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE79Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (!((TaggedBlockHeader *)cur)->used) {
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE80Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::trimArenaBlock(E80): Arena (0x%x) corrupted.  First block should have had previous in use bit set.");
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE80Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    /* A block that starts at the top chunk has nothing to walk: straight to the release. */
    if (cur == top) {
        goto reset;
    }
    while (walk < end) {
        TaggedBlockHeader *h = (TaggedBlockHeader *)walk;
        unsigned int sz = h->size;
        if (h->big == 1) {
            sz += h->sizeHigh << 19;
        }
        sz = (sz + 3) & ~3;
        size = sz + (h->words + 1) * 4;
        n = (TaggedBlockHeader *)(walk + size);
        if (walk == top) {
            walk = (char *)n;
            break;
        }
        int min = self->_smallestChunkSize;
        if (size < min) {
            if (end - walk <= min) {
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
        if (n->used) {
            inUse++;
        }
        if ((char *)n > end || (char *)n < walk) {
            goto bad;
        }
        walk = (char *)n;
        count++;
    }
    if (walk != end && !ok) {
bad:
        if (self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE81Notice == 0) {
                int r = igReportNotice("igArenaMemoryPool::trimArenaBlock(E81): The block at 0x%x at block index %d chunk index %d has an invalid chunk size 0x%x.  Arena start is 0x%x, end is 0x%x", walk, index, count, size, cur, end);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE81Notice = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (inUse == 0) {
        igResult removed;
        igArenaMemoryPool_RemoveFreeChunksInRange((int *)&removed, self, (unsigned int)cur, (unsigned int)end);
reset:
        if (top >= cur && top < end) {
            ArenaState *state = self->_arenaState;
            state->top = &state->bins[1].header;
        }
        unsigned int pageMask = g_activeSystemAllocator->GetPageSize() - 1;
        cur = (char *)((unsigned int)cur & ~pageMask);
        end = (char *)(~pageMask & (unsigned int)(end + pageMask));
        self->SystemFree(cur, end - cur);
        return g_resultSuccess;
    }
    return g_resultFailure;
}

void igArenaMemoryPool_RemoveFreeChunksInRange(int *status, igArenaMemoryPoolView *self, unsigned int start, unsigned int end) {
    ArenaState *state;
    int i;
    char *head;
    unsigned int cur;
    int prev;
    state = self->_arenaState;
    head = (char *)&state->bins[1];
    for (i = 1; i < 96; i++, head += 20) {
        cur = NEXT(head);
        while (cur != (unsigned)head) {
            if (cur >= start && cur < end) {
                prev = PREV(cur);
                cur = NEXT(cur);
                NEXT(prev) = cur;
                PREV(cur) = prev;
            } else {
                cur = NEXT(cur);
            }
        }
    }
    cur = (unsigned int)state->lastRemainder;
    if (cur != 0 && cur >= start && cur < end) {
        state->lastRemainder = 0;
    }
    *status = g_resultSuccess.v;
}

unsigned char g_arenaNoticeE59Silenced;
unsigned char g_arenaNoticeE60Silenced;
unsigned char g_arenaNoticeE67Silenced;

/* dlmalloc's mALLOc: a fast bin or small bin of the exact size, then the unsorted list (binning what
 * does not fit), the request's large bin, the next non-empty bin by the bin map, and last the top
 * chunk. A pool with the top-only option goes straight to the top. When the top is too small, a pool
 * on raw memory, or one not pre-sized, consolidates the fast bins and tries once more before the
 * system is asked. */
void *igArenaMemoryPool_Malloc(igArenaMemoryPoolView *self, unsigned int bytes) {
    ArenaState *state;
    unsigned int nb;
    unsigned int idx;
    TaggedBlockHeader *bin;
    TaggedBlockHeader **fb;
    TaggedBlockHeader *victim;
    unsigned int size;
    int victimIndex;
    TaggedBlockHeader *remainder;
    unsigned int remainderSize;
    unsigned int block;
    unsigned int bit;
    unsigned int map;
    TaggedBlockHeader *fwd;
    TaggedBlockHeader *bck;
    int attempt;
    int r;
    if (self->_heapIntegrityCheckLevel >= 3) {
        ArenaHeapCheck check(self);
    }
    state = self->_arenaState;
    attempt = 1;
    nb = 0;
    if (bytes >= (unsigned int)-32) {
        if (self->HandleOutOfMemory(bytes, attempt) == 0) {
            return 0;
        }
    } else {
        unsigned int smallest = self->_smallestChunkSize;
        nb = (bytes + headerBytesFor(bytes, (unsigned int)self->_poolIndex >> 1) + 7) & ~7;
        if (nb < smallest) {
            nb = smallest;
        }
    }
    for (;;) {
        if (hasPoolOption(self->_poolOptionFlags, 0x10)) {
            goto use_top;
        }
        if (!(state->maxFast & 1)) {
            if (state->maxFast == 0) {
                igArenaMemoryPool_MallocConsolidate(self);
            }
            goto use_top;
        }
        if (nb <= state->maxFast) {
            fb = &state->fastBins[(nb >> 3) - 2];
            if ((victim = *fb) != 0) {
                *fb = chunkLinks(victim)->forward;
                setChunkPayload(victim, bytes, nb);
                if (self->_heapIntegrityCheckLevel > 0) {
                    igArenaMemoryPool_CheckBlock(self, victim, nb);
                }
                return chunkMemory(victim);
            }
        }
        if (nb < 256) {
            idx = nb >> 3;
            bin = &state->bins[idx].header;
            if ((victim = chunkLinks(bin)->back) != bin) {
                setChunkPayload(victim, bytes, nb);
                TaggedBlockHeader *previous = chunkLinks(victim)->back;
                ((TaggedBlockHeader *)((char *)victim + nb))->used = 1;
                chunkLinks(bin)->back = previous;
                chunkLinks(previous)->forward = bin;
                if (self->_heapIntegrityCheckLevel > 0) {
                    igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, nb);
                }
                return chunkMemory(victim);
            }
        } else {
            idx = largeBinIndex(nb);
            if (state->maxFast & 2) {
                igArenaMemoryPool_MallocConsolidate(self);
            }
        }
        while ((victim = chunkLinks(&state->bins[1].header)->back) != &state->bins[1].header) {
            TaggedBlockHeader *previous = chunkLinks(victim)->back;
            size = chunkBytes(victim);
            if (nb < 256 && previous == &state->bins[1].header && victim == state->lastRemainder && size > nb + ((self->_smallestChunkSize + 7) & ~7)) {
                remainderSize = size - nb;
                remainder = (TaggedBlockHeader *)((char *)victim + nb);
                initChunkHeader(self, victim, bytes, nb, 0);
                victim->used = 1;
                initChunkHeader(self, remainder, (unsigned int)-1, remainderSize, 0);
                remainder->used = 1;
                *(unsigned int *)((char *)remainder + chunkBytes(remainder) - 4) = remainderSize;
                chunkLinks(&state->bins[1].header)->back = remainder;
                chunkLinks(&state->bins[1].header)->forward = remainder;
                state->lastRemainder = remainder;
                chunkLinks(remainder)->back = &state->bins[1].header;
                chunkLinks(remainder)->forward = &state->bins[1].header;
                if (self->_heapIntegrityCheckLevel > 0) {
                    igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, nb);
                }
                return chunkMemory(victim);
            }
            chunkLinks(&state->bins[1].header)->back = previous;
            chunkLinks(previous)->forward = &state->bins[1].header;
            if (size == nb) {
                ((TaggedBlockHeader *)((char *)victim + size))->used = 1;
                setChunkPayload(victim, bytes, size);
                if (self->_heapIntegrityCheckLevel > 0) {
                    igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, nb);
                }
                return chunkMemory(victim);
            }
            if (size < 256) {
                victimIndex = size >> 3;
                bck = &state->bins[victimIndex].header;
                fwd = chunkLinks(bck)->forward;
            } else {
                victimIndex = largeBinIndex(size);
                bck = &state->bins[victimIndex].header;
                fwd = chunkLinks(bck)->forward;
                if (fwd != bck) {
                    if (size < chunkBytes(chunkLinks(bck)->back)) {
                        fwd = bck;
                        bck = chunkLinks(bck)->back;
                    } else if (size >= 256) {
                        size |= 1;
                        while (size < chunkBytes(fwd)) {
                            fwd = chunkLinks(fwd)->forward;
                        }
                        bck = chunkLinks(fwd)->back;
                    }
                }
            }
            state->binMap[victimIndex >> 5] |= 1 << (victimIndex & 31);
            chunkLinks(victim)->back = bck;
            chunkLinks(victim)->forward = fwd;
            chunkLinks(fwd)->back = victim;
            chunkLinks(bck)->forward = victim;
        }
        if (nb >= 256) {
            bin = &state->bins[idx].header;
            for (victim = chunkLinks(bin)->back; victim != bin; victim = chunkLinks(victim)->back) {
                size = chunkBytes(victim);
                if (size >= nb) {
                    remainderSize = size - nb;
                    unlinkChunk(victim);
                    if (remainderSize < ((self->_smallestChunkSize + 7) & ~7)) {
                        ((TaggedBlockHeader *)((char *)victim + size))->used = 1;
                        setChunkPayload(victim, bytes, size);
                        if (self->_heapIntegrityCheckLevel > 0) {
                            igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, size);
                        }
                        return chunkMemory(victim);
                    } else {
                        remainder = (TaggedBlockHeader *)((char *)victim + nb);
                        initChunkHeader(self, victim, bytes, nb, 0);
                        victim->used = 1;
                        initChunkHeader(self, remainder, (unsigned int)-1, remainderSize, 0);
                        remainder->used = 1;
                        *(unsigned int *)((char *)remainder + chunkBytes(remainder) - 4) = remainderSize;
                        chunkLinks(&state->bins[1].header)->back = remainder;
                        chunkLinks(&state->bins[1].header)->forward = remainder;
                        chunkLinks(remainder)->back = &state->bins[1].header;
                        chunkLinks(remainder)->forward = &state->bins[1].header;
                        if (self->_heapIntegrityCheckLevel > 0) {
                            igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, nb);
                        }
                        return chunkMemory(victim);
                    }
                }
            }
        }
        ++idx;
        bin = &state->bins[idx].header;
        block = idx >> 5;
        map = state->binMap[block];
        bit = 1 << (idx & 31);
        for (;;) {
            if (bit > map || bit == 0) {
                do {
                    if (++block >= 3) {
                        goto use_top;
                    }
                } while ((map = state->binMap[block]) == 0);
                bin = &state->bins[block << 5].header;
                bit = 1;
            }
            while ((bit & map) == 0) {
                bin = nextBin(bin);
                bit <<= 1;
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(bit != 0) && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_arenaNoticeE59Silenced == 0) {
                        r = igReportNotice("igArenaMemoryPool: %s","(E59) Corrupted control structure.");
                        if (r != 1 && r == 2) {
                            g_arenaNoticeE59Silenced = 1;
                        }
                    }
                }
            }
            victim = chunkLinks(bin)->back;
            if (victim == bin) {
                state->binMap[block] = map &= ~bit;
                bin = nextBin(bin);
                bit <<= 1;
            } else {
                size = chunkBytes(victim);
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(size >= nb) && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_arenaNoticeE60Silenced == 0) {
                        r = igReportNotice("igArenaMemoryPool: Invalid or corrupted block at 0x%x - %s", victim,"(E60) Corrupted block header.");
                        if (r != 1 && r == 2) {
                            g_arenaNoticeE60Silenced = 1;
                        }
                    }
                }
                remainderSize = size - nb;
                bck = chunkLinks(victim)->back;
                chunkLinks(bin)->back = bck;
                chunkLinks(bck)->forward = bin;
                if (remainderSize < ((self->_smallestChunkSize + 7) & ~7)) {
                    ((TaggedBlockHeader *)((char *)victim + size))->used = 1;
                    setChunkPayload(victim, bytes, size);
                    if (self->_heapIntegrityCheckLevel > 0) {
                        igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, size);
                    }
                    return chunkMemory(victim);
                } else {
                    remainder = (TaggedBlockHeader *)((char *)victim + nb);
                    initChunkHeader(self, victim, bytes, nb, 0);
                    victim->used = 1;
                    initChunkHeader(self, remainder, (unsigned int)-1, remainderSize, 0);
                    remainder->used = 1;
                    *(unsigned int *)((char *)remainder + chunkBytes(remainder) - 4) = remainderSize;
                    chunkLinks(&state->bins[1].header)->back = remainder;
                    chunkLinks(&state->bins[1].header)->forward = remainder;
                    chunkLinks(remainder)->back = &state->bins[1].header;
                    chunkLinks(remainder)->forward = &state->bins[1].header;
                    if (nb < 256) {
                        state->lastRemainder = remainder;
                    }
                    if (self->_heapIntegrityCheckLevel > 0) {
                        igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, nb);
                    }
                    return chunkMemory(victim);
                }
            }
        }
    use_top:
        victim = state->top;
        size = chunkBytes(victim);
        if (size >= nb + ((self->_smallestChunkSize + 7) & ~7)) {
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !IS_ARENA_CHUNK(self, state->top) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_arenaNoticeE67Silenced == 0) {
                    r = igReportNotice("igArenaMemoryPool::%s - Possibly corrupt memory block at: 0x%x","igArena_malloc (E67)", state->top);
                    if (r != 1 && r == 2) {
                        g_arenaNoticeE67Silenced = 1;
                    }
                }
            }
            remainderSize = size - nb;
            remainder = (TaggedBlockHeader *)((char *)victim + nb);
            state->top = remainder;
            initChunkHeader(self, victim, bytes, nb, 0);
            victim->used = 1;
            initChunkHeader(self, remainder, (unsigned int)-1, remainderSize, 0);
            remainder->used = 1;
            if (self->_heapIntegrityCheckLevel > 0) {
                igArenaMemoryPool_CheckInUseBlock(self, (unsigned char *)victim, nb);
            }
            return chunkMemory(victim);
        }
        if (self->_size != 0 || self->_poolPreSized == 0) {
            if (attempt-- != 0) {
                igArenaMemoryPool_MallocConsolidate(self);
                continue;
            }
        }
        return igArenaMemoryPool_SystemMalloc(self, nb, bytes);
    }
}

/* dlmalloc's fREe: a small chunk goes on its fast bin; any other is merged with its free neighbours
 * and put on the unsorted list or into the top chunk, and a large enough result consolidates the
 * fast bins and trims the top. */
void igArenaMemoryPool_FreeChunk(igArenaMemoryPoolView *self, char *mem) {
    ArenaState *state;
    TaggedBlockHeader *p;
    unsigned int size;
    TaggedBlockHeader **fb;
    TaggedBlockHeader *nextchunk;
    unsigned int nextsize;
    int nextinuse;
    unsigned int prevsize;
    TaggedBlockHeader *bck;
    TaggedBlockHeader *fwd;
    if (self->_heapIntegrityCheckLevel >= 3) {
        ArenaHeapCheck check(self);
    }
    state = self->_arenaState;
    if (mem != 0) {
        p = (TaggedBlockHeader *)(mem - 4);
        if (((TaggedTailByte *)(mem - 1))->extended == 1) {
            p = (TaggedBlockHeader *)(mem - 12);
        }
        {
            unsigned int payload = alignedPayloadSize(p);
            size = payload + (p->words + 1) * 4;
        }
        if (self->_heapIntegrityCheckLevel > 0) {
            igArenaMemoryPool_CheckInUseChunk(self, p);
        }
        if (size <= state->maxFast) {
            state->maxFast |= 3;
            fb = &state->fastBins[(size >> 3) - 2];
            setForwardLink(p, *fb);
            *fb = p;
        } else if (!chunkIsMapped(p)) {
            state->maxFast |= 1;
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
            if (nextchunk != state->top) {
                nextinuse = ((TaggedBlockHeader *)((char *)nextchunk + nextsize))->used;
                nextchunk->used = 0;
                if (!nextinuse) {
                    unlinkChunk(nextchunk);
                    size += nextsize;
                }
                initChunkHeader(self, p, (unsigned int)-1, size, 0);
                p->used = 1;
                {
                    unsigned int payload = alignedPayloadSize(p);
                    *(unsigned int *)((char *)p + (payload + (p->words + 1) * 4) - 4) = size;
                }
                bck = &state->bins[1].header;
                fwd = chunkLinks(bck)->forward;
                chunkLinks(p)->back = bck;
                chunkLinks(p)->forward = fwd;
                chunkLinks(bck)->forward = p;
                chunkLinks(fwd)->back = p;
                if (self->_heapIntegrityCheckLevel > 0) {
                    igArenaMemoryPool_CheckFreeChunk(self, p);
                }
            } else {
                size += nextsize;
                initChunkHeader(self, p, (unsigned int)-1, size, 0);
                p->used = 1;
                state->top = p;
                if (self->_heapIntegrityCheckLevel > 0) {
                    igArenaMemoryPool_CheckChunk(self, p);
                }
            }
            if (size >= 0x20000) {
                if (state->maxFast & 2) {
                    igArenaMemoryPool_MallocConsolidate(self);
                }
                {
                    TaggedBlockHeader *top = state->top;
                    unsigned int payload = alignedPayloadSize(top);
                    if (payload + (top->words + 1) * 4 >= state->trimThreshold) {
                        igArenaMemoryPool_SystemTrim(self, state->topPad, 0);
                    }
                }
            }
        }
    }
}

/* dlmalloc's malloc_consolidate: empties the fast bins, merging each chunk with its free neighbours
 * and putting the result on the unsorted list or into the top chunk. A state not yet set up is
 * initialised instead. */
void igArenaMemoryPool_MallocConsolidate(igArenaMemoryPoolView *self) {
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
        unsortedBin = &state->bins[1].header;
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
                    if (nextchunk != state->top) {
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
                        state->top = p;
                    }
                } while ((p = nextp) != 0);
            }
        } while (fb++ != maxfb);
    } else {
        igArenaMemoryPool_InitMallocState(self);
        if (self->_heapIntegrityCheckLevel >= 2) {
            igArenaMemoryPool_CheckMallocState(self);
        }
    }
}

unsigned char g_arenaAssertNcopiesSilenced;
unsigned char g_arenaAssertNewsizeSilenced;
unsigned char g_arenaNoticeE104Silenced;

/* dlmalloc's rEALLOc, with the header's size taken into account: a request that moves the chunk
 * between the 4-byte and the 12-byte header keeps the larger header when the chunk already has it,
 * and otherwise moves the payload to its new offset. The chunk is resized in place when it is big
 * enough or can grow into the top or a free neighbour; otherwise a new chunk is allocated, the
 * payload copied and the old chunk freed. A system-mapped chunk cannot be resized. */
void *igArenaMemoryPool_Realloc(igArenaMemoryPoolView *self, char *oldmem, unsigned int bytes) {
    ArenaState *state;
    unsigned int nb;
    TaggedBlockHeader *oldp;
    unsigned int oldsize;
    TaggedBlockHeader *newp;
    unsigned int newsize;
    char *newmem;
    TaggedBlockHeader *next;
    TaggedBlockHeader *remainder;
    unsigned int remainderSize;
    unsigned int copysize;
    unsigned int ncopies;
    unsigned int *s;
    unsigned int *d;
    unsigned int oldHeader;
    unsigned int newHeader;
    bool keepHeader;
    int prevInUse;
    int r;
    if (self->_heapIntegrityCheckLevel >= 3) {
        ArenaHeapCheck check(self);
    }
    state = self->_arenaState;
    nb = 0;
    keepHeader = false;
    if (oldmem == 0) {
        return igArenaMemoryPool_Malloc(self, bytes);
    }
    if (bytes >= (unsigned int)-32) {
        if (self->HandleOutOfMemory(bytes, 1) == 0) {
            return 0;
        }
    } else {
        unsigned int smallest = self->_smallestChunkSize;
        nb = (bytes + headerBytesFor(bytes, (unsigned int)self->_poolIndex >> 1) + 7) & ~7;
        if (nb < smallest) {
            nb = smallest;
        }
    }
    for (;;) {
        oldp = (TaggedBlockHeader *)(oldmem - 4);
        if (((TaggedTailByte *)(oldmem - 1))->extended == 1) {
            oldp = (TaggedBlockHeader *)(oldmem - 12);
        }
        oldsize = chunkBytes(oldp);
        oldHeader = oldp->big == 0 ? 4 : 12;
        prevInUse = chunkUsedBit(oldp);
        newHeader = headerBytesFor(bytes, (unsigned int)self->_poolIndex >> 1);
        if (newHeader < oldHeader) {
            keepHeader = true;
            nb += oldHeader - newHeader;
            newHeader = oldHeader;
        }
        if (self->_heapIntegrityCheckLevel > 0) {
            igArenaMemoryPool_CheckInUseChunk(self, oldp);
        }
        if (!chunkIsMapped(oldp)) {
            if (oldsize >= nb) {
                if (oldsize - nb < ((self->_smallestChunkSize + 7) & ~7)) {
                    if (newHeader != oldHeader) {
                        memmove((char *)oldp + newHeader, (char *)oldp + oldHeader, bytes);
                        initChunkHeader(self, oldp, bytes, oldsize, 0);
                        oldp->used = prevInUse;
                        return chunkMemory(oldp);
                    }
                    setChunkPayload(oldp, bytes, oldsize);
                    return chunkMemory(oldp);
                }
                newp = oldp;
                newsize = oldsize;
            } else {
                next = (TaggedBlockHeader *)((char *)oldp + oldsize);
                if (next == state->top && (newsize = oldsize + chunkBytes(next)) >= nb + ((self->_smallestChunkSize + 7) & ~7)) {
                    if (newHeader != oldHeader) {
                        memmove((char *)oldp + newHeader, (char *)oldp + oldHeader, payloadSize(oldp));
                    }
                    initChunkHeader(self, oldp, bytes, nb, 0);
                    oldp->used = prevInUse;
                    state->top = (TaggedBlockHeader *)((char *)oldp + nb);
                    initChunkHeader(self, state->top, (unsigned int)-1, newsize - nb, 0);
                    state->top->used = 1;
                    return chunkMemory(oldp);
                } else if (next != state->top && !((TaggedBlockHeader *)((char *)next + chunkBytes(next)))->used && (newsize = oldsize + chunkBytes(next)) >= nb) {
                    newp = oldp;
                    unlinkChunk(next);
                } else {
                    newmem = (char *)igArenaMemoryPool_Malloc(self, bytes);
                    if (newmem == 0) {
                        return 0;
                    }
                    newp = (TaggedBlockHeader *)(newmem - 4);
                    if (((TaggedTailByte *)(newmem - 1))->extended == 1) {
                        newp = (TaggedBlockHeader *)(newmem - 12);
                    }
                    newsize = chunkBytes(newp);
                    prevInUse = chunkUsedBit(oldp);
                    if (newp == next) {
                        if (self->_heapIntegrityCheckLevel >= 3) {
                            igArenaMemoryPool_CheckMallocState(self);
                        }
                        newsize += oldsize;
                        newp = oldp;
                    } else {
                        copysize = oldsize - 4;
                        s = (unsigned int *)oldmem;
                        d = (unsigned int *)newmem;
                        ncopies = copysize / 4;
                        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(ncopies >= 3) && self->_messageLevel > 0) {
                            Memory_PrintPoolStatistics(0, self);
                            if (g_arenaAssertNcopiesSilenced == 0) {
                                r = igReportNotice("ncopies >= 3");
                                if (r != 1 && r == 2) {
                                    g_arenaAssertNcopiesSilenced = 1;
                                }
                            }
                        }
                        if (ncopies > 9) {
                            memcpy(d, s, copysize);
                        } else {
                            d[0] = s[0];
                            d[1] = s[1];
                            d[2] = s[2];
                            if (ncopies > 4) {
                                d[3] = s[3];
                                d[4] = s[4];
                                if (ncopies > 6) {
                                    d[5] = s[5];
                                    d[6] = s[6];
                                    if (ncopies > 8) {
                                        d[7] = s[7];
                                        d[8] = s[8];
                                    }
                                }
                            }
                        }
                        igArenaMemoryPool_FreeChunk(self, oldmem);
                        if (self->_heapIntegrityCheckLevel > 0) {
                            igArenaMemoryPool_CheckInUseChunk(self, newp);
                        }
                        return chunkMemory(newp);
                    }
                }
            }
            if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(newsize >= nb) && self->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, self);
                if (g_arenaAssertNewsizeSilenced == 0) {
                    r = igReportNotice("(igUnsignedInt)(newsize) >= (igUnsignedInt)(nb)");
                    if (r != 1 && r == 2) {
                        g_arenaAssertNewsizeSilenced = 1;
                    }
                }
            }
            remainderSize = newsize - nb;
            if (remainderSize == 0) {
                if (newHeader != oldHeader) {
                    memmove((char *)newp + newHeader, (char *)newp + oldHeader, bytes);
                }
                setChunkPayload(newp, bytes, nb);
                ((TaggedBlockHeader *)((char *)newp + chunkBytes(newp)))->used = 1;
                ((TaggedBlockHeader *)((char *)newp + nb))->used = 1;
            } else if (remainderSize < ((self->_smallestChunkSize + 7) & ~7)) {
                if (newHeader != oldHeader) {
                    memmove((char *)newp + newHeader, (char *)newp + oldHeader, bytes);
                }
                initChunkHeader(self, newp, bytes, newsize, 0);
                newp->used = prevInUse;
                ((TaggedBlockHeader *)((char *)newp + chunkBytes(newp)))->used = 1;
                if (self->_heapIntegrityCheckLevel > 0) {
                    igArenaMemoryPool_CheckInUseChunk(self, newp);
                }
                return chunkMemory(newp);
            } else {
                if (keepHeader) {
                    setChunkPayload(newp, bytes, nb);
                } else {
                    if (newHeader != oldHeader) {
                        memmove((char *)newp + newHeader, (char *)newp + oldHeader, bytes);
                    }
                    initChunkHeader(self, newp, bytes, nb, 0);
                    newp->used = prevInUse;
                }
                remainder = (TaggedBlockHeader *)((char *)newp + nb);
                initChunkHeader(self, remainder, (unsigned int)-1, remainderSize, 0);
                remainder->used = 1;
                ((TaggedBlockHeader *)((char *)remainder + remainderSize))->used = 1;
                igArenaMemoryPool_FreeChunk(self, chunkMemory(remainder));
            }
            if (self->_heapIntegrityCheckLevel > 0) {
                igArenaMemoryPool_CheckInUseChunk(self, newp);
            }
            return chunkMemory(newp);
        }
        if (self->_heapIntegrityCheckLevel >= 2) {
            igArenaMemoryPool_CheckMallocState(self);
        }
        if (self->HandleOutOfMemory(bytes, 3) == 0) {
            if (hasPoolOption(self->_poolOptionFlags, 0x80)) {
                SystemMemoryStatistics stats;
                g_activeSystemAllocator->GetStatistics(&stats);
                if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && self->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_arenaNoticeE104Silenced == 0) {
                        r = igReportNotice("igArenaMemoryPool(E104): %s memory exhausted.\nThis pool's (index %d) statistics:\n    Total allocated:                      %u\n    Total freed:                          %u\n    Net allocated:                        %u\n    Net allocated high:                   %u\n    Total allocated with overhead:        %u\n    Total freed with overhead:            %u\n    Net allocated with overhead:          %u\n    Net allocated high with overhead:     %u\n    Total allocation count:               %u\n    Total free count:                     %u\n    Net allocation count:                 %u\n    Net allocation count high:            %u\nThe system pool's statistics:\n    totalSystemMemorySize:                %d\n    allocationSpan:                       %d\n    maximumSpan:                          %d\n    allocatedAndInUse:                    %d\n    allocatedAndAvailable:                %d\n    freeFromTop:                          %d\n", self->_size != 0 ?"Raw" :"System", self->_poolIndex,
                                           (unsigned int)self->getLocalAllocated(), (unsigned int)self->getLocalFreed(),
                                           (unsigned int)self->getLocalNetAllocated(), (unsigned int)self->getLocalNetAllocatedHigh(),
                                           (unsigned int)self->getLocalAllocatedWithOverhead(), (unsigned int)self->getLocalFreedWithOverhead(),
                                           (unsigned int)self->getLocalNetAllocatedWithOverhead(), (unsigned int)self->getLocalNetAllocatedWithOverheadHigh(),
                                           (unsigned int)self->getLocalAllocationCount(), (unsigned int)self->getLocalFreeCount(),
                                           (unsigned int)self->getLocalNetAllocationCount(), (unsigned int)self->getLocalNetAllocationCountHigh(),
                                           stats.totalSystemMemorySize, stats.allocationSpan, stats.maximumSpan,
                                           stats.allocatedAndInUse, stats.allocatedAndAvailable, stats.freeFromTop);
                        if (r != 1 && r == 2) {
                            g_arenaNoticeE104Silenced = 1;
                        }
                    }
                }
            }
            return 0;
        }
    }
}

unsigned char g_igArenaMemoryPool_ignoreE64Notice;

/* dlmalloc's mEMALIGn: allocates with room to spare, then gives back the part before the aligned
 * address and, when it is big enough to stand as a chunk, the part after the request. */
void *igArenaMemoryPool_MallocAligned(igArenaMemoryPoolView *self, unsigned int alignment, unsigned int bytes) {
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
        return igArenaMemoryPool_Malloc(self, bytes);
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
        if (self->HandleOutOfMemory(bytes, 1) == 0) {
            return 0;
        }
    } else {
        nb = (bytes + headerBytesFor(bytes, (unsigned int)self->_poolIndex >> 1) + 7) & ~7;
        if (nb < self->_smallestChunkSize) {
            nb = self->_smallestChunkSize;
        }
    }
    m = (char *)igArenaMemoryPool_Malloc(self, nb + alignment + ((self->_smallestChunkSize + 7) & ~7));
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
            initChunkHeader(self, newp, (unsigned int)-1, newsize, 1);
            newp->used = 0;
            return chunkMemory(newp);
        }
        initChunkHeader(self, newp, bytes, newsize, 0);
        newp->used = 1;
        remainder->used = 1;
        if (remainderSize != 0) {
            initChunkHeader(self, remainder, (unsigned int)-1, remainderSize, 0);
            remainder->used = 1;
            ((TaggedBlockHeader *)((char *)remainder + remainderSize))->used = 1;
        }
        {
            int used = chunkUsedBit(p);
            initChunkHeader(self, p, (unsigned int)-1, leadsize, 0);
            p->used = used;
        }
        igArenaMemoryPool_FreeChunk(self, chunkMemory(p));
        if (remainderSize != 0) {
            igArenaMemoryPool_FreeChunk(self, chunkMemory(remainder));
        } else {
            igReport_Printf("remainder was empty.\n");
            igReport_Flush();
        }
        p = newp;
        if (self->_heapIntegrityCheckLevel > 0 && self->_messageLevel > 0 && !(newsize >= nb && (unsigned int)chunkMemory(p) % alignment == 0) && self->_messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (g_igArenaMemoryPool_ignoreE64Notice == 0) {
                r = igReportNotice("igArenaMemoryPool: Invalid or corrupted block at 0x%x - %s", p,"(E64) Corrupted block.");
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE64Notice = 1;
                }
            }
        }
    } else if (!chunkIsMapped(p)) {
        if (size >= nb + self->_smallestChunkSize) {
            remainder = (TaggedBlockHeader *)((char *)p + nb);
            remainderSize = size - nb;
            initChunkHeader(self, remainder, (unsigned int)-1, remainderSize, 0);
            remainder->used = 1;
            newsize = size - remainderSize;
            setChunkPayload(p, bytes, newsize);
            igArenaMemoryPool_FreeChunk(self, chunkMemory(remainder));
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
        if (strstr(options, ((char *)"Fill"))) flags |= 2;
        if (strstr(options, ((char *)"Zero"))) flags |= 4;
        if (strstr(options,"Sentinels")) flags |= 1;
        if (strstr(options,"Contiguous")) flags |= 0x10;
        if (strstr(options, ((char *)"AutoLock"))) flags |= 8;
        if (strstr(options, ((char *)"SystemMemoryExhausted"))) flags |= 0x80;
        if (strstr(options,"PreSizeReached")) flags |= 0x40;
        if (strstr(options, ((char *)"MaxSizeReached"))) flags |= 0x20;
        if (pool == (igArenaMemoryPool *)(*(ObjectSystemView * *)&g_objectSystem)->bootstrapPool && (flags & 1) != (pool->_poolOptionFlags & 1)) {
            flags ^= 1;
        }
        igArenaMemoryPool_SetPoolOptionFlags(pool, flags);
    }
    if (integrityCheck) {
        int level = pool->_heapIntegrityCheckLevel;
        if (strstr(integrityCheck,"NoChecking")) {
            level = 0;
        } else if (strstr(integrityCheck,"LightChecking")) {
            level = 1;
        } else if (strstr(integrityCheck,"ModerateChecking")) {
            level = 2;
        } else if (strstr(integrityCheck,"HeavyChecking")) {
            level = 3;
        }
        pool->_heapIntegrityCheckLevel = level;
    }
    if (messages) {
        int level = pool->_messageLevel;
        if (strstr(messages, ((char *)"NoMessages"))) {
            level = 0;
        } else if (strstr(messages, ((char *)"ErrorMessages"))) {
            level = 1;
        } else if (strstr(messages, ((char *)"WarningMessages"))) {
            level = 2;
        } else if (strstr(messages, ((char *)"Notifications"))) {
            level = 3;
        }
        pool->_messageLevel = level;
    }
    return result;
}

void igArenaMemoryPool_Activate(igArenaMemoryPoolView *self) {
    igResult lockResult;
    if (self->_isActive == 0) {
        self->ResetStatistics();
        self->_systemAllocated = 0;
        self->_isActive = 1;
        self->_poolPreSized = 0;
        if (self->_poolOptionFlags & 8) {
            lockResult = self->EnableAllocationLock(1);
        }
        if (self->_preSize != 0) {
            self->Free(self->Allocate(0x10));
        }
    }
}

void igArenaMemoryPool_Reset(igArenaMemoryPool *self) {
    int arenaState;

    if (self->_size != 0) {
        ((igMemoryPoolView *)self)->ResetStatistics();
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
        p->Reset();
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
        p->_arenaState->sbrkedMem = (int)usable;
        p->_arenaState->maxSbrkedMem = (int)usable;
        p->_arenaState->systemBytes = (int)usable;
        p->ResetStatistics();
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
int igArenaMemoryPool_IsSecondaryAllocator(void) {
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
            lock->Wait(1);
            lock->Destroy();
        }
    } else if ((unsigned char)flag == 1) {
        if (p->_allocationLock != 0) { *ret = g_resultSuccess.v; return; }
        igSmartPointer<igSemaphoreView> created((igSemaphoreView *)igSemaphore_Create((int)(((void *)igObject_GetAllocator((int)p)))));
        created->Create();
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

long long igArenaMemoryPool_GetSize(igArenaMemoryPool *self) {
    long long size;

    size = self->_size;
    if (size != 0) {
        return size;
    }
    return self->_systemAllocated;
}

/* The comparison is written `maxSize <= size`, not `size >= maxSize`, and the store is repeated in both
 * arms. */
void igArenaMemoryPool_SetMaxSize(int *status, igArenaMemoryPool *self, unsigned long long maxSize) {
    unsigned long long size = self->_size;
    if (size == 0 || maxSize <= size) {
        self->_maxSize = maxSize;
        *status = g_resultSuccess.v;
    } else {
        *status = g_resultFailure.v;
    }
}

/* Accessor: the arena's reflected _maxSize field (igUnsignedLongMetaField, +152). */
long long igArenaMemoryPool_GetMaxSize(igArenaMemoryPool *self) {
    return self->_maxSize;
}

void igArenaMemoryPool_SetPreSize(int *status, igArenaMemoryPoolView *self, int preSize) {
    self->_preSize = preSize;
    self->_poolPreSized = 0;
    if (self->IsActive() != 0) {
        self->Free(self->Allocate(0x10));
    }
    *status = g_resultSuccess.v;
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

long long Gap__Core__igArenaMemoryPool__vfunc_46(igArenaMemoryPool *self) {
    return self->_maxSize - self->_localNetAllocatedWithOverhead;
}

/* Accessor: the arena's reflected _localNetAllocated statistic (igLongMetaField, +24). */
long long igArenaMemoryPool_GetLocalNetAllocated(igArenaMemoryPool *self) {
    return self->_localNetAllocated;
}

/* Accessor: the arena's reflected _localNetAllocatedWithOverhead statistic (igLongMetaField, +56). */
long long igArenaMemoryPool_GetLocalNetAllocatedWithOverhead(igArenaMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long igArenaMemoryPool_GetLocalNetAllocatedHigh(igArenaMemoryPool *self) {
    return self->_localNetAllocatedHigh;
}

long long igArenaMemoryPool_GetLocalNetAllocatedWithOverheadHigh(igArenaMemoryPool *self) {
    return self->_localNetAllocatedWithOverheadHigh;
}

int igArenaMemoryPool_GetArenaCount(igArenaMemoryPoolView *self) {
    int blockCount;
    int arenaCount;

    blockCount = self->_arenaState->blockCount;
    arenaCount = blockCount >> 1;
    if (blockCount < 0) {
        arenaCount = (int) (blockCount + 1) >> 1;
    }
    return arenaCount;
}

int igArenaMemoryPool_GetArenaHighCount(igArenaMemoryPoolView *self) {
    return self->_arenaState->maxBlockPairs;
}

long long igArenaMemoryPool_GetSystemAllocated(igArenaMemoryPool *self) {
    long long size;

    size = self->_size;
    if (size != 0) {
        return size;
    }
    return self->_systemAllocated;
}

long long igArenaMemoryPool_GetFreeSize(igArenaMemoryPool *self) {
    return self->_maxSize - self->_localNetAllocatedWithOverhead;
}

void *igArenaMemoryPool_AllocateElement(igArenaMemoryPoolView *self)
{
    return self->Allocate(self->_elementSize);
}

void igArenaMemoryPool_Lock(igArenaMemoryPoolView *self) {
    igResult lockResult;
    void **lock;

    lock = (void **)self->_allocationLock;
    if (lock != 0) {
        lockResult = ((igSemaphoreView *)(lock))->Wait(1);
    }
}

void igArenaMemoryPool_Unlock(igArenaMemoryPoolView *self) {
    igResult lockResult;
    void **lock;

    lock = (void **)self->_allocationLock;
    if (lock != 0) {
        lockResult = ((igSemaphoreView *)(lock))->Signal();
    }
}

int igArenaMemoryPool_UnlockAndReturn(igArenaMemoryPoolView *self, int value) {
    igResult lockResult;
    void **lock;

    lock = (void **)self->_allocationLock;
    if (lock != 0) {
        lockResult = ((igSemaphoreView *)(lock))->Signal();
    }
    return value;
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

unsigned char g_igArenaMemoryPool_ignoreE98Notice;
unsigned char g_igArenaMemoryPool_ignoreE100Notice;

/* Gang allocation: one system block carries every requested block. The block starts with its own
 * byte count; each member is a GangRecord followed by a tagged header and the payload. */
igResult igArenaMemoryPool_GangAlloc(igArenaMemoryPoolView *self, int count, unsigned int *sizes, void **blocks) {
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
            if (hasPoolOption(self->_poolOptionFlags, 0x20)) {
                if (self->_heapIntegrityCheckLevel > 0) {
                    if (self->_messageLevel > 0) {
                        if ((unsigned)(total + (int)self->_localNetAllocated) > self->_maxSize && self->_messageLevel > 0) {
                            Memory_PrintPoolStatistics(0, self);
                            if (g_igArenaMemoryPool_ignoreE98Notice == 0) {
                                int r = igReportNotice((const char *)"igArenaMemoryPool(E98): Maximum memory size limit of %d bytes reached.  %d bytes already allocated.", (unsigned)self->_maxSize, (int)self->_localNetAllocated);
                                if (r != 1 && r == 2) {
                                    g_igArenaMemoryPool_ignoreE98Notice = 1;
                                }
                            }
                        }
                    }
                }
            } else if (self->_messageLevel >= 3 && g_igArenaMemoryPool_ignoreE100Notice == 0) {
                int r = igReportNotice((const char *)"igMallocMemoryPool[%d](E100) - refused request of %d bytes\nPool has already allocated %u bytes of maximum %u bytes\n", self->_poolIndex, sizes, (int)self->_localNetAllocated, (int)self->_maxSize);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE100Notice = 1;
                }
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

void igArenaMemoryPool_GangAllocAligned(int *status) {
    *status = g_resultFailure.v;
}

static inline char *blockHeader(char *p) {
    char *h = p - sizeof(int);
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

unsigned char g_igArenaMemoryPool_ignoreE82Notice;
unsigned char g_igArenaMemoryPool_ignoreE99Notice;
unsigned char g_igArenaMemoryPool_ignoreE83Notice;

/* Allocates a block straight from the system allocator on the pool's behalf. The block always takes
 * the 12-byte header, with `extraMarked` set to tell it from an arena chunk. */
int igArenaMemoryPool_AllocateFromSystem(igArenaMemoryPoolView *self, int size) {
    char *result;
    int guard;
    igArenaMemoryPool_Lock(self);
    guard = 0;
    result = 0;
    if (hasPoolOption(self->_poolOptionFlags, 1)) {
        guard = 12;
    }
    for (;;) {
        if ((unsigned)(size + (int)self->_localNetAllocated) <= self->_maxSize) {
            TaggedBlockHeader *h;
            unsigned total = size + guard;
            h = (TaggedBlockHeader *)g_activeSystemAllocator->Allocate(guard + (size + 12));
            if (h != 0) {
                initBlockHeader(self, h, total, 0, false, true);
                if (self->_size == 0 && self->_updateStatistics != 0) {
                    self->UpdateStatistics(size, chunkBytes(h), 1);
                }
                result = (char *)h + (h->big == 0 ? 4 : 12);
                if (flag2(self)) {
                    memset(result, 0xCD, chunkBytes(h) - (h->big == 0 ? 4 : 12) - guard);
                } else if (flag4(self)) {
                    memset(result, 0, chunkBytes(h) - (h->big == 0 ? 4 : 12) - guard);
                }
                if (guard != 0) {
                    ((unsigned *)result)[1] = 0xAAAAAAAF;
                    ((unsigned *)result)[0] = 8;
                    result += 8;
                    *(unsigned *)((char *)h + signedChunkBytes(h) - 4) = 0xBBBBBBBF;
                }
            } else if (self->_messageLevel >= 3 && g_igArenaMemoryPool_ignoreE82Notice == 0) {
                int r = igReportNotice((const char *)"igArenaMemoryPool[%d](E82) - malloc failed on request of %d bytes\n", self->_poolIndex, size);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE82Notice = 1;
                }
            }
            break;
        }
        if (self->HandleOutOfMemory(size, 1) == 0) {
            if (hasPoolOption(self->_poolOptionFlags, 0x20)) {
                if (self->_heapIntegrityCheckLevel > 0) {
                    if (self->_messageLevel > 0) {
                        if ((unsigned)(size + (int)self->_localNetAllocated) > self->_maxSize && self->_messageLevel > 0) {
                            Memory_PrintPoolStatistics(0, self);
                            if (g_igArenaMemoryPool_ignoreE99Notice == 0) {
                                int r = igReportNotice((const char *)"igArenaMemoryPool(E99): Maximum memory size limit of %d bytes reached.  %d bytes already allocated.", (int)self->_maxSize, (int)self->_localNetAllocated);
                                if (r != 1 && r == 2) {
                                    g_igArenaMemoryPool_ignoreE99Notice = 1;
                                }
                            }
                        }
                    }
                }
            } else if (self->_messageLevel >= 3 && g_igArenaMemoryPool_ignoreE83Notice == 0) {
                int r = igReportNotice((const char *)"igMallocMemoryPool[%d](E83) - refused request of %d bytes\nPool has already allocated %u bytes of maximum %u bytes\n", self->_poolIndex, size, (int)self->_localNetAllocated, (int)self->_maxSize);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE83Notice = 1;
                }
            }
            break;
        }
    }
    return igArenaMemoryPool_UnlockAndReturn(self, (int)result);
}

unsigned char g_igArenaMemoryPool_ignoreStateAllocError;
unsigned char g_igArenaMemoryPool_ignoreBlockListAllocError;
int g_igArenaMemoryPool_liveCount;

void igArenaMemoryPool_SetDefaults(igArenaMemoryPoolView *self) {
    int v;
    igMemoryPool_SetDefaults(self);
    self->_refCount = 0;
    ((igRefCountWord *)&self->_refCount)->bits.count = 1;
    ((char *)self)[7] = 0;
    self->_arenaState = (ArenaState *)g_activeSystemAllocator->Allocate(0x814);
    if (self->_arenaState == 0 && g_igArenaMemoryPool_ignoreStateAllocError == 0) {
        v = igReportError("Unable to allocate memory for arena state.");
        if (v != 1) {
            if (v == 2)
                g_igArenaMemoryPool_ignoreStateAllocError = 1;
        }
    }
    memset(self->_arenaState, 0, 0x814);
    self->_rawMemory = 0;
    self->_isAlchemyMemory = 0;
    self->_systemAllocated = 0;
    self->ResetStatistics();
    self->_maxSize = 0xFFFFFFFFFFFFFFFFULL;
    self->_size = 0;
    self->_preSize = 0;
    self->_alignment = 1;
    releaseRefObject(self->_eventTracker);
    self->_eventTracker = 0;
    self->_isActive = 0;
    g_igArenaMemoryPool_liveCount = g_igArenaMemoryPool_liveCount + 1;
    releaseRefObject(self->_allocationLock);
    self->_allocationLock = 0;
    self->_poolIndex = 0;
    self->_heapIntegrityCheckLevel = 0;
    self->_messageLevel = 1;
    self->_poolOptionFlags = g_igArenaMemoryPool_defaultPoolOptionFlags & ~8;
    self->_poolPreSized = 0;
    self->_smallestChunkSize = 16;
    if (self->_arenaState->blocks == 0) {
        self->_arenaState->blocks = (int *)g_activeSystemAllocator->AllocateAligned(0x200, 4);
        if (self->_arenaState->blocks == 0 && g_igArenaMemoryPool_ignoreBlockListAllocError == 0) {
            v = igReportError("Unable to allocate memory for arena state.");
            if (v != 1) {
                if (v == 2)
                    g_igArenaMemoryPool_ignoreBlockListAllocError = 1;
            }
        }
        self->_arenaState->blockCapacity = 0x200;
        self->_arenaState->blockCount = 0;
        self->_arenaState->maxBlockPairs = 0;
        self->_arenaState->lowestAddress = -1;
        self->_arenaState->highestAddress = 0;
    }
}

unsigned char g_igArenaMemoryPool_ignoreE84Notice;
unsigned char g_igArenaMemoryPool_ignoreE85Notice;
unsigned char g_igArenaMemoryPool_ignoreE115Notice;
unsigned int g_igArenaMemoryPool_shutdownNetAllocated;
unsigned int g_igArenaMemoryPool_shutdownNetAllocatedWithOverhead;

void igArenaMemoryPool_Shutdown(igArenaMemoryPoolView *self) {
    const char *name;
    int r;
    ArenaState *state;
    int *blocks;

    if (self->_size == 0) {
        igArenaMemoryPool_MallocConsolidate(self);
    }
    if ((int)self->_localNetAllocated != 0) {
        name = ((const char *)Memory_GetPoolName((int)self));
        self->CheckHeapLocked();
        if ((self->_messageLevel >= 3) && (g_igArenaMemoryPool_ignoreE84Notice == 0)) {
            long long netAllocated = self->_localNetAllocated;
            name = name ? name : "";
            r = igReportNotice("igArenaMemoryPool[%s index %d](E84) being reset with outstanding memory blocks of %d bytes.\n", name, self->_poolIndex, (int)netAllocated);
            if ((r != 1) && (r == 2)) {
                g_igArenaMemoryPool_ignoreE84Notice = 1;
            }
        }
        self->DisplayOutstandingAllocations();
    } else if (self->_localNetAllocationCount != 0) {
        name = ((const char *)Memory_GetPoolName((int)self));
        if ((self->_messageLevel >= 3) && (g_igArenaMemoryPool_ignoreE85Notice == 0)) {
            long long netAllocationCount = self->_localNetAllocationCount;
            name = name ? name : "";
            r = igReportNotice("igArenaMemoryPool[%s index %d](E85) being reset with %d outstanding allocations.\n", name, self->_poolIndex, (int)netAllocationCount);
            if ((r != 1) && (r == 2)) {
                g_igArenaMemoryPool_ignoreE85Notice = 1;
            }
        }
        self->DisplayOutstandingAllocations();
    }
    int t = (self->_poolOptionFlags & 0x200) != 0;
    if (!t && igArenaMemoryPool_GetArenaHighCount(self) > 1U) {
        name = ((const char *)Memory_GetPoolName((int)self));
        if ((self->_messageLevel >= 3) && (g_igArenaMemoryPool_ignoreE115Notice == 0)) {
            name = name ? name : "";
            r = igReportNotice("igArenaMemoryPool[%s index %d](E115) used a high of %d arenas.  This might mean system memory is fragmenting.\n", name, self->_poolIndex, igArenaMemoryPool_GetArenaHighCount(self));
            if ((r != 1) && (r == 2)) {
                g_igArenaMemoryPool_ignoreE115Notice = 1;
            }
        }
    }
    g_igArenaMemoryPool_shutdownNetAllocated += (int)self->_localNetAllocated;
    g_igArenaMemoryPool_shutdownNetAllocatedWithOverhead += (int)self->_localNetAllocatedWithOverhead;
    if (self->_size == 0) {
        self->Trim(0);
    }
    state = self->_arenaState;
    if (state != 0) {
        blocks = state->blocks;
        if (blocks != 0) {
            g_activeSystemAllocator->Free(blocks);
            self->_arenaState->blockCapacity = 0;
            self->_arenaState->blockCount = 0;
            self->_arenaState->maxBlockPairs = 0;
        }
        g_activeSystemAllocator->Free((void *)self->_arenaState);
        self->_arenaState = 0;
    }
    self->_arenaState = 0;
    g_igArenaMemoryPool_liveCount -= 1;
}

void *igArenaMemoryPool_Initialize(igArenaMemoryPool *self) {
    igMemoryPool_Initialize((int **)self);
    self->_vtable = (int)(&g_igArenaMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    return self;
}

void *igArenaMemoryPool_Construct(igArenaMemoryPool *self, int extra1) {
    igMemoryPool_Construct((int **)self);
    self->_vtable = (int)(&g_igArenaMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    if (self != 0) {
        igArenaMemoryPool_Initialize(self);
    }
    return self;
}

void *igArenaMemoryPool_CopyConstruct(igArenaMemoryPool *self, int source) {
    igMemoryPool_CopyConstruct((igMemoryPool *)self, (igMemoryPool *)source);
    self->_vtable = (int)(&g_igArenaMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    return self;
}

void igArenaMemoryPool_Destruct(void **self) {
    ((igMemoryPoolView *)(self))->Shutdown();
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

int igArenaMemoryPool_GetAllocationSize(int self, unsigned char *p) {
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

unsigned char g_igArenaMemoryPool_ignoreE111Notice;

void igArenaMemoryPool_SetPoolOptionFlags(igArenaMemoryPool *p, int f) {
    int r;
    if ((f & 1) != (p->_poolOptionFlags & 1)) {
        if (((igMemoryPoolView *)p)->IsActive() != 0) {
            if (p->_messageLevel > 0) {
                Memory_PrintPoolStatistics(0, p);
                if (g_igArenaMemoryPool_ignoreE111Notice == 0) {
                    r = igReportNotice("igArenaMemoryPool::setPoolOptionFlags(E111): You are not allowed to change the kSentinels flag on an activated pool.");
                    if (r != 1) { if (r == 2) { g_igArenaMemoryPool_ignoreE111Notice = 1; } }
                }
            }
            return;
        }
    }
    p->_poolOptionFlags = f;
}

int igArenaMemoryPool_GetEventTracker(igArenaMemoryPool *self) {
    return self->_eventTracker;
}

void igArenaMemoryPool_SetEventTracker(igArenaMemoryPool *self, igObject *tracker) {
    igObject *previous;
    if (tracker == 0 || (igArenaMemoryPool *)((void *)igObject_GetAllocator((int)tracker)) != self) {
        if (tracker != 0) {
            tracker->_refCount++;
        }
        previous = (igObject *)self->_eventTracker;
        if (previous != 0) {
            --previous->_refCount;
            if ((previous->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_eventTracker = (int)tracker;
    }
}

void igArenaMemoryPool_Dump(void) {

}

int igArenaMemoryPool_GetPoolIndex(igArenaMemoryPool *self) {
    return self->_poolIndex;
}

void igArenaMemoryPool_SetPoolIndex(igArenaMemoryPool *self, int index) {
    self->_poolIndex = index;
    if (self->_poolIndex >= 0x40) {
        self->_smallestChunkSize = 0x18;
    } else {
        self->_smallestChunkSize = 0x10;
    }
}

static inline int acceptsPoolIndex(igArenaMemoryPoolView *pool, int index) {
    if (pool->_poolIndex < 64 && index >= 64) return 0;
    return 1;
}

void igArenaMemoryPool_TransferAllocation(int *status, igArenaMemoryPoolView *self, char *block, igMemoryPoolView *target) {
    int targetIndex = target->GetPoolIndex();
    int accepted;
    TaggedBlockHeader *h;
    int poolIndex;
    accepted = acceptsPoolIndex(self, targetIndex);
    if (accepted != 0) {
        if (*(unsigned int *)(block - 4) == 0xAAAAAAAF) {
            unsigned int off = *(unsigned int *)(block - 8);
            if (off < 0x100011) {
                block = block - off;
            } else {
                *status = g_resultFailure.v;
                return;
            }
        }
        h = (TaggedBlockHeader *)(block - 4);
        if (((TaggedTailByte *)(block - 1))->extended == 1) {
            h = (TaggedBlockHeader *)(block - 12);
        }
        poolIndex = target->GetPoolIndex() >> 1;
        h->poolLow = poolIndex;
        if (h->big == 1) {
            h->poolHigh = poolIndex >> 5;
        }
        *status = g_resultSuccess.v;
    } else {
        *status = g_resultFailure.v;
    }
}

int igArenaMemoryPool_CanTransferTo(igArenaMemoryPool *self, igMemoryPoolView *target) {
    int targetIndex;
    int accepted;

    targetIndex = target->GetPoolIndex();
    if ((self->_poolIndex < 0x40) && (targetIndex >= 0x40)) {
        accepted = 0;
    } else {
        accepted = 1;
    }
    if (accepted != 0) {
        return 1;
    }
    return 0;
}

int igArenaMemoryPool_GetAllocationPoolIndex(int self, unsigned char *p) {
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

unsigned char g_igArenaMemoryPool_ignoreFieldsBlockListAllocError;

void Gap__Core__igArenaMemoryPool__constructFields(igArenaMemoryPoolView *self, int flags) {
    int t;
    self->_arenaState = (ArenaState *)g_activeSystemAllocator->Allocate(0x814);
    memset(self->_arenaState, 0, 0x814);
    if (self->_arenaState->blocks == 0) {
        self->_arenaState->blocks = (int *)g_activeSystemAllocator->AllocateAligned(0x200, 4);
        if (self->_arenaState->blocks == 0 && g_igArenaMemoryPool_ignoreFieldsBlockListAllocError == 0) {
            t = igReportError("Unable to allocate memory for arena state.");
            if (t != 1 && t == 2) {
                g_igArenaMemoryPool_ignoreFieldsBlockListAllocError = 1;
            }
        }
        self->_arenaState->blockCapacity = 0x200;
        self->_arenaState->blockCount = 0;
        self->_arenaState->maxBlockPairs = 0;
        self->_arenaState->lowestAddress = -1;
        self->_arenaState->highestAddress = 0;
    }
    g_igArenaMemoryPool_liveCount += 1;
    Gap__Core__igObject__constructFields((int)self, flags);
}

void Gap__Core__igArenaMemoryPool__destructFields(igArenaMemoryPool *self) {
    ((igMemoryPoolView *)self)->Shutdown();
    Gap__Core__igObject__destructFields((int)self);
}

void Gap__Core__igArenaMemoryPool__resetFields(igArenaMemoryPool *self, int extra1) {
    Gap__Core__igObject__resetFields((int)self, extra1);
    self->_poolOptionFlags = (int) g_igArenaMemoryPool_defaultPoolOptionFlags;
}

unsigned char g_igArenaMemoryPool_ignoreE110Notice;
unsigned char g_igArenaMemoryPool_ignoreE88Notice;
unsigned char g_igArenaMemoryPool_ignoreE89Notice;
unsigned char g_igArenaMemoryPool_ignoreE107Notice;
unsigned char g_igArenaMemoryPool_ignoreE108Notice;
unsigned char g_igArenaMemoryPool_ignoreE112Notice;
unsigned char g_igArenaMemoryPool_ignoreGangDoubleFreeNotice;
unsigned char g_igArenaMemoryPool_ignoreE90Notice;
unsigned char g_igArenaMemoryPool_ignoreE101Notice;
unsigned char g_igArenaMemoryPool_ignoreE91Notice;
unsigned char g_igArenaMemoryPool_ignoreE92Notice;
unsigned char g_igArenaMemoryPool_ignoreE109Notice;
unsigned char g_igArenaMemoryPool_ignoreE113Notice;
unsigned char g_igArenaMemoryPool_ignoreE65Notice;
unsigned char g_igArenaMemoryPool_ignoreE94Notice;

int g_arenaTriggerCheck = 0x30f040;

/* The arena pool's allocate / reallocate / free core: size -1 frees `block`; otherwise the block is
 * (re)allocated from the arena, with the out-of-memory hook given a chance to make room before the
 * maximum size refuses the request. With the sentinel option every block carries a head sentinel
 * after `headBytes` of padding (the padding's size is kept in the word before it) and a tail
 * sentinel in the last word of its chunk. */
void *igArenaMemoryPool_MemoryOperation(igArenaMemoryPoolView *self, char *block, int size, unsigned short alignment) {
    int newBytes;
    int total;
    bool moved;
    /* matching construct: variant search — the initialiser is dead; it makes this the first of the
     * three variables whose lifetimes the optimizer splits, which decides their stack slots */
    int oldHeadBytes = 0;
    int oldSize;
    int oldBytes;
    int sentinelBytes;
    int oldSentinelBytes;
    int headBytes;
    TaggedBlockHeader *h;
    char *result;
    char *fresh;
    TaggedBlockHeader *newHeader;
    int r;

    oldSize = 0;
    oldBytes = 0;
    oldHeadBytes = 0;
    sentinelBytes = 0;
    oldSentinelBytes = 0;
    headBytes = 0;
    h = 0;
    moved = false;
    g_arenaOperationOrdinal++;
    if (hasPoolOption(self->_poolOptionFlags, 0x100)) {
        if (self->_messageLevel >= 2 && g_igArenaMemoryPool_ignoreE110Notice == 0) {
            r = igReportNotice("igArenaMemoryPool(E110): Assert-on-memory-operation is in effect and %s was requested.", (size == -1 && block == 0) ?"a deallocation" :"an allocation");
            if (r != 1 && r == 2) {
                g_igArenaMemoryPool_ignoreE110Notice = 1;
            }
        }
        if (self->HandleOutOfMemory(size, 4) == 0) {
            return 0;
        }
    }
    igArenaMemoryPool_Lock(self);
    if (self->_alignment > alignment) {
        alignment = self->_alignment;
    }
    if (alignment < 8u) {
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
                    if (((unsigned *)block)[-1] == 0xAAAAAAAF) {
                        oldHeadBytes = ((int *)block)[-2];
                        block -= oldHeadBytes;
                        oldSentinelBytes = oldHeadBytes + 4;
                        h = (TaggedBlockHeader *)blockHeader(block);
                        unsigned *tail = (unsigned *)((char *)h + chunkBytes(h) - 4);
                        if (*tail != 0xBBBBBBBF && self->_messageLevel >= 1) {
                            Memory_PrintPoolStatistics(0, self);
                            if (g_igArenaMemoryPool_ignoreE88Notice == 0) {
                                r = igReportNotice("igArenaMemoryPool::free(E88): Bad tail sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", (unsigned)block + 8u, 0xBBBBBBBF, *tail);
                                if (r != 1 && r == 2) {
                                    g_igArenaMemoryPool_ignoreE88Notice = 1;
                                }
                            }
                        }
                    } else if (self->_messageLevel >= 1) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_igArenaMemoryPool_ignoreE89Notice == 0) {
                            r = igReportNotice("igArenaMemoryPool::free(E89): Bad head sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", block, 0xAAAAAAAF, ((unsigned *)block)[-1]);
                            if (r != 1 && r == 2) {
                                g_igArenaMemoryPool_ignoreE89Notice = 1;
                            }
                        }
                    }
                } else if (((unsigned *)block)[-1] == 0xAAAAAAAF) {
                    oldHeadBytes = ((int *)block)[-2];
                    if (oldHeadBytes > 0x100010) {
                        if (self->_messageLevel >= 1) {
                            Memory_PrintPoolStatistics(0, self);
                            if (g_igArenaMemoryPool_ignoreE107Notice == 0) {
                                r = igReportNotice("igArenaMemoryPool::free(E107): Bad head sentinel off.  Offset 0x%x.", (unsigned)block + 8u, oldHeadBytes);
                                if (r != 1 && r == 2) {
                                    g_igArenaMemoryPool_ignoreE107Notice = 1;
                                }
                            }
                        }
                        igArenaMemoryPool_Unlock(self);
                        return 0;
                    }
                    block -= oldHeadBytes;
                    oldSentinelBytes = oldHeadBytes + 4;
                    h = (TaggedBlockHeader *)blockHeader(block);
                    unsigned *tail = (unsigned *)((char *)h + chunkBytes(h) - 4);
                    if (*tail != 0xBBBBBBBF && self->_messageLevel >= 1) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_igArenaMemoryPool_ignoreE108Notice == 0) {
                            r = igReportNotice("igArenaMemoryPool::free(E108): Bad tail sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", (unsigned)block + 8u, 0xBBBBBBBF, *tail);
                            if (r != 1 && r == 2) {
                                g_igArenaMemoryPool_ignoreE108Notice = 1;
                            }
                        }
                    }
                } else {
                    h = (TaggedBlockHeader *)blockHeader(block);
                }
            } else {
                igArenaMemoryPool_Unlock(self);
                return 0;
            }
            if (h != 0) {
                oldSize = payloadSize(h) - oldSentinelBytes;
                oldBytes = chunkBytes(h);
                if (g_arenaTriggerCheck != 0) {
                    igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 2, (int)block, oldSize);
                }
                if (self->_poolIndex != chunkPoolIndex(h) && self->_messageLevel >= 1) {
                    Memory_PrintPoolStatistics(0, self);
                    if (g_igArenaMemoryPool_ignoreE112Notice == 0) {
                        r = igReportNotice("igArenaMemoryPool::free(E112): Attempt to free user block 0x%08x from pool[%d] with pool[%d].", block, chunkPoolIndex(h), self->_poolIndex);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreE112Notice = 1;
                        }
                    }
                }
                if (hasPoolOption(self->_poolOptionFlags, 2)) {
                    memset(block, 0xFD, oldBytes - (h->big == 0 ? 4 : 12));
                }
                if (chunkIsExternal(h)) {
                    g_activeSystemAllocator->Free(h);
                    if (self->_size == 0) {
                        if (self->_updateStatistics) {
                            self->UpdateStatistics(oldSize, oldBytes, 0);
                        }
                    }
                } else if (h->marked) {
                    GangRecord *record = (GangRecord *)padRecord(blockHeader(block));
                    GangRecord *first = record;
                    unsigned short offset = record->offset;
                    if (offset) {
                        first = (GangRecord *)((char *)record - offset);
                    }
                    if (first->count == 0 && self->_messageLevel >= 3 && g_igArenaMemoryPool_ignoreGangDoubleFreeNotice == 0) {
                        r = igReportNotice("free() call on gang alloced memory that was already free (0x%08x)", block);
                        if (r != 1 && r == 2) {
                            g_igArenaMemoryPool_ignoreGangDoubleFreeNotice = 1;
                        }
                    }
                    self->_localFreeCount++;
                    self->_localNetAllocationCount--;
                    if (--first->count == 0) {
                        unsigned *gang = (unsigned *)first - 1;
                        if (self->_updateStatistics) {
                            self->UpdateStatistics(*gang, *gang + 4, 0);
                        }
                        igArenaMemoryPool_FreeChunk(self, (char *)(gang - 1));
                    }
                } else {
                    if (self->_updateStatistics) {
                        self->UpdateStatistics(oldSize, oldBytes, 0);
                    }
                    igArenaMemoryPool_FreeChunk(self, block);
                }
            } else if (self->_messageLevel >= 3 && g_igArenaMemoryPool_ignoreE90Notice == 0) {
                r = igReportNotice("igArenaMemoryPool::free(E90) - Invalid memory block 0x%x.\n", self->_poolIndex, block);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE90Notice = 1;
                }
            }
            break;
        }
        if ((unsigned int)(size + (int)self->_localNetAllocated) > self->_maxSize) {
            if (g_arenaTriggerCheck != 0) {
                igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 1, 0, size);
            }
            if (self->HandleOutOfMemory(size, 1) != 0) {
                continue;
            }
            if (hasPoolOption(self->_poolOptionFlags, 0x20)) {
                if (self->_heapIntegrityCheckLevel > 0) {
                    if (self->_messageLevel >= 1) {
                        if ((unsigned int)(size + (int)self->_localNetAllocated) > self->_maxSize && self->_messageLevel >= 1) {
                            Memory_PrintPoolStatistics(0, self);
                            if (g_igArenaMemoryPool_ignoreE101Notice == 0) {
                                r = igReportNotice("igArenaMemoryPool(E101): Maximum memory size limit of %d bytes reached.  %d bytes already allocated.", (int)self->_maxSize, (int)self->_localNetAllocated);
                                if (r != 1 && r == 2) {
                                    g_igArenaMemoryPool_ignoreE101Notice = 1;
                                }
                            }
                        }
                    }
                }
            } else if (self->_messageLevel >= 3 && g_igArenaMemoryPool_ignoreE91Notice == 0) {
                r = igReportNotice("igArenaMemoryPool::memoryOperation[%d](E91) - Operation refused request of %d bytes\nPool has already allocated %u bytes of maximum %u bytes\n", self->_poolIndex, size, (int)self->_localNetAllocated, (int)self->_maxSize);
                if (r != 1 && r == 2) {
                    g_igArenaMemoryPool_ignoreE91Notice = 1;
                }
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
                    unsigned *tail = (unsigned *)((char *)h + chunkBytes(h) - 4);
                    if (*tail != 0xBBBBBBBF && self->_messageLevel >= 1) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_igArenaMemoryPool_ignoreE92Notice == 0) {
                            r = igReportNotice("igArenaMemoryPool::realloc(E92): Bad tail sentinel.  Address 0x%x, expected 0x%x, got 0x%x.", block + oldHeadBytes, 0xBBBBBBBF, *tail);
                            if (r != 1 && r == 2) {
                                g_igArenaMemoryPool_ignoreE92Notice = 1;
                            }
                        }
                    }
                } else {
                    h = (TaggedBlockHeader *)blockHeader(block);
                    if (igAllocator_ResolveEncodedIndex(chunkPoolIndex(h)) != self) {
                        if (self->_messageLevel >= 1) {
                            Memory_PrintPoolStatistics(0, self);
                            if (g_igArenaMemoryPool_ignoreE109Notice == 0) {
                                r = igReportNotice("igArenaMemoryPool::realloc(E109): Invalid memory block header.  Address 0x%x.", block);
                                if (r != 1 && r == 2) {
                                    g_igArenaMemoryPool_ignoreE109Notice = 1;
                                }
                            }
                        }
                        igArenaMemoryPool_Unlock(self);
                        return 0;
                    }
                }
            } else {
                h = (TaggedBlockHeader *)blockHeader(block);
            }
            if (self->_poolIndex != chunkPoolIndex(h) && self->_messageLevel >= 1) {
                Memory_PrintPoolStatistics(0, self);
                if (g_igArenaMemoryPool_ignoreE113Notice == 0) {
                    r = igReportNotice("igArenaMemoryPool::free(E113): Attempt to free user block 0x%08x from pool[%d] with pool[%d].", block, chunkPoolIndex(h), self->_poolIndex);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE113Notice = 1;
                    }
                }
            }
            oldSize = payloadSize(h) - oldSentinelBytes;
            oldBytes = chunkBytes(h);
            if (g_arenaTriggerCheck != 0) {
                igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 4, (int)block, oldSize);
            }
            if ((alignment <= 8u || oldSize >= size) && oldSentinelBytes == sentinelBytes && (unsigned)block % alignment == 0) {
                fresh = (char *)igArenaMemoryPool_Realloc(self, block, total);
            } else {
                fresh = (char *)igArenaMemoryPool_MallocAligned(self, alignment, total);
                moved = true;
            }
            if (g_arenaTriggerCheck != 0) {
                igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 4, (int)fresh, size);
            }
        } else if (alignment > 8u) {
            if (g_arenaTriggerCheck != 0) {
                igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 1, 0, size);
            }
            fresh = (char *)igArenaMemoryPool_MallocAligned(self, alignment, total);
            if (g_arenaTriggerCheck != 0) {
                igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 1, (int)fresh, size);
            }
        } else {
            if (g_arenaTriggerCheck != 0) {
                igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 1, 0, size);
            }
            fresh = (char *)igArenaMemoryPool_Malloc(self, total);
            if (g_arenaTriggerCheck != 0) {
                igArenaMemoryPool_CheckTriggerEvent((igArenaMemoryPool *)self, 1, (int)fresh, size);
            }
        }
        if (fresh != 0) {
            newHeader = (TaggedBlockHeader *)blockHeader(fresh);
            newBytes = chunkBytes(newHeader);
            if (self->_heapIntegrityCheckLevel > 0) {
                if (self->_messageLevel >= 1) {
                    if (total != payloadSize(newHeader) && self->_messageLevel >= 1) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_igArenaMemoryPool_ignoreE65Notice == 0) {
                            r = igReportNotice("igArenaMemoryPool: Invalid or corrupted block at 0x%x - %s", newHeader,"(E65) Software error - unexpected block size.");
                            if (r != 1 && r == 2) {
                                g_igArenaMemoryPool_ignoreE65Notice = 1;
                            }
                        }
                    }
                }
            }
            if (block != 0) {
                if (moved) {
                    memcpy(fresh + headBytes, block + oldHeadBytes, oldSize > size ? size : oldSize);
                    if (hasPoolOption(self->_poolOptionFlags, 2)) {
                        memset(block, 0xFD, oldBytes - (h->big == 0 ? 4 : 12));
                    }
                    if (chunkIsExternal(h)) {
                        if (self->_size == 0 && self->_updateStatistics) {
                            self->UpdateStatistics(oldSize, oldBytes, 0);
                        }
                        g_activeSystemAllocator->Free(h);
                    } else {
                        if (self->_updateStatistics) {
                            self->UpdateStatistics(oldSize, oldBytes, 0);
                        }
                        igArenaMemoryPool_FreeChunk(self, block);
                    }
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
                if (g_igArenaMemoryPool_ignoreE94Notice == 0) {
                    r = igReportNotice("igArenaMemoryPool::memoryOperation[%d](E94) - Operation failed on request of %d bytes\n", self->_poolIndex, size);
                    if (r != 1 && r == 2) {
                        g_igArenaMemoryPool_ignoreE94Notice = 1;
                    }
                }
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
    return (void *)igArenaMemoryPool_UnlockAndReturn(self, (int)result);
}

unsigned int igArenaMemoryPool_SystemAllocate(igArenaMemoryPool *self, int address, int size) {
    unsigned int blockEnd;
    unsigned int block;
    void *state;
    void *stateAgain;

    if (self->_size != 0) {
        return -1U;
    }
    block = g_activeSystemAllocator->AllocateRange(address, size);
    if (block != -1U) {
        self->_systemAllocated = self->_systemAllocated + size;
        /* matching construct: hand — the address bounds are stored as ints through an untyped state pointer;
         * typed ArenaState stores let the compiler skip the second _arenaState load retail makes. */
        state = (void *)(self->_arenaState);
        if (block < ((ArenaState *)state)->lowestAddress) {
            *(int *)&((ArenaState *)state)->lowestAddress = block;
        }
        stateAgain = (void *)(self->_arenaState);
        blockEnd = block + size;
        if (((ArenaState *)stateAgain)->highestAddress < blockEnd) {
            *(int *)&((ArenaState *)stateAgain)->highestAddress = blockEnd;
        }
    }
    return block;
}

igResult igArenaMemoryPool_SystemFree(void *self, int address, long long size) {
    igArenaMemoryPool *pool = (igArenaMemoryPool *)self;
    if (pool->_size != 0) {
        igResult result;
        result.v = g_resultFailure.v;
        return result;
    }
    long long released = (long long)(int)size;
    if ((unsigned long long)released < pool->_systemAllocated) {
        pool->_systemAllocated = pool->_systemAllocated - released;
    } else {
        pool->_systemAllocated = 0;
    }
    return g_activeSystemAllocator->FreeRange(address, size);
}

void igArenaMemoryPool_GetStackSize(igArenaMemoryPoolView *self)
{
    g_activeSystemAllocator->GetStackSize();
}

void Gap__Core__igArenaMemoryPool__vfunc_108(void) {

}

int igArenaMemoryPool_GetLowestAddress(igArenaMemoryPoolView *self) {
    int rawMemory;

    rawMemory = self->_rawMemory;
    if (rawMemory != 0) {
        return rawMemory;
    }
    return self->_arenaState->lowestAddress;
}

int igArenaMemoryPool_GetHighestAddress(igArenaMemoryPoolView *self) {
    int rawMemory;

    rawMemory = self->_rawMemory;
    if (rawMemory != 0) {
        return rawMemory + *(int *)&self->_size;
    }
    return self->_arenaState->highestAddress;
}


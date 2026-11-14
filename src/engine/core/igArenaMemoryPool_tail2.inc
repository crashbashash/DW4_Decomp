void igArenaMemoryPool_UpdateBlockList(igArenaMemoryPool *o, unsigned int lo, int len) {
    ArenaState *r;
    int i;
    bool found;
    unsigned int hi;
    found = 0;
    r = (ArenaState *)o->_arenaState;
    r->systemBytes += len;
    if (len < 0) hi = lo; else hi = lo + len;
    i = r->blockCount - 2;
    for (; i >= 0; i -= 2) {
        unsigned int *e = (unsigned int *)((char *)r->blocks + i * 4);
        unsigned int a = e[0];
        unsigned int *h;
        if (lo >= a && (h = e + 1, lo <= e[1])) {
            if (found) {
                if (o->_messageLevel >= 2 && GPR_00554ce4 == 0) {
                    int rc = igReportNotice(text_igArenaMemoryPool_E67_Block_list, r->blocks, h, a);
                    if (rc != 1 && rc == 2) GPR_00554ce4 = 1;
                }
                return;
            } else {
                if (len < 0 && a == hi) {
                    int n = r->blockCount;
                    int j = i + 2;
                    if (j < n) {
                        memcpy(e, (char *)r->blocks + j * 4, (n - j) * 4);
                    }
                    r->blockCount -= 2;
                } else if (len < 0 || e[1] < hi) {
                    *h = hi;
                }
                found = 1;
                if (o->_heapIntegrityCheckLevel < 2) break;
            }
        }
        if (len > 0) break;
    }
    if (!found && len >= 0) {
        int ncap;
        int cap = r->blockCapacity;
if (r->blockCount >= cap) {
            void *np;
            ncap = cap + 2;
            if (ncap == 0) ncap = 512;
            np = g_activeSystemAllocator[0]->Reallocate(r->blocks, ncap * 4);
            if (np != 0) {
                r->blocks = (int *)np;
                r->blockCapacity = ncap;
            } else {
                if (o->_messageLevel > 0) {
                    Memory_PrintPoolStatistics(0, o);
                    if (GPR_00554ce8 == 0) {
                        int rc = igReportNotice(text_igArenaMemoryPool_E68_Unable_to);
                        if (rc != 1 && rc == 2) GPR_00554ce8 = 1;
                    }
                }
                return;
            }
        }
        {
            int h;
            r->blocks[r->blockCount] = lo;
            r->blocks[r->blockCount + 1] = lo + len;
            r->blockCount += 2;
            h = r->blockCount / 2;
            if (r->maxBlockPairs < h) r->maxBlockPairs = h;
        }
    }
}

void igArenaMemoryPool_DisplayOutstandingAllocations(void *self0) {
 igArenaMemoryPoolView *s; ArenaState *arena; int i;
 s = (igArenaMemoryPoolView *)self0;
 arena = s->_arenaState;
 if (arena->blockCount == 0 || arena->blocks == 0 || arena->blockCapacity == 0) { return; }
 if (arena->blockCount < 0 || arena->blockCapacity < 0 || arena->blockCount > arena->blockCapacity) { return; }
 for (i = 0; i < arena->blockCount; i += 2) {
   int *p = &arena->blocks[i];
   igArenaMemoryPool_DisplayOutstandingAllocationsBlock(s, i, (char *)p[0], (char *)p[1]);
 }
 igReport_Printf(DAT_004f95c8);
 igReport_Flush();
}

/* Walks the chunks of system block `index` from `cur` to `end` and prints each chunk still in use
 * (its successor's previous-in-use bit is set); a bad block bound or chunk size stops the walk with a
 * message. */
void igArenaMemoryPool_DisplayOutstandingAllocationsBlock(igArenaMemoryPoolView *self, int index, char *cur, char *end) {
    char *hi = self->getHighestAddress();
    char *lo = self->getLowestAddress();
    TaggedBlockHeader *n;
    unsigned int size = 0;
    int count = 0;
    bool ok = false;
    if (cur < lo || hi < cur) {
        igReport_Printf(DAT_004fbf10, index, cur, lo, hi);
        igReport_Flush();
        return;
    }
    if (end < lo || hi < end) {
        igReport_Printf(DAT_004fbf90, index, end, lo, hi);
        igReport_Flush();
        return;
    }
    if (end < cur) {
        igReport_Printf(DAT_004fc010, index, end, cur);
        igReport_Flush();
        return;
    }
    if (!((TaggedBlockHeader *)cur)->used) {
        igReport_Printf(DAT_004fc090);
        igReport_Flush();
        return;
    }
    while (cur < end) {
        TaggedBlockHeader *h = (TaggedBlockHeader *)cur;
        unsigned int sz = h->size;
        int big = h->big;
        if (big == 1) {
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
        if ((char *)n != end && n->used) {
            char *allocation = cur + (big == 0 ? 4 : 12);
            igReport_Printf((const char *)DAT_004fc120, allocation, big == 0 ? h->size : h->size + (h->sizeHigh << 19), sz);
            igReport_Flush();
        }
        cur = (char *)n;
        count++;
    }
    if (cur != end && !ok) {
bad:
        igReport_Printf(DAT_004fc150, cur, index, count, size);
        igReport_Flush();
        return;
    }
}


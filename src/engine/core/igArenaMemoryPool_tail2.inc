void Gap__Core__igArenaMemoryPool__vfunc_111(igArenaMemoryPool *o, unsigned int lo, int len) {
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

void Gap__Core__igArenaMemoryPool__vfunc_88(void *self0) {
 igArenaMemoryPoolView *s; ArenaState *arena; int i;
 s = (igArenaMemoryPoolView *)self0;
 arena = s->_arenaState;
 if (arena->blockCount == 0 || arena->blocks == 0 || arena->blockCapacity == 0) { return; }
 if (arena->blockCount < 0 || arena->blockCapacity < 0 || arena->blockCount > arena->blockCapacity) { return; }
 for (i = 0; i < arena->blockCount; i += 2) {
   int *p = &arena->blocks[i];
   igArenaMemoryPool_DisplayOutstandingAllocationsBlock(s, i, p[0], p[1]);
 }
 FUN_00304430(DAT_004f95c8);
 FUN_00304680();
}


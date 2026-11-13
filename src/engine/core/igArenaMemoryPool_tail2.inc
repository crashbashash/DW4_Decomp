void Gap__Core__igArenaMemoryPool__vfunc_111(Obj_311990 *o, unsigned int lo, int len) {
    Ranges *r;
    int i;
    bool found;
    unsigned int hi;
    found = 0;
    r = o->r;
    r->total += len;
    if (len < 0) hi = lo; else hi = lo + len;
    i = r->count - 2;
    for (; i >= 0; i -= 2) {
        unsigned int *e = (unsigned int *)((char *)r->data + i * 4);
        unsigned int a = e[0];
        unsigned int *h;
        if (lo >= a && (h = e + 1, lo <= e[1])) {
            if (found) {
                if (o->lvlB >= 2 && GPR_00554ce4 == 0) {
                    int rc = igReportNotice(text_igArenaMemoryPool_E67_Block_list, r->data, h, a);
                    if (rc != 1 && rc == 2) GPR_00554ce4 = 1;
                }
                return;
            } else {
                if (len < 0 && a == hi) {
                    int n = r->count;
                    int j = i + 2;
                    if (j < n) {
                        memcpy(e, (char *)r->data + j * 4, (n - j) * 4);
                    }
                    r->count -= 2;
                } else if (len < 0 || e[1] < hi) {
                    *h = hi;
                }
                found = 1;
                if (o->lvlA < 2) break;
            }
        }
        if (len > 0) break;
    }
    if (!found && len >= 0) {
        int ncap;
        int cap = r->cap;
if (r->count >= cap) {
            void *np;
            ncap = cap + 2;
            if (ncap == 0) ncap = 512;
            np = ((Alloc_311990 * *)g_activeSystemAllocator)[0]->Realloc(r->data, ncap * 4);
            if (np != 0) {
                r->data = (unsigned int *)np;
                r->cap = ncap;
            } else {
                if (o->lvlB > 0) {
                    Memory_PrintPoolStatistics(0, (int)o);
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
            r->data[r->count] = lo;
            r->data[r->count + 1] = lo + len;
            r->count += 2;
            h = r->count / 2;
            if (r->half < h) r->half = h;
        }
    }
}

void Gap__Core__igArenaMemoryPool__vfunc_88(void *self0) {
 ArenaPoolView *s; ArenaBlockTable *arena; int i;
 s = (ArenaPoolView *)self0;
 arena = s->arena;
 if (arena->count == 0 || arena->blocks == 0 || arena->capacity == 0) { return; }
 if (arena->count < 0 || arena->capacity < 0 || arena->count > arena->capacity) { return; }
 for (i = 0; i < arena->count; i += 2) {
   int *p = &arena->blocks[i];
   igArenaMemoryPool_DisplayOutstandingAllocationsBlock(s, i, p[0], p[1]);
 }
 FUN_00304430(DAT_004f95c8);
 FUN_00304680();
}


#include "dw4/cri/sfdply.h"

extern void *memset(void *dst, int value, unsigned int size);
int sfd_ReportError();
int sfd_CheckHn(SfdPly *h);

void FUN_002ac770(SfdRing *ring, char *buffer, int size);
int sfring_Push(SfdRing *ring, SfdItem *item, int *full);
void FUN_002ac990(SfdRing *ring, unsigned int pos, SfdItem *out, unsigned int base, unsigned int span);
int sfring_FindPos(SfdRing *ring, unsigned int pos, unsigned int base, unsigned int span);

/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void FUN_002ac6d0(SfdRing *ring) {
    ring->items = 0;
    ring->size = 0;
    ring->count = 0;
    ring->wr = 0;
    ring->rd = 0;
}

int FUN_002ac6e8(SfdPly *h, void *data, int size) {
    if (data == 0 || size <= 0) {
        return 0;
    }
    if (sfd_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000165);
    }
    FUN_002ac770(&h->ent[1].ring, data, size);
    return 0;
}

void FUN_002ac770(SfdRing *ring, char *buffer, int size) {
    char *base = (char *)(((int)buffer + 7) & ~7);
    int usable = size - (base - buffer);
    memset(base, 0, usable);
    ring->items = (SfdItem *)base;
    ring->size = usable / 16;
    ring->count = 0;
    ring->wr = 0;
    ring->rd = 0;
}

int FUN_002ac7f0(SfdPly *h, int index, SfdItem *item, int *full) {
    SfdRing *ring;
    *full = 0;
    if (item->pos < 0) {
        return 0;
    }
    ring = &h->ent[index].ring;
    if (ring->items == 0) {
        return 0;
    }
    if (sfring_Push(ring, item, full) == -1) {
        return sfd_ReportError(h, 0xFF000421);
    }
    return 0;
}

int sfring_Push(SfdRing *ring, SfdItem *item, int *full) {
    int wr;
    if (ring->count == ring->size) {
        *full = 1;
        return -1;
    }
    wr = ring->wr;
    ring->items[wr] = *item;
    ring->wr = (wr + 1 < ring->size) ? wr + 1 : wr + 1 - ring->size;
    ring->count++;
    if (ring->count >= ring->size) {
        *full = 1;
    } else {
        *full = 0;
    }
    return 0;
}

int FUN_002ac918(SfdPly *h, int index, unsigned int pos, SfdItem *out) {
    /* matching construct: table base taken into a local before indexing */
    SfdStmEnt *entries = h->ent;
    SfdStmEnt *entry;
    SfdRing *ring;
    SfdStmInf *info;
    unsigned int span;
    unsigned int base;
    out->pos = -1;
    entry = &entries[index];
    ring = &entry->ring;
    info = &entry->info;
    span = info->size;
    base = info->base;
    if (ring->items == 0) {
        return 0;
    }
    FUN_002ac990(ring, pos < base + span ? pos : pos - span, out, base, span);
    return 0;
}

void FUN_002ac990(SfdRing *ring, unsigned int pos, SfdItem *out, unsigned int base, unsigned int span) {
    int skip;
    int rd;
    if (ring->count == 0) {
        return;
    }
    skip = sfring_FindPos(ring, pos, base, span);
    if (skip == -1) {
        return;
    }
    rd = ring->rd + skip;
    if (rd >= ring->size) {
        rd -= ring->size;
    }
    ring->rd = rd;
    ring->count -= skip;
    *out = ring->items[rd];
}

int sfring_FindPos(SfdRing *ring, unsigned int pos, unsigned int base, unsigned int span) {
    int size = ring->size;
    unsigned int end = base + span;
    int rd = ring->rd;
    int n;
    SfdItem *item;
    unsigned int start;
    unsigned int stop;
    for (n = 0; n < ring->count; n++) {
        item = &ring->items[rd];
        start = item->addr;
        stop = start + item->size;
        if (stop <= end) {
            if (pos >= start && pos < stop) {
                return n;
            }
        } else if ((pos >= start && pos < end) || (pos >= base && pos < stop - span)) {
            return n;
        }
        rd = (rd + 1 < size) ? rd + 1 : rd + 1 - size;
    }
    return -1;
}

int FUN_002acaf0(SfdPly *h, int index) {
    SfdRing *ring = &h->ent[index].ring;
    if (ring->items == 0) {
        return 0;
    }
    return ring->count >= ring->size;
}

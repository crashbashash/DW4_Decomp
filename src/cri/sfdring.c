#include "dw4/cri/sfdply.h"
#include <string.h>
#include "dw4/cri/sfd.h"


void sfpts_SetupPtsQue(SfdRing *ring, char *buffer, int size);
int sfpts_WritePtsQueSub(SfdRing *ring, SfdItem *item, int *full);
void sfpts_ReadPtsQueSub(SfdRing *ring, unsigned int pos, SfdItem *out, unsigned int base, unsigned int span);
int sfpts_SearchPtsQue(SfdRing *ring, unsigned int pos, unsigned int base, unsigned int span);

/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void SFPTS_InitPtsQue(void *ringp) {
    SfdRing *ring = ringp;
    ring->items = 0;
    ring->size = 0;
    ring->count = 0;
    ring->wr = 0;
    ring->rd = 0;
}

int SFD_SetVideoPts(void *sfd, void *data, int size) {
    SfdPly *h = sfd;
    if (data == 0 || size <= 0) {
        return 0;
    }
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000165);
    }
    sfpts_SetupPtsQue(&h->ent[1].ring, data, size);
    return 0;
}

void sfpts_SetupPtsQue(SfdRing *ring, char *buffer, int size) {
    char *base = (char *)(((int)buffer + 7) & ~7);
    int usable = size - (base - buffer);
    memset(base, 0, usable);
    ring->items = (SfdItem *)base;
    ring->size = usable / 16;
    ring->count = 0;
    ring->wr = 0;
    ring->rd = 0;
}

int SFPTS_WritePtsQue(void *sfd, int index, SfdItem *item, int *full) {
    SfdPly *h = sfd;
    SfdRing *ring;
    *full = 0;
    if (item->pos < 0) {
        return 0;
    }
    ring = &h->ent[index].ring;
    if (ring->items == 0) {
        return 0;
    }
    if (sfpts_WritePtsQueSub(ring, item, full) == -1) {
        return sfd_ReportError(h, 0xFF000421);
    }
    return 0;
}

int sfpts_WritePtsQueSub(SfdRing *ring, SfdItem *item, int *full) {
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

int SFPTS_ReadPtsQue(SfdPly *h, int index, unsigned int pos, SfdItem *out) {
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
    sfpts_ReadPtsQueSub(ring, pos < base + span ? pos : pos - span, out, base, span);
    return 0;
}

void sfpts_ReadPtsQueSub(SfdRing *ring, unsigned int pos, SfdItem *out, unsigned int base, unsigned int span) {
    int skip;
    int rd;
    if (ring->count == 0) {
        return;
    }
    skip = sfpts_SearchPtsQue(ring, pos, base, span);
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

int sfpts_SearchPtsQue(SfdRing *ring, unsigned int pos, unsigned int base, unsigned int span) {
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

int SFPTS_IsPtsQueFull(void *sfd, int index) {
    SfdPly *h = sfd;
    SfdRing *ring = &h->ent[index].ring;
    if (ring->items == 0) {
        return 0;
    }
    return ring->count >= ring->size;
}

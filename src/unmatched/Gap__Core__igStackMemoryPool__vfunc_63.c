typedef struct StackPoolFields {
    char pad0[112];
    unsigned short alignment;
    char pad1[18];
    unsigned top;
    unsigned *end;
} StackPoolFields;
extern int DAT_004fb410;
extern int DAT_004fb418;
static inline unsigned short effectiveAlign(StackPoolFields *pool, unsigned short wanted) {
    return wanted > pool->alignment ? wanted : pool->alignment;
}
void Gap__Core__igStackMemoryPool__vfunc_63(int *result, StackPoolFields *pool, int n, unsigned *sizes, unsigned *out, unsigned short *aligns) {
    unsigned total = 0;
    unsigned padding = 0;
    unsigned size2;
    unsigned align;
    unsigned align2;
    unsigned mask2;
    unsigned i;
    unsigned l;
    unsigned *end;
    unsigned low;
    unsigned pad;
    unsigned count;
    unsigned mask;
    unsigned start;
    unsigned start2;
    unsigned size;
    unsigned avail;
    unsigned pad2;
    unsigned scaled;
    unsigned k;
    unsigned j;
    i = 0;
    count = (unsigned short)n;
    for (; i < count; i++) {
        total += sizes[i];
        padding += effectiveAlign(pool, aligns[i]);
    }
    padding -= n & 0xffff;
    total += padding + count * 4;
    low = pool->top;
    end = pool->end;
    avail = (unsigned)(end + 1) - low;
    if (total <= avail) {
        for (j = 0; j < count; j++) {
            align = effectiveAlign(pool, aligns[j]);
            start = pool->top;
            mask = align - 1;
            mask &= align - (start & mask);
            pad = mask;
            size = pad + sizes[j];
            out[j] = start + pad;
            pool->top += size;
            *end = size;
            end--;
        }
        pool->end = end;
        *result = DAT_004fb410;
        return;
    }
    if (total - padding <= avail) {
        for (k = 0; k < count; k++) {
            align2 = effectiveAlign(pool, aligns[k]);
            start2 = pool->top;
            mask2 = align2 - 1;
            mask2 &= align2 - (start2 & mask2);
            pad2 = mask2;
            scaled = k * 4;
            size2 = pad2 + *(unsigned *)((char *)sizes + scaled);
            if ((unsigned)end - low < size2) {
                break;
            }
            *(unsigned *)((char *)out + scaled) = start2 + pad2;
            low += size2;
            *end = size2;
            end--;
        }
        if (k == count) {
            pool->top = low;
            pool->end = end;
            *result = DAT_004fb410;
            return;
        }
    }
    for (l = 0; l < count; l++) {
        out[l] = 0;
    }
    *result = DAT_004fb418;
}

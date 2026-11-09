typedef struct Pool { char p[136]; int debug; int p2; unsigned *slots[32]; } Pool;
extern unsigned char GPR_00554dd8;
extern int DAT_004ff4b0[4];
void FUN_002f8870(int, Pool *);
int FUN_003081d0(void *);
unsigned igPageMemoryPool_GetBlockSize(Pool *self, unsigned addr) {
    unsigned slot = addr >> 27;
    unsigned *tbl = self->slots[slot];
    unsigned size = 4096;
    unsigned page;
    unsigned first;
    unsigned bit;
    unsigned end;
    unsigned word;
    unsigned mask;
    unsigned *w;
    unsigned v;
    if (tbl == 0) {
        return 0;
    }
    page = (addr & 0x7ffffff) >> 12;
    bit = page & 15;
    word = page >> 4;
    end = 2 << (bit * 2);
    w = tbl + word;
    v = *w;
    first = 1 << (bit * 2);
    if ((first & v) == 0) {
        return 0;
    }
    if ((v & 0xAAAAAAAA) != 0) {
        for (; end != 0; end <<= 2) {
            if (end & *(unsigned *)w) {
                return size;
            }
            size += 4096;
        }
    } else {
        size += (16 - bit) << 12;
    }
    for (;;) {
        word++;
        if (word >= 2048) {
            slot++;
            if (slot >= 32) {
                return 0;
            }
            tbl = self->slots[slot];
            if (tbl == 0) {
                return 0;
            }
            word = 0;
        }
        w = tbl + word;
        v = *w;
        if ((v & 0xAAAAAAAA) != 0) {
            for (mask = 2; mask != 0; mask <<= 2) {
                if (mask & *(unsigned *)w) {
                    return size;
                }
                size += 4096;
            }
            if (self->debug > 0) {
                FUN_002f8870(0, self);
                if (GPR_00554dd8 == 0) {
                    int r = FUN_003081d0(DAT_004ff4b0);
                    if (r != 1 && r == 2) {
                        GPR_00554dd8 = 1;
                    }
                }
            }
        } else {
            size += 0x10000;
        }
    }
}

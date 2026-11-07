struct R { int v; R() {} R(const R &o) : v(o.v) {}
  bool operator==(const R &o) const { return v == o.v; }
  bool operator!=(const R &o) const { return v != o.v; }
};
extern "C" {
extern R DAT_004fb410;
extern unsigned char GPR_00554d1c;
extern int DAT_004fcbc0[4];
int FUN_003081d0(void *);
void FUN_00318b40(void *);
void FUN_00314510(void *, int, int);
void *memcpy(void *, void *, int);
}
struct ArenaHeap { char p0[1992]; int top; char p1[24]; int *blocks; int capacity; int count; };
struct Pool { char p0[112]; ArenaHeap *arena; char p1[44]; long long locked; char p2[20]; int debug; };
extern "C" R igArenaMemoryPool_TrimArenaBlock(Pool *, int, int, int);
extern "C" bool igArenaMemoryPool_Trim(Pool *self, int pad) {
    int count;
    int cap;
    ArenaHeap *a;
    int i;
    bool trimmed;
    a = self->arena;
    trimmed = false;
    FUN_00318b40(self);
    if (self->locked != 0) {
        return false;
    }
    count = a->count;
    if (count < 0 || (cap = a->capacity) < 0 || count > cap) {
        if (self->debug >= 3) {
            if (GPR_00554d1c == 0) {
                int r = FUN_003081d0(DAT_004fcbc0);
                if (r != 1 && r == 2) {
                    GPR_00554d1c = 1;
                }
            }
        }
        return false;
    }
    for (i = a->count - 2; i >= 0; i -= 2) {
        if (igArenaMemoryPool_TrimArenaBlock(self, i, a->blocks[i], a->blocks[i + 1]) == DAT_004fb410) {
            if (i < a->count - 2) {
                memcpy(a->blocks + i, a->blocks + (i + 2), (a->count - (i + 2)) * 4);
            }
            trimmed = true;
            a->blocks[a->count - 1] = 0;
            a->blocks[a->count - 2] = 0;
            a->count = a->count - 2;
        }
    }
    FUN_00314510(self, a->top, pad);
    return trimmed;
}

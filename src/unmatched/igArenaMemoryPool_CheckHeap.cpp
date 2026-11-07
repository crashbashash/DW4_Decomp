struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } igResult &operator=(const igResult &o) { w0 = o.w0; return *this; } bool operator==(const igResult &o) const { return w0 == o.w0; } };
extern "C" {
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
extern char DAT_004fc400[];
extern char DAT_004fc440[];
extern unsigned char GPR_00554cec;
extern unsigned char GPR_00554cf0;
int FUN_002f8870(...);
int FUN_003081d0(...);
}
struct ArenaHeap { char pad[2020]; int *blocks; int capacity; int count; };
struct Pool { char pad[112]; ArenaHeap *arena; char pad2[72]; int verbosity; };
extern "C" igResult FUN_00312790(Pool *self, int i, int a, int b);
extern "C" igResult igArenaMemoryPool_CheckHeap(Pool *self) {
    ArenaHeap *arena = self->arena;
    igResult ok = DAT_004fb410;
    igResult result;
    int i;
    int r;

    result.w0 = *(volatile int *)&DAT_004fb410.w0;
    if (arena->count == 0) {
        return ok;
    }
    if (arena->blocks == 0 || arena->capacity == 0) {
        if (self->verbosity > 0) {
            FUN_002f8870(0, self);
            if (GPR_00554cec == 0) {
                r = FUN_003081d0(DAT_004fc400);
                if (r == 1) {
                } else if (r == 2) {
                    GPR_00554cec = 1;
                }
            }
        }
        result = DAT_004fb418;
    }
    if (arena->count < 0 || arena->capacity < 0 || arena->count > arena->capacity) {
        if (self->verbosity >= 3 && GPR_00554cf0 == 0) {
            r = FUN_003081d0(DAT_004fc440);
            if (r == 1) {
            } else if (r == 2) {
                GPR_00554cf0 = 1;
            }
        }
        return DAT_004fb418;
    }
    for (i = 0; i < arena->count; i += 2) {
        int *p = &arena->blocks[i];
        if (FUN_00312790(self, i, p[0], p[1]) == DAT_004fb418) {
            result = DAT_004fb418;
            break;
        }
    }
    return result;
}

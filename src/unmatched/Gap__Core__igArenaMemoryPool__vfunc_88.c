int FUN_00304430();
int FUN_00304680();
int igArenaMemoryPool_DisplayOutstandingAllocationsBlock();
extern char DAT_004f95c8[];
typedef struct ArenaBlockTable { char pad[2020]; int *blocks; int capacity; int count; } ArenaBlockTable;
typedef struct ArenaPoolView { char pad[112]; ArenaBlockTable *arena; } ArenaPoolView;
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

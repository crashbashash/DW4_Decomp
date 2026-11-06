int FUN_00310c00(int);
int igArenaMemoryPool_CheckHeap(int *);

void FUN_00312580(int *arg0, int arg1) {
    int sp3C;

    igArenaMemoryPool_CheckHeap(&sp3C);
    FUN_00310c00(arg1);
    *arg0 = sp3C;
}

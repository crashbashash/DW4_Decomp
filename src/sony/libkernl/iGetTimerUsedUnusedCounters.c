typedef struct {
    int f0;
    int f4;
    int f8;
    int f12;
    volatile int f16;
} KState;
extern KState DAT_00483508;
int iGetTimerUsedUnusedCounters(int *used, int *left) {
    if (DAT_00483508.f8 < 0) return 0x80008001;
    if (used) *used = DAT_00483508.f16;
    if (left) *left = 128 - DAT_00483508.f16;
    return 0;
}

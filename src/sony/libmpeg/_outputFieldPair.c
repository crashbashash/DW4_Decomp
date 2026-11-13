typedef struct {
    char p0[16];
    long long pts;
    long long dts;
    long long flags;
    long long pts2;
    long long dts2;
    long long flags2;
} Out;
void FUN_00107f00(char *d, int *pic, long long *pts, long long *dts, long long *flags);
int FUN_00107ba8(char *d, int *pic);
void FUN_00107c48(char *d, int *pic);
void FUN_00107ed8(char *d);
void FUN_00108a40(char *d, int *pic);
void _outputFieldPair(char *d, int *top, int *bot) {
    int *first;
    int *second;
    int mask = 0;

    if (*(int *)(d + 396) == 2) {
        first = top;
        second = bot;
        mask = 64;
    } else {
        first = bot;
        second = top;
    }
    FUN_00107f00(d, first, &(*(Out **)(d + 2160))->pts, &(*(Out **)(d + 2160))->dts, &(*(Out **)(d + 2160))->flags);
    *(int *)(d + 152) = (*(Out **)(d + 2160))->pts;
    *(long long *)(d + 160) = 1;
    FUN_00107f00(d, second, &(*(Out **)(d + 2160))->pts2, &(*(Out **)(d + 2160))->dts2, &(*(Out **)(d + 2160))->flags2);
    *(int *)(d + 152) = (*(Out **)(d + 2160))->pts2;
    *(long long *)(d + 160) = 1;
    *(int *)(d + 228) = first[23];
    (*(Out **)(d + 2160))->flags |= mask;
    (*(Out **)(d + 2160))->flags2 |= mask;
    *(int *)(d + 232) = first[24];
    *(int *)(d + 204) = first[17];
    *(int *)(d + 208) = second[18];
    *(int *)(d + 216) = first[20];
    *(int *)(d + 220) = second[21];
    if (FUN_00107ba8(d, top) && top[10] == 1 && bot[10] == 1) {
        top[4] *= 2;
        if (*(int *)(d + 200)) {
            FUN_00108a40(d, top);
        } else {
            FUN_00107c48(d, top);
        }
        top[4] >>= 1;
        FUN_00107ed8(d);
    }
}

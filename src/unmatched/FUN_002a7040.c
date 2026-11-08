typedef struct { char c[44]; } Blk;
extern int FUN_002a96e0(void *h);
extern int FUN_002aa040(void *h);
extern void FUN_002a70e8(void *h, void *o);
typedef struct { char c[40]; int last; } Info;
void FUN_002a7040(char *h, char *o) {
    *(Info *)(o + 12) = *(Info *)(h + 3560);
    if (FUN_002a96e0(h) != 0) {
        *(int *)(o + 224) = FUN_002aa040(h);
    }
    FUN_002a70e8(h, o);
}

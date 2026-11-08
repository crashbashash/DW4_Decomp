typedef struct {
    int ready;
    int rate;
    int valid;
    int f12;
    int f16;
    int f20;
} Info29c3b8;

Info29c3b8 *FUN_0029ceb8(void);
int FUN_0029c470(int);
int FUN_0026c328(int);
int FUN_0026c2d8(int);
int FUN_0026c378(int);


void FUN_0029c3b8(char *obj) {
    Info29c3b8 *info = FUN_0029ceb8();
    int h;
    int n;

    if (info != 0 && info->ready == 0) {
        h = **(int **)(obj + 8188);
        if (FUN_0029c470(h) != 0) {
            info->f16 = FUN_0026c328(h);
            info->f20 = FUN_0026c2d8(h);
            info->f12 = FUN_0026c378(h);
            n = info->f16 * info->f12 * 9 / 16;
            info->valid = 1;
            info->ready = 1;
            info->rate = n;
        }
    }
}

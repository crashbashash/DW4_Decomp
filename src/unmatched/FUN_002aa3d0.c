extern int FUN_002aa460(void *h, int mode);
int FUN_002aa3d0(char *h, unsigned int mode) {
    int r = 0;
    switch (mode) {
    case 2:
        if (*(int *)(h + 72) == 4) r = FUN_002aa460(h, mode);
        break;
    case 1:
        if (++*(int *)(h + 84) == mode) r = FUN_002aa460(h, mode);
        break;
    case 0:
        if (--*(int *)(h + 84) == 0) r = FUN_002aa460(h, 0);
        break;
    }
    return r;
}

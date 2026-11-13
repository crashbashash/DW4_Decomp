extern char DAT_004d2138[];
extern char DAT_004d2158[];
int FUN_001057a0(char *d);
void _sceMpegMessage(char *d, const char *msg, ...);
int FUN_00107790(char *d) {
    char *p;
    int r;

    if (*(int *)(d + 396) == 3 && *(int *)(d + 312) != 0) {
        _sceMpegMessage(d, DAT_004d2138);
        *(int *)(d + 312) = 0;
    }
    switch (*(int *)(d + 396)) {
    case 3:
        p = *(char **)(d + 472);
        break;
    case 1:
        p = *(char **)(d + 488);
        break;
    case 2:
        p = *(char **)(d + 504);
        break;
    default:
        p = *(char **)(d + 472);
        _sceMpegMessage(d, DAT_004d2158);
        break;
    }
    r = FUN_001057a0(d);
    if (r) {
        *(int *)(p + 40) = 1;
    }
    return r;
}

extern char DAT_004d2178[];
int sprintf(char *buf, const char *fmt, ...);
void _sceMpegMessage(char *d, const char *msg, ...);
int FUN_00107ba8(char *d, int *lim) {
    char buf[256];
    int ok;

    if (*(int *)(d + 248)) {
        ok = *(int *)(d + 244) >= lim[1] && *(int *)(d + 248) >= lim[2];
    } else {
        ok = *(int *)(d + 252) >= lim[3] * lim[4];
    }
    if (!ok) {
        sprintf(buf, DAT_004d2178, lim[1], lim[2]);
        _sceMpegMessage(d, buf);
    }
    return ok;
}

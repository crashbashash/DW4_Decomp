void FUN_00129e60(char *);
int _sceMpegMessage(void *, char *);
int _sceMpegErrorf(void *a) {
    char buf[256];
    FUN_00129e60(buf);
    return _sceMpegMessage(a, buf);
}

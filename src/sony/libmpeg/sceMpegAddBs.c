typedef struct {
    int width;
    int height;
    int frameCount;
    long pts;
    long dts;
    unsigned long flags;
    long pts2nd;
    long dts2nd;
    unsigned long flags2nd;
    void *sys;
} sceMpeg;

int _sceMpegAddBs(void *dec, void *bs, int size);

int sceMpegAddBs(sceMpeg *mp, void *bs, int size) {
    _sceMpegAddBs(mp->sys, bs, (size + 19) / 16 * 16);
    return 1;
}

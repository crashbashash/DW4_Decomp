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
typedef struct {
    int isEnd;
    int refBuffCount;
    char pad0[132];
    int ptsSet;
    long pts;
    char pad1[20];
    int ni;
    int np;
    int nb;
    char pad2[20];
    int pictureInfo[6];
    int dispWidth;
    int dispHeight;
    char pad3[4];
    void *imageBuff;
    char pad4[12];
    int outputFlags;
    char pad5[4];
    long dts;
    int dtsSet;
} MpegDecoder;

int *sceMpegGetDisplayInfo(sceMpeg *mp) {
    return ((MpegDecoder *)mp->sys)->pictureInfo;
}

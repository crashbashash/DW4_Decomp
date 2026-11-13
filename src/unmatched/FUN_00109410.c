typedef struct {
    int done;
    char pad4[172 - 4];
    int imageY;
    int imageU;
    int imageV;
    int countY;
    int countU;
    int countV;
    char pad196[236 - 196];
    int f236;
    unsigned int image;
    char pad244[396 - 244];
    int f396;
    char pad400[2104 - 400];
    int stopped;
    char pad2108[2144 - 2108];
    int mpeg1;
    char pad2148[4256 - 2148];
    int aborted;
} MpegDecoder;
typedef struct {
    int pad[16];
    MpegDecoder *sys;
} MpegStream;
extern char DAT_004d2208[];
extern char DAT_004d2248[];
extern char DAT_004d2288[];
int _sceMpegErrorf(MpegDecoder *d, const char *message, int value);
int scePrintf(const char *format, ...);
int FUN_00106ee0(MpegDecoder *d);
int FUN_001098a8(MpegStream *mp);
int FUN_001096e8(MpegStream *mp, int index, int image);
int FUN_00109410(MpegStream *mp) {
    MpegDecoder *d = mp->sys;
    int result = 0;
    int code = 1;
    d->done = 0;
    if (d->image & 0x3F) {
        _sceMpegErrorf(d, DAT_004d2208, d->image);
        return -1;
    }
    if (d->aborted) {
        scePrintf(DAT_004d2248);
        return -1;
    }
    d->stopped = 0;
    do {
        if (result != -1) {
            do {
                code = FUN_00106ee0(d);
                if (code < 0) return -1;
                if (code == 0) break;
                if (d->f396 == d->f236) break;
            } while (d->mpeg1);
        }
        switch (code) {
        case 0:
            FUN_001098a8(mp);
            d->done = 1;
            break;
        case 1:
            d->countV = 0;
            d->countU = 0;
            d->countY = 0;
            result = FUN_001096e8(mp, 0, d->imageY);
            d->countY++;
            break;
        case 2:
            result = FUN_001096e8(mp, d->countU, d->imageU);
            d->countU++;
            break;
        case 3:
        case 4:
            result = FUN_001096e8(mp, d->countV, d->imageV);
            d->countV++;
            break;
        }
        if (d->aborted) {
            scePrintf(DAT_004d2288);
            return -1;
        }
        if (d->stopped) return 1;
    } while (d->done == 0);
    return 1;
}

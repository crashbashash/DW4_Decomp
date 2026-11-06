/* Starts a non-wait read of nsct sectors into buf (ADXF_ReadNw32). The D_004edXXX externs are the
 * argument-check strings, which keep address-bearing names. */
typedef struct SjObj SjObj;
typedef struct SjVT {
    char pad[12];
    void (*destroy)(SjObj *);
} SjVT;
struct SjObj { SjVT *vt; };

typedef struct Adxf {
    char pad0;
    char stat;
    char busy;
    char pad3[5];
    SjObj *sj;
    char pad12[24];
    void *buf;
    int bufSize;
} Adxf;

extern int D_0049a628;
extern const char D_004edc80[], D_004edca8[], D_004edcd8[], D_004edd00[];
extern void FUN_00260c20(int, int, void *, int, void *);
extern void FUN_002607e8(const char *);
extern SjObj *FUN_0027bd48(void *, int, int);
extern void FUN_0025f2d0(void);
extern void FUN_0025f2e8(void);
extern void FUN_00260a40(void *, int);
extern int FUN_00261da0(Adxf *, int, SjObj *);

int FUN_00261f48(Adxf *adxf, int nsct, void *buf)
{
    SjObj *sj;
    int size;
    int ret;

    FUN_00260c20(4, 0, adxf, nsct, buf);
    if (adxf == 0) {
        FUN_002607e8(D_004edc80);
        return -3;
    }
    if (nsct < 0) {
        FUN_002607e8(D_004edca8);
        return -3;
    }
    if (buf == 0) {
        FUN_002607e8(D_004edcd8);
        return -3;
    }
    if (adxf->stat == 2)
        return 0;
    if (adxf->sj != 0) {
        FUN_002607e8(D_004edd00);
        return -1;
    }
    size = nsct << 11;
    sj = FUN_0027bd48(buf, size, 0);
    if (sj == 0)
        return -2;
    FUN_0025f2d0();
    adxf->buf = buf;
    adxf->sj = sj;
    adxf->bufSize = size;
    if (D_0049a628 == 1)
        FUN_00260a40(buf, size);
    FUN_0025f2e8();
    ret = FUN_00261da0(adxf, nsct, adxf->sj);
    if (ret <= 0) {
        FUN_0025f2d0();
        if (adxf->sj != 0) {
            adxf->sj->vt->destroy(adxf->sj);
            adxf->sj = 0;
        }
        FUN_0025f2e8();
    }
    adxf->busy = 0;
    FUN_00260c20(4, 1, adxf, nsct, buf);
    return ret;
}

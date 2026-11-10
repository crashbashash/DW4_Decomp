typedef struct SjObj SjObj;

typedef struct SjChunk {
    char *addr;
    int size;
} SjChunk;

typedef struct SjVtbl {
    void *f0;
    void *f4;
    void *f8;
    void (*destroy)(SjObj *sj);                                   /* 12 */
    void *getUuid;                                                /* 16 */
    void (*reset)(SjObj *sj);                                     /* 20 */
    void (*getChunk)(SjObj *sj, int id, int size, SjChunk *chunk); /* 24 */
    void *ungetChunk;                                             /* 28 */
    void (*putChunk)(SjObj *sj, int id, SjChunk *chunk);          /* 32 */
    int (*getNumData)(SjObj *sj, int id);                         /* 36 */
} SjVtbl;

struct SjObj {
    SjVtbl *vtbl;
};

typedef struct MwsfdPly MwsfdPly;

typedef struct MwsfdPlyVtbl {
    void *f0[8];
    int (*getStat)(MwsfdPly *ply); /* 32 */
} MwsfdPlyVtbl;

typedef struct MwsfdCreInf {
    int type;      /* 0 */
    char pad4[28];
    int f32;       /* 32 */
} MwsfdCreInf;

typedef enum MwsfdChromaFmt {
    MWSFD_CHROMA_FMT_0,
    MWSFD_CHROMA_FMT_1,
    MWSFD_CHROMA_FMT_2,
    MWSFD_CHROMA_FMT_3
} MwsfdChromaFmt;

typedef enum MwsfdChromaPos {
    MWSFD_CHROMA_POS_0,
    MWSFD_CHROMA_POS_1
} MwsfdChromaPos;

typedef struct MwsfdPicInf {
    unsigned int pictureStructure; /* 0 */
    unsigned int chromaFormat;     /* 4 */
    int f8;
    int f12;
    int f16;
    MwsfdChromaPos chromaPosH;     /* 20 */
    MwsfdChromaPos chromaPosV;     /* 24 */
} MwsfdPicInf;

typedef struct MwsfdUsrBuf {
    char *buf; /* 0 */
    int size;  /* 4 */
    int f8;    /* 8 */
} MwsfdUsrBuf;

typedef struct MwsfdAddInf {
    int valid;  /* 0 */
    char *addr; /* 4 */
    int size;   /* 8 */
} MwsfdAddInf;

struct MwsfdPly {
    MwsfdPlyVtbl *vtbl;     /* 0 */
    int used;               /* 4 */
    int f8;
    MwsfdCreInf cre;        /* 12 */
    char pad48[16];
    int stream;             /* 64 */
    char pad68[12];
    int compoSet;           /* 80 */
    int compoMode;          /* 84 */
    char pad88[52];
    MwsfdPicInf pic;        /* 140 */
    int f160;
    void *sfx;              /* 172 */
    char pad176[224];
    SjObj *addInfSj;        /* 400 */
    char *addInfBase;       /* 404 */
    int addInfSize;         /* 408 */
    MwsfdUsrBuf usrBuf;     /* 412 */
    MwsfdAddInf addInf;     /* 424 */
};

typedef struct MwsfdFrm {
    int addr;       /* 0 */
    unsigned int bufFmt; /* 4 */
    int width;      /* 8 */
    int height;     /* 12 */
    int f16[8];
    int f48;        /* 48 */
} MwsfdFrm;

typedef struct MwsfdPlane {
    int addr;   /* 0 */
    int width;  /* 4 */
    int height; /* 8 */
    int f12;
} MwsfdPlane;

typedef struct MwsfdPicFmt {
    int pictureStructure;        /* 0 */
    MwsfdChromaFmt chromaFormat; /* 4 */
    int f8;
    int f12;
    int f16;
    int chromaPosH;       /* 20 */
    int chromaPosV;       /* 24 */
} MwsfdPicFmt;

typedef struct MwsfdCnvPrm {
    int bufFmt;           /* 0 */
    MwsfdPlane plane[3];  /* 4 */
    int f52[4];
    int width;            /* 68 */
    int height;           /* 72 */
    int f76;              /* 76 */
    int f80;              /* 80 */
    int f84;              /* 84 */
    int f88;              /* 88 */
    int f92;              /* 92 */
    MwsfdPicFmt fmt;      /* 96 */
    int f120[5];
} MwsfdCnvPrm;

extern char DAT_004f4028[];
extern char DAT_004f4050[];
extern char DAT_004f4078[];
extern char DAT_004f40a0[];
extern char DAT_004f40c0[];
extern char DAT_004f40f0[];
extern char DAT_004f4120[];
extern char DAT_004f4150[];
extern char DAT_004f4180[];
extern char DAT_004f41b8[];
extern char DAT_004f4200[];
extern char DAT_004f4250[];
extern char DAT_004f4288[];
extern char DAT_004f42c8[];
extern char DAT_004f4300[];
extern char DAT_004f4338[];
extern char DAT_004f4370[];
extern char DAT_004f43a8[];
extern char DAT_004f43e0[];
extern char DAT_004f4420[];
extern char DAT_004f4458[];
extern char DAT_004f4460[];
extern char DAT_004f4468[];
extern char DAT_004f4498[];
extern char DAT_004f44c8[];
extern char DAT_004f44f8[];
extern char DAT_004f4528[];
extern char DAT_004f4558[];
extern char DAT_004f4588[];
extern char DAT_004f45c0[];

SjObj *FUN_0027bd48(char *buf, int size, int flags);
int FUN_0027d6b0(SjChunk *in, const char *start, const char *end, SjChunk *out);
void FUN_00293118(MwsfdPly *ply);
void FUN_00293f60(int addr, int width, int height, int *out);
int FUN_002944b0(MwsfdPly *ply);
int FUN_002968c0(MwsfdPly *ply);
void FUN_0029a320(const char *msg);
int FUN_002b0ff8(int stream, int index, SjObj *sj, int b);
void FUN_002b3690(void *sfx, MwsfdCnvPrm *prm);
void FUN_002b3708(void *sfx, MwsfdCnvPrm *prm);
void FUN_002b3788(void);
void FUN_002b3858(void);
void FUN_002b38b0(void (*fn)(void *ctx, const char *msg), void *ctx);
void FUN_002b38c8(void);
void FUN_002b3ae8(void);
void FUN_002b3b78(void);
void FUN_002b3b88(void);
void FUN_002b3bb8(void *sfx, int value);
void FUN_002b3bd8(void *sfx, int mode);
int FUN_002b3be0(void *sfx);
void FUN_002b3be8(void *sfx, int value);
void FUN_002b3bf8(void *sfx, int a, int b);
void FUN_002b3c08(void *sfx, int a, int b);
void FUN_002b3c20(void *sfx, int value);
void FUN_002b3c28(void *sfx);
void FUN_002b3c78(void *sfx);
void FUN_002b3c98(void *sfx, char *addr, int size);
void FUN_002b3d30(void *sfx, int *first, int *second);
void FUN_002b3d60(void *sfx, int value);
int FUN_002b3d68(void *sfx);
void FUN_002b3d70(void *sfx, int value);
int FUN_002b3d78(void *sfx);
void FUN_002b3d80(void *sfx);
void FUN_002b3d98(void *sfx);
void FUN_002b3db0(void *sfx, MwsfdCnvPrm *prm, int a, int b);
void FUN_002b3dd0(void *sfx, int a, int b, int flag);
void FUN_002b3de8(void *sfx, int *a, int *b, int *c);
void FUN_002b3e00(void *sfx, unsigned char a, unsigned char b, unsigned char c);
void FUN_002b3e40(void *sfx, int a, int b, int c);
void FUN_002b3e58(void *sfx);
void FUN_002b3e60(void *sfx);
void FUN_002b3e68(void *sfx);
void FUN_002b3e70(void *sfx);
void FUN_002b3e78(void *sfx);
void FUN_002b3e80(void *sfx);
void FUN_002b3e88(void *sfx, int value);
int FUN_002b3e90(void *sfx);
void FUN_002b3ff8(void *sfx, int value);
int FUN_002b4050(void *sfx);
void FUN_002b4068(void);
void FUN_002b40b0(void *sfx);
void FUN_002b40d0(void *sfx);
void FUN_002b40f0(void *sfx);
void FUN_002b4110(void *sfx);
void FUN_002b4130(void *sfx);
void FUN_002b4150(void *sfx);
void FUN_002b4170(void *sfx);
void FUN_002b4190(void *sfx);
void FUN_002b41b0(void *sfx);
void FUN_002b41d0(void *sfx);
void FUN_002b41f0(void *sfx);
void FUN_002b4ba8(void *sfx, MwsfdCnvPrm *prm, int arg);
void FUN_002b4c48(void *sfx, MwsfdCnvPrm *prm, int arg);

void FUN_002977a8(void *ctx, const char *msg);
int FUN_002978b0(unsigned int format);
void FUN_00297910(MwsfdFrm *frm, MwsfdCnvPrm *prm);
int FUN_002979c8(MwsfdFrm *frm, MwsfdCnvPrm *prm);
void FUN_002979d8(MwsfdPlane *plane, int addr, int width, int height);
void FUN_002979e8(MwsfdPly *ply, MwsfdFrm *frm, MwsfdCnvPrm *prm);
void FUN_00297a30(MwsfdPly *ply, MwsfdCnvPrm *prm);
int FUN_00297aa8(MwsfdPly *ply);
MwsfdChromaFmt FUN_00297b18(MwsfdPly *ply);
int FUN_00297b88(MwsfdChromaPos position);
void FUN_00297e58(MwsfdPly *ply, int mode);
void FUN_00298028(MwsfdPly *ply, int a, int b, int c);
void FUN_00298468(MwsfdPly *ply);
void FUN_00298618(MwsfdPly *ply);
int FUN_002986c0(MwsfdPly *ply);

void FUN_00297780(void)
{
    FUN_002b3788();
    FUN_002b38b0(FUN_002977a8, 0);
}

void FUN_002977a8(void *ctx, const char *msg)
{
    FUN_0029a320(msg);
}

void FUN_002977c0(void)
{
    FUN_002b3858();
}

int FUN_002977d8(void)
{
    return 6175;
}

void FUN_002977e0(void)
{
    FUN_002b38c8();
}

void FUN_002977f8(void)
{
    FUN_002b3ae8();
}

void *FUN_00297810(MwsfdPly *ply)
{
    return ply->sfx;
}

void FUN_00297818(MwsfdPly *ply, void *sfx)
{
    ply->sfx = sfx;
}

void FUN_00297838(MwsfdPly *ply, MwsfdFrm *frm, MwsfdCnvPrm *prm);

void FUN_00297820(MwsfdPly *ply, MwsfdFrm *frm, MwsfdCnvPrm *prm)
{
    FUN_00297838(ply, frm, prm);
}

void FUN_00297838(MwsfdPly *ply, MwsfdFrm *frm, MwsfdCnvPrm *prm)
{
    prm->bufFmt = FUN_002978b0(frm->bufFmt);
    FUN_00297910(frm, prm);
    FUN_002979c8(frm, prm);
    FUN_002979e8(ply, frm, prm);
    FUN_00297a30(ply, prm);
}

int FUN_002978b0(unsigned int format)
{
    int result;

    switch (format) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        FUN_0029a320(DAT_004f4028);
        result = 3;
        break;
    }
    return result;
}

void FUN_00297910(MwsfdFrm *frm, MwsfdCnvPrm *prm)
{
    int out[6];
    int width = frm->width;
    int height = frm->height;
    int mode = frm->bufFmt;

    prm->width = width;
    prm->height = height;
    if (mode != 3) {
        FUN_002979d8(&prm->plane[0], frm->addr, width, height);
        return;
    }
    FUN_00293f60(frm->addr, width, height, out);
    FUN_002979d8(&prm->plane[0], out[0], out[3], height);
    FUN_002979d8(&prm->plane[1], out[1], out[4], height);
    FUN_002979d8(&prm->plane[2], out[2], out[5], height);
}

int FUN_002979c8(MwsfdFrm *frm, MwsfdCnvPrm *prm)
{
    return prm->f76 = frm->f48;
}

void FUN_002979d8(MwsfdPlane *plane, int addr, int width, int height)
{
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    plane->addr = addr;
    plane->width = width;
    plane->height = height;
}

void FUN_002979e8(MwsfdPly *ply, MwsfdFrm *frm, MwsfdCnvPrm *prm)
{
    int values[2];

    FUN_002b3d30(ply->sfx, &values[0], &values[1]);
    prm->f80 = values[0];
    prm->f84 = values[1];
    prm->f88 = 0;
    prm->f92 = 0;
}

void FUN_00297a30(MwsfdPly *ply, MwsfdCnvPrm *prm)
{
    MwsfdPicFmt *dst = &prm->fmt;
    MwsfdPicInf *src;

    dst->pictureStructure = FUN_00297aa8(ply);
    src = &ply->pic;
    dst->chromaFormat = FUN_00297b18(ply);
    dst->f8 = src->f8;
    dst->f12 = src->f12;
    dst->f16 = src->f16;
    dst->chromaPosH = FUN_00297b88(src->chromaPosH);
    dst->chromaPosV = FUN_00297b88(src->chromaPosV);
}

int FUN_00297aa8(MwsfdPly *ply)
{
    int result = 3;

    switch (ply->pic.pictureStructure) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        FUN_0029a320(DAT_004f4050);
        break;
    }
    return result;
}

MwsfdChromaFmt FUN_00297b18(MwsfdPly *ply)
{
    MwsfdChromaFmt result = MWSFD_CHROMA_FMT_1;

    switch (ply->pic.chromaFormat) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        FUN_0029a320(DAT_004f4078);
        break;
    }
    return result;
}

int FUN_00297b88(MwsfdChromaPos position)
{
    int result = 1;

    switch (position) {
    case 0:
        result = 0;
        break;
    case 1:
        result = 1;
        break;
    default:
        FUN_0029a320(DAT_004f40a0);
        break;
    }
    return result;
}

void FUN_00297bd8(MwsfdPly *ply)
{
    FUN_002b3c28(ply->sfx);
}

void FUN_00297bf0(MwsfdPly *ply)
{
    FUN_002b3c78(ply->sfx);
}

void FUN_00297c08(MwsfdPly *ply, MwsfdFrm *frm, int arg)
{
    MwsfdCnvPrm prm;
    void *sfx;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f40c0);
    } else if (frm->addr == 0) {
        FUN_0029a320(DAT_004f40f0);
    } else {
        sfx = FUN_00297810(ply);
        FUN_00297838(ply, frm, &prm);
        FUN_002b4ba8(sfx, &prm, arg);
    }
}

void FUN_00297cb0(MwsfdPly *ply, MwsfdFrm *frm, int arg)
{
    MwsfdCnvPrm prm;
    void *sfx;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4120);
    } else if (frm->addr == 0) {
        FUN_0029a320(DAT_004f4150);
    } else {
        sfx = FUN_00297810(ply);
        FUN_00297838(ply, frm, &prm);
        FUN_002b4c48(sfx, &prm, arg);
    }
}

void FUN_00297d58(MwsfdPly *ply, int mode)
{
    int compo = mode;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4180);
        return;
    }
    if (ply->addInfSj == 0) {
        if (mode == 0x101) {
            FUN_0029a320(DAT_004f41b8);
            return;
        }
        if (mode == 0) {
            FUN_0029a320(DAT_004f4200);
            return;
        }
    }
    compo = mode;
    if (ply->vtbl->getStat(ply) == 2 && compo == 0) {
        compo = FUN_002944b0(ply);
        if (compo == -1) {
            compo = 17;
        }
    }
    FUN_00297e58(ply, compo);
}

void FUN_00297e58(MwsfdPly *ply, int mode)
{
    FUN_002b3bd8(FUN_00297810(ply), mode);
}

int FUN_00297e88(MwsfdPly *ply)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4250);
        return 0;
    }
    return FUN_002b3be0(FUN_00297810(ply));
}

void FUN_00297ee8(MwsfdPly *ply, int value)
{
    FUN_002b3be8(FUN_00297810(ply), value);
}

void FUN_00297f18(MwsfdPly *ply)
{
    FUN_002b3e58(ply->sfx);
}

void FUN_00297f30(MwsfdPly *ply)
{
    FUN_00297f18(ply);
}

void FUN_00297f48(MwsfdPly *ply)
{
    FUN_002b3e60(ply->sfx);
}

void FUN_00297f60(MwsfdPly *ply, int a, int b)
{
    FUN_00298028(ply, a, b, 0);
}

void FUN_00297f78(MwsfdPly *ply, int a, int b)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4288);
        return;
    }
    FUN_002b3c08(FUN_00297810(ply), a, b);
}

void FUN_00297ff8(MwsfdPly *ply, int a, int b)
{
    FUN_00298028(ply, a, b, 0);
}

void FUN_00298010(MwsfdPly *ply, int a, int b)
{
    FUN_00297f78(ply, a, b);
}

void FUN_00298028(MwsfdPly *ply, int a, int b, int c)
{
    void *sfx;

    if (!FUN_002968c0(ply)) {
        FUN_0029a320(DAT_004f42c8);
        return;
    }
    sfx = FUN_00297810(ply);
    FUN_002b3bf8(sfx, a, b);
    FUN_002b3c20(sfx, c);
}

void FUN_002980c0(MwsfdPly *ply, int value)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4300);
        return;
    }
    FUN_002b3d60(FUN_00297810(ply), value);
}

int FUN_00298128(MwsfdPly *ply)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4338);
        return 0;
    }
    return FUN_002b3d68(FUN_00297810(ply));
}

void FUN_00298188(MwsfdPly *ply, int value)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4370);
        return;
    }
    FUN_002b3d70(FUN_00297810(ply), value);
}

int FUN_002981f0(MwsfdPly *ply)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f43a8);
        return 0;
    }
    return FUN_002b3d78(FUN_00297810(ply));
}

int FUN_00298250(MwsfdPly *ply)
{
    return ply->cre.type == 2;
}

int FUN_00298260(MwsfdCreInf *cre)
{
    int result;

    switch (cre->f32) {
    case 0:
    case 0x101:
        result = 1;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

SjObj *FUN_00298288(MwsfdPly *ply)
{
    SjObj *sj;

    if (FUN_00298260(&ply->cre) == 0) {
        return 0;
    }
    sj = FUN_0027bd48(ply->addInfBase, ply->addInfSize, 0);
    if (sj == 0) {
        FUN_0029a320(DAT_004f43e0);
        FUN_00293118(ply);
        return 0;
    }
    return sj;
}

void FUN_002982e8(MwsfdPly *ply)
{
    SjObj *sj = ply->addInfSj;

    if (sj != 0) {
        sj->vtbl->destroy(sj);
    }
}

int FUN_00298318(MwsfdPly *ply)
{
    SjObj *sj;

    if (FUN_00298250(ply) == 1) {
        return 0;
    }
    sj = ply->addInfSj;
    if (sj == 0) {
        return 0;
    }
    if (FUN_002b0ff8(ply->stream, 2, sj, 0) != 0) {
        return -1;
    }
    return 0;
}

void FUN_00298378(MwsfdPly *ply)
{
    MwsfdAddInf *inf = &ply->addInf;

    inf->valid = 0;
    inf->addr = 0;
    inf->size = 0;
    ply->usrBuf.f8 = -1;
}

void FUN_00298398(MwsfdPly *ply)
{
    SjObj *sj = ply->addInfSj;

    if (sj != 0) {
        sj->vtbl->reset(sj);
    }
}

void FUN_002983c8(MwsfdPly *ply)
{
    MwsfdAddInf *inf = &ply->addInf;

    if (ply->addInfSj != 0 && inf->valid != 1) {
        FUN_00298468(ply);
        FUN_00298618(ply);
    }
}

void FUN_00298420(MwsfdPly *ply)
{
    if (ply->addInfSj == 0) {
        return;
    }
    FUN_00298468(ply);
    FUN_00298618(ply);
}

void FUN_002985b8(MwsfdPly *ply, char *buf, int size)
{
    MwsfdUsrBuf *ub = &ply->usrBuf;

    if (size < 0x20000) {
        FUN_0029a320(DAT_004f4420);
    }
    ub->buf = buf;
    ub->size = size;
}

void FUN_00298618(MwsfdPly *ply)
{
    SjChunk in;
    SjChunk out;
    MwsfdAddInf *inf = &ply->addInf;
    void *sfx = ply->sfx;

    if (inf->addr == 0) {
        FUN_002b3c98(sfx, 0, 0);
        return;
    }
    in.addr = inf->addr;
    in.size = inf->size;
    if (FUN_0027d6b0(&in, DAT_004f4458, DAT_004f4460, &out) == 0) {
        FUN_002b3c98(sfx, 0, 0);
        return;
    }
    FUN_002b3c98(sfx, out.addr, out.size);
}

int FUN_002986c0(MwsfdPly *ply)
{
    if (FUN_00298250(ply) == 1) {
        return 0;
    }
    if (ply->addInfSj == 0) {
        return 0;
    }
    if (FUN_002b0ff8(ply->stream, 2, 0, 0) != 0) {
        return -1;
    }
    return 0;
}

void FUN_00298720(MwsfdPly *ply)
{
    FUN_002b3d80(ply->sfx);
}

void FUN_00298738(MwsfdPly *ply)
{
    FUN_002b3d98(ply->sfx);
}

void FUN_00298750(MwsfdPly *ply, char **addr, int *size)
{
    MwsfdAddInf *inf = &ply->addInf;

    *addr = inf->addr;
    *size = inf->size;
}

void FUN_002987b8(MwsfdPly *ply, MwsfdFrm *frm, int a, int b)
{
    MwsfdCnvPrm prm;
    void *sfx = FUN_00297810(ply);

    FUN_00297838(ply, frm, &prm);
    FUN_002b3db0(sfx, &prm, a, b);
}

void FUN_00298830(MwsfdPly *ply, int a, int b, int mode)
{
    FUN_002b3dd0(FUN_00297810(ply), a, b, mode == 1);
}

void FUN_002988f0(MwsfdPly *ply, unsigned char a, unsigned char b, unsigned char c)
{
    FUN_002b3e00(FUN_00297810(ply), a, b, c);
}

void FUN_00298940(MwsfdPly *ply, int a, int b, int c)
{
    FUN_002b3e40(FUN_00297810(ply), a, b, c);
}

void FUN_00298990(MwsfdPly *ply, MwsfdFrm *frm)
{
    MwsfdCnvPrm prm;
    void *sfx;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4468);
        return;
    }
    if (frm->addr == 0) {
        FUN_0029a320(DAT_004f4498);
        return;
    }
    sfx = FUN_00297810(ply);
    FUN_00297838(ply, frm, &prm);
    FUN_002b3690(sfx, &prm);
}

void FUN_00298a30(MwsfdPly *ply, MwsfdFrm *frm)
{
    MwsfdCnvPrm prm;
    void *sfx;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f44c8);
        return;
    }
    if (frm->addr == 0) {
        FUN_0029a320(DAT_004f44f8);
        return;
    }
    sfx = FUN_00297810(ply);
    FUN_00297838(ply, frm, &prm);
    FUN_002b3708(sfx, &prm);
}

void FUN_00298ad0(MwsfdPly *ply)
{
    FUN_002b40b0(ply->sfx);
}

void FUN_00298ae8(MwsfdPly *ply)
{
    FUN_002b4110(ply->sfx);
}

void FUN_00298b00(MwsfdPly *ply)
{
    FUN_002b40d0(ply->sfx);
}

void FUN_00298b18(MwsfdPly *ply)
{
    FUN_002b40f0(ply->sfx);
}

void FUN_00298b30(MwsfdPly *ply)
{
    FUN_00298ae8(ply);
}

void FUN_00298b48(MwsfdPly *ply)
{
    FUN_002b4130(ply->sfx);
}

void FUN_00298b60(MwsfdPly *ply)
{
    FUN_002b4150(ply->sfx);
}

void FUN_00298b78(MwsfdPly *ply)
{
    FUN_002b4170(ply->sfx);
}

void FUN_00298b90(MwsfdPly *ply)
{
    FUN_002b4190(ply->sfx);
}

void FUN_00298ba8(MwsfdPly *ply)
{
    FUN_002b41b0(ply->sfx);
}

void FUN_00298bc0(MwsfdPly *ply)
{
    FUN_002b41d0(ply->sfx);
}

void FUN_00298bd8(MwsfdPly *ply)
{
    FUN_002b41f0(ply->sfx);
}

void FUN_00298bf0(MwsfdPly *ply)
{
    FUN_002b3e68(ply->sfx);
}

void FUN_00298c08(MwsfdPly *ply)
{
    FUN_002b3e70(ply->sfx);
}

void FUN_00298c20(MwsfdPly *ply)
{
    FUN_002b3e78(ply->sfx);
}

void FUN_00298c38(MwsfdPly *ply)
{
    FUN_002b3e80(ply->sfx);
}

void FUN_00298c50(void)
{
    FUN_002b3b78();
}

void FUN_00298c68(void)
{
    FUN_002b3b88();
}

void FUN_00298c80(MwsfdPly *ply, int value)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4528);
        return;
    }
    FUN_002b3ff8(FUN_00297810(ply), value);
}

int FUN_00298ce8(MwsfdPly *ply)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4558);
        return 0;
    }
    return FUN_002b4050(FUN_00297810(ply));
}

void FUN_00298d48(MwsfdPly *ply, int value)
{
    FUN_002b3bb8(FUN_00297810(ply), value);
}

void FUN_00298d78(MwsfdPly *ply)
{
    int mode;

    if (ply->compoSet == 0) {
        mode = FUN_002944b0(ply);
        if (mode != -1) {
            ply->compoMode = mode;
        } else {
            ply->compoMode = 0x11;
        }
    }
    FUN_002b3bd8(FUN_00297810(ply), ply->compoMode);
}

void FUN_00298de0(MwsfdPly *ply, int value)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4588);
        return;
    }
    FUN_002b3e88(FUN_00297810(ply), value);
}

int FUN_00298e48(MwsfdPly *ply)
{
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f45c0);
        return 0;
    }
    return FUN_002b3e90(FUN_00297810(ply));
}

void FUN_00298ea8(void)
{
    FUN_002b4068();
}

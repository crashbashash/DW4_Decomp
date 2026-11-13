/* SFX alpha: the alpha handles an SFX handle keeps (SfxHn.ahn): the parameters of the CFT colour
 * conversion table and the three alpha levels of the alpha tables, and the frame helpers after them. */

void *memset(void *dst, int value, unsigned int size);
void cft_MakeYccTbl(int mode, int lo, int hi, int table);
void cft_MakeAlpha3Tbl(int table, int alpha0, int alpha1, int alpha2);
void cft_MakeAlpha3TblBlack(int table, int alpha0, int alpha1, int alpha2);
void sfx_ClipFrame();

typedef struct SfxaPrm {
    int mode;
    int lo;
    int hi;
} SfxaPrm;

typedef struct SfxaHn {
    int used;
    int changed;              /* the parameters differ from the last colour table built */
    SfxaPrm prm;
    unsigned char alpha[3];
} SfxaHn;

typedef struct SfxaLib {
    int nhn;
    int maxhn;
    SfxaHn hn[8];
} SfxaLib;

typedef struct SfxaFrame {
    char pad0[68];
    int right;
    int bottom;
} SfxaFrame;

typedef struct SfxaLineWalk {
    int addr;
    int pad4;
    int lines;
    int pitch;
} SfxaLineWalk;

extern SfxaLib sfxa_lib;

SfxaHn *sfxalp_SearchFreeHn(void);
void sfxalp_InitHn(SfxaHn *hn);
void sfxa_InitLib(void);

void sfxa_Init(void) {
    sfxa_InitLib();
}

void sfxa_InitLib(void) {
    memset(&sfxa_lib, 0, sizeof(SfxaLib));
    sfxa_lib.maxhn = 8;
}

void sfxa_Finish(void) {
}

SfxaHn *SFXA_Create(void) {
    SfxaHn *hn = sfxalp_SearchFreeHn();

    if (hn == 0) {
        return 0;
    }
    sfxalp_InitHn(hn);
    sfxa_lib.nhn++;
    hn->used = 1;
    return hn;
}

/* matching construct: manual — the in-use word is read through a volatile pointer; retail leaves the loop branch's delay slot empty */
SfxaHn *sfxalp_SearchFreeHn(void) {
    int maxhn = sfxa_lib.maxhn;
    SfxaHn *tbl = sfxa_lib.hn;
    volatile SfxaHn *hn;
    int i;

    for (i = 0; i < maxhn; i++) {
        hn = &tbl[i];
        if (hn->used == 0) {
            return (SfxaHn *)hn;
        }
    }
    return 0;
}

void sfxalp_InitHn(SfxaHn *hn) {
    /* matching construct: manual — taking the byte pointer first gives retail's v1/v0 order */
    unsigned char *alpha = hn->alpha;
    SfxaPrm *prm = &hn->prm;

    prm->mode = 0;
    prm->lo = 31;
    prm->hi = 100;
    hn->changed = 1;
    alpha[0] = 0;
    alpha[1] = 64;
    alpha[2] = 128;
}

/* matching construct: manual — the in-use word is written through a volatile pointer; retail leaves the branch delay slot empty */
void SFXA_Destroy(volatile int *hn) {
    if (hn != 0) {
        *hn = 0;
        sfxa_lib.nhn--;
    }
}

void SFXA_MakeAlpLumiTbl(SfxaHn *hn, int unused, int table) {
    SfxaPrm *prm = &hn->prm;

    cft_MakeYccTbl(prm->mode, prm->lo, prm->hi, table);
    hn->changed = 0;
}

void SFXA_MakeAlp3110Tbl(SfxaHn *hn, int unused, int table) {
    cft_MakeAlpha3Tbl(table, hn->alpha[0], hn->alpha[1], hn->alpha[2]);
}

void SFXA_MakeAlp3211Tbl(SfxaHn *hn, int unused, int table) {
    cft_MakeAlpha3TblBlack(table, hn->alpha[0], hn->alpha[1], hn->alpha[2]);
}

int SFXA_IsNeedUpdateLumiTbl(SfxaHn *hn) {
    return hn->changed;
}

void SFXA_SetLumiPrm(SfxaHn *hn, int lo, int hi, int mode) {
    SfxaPrm *prm = &hn->prm;

    prm->mode = mode;
    prm->lo = lo;
    prm->hi = hi;
    hn->changed = 1;
}

void SFXA_GetLumiPrm(SfxaHn *hn, int *lo, int *hi, int *mode) {
    SfxaPrm *prm = &hn->prm;

    *mode = prm->mode;
    *lo = prm->lo;
    *hi = prm->hi;
}

void SFXA_SetAlp3Prm(SfxaHn *hn, unsigned char alpha0, unsigned char alpha1, unsigned char alpha2) {
    unsigned char *alpha = hn->alpha;

    alpha[0] = alpha0;
    alpha[1] = alpha1;
    alpha[2] = alpha2;
}

void SFXA_GetAlp3Prm(SfxaHn *hn, unsigned char *alpha0, unsigned char *alpha1, unsigned char *alpha2) {
    unsigned char *alpha = hn->alpha;

    *alpha0 = alpha[0];
    *alpha1 = alpha[1];
    *alpha2 = alpha[2];
}

void SFX_SetClipping(SfxaFrame *frm, int left, int top, int right, int bottom) {
    frm->right = right;
    frm->bottom = bottom;
    sfx_ClipFrame(frm, left, top, right, bottom);
}

/* Turns a line walk upside down: start at the last line and step backwards. */
void SFX_SetBottomUpDstBuf(SfxaLineWalk *walk) {
    int pitch = walk->pitch;

    walk->pitch = -pitch;
    walk->addr += pitch * (walk->lines - 1);
}

void SFX_SetBottomUpPlnBuf(SfxaLineWalk *walk) {
    int pitch = walk->pitch;

    walk->pitch = -pitch;
    walk->addr += pitch * (walk->lines - 1);
}

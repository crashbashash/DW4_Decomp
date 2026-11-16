/* CRI SFX conversion: checks a conversion format and, per composition kind, builds the lookup table the
 * conversion reads. Fields of the handles are named by offset. */

/* The format handle sfxcnv_IsCnvUpHalf checks. */
typedef struct SfxCnvHn {
    int pad0;
    int format;
} SfxCnvHn;

/* The conversion table handle: the composition kind it was last set to, and what the builders read. */
typedef struct SfxCnvTbl {
    char pad0[40];
    int f40;
    char pad44[8];
    int f52;
    char pad56[4];
    unsigned int compo;
    unsigned char *table;
} SfxCnvTbl;

typedef struct SfxCnvSrc {
    char pad0[76];
    int f76;
} SfxCnvSrc;

extern char DAT_004f53b0[];
extern char DAT_004f53e0[];
extern int D_004f5758[];
extern int D_004f5788[];

void SFXLIB_Error(void *hn, void *info, void *msg);
void sfxcnv_MakeTable(SfxCnvTbl *tbl, SfxCnvSrc *src, unsigned int compo);
int FUN_002b3bf0(void *hn);
int SFXZ_MakeCnvZ32Tbl();
int SFXZ_IsSetZclip(int x);
void FUN_002b50c8(SfxCnvTbl *tbl, int n);
int SFXA_IsNeedUpdateLumiTbl(int);
int SFXA_MakeAlpLumiTbl();
int SFXA_MakeAlp3110Tbl();
int SFXA_MakeAlp3Tbl();
int FUN_00284dc8();
int FUN_00284dc0();

void FUN_002b3510(SfxCnvTbl *tbl, SfxCnvSrc *src);
void FUN_002b3548(unsigned char *t);
void FUN_002b3530(SfxCnvTbl *tbl, SfxCnvSrc *src);
void FUN_002b3600(SfxCnvTbl *tbl, SfxCnvSrc *src);
void FUN_002b3620(SfxCnvTbl *tbl, SfxCnvSrc *src);
void FUN_002b3640(SfxCnvTbl *tbl, SfxCnvSrc *src);
void FUN_002b3660(SfxCnvTbl *tbl, SfxCnvSrc *src);
void FUN_002b3678(SfxCnvTbl *tbl, SfxCnvSrc *src);
int FUN_002b3490(SfxCnvTbl *tbl, unsigned int compo);

int sfxcnv_IsCnvUpHalf(SfxCnvHn *hn) {
    switch (hn->format) {
    case 4097:
        return 0;
    case 33:
    case 257:
        return 1;
    case 17:
    case 49:
    case 65:
    case 81:
    case 97:
    case 113:
    case 241:
    case 273:
        break;
    default:
        SFXLIB_Error(0, 0, DAT_004f53b0);
        break;
    }
    return 0;
}


void FUN_002b3300(SfxCnvTbl *tbl, SfxCnvSrc *src, unsigned int compo) {
    sfxcnv_MakeTable(tbl, src, compo);
}

void sfxcnv_MakeTable(SfxCnvTbl *tbl, SfxCnvSrc *src, unsigned int compo)
{
    if (FUN_002b3490(tbl, compo) != 1)
        return;
    tbl->compo = compo;
    switch (compo) {
    case 11:
    case 13:
        FUN_002b3510(tbl, src);
        return;
    case 2:
        FUN_002b3600(tbl, src);
        return;
    case 4:
        FUN_002b3620(tbl, src);
        return;
    case 5:
        FUN_002b3640(tbl, src);
        return;
    case 21:
        FUN_002b3660(tbl, src);
        return;
    case 22:
        FUN_002b3678(tbl, src);
        return;
    case 1:
        FUN_002b3530(tbl, src);
        return;
    case 0:
    case 100:
    default:
        SFXLIB_Error(tbl, (void *)src, DAT_004f53e0);
        return;
    }
}

int FUN_002b3490(SfxCnvTbl *tbl, unsigned int compo)
{
    int ret = 1;
    if (tbl->compo == 100)
        return 0;
    if (tbl->compo == compo) {
        switch (compo) {
        case 2:
            if (SFXA_IsNeedUpdateLumiTbl(tbl->f52) == 1)
                break;
        case 1:
        case 4:
        case 5:
        case 21:
        case 22:
            ret = 0;
            break;
        case 0:
        case 3:
        case 6 ... 20:
        case 23 ... 100:
        default:
            break;
        }
    }
    return ret;
}

void FUN_002b3510(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    SFXZ_MakeCnvZ32Tbl(tbl->f40, src->f76, tbl->table);
}

void FUN_002b3530(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    FUN_002b3548(tbl->table);
}

void FUN_002b3548(unsigned char *t) {
    int i;
    for (i = 0; i < 16; i++) {
        t[i] = 0;
    }
    for (i = 16; i < 236; i++) {
        t[i] = (unsigned int)((float)(i - 16) * 0.582f);
    }
    for (i = 236; i < 256; i++) {
        t[i] = 0x80;
    }
}

void FUN_002b3600(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    SFXA_MakeAlpLumiTbl(tbl->f52, src->f76, tbl->table);
}

void FUN_002b3620(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    SFXA_MakeAlp3110Tbl(tbl->f52, src->f76, tbl->table);
}

void FUN_002b3640(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    SFXA_MakeAlp3Tbl(tbl->f52, src->f76, tbl->table);
}

void FUN_002b3660(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    FUN_00284dc8(tbl->table);
}

void FUN_002b3678(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    FUN_00284dc0(tbl->table);
}

void SFX_MakeTblZ16(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    if (SFXZ_IsSetZclip(tbl->f40) != 1) {
        SFXLIB_Error(tbl, src, D_004f5758);
        return;
    }
    FUN_002b50c8(tbl, 16);
    FUN_002b3510(tbl, src);
}

void SFX_MakeTblZ32(SfxCnvTbl *tbl, SfxCnvSrc *src) {
    if (SFXZ_IsSetZclip(tbl->f40) != 1) {
        SFXLIB_Error(tbl, src, D_004f5788);
        return;
    }
    FUN_002b50c8(tbl, 32);
    FUN_002b3510(tbl, src);
}

int SFXINF_GetStmInf(void)
{
    return 17;
}

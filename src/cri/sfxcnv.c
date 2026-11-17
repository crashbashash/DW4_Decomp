/* CRI SFX conversion: checks a conversion format and, per composition kind, builds the lookup table the
 * conversion reads. Fields of the handles are named by offset. */
#include "dw4/cri/sfx.h"

/* The format handle sfxcnv_IsCnvUpHalf checks. */
typedef struct SfxCnvHn {
    int pad0;
    int format;
} SfxCnvHn;

/* The conversion table handle: the composition kind it was last set to, and what the builders read. */
struct SfxCnvTbl {
    char pad0[40];
    SfxZHn *zhn;
    char pad44[8];
    SfxaHn *ahn;
    char pad56[4];
    unsigned int compo;
    void *table;
};

void sfxcnv_MakeTable(SfxCnvTbl *tbl, SfxFrame *frm, unsigned int compo);

void sfxcnv_MakeZTbl(SfxCnvTbl *tbl, SfxFrame *frm);
void SFXCNV_MakeCcirFromY(unsigned char *t);
void sfxcnv_MakeCcirTbl(SfxCnvTbl *tbl, SfxFrame *frm);
void sfxcnv_MakeAlpLumiTbl(SfxCnvTbl *tbl, SfxFrame *frm);
void sfxcnv_MakeAlp3110Tbl(SfxCnvTbl *tbl, SfxFrame *frm);
void sfxcnv_MakeAlp3Tbl(SfxCnvTbl *tbl, SfxFrame *frm);
void sfxcnv_MakeColAdjTbl(SfxCnvTbl *tbl, SfxFrame *frm);
void sfxcnv_MakeYuv422ColAdjTbl(SfxCnvTbl *tbl, SfxFrame *frm);
int sfxcnv_IsNeedUpdateTbl(SfxCnvTbl *tbl, unsigned int compo);

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
        SFXLIB_Error(0, 0, "E201312: sfxcnv_IsCnvUpHalf : compo is invalid.");
        break;
    }
    return 0;
}

int SFX_DecideTableAlph3(void *hn, int compo) {
    int frmcompo;

    if (compo == 81) {
        return 4;
    }
    if (compo == 97) {
        return 5;
    }
    frmcompo = SFX_GetFxType(hn);
    if (frmcompo == 81) {
        return 4;
    }
    if (frmcompo == 97) {
        return 5;
    }
    return 5;
}

void SFX_MakeTable(SfxCnvTbl *tbl, SfxFrame *frm, unsigned int compo) {
    sfxcnv_MakeTable(tbl, frm, compo);
}

void sfxcnv_MakeTable(SfxCnvTbl *tbl, SfxFrame *frm, unsigned int compo)
{
    if (sfxcnv_IsNeedUpdateTbl(tbl, compo) != 1)
        return;
    tbl->compo = compo;
    switch (compo) {
    case 11:
    case 13:
        sfxcnv_MakeZTbl(tbl, frm);
        return;
    case 2:
        sfxcnv_MakeAlpLumiTbl(tbl, frm);
        return;
    case 4:
        sfxcnv_MakeAlp3110Tbl(tbl, frm);
        return;
    case 5:
        sfxcnv_MakeAlp3Tbl(tbl, frm);
        return;
    case 21:
        sfxcnv_MakeColAdjTbl(tbl, frm);
        return;
    case 22:
        sfxcnv_MakeYuv422ColAdjTbl(tbl, frm);
        return;
    case 1:
        sfxcnv_MakeCcirTbl(tbl, frm);
        return;
    case 0:
    case 100:
    default:
        SFXLIB_Error(tbl, frm, "E201311: sfxcnv_MakeTable : compo is not support.");
        return;
    }
}

int sfxcnv_IsNeedUpdateTbl(SfxCnvTbl *tbl, unsigned int compo)
{
    int ret = 1;
    if (tbl->compo == 100)
        return 0;
    if (tbl->compo == compo) {
        switch (compo) {
        case 2:
            if (SFXA_IsNeedUpdateLumiTbl(tbl->ahn) == 1)
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

void sfxcnv_MakeZTbl(SfxCnvTbl *tbl, SfxFrame *frm) {
    SFXZ_MakeCnvZTbl(tbl->zhn, frm->fno, tbl->table);
}

void sfxcnv_MakeCcirTbl(SfxCnvTbl *tbl, SfxFrame *frm) {
    SFXCNV_MakeCcirFromY(tbl->table);
}

void SFXCNV_MakeCcirFromY(unsigned char *t) {
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

void sfxcnv_MakeAlpLumiTbl(SfxCnvTbl *tbl, SfxFrame *frm) {
    SFXA_MakeAlpLumiTbl(tbl->ahn, frm->fno, tbl->table);
}

void sfxcnv_MakeAlp3110Tbl(SfxCnvTbl *tbl, SfxFrame *frm) {
    SFXA_MakeAlp3110Tbl(tbl->ahn, frm->fno, tbl->table);
}

void sfxcnv_MakeAlp3Tbl(SfxCnvTbl *tbl, SfxFrame *frm) {
    SFXA_MakeAlp3Tbl(tbl->ahn, frm->fno, tbl->table);
}

void sfxcnv_MakeColAdjTbl(SfxCnvTbl *tbl, SfxFrame *frm) {
    CFT_MakeArgb8888ColAdjTbl(tbl->table);
}

void sfxcnv_MakeYuv422ColAdjTbl(SfxCnvTbl *tbl, SfxFrame *frm) {
    CFT_MakeYcc422ColAdjTbl(tbl->table);
}

void SFX_MakeTblZ16(SfxCnvTbl *tbl, SfxFrame *frm) {
    if (SFXZ_IsSetZclip(tbl->zhn) != 1) {
        SFXLIB_Error(tbl, frm, "E202282: SFX_MakeTblZ16 : zclip is not set.");
        return;
    }
    SFX_SetZbit(tbl, 16);
    sfxcnv_MakeZTbl(tbl, frm);
}

void SFX_MakeTblZ32(SfxCnvTbl *tbl, SfxFrame *frm) {
    if (SFXZ_IsSetZclip(tbl->zhn) != 1) {
        SFXLIB_Error(tbl, frm, "E202281: SFX_MakeTblZ32 : zclip is not set.");
        return;
    }
    SFX_SetZbit(tbl, 32);
    sfxcnv_MakeZTbl(tbl, frm);
}

int SFXINF_GetStmInf(SfxFrame *frm, char *tag)
{
    return 17;
}

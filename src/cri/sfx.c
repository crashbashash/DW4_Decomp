#include "dw4/cri/sfx.h"
#include "dw4/cri/sud.h"
#include <string.h>
#include "dw4/cri/sj.h"

typedef struct SfxCbSlot {
    SfxErrFn fn;
    void *obj;
    int count;
} SfxCbSlot;

typedef struct SfxLib {
    int nhn;
    int maxhn;
    SfxCbSlot err;
    int f20;
    SfxHn hn[8];
    int pad984[4];
} SfxLib;

extern int sfx_init_cnt;
extern int sfxcnv_forcesplit;
extern SfxLib sfx_libwork;
extern char *volatile sfx_version_ptr; /* matching construct: volatile — stored through a materialised address */


void FUN_00283038();
int FUN_002b53a0();
int FUN_002b5400();
int FUN_002b5490();
int FUN_002b54f8();
int FUN_002b5578();
int FUN_002b55f8();
int FUN_002b5678();

/* kept here unprototyped: their definitions take volatile pointers, which sfx.h would show to every unit */
int SFXA_Destroy();
void SFXZ_Destroy();

char *sfx_GetVersionStr(void);
void sfx_InitLibWork(void);
SfxHn *sfx_SearchFreeHn(void);
void sfx_InitHn(SfxHn *hn, int work, int wksize);
int sfx_IsEnoughHnWorkSize(int wksize, int a, int b);
void SFXSET_SetTblPtn(SfxHn *hn, int value);
void sfxset_ShiftBufInfByLine(SfxPlane *plane, int lines);
void FUN_002b3fd0(SfxPlane *plane, int first, int second);
void SFXSUD_Init(void);
void SFXSUD_Finish(void);

void SFX_Init(void) {
    int *initialised = &sfx_init_cnt;
    if (*initialised > 0) {
        return;
    }
    sfx_version_ptr = sfx_GetVersionStr();
    sfx_InitLibWork();
    SFXSUD_Init();
    SFXZ_Init();
    SFXA_Init();
    sfxcnv_forcesplit = 0;
    (*initialised)++;
}

char *sfx_GetVersionStr(void) {
    return "\nCRI SFX/PS2EE Ver.2.08 Build:Oct  6 2004 11:36:34\n";
}

void sfx_InitLibWork(void) {
    memset(&sfx_libwork, 0, 1000);
    sfx_libwork.maxhn = 8;
    SFX_SetCcirFx(1);
    CFT_Init();
    CFT_Ycc420rgbToArgb8888();
}

void SFX_Finish(void) {
    if (sfx_init_cnt > 0) {
        SFXZ_Finish();
        SFXA_Finish();
        SFXSUD_Finish();
        CFT_Finish();
        sfx_init_cnt--;
    }
}

void SFX_SetErrFn(SfxErrFn fn, void *obj) {
    SfxCbSlot *err = &sfx_libwork.err;
    err->fn = fn;
    err->obj = obj;
}

SfxHn *SFX_Create(int work, int wksize, int a2, int a3) {
    SfxHn *hn;
    SfxZHn *zhn;
    void *ahn;
    hn = sfx_SearchFreeHn();
    if (hn == 0) return hn;
    if (sfx_IsEnoughHnWorkSize(wksize, a2, a3) != 1) {
        SFXLIB_Error(0, 0, "E201194: sfx_InitHn: work size is short.");
        return 0;
    }
    sfx_InitHn(hn, work, wksize);
    zhn = SFXZ_Create();
    if (zhn == 0) {
        SFXLIB_Error(0, 0, "E201281: SfxZHn: can't create.");
        SFX_Destroy(hn);
        return 0;
    }
    hn->zhn = zhn;
    ahn = SFXA_Create();
    if (ahn == 0) {
        SFXLIB_Error(0, 0, "E202011: SfxAHn: can't create.");
        SFX_Destroy(hn);
        return 0;
    }
    hn->ahn = ahn;
    sfx_libwork.nhn++;
    return hn;
}

/* matching construct: manual — the in-use word is read through a volatile pointer; retail leaves the loop branch's delay slot empty */
SfxHn *sfx_SearchFreeHn(void) {
    int maxhn = sfx_libwork.maxhn;
    SfxHn *tbl = sfx_libwork.hn;
    volatile SfxHn *hn;
    int i;

    for (i = 0; i < maxhn; i++) {
        hn = &tbl[i];
        if (hn->used == 0) {
            return (SfxHn *)hn;
        }
    }
    return 0;
}

void sfx_InitHn(SfxHn *hn, int work, int wksize) {
    int base;
    memset(hn, 0, 0x78);
    base = (work + 31) & ~31;
    hn->width = 0;
    hn->height = 0;
    hn->f44 = 1;
    hn->used = 1;
    hn->f8 = 17;
    hn->f48 = 0;
    hn->f60 = 0;
    hn->tbl[0] = base;
    hn->tbl[1] = base + 0x400;
    hn->tbl[2] = base + 0x800;
    hn->tbl[3] = base + 0xC00;
    hn->work = work;
    hn->wksize = wksize;
    hn->f104 = -1;
    hn->f116 = 0;
    hn->compo = 0;
}

int sfx_IsEnoughHnWorkSize(int wksize, int a, int b) {
    return wksize >= 0x181F;
}

void SFX_Destroy(SfxHn *hn) {
    void *ahn;
    if (hn != 0) {
        ahn = hn->ahn;
        hn->used = 0;
        SFXZ_Destroy(hn->zhn);
        SFXA_Destroy(ahn);
        sfx_libwork.nhn -= 1;
    }
}

void SFXLIB_Error(void *obj, void *info, char *msg) {
    /* Both callback words are read before the counter is bumped, as in retail. */
    SfxCbSlot *slot = &sfx_libwork.err;
    SfxErrFn fn = slot->fn;
    void *cbobj = slot->obj;
    slot->count++;
    if (fn != 0) {
        fn(cbobj, msg);
    }
}

void SFX_SetCcirFx(int value) {
    sfx_libwork.f20 = value;
}

int SFX_GetCcirFx(void) {
    return sfx_libwork.f20;
}

void SFX_SetForceSplit(int value) {
    sfxcnv_forcesplit = value;
}

int SFX_GetForceSplit(void) {
    return sfxcnv_forcesplit;
}

void FUN_002b3bb8(SfxHn *hn, SfxZCbFn fn) {
    hn->zhn->cbfn = fn;
}

void FUN_002b3bc8(SfxHn *hn, int arg) {
    hn->zhn->cbarg = arg;
}

void SFX_SetCompoMode(SfxHn *hn, int value) {
    hn->compo = value;
}

int SFX_GetCompoMode(SfxHn *hn) {
    return hn->compo;
}

void SFX_SetFxType(SfxHn *hn, int value) {
    hn->f8 = value;
}

int SFX_GetFxType(SfxHn *hn) {
    return hn->f8;
}

void SFX_SetOutBufSize(SfxHn *hn, int width, int height) {
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    hn->width = width;
    hn->height = height;
}

int SFX_GetOutBufSize(SfxHn *hn, int *width, int *height) {
    int t = hn->width;
    *width = t;
    *height = hn->height;
    return t;
}

void SFX_SetUnitWidth(SfxHn *hn, int value) {
    hn->f20 = value;
}

void SFX_SetCnvTable(SfxHn *hn, int index, int value) {
    SFXSET_SetTblPtn(hn, 100);
    hn->tbl[index] = value;
}

int SFX_GetCnvTable(SfxHn *hn, int index) {
    return hn->tbl[index];
}

void SFXSET_SetTblPtn(SfxHn *hn, int value) {
    hn->f60 = value;
}

int SFXSET_GetTblPtn(SfxHn *hn) {
    return hn->f60;
}

void SFX_SetTagInf(SfxHn *hn, char *data, int size) {
    SfxChunk *zinf = &hn->zinf;
    SfxZHn *zhn;
    SfdSjChunk in;
    SfdSjChunk out;
    zinf->data = data;
    zinf->size = size;
    zhn = hn->zhn;
    in.data = data;
    in.len = size;
    if (SJ_SearchTag(&in, "SFXZ", "SFXINFE", &out) == 0)
        SFXZ_SetTagInf(zhn, 0, 0);
    else
        SFXZ_SetTagInf(zhn, out.data, out.len);
    zinf->valid = 1;
}

void SFX_GetTagInf(SfxHn *hn, char **data, int *size) {
    SfxChunk *zinf = &hn->zinf;
    char *value4;
    int value8;
    if (zinf->valid != 1) {
        *data = 0;
        *size = 0;
        return;
    }
    /* Both reads precede the stores: the outputs could alias the record. */
    value4 = zinf->data;
    value8 = zinf->size;
    *size = value8;
    *data = value4;
}

void SFX_SetOutZscale(SfxHn *hn, int value) {
    hn->f44 = value;
}

int SFX_GetOutZscale(SfxHn *hn) {
    return hn->f44;
}

void SFX_SetOutZoffset(SfxHn *hn, int value) {
    hn->f48 = value;
}

int SFX_GetOutZoffset(SfxHn *hn) {
    return hn->f48;
}

void SFX_SetZclip(SfxHn *hn, float zmin, float zmax) {
    SFXZ_SetZclip(hn->zhn, zmin, zmax);
}

void SFX_GetZclip(SfxHn *hn, float *zmin, float *zmax) {
    SFXZ_GetZclip(hn->zhn, zmin, zmax);
}

void SFX_GetZfrmRange(SfxHn *hn, SfxFrame *frm, int *first, int *second) {
    SFXZ_GetZfrmRange(hn->zhn, frm->fno, first, second);
}

void SFX_SetALumiPrm(SfxHn *hn, int lo, int hi, int mode) {
    SFXA_SetLumiPrm(hn->ahn, lo, hi, mode);
}

void SFX_GetALumiPrm(SfxHn *hn, int *lo, int *hi, int *mode) {
    SFXA_GetLumiPrm(hn->ahn, lo, hi, mode);
}

void SFX_SetAlp3Prm(SfxHn *hn, int a, int b, int c) {
    SFXA_SetAlp3Prm(hn->ahn, a & 0xFF, b & 0xFF, c & 0xFF);
    SFXSET_SetTblPtn(hn, 0);
}

void SFX_GetAlp3Prm(SfxHn *hn, unsigned char *alpha0, unsigned char *alpha1, unsigned char *alpha2) {
    SFXA_GetAlp3Prm(hn->ahn, alpha0, alpha1, alpha2);
}

void SFX_SetColAdj(SfxHn *hn, int value) {
    hn->f56 = value;
}

int SFX_GetColAdj(SfxHn *hn) {
    return hn->f56;
}

void SFX_SetSplitField(SfxHn *hn, int value) {
    hn->f104 = value;
}

int SFX_GetSplitField(SfxHn *hn) {
    return hn->f104;
}

void SFX_SetProgOut(SfxHn *hn, int value) {
    hn->f108 = value;
}

int SFX_GetProgOut(SfxHn *hn) {
    return hn->f108;
}

void SFX_SetCnvBottomUp(SfxHn *hn, int value) {
    hn->f116 = value;
}

int SFX_GetCnvBottomUp(SfxHn *hn) {
    return hn->f116;
}

void SFX_ShiftYccPtrByLine(SfxFrame *frm, int lines) {
    lines = lines / 2 * 2;
    sfxset_ShiftBufInfByLine(&frm->plane[0], lines);
    sfxset_ShiftBufInfByLine(&frm->plane[1], lines >> 1);
    sfxset_ShiftBufInfByLine(&frm->plane[2], lines >> 1);
}

void sfxset_ShiftBufInfByLine(SfxPlane *plane, int lines) {
    int pitch = plane->pitch;
    int addr = plane->addr;
    plane->height -= lines;
    plane->addr = addr + lines * pitch;
}

void SFX_SetMaxRowToYccPln(SfxFrame *frm, int height) {
    height = height / 2 * 2;
    frm->plane[0].height = height;
    frm->plane[1].height = height >> 1;
    frm->plane[2].height = height >> 1;
}

void sfx_ClipFrame(SfxFrame *frm, int second, int first) {
    first = first / 2 * 2;
    second = second / 2 * 2;
    FUN_002b3fd0(&frm->plane[0], first, second);
    FUN_002b3fd0(&frm->plane[1], first >> 1, second >> 1);
    FUN_002b3fd0(&frm->plane[2], first >> 1, second >> 1);
}

void FUN_002b3fd0(SfxPlane *plane, int first, int second) {
    plane->height = plane->height - first;
    plane->addr = plane->addr + first * plane->pitch + second;
}

void SFX_SetMaxAlpha(SfxHn *hn, int value) {
    unsigned int temp_s0;
    temp_s0 = value & 0xFF;
    CFT_SetMaxAlpha(value);
    SFXSET_SetTblPtn(hn, 0);
    SFX_SetAlp3Prm(hn, 0, temp_s0 >> 1, temp_s0);
}

int SFX_GetMaxAlpha(SfxHn *hn) {
    return CFT_GetMaxAlpha();
}

void FUN_002b4068(void) {
    FUN_00283038();
}

void SFXSUD_Init(void) {
    SUD_Init();
}

void SFXSUD_Finish(void) {
    SUD_Finish();
}

void SFX_SetPicUsrDat(SfxHn *hn, char *ud, int size) {
    int *sud = hn->sud;
    sud[0] = (int)ud;
    sud[1] = size;
}

int SFX_IsEnablePicUsr(SfxHn *hn) {
    return hn->sud[0] != 0;
}

int SFX_GetSudVersion(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    return SUD_AnalyVersion((char *)sud[0], sud[1]);
}

int SFX_GetTypeDivField(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    /* the handle keeps the user-data header address as a word */
    return SUD_AnalyTypeDivField((char *)sud[0], sud[1]);
}

int SFX_GetTypeCcs(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    /* the handle keeps the user-data header address as a word */
    return SUD_AnalyTypeCcs((char *)sud[0], sud[1]);
}

void FUN_002b4130(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b53a0(sud[0], sud[1]);
}

void FUN_002b4150(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b5400(sud[0], sud[1]);
}

void FUN_002b4170(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b5490(sud[0], sud[1]);
}

void FUN_002b4190(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b54f8(sud[0], sud[1]);
}

void FUN_002b41b0(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b5578(sud[0], sud[1]);
}

void FUN_002b41d0(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b55f8(sud[0], sud[1]);
}

void FUN_002b41f0(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b5678(sud[0], sud[1]);
}

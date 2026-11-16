#include "dw4/cri/sfx.h"

typedef struct SfxPicInf {
    int pad0[19];
    int fno;
} SfxPicInf;

typedef struct SfxCbSlot {
    void (*fn)(int arg, char *msg);
    int arg;
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

extern int DAT_004bec20;
extern int DAT_004bec24;
extern SfxLib DAT_004bec28;
extern char *volatile DAT_005856a0; /* matching construct: volatile — stored through a materialised address */

extern char DAT_004f57b8[];
extern char DAT_004f57f0[];
extern char DAT_004f5820[];
extern char DAT_004f5840[];
extern char DAT_004f5860[];
extern char DAT_004f5868[];

void *memset(void *dst, int value, unsigned int size);
int SJ_SearchTag(SfxMem *in, char *tag, char *endtag, SfxMem *out);
void FUN_00283038();
void FUN_00283058(void);
/* matching construct: manual — CFT_Finish declared void (its result is unused) leaves v0 free for the decrement, as in retail */
void CFT_Finish();
int FUN_002830a8();
void FUN_002830d0();
void CFT_Ycc420rgbToArgb8888(void);
void SFXA_Init(void);
int SFXA_Finish();
void *SFXA_Create(void);
int SFXA_Destroy();
int SFXA_SetLumiPrm();
int SFXA_GetLumiPrm();
int SFXA_SetAlp3Prm();
int SFXA_GetAlp3Prm();
void SFXZ_Destroy();
int SUD_Init();
int SUD_Finish();
int FUN_002b52d8();
int SUD_AnalyTypeDivField();
int SUD_AnalyTypeCcs();
int FUN_002b53a0();
int FUN_002b5400();
int FUN_002b5490();
int FUN_002b54f8();
int FUN_002b5578();
int FUN_002b55f8();
int FUN_002b5678();

char *sfx_GetVersionStr(void);
void sfx_InitLibWork(void);
SfxHn *sfx_SearchFreeHn(void);
void sfx_InitHn(SfxHn *hn, int work, int wksize);
int sfx_IsEnoughHnWorkSize(int wksize, int a, int b);
void SFX_Destroy(SfxHn *hn);
void FUN_002b3b78(int value);
void SFXSET_SetTblPtn(SfxHn *hn, int value);
void FUN_002b3e00(SfxHn *hn, int a, int b, int c);
void sfxset_ShiftBufInfByLine(SfxPlane *plane, int lines);
void FUN_002b3fd0(SfxPlane *plane, int first, int second);
void FUN_002b4080(void);
void FUN_002b4098(void);

void SFX_Init(void) {
    int *initialised = &DAT_004bec20;
    if (*initialised > 0) {
        return;
    }
    DAT_005856a0 = sfx_GetVersionStr();
    sfx_InitLibWork();
    FUN_002b4080();
    SFXZ_Init();
    SFXA_Init();
    DAT_004bec24 = 0;
    (*initialised)++;
}

char *sfx_GetVersionStr(void) {
    return DAT_004f57b8;
}

void sfx_InitLibWork(void) {
    memset(&DAT_004bec28, 0, 1000);
    DAT_004bec28.maxhn = 8;
    FUN_002b3b78(1);
    FUN_00283058();
    CFT_Ycc420rgbToArgb8888();
}

void SFX_Finish(void) {
    if (DAT_004bec20 > 0) {
        SFXZ_Finish();
        SFXA_Finish();
        FUN_002b4098();
        CFT_Finish();
        DAT_004bec20--;
    }
}

void SFX_SetErrFn(void (*fn)(int arg, char *msg), int arg) {
    SfxCbSlot *err = &DAT_004bec28.err;
    err->fn = fn;
    err->arg = arg;
}

SfxHn *SFX_Create(int work, int wksize, int a2, int a3) {
    SfxHn *hn;
    SfxZHn *zhn;
    void *ahn;
    hn = sfx_SearchFreeHn();
    if (hn == 0) return hn;
    if (sfx_IsEnoughHnWorkSize(wksize, a2, a3) != 1) {
        SFXLIB_Error(0, 0, DAT_004f57f0);
        return 0;
    }
    sfx_InitHn(hn, work, wksize);
    zhn = SFXZ_Create();
    if (zhn == 0) {
        SFXLIB_Error(0, 0, DAT_004f5820);
        SFX_Destroy(hn);
        return 0;
    }
    hn->zhn = zhn;
    ahn = SFXA_Create();
    if (ahn == 0) {
        SFXLIB_Error(0, 0, DAT_004f5840);
        SFX_Destroy(hn);
        return 0;
    }
    hn->ahn = ahn;
    DAT_004bec28.nhn++;
    return hn;
}

/* matching construct: manual — the in-use word is read through a volatile pointer; retail leaves the loop branch's delay slot empty */
SfxHn *sfx_SearchFreeHn(void) {
    int maxhn = DAT_004bec28.maxhn;
    SfxHn *tbl = DAT_004bec28.hn;
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
        DAT_004bec28.nhn -= 1;
    }
}

void SFXLIB_Error(void *obj, void *info, char *msg) {
    /* Both callback words are read before the counter is bumped, as in retail. */
    SfxCbSlot *slot = &DAT_004bec28.err;
    void (*fn)(int arg, char *msg) = slot->fn;
    int arg = slot->arg;
    slot->count++;
    if (fn != 0) {
        fn(arg, msg);
    }
}

void FUN_002b3b78(int value) {
    DAT_004bec28.f20 = value;
}

int FUN_002b3b88(void) {
    return DAT_004bec28.f20;
}

void FUN_002b3b98(int value) {
    DAT_004bec24 = value;
}

int FUN_002b3ba8(void) {
    return DAT_004bec24;
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

void SFX_SetOutBufSize(SfxHn *hn, int value) {
    hn->f8 = value;
}

int FUN_002b3bf0(SfxHn *hn) {
    return hn->f8;
}

void FUN_002b3bf8(SfxHn *hn, int width, int height) {
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

void FUN_002b3c20(SfxHn *hn, int value) {
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
    SfxMem in;
    SfxMem out;
    zinf->data = data;
    zinf->size = size;
    zhn = hn->zhn;
    in.data = data;
    in.size = size;
    if (SJ_SearchTag(&in, DAT_004f5860, DAT_004f5868, &out) == 0)
        SFXZ_SetTagInf(zhn, 0, 0);
    else
        SFXZ_SetTagInf(zhn, out.data, out.size);
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

void SFX_GetZfrmRange(SfxHn *hn, SfxPicInf *pic, int *first, int *second) {
    FUN_002b4498(hn->zhn, pic->fno, first, second);
}

void FUN_002b3dd0(SfxHn *hn) {
    SFXA_SetLumiPrm(hn->ahn);
}

void SFX_SetALumiPrm(SfxHn *hn) {
    SFXA_GetLumiPrm(hn->ahn);
}

void FUN_002b3e00(SfxHn *hn, int a, int b, int c) {
    SFXA_SetAlp3Prm(hn->ahn, a & 0xFF, b & 0xFF, c & 0xFF);
    SFXSET_SetTblPtn(hn, 0);
}

void SFX_GetALumiPrm(SfxHn *hn) {
    SFXA_GetAlp3Prm(hn->ahn);
}

void FUN_002b3e58(SfxHn *hn, int value) {
    hn->f56 = value;
}

int FUN_002b3e60(SfxHn *hn) {
    return hn->f56;
}

void SFX_SetColAdj(SfxHn *hn, int value) {
    hn->f104 = value;
}

int SFX_GetColAdj(SfxHn *hn) {
    return hn->f104;
}

void SFX_SetSplitField(SfxHn *hn, int value) {
    hn->f108 = value;
}

int SFX_GetSplitField(SfxHn *hn) {
    return hn->f108;
}

void SFX_SetProgOut(SfxHn *hn, int value) {
    hn->f116 = value;
}

int SFX_GetProgOut(SfxHn *hn) {
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

void FUN_002b3ff8(SfxHn *hn, int value) {
    unsigned int temp_s0;
    temp_s0 = value & 0xFF;
    FUN_002830a8(value);
    SFXSET_SetTblPtn(hn, 0);
    FUN_002b3e00(hn, 0, temp_s0 >> 1, temp_s0);
}

void FUN_002b4050(void) {
    FUN_002830d0();
}

void FUN_002b4068(void) {
    FUN_00283038();
}

void FUN_002b4080(void) {
    SUD_Init();
}

void FUN_002b4098(void) {
    SUD_Finish();
}

void FUN_002b40b0(SfxHn *hn, int a, int b) {
    int *sud = hn->sud;
    sud[0] = a;
    sud[1] = b;
}

int FUN_002b40c0(SfxHn *hn) {
    return hn->sud[0] != 0;
}

void FUN_002b40d0(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b52d8(sud[0], sud[1]);
}

void FUN_002b40f0(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    SUD_AnalyTypeDivField(sud[0], sud[1]);
}

void FUN_002b4110(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    SUD_AnalyTypeCcs(sud[0], sud[1]);
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

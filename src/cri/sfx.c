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
/* matching construct: manual — FUN_00283090 declared void (its result is unused) leaves v0 free for the decrement, as in retail */
void FUN_00283090();
int FUN_002830a8();
void FUN_002830d0();
void FUN_002830f0(void);
void sfxa_Init(void);
int sfxa_Finish();
void *SFXA_Create(void);
int SFXA_Destroy();
int SFXA_SetLumiPrm();
int SFXA_GetLumiPrm();
int SFXA_SetAlp3Prm();
int SFXA_GetAlp3Prm();
void FUN_002b4330();
int FUN_002b50e8();
int FUN_002b5148();
int FUN_002b52d8();
int FUN_002b5320();
int FUN_002b5360();
int FUN_002b53a0();
int FUN_002b5400();
int FUN_002b5490();
int FUN_002b54f8();
int FUN_002b5578();
int FUN_002b55f8();
int FUN_002b5678();

char *FUN_002b37f8(void);
void FUN_002b3808(void);
SfxHn *FUN_002b39e0(void);
void FUN_002b3a30(SfxHn *hn, int work, int wksize);
int FUN_002b3ad8(int wksize, int a, int b);
void FUN_002b3ae8(SfxHn *hn);
void FUN_002b3b78(int value);
void FUN_002b3c88(SfxHn *hn, int value);
void FUN_002b3e00(SfxHn *hn, int a, int b, int c);
void FUN_002b3ef8(SfxPlane *plane, int lines);
void FUN_002b3fd0(SfxPlane *plane, int first, int second);
void FUN_002b4080(void);
void FUN_002b4098(void);

void FUN_002b3788(void) {
    int *initialised = &DAT_004bec20;
    if (*initialised > 0) {
        return;
    }
    DAT_005856a0 = FUN_002b37f8();
    FUN_002b3808();
    FUN_002b4080();
    FUN_002b4210();
    sfxa_Init();
    DAT_004bec24 = 0;
    (*initialised)++;
}

char *FUN_002b37f8(void) {
    return DAT_004f57b8;
}

void FUN_002b3808(void) {
    memset(&DAT_004bec28, 0, 1000);
    DAT_004bec28.maxhn = 8;
    FUN_002b3b78(1);
    FUN_00283058();
    FUN_002830f0();
}

void FUN_002b3858(void) {
    if (DAT_004bec20 > 0) {
        FUN_002b4268();
        sfxa_Finish();
        FUN_002b4098();
        FUN_00283090();
        DAT_004bec20--;
    }
}

void FUN_002b38b0(void (*fn)(int arg, char *msg), int arg) {
    SfxCbSlot *err = &DAT_004bec28.err;
    err->fn = fn;
    err->arg = arg;
}

SfxHn *FUN_002b38c8(int work, int wksize, int a2, int a3) {
    SfxHn *hn;
    SfxZHn *zhn;
    void *ahn;
    hn = FUN_002b39e0();
    if (hn == 0) return hn;
    if (FUN_002b3ad8(wksize, a2, a3) != 1) {
        FUN_002b3b38(0, 0, DAT_004f57f0);
        return 0;
    }
    FUN_002b3a30(hn, work, wksize);
    zhn = FUN_002b4270();
    if (zhn == 0) {
        FUN_002b3b38(0, 0, DAT_004f5820);
        FUN_002b3ae8(hn);
        return 0;
    }
    hn->zhn = zhn;
    ahn = SFXA_Create();
    if (ahn == 0) {
        FUN_002b3b38(0, 0, DAT_004f5840);
        FUN_002b3ae8(hn);
        return 0;
    }
    hn->ahn = ahn;
    DAT_004bec28.nhn++;
    return hn;
}

/* matching construct: manual — the in-use word is read through a volatile pointer; retail leaves the loop branch's delay slot empty */
SfxHn *FUN_002b39e0(void) {
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

void FUN_002b3a30(SfxHn *hn, int work, int wksize) {
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

int FUN_002b3ad8(int wksize, int a, int b) {
    return wksize >= 0x181F;
}

void FUN_002b3ae8(SfxHn *hn) {
    void *ahn;
    if (hn != 0) {
        ahn = hn->ahn;
        hn->used = 0;
        FUN_002b4330(hn->zhn);
        SFXA_Destroy(ahn);
        DAT_004bec28.nhn -= 1;
    }
}

void FUN_002b3b38(void *obj, void *info, char *msg) {
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

void FUN_002b3bd8(SfxHn *hn, int value) {
    hn->compo = value;
}

int FUN_002b3be0(SfxHn *hn) {
    return hn->compo;
}

void FUN_002b3be8(SfxHn *hn, int value) {
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

int FUN_002b3c08(SfxHn *hn, int *width, int *height) {
    int t = hn->width;
    *width = t;
    *height = hn->height;
    return t;
}

void FUN_002b3c20(SfxHn *hn, int value) {
    hn->f20 = value;
}

void FUN_002b3c28(SfxHn *hn, int index, int value) {
    FUN_002b3c88(hn, 100);
    hn->tbl[index] = value;
}

int FUN_002b3c78(SfxHn *hn, int index) {
    return hn->tbl[index];
}

void FUN_002b3c88(SfxHn *hn, int value) {
    hn->f60 = value;
}

int FUN_002b3c90(SfxHn *hn) {
    return hn->f60;
}

void FUN_002b3c98(SfxHn *hn, char *data, int size) {
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
        FUN_002b4358(zhn, 0, 0);
    else
        FUN_002b4358(zhn, out.data, out.size);
    zinf->valid = 1;
}

void SFX_GetZinf(SfxHn *hn, char **data, int *size) {
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

void FUN_002b3d60(SfxHn *hn, int value) {
    hn->f44 = value;
}

int FUN_002b3d68(SfxHn *hn) {
    return hn->f44;
}

void FUN_002b3d70(SfxHn *hn, int value) {
    hn->f48 = value;
}

int FUN_002b3d78(SfxHn *hn) {
    return hn->f48;
}

void FUN_002b3d80(SfxHn *hn, float zmin, float zmax) {
    FUN_002b4aa8(hn->zhn, zmin, zmax);
}

void FUN_002b3d98(SfxHn *hn, float *zmin, float *zmax) {
    FUN_002b4b40(hn->zhn, zmin, zmax);
}

void FUN_002b3db0(SfxHn *hn, SfxPicInf *pic, int *first, int *second) {
    FUN_002b4498(hn->zhn, pic->fno, first, second);
}

void FUN_002b3dd0(SfxHn *hn) {
    SFXA_SetLumiPrm(hn->ahn);
}

void FUN_002b3de8(SfxHn *hn) {
    SFXA_GetLumiPrm(hn->ahn);
}

void FUN_002b3e00(SfxHn *hn, int a, int b, int c) {
    SFXA_SetAlp3Prm(hn->ahn, a & 0xFF, b & 0xFF, c & 0xFF);
    FUN_002b3c88(hn, 0);
}

void FUN_002b3e40(SfxHn *hn) {
    SFXA_GetAlp3Prm(hn->ahn);
}

void FUN_002b3e58(SfxHn *hn, int value) {
    hn->f56 = value;
}

int FUN_002b3e60(SfxHn *hn) {
    return hn->f56;
}

void FUN_002b3e68(SfxHn *hn, int value) {
    hn->f104 = value;
}

int FUN_002b3e70(SfxHn *hn) {
    return hn->f104;
}

void FUN_002b3e78(SfxHn *hn, int value) {
    hn->f108 = value;
}

int FUN_002b3e80(SfxHn *hn) {
    return hn->f108;
}

void FUN_002b3e88(SfxHn *hn, int value) {
    hn->f116 = value;
}

int FUN_002b3e90(SfxHn *hn) {
    return hn->f116;
}

void FUN_002b3e98(SfxFrame *frm, int lines) {
    lines = lines / 2 * 2;
    FUN_002b3ef8(&frm->plane[0], lines);
    FUN_002b3ef8(&frm->plane[1], lines >> 1);
    FUN_002b3ef8(&frm->plane[2], lines >> 1);
}

void FUN_002b3ef8(SfxPlane *plane, int lines) {
    int pitch = plane->pitch;
    int addr = plane->addr;
    plane->height -= lines;
    plane->addr = addr + lines * pitch;
}

void FUN_002b3f20(SfxFrame *frm, int height) {
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
    FUN_002b3c88(hn, 0);
    FUN_002b3e00(hn, 0, temp_s0 >> 1, temp_s0);
}

void FUN_002b4050(void) {
    FUN_002830d0();
}

void FUN_002b4068(void) {
    FUN_00283038();
}

void FUN_002b4080(void) {
    FUN_002b50e8();
}

void FUN_002b4098(void) {
    FUN_002b5148();
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
    FUN_002b5320(sud[0], sud[1]);
}

void FUN_002b4110(SfxHn *hn) {
    /* matching construct: manual — the pair pointer is kept, so retail addresses both words from obj+96 */
    int *sud = hn->sud;
    FUN_002b5360(sud[0], sud[1]);
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

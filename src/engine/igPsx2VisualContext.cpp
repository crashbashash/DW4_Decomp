#include "dw4/reflected.h"

extern "C" {

struct VisualContextTextures;
class TextureImage;
struct O520;
struct S0;
struct Oab80;
struct OB1d0;

int memset(void *p, int v, int n);
void *thunk_FUN_002ed3b0(void *p, int n, int a);
void *Memory_FindBufferOwner(void *p);
void *Memory_AllocateBufferDirect(int n, int a);
int Memory_FreeBuffer(...);
void igObject_Destroy(void *object);
int FUN_00165cb0(void *self);
void *FUN_00165cf0(void *self);
int FUN_00165d10(void *self);
int FUN_00165bb0(void *self);
int FUN_00164f50();
int FUN_00169260(void *self, int option);
int FUN_0016c650(void *self, int option);
int FUN_00170510(void *self, int option);
int FUN_001788e0(void *self, int option);
int FUN_0017a540(void *self, int option);
int FUN_0017a2b0(int format);
int FUN_0017aa20(void *self, int width, int height, int format, int kind, unsigned int flags, unsigned int levels);
int FUN_00193540(void *a, int b, int c);
void FUN_0015a530(TextureImage *image, void *pixels, int format, int width, int height);
int FUN_001e8d10(int x, int y, int w, int h);
int FUN_001e99c0(int mode);
int FUN_001e99f0(int mask, int a, int b);
int FUN_001ea420(int handle);
int FUN_001ea430(int a, int b, int c, int d);
int FUN_001ea8a0(int handle);
int FUN_001edf20();
int FUN_001f05a0(int a, int b);
void FUN_00203580(void *source, int sourceFormat, int width, int height, int layout, void *pixels, int flags);
void FUN_00203c50(void *source, int sourceFormat, int width, int height, int layout, void *pixels, int flags);
void FUN_002094c0(int a, int b);
void FUN_00209cf0(int a, int b, int c, int d, int e, int f, int g);
void FUN_0020a590(int a, int b, int c, int d, int e, int f, int g, int h);
void FUN_0020a990(int a, int b, int c, int d, int e, int f, int g, int h);
int FUN_0020ad60(...);
int FUN_0020b110(int, int, int);
int FUN_0020b270(int handle);
int FUN_0020bb20(int *handle, int a, int b);
int FUN_0020c800(int handle);
int FUN_0020c9f0(int handle);
int FUN_0020dba0(int, int, int, int, float, float);
int p2LoadTexture(int a, int b, int c, int d, int e);
int FUN_002eb010(int n);
int FUN_002ed5c0(void *p);
int StringPool_Construct(int pool);
int *StringPool_Intern(int pool, const void *s);
int StringChunk_ReleaseHeader(int a, int *header);
int thunk_FUN_003065f0(int a, int b, int *c, int *d, int e, int f);

int FUN_00169e40(VisualContextTextures *self, int index, TextureImage *image, void *source, int sourceFormat, int width, int height, int flags);
void FUN_0016a520(O520 *o);
void FUN_0016a800(S0 *arg0);
void FUN_0016a9f0(igPsx2VisualContext *arg0, int arg1);
void FUN_0016ab80(Oab80 *arg0, int arg1);
void FUN_0016aea0(int arg0, int arg1, int *arg2, int *arg3);
void FUN_0016b1d0(OB1d0 *arg0, int arg1);

extern int DAT_0048a4e0[4];
extern int DAT_0048a4ec[4];
extern int DAT_0048acd0[];
extern int DAT_004df370[4];
extern void *DAT_00586dc8[4];
extern int DAT_00586f20[4];

struct Ent46 { int f0; int f4; int f8; int f12; int f16; int f20; float f24; int f28; int f32; int f36; int f40; int f44; };
struct Pool46 { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; unsigned short *f12; Ent46 *f16; };
class Buf46 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual unsigned short *vB(unsigned short *p, int n); };
struct Src { int f0; int f4; int f8; int f12; int f16; int f20; int f24; float f28; };
struct Obj46 { char pad[868]; Pool46 *f868; int f872; };
int Gap__Gfx__igPsx2VisualContext__vfunc_46(Obj46 *arg0, Src *arg1) {
    Pool46 *p;
    Ent46 *e;
    int s0;
    int i;
    p = arg0->f868;
    if (p->f4 <= 0) {
        p->f16 = (Ent46 *)thunk_FUN_002ed3b0(p->f16, (p->f0 + 4) * 48, 16);
        memset(p->f16 + p->f0, 0, 192);
        if (p->f2 < 4) {
            Buf46 *b = (Buf46 *)Memory_FindBufferOwner(p);
            p->f12 = b->vB(p->f12, 8);
            p->f2 = 4;
        }
        i = 0;
        do {
            p->f12[i] = p->f0 + i;
            i++;
        } while (i < 4);
        p->f4 = 4;
        p->f0 = p->f0 + 4;
    }
    s0 = p->f12[p->f4 - 1];
    p->f4 = p->f4 - 1;
    e = arg0->f868->f16 + s0;
    e->f28 = arg1->f0;
    e->f0 = arg1->f4;
    e->f4 = arg1->f8;
    e->f8 = arg1->f12;
    e->f16 = arg1->f16;
    e->f12 = arg1->f20;
    e->f20 = arg1->f24;
    e->f24 = arg1->f28;
    e->f40 = 0;
    e->f44 = 0;
    e->f36 = -1;
    arg0->f872 = s0;
    return s0;
}

class DW4VC_524 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void vX(int, void *); };
class DW4VC_232 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void *vX(void *, int); };
struct Ent47 { char pad[36]; int f36; char pad2[8]; };
struct Tb { char pad[16]; Ent47 *f16; };
struct Ar { unsigned short n; unsigned short cap; unsigned short cnt; char pad[6]; void *f12; Ent47 *f16; };
void Gap__Gfx__igPsx2VisualContext__vfunc_47(igPsx2VisualContext *arg0, int arg1) {
    int temp_a1;
    Ar *temp_s0;
    Ar *temp_a2;
    DW4VC_232 *temp_v0;

    temp_a2 = (Ar *)arg0->_pBufList;
    temp_a1 = *(int *)((char *)temp_a2->f16 + arg1 * 0x30 + 36);
    if (-1 < temp_a1) {
        ((DW4VC_524 *)arg0)->vX(temp_a1, temp_a2);
    }
    temp_s0 = (Ar *)arg0->_pBufList;
    if ((arg1 < temp_s0->n) && (arg1 >= 0)) {
        if (temp_s0->cnt >= temp_s0->cap) {
            temp_v0 = (DW4VC_232 *)Memory_FindBufferOwner(temp_s0);
            temp_s0->cap = temp_s0->cap + 8;
            temp_s0->f12 = temp_v0->vX(temp_s0->f12, temp_s0->cap * 2);
        }
        ((short *)temp_s0->f12)[temp_s0->cnt] = arg1;
        temp_s0->cnt = temp_s0->cnt + 1;
    }
}

struct I { int w; int h; int p8; int f12; int p16[3]; int f28; int p32[2]; int f40; int f44; };
struct L48 { char pad[16]; I *f16; };
class V { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215(); virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223(); virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); 
virtual void vX(int);
char pad[864]; L48 *f868; int f872; char pad2[40]; int f916; int f920; int f924; int f928; float f932; float f936; };
void Gap__Gfx__igPsx2VisualContext__vfunc_48(V *arg0, int arg1) {
    I *base;
    I *s0;
    I *cur;
    int t;
    base = arg0->f868->f16;
    s0 = base + arg1;
    cur = base + arg0->f872;
    t = s0->f28;
    if (t != 2 && cur->f28 == 2) {
        FUN_0020b110(t, arg1 * 0x30, (int)base);
        FUN_0020dba0(arg0->f916, arg0->f920, arg0->f924, arg0->f928, 1.0f - arg0->f932, 1.0f - arg0->f936);
    } else if (t == 2) {
        FUN_0020ad60(s0->f40, s0->f44, (int)base);
        FUN_0020dba0(0, 0, s0->w, s0->h, 1.0f - arg0->f932, 1.0f - arg0->f936);
    }
    arg0->f872 = arg1;
    FUN_0016a520((O520 *)arg0);
    if (s0->f12 <= 0) {
        arg0->vX(0);
        return;
    }
    arg0->vX(1);
}

struct Buf49 { int width; int height; int format; int depthFormat; int f16; int p20[4]; int texIndex; int colorTex; int depthTex; };
struct BufList49 { char pad[16]; Buf49 *records; };
struct Tex49 { char pad[72]; int *handle; int depthHandle; char pad80[52]; int state; };
struct TexList49 { char pad[16]; Tex49 *records; };
class VC49 { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
virtual void releaseTexture(int); virtual void freeTexture(int);
virtual void e130(); virtual void e131(); virtual void e132(); virtual void e133(); virtual void e134(); virtual void e135(); virtual void e136(); virtual void e137(); virtual void e138(); virtual void e139(); virtual void e140(); virtual void e141(); virtual void e142(); virtual void e143(); virtual void e144(); virtual void e145(); virtual void e146(); virtual void e147(); virtual void e148(); virtual void e149(); virtual void e150(); virtual void e151(); virtual void e152(); virtual void e153(); virtual void e154(); virtual void e155(); virtual void e156(); virtual void e157(); virtual void e158(); virtual void e159(); virtual void e160(); virtual void e161(); virtual void e162(); virtual void e163(); virtual void e164(); virtual void e165(); virtual void e166(); virtual void e167(); virtual void e168(); virtual void e169(); virtual void e170(); virtual void e171(); virtual void e172(); virtual void e173(); virtual void e174(); virtual void e175(); virtual void e176(); virtual void e177(); virtual void e178(); virtual void e179(); virtual void e180(); virtual void e181(); virtual void e182(); virtual void e183(); virtual void e184(); virtual void e185(); virtual void e186(); virtual void e187(); virtual void e188(); virtual void e189(); virtual void e190(); virtual void e191(); virtual void e192(); virtual void e193(); virtual void e194(); virtual void e195(); virtual void e196(); virtual void e197(); virtual void e198(); virtual void e199(); virtual void e200(); virtual void e201(); virtual void e202(); virtual void e203(); virtual void e204(); virtual void e205(); virtual void e206(); virtual void e207(); virtual void e208(); virtual void e209(); virtual void e210(); virtual void e211(); virtual void e212(); virtual void e213(); virtual void e214(); virtual void e215(); virtual void e216(); virtual void e217(); virtual void e218(); virtual void e219(); virtual void e220(); virtual void e221(); virtual void e222(); virtual void e223(); virtual void e224(); virtual void e225(); virtual void e226(); virtual void e227(); virtual void e228(); virtual void e229(); virtual void e230();
virtual void setDepth(int);
char pad[320]; TexList49 *texList; char pad328[540]; BufList49 *bufList; int currentBuf; char pad876[56]; float near; float far; };
void Gap__Gfx__igPsx2VisualContext__vfunc_49(VC49 *self, int bufferIndex, int *textureIndex) {
    int index;
    int format;
    bool create;
    Tex49 *tex;
    int colorFormat;
    Buf49 *buf;
    buf = &self->bufList->records[bufferIndex];
    tex = 0;
    index = *textureIndex;
    create = false;
    if (index == -1) {
        create = true;
    } else {
        tex = &self->texList->records[index];
        if (*tex->handle == 0) {
            create = true;
        }
    }
    if (create) {
        switch (buf->format) {
        case 16:
        case 15:
            colorFormat = 3;
            format = 8;
            break;
        case 24:
            if (buf->f16 == 0) {
                colorFormat = 1;
                format = 5;
            } else {
                colorFormat = 0;
                format = 7;
            }
            break;
        case 7:
        case 8:
        default:
            colorFormat = 0;
            format = 7;
            break;
        }
        if (index == -1) {
            *textureIndex = FUN_0017aa20(self, buf->width, buf->height, format, 3, 0, 1);
            buf->texIndex = *textureIndex;
            tex = &self->texList->records[*textureIndex];
        }
        if (buf->colorTex != 0) {
            self->releaseTexture(buf->texIndex);
        }
        if (buf->depthFormat > 0) {
            int depthFormat;
            switch (buf->depthFormat) {
            case 16:
            default:
                depthFormat = 12;
                break;
            case 24:
                depthFormat = 10;
                break;
            case 32:
                depthFormat = 9;
                break;
            }
            buf->depthTex = p2LoadTexture(0, buf->width, buf->height, depthFormat, 0);
        }
        buf->colorTex = p2LoadTexture(0, buf->width, buf->height, colorFormat, 0);
        if (buf->colorTex != 0) {
            *tex->handle = buf->colorTex;
            tex->depthHandle = buf->depthTex;
            tex->state = 2;
        } else {
            self->freeTexture(*textureIndex);
            *textureIndex = -1;
            return;
        }
    }
    FUN_0020ad60(buf->colorTex, buf->depthTex);
    self->currentBuf = bufferIndex;
    FUN_0020dba0(0, 0, buf->width, buf->height, 1.0f - self->near, 1.0f - self->far);
    FUN_0016a520((O520 *)self);
    if (buf->depthFormat <= 0) {
        self->setDepth(0);
        return;
    }
    self->setDepth(1);
}

/* Read the first two fields of VRAM buffer record `bufferIndex` (0x30-byte records at _pBufList +
 * 0x10) into *word0 and *word1; vfunc_52 is the matching setter. */
void Gap__Gfx__igPsx2VisualContext__vfunc_53(igPsx2VisualContext *self, int bufferIndex, int *word0, int *word1) {
    int recordOffset;

    recordOffset = bufferIndex * 0x30;
    *word0 = *(int *)(*(int *)((char *)(self->_pBufList) + 16) + recordOffset);
    *word1 = *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + recordOffset)) + 4);
}

/* Store two words into the first two fields of VRAM buffer record `bufferIndex`. _pBufList
 * (+0x364) holds the 0x30-byte VRAM buffer records at +0x10; vfunc_53 is the matching getter. */
int Gap__Gfx__igPsx2VisualContext__vfunc_52(igPsx2VisualContext *self, int bufferIndex, int word0, int word1) {
    int recordOffset;

    recordOffset = bufferIndex * 0x30;
    *(int *)(*(int *)((char *)(self->_pBufList) + 16) + recordOffset) = word0;
    *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + recordOffset)) + 4) = word1;
    return 1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_50(int *p)
{
    return *(int *)((char *)p + 872);
}

/* Getter for the record field at +0x1c of buffer `bufferIndex`. `_pBufList` (+0x364) is an
 * igDataList whose data pointer (+0x10) addresses 0x30-byte VRAM buffer records. */
#define BUFFER_RECORD_SIZE 0x30  /* bytes per _pBufList record */
int Gap__Gfx__igPsx2VisualContext__vfunc_51(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 28);
}

void FUN_00169be0(void *d0, int arg1) {
    if (arg1 == 1) {
        FUN_001e99c0(0x40);
        return;
    }
    FUN_001e99c0(0);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_176(void *arg0, int arg1) {
    int var_a0;

    var_a0 = 0;
    if (arg1 & 1) {
        var_a0 |= 1;
    }
    if (arg1 & 2) {
        var_a0 |= 2;
    }
    FUN_001e99f0(var_a0, *(int *)((char *)(arg0) + 896), *(int *)((char *)(arg0) + 900));
}

int Gap__Gfx__igPsx2VisualContext__vfunc_171(igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8) {
    int temp_a1;
    int temp_a2;
    int temp_v1;
    char *temp_a3;
    char *temp_s0;
    char *temp_s7;

    temp_a2 = (arg1 * 3) << 4;
    temp_a3 = (char *)arg0->_pBufList;
    temp_a1 = *(int *)(temp_a3 + 16);
    temp_s7 = (char *)(temp_a1 + temp_a2);
    temp_s0 = (char *)(*(int *)((char *)arg0->_pTexList + 16) + (arg2 * 0x88));
    if (**(int **)(temp_s0 + 72) == 0) {
        **(int **)(temp_s0 + 72) = p2LoadTexture(0, *(int *)(temp_s0 + 32), *(int *)(temp_s0 + 36), FUN_0017a2b0(*(int *)(temp_s0 + 0)), 0);
    }
    if ((arg7 == -1) || (arg8 == -1)) {
        if (arg0->_textureStateFilter != 0) {
            temp_v1 = (arg0->_textureMagFilter << 0x10) | arg0->_textureMinFilter;
            if (arg0->_currentTextureFilter[0] != temp_v1) {
                arg0->_currentTextureFilter[0] = temp_v1;
                FUN_002094c0(DAT_0048acd0[arg0->_textureMagFilter], DAT_0048acd0[arg0->_textureMinFilter]);
            }
        }
        FUN_00209cf0(*(int *)(temp_s7 + 40), **(int **)(temp_s0 + 72), arg3, arg4, arg5, arg6, 0);
    } else if (*(int *)(temp_s7 + 28) == 2) {
        FUN_0020a990(*(int *)(temp_s7 + 40), arg3, arg4, **(int **)(temp_s0 + 72), arg7, arg8, arg5, arg6);
    } else {
        FUN_0020a590(**(int **)(temp_s0 + 72), arg3, arg4, arg7, arg8, arg5, arg6, 0);
    }
    *(int *)(temp_s0 + 132) = 3;
    return 1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_172(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    FUN_00169e40((VisualContextTextures *)arg0, arg1, (TextureImage *)arg2, (void *)arg3, arg4, arg5, arg6, 0);
}

class TextureImage {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void setPixels(void *pixels, int format, int quality, int width, int height);
    char pad4[44];
    int f48;
    void *pixels;
};

class BufferAllocator {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void *allocate(int size, int align);
};

struct TextureEntry { char pad0[8]; int depth; int pad12; int indexed; char pad20[8]; int kind; char pad32[4]; int palette; int layout; char pad44[4]; };
struct TextureTable { char pad0[16]; TextureEntry *entries; };
struct PaletteEntry { int format; char pad4[132]; };
struct PaletteTable { char pad0[16]; PaletteEntry *entries; };
struct VisualContextTextures { char pad0[324]; PaletteTable *palettes; char pad328[540]; TextureTable *textures; };
/* matching construct: a small sweep of spellings */
int FUN_00169e40(VisualContextTextures *self, int index, TextureImage *image, void *source, int sourceFormat, int width, int height, int flags) {
    void *pixels;
    TextureEntry *entry;
    entry = &self->textures->entries[index];
    pixels = image->pixels;
    bool allocated = false;
    int format;
    if (pixels == 0 || image->f48 < 0 || ((int)pixels & 15) != 0) {
        pixels = ((BufferAllocator *)FUN_00165cf0(self))->allocate(width * height * 4, 16);
        allocated = true;
    }
    if (entry->kind == 2) {
        FUN_00203c50(source, sourceFormat, width, height, entry->layout, pixels, flags);
        format = self->palettes->entries[entry->palette].format;
    } else {
        FUN_00203580(source, sourceFormat, width, height, 1, pixels, flags);
        if (entry->depth == 32) {
            format = 7;
        } else if (entry->depth == 24) {
            if (entry->indexed) {
                format = 7;
            } else {
                format = 5;
            }
        } else if (entry->depth == 15 || entry->depth == 16) {
            format = 8;
        } else {
            format = 7;
        }
    }
    if (allocated) {
        image->setPixels(pixels, format, 100, width, height);
        Memory_FreeBuffer(pixels);
    } else {
        FUN_0015a530(image, pixels, format, width, height);
    }
    return 1;
}

struct S185 { char pad0[104]; int f104; char pad6C[808]; int f916; int f920; int f924; int f928; float f932; float f936; };

void Gap__Gfx__igPsx2VisualContext__vfunc_185(struct S185 *arg0, int arg1, int arg2, int arg3, int arg4, float fparg0, float fparg1) {
    arg0->f916 = arg1;
    arg0->f920 = arg2;
    arg0->f924 = arg3;
    arg0->f928 = arg4;
    arg0->f932 = fparg0;
    arg0->f936 = fparg1;
    if (arg0->f104 == 0) {
        FUN_0016a520((O520 *)arg0);
    }
    FUN_0020dba0(arg1, arg2, arg3, arg4, 1.0f - arg0->f932, 1.0f - arg0->f936);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_186(void *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = *(int *)((char *)(arg0) + 916);
    *arg2 = *(int *)((char *)(arg0) + 920);
    *arg3 = *(int *)((char *)(arg0) + 924);
    *arg4 = *(int *)((char *)(arg0) + 928);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_187(igPsx2VisualContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4, float *arg5, float *arg6) {
    *arg1 = arg0->_iViewportX;
    *arg2 = arg0->_iViewportY;
    *arg3 = arg0->_iViewportW;
    *arg4 = arg0->_iViewportH;
    *arg5 = arg0->_viewportNear;
    *arg6 = arg0->_viewportFar;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_177(igPsx2VisualContext *self, float *color) {
    self->_clearColor[0] = color[0];
    self->_clearColor[1] = color[1];
    self->_clearColor[2] = color[2];
    self->_clearColor[3] = color[3];
    int green = (unsigned int)(255.0f * self->_clearColor[1]) << 8;
    self->_uiClearColor = ((unsigned int)(255.0f * ((128.0f * self->_clearColor[3]) / 255.0f)) << 24)
        + (((unsigned int)(255.0f * self->_clearColor[2]) << 16) + ((unsigned int)(255.0f * self->_clearColor[0]) + green));
}

void Gap__Gfx__igPsx2VisualContext__vfunc_178(int *a, unsigned int x) {
    a[224] = (x & 0xffffff) | (((x >> 1) & 0x7f000000) + (x & 0x01000000));
}

int Gap__Gfx__igPsx2VisualContext__vfunc_180(void *arg0) {
    int temp_a1;
    unsigned int temp_a0;

    temp_a1 = *(int *)((char *)(arg0) + 896);
    temp_a0 = (unsigned int)(temp_a1 & 0x80000000) >> 7;
    return (temp_a1 & 0xFFFFFF) | (temp_a0 + (((temp_a1 & 0xFF000000) - temp_a0) * 2));
}

typedef struct Obj179 { char pad[896]; int f896; } Obj179;

void Gap__Gfx__igPsx2VisualContext__vfunc_179(Obj179 *arg0, void *arg1) {
    FUN_00193540(arg1, 1, arg0->f896);
}

typedef struct S181 { char pad[892]; float f892; char pad896[4]; unsigned f900; char pad904[376]; unsigned f1280; } S181;

void Gap__Gfx__igPsx2VisualContext__vfunc_181(S181 *arg0, float fparg0) {
    arg0->f892 = fparg0;
    if (arg0->f1280 & 4) {
        arg0->f900 = (unsigned)(2.1474836e9f * arg0->f892);
        return;
    }
    arg0->f900 = (unsigned)(2.1474836e9f * (1.0f - arg0->f892));
}

float Gap__Gfx__igPsx2VisualContext__vfunc_182(void *arg0) {
    return *(float *)((char *)arg0 + 892);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_183(int a0, int a1)
{
    *(int *)((char *)a0 + 904) = a1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_184(void *arg0) {
    return *(int *)((char *)(arg0) + 904);
}

/* Getter for the record field at +0x8 of buffer `bufferIndex`: the buffer format
 * (8/7/0x18/0xf/0x10). `_pBufList` (+0x364) is an igDataList whose data pointer
 * (+0x10) addresses 0x30-byte VRAM buffer records. */
int Gap__Gfx__igPsx2VisualContext__vfunc_54(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 8);
}

/* Getter for the record field at +0x10 of buffer `bufferIndex`. `_pBufList` (+0x364) is an
 * igDataList whose data pointer (+0x10) addresses 0x30-byte VRAM buffer records. */
int Gap__Gfx__igPsx2VisualContext__vfunc_55(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 16);
}

/* Getter for the record field at +0xc of buffer `bufferIndex`: the secondary format (0x20/0x18 in
 *. `_pBufList` (+0x364) is an igDataList whose data pointer (+0x10) addresses
 * 0x30-byte VRAM buffer records. */
int Gap__Gfx__igPsx2VisualContext__vfunc_56(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 12);
}

/* igPsx2VisualContext vtable slot 57: reads the word at +20 of one VRAM buffer record. _pBufList
 * is the context's table of 0x30-byte buffer records whose element array is at +16 (texture
 * capture). */
#define VRAM_BUFFER_RECORD_SIZE 0x30
int Gap__Gfx__igPsx2VisualContext__vfunc_57(igPsx2VisualContext *self, int buffer_index) {
    return *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + (buffer_index * VRAM_BUFFER_RECORD_SIZE))) + 20);
}

/* igPsx2VisualContext vtable slot 58: reads the float at +24 of one VRAM buffer record (companion
 * of slot 57, which reads the word at +20). _pBufList is the context's table of 0x30-byte buffer
 * records whose element array is at +16 (texture capture). */
float Gap__Gfx__igPsx2VisualContext__vfunc_58(igPsx2VisualContext *self, int buffer_index) {
    return *(float *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + (buffer_index * VRAM_BUFFER_RECORD_SIZE))) + 24);
}

typedef struct R520 { int x; int y; } R520;
typedef struct L520 { char pad[16]; R520 *rects; } L520;
typedef struct O520 {
    char p0[104]; int f68; char p1[760]; L520 *l364; int idx;
    char p2[40]; int e394; int e398; int e39c; int e3a0;
    char p3[304]; int e4d4; int e4d8; int e4dc; int e4e0;
} O520;
#define MIN(a,b) ((a) < (b) ? (a) : (b))
struct H {
static inline int clampLen(int lim, int diff) {
    if (MIN(lim, diff) > 1) return MIN(lim, diff);
    return 1;
}
static inline int clampLow(int lim, int diff) {
    if (MIN(lim, diff) > 0) return MIN(lim, diff);
    return 0;
}
};
void FUN_0016a520(O520 *o) {
    R520 *r = (R520 *)((char *)o->l364->rects + o->idx * 0x30);
    if (r != 0) {
        if (o->f68 == 0) {
            int a = o->e398; int hi_y = r->y; int c = o->e3a0;
            c = H::clampLen(c, hi_y - a);
            { int lo_x = o->e394; int hi_x = r->x; int w = o->e39c;
              w = H::clampLen(w, hi_x - lo_x);
              a = H::clampLow(a, hi_y);
              lo_x = H::clampLow(lo_x, hi_x);
              FUN_001e8d10(lo_x, a, w, c); }
        } else {
            int a = o->e4d8; int hi_y = r->y; int c = o->e4e0;
            c = H::clampLen(c, hi_y - a);
            { int lo_x = o->e4d4; int hi_x = r->x; int w = o->e4dc;
              w = H::clampLen(w, hi_x - lo_x);
              a = H::clampLow(a, hi_y);
              lo_x = H::clampLow(lo_x, hi_x);
              FUN_001e8d10(lo_x, a, w, c); }
        }
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_188(igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4) {
    int temp_a1;

    arg0->_scissorX = arg1;
    arg0->_scissorY = arg2;
    arg0->_scissorW = arg3;
    arg0->_scissorH = arg4;
    temp_a1 = arg0->_scissorType;
    if (temp_a1 == 1) {
        FUN_0016a520((O520 *)arg0);
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_189(void *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = *(int *)((char *)(arg0) + 1236);
    *arg2 = *(int *)((char *)(arg0) + 1240);
    *arg3 = *(int *)((char *)(arg0) + 1244);
    *arg4 = *(int *)((char *)(arg0) + 1248);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_190(int a0, int a1) {
    *(int *)((char *)a0 + 104) = (int)a1;
    FUN_0016a520((O520 *)a0);
}

typedef struct S0 { char pad4[4]; int f4; int f8; char pad20[8]; int f14; } S0;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;

void FUN_0016a800(S0 *arg0) {
    S_temp_a0 *temp_a0;
    temp_a0 = (S_temp_a0 *)(arg0->f4);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f4 = 0;
    arg0->f8 = 0;
    arg0->f14 = 0;
}

struct P { unsigned short f0; unsigned short f2; unsigned short f4; char p6[2]; int *f8; short *f12; int f16; };
class Buf860 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual short *vB(int n, int sz); virtual int vA(int n, int sz, int al); };
struct Arg { char pad[328]; P *f328; char pad2[12]; int f344; };
void FUN_0016a860(Arg *arg0) {
    int sp5C;
    int i;
    P *p;
    int n;
    int v;
    int *old;
    int *s3;
    Buf860 *b;
    sp5C = 64;
    thunk_FUN_003065f0(*(int *)((char *)(DAT_00586dc8[0]) + 56), 4, &DAT_004df370[0], &sp5C, 64, 0);
    p = (P *)Memory_AllocateBufferDirect(20, FUN_00165d10(arg0));
    if (p != 0) {
        n = sp5C;
        p->f8 = 0;
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s3 = StringPool_Intern(DAT_00586f20[0], &DAT_004df370[0]);
        old = p->f8;
        if (old != 0) {
            int *a1 = old - 2;
            int v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        p->f8 = s3;
        if (n == 0) {
            n = 1;
        }
        b = (Buf860 *)Memory_FindBufferOwner(p);
        p->f16 = b->vA(n, 24, 16);
        p->f12 = b->vB(n, 2);
        i = 0;
        p->f2 = n;
        p->f0 = n;
        p->f4 = n;
        while (i < n) {
            p->f12[i] = i;
            i = i + 1;
        }
    }
    arg0->f328 = p;
    arg0->f344 = -1;
}

struct T9f0 { unsigned short f0; short pad; unsigned short f4; short pad2; int f8; unsigned short *f12; int f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
void FUN_0016a9f0(igPsx2VisualContext *arg0, int arg1) {
    int s0, s2, v, old;
    int *hd;
    T9f0 *t;
    s0 = ((T9f0 *)arg0->_pClutList)->f0 - 1;
    for (; s0 > -1; s0--) {
        if (((T9f0 *)arg0->_pClutList)->Chk(s0)) {
            FUN_0016ab80((Oab80 *)arg0, s0);
        }
    }
    if (arg1 == 0) {
        t = (T9f0 *)arg0->_pClutList;
        if (t != 0) {
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(16);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20[0] = v;
            }
            s2 = (int)StringPool_Intern(DAT_00586f20[0], 0);
            old = t->f8;
            if (old != 0) {
                hd = (int *)(old - 8);
                v = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader(*hd, hd);
                }
            }
            t->f8 = s2;
            Memory_FreeBuffer(t->f16);
            Memory_FreeBuffer((int)t->f12);
            if (&t->f8 != 0) {
                old = t->f8;
                if (old != 0) {
                    hd = (int *)(old - 8);
                    v = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = v;
                    if (v == 0) {
                        StringChunk_ReleaseHeader(*hd, hd);
                    }
                }
            }
            FUN_002ed5c0(t);
        }
        arg0->_pClutList = 0;
    }
}

struct RC { int p0; unsigned refs; };
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();  virtual void *v58(void *, int); };
struct E { int p0; RC *f4; int f8; int p12; int f16; int p20; };
struct Tab80 { unsigned short f0; unsigned short f2; unsigned short f4; short pad2; int f8; unsigned short *f12; E *f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
struct Oab80 { int w[82]; Tab80 *f328; };
void FUN_0016ab80(Oab80 *arg0, int arg1) {
    Tab80 *t;
    E *e;
    RC *r;
    t = arg0->f328;
    if (t->Chk(arg1)) {
        e = (E *)((char *)t->f16 + arg1 * 24);
        if (e->f8 != 0) {
            FUN_0016b1d0((OB1d0 *)arg0, arg1);
        }
        r = e->f4;
        if (r != 0) {
            --r->refs;
            if (!(r->refs & 0x7fffff)) igObject_Destroy(r);
        }
        e->f4 = 0;
        if (e->f16 != 0) {
            Memory_FreeBuffer(e->f16);
        }
        t = arg0->f328;
        if (arg1 < t->f0 && arg1 >= 0) {
            if (t->f4 >= t->f2) {
                VO *ow = (VO *)Memory_FindBufferOwner(t);
                t->f2 = t->f2 + 8;
                t->f12 = (unsigned short *)ow->v58(t->f12, t->f2 * 2);
            }
            t->f12[t->f4] = arg1;
            t->f4 = t->f4 + 1;
        }
    }
}

struct EntAd20 { int f0; int f4; int f8; int f12; int f16; int f20; };
struct PoolAd20 { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; unsigned short *f12; EntAd20 *f16; };
struct ObjAd20 { char pad[328]; PoolAd20 *f328; };
int FUN_0016ad20(ObjAd20 *arg0, int arg1, int arg2) {
    PoolAd20 *p;
    EntAd20 *e;
    int s0;
    int i;
    if (arg1 > 256) {
        return -1;
    }
    p = arg0->f328;
    if (p->f4 <= 0) {
        p->f16 = (EntAd20 *)thunk_FUN_002ed3b0(p->f16, (p->f0 + 4) * 24, 16);
        memset(p->f16 + p->f0, 0, 96);
        if (p->f2 < 4) {
            Buf46 *b = (Buf46 *)Memory_FindBufferOwner(p);
            p->f12 = b->vB(p->f12, 8);
            p->f2 = 4;
        }
        i = 0;
        do {
            p->f12[i] = p->f0 + i;
            i++;
        } while (i < 4);
        p->f4 = 4;
        p->f0 = p->f0 + 4;
    }
    s0 = p->f12[p->f4 - 1];
    p->f4 = p->f4 - 1;
    e = arg0->f328->f16 + s0;
    FUN_0016a800((S0 *)e);
    e->f20 = 0;
    e->f12 = arg2;
    e->f0 = arg1;
    e->f16 = 0;
    return s0;
}

void FUN_0016aea0(int arg0, int arg1, int *arg2, int *arg3) {
    int *var_a2;
    int *var_a3;
    int temp_v1;
    int var_a1;
    int var_a1_2;

    var_a2 = arg2;
    var_a3 = arg3;
    switch (arg1) {
    case 0:
        var_a1 = 0;
        do {
            var_a1 += 1;
            *var_a2 = *var_a3;
            var_a3 += 1;
            var_a2 += 1;
        } while (var_a1 < 0x10);
        return;
    case 1:
        var_a1_2 = 0;
        do {
            temp_v1 = (var_a1_2 & 0xE7) | (((var_a1_2 >> 1) & 8) | ((var_a1_2 & 8) * 2));
            var_a1_2 += 1;
            *var_a2 = *(var_a3 + temp_v1);
            var_a2 += 1;
        } while (var_a1_2 < 0x100);
        return;
    }
}

struct RAf30 { char pad[4]; int f4; char pad2[12]; int f14; char pad3[4]; unsigned char f1c; };
struct EntAf30 { int f0; RAf30 *f4; int f8; int fc; int f10; int f14; };
struct Tab { char pad[16]; EntAf30 *f10; };
struct A { char pad[328]; Tab *f148; char pad2[1136]; unsigned char f5bc; };
class VC_220 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52();  virtual int vX(int, int); };
void FUN_0016af30(A *arg0, int arg1, RAf30 *arg2) {
    EntAf30 *e;
    int n;
    RAf30 *t;
    void **o;
    e = &arg0->f148->f10[arg1];
    if (arg2 != 0) {
        arg2->f4 = arg2->f4 + 1;
    }
    t = e->f4;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    e->f4 = arg2;
    e->f14 = 0;
    n = 256;
    if (arg0->f5bc != 0 && e->f0 < 17) {
        e->fc = 0;
        n = 16;
    }
    if (e->f10 != 0 && e->f8 != 0) {
        FUN_001f05a0(2, FUN_0020b270(FUN_001ea420(e->f8)));
    } else if (e->f10 == 0) {
        o = (void **)FUN_00165cf0(arg0);
        e->f10 = ((VC_220 *)o)->vX(n * 4, 128);
    }
    if (e->f10 != 0) {
        arg2->f1c = 1;
        FUN_0016aea0((int)arg0, e->fc, (int *)e->f10, (int *)arg2->f14);
    }
}

typedef struct Q { char p[20]; int f20; char p2[4]; unsigned char f28; } Q;
typedef struct RB090 { int f0; Q *f4; int f8; int f12; int f16; int f20; } RB090;
typedef struct A1 { char p[16]; RB090 *f16; } A1;
typedef struct Ob { char p[328]; A1 *f328; } Ob;
bool FUN_0016b090(Ob *arg0, int arg1) {
    int sp5C;
    bool v;
    int h;
    int r;
    RB090 *s;
    Q *q;
    s = arg0->f328->f16 + arg1;
    v = true;
    if (s->f8 == 0 || s->f4->f28 != 0) {
        if (s->f8 != 0) {
            h = FUN_001ea420(s->f8);
            FUN_0020c800(h);
            FUN_001f05a0(2, FUN_0020b270(h));
            q = s->f4;
            q->f28 = 1;
            FUN_0016aea0((int)arg0, s->f12, (int *)s->f16, (int *)q->f20);
        } else {
            s->f8 = FUN_001ea430(DAT_0048a4e0[s->f12], 0, DAT_0048a4ec[0], s->f16);
        }
        s->f4->f28 = 0;
    }
    if (s->f20 != 5) {
        sp5C = FUN_001ea420(s->f8);
        v = FUN_0020bb20(&sp5C, 0, 0) != 0;
    }
    s->f20 = 4;
    return v;
}

struct E8 { int p0; int p4; int w8; int p12[3]; };
struct TB1d0 { unsigned short f0; short pad; unsigned short f4; short pad2; int f8; unsigned short *f12; E8 *f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
struct OB1d0 { int w[82]; TB1d0 *f328; int p332[3]; int f344; };
void FUN_0016b1d0(OB1d0 *arg0, int arg1) {
    TB1d0 *t;
    int h;
    E8 *e;
    t = arg0->f328;
    if (t->Chk(arg1)) {
        e = t->f16 + arg1;
        if (e->w8 != 0) {
            h = FUN_001ea420(e->w8);
            FUN_001f05a0(2, FUN_0020b270(h));
            FUN_0020c9f0(h);
            FUN_001ea8a0(e->w8);
        }
        e->w8 = 0;
        arg0->f344 = -1;
    }
}

/* J-thunk for igVisualContextCapabilityManager virtual slot 31, forwarding to the slot body. The
 * callee takes the caller's registers untouched, so the thunk has no arguments of its own. */

void thunk_FUN_00164f50(void) {
    FUN_00164f50();
}

typedef struct { char pad0[80]; int f50; char pad84[238]; unsigned char f142; } S10;

void Gap__Gfx__igPsx2VisualContext__vfunc_10(S10 *arg0) {
    int temp_a0;

    temp_a0 = arg0->f50;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        arg0->f50 = 0;
    }
    FUN_00169260(arg0, 0);
    FUN_0017a540(arg0, 0);
    FUN_0016a9f0((igPsx2VisualContext *)arg0, 0);
    FUN_00170510(arg0, 0);
    FUN_0016c650(arg0, 0);
    FUN_001788e0(arg0, 0);
    if (arg0->f142 != 0) {
        FUN_001edf20();
    }
    FUN_00165bb0(arg0);
}

struct T35 { int word0; int references; };
struct Obj35 {
    char p[940]; T35 *m940; T35 *m944; T35 *m948;
    inline void rel(T35 *&r) {
        T35 *object = r;
        if (object) {
            --object->references;
            if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
        r = 0;
    }
};
void Gap__Gfx__igPsx2VisualContext__vfunc_35(Obj35 *arg0) {
    FUN_00165cb0(arg0);
    arg0->rel(arg0->m940);
    arg0->rel(arg0->m944);
    arg0->rel(arg0->m948);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_37(igPsx2VisualContext *context, unsigned int query) {
    switch (query) {
    case 0:
        return 640;
    case 1:
        return 448;
    case 2:
        return 24;
    case 3:
        return 8;
    case 4:
        return 32;
    case 5:
        return 0;
    case 6:
        return 0;
    case 8:
        return 1;
    case 22:
        return context->_maxStageNum;
    case 7:
        return 1024;
    case 9:
        return 8;
    case 10:
        return 1;
    case 11:
        return 0;
    case 12:
        return 1;
    case 13:
        return 4;
    case 14:
        return 0;
    case 15:
        return 0;
    case 16:
        return 0;
    case 17:
        return 0;
    case 23:
        return 1;
    case 21:
        return 0;
    case 28:
    default:
        return 0;
    }
}

}

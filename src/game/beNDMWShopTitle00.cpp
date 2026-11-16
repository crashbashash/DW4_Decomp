#include "dw4/reflected.h"
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool[0] == 0) { \
            void *pool = StringPool_Allocate(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool[0] = pool; \
        } \
        tok = StringPool_Intern(g_stringPool[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }

extern "C" int beNDMWWindow_PresentModelAtOrigin(...);
extern "C" void beNDMWShopTitle00_Setup(beNDMWShopTitle00 *self);
extern "C" void *StringPool_Allocate(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" int beNDMWWindow_RunMessageScript(void *, int *, int);
extern "C" void beNDMWShopTitle03_Setup(int p0, char * p1, int p2, char * p3, char * p4);
extern "C" int beNDMWShopTitle03_GetMeta(void);
extern "C" int beNDMWShopTitle01_GetMeta(void);
extern "C" int beNDMWShopTitle00_GetMeta(void);
extern "C" int text_j_shback[4];
extern "C" int SQ_OPEN_10[4];
extern "C" int SQ_CLOSE_12[4];
extern "C" int text_i_bgclear[4];
extern "C" int text_i_sttitle[4];
extern "C" int STWINFONT12_3[4];
extern "C" int text_font000[4];
extern "C" int text_txt_shop_lua[4];
extern "C" void *g_stringPool[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
extern "C" void beNDMWShopTitle01_Setup(beNDMWShopTitle01 *self);
extern "C" char text_i_messwn[];
extern "C" int g_beNDMWShopTitle03_metaObject[4];
extern "C" int g_beNDMWShopTitle01_metaObject[4];
extern "C" int g_beNDMWShopTitle00_metaObject[4];

void beNDMWShopTitle00_Setup(beNDMWShopTitle00 *self) {
    beNDMWWindow_PresentModelAtOrigin(self, &text_j_shback[0], 0, &SQ_OPEN_10[0], &SQ_CLOSE_12[0]);
    beNDMWWindow_PresentModelAtOrigin(self, &text_i_bgclear[0], 0, &SQ_OPEN_10[0], &SQ_CLOSE_12[0]);
}

void beNDMWShopTitle01_Setup(beNDMWShopTitle01 *self) {
    int s;
    beNDMWWindow_PresentModelAtOrigin(self, text_i_sttitle, 0, SQ_OPEN_10, SQ_CLOSE_12);
    switch (self->_entCode) {
    case 1: s = 1100; break;
    case 2: s = 1200; break;
    case 3: s = 1300; break;
    case 4: s = 1400; break;
    case 5: s = 1500; break;
    case 6: s = 1600; break;
    case 7: s = 1700; break;
    case 8: s = 1800; break;
    case 9: s = 1900; break;
    case 10: s = 2000; break;
    }
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT12_3)
    INTERN_APPEND(self->_textCloseNameList, text_font000)
    beNDMWWindow_RunMessageScript(self, text_txt_shop_lua, s);
}

void beNDMWShopTitle03_Setup(int p0, char * p1, int p2, char * p3, char * p4)
{
    beNDMWWindow_PresentModelAtOrigin(p0, text_i_messwn, 0, ((char *)SQ_OPEN_10), ((char *)SQ_CLOSE_12));
}

int beNDMWShopTitle03_GetMeta(void)
{
    return g_beNDMWShopTitle03_metaObject[0];
}

int beNDMWShopTitle01_GetMeta(void)
{
    return g_beNDMWShopTitle01_metaObject[0];
}

int beNDMWShopTitle00_GetMeta(void)
{
    return g_beNDMWShopTitle00_metaObject[0];
}


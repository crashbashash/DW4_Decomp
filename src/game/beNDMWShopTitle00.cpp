#include "dw4/support/reflected.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/ndmw/beNDMWShopTitle00.h"
#include "dw4/game/ndmw/beNDMWShopTitle01.h"
#include "dw4/game/ndmw/beNDMWShopTitle03.h"
#include "dw4/game/ndmw/beNDMWWindow.h"
#include "dw4/support/list-services.h"
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool == 0) { \
            StringPool *pool = (StringPool *)StringPool_Allocate(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool = pool; \
        } \
        tok = StringPool_Intern(g_stringPool, (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained((igStringRefList *)(field), held.ref()); }

extern "C" void beNDMWShopTitle00_Setup(beNDMWShopTitle00 *self);
extern "C" void beNDMWShopTitle03_Setup(beNDMWShopTitle03 *self);
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
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    char *const *ref() const { return (char *const *)&p; }
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h); } }
};
extern "C" void beNDMWShopTitle01_Setup(beNDMWShopTitle01 *self);
extern "C" char text_i_messwn[];

void beNDMWShopTitle00_Setup(beNDMWShopTitle00 *self) {
    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, (const char *)text_j_shback, 0, (const char *)SQ_OPEN_10, (const char *)SQ_CLOSE_12);
    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, (const char *)text_i_bgclear, 0, (const char *)SQ_OPEN_10, (const char *)SQ_CLOSE_12);
}

void beNDMWShopTitle01_Setup(beNDMWShopTitle01 *self) {
    int s;
    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, (const char *)text_i_sttitle, 0, (const char *)SQ_OPEN_10, (const char *)SQ_CLOSE_12);
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
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, (const char *)text_txt_shop_lua, s);
}

void beNDMWShopTitle03_Setup(beNDMWShopTitle03 *self)
{
    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, text_i_messwn, 0, (const char *)SQ_OPEN_10, (const char *)SQ_CLOSE_12);
}

int beNDMWShopTitle03_GetMeta(void)
{
    return (int)g_beNDMWShopTitle03_metaObject;
}

int beNDMWShopTitle01_GetMeta(void)
{
    return (int)g_beNDMWShopTitle01_metaObject;
}

int beNDMWShopTitle00_GetMeta(void)
{
    return (int)g_beNDMWShopTitle00_metaObject;
}


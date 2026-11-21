#include "dw4/support/reflected.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/gfx/igVertexArrayLock.h"
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/game/beFont.h"
#include "dw4/game/beUnicodeObj.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beFontGeomAttrPair.h"
#include "dw4/game/beFontImage.h"
#include "dw4/game/beFontInfo.h"
#include "dw4/game/beMessenger.h"
#include "dw4/attrs/igColorAttr.h"
#include "dw4/core/igDataLists.h"
#include "dw4/attrs/igGeometryAttr.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igPlanarShadowShader.h"
#include "dw4/core/igStringObj.h"
#include "dw4/scenegraph/igSwitch.h"
#include "dw4/gfx/igVertexArray.h"
#include <string.h>
#pragma push
#pragma readonly_strings on

/* beFont's load state (beBaseInfoRam::_st0). */
enum beFontState {
    kFontStateInitialize = 0,
    kFontStateReady = 1,
    kFontStateFailed = 10000
};

/* The "Message" enum of beFont's messages. */
enum beFontMessage {
    kFontMessageInitialize = 0,
    kFontMessageTextSet = 1,
    kFontMessageAlign = 2,
    kFontMessageSwitch = 3,
    kFontMessageSetPosition = 4,
    kFontMessageColor = 5,
    kFontMessageDefaultColor = 6,
    kFontMessageCancelColor = 7,
    kFontMessageReplaceUnknown = 8
};

/* igObject laid out as igAttrSet (igGroup and igSwitch share the prefix up to _childList), seen
 * through its virtual functions: slot 30 is igColorAttr's colour setter.
 * ABI view only: never instantiated. */
class igNodeView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setColor(void *color);
    int _name;
    int _bound;
    igObjectList *_parentList;
    int _flags;
    int _handle;
    igObjectList *_childList;
    igObjectList *_attributes;
};

/* beFontImage's virtuals: slot 22 writes the glyph quads of a UTF-16 text into a vertex array, slot 23
 * returns the triangles one character draws (0 when the font has no glyph for it).
 * ABI view only: never instantiated. */
class beFontImageDispatchView : public igObjectDispatchView {
public:
    virtual void d21();
    virtual void buildVertices(igVertexArrayView *vertices, int text);
    virtual int countTriangles(int character);
};

/* igGeometryAttr's slot 37 sets the primitive type, primitive count and first index.
 * ABI view only: never instantiated. */
class igGeometryAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void d35(); virtual void d36();
    virtual void configure(int primType, int primCount, int offset);
};


/* One row of the Shift-JIS to UTF-16 table; a row of 0xffff ends it. */
struct SjisUnicodePair { unsigned short unicode; unsigned short sjis; };
struct SjisUnicodeTable { SjisUnicodePair entries[425]; };

/* _lineFeedList and _alignList with typed element arrays. */
struct UnsignedIntListView { char header[8]; int count; int capacity; int *data; int getCount() const { return count; } };
struct FloatListView { char header[8]; int count; int capacity; float *data; int getCount() const { return count; } };
union FloatBits { float f; struct { unsigned char b0, b1, b2; unsigned char high : 7; unsigned char sign : 1; } bits; };

#include "dw4/support/emptyString.h"
#include "dw4/support/list-services.h"
#include "dw4/maths/igVec4f.h"
extern "C" {
void beFont_Start(beFont *self);
void beFont_Stop(beFont *self);
void beFont_OnAddRam(beFont *self, int receiver);
igMetaObject *beFont_GetInfoMeta(void);
void beFont_UpdateRam(void);
int beFont_OnMessage(beFont *self, beBaseInfoRam *ram, beMessengerWork *work);
int beFont_FindFontIndex(beFont *self, int name);
void beFont_SetText(beFont *self, beBaseInfoRam *ram, igNodeView *text, int index);
void beFont_ReplaceVertexArray(beFont *self, igGeometryAttr *geometry, int fontIndex, int vertexCount);
void beFont_PrepareGeometry(beFont *self, igGeometryAttr *geometry, int text, int wide);
void beFont_LayoutLines(beFont *self, unsigned short *text, int entry, igVertexArrayLock *positions);
void beFont_AlignLines(beFont *self, int text, beFontInfoData *entry, igVertexArrayLock *positions);
void beFont_LockVertexArray(beFont *self, igVertexArrayView *vertices, igVertexArrayLock *positions, igVertexArrayLock *texCoords);
int beFont_FindFirstLayoutEntry(beFont *self, beBaseInfoRam *ram, int dataName, int setName);
int beFont_FindNextLayoutEntry(beFont *self, beBaseInfoRam *ram);
igMetaObject *beFont_GetMeta(void);
void beUnicodeObj_userDestruct(beUnicodeObj *self);
igMetaObject *beUnicodeObj_GetMeta(void);


SjisUnicodeTable g_sjisToUnicodeTable = {{
    {0x0020, 0x0020}, {0x3000, 0x8140}, {0x0030, 0x0030}, {0x0031, 0x0031},
    {0x0032, 0x0032}, {0x0033, 0x0033}, {0x0034, 0x0034}, {0x0035, 0x0035},
    {0x0036, 0x0036}, {0x0037, 0x0037}, {0x0038, 0x0038}, {0x0039, 0x0039},
    {0xff10, 0x824f}, {0xff11, 0x8250}, {0xff12, 0x8251}, {0xff13, 0x8252},
    {0xff14, 0x8253}, {0xff15, 0x8254}, {0xff16, 0x8255}, {0xff17, 0x8256},
    {0xff18, 0x8257}, {0xff19, 0x8258}, {0x0041, 0x0041}, {0x0042, 0x0042},
    {0x0043, 0x0043}, {0x0044, 0x0044}, {0x0045, 0x0045}, {0x0046, 0x0046},
    {0x0047, 0x0047}, {0x0048, 0x0048}, {0x0049, 0x0049}, {0x004a, 0x004a},
    {0x004b, 0x004b}, {0x004c, 0x004c}, {0x004d, 0x004d}, {0x004e, 0x004e},
    {0x004f, 0x004f}, {0x0050, 0x0050}, {0x0051, 0x0051}, {0x0052, 0x0052},
    {0x0053, 0x0053}, {0x0054, 0x0054}, {0x0055, 0x0055}, {0x0056, 0x0056},
    {0x0057, 0x0057}, {0x0058, 0x0058}, {0x0059, 0x0059}, {0x005a, 0x005a},
    {0xff21, 0x8260}, {0xff22, 0x8261}, {0xff23, 0x8262}, {0xff24, 0x8263},
    {0xff25, 0x8264}, {0xff26, 0x8265}, {0xff27, 0x8266}, {0xff28, 0x8267},
    {0xff29, 0x8268}, {0xff2a, 0x8269}, {0xff2b, 0x826a}, {0xff2c, 0x826b},
    {0xff2d, 0x826c}, {0xff2e, 0x826d}, {0xff2f, 0x826e}, {0xff30, 0x826f},
    {0xff31, 0x8270}, {0xff32, 0x8271}, {0xff33, 0x8272}, {0xff34, 0x8273},
    {0xff35, 0x8274}, {0xff36, 0x8275}, {0xff37, 0x8276}, {0xff38, 0x8277},
    {0xff39, 0x8278}, {0xff3a, 0x8279}, {0x0061, 0x0061}, {0x0062, 0x0062},
    {0x0063, 0x0063}, {0x0064, 0x0064}, {0x0065, 0x0065}, {0x0066, 0x0066},
    {0x0067, 0x0067}, {0x0068, 0x0068}, {0x0069, 0x0069}, {0x006a, 0x006a},
    {0x006b, 0x006b}, {0x006c, 0x006c}, {0x006d, 0x006d}, {0x006e, 0x006e},
    {0x006f, 0x006f}, {0x0070, 0x0070}, {0x0071, 0x0071}, {0x0072, 0x0072},
    {0x0073, 0x0073}, {0x0074, 0x0074}, {0x0075, 0x0075}, {0x0076, 0x0076},
    {0x0077, 0x0077}, {0x0078, 0x0078}, {0x0079, 0x0079}, {0x007a, 0x007a},
    {0xff41, 0x8281}, {0xff42, 0x8282}, {0xff43, 0x8283}, {0xff44, 0x8284},
    {0xff45, 0x8285}, {0xff46, 0x8286}, {0xff47, 0x8287}, {0xff48, 0x8288},
    {0xff49, 0x8289}, {0xff4a, 0x828a}, {0xff4b, 0x828b}, {0xff4c, 0x828c},
    {0xff4d, 0x828d}, {0xff4e, 0x828e}, {0xff4f, 0x828f}, {0xff50, 0x8290},
    {0xff51, 0x8291}, {0xff52, 0x8292}, {0xff53, 0x8293}, {0xff54, 0x8294},
    {0xff55, 0x8295}, {0xff56, 0x8296}, {0xff57, 0x8297}, {0xff58, 0x8298},
    {0xff59, 0x8299}, {0xff5a, 0x829a}, {0x0021, 0x0021}, {0x0022, 0x0022},
    {0x0028, 0x0028}, {0x0029, 0x0029}, {0x002b, 0x002b}, {0x002c, 0x002c},
    {0x002d, 0x002d}, {0x003a, 0x003a}, {0x0027, 0x0027}, {0x002e, 0x002e},
    {0x003c, 0x003c}, {0x003e, 0x003e}, {0x003f, 0x003f}, {0x005e, 0x005e},
    {0x005f, 0x005f}, {0x007c, 0x007c}, {0x3001, 0x8141}, {0x3002, 0x8142},
    {0xff0c, 0x8143}, {0x30fb, 0x8145}, {0xff1a, 0x8146}, {0xff1f, 0x8148},
    {0xff01, 0x8149}, {0xff3e, 0x814f}, {0xff3f, 0x8151}, {0x30fc, 0x815b},
    {0xff5e, 0x8160}, {0x2019, 0x8166}, {0xff0e, 0x8144}, {0xff5c, 0x8162},
    {0x2026, 0x8163}, {0x201d, 0x8168}, {0xff08, 0x8169}, {0xff09, 0x816a},
    {0x3008, 0x8171}, {0x3009, 0x8172}, {0x300c, 0x8175}, {0x300d, 0x8176},
    {0x300e, 0x8177}, {0x300f, 0x8178}, {0xff0b, 0x817b}, {0xff0d, 0x817c},
    {0x00d7, 0x817e}, {0x25cb, 0x819b}, {0x25a1, 0x81a0}, {0x25b3, 0x81a2},
    {0x3041, 0x829f}, {0x3042, 0x82a0}, {0x3043, 0x82a1}, {0x3044, 0x82a2},
    {0x3045, 0x82a3}, {0x3046, 0x82a4}, {0x3047, 0x82a5}, {0x3048, 0x82a6},
    {0x3049, 0x82a7}, {0x304a, 0x82a8}, {0x304b, 0x82a9}, {0x304c, 0x82aa},
    {0x304d, 0x82ab}, {0x304e, 0x82ac}, {0x304f, 0x82ad}, {0x3050, 0x82ae},
    {0x3051, 0x82af}, {0x3052, 0x82b0}, {0x3053, 0x82b1}, {0x3054, 0x82b2},
    {0x3055, 0x82b3}, {0x3056, 0x82b4}, {0x3057, 0x82b5}, {0x3058, 0x82b6},
    {0x3059, 0x82b7}, {0x305a, 0x82b8}, {0x305b, 0x82b9}, {0x305c, 0x82ba},
    {0x305d, 0x82bb}, {0x305e, 0x82bc}, {0x305f, 0x82bd}, {0x3060, 0x82be},
    {0x3061, 0x82bf}, {0x3062, 0x82c0}, {0x3063, 0x82c1}, {0x3064, 0x82c2},
    {0x3065, 0x82c3}, {0x3066, 0x82c4}, {0x3067, 0x82c5}, {0x3068, 0x82c6},
    {0x3069, 0x82c7}, {0x306a, 0x82c8}, {0x306b, 0x82c9}, {0x306c, 0x82ca},
    {0x306d, 0x82cb}, {0x306e, 0x82cc}, {0x306f, 0x82cd}, {0x3070, 0x82ce},
    {0x3071, 0x82cf}, {0x3072, 0x82d0}, {0x3073, 0x82d1}, {0x3074, 0x82d2},
    {0x3075, 0x82d3}, {0x3076, 0x82d4}, {0x3077, 0x82d5}, {0x3078, 0x82d6},
    {0x3079, 0x82d7}, {0x307a, 0x82d8}, {0x307b, 0x82d9}, {0x307c, 0x82da},
    {0x307d, 0x82db}, {0x307e, 0x82dc}, {0x307f, 0x82dd}, {0x3080, 0x82de},
    {0x3081, 0x82df}, {0x3082, 0x82e0}, {0x3083, 0x82e1}, {0x3084, 0x82e2},
    {0x3085, 0x82e3}, {0x3086, 0x82e4}, {0x3087, 0x82e5}, {0x3088, 0x82e6},
    {0x3089, 0x82e7}, {0x308a, 0x82e8}, {0x308b, 0x82e9}, {0x308c, 0x82ea},
    {0x308d, 0x82eb}, {0x308e, 0x82ec}, {0x308f, 0x82ed}, {0x3092, 0x82f0},
    {0x3093, 0x82f1}, {0x30a1, 0x8340}, {0x30a2, 0x8341}, {0x30a3, 0x8342},
    {0x30a4, 0x8343}, {0x30a5, 0x8344}, {0x30a6, 0x8345}, {0x30a7, 0x8346},
    {0x30a8, 0x8347}, {0x30a9, 0x8348}, {0x30aa, 0x8349}, {0x30ab, 0x834a},
    {0x30ac, 0x834b}, {0x30ad, 0x834c}, {0x30ae, 0x834d}, {0x30af, 0x834e},
    {0x30b0, 0x834f}, {0x30b1, 0x8350}, {0x30b2, 0x8351}, {0x30b3, 0x8352},
    {0x30b4, 0x8353}, {0x30b5, 0x8354}, {0x30b6, 0x8355}, {0x30b7, 0x8356},
    {0x30b8, 0x8357}, {0x30b9, 0x8358}, {0x30ba, 0x8359}, {0x30bb, 0x835a},
    {0x30bc, 0x835b}, {0x30bd, 0x835c}, {0x30be, 0x835d}, {0x30bf, 0x835e},
    {0x30c0, 0x835f}, {0x30c1, 0x8360}, {0x30c2, 0x8361}, {0x30c3, 0x8362},
    {0x30c4, 0x8363}, {0x30c5, 0x8364}, {0x30c6, 0x8365}, {0x30c7, 0x8366},
    {0x30c8, 0x8367}, {0x30c9, 0x8368}, {0x30ca, 0x8369}, {0x30cb, 0x836a},
    {0x30cc, 0x836b}, {0x30cd, 0x836c}, {0x30ce, 0x836d}, {0x30cf, 0x836e},
    {0x30d0, 0x836f}, {0x30d1, 0x8370}, {0x30d2, 0x8371}, {0x30d3, 0x8372},
    {0x30d4, 0x8373}, {0x30d5, 0x8374}, {0x30d6, 0x8375}, {0x30d7, 0x8376},
    {0x30d8, 0x8377}, {0x30d9, 0x8378}, {0x30da, 0x8379}, {0x30db, 0x837a},
    {0x30dc, 0x837b}, {0x30dd, 0x837c}, {0x30de, 0x837d}, {0x30df, 0x837e},
    {0x30e0, 0x8380}, {0x30e1, 0x8381}, {0x30e2, 0x8382}, {0x30e3, 0x8383},
    {0x30e4, 0x8384}, {0x30e5, 0x8385}, {0x30e6, 0x8386}, {0x30e7, 0x8387},
    {0x30e8, 0x8388}, {0x30e9, 0x8389}, {0x30ea, 0x838a}, {0x30eb, 0x838b},
    {0x30ec, 0x838c}, {0x30ed, 0x838d}, {0x30ee, 0x838e}, {0x30ef, 0x838f},
    {0x30f2, 0x8392}, {0x30f3, 0x8393}, {0x30f4, 0x8394}, {0x2282, 0x81bc},
    {0x2283, 0x81bd}, {0x222a, 0x81be}, {0x2229, 0x81bf}, {0x2208, 0x81b8},
    {0x220b, 0x81b9}, {0x2228, 0x81c9}, {0x2227, 0x81c8}, {0x03b1, 0x83bf},
    {0x03b2, 0x83c0}, {0x03b3, 0x83c1}, {0x03b4, 0x83c2}, {0x03b5, 0x83c3},
    {0x2286, 0x81ba}, {0x2191, 0x81aa}, {0x2193, 0x81ab}, {0x221e, 0x8187},
    {0x0026, 0x0026}, {0xff06, 0x8195}, {0x2261, 0x81df}, {0x226a, 0x81e1},
    {0x226b, 0x81e2}, {0x2207, 0x81de}, {0x22a5, 0x81db}, {0x2220, 0x81da},
    {0x2312, 0x81dc}, {0x2252, 0x81e0}, {0x221a, 0x81e3}, {0x2235, 0x81e6},
    {0x00b6, 0x81f7}, {0x4e9c, 0x889f}, {0x5a03, 0x88a1}, {0x8d6b, 0x8a71},
    {0x00a1, 0x88d7}, {0x00a3, 0x88d8}, {0x00a7, 0x88d9}, {0x00b5, 0x88a2},
    {0x00bf, 0x88a3}, {0x00c3, 0x88a4}, {0x00c4, 0x88a5}, {0x00c5, 0x88a6},
    {0x00c6, 0x88a7}, {0x00c7, 0x88a8}, {0x00d1, 0x88a9}, {0x00d5, 0x88aa},
    {0x00d6, 0x88ab}, {0x00d8, 0x88ac}, {0x00dc, 0x88ad}, {0x00df, 0x88ae},
    {0x00e0, 0x88af}, {0x00e2, 0x88b0}, {0x00e3, 0x88b1}, {0x00e4, 0x88b2},
    {0x00e7, 0x88b3}, {0x00e8, 0x88b4}, {0x00e9, 0x88b5}, {0x00ea, 0x88b6},
    {0x00eb, 0x88b7}, {0x00ec, 0x88b8}, {0x00ee, 0x88b9}, {0x00ef, 0x88ba},
    {0x00f1, 0x88bb}, {0x00f2, 0x88bc}, {0x00f4, 0x88bd}, {0x00f5, 0x88be},
    {0x00f6, 0x88bf}, {0x00f9, 0x88c0}, {0x00fb, 0x88c1}, {0x00fc, 0x88c2},
    {0x00e1, 0x88c3}, {0x00ed, 0x88c4}, {0x00f3, 0x88c5}, {0x00fa, 0x88c6},
    {0x00c2, 0x88c7}, {0x00ca, 0x88c8}, {0x00d4, 0x88c9}, {0x00cb, 0x88ca},
    {0x00cf, 0x88cb}, {0x00c1, 0x88cc}, {0x00c9, 0x88cd}, {0x00cd, 0x88ce},
    {0x00d3, 0x88cf}, {0x00da, 0x88d0}, {0x00c0, 0x88d1}, {0x00c8, 0x88d2},
    {0x00cc, 0x88d3}, {0x00d2, 0x88d4}, {0x00d9, 0x88d5}, {0x00b0, 0x88d6},
    {0xffff, 0xffff},
}};
}

static inline igNodeView *nodeAt(igObjectList *list, int index) { return ((igNodeView **)list->_data)[index]; }
static inline int countOf(igObjectList *list) { if (list != 0) return list->_count; return 0; }
static inline igNodeView *asAttrSet(igNodeView *node) {
    if (node != 0 && ((Gap::Core::igObject *)node)->isOfType(g_igAttrSet_metaObject) != 0) return node; else return 0;
}

/* Marks the load as failed, so the font ignores every later message. */
static inline void abandonLoad(beBaseInfoRam *ram) {
    ram->_st0 = kFontStateFailed;
    ram->_st3 = 0;
    ram->_st2 = 0;
    ram->_st1 = 0;
}

/* The interned copy of `text` in the global string pool, creating the pool on first use. */
static inline int internString(int text) {
    if (g_stringPool == 0) {
        int pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)(StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    return (int)(StringPool_Intern(g_stringPool, (const char *)text));
}

/* Drops one reference to an interned string (its count is the word before the text). */
static inline void releaseString(int text) {
    if (text != 0) {
        int *header = (int *)(text - 8);
        int refs = *(int *)(text - 4) - 1;
        *(int *)(text - 4) = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
}

/* Replaces a pooled string field of the pair being named with the interned copy of `text` (the
 * empty string for null). */
#define SET_POOLED_STRING(object, field, text) { \
    const char *value_ = (text) ? (const char *)(text) : (const char *)emptyString; \
    int interned_; \
    pair = (object); \
    interned_ = internString((int)value_); \
    releaseString(pair->field); \
    pair->field = interned_; \
}

/* Tail call to the base-class slot 23 (igObject::vfunc_23). */
void beFont_Start(beFont *self)
{
    beBaseInfoManager_Start((beBaseInfoManager *)self);
}

void beFont_Stop(beFont *self) {
    beFontImageList *fonts;
    int count;
    int clearCount;
    int i;
    int j;
    igObject *font;

    fonts = (beFontImageList *)self->_fonts;
    count = fonts->_count;
    for (i = 0; i < count; i++) {
        font = ((igObject **)fonts->_data)[i];
        igRelease(font);
    }
    clearCount = fonts->_count;
    for (j = 0; j < clearCount; j++) {
        ((igObject **)fonts->_data)[j] = 0;
    }
    fonts->_count = 0;
    beBaseInfoManager_Stop((beBaseInfoManager *)self);
}

/* Registers `receiver` with the font's messenger under the "TEXTCTL" group string, with a null
 * text argument and -1 as the last argument. */
void beFont_OnAddRam(beFont *self, int receiver)
{
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, (beBaseInfoRam *)receiver, "TEXTCTL", 0, -1);
}

static inline int count(const beFontGeomAttrPairList *list) { return list->_count; }

void beFont_Prepare(beFont *self) {
    beFontGeomAttrPairList *pairs;
    int pairCount;
    int clearCount;
    int i;
    int j;
    igObject *pair;
    igObject *root;

    root = (igObject *)self->_root;
    igRelease(root);
    self->_root = 0;
    pairs = (beFontGeomAttrPairList *)self->_gaPairList;
    if (count(pairs) > 0) {
        pairCount = pairs->_count;
        for (i = 0; i < pairCount; i++) {
            pair = ((igObject **)pairs->_data)[i];
            igRelease(pair);
        }
        clearCount = pairs->_count;
        for (j = 0; j < clearCount; j++) {
            ((igObject **)pairs->_data)[j] = 0;
        }
        pairs->_count = 0;
        if (!(0 < ((beFontGeomAttrPairList *)self->_gaPairList)->_count)) {
            ((Gap::Core::igDataList *)self->_gaPairList)->setCapacity(0, 4);
        }
    }
    igStringObj_Clear((igStringObj *)self->_convertData);
}

igMetaObject *beFont_GetInfoMeta(void)
{
    return g_beFontInfo_metaObject;
}

void beFont_UpdateRam(void)
{
}

/* Message handler. INITIALIZE asks the layer controller for the font's layer node, keeps its
 * attribute set as _root and pairs every panel of every category with a new geometry attribute;
 * the other messages act on every layout entry the first two string arguments select. */
int beFont_OnMessage(beFont *self, beBaseInfoRam *ram, beMessengerWork *work) {
    beFontInfo *info;
    int message;
    igNodeView *group;
    igNodeView *layers;
    /* matching construct: `pair` also holds the layer attribute set; one variable for both keeps
       retail's register assignment */
    beFontGeomAttrPair *pair;
    int childCount;
    igObjectList *list;
    int i;
    int j;
    igNodeView *category;
    igNodeView *categorySwitch;
    igNodeView *panel;
    int index;
    int visible;
    unsigned int bitCount;
    int state;
    int result;
    int categoryCount;
    int categories;

    if (((beFontImageList *)self->_fonts)->_count <= 0) { result = 1; goto end; }
    info = (beFontInfo *)ram->_parentInfo;
    message = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beFont_GetMessageEnum(), (const char *)work->_message);
    state = ram->_st0;
    switch (state) {
    case kFontStateInitialize:
        switch (message) { case kFontMessageInitialize:
        {
        if (((beFontImageList *)self->_fonts)->_count <= 0) { abandonLoad(ram); result = 1; goto end; }
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
        beMessenger_AppendString((beMessenger *)self->_messenger, "FONT");
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETLAYERNODE");
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) <= 0) { abandonLoad(ram); result = 1; goto end; }
        group = (igNodeView *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        if (g_igGroup_metaObject != group->GetMeta()) { abandonLoad(ram); result = 1; goto end; }
        list = group->_childList;
        childCount = 0;
        if (list != 0) childCount = list->_count;
        if (childCount <= 0) { abandonLoad(ram); result = 1; goto end; }
        pair = (beFontGeomAttrPair *)nodeAt(list, 0);
        if (g_igAttrSet_metaObject != ((igNodeView *)pair)->GetMeta()) { abandonLoad(ram); result = 1; goto end; }
        if (pair) pair->_refCount = pair->_refCount + 1;
        {
            igNodeView *old = (igNodeView *)self->_root;
            igRelease((igObject *)old);
        }
        self->_root = (int)pair;
        layers = nodeAt(((igNodeView *)self->_root)->_childList, 0);
        i = 0;
        goto nextCategory;
        do {
            category = nodeAt((igObjectList *)categories, i);
            categorySwitch = nodeAt(category->_childList, 0);
            ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)category->_attributes))->concatenate((Gap::Core::igObjectList *)((igTDataList<igObject *> *)((void *)((beFontImage **)((beFontImageList *)self->_fonts)->_data)[beFont_FindFontIndex(self, (int)(categorySwitch->_name ? (const char *)categorySwitch->_name : (const char *)emptyString))]->_attrList)));
            j = 0;
            while (j < countOf(categorySwitch->_childList)) {
                panel = asAttrSet(nodeAt(categorySwitch->_childList, j));
                {
                    void *allocator = ((Gap::Core::igObject *)self)->getMemoryPool();
                    void *creator;
                    if (g_useOwnerAllocator != 0) creator = allocator; else creator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                    igSmartPointer<beFontGeomAttrPair> newPair(beFontGeomAttrPair_Create((int)creator));
                    SET_POOLED_STRING(newPair.p, _category, category->_name)
                    SET_POOLED_STRING(newPair.p, _panel, panel->_name)
                    allocator = ((Gap::Core::igObject *)self)->getMemoryPool();
                    if (g_useOwnerAllocator != 0) creator = allocator; else creator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                    igSmartPointer<igGeometryAttr> geometry(igGeometryAttr_Create((int)creator));
                    ((Gap::Core::igObjectList *)newPair.p->_geomAttrs)->append((Gap::Core::igObject *)geometry.p);
                    ((Gap::Core::igObjectList *)self->_gaPairList)->append((Gap::Core::igObject *)newPair.p);
                }
                j++;
            }
            i++;
        nextCategory:
            list = layers->_childList;
            if (list != 0) categoryCount = list->_count; else categoryCount = 0;
            categories = (int)list;
        } while (i < categoryCount);
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        { result = 1; goto end; }
        }
        }
        goto unhandled;
    }
    result = 1;
    switch (state) {
    case kFontStateReady:
        switch (message) {
        case kFontMessageTextSet: {
            int dataName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
            int setName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            igSmartPointer<igObject> text((igObject *)0, kRetainReference);
            igSmartPointer<igStringObj> scratch((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
            if (beMessenger_GetStringCount((beMessenger *)self->_messenger) > 2) {
                if (beMessenger_GetString((beMessenger *)self->_messenger, 2) != 0) { igStringObj *target = scratch.p; igStringObj_Set(target, beMessenger_GetString((beMessenger *)self->_messenger, 2)); }
                else igStringObj_Set(scratch.p, "\202\251\202\347\202\301\202\333");
                text = scratch;
            } else if (beMessenger_GetIntCount((beMessenger *)self->_messenger) > 0) {
                int k = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                igObjectList *unicodeList = (igObjectList *)info->_unicodeList;
                if (unicodeList != 0 && k < unicodeList->_count) {
                    text = ((igObject **)unicodeList->_data)[k];
                }
            } else if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) > 0) {
                igNodeView *object = (igNodeView *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                object->GetMeta();
                if (g_beUnicodeObj_metaObject == object->GetMeta()) {
                    text = (igObject *)object;
                } else {
                    igStringObj_Set(scratch.p, "\202\251\202\347\202\301\202\333");
                    text = scratch;
                }
            }
            if (text.p != 0) {
                index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
                if (index != -1) {
                    do {
                        beFont_SetText(self, ram, (igNodeView *)text.p, index);
                        index = beFont_FindNextLayoutEntry(self, ram);
                    } while (index != -1);
                }
            }
            return 1;
        }
        case kFontMessageAlign: {
            int dataName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
            int setName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            int align = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 2));
            align = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beFont_GetAlignEnum(), (const char *)align);
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    ((beFontInfoData **)((igObjectList *)info->_dataList)->_data)[index]->_align = align;
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            { result = 1; goto end; }
        }
        case kFontMessageSwitch: {
            int dataName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
            int setName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            igObjectList *dataList;
            igNodeView *layerSwitch;
            igBitMask *categoryMask;
            int k;
            if (beMessenger_GetStringCount((beMessenger *)self->_messenger) > 2) {
                bitCount = (unsigned int)(beMessenger_GetString((beMessenger *)self->_messenger, 2));
                switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beFont_GetSwitchEnum(), (const char *)bitCount)) {
                case 1:
                    visible = 1;
                    break;
                case 0:
                    visible = 0;
                    break;
                }
            } else if (beMessenger_GetIntCount((beMessenger *)self->_messenger) > 0) {
                visible = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            }
            dataList = (igObjectList *)info->_dataList;
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    beFontInfoData *data = ((beFontInfoData **)dataList->_data)[index];
                    int categoryBit = data->_cbitNo;
                    int panelBit = data->_tbitNo;
                    igNodeView *rootSwitch = nodeAt(((igNodeView *)self->_root)->_childList, 0);
                    if (visible != 0) igSwitch_EnableChild((igSwitch *)rootSwitch, categoryBit);
                    {
                        igNodeView *panelSwitch = nodeAt(nodeAt(rootSwitch->_childList, categoryBit)->_childList, 0);
                        if (visible != 0) igSwitch_EnableChild((igSwitch *)panelSwitch, panelBit); else igSwitch_DisableChild((igSwitch *)panelSwitch, panelBit);
                    }
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            k = 0;
            layerSwitch = nodeAt(((igNodeView *)self->_root)->_childList, 0);
            categoryMask = (igBitMask *)((igSwitch *)layerSwitch)->_childMask;
            while (k < countOf(layerSwitch->_childList)) {
                igBitMask *panelMask = (igBitMask *)((igSwitch *)nodeAt(nodeAt(layerSwitch->_childList, k)->_childList, 0))->_childMask;
                if ((1 << (k & 31)) & ((int *)categoryMask->_data)[(unsigned int)k >> 5]) {
                    unsigned char anyPanel = 0;
                    unsigned int bit;
                    bitCount = panelMask->_bitCount;
                    for (bit = 0; bit < bitCount; bit++) {
                        if ((1 << (bit & 31)) & ((int *)panelMask->_data)[bit >> 5]) anyPanel = 1;
                    }
                    if (!anyPanel) igSwitch_DisableChild((igSwitch *)layerSwitch, k);
                } else {
                    unsigned char anyPanel = 0;
                    unsigned int bit;
                    bitCount = panelMask->_bitCount;
                    for (bit = 0; bit < bitCount; bit++) {
                        if ((1 << (bit & 31)) & ((int *)panelMask->_data)[bit >> 5]) anyPanel = 1;
                    }
                    if (anyPanel) igSwitch_EnableChild((igSwitch *)layerSwitch, k);
                }
                k++;
            }
            { result = 1; goto end; }
        }
        case kFontMessageSetPosition: {
            int dataName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
            int setName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            igVec3f position = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    igNodeView *attrSet = (igNodeView *)((beFontInfoData **)((igObjectList *)info->_dataList)->_data)[index]->_attrSet;
                    igMatrix44f_SetTranslation(((igTransform *)nodeAt(attrSet->_childList, 0))->_m, position.vec);
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            { result = 1; goto end; }
        }
        case kFontMessageColor:
        case kFontMessageDefaultColor:
        case kFontMessageCancelColor: {
            int dataName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
            int setName = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
            float red;
            float green;
            float blue;
            if (message == kFontMessageDefaultColor) {
                blue = green = red = 0.9f;
            } else if (message == kFontMessageCancelColor) {
                blue = green = red = 0.5f;
            } else {
                igVec3f requested = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
                red = requested[0];
                green = requested[1];
                blue = requested[2];
            }
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    int a;
                    igNodeView *attribute;
                    igObjectList *attributes = ((igNodeView *)((beFontInfoData **)((igObjectList *)info->_dataList)->_data)[index]->_attrSet)->_attributes;
                    a = 0;
                    if (0 < attributes->_count) {
                        do {
                        attribute = ((igNodeView **)attributes->_data)[a];
                        if (Gap::Attrs::igColorAttr::getClassMeta() == attribute->GetMeta()) {
                            igVec4f color;
                            Color4f_Unpack(&color, 1, ((igColorAttr *)attribute)->_colorPacked);
                            color[0] = red;
                            color[1] = green;
                            color[2] = blue;
                            attribute->setColor(&color);
                        }
                        a++;
                        } while (a < attributes->_count);
                    }
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            { result = 1; goto end; }
        }
        case kFontMessageReplaceUnknown: {
            if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) <= 0) { result = 1; goto end; }
            if (beMessenger_GetIntCount((beMessenger *)self->_messenger) <= 0) { result = 1; goto end; }
            {
                beUnicodeObj *text = (beUnicodeObj *)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                int replacement = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                beFontImageDispatchView *font = ((beFontImageDispatchView **)((beFontImageList *)self->_fonts)->_data)[0];
                unsigned short *p = (unsigned short *)text->_buffer;
                unsigned int length = Memory_GetBufferSize(p) >> 1;
                int c;
                for (c = 0; c < (int)length; c++, p++) {
                    unsigned short character = *p;
                    if (character == 0) break;
                    if (!(0 < font->countTriangles(character))) *p = replacement;
                }
            }
            { result = 1; goto end; }
        }
        default:
            goto unhandled;
        }
    }
    goto end;
unhandled:
    result = 0;
end:
    return result;
}

/* igObjectList with a typed element array. */
struct igObjectListView { char header[8]; int count; int capacity; igNodeView **data; };
/* igNamedObjectInfo with its object list typed. */
struct igNamedObjectInfoView { char header[20]; igObjectListView *objects; igObjectListView *getObjects() const { return objects; } };
static inline int objectCount(igObjectListView *list) { return list->count; }
static inline igNodeView *objectAt(igObjectListView *list, int index) { return list->data[index]; }

/* Adds every beFontImage among the info's objects to the font's images. */
void beFont_AddFontImages(beFont *self, igNamedObjectInfo *info) {
    igNamedObjectInfoView *named = (igNamedObjectInfoView *)info;
    int i;
    for (i = 0; i < objectCount(named->getObjects()); i++) {
        igNodeView *object = objectAt(named->objects, i);
        igMetaObject *fontImageMeta = g_beFontImage_metaObject;
        if (fontImageMeta == object->GetMeta()) {
            ((Gap::Core::igObjectList *)self->_fonts)->append((Gap::Core::igObject *)object);
        }
    }
}

/* Converts Shift-JIS text to a new beUnicodeObj. The first pass counts the characters the table
 * knows and keeps the text in _convertData; carriage returns are dropped, and a line feed is kept
 * once text has started. */
igSmartPointer<beUnicodeObj> beFont_ConvertToUnicode(beFont *self, const char *text) {
    SjisUnicodeTable table = g_sjisToUnicodeTable;
    char lead;
    char trail;
    char single;
    int length = 0;
    unsigned i = 0;
    int allocator;
    while (i < (unsigned)strlen(text)) {
        const char *p = text + i;
        unsigned c = (unsigned char)*p;
        if (c == '\n') {
            if (length > 0) length++;
            i++;
        } else if (c == '\r') {
            i++;
        } else if (c & 0x80) {
            unsigned short high = (unsigned char)c << 8;
            unsigned short sjis = high | (unsigned char)p[1];
            const char *second = p + 1;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { length++; break; }
                    entry++;
                } while (entry->unicode != 0xffff);
            }
            igStringObj_Clear((igStringObj *)self->_convertData);
            lead = *p;
            igStringObj_Insert((igStringObj *)self->_convertData, &lead, ((igStringObj *)self->_convertData)->_length, 1);
            trail = *second;
            igStringObj_Insert((igStringObj *)self->_convertData, &trail, ((igStringObj *)self->_convertData)->_length, 1);
            i += 2;
        } else {
            unsigned char ch = c;
            unsigned short sjis = ch;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { length++; break; }
                    entry++;
                } while (entry->unicode != 0xffff);
            }
            igStringObj_Clear((igStringObj *)self->_convertData);
            single = *p;
            igStringObj_Insert((igStringObj *)self->_convertData, &single, ((igStringObj *)self->_convertData)->_length, 1);
            i++;
        }
    }
    allocator = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    allocator = g_useOwnerAllocator ? allocator : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beUnicodeObj> result(beUnicodeObj_Create(allocator));
    beUnicodeObj_AllocateBuffer(result.p, length);
    unsigned short *out = (unsigned short *)result.p->_buffer;
    int written = 0;
    unsigned j = 0;
    while (j < (unsigned)strlen(text)) {
        const char *p = text + j;
        unsigned c = (unsigned char)*p;
        if (c == '\n') {
            if (written > 1) out[written++] = c;
            j++;
        } else if (c == '\r') {
            j++;
        } else if (c & 0x80) {
            unsigned short high = (unsigned char)c << 8;
            unsigned short sjis = high | (unsigned char)p[1];
            int k = 0;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { out[written++] = table.entries[k].unicode; break; }
                    entry++;
                    k++;
                } while (entry->unicode != 0xffff);
            }
            j += 2;
        } else {
            unsigned char ch = c;
            unsigned short sjis = ch;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { out[written++] = ch; break; }
                    entry++;
                } while (entry->unicode != 0xffff);
            }
            j++;
        }
    }
    out[written] = 0;
    return result;
}

/* Index of the font image called `name`; the first font when none is, or `name` is null. */
int beFont_FindFontIndex(beFont *self, int name) {
    int i;
    int *fontName;
    if (name == 0) {
        return 0;
    }
    i = 0;
    if (0 < ((beFontImageList *)self->_fonts)->_count) {
        do {
            fontName = (int *)(((beFontImage **)((beFontImageList *)self->_fonts)->_data)[i])->_name;
            fontName = fontName ? fontName : (int *)emptyString;
            if (strcmp((const char *)name, (const char *)fontName) == 0) {
                return i;
            }
            i += 1;
        } while (i < ((beFontImageList *)self->_fonts)->_count);
    }
    return 0;
}

/* Builds the text geometry of layout entry `index` from an igStringObj (Shift-JIS) or a
 * beUnicodeObj, then swaps it into the entry's attribute set. */
void beFont_SetText(beFont *self, beBaseInfoRam *ram, igNodeView *text, int index) {
    beFontInfoData *entry = ((beFontInfoData **)((igObjectList *)((beFontInfo *)ram->_parentInfo)->_dataList)->_data)[index];
    igNodeView *target = nodeAt(nodeAt(((igNodeView *)entry->_attrSet)->_childList, 0)->_childList, 0);
    void *spare = nodeAt(target->_attributes, 0);
    igSmartPointer<beUnicodeObj> unicode((beUnicodeObj *)0, kRetainReference);
    igMetaObject *meta;
    meta = text->GetMeta();
    if (strcmp((const char *)meta->_name, "igStringObj") == 0) {
        const char *buffer = (const char *)((igStringObj *)text)->_buffer;
        const char *sjis;
        if (buffer == 0) sjis = g_stringObjEmptyText; else sjis = buffer;
        igSmartPointer<beUnicodeObj> converted(beFont_ConvertToUnicode(self, sjis));
        unicode = converted;
    } else if (strcmp((const char *)meta->_name, "beUnicodeObj") == 0) {
        unicode = (beUnicodeObj *)text;
    } else {
        return;
    }
    /* matching construct: declaration-order search — the order of these locals sets which argument registers the search loop uses */
    beFontGeomAttrPair *pair = 0;
    int i;
    beFontGeomAttrPair *candidate;
    int offset;
    beFontGeomAttrPairList *pairs = (beFontGeomAttrPairList *)self->_gaPairList;
    beFontGeomAttrPairList *list = pairs;
    if (list->_count > 0) {
        i = 0;
        if (i < list->_count) {
            offset = 0;
            do {
                candidate = (beFontGeomAttrPair *)((int *)((char *)list->_data + offset))[0];
                const int *category = (const int *)entry->_name;
                const int *categoryName;
                if (category != 0) categoryName = category; else categoryName = (const int *)emptyString;
                if ((int)categoryName == candidate->_category) {
                    const int *panel = (const int *)((igAttrSet *)entry->_attrSet)->_name;
                    const int *panelName;
                    if (panel != 0) panelName = panel; else panelName = (const int *)emptyString;
                    if ((int)panelName == candidate->_panel) { pair = candidate; break; }
                }
                list = pairs;
                i++;
                offset += 4;
            } while (i < *(int *)&list->_count);
        }
    }
    int characters = unicode.p->_buffer;
    self->_fontIdx = beFont_FindFontIndex(self, entry->_kind);
    igGeometryAttr *geometry = (igGeometryAttr *)nodeAt((igObjectList *)pair->_geomAttrs, 0);
    beFont_PrepareGeometry(self, geometry, characters, 1);
    igVertexArrayView *vertices = (igVertexArrayView *)geometry->_vertexArray;
    ((beFontImageDispatchView **)((beFontImageList *)self->_fonts)->_data)[self->_fontIdx]->buildVertices(vertices, characters);
    igVertexArrayLock positions;
    igVertexArrayLock texCoords;
    igVertexArrayLock_Init(&positions);
    igVertexArrayLock_Init(&texCoords);
    beFont_LockVertexArray(self, vertices, &positions, &texCoords);
    beFont_LayoutLines(self, (unsigned short *)characters, (int)entry, &positions);
    if (entry->_align == 1 || entry->_align == 2) beFont_AlignLines(self, characters, entry, &positions);
    vertices->unlock(&texCoords, 0);
    vertices->unlock(&positions, 0);
    ((Gap::Core::igObjectList *)pair->_geomAttrs)->append((Gap::Core::igObject *)spare);
    igObjectList *targetAttributes = target->_attributes;
    if (geometry != 0) ++geometry->_refCount;
    igGeometryAttr *old = (igGeometryAttr *)((int *)targetAttributes->_data)[0];
    igRelease(old);
    int slot = 0;
    if (targetAttributes->_count != 0 && slot >= 0 && slot < targetAttributes->_count) ((int *)targetAttributes->_data)[0] = (int)geometry;
    igObjectList *pairGeometry = (igObjectList *)pair->_geomAttrs;
    igGeometryAttr *taken = (igGeometryAttr *)((int *)pairGeometry->_data)[0];
    igRelease(taken);
    List_RemoveWordAt((igDataList *)pairGeometry, 0);
    ((int *)pairGeometry->_data)[pairGeometry->_count] = 0;
}

/* Gives `geometry` a new vertex array of `vertexCount` vertices in the font image's vertex format,
 * with format bit 2 cleared. */
void beFont_ReplaceVertexArray(beFont *self, igGeometryAttr *geometry, int fontIndex, int vertexCount) {
    igSmartPointer<igVertexArray> vertices((igVertexArray *)geometry->_vertexArray); /* matching construct: declared first so it takes the retail slot above format */
    unsigned format;
    void *allocator;
    igVertexArray *held;
    igVertexArray *created;
    held = vertices.p;
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    allocator = ((Gap::Core::igObject *)self)->getMemoryPool();
    allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    held = vertices.p;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if ((held->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(held);
        }
    }
    vertices.p = (igVertexArray *)igVertexArray_Create((int)allocator);
    format = ((beFontImage **)((beFontImageList *)self->_fonts)->_data)[fontIndex]->_vertexFlags;
    format = format & ~4u;
    ((igVertexArrayView *)vertices.p)->configure(format, vertexCount, 0, 0);
    created = vertices.p;
    if (created != 0) {
        created->_refCount = created->_refCount + 1;
    }
    held = (igVertexArray *)geometry->_vertexArray;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if ((held->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(held);
        }
    }
    geometry->_vertexArray = (int)created;
}

/* Sizes `geometry` for `text` as a triangle list (two extra triangles for UTF-16 text), replacing
 * its vertex array when that is missing or too small. */
void beFont_PrepareGeometry(beFont *self, igGeometryAttr *geometry, int text, int wide) {
    int triangles;
    unsigned vertexCount;
    igVertexArray *held;
    if (wide != 0) {
        triangles = beFontImage_CountTrianglesWide((beFontImage *)(((int *)((igObjectList *)self->_fonts)->_data)[self->_fontIdx]), (const unsigned short *)text);
        vertexCount = (triangles + 2) * 3;
    } else {
        triangles = beFontImage_CountTriangles((beFontImage *)(((int *)((igObjectList *)self->_fonts)->_data)[self->_fontIdx]), (const char *)text);
        vertexCount = triangles * 3;
    }
    ((igGeometryAttrDispatchView *)geometry)->configure(3, triangles, 0);
    {
        igSmartPointer<igVertexArray> vertices((igVertexArray *)geometry->_vertexArray);
        held = vertices.p;
        if (held != 0) {
            held->_refCount = held->_refCount + 1;
        }
        held = vertices.p;
        if (held != 0) {
            if (held->_numVerts < vertexCount) {
                goto replace;
            }
        } else {
replace:
            beFont_ReplaceVertexArray(self, geometry, self->_fontIdx, (int)vertexCount);
        }
    }
}

/* Moves each glyph quad (six vertices) onto its line, and records in _lineFeedList the vertex where
 * each line ends and in _alignList its width. */
void beFont_LayoutLines(beFont *self, unsigned short *text, int entry, igVertexArrayLock *positions) {
    float z;
    unsigned short ch;
    int lastLine;
    unsigned i;
    FloatBits start;
    int lastWidth;
    char *base;
    float *vertex;
    float y;
    unsigned end;
    int line;
    unsigned vertexIndex;
    UnsignedIntListView *lineEnds;
    float x;
    int width;
    FloatListView *lineWidths;
    int character;
    vertexIndex = 0;
    x = 0.0f;
    z = 0.0f;
    ((UnsignedIntListView *)self->_lineFeedList)->count = 0;
    ((FloatListView *)self->_alignList)->count = 0;
    ch = *text;
    base = positions->data;
    y = x;
    if (ch != 0) {
        do {
            character = ch;
            switch (character) {
            case '\r':
                break;
            case '\n':
                if (vertexIndex != 0) {
                    lineEnds = ((UnsignedIntListView *)self->_lineFeedList);
                    line = lineEnds->count;
                    vertex = (float *)(base + positions->stride * vertexIndex);
                    if (line < lineEnds->capacity) lineEnds->count = lineEnds->getCount() + 1; else ((Gap::Core::igDataList *)lineEnds)->resizeAndSetCount(line + 1, 4);
                    lineEnds->data[line] = vertexIndex;
                    start.f = x;
                    start.bits.sign = 0;
                    lineWidths = ((FloatListView *)self->_alignList);
                    width = lineWidths->count;
                    x = *vertex - start.f;
                    if (width < lineWidths->capacity) lineWidths->count = lineWidths->getCount() + 1; else ((Gap::Core::igDataList *)lineWidths)->resizeAndSetCount(width + 1, 4);
                    lineWidths->data[width] = x;
                    x = -*vertex;
                    y = y - ((beFontImage **)((beFontImageList *)self->_fonts)->_data)[self->_fontIdx]->_height;
                }
                break;
            default:
                end = vertexIndex + 6;
                i = vertexIndex;
                if (vertexIndex < end) {
                  if (i < end) {
                    do {
                        vertex = (float *)(base + positions->stride * i);
                        i++;
                        vertex[0] = vertex[0] + x;
                        vertex[1] = vertex[1] + y;
                        vertex[2] = vertex[2] + z;
                    } while (i < end);
                  }
                }
                vertexIndex += 6;
                break;
            }
            text++;
            ch = *text;
        } while (ch != 0);
    }
    positions->count = vertexIndex;
    lineEnds = ((UnsignedIntListView *)self->_lineFeedList);
    lastLine = lineEnds->count;
    if (lastLine < lineEnds->capacity) lineEnds->count = lineEnds->getCount() + 1; else ((Gap::Core::igDataList *)lineEnds)->resizeAndSetCount(lastLine + 1, 4);
    lineEnds->data[lastLine] = vertexIndex;
    lineWidths = ((FloatListView *)self->_alignList);
    lastWidth = lineWidths->count;
    if (lastWidth < lineWidths->capacity) lineWidths->count = lineWidths->getCount() + 1; else ((Gap::Core::igDataList *)lineWidths)->resizeAndSetCount(lastWidth + 1, 4);
    lineWidths->data[lastWidth] = *vertex;
}

/* Shifts each line's glyph quads right by the line's spare width (alignment 1) or half of it
 * (alignment 2). The shift is an igVec3f added with its inline operator+=; that inlined member is why
 * retail keeps an exception record for this frameless function. */
void beFont_AlignLines(beFont *self, int text, beFontInfoData *entry, igVertexArrayLock *positions) {
    float width = entry->_width;
    int align = entry->_align;
    igVec3f shift(0.0f, 0.0f, 0.0f);
    char *base = positions->data;
    unsigned vertexIndex = 0;
    int line;
    igVec3f *vertex;
    unsigned end;
    unsigned i;
    for (line = 0; line < ((UnsignedIntListView *)self->_lineFeedList)->count; line++) {
        end = ((UnsignedIntListView *)self->_lineFeedList)->data[line];
        switch (align) {
        case 1:
            shift[0] = width - ((FloatListView *)self->_alignList)->data[line];
            break;
        case 2:
            shift[0] = (width - ((FloatListView *)self->_alignList)->data[line]) / 2.0f;
            break;
        }
        while (vertexIndex < end) {
            for (i = vertexIndex; i < vertexIndex + 6; i++) {
                vertex = (igVec3f *)(base + positions->stride * i);
                *vertex += shift;
            }
            vertexIndex += 6;
        }
    }
}

/* Locks the positions (component 0) and the first texture-coordinate set (component 3) of every
 * vertex. */
void beFont_LockVertexArray(beFont *self, igVertexArrayView *vertices, igVertexArrayLock *positions, igVertexArrayLock *texCoords) {
    unsigned int vertexCount;

    positions->component = 0;
    positions->firstVertex = 0;
    positions->componentIndex = 0;
    texCoords->component = 3;
    texCoords->firstVertex = 0;
    texCoords->componentIndex = 0;
    vertexCount = ((igVertexArray *)vertices)->_numVerts;
    texCoords->count = vertexCount;
    positions->count = vertexCount;
    vertices->lock(positions, 1);
    vertices->lock(texCoords, 1);
}

/* Starts a layout-entry search: entries whose name is `dataName` (or every entry for "ALL") and
 * whose attribute set is `setName`. */
int beFont_FindFirstLayoutEntry(beFont *self, beBaseInfoRam *ram, int dataName, int setName) {
    dataName = internString(dataName);
    releaseString(self->_condition00);
    self->_condition00 = dataName;
    setName = internString(setName);
    releaseString(self->_condition01);
    self->_condition01 = setName;
    self->_history = 0;
    return beFont_FindNextLayoutEntry(self, ram);
}

/* Next layout entry from _history on that matches _condition00/_condition01, or -1. */
int beFont_FindNextLayoutEntry(beFont *self, beBaseInfoRam *ram) {
    int j;
    const char *name;
    int found;
    int i;
    igAttrSet *attrSet;
    const char *wanted;
    beFontInfoData *data;
    int offset;
    beBaseInfoDataList *list;
    int offset2;

    found = -1;
    list = (beBaseInfoDataList *)((beFontInfo *)ram->_parentInfo)->_dataList;
    if (strcmp((const char *)self->_condition00, "ALL") == 0) {
        i = self->_history;
        offset = i * 4;
        if (i < list->_count) {
            do {
                wanted = (const char *)self->_condition01;
                name = (const char *)((igAttrSet *)((beFontInfoData *)*(int *)(list->_data + offset))->_attrSet)->_name;
                if (strcmp(name != 0 ? name : ((char *)emptyString), wanted) == 0) {
                    found = i;
                    break;
                }
                i += 1;
                offset += 4;
            } while (i < list->_count);
        }
    } else {
        j = self->_history;
        offset2 = j * 4;
        if (j < list->_count) {
            do {
                data = (beFontInfoData *)*(int *)(list->_data + offset2);
                name = (const char *)data->_name;
                attrSet = (igAttrSet *)data->_attrSet;
                wanted = (const char *)self->_condition00;
                if (strcmp(name != 0 ? name : ((char *)emptyString), wanted) == 0) {
                    name = (const char *)attrSet->_name;
                    wanted = (const char *)self->_condition01;
                    if (strcmp(name != 0 ? name : ((char *)emptyString), wanted) == 0) {
                        found = j;
                        break;
                    }
                }
                j += 1;
                offset2 += 4;
            } while (j < list->_count);
        }
    }
    if (found != -1) {
        self->_history = found + 1;
    }
    return found;
}

void beUnicodeObj_userDestruct(beUnicodeObj *self) {
    if (self->_buffer != 0) {
        Memory_FreeBufferWithAllocator((void *)self->_buffer, ((Gap::Core::igObject *)self)->getMemoryPool());
    }
    Gap__Core__igObject__userDestruct((igObject *)self);
}

/* Makes the buffer hold `length` UTF-16 characters and a terminator, and clears it. */
void beUnicodeObj_AllocateBuffer(beUnicodeObj *self, int length) {
    unsigned int need;
    if (self->_buffer != 0) {
        need = (length + 1) * 2;
        if (Memory_GetBufferSize((void *)self->_buffer) < need) {
            Memory_FreeBufferWithAllocator((void *)self->_buffer, ((Gap::Core::igObject *)self)->getMemoryPool());
            self->_buffer = (int)Memory_AllocateAlignedWithAllocator(need, 0x10, ((Gap::Core::igObject *)self)->getMemoryPool());
        }
    } else {
        self->_buffer = (int)Memory_AllocateAlignedWithAllocator((length + 1) * 2, 0x10, ((Gap::Core::igObject *)self)->getMemoryPool());
    }
    memset((void *)self->_buffer, 0, Memory_GetBufferSize((void *)self->_buffer));
}

igMetaObject *beUnicodeObj_GetMeta(void)
{
    return g_beUnicodeObj_metaObject;
}

igMetaObject *beFont_GetMeta(void)
{
    return g_beFont_metaObject;
}

#pragma pop

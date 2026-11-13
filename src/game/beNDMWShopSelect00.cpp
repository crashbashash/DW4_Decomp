#include "dw4/reflected.h"

extern "C" void *StringPool_Allocate(int size);
extern "C" void *StringPool_Construct(void *pool);
extern "C" char *StringPool_Intern(void *pool, const char *text);
extern "C" int StringChunk_ReleaseHeader(int chunk, int *header);
extern "C" void *g_stringPool[4];
extern "C" int beNDMWWindow_RunMessageScript(void *self, const char *script, int entCode);
extern "C" int beNDMWWindow_PresentModelAtOrigin(void *self, const char *model, int id, const char *sequence, const char *close);
extern "C" int beNDMWWindow_QueueText(void *self, const char *type, const char *name, const char *text, const char *align);
extern "C" int beMessenger_AppendBool(int messenger, int value);
extern "C" int beMessenger_AppendInt(int messenger, int value);
extern "C" int beMessenger_AppendString(int messenger, const char *text);
extern "C" void beMessenger_AppendVec3(int messenger, float *vec);
extern "C" int beMessenger_DispatchSelected(int messenger, const char *message);
extern "C" int beMessenger_SelectGroup(int messenger, const char *group);
extern "C" int beMessenger_GetObject(int messenger, int index);
extern "C" void sprintf(char *out, const char *format, ...);
extern "C" int strlen(const char *text);

typedef struct PropertyRecord {
    char pad[12];
    int value;
} PropertyRecord;
extern "C" PropertyRecord *igProperty_GetRecord(int object, const char *name);

extern "C" char STWINFONT13_3[];
extern "C" char STWINFONT14_3[];
extern "C" char STWINFONT19[];
extern "C" char STWINFONT25_2[];
extern "C" char STWINFONT28_2[];
extern "C" char STWINFONT29_4[];
extern "C" char STWINFONT33_2[];
extern "C" char STWINFONT34[];
extern "C" char STWINFONT35_2[];
extern "C" char TALKFONT01_2[];
extern "C" char font00[];
extern "C" char font000_4[];
extern "C" char font001_4[];
extern "C" char font002_3[];
extern "C" char font003_3[];
extern "C" char font004_2[];
extern "C" char font005_2[];
extern "C" char font006_2[];
extern "C" char font100_4[];
extern "C" char font_03d_3[];
extern "C" char font01_d_2[];
extern "C" char font02_d_2[];
extern "C" char txt_shop_lua_3[];
extern "C" char i_messky[];
extern "C" char i_stmessky[];
extern "C" char i_stmesscr_2[];
extern "C" char i_stcursor01_2[];
extern "C" char i_stcursor03_3[];
extern "C" char i_stcursor05[];
extern "C" char j_shwin_2[];
extern "C" char j_shcardwin_2[];
extern "C" char j_shcardcursor[];
extern "C" char SQ_XDATASTATUSOPEN[];
extern "C" char SQ_OPEN_7[];
extern "C" char SQ_CLOSE_8[];
extern "C" char GAMERAM_10[];
extern "C" char GETPLAYER_7[];
extern "C" char RECALCPLAYER_6[];
extern "C" char TEXTCTL_6[];
extern "C" char TEXTSET_4[];
extern "C" char COLOR_2[];
extern "C" char DEFAULTCOLOR_4[];
extern "C" char CANCELCOLOR_3[];
extern "C" char ALIGN_4[];
extern "C" char LEFT_5[];
extern "C" char CENTER_3[];
extern "C" char RIGHT_4[];
extern "C" char SWITCH_5[];
extern "C" char DISPON_4[];
extern "C" char DISPOFF_3[];
extern "C" char space_3[];
extern "C" char dashdashdashdash_3[];
extern "C" char percent_d_6[];
extern "C" char percent_02d[];
extern "C" char percent_03d[];
extern "C" char percent_04d[];
extern "C" char percent_05d[];
extern "C" char percent_06d[];
extern "C" char percent_07d[];

/* The seven XDATA stats: property key, cost-display cap and value font, in display order. */
typedef struct StatNameTable { const char *names[7]; } StatNameTable;
typedef struct StatCapTable { int caps[7]; } StatCapTable;
extern "C" const StatNameTable g_shopStatPropertyNames;
extern "C" const StatCapTable g_shopStatCaps;
extern "C" const StatNameTable g_shopStatValueFonts;
/* STWINFONT29 fonts naming the decision rows of ShopSelectB0. */
typedef struct DecideFontPair { const char *fonts[2]; } DecideFontPair;
extern "C" const DecideFontPair g_shopDecideFlagFonts;

extern "C" int g_beNDMWShopSelectB0_metaObject[4];
extern "C" int g_beNDMWShopSelectA0_metaObject[4];
extern "C" int g_beNDMWShopSelect52_metaObject[4];
extern "C" int g_beNDMWShopSelect34_metaObject[4];
extern "C" int g_beNDMWShopSelect11_metaObject[4];
extern "C" int g_beNDMWShopSelect03_metaObject[4];
extern "C" int g_beNDMWShopSelect02_metaObject[4];
extern "C" int g_beNDMWShopSelect01_metaObject[4];
extern "C" int g_beNDMWShopSelect00_metaObject[4];

extern "C" void beNDMWShopSelect00_Setup(beNDMWShopSelect00 *self);
extern "C" void beNDMWShopSelect01_Setup(beNDMWShopSelect01 *self);
extern "C" void beNDMWShopSelect03_Setup(beNDMWShopSelect03 *self);
extern "C" void beNDMWShopSelect11_Setup(beNDMWShopSelect11 *self);
extern "C" void beNDMWShopSelect11_RefreshStatCosts(beNDMWShopSelect11 *self);
extern "C" void beNDMWShopSelect34_Setup(beNDMWShopSelect34 *self);
extern "C" void beNDMWShopCtrlEditBit_ShowValueDigits(beNDMWShopCtrlEditBit *self, int mode, int value);
extern "C" void beNDMWWindow_ShowPaddedDigits(beNDMWWindow *self, int value, unsigned int digits, const char *slotFormat);
extern "C" void beNDMWShopSelect52_Setup(beNDMWShopSelect52 *self);
extern "C" void beNDMWShopSelectA0_Setup(beNDMWShopSelectA0 *self);
extern "C" void beNDMWShopSelectB0_Setup(beNDMWShopSelectB0 *self);
extern "C" int beNDMWShopSelectB0_GetMeta(void);
extern "C" int beNDMWShopSelectA0_GetMeta(void);
extern "C" int beNDMWShopSelect52_GetMeta(void);
extern "C" int beNDMWShopSelect34_GetMeta(void);
extern "C" int beNDMWShopSelect11_GetMeta(void);
extern "C" int beNDMWShopSelect03_GetMeta(void);
extern "C" int beNDMWShopSelect02_GetMeta(void);
extern "C" int beNDMWShopSelect01_GetMeta(void);
extern "C" int beNDMWShopSelect00_GetMeta(void);

/* The pooled-string singleton, created on first use. */
static inline void *StringPool_Get(void) {
    if (g_stringPool[0] == 0) {
        void *pool = StringPool_Allocate(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return g_stringPool[0];
}

/* Drops one share of a pooled string token (reference count at token[-1], chunk header at token[-2]). */
static inline void StringToken_Release(char *token) {
    if (token != 0) {
        int *header = (int *)token - 2;
        int refs = ((int *)token)[-1] - 1;
        ((int *)token)[-1] = refs;
        if (refs == 0) StringChunk_ReleaseHeader(*header, header);
    }
}

/* Owning stack reference to a pooled string token; releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    /* takes an extra share of a token already owned elsewhere */
    StringRef(char *s, int retain) : p(s) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    ~StringRef() { StringToken_Release(p); }
};
extern "C" int StringList_AppendRetained(int list, StringRef *token);

/* Appends a pooled copy of `text` to a window string list; a null text appends a null token. */
#define INTERN_APPEND(list, text) { \
    char *token; \
    if ((text) == 0) { \
        token = 0; \
    } else { \
        token = StringPool_Intern(StringPool_Get(), (text)); \
    } \
    StringRef held(token); \
    StringList_AppendRetained(list, &held); }

/* Interns `name` as the window's SELECTCTRL receiver name, dropping the previous one. */
#define SET_INFO_NAME(self, name) { \
    char *fresh = StringPool_Intern(StringPool_Get(), (name)); \
    StringToken_Release((char *)(self)->_infoName); \
    (self)->_infoName = (int)fresh; }

void beNDMWShopSelect00_Setup(beNDMWShopSelect00 *self) {
    if (self->_entCode > 0) {
        INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
        if (self->_panelName == 0) {
            INTERN_APPEND(self->_textCloseNameList, font000_4)
        } else {
            StringRef held((char *)self->_panelName, 1);
            StringList_AppendRetained(self->_textCloseNameList, &held);
        }
        beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, self->_entCode);
    }
    SET_INFO_NAME(self, i_stmessky)
    self->_selectMax = 1;
    self->_offsetPos[0] = 0;
    self->_offsetPos[1] = 0;
    self->_offsetPos[2] = 0;
    self->_startPoint = 0;
    self->_isNoCancel = 0;
}

void beNDMWShopSelect01_Setup(beNDMWShopSelect01 *self) {
    switch (self->_entCode) {
    case 0x48B: case 0x48E: case 0x493: case 0x4E7: case 0x4EA: case 0x4F8: case 0x54B:
    case 0x614: case 0x678: case 0x6DC: case 0x740: case 0x61A: case 0x5AD: case 0x7AA:
        INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
        INTERN_APPEND(self->_textCloseNameList, font000_4)
        INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
        INTERN_APPEND(self->_textCloseNameList, font001_4)
        beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, self->_entCode);
        self->_selectMax = 2;
        break;
    case 0x47E: case 0x546: case 0x60E: case 0x672: case 0x6D6: case 0x73A: case 0x79E:
        INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
        INTERN_APPEND(self->_textCloseNameList, font000_4)
        INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
        INTERN_APPEND(self->_textCloseNameList, font001_4)
        INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
        INTERN_APPEND(self->_textCloseNameList, font002_3)
        beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, self->_entCode);
        self->_selectMax = 3;
        break;
    }
    SET_INFO_NAME(self, i_stmesscr_2)
    self->_offsetPos[0] = 0;
    self->_offsetPos[1] = 0;
    self->_offsetPos[2] = 0;
    self->_isNoCancel = 0;
}

void beNDMWShopSelect03_Setup(beNDMWShopSelect03 *self) {
    if (self->_entCode > 0) {
        INTERN_APPEND(self->_textCloseTypeList, TALKFONT01_2)
        INTERN_APPEND(self->_textCloseNameList, font00)
        beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, self->_entCode);
    }
    SET_INFO_NAME(self, i_messky)
    self->_selectMax = 1;
    self->_offsetPos[0] = 0;
    self->_offsetPos[1] = 0;
    self->_offsetPos[2] = 0;
    self->_startPoint = 0;
    self->_isNoCancel = 0;
}

void beNDMWShopSelect11_Setup(beNDMWShopSelect11 *self) {
    beNDMWWindow_PresentModelAtOrigin(self, j_shwin_2, 0, SQ_XDATASTATUSOPEN, SQ_CLOSE_8);
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
    INTERN_APPEND(self->_textCloseNameList, font100_4)
    beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, 0x481);
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT13_3)
    INTERN_APPEND(self->_textCloseNameList, font000_4)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT35_2)
    INTERN_APPEND(self->_textCloseNameList, font001_4)
    beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, 0x44D);
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT14_3)
    INTERN_APPEND(self->_textCloseNameList, font000_4)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT14_3)
    INTERN_APPEND(self->_textCloseNameList, font001_4)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT14_3)
    INTERN_APPEND(self->_textCloseNameList, font002_3)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT14_3)
    INTERN_APPEND(self->_textCloseNameList, font003_3)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT14_3)
    INTERN_APPEND(self->_textCloseNameList, font004_2)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT14_3)
    INTERN_APPEND(self->_textCloseNameList, font005_2)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT14_3)
    INTERN_APPEND(self->_textCloseNameList, font006_2)
    beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, 0x44F);
    beNDMWWindow_QueueText(self, STWINFONT19, font000_4, space_3, RIGHT_4);
    beNDMWWindow_QueueText(self, STWINFONT19, font001_4, space_3, RIGHT_4);
    beNDMWWindow_QueueText(self, STWINFONT19, font002_3, space_3, RIGHT_4);
    beNDMWWindow_QueueText(self, STWINFONT19, font003_3, space_3, RIGHT_4);
    beNDMWWindow_QueueText(self, STWINFONT19, font004_2, space_3, RIGHT_4);
    beNDMWWindow_QueueText(self, STWINFONT19, font005_2, space_3, RIGHT_4);
    beNDMWWindow_QueueText(self, STWINFONT19, font006_2, space_3, RIGHT_4);
    beNDMWWindow_QueueText(self, STWINFONT29_4, font000_4, space_3, LEFT_5);
    beMessenger_SelectGroup(self->_messenger, GAMERAM_10);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_AppendBool(self->_messenger, 0);
    beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_6);
    beNDMWShopSelect11_RefreshStatCosts(self);
    beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, self->_entCode + 0x482);
    SET_INFO_NAME(self, i_stcursor01_2)
    self->_selectMax = 7;
    self->_offsetPos[0] = -121.0f;
    self->_offsetPos[1] = 128.0f;
    self->_offsetPos[2] = 0.0f;
    self->_startPoint = self->_entCode;
    self->_isNoCancel = 0;
}

/* Shows the raise cost of each of the player's seven stats, or ---- once the stat reached its cap. */
void beNDMWShopSelect11_RefreshStatCosts(beNDMWShopSelect11 *self) {
    float color[3];
    char text[16];
    StatNameTable properties;
    StatCapTable caps;
    StatNameTable fonts;
    int player;
    int i;
    int value;
    const char **property;
    int *cap;
    const char **font;

    beMessenger_SelectGroup(self->_messenger, GAMERAM_10);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_7);
    player = beMessenger_GetObject(self->_messenger, 0);
    properties = g_shopStatPropertyNames;
    caps = g_shopStatCaps;
    fonts = g_shopStatValueFonts;
    property = properties.names;
    cap = caps.caps;
    font = fonts.names;
    i = 0;
    do {
        value = igProperty_GetRecord(player, *property)->value;
        {
            int rest = (value - 45) % 5;
            int cost = (value - 45 - rest) / 5 + (rest ? 1 : 0);
            cost = cost > 400 ? 400 : (cost < 0 ? 1 : cost);
            if (value >= *cap)
                sprintf(text, dashdashdashdash_3, cost);
            else
                sprintf(text, percent_d_6, cost);
        }
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
        beMessenger_AppendString(self->_messenger, STWINFONT19);
        beMessenger_AppendString(self->_messenger, *font);
        beMessenger_AppendString(self->_messenger, text);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET_4);
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
        beMessenger_AppendString(self->_messenger, STWINFONT14_3);
        beMessenger_AppendString(self->_messenger, *font);
        if (value >= *cap) {
            color[0] = 0.9f;
            color[1] = 0.4f;
            color[2] = 0.2f;
            beMessenger_AppendVec3(self->_messenger, color);
            beMessenger_DispatchSelected(self->_messenger, COLOR_2);
        } else {
            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_4);
        }
        i++; property++; cap++; font++;
    } while (i < 7);
}

void beNDMWShopSelect34_Setup(beNDMWShopSelect34 *self) {
    char slot[16];
    int i;
    i = 0;
    do {
        switch (self->_entCode) {
        case 3:
            sprintf(slot, font_03d_3, i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, STWINFONT28_2);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, CENTER_3);
            beMessenger_DispatchSelected(self->_messenger, ALIGN_4);
            break;
        default:
            sprintf(slot, font_03d_3, i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, STWINFONT25_2);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, CENTER_3);
            beMessenger_DispatchSelected(self->_messenger, ALIGN_4);
            sprintf(slot, font01_d_2, i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, STWINFONT25_2);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, CENTER_3);
            beMessenger_DispatchSelected(self->_messenger, ALIGN_4);
            sprintf(slot, font02_d_2, i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, STWINFONT25_2);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, CENTER_3);
            beMessenger_DispatchSelected(self->_messenger, ALIGN_4);
            break;
        }
        i++;
    } while (i < 7);
    SET_INFO_NAME(self, i_stcursor03_3)
    self->_selectMax = 7;
    self->_startPoint = 6;
    self->_isNoCancel = 0;
    switch (self->_entCode) {
    case 2:
    case 0:
        self->_offsetPos[0] = -20.0f;
        self->_offsetPos[1] = 138.0f;
        self->_offsetPos[2] = 0;
        break;
    case 1:
        self->_offsetPos[0] = -20.0f;
        self->_offsetPos[1] = -1.0f;
        self->_offsetPos[2] = 0;
        break;
    case 3:
        self->_offsetPos[0] = 147.0f;
        self->_offsetPos[1] = -2.0f;
        self->_offsetPos[2] = 0;
        break;
    }
}

/* Hides the seven STWINFONT25 digit slots, then shows `value` right-aligned in them. */
void beNDMWShopCtrlEditBit_ShowValueDigits(beNDMWShopCtrlEditBit *self, int mode, int value) {
    char slot[16];
    char digits[12];
    char digit[2];
    const char *slotFormat;
    int length;
    int i;
    int pos;

    switch (mode) {
    default:
        slotFormat = font01_d_2;
        break;
    case 1:
        slotFormat = font_03d_3;
        break;
    }
    i = 0;
    do {
        sprintf(slot, slotFormat, i);
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
        beMessenger_AppendString(self->_messenger, STWINFONT25_2);
        beMessenger_AppendString(self->_messenger, slot);
        beMessenger_AppendString(self->_messenger, DISPOFF_3);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_5);
        i += 1;
    } while (i < 7);
    sprintf(digits, percent_d_6, value);
    length = strlen(digits);
    pos = length - 1;
    digit[1] = 0;
    if (pos > -1) {
        do {
            sprintf(slot, slotFormat, pos);
            digit[0] = digits[(length - 1) - pos];
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, STWINFONT25_2);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, digit);
            beMessenger_DispatchSelected(self->_messenger, TEXTSET_4);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, STWINFONT25_2);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, DISPON_4);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_5);
            pos -= 1;
        } while (pos > -1);
    }
}

/* Hides the seven digit slots named by `slotFormat`, then shows `value` zero-padded to
 * `digits` places (1..7; 0 or more leaves them hidden). */
void beNDMWWindow_ShowPaddedDigits(beNDMWWindow *self, int value, unsigned int digits, const char *slotFormat) {
    char slot[16];
    char text[12];
    char digit[2];
    char *type;
    int i, length;

    if (self->_entCode == 3) {
        type = STWINFONT28_2;
    } else {
        type = STWINFONT25_2;
    }
    i = 0;
    do {
        sprintf(slot, slotFormat, i);
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
        beMessenger_AppendString(self->_messenger, type);
        beMessenger_AppendString(self->_messenger, slot);
        beMessenger_AppendString(self->_messenger, DISPOFF_3);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_5);
        i++;
    } while (i < 7);
    switch (digits) {
    case 0: return;
    case 1: sprintf(text, percent_d_6, value); break;
    case 2: sprintf(text, percent_02d, value); break;
    case 3: sprintf(text, percent_03d, value); break;
    case 4: sprintf(text, percent_04d, value); break;
    case 5: sprintf(text, percent_05d, value); break;
    case 6: sprintf(text, percent_06d, value); break;
    case 7: sprintf(text, percent_07d, value); break;
    default: return;
    }
    length = strlen(text);
    i = length - 1;
    digit[1] = 0;
    if (i > -1) {
        do {
            sprintf(slot, slotFormat, i);
            digit[0] = text[(length - 1) - i];
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, type);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, digit);
            beMessenger_DispatchSelected(self->_messenger, TEXTSET_4);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
            beMessenger_AppendString(self->_messenger, type);
            beMessenger_AppendString(self->_messenger, slot);
            beMessenger_AppendString(self->_messenger, DISPON_4);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_5);
            i--;
        } while (i > -1);
    }
}

void beNDMWShopSelect52_Setup(beNDMWShopSelect52 *self) {
    SET_INFO_NAME(self, i_stcursor05)
    self->_selectMax = self->_entCode;
    self->_startPoint = self->_entCode - 1;
    self->_isNoCancel = 0;
}

void beNDMWShopSelectA0_Setup(beNDMWShopSelectA0 *self) {
    beNDMWWindow_PresentModelAtOrigin(self, j_shcardwin_2, 0, SQ_OPEN_7, SQ_CLOSE_8);
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT34)
    INTERN_APPEND(self->_textCloseNameList, font000_4)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT34)
    INTERN_APPEND(self->_textCloseNameList, font001_4)
    beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, 0x7D1);
    beNDMWWindow_QueueText(self, STWINFONT33_2, font000_4, space_3, CENTER_3);
    beNDMWWindow_QueueText(self, STWINFONT33_2, font001_4, space_3, CENTER_3);
    SET_INFO_NAME(self, j_shcardcursor)
    self->_selectMax = 9;
    self->_offsetPos[0] = 0;
    self->_offsetPos[1] = 0;
    self->_offsetPos[2] = 0;
    self->_startPoint = 0;
    self->_isNoCancel = 0;
}

/* The selector's decision flags: one byte per row, nonzero when the row can be chosen. */
static inline igDataList *beNDMWShopSelectB0_DecideFlags(const beNDMWShopSelectB0 *self) { return (igDataList *)self->_decideList; }

void beNDMWShopSelectB0_Setup(beNDMWShopSelectB0 *self) {
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
    INTERN_APPEND(self->_textCloseNameList, font100_4)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
    INTERN_APPEND(self->_textCloseNameList, font000_4)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT29_4)
    INTERN_APPEND(self->_textCloseNameList, font001_4)
    beNDMWWindow_RunMessageScript(self, txt_shop_lua_3, 0x625);
    if (self->_decideList != 0) {
        int i;
        const char **font;
        DecideFontPair rowFonts = g_shopDecideFlagFonts;
        font = rowFonts.fonts;
        i = 0;
        if (0 < beNDMWShopSelectB0_DecideFlags(self)->_count) {
            do {
                const char *color;
                if (((unsigned char *)(((igDataList *)self->_decideList)->_data + i))[0] != 0 /* matching construct: int _data + i keeps retail addu operand order */) {
                    color = DEFAULTCOLOR_4;
                } else {
                    color = CANCELCOLOR_3;
                }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_6);
                beMessenger_AppendString(self->_messenger, STWINFONT29_4);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_DispatchSelected(self->_messenger, color);
                i++;
                font++;
            } while (i < ((igDataList *)self->_decideList)->_count);
        }
    }
    SET_INFO_NAME(self, i_stmesscr_2)
    self->_selectMax = 2;
    self->_offsetPos[0] = 0;
    self->_offsetPos[1] = 0;
    self->_offsetPos[2] = 0;
    self->_startPoint = 0;
    self->_isNoCancel = 0;
}

int beNDMWShopSelectB0_GetMeta(void) {
    return g_beNDMWShopSelectB0_metaObject[0];
}

int beNDMWShopSelectA0_GetMeta(void) {
    return g_beNDMWShopSelectA0_metaObject[0];
}

int beNDMWShopSelect52_GetMeta(void) {
    return g_beNDMWShopSelect52_metaObject[0];
}

int beNDMWShopSelect34_GetMeta(void) {
    return g_beNDMWShopSelect34_metaObject[0];
}

int beNDMWShopSelect11_GetMeta(void) {
    return g_beNDMWShopSelect11_metaObject[0];
}

int beNDMWShopSelect03_GetMeta(void) {
    return g_beNDMWShopSelect03_metaObject[0];
}

int beNDMWShopSelect02_GetMeta(void) {
    return g_beNDMWShopSelect02_metaObject[0];
}

int beNDMWShopSelect01_GetMeta(void) {
    return g_beNDMWShopSelect01_metaObject[0];
}

int beNDMWShopSelect00_GetMeta(void) {
    return g_beNDMWShopSelect00_metaObject[0];
}

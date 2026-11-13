/* The title windows of the status screens: the shared beNDMWWindowTitle update, and the model and
 * text setup of beNDMWStatusTitle00..04 (background, Digimon face, account and title plates). */
#include "dw4/reflected.h"

extern "C" void beNDMWWindow_ClearQueuedText(beNDMWWindow *self);
extern "C" void beNDMWWindow_PlayQueuedModelClose(...);
extern "C" int beNDMWWindow_PollCloseComplete(...);
extern "C" void beNDMWWindow_RequestChildrenClose(beNDMWWindow *self);
extern "C" void beNDMWWindow_PresentModel(beNDMWWindow *self, const char *model, int id, const char *sequence,
                                          const char *close, float *position);
extern "C" void beNDMWWindow_PresentModelAtOrigin(void *self, const char *model, int id, const char *sequence,
                                                  const char *close);
extern "C" void beNDMWWindow_RunMessageScript(void *self, const char *chunk, int callNo);
extern "C" void *StringPool_Allocate(int size);
extern "C" void *StringPool_Construct(void *pool);
extern "C" const char *StringPool_Intern(void *pool, const char *text);
extern "C" void StringChunk_ReleaseHeader(int chunk, int *header);
extern "C" void beMessenger_SelectGroup(int messenger, const char *group);
extern "C" void beMessenger_AppendInt(int messenger, int value);
extern "C" void beMessenger_AppendString(int messenger, const char *text);
extern "C" void beMessenger_DispatchSelected(int messenger, const char *name);
extern "C" int beMessenger_GetObject(int messenger, int index);
extern "C" beDataObjInt *igProperty_GetRecord(int record, const char *name);

extern "C" void *g_stringPool[4];

extern "C" char i_stback_2[];
extern "C" char SQ_OPEN_9[];
extern "C" char SQ_CLOSE_9[];
extern "C" char i_bgclear[];
extern "C" char STWINFONT06_2[];
extern "C" char font000_6[];
extern "C" char STWINFONT04_2[];
extern "C" char font001_6[];
extern "C" char txt_status_lua_3[];
extern "C" char SUBWND_4[];
extern "C" char UPDATE_2[];
extern "C" char GAMERAM_11[];
extern "C" char GETPLAYER_9[];
extern "C" char DIGIMONNO_5[];
extern "C" char SQ_agumonOPEN[];
extern "C" char SQ_vmonOPEN[];
extern "C" char SQ_girumonOPEN[];
extern "C" char SQ_dorumonOPEN[];
extern "C" char SQ_weregaruOPEN[];
extern "C" char SQ_hekabutOPEN[];
extern "C" char SQ_wargreyOPEN[];
extern "C" char SQ_angelrOPEN[];
extern "C" char SQ_beelzebOPEN[];
extern "C" char SQ_alphaOPEN[];
extern "C" char SQ_bwargreyOPEN[];
extern "C" char SQ_impdrafmOPEN[];
extern "C" char SQ_impdrapmOPEN[];
extern "C" char SQ_metalgaruOPEN[];
extern "C" char SQ_dukecrimOPEN[];
extern "C" char SQ_susanooOPEN[];
extern "C" char i_stdigiface[];
extern "C" char i_stbase[];
extern "C" char SQ_LOPEN[];
extern "C" char TEXTCTL_8[];
extern "C" char DISPON_5[];
extern "C" char SWITCH_6[];
extern "C" char j_shbase[];
extern "C" char DISPOFF_5[];
extern "C" char i_messwn_2[];
extern "C" char SQ_STOPEN_2[];
extern "C" char SQ_STCLOSE[];
extern "C" char i_staccount[];
extern "C" char STWINFONT34_3[];
extern "C" char font002_5[];
extern "C" char DEFAULTCOLOR_6[];
extern "C" char CANCELCOLOR_5[];
extern "C" char i_sttitle_2[];
extern "C" char STWINFONT12_2[];

/* A null-terminated list of the STWINFONT06 text elements a layout switches (font030..font071). */
typedef struct FontNameList { const char *name[29]; } FontNameList;
extern "C" FontNameList g_statusLayoutFontNames;
extern "C" FontNameList g_shopLayoutFontNames;

/* matching construct: dummy-virtual view (22 slots) so Setup() compiles to the retail vtable call
 * through slot 22, the per-title model setup; it carries no data. */
class beNDMWWindowTitleVirtuals { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void Setup(); };

static inline void *SharedStringPool() {
    if (g_stringPool[0] == 0) {
        void *pool = StringPool_Allocate(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return g_stringPool[0];
}

/* Drops one reference to a pooled string token (reference count at p[-1], chunk header at p[-2]). */
static inline void ReleaseToken(int *p) {
    if (p != 0) {
        int *header = p - 2;
        int refs = p[-1] - 1;
        p[-1] = refs;
        if (refs == 0) StringChunk_ReleaseHeader(*header, header);
    }
}

/* Owning stack reference to a pooled string token: releases it on scope exit; Set() drops the held
 * token for a new one. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    void Set(int *t) { int *cur = p; ReleaseToken(cur); p = t; }
};
extern "C" int StringList_AppendRetained(int list, StringRef *text);

/* The pooled copy of `text` (null for null), creating the string pool on first use. */
static inline int *InternString(const char *text) {
    if (text == 0) return 0;
    return (int *)StringPool_Intern(SharedStringPool(), text);
}

/* InternString for a text that is never null. */
static inline int *InternLiteral(const char *text) {
    return (int *)StringPool_Intern(SharedStringPool(), text);
}

/* Appends the pooled copy of `text` to a string list, which takes its own reference. */
static inline void AppendInterned(const int &list, const char *text) {
    StringRef held(InternString(text));
    StringList_AppendRetained(list, &held);
}

/* Empties a string list: every slot is pointed at the pooled empty string, releasing the string it
 * held. */
static inline void ClearStringList(igStringRefList *list) {
    int count = list->_count;
    for (int i = 0; i < count; i++) {
        int **slot = &((int **)list->_data)[i];
        int *blank = (int *)StringPool_Intern(SharedStringPool(), 0);
        ReleaseToken(*slot);
        *slot = blank;
    }
    list->_count = 0;
}

/* Shared title update: st0 0 runs the title's Setup, 2 plays the queued closes and asks the children
 * to close, 3 waits for the close to finish and ends the run. */
extern "C" void Gap__Bec__beNDMWWindowTitle__vfunc_21(beNDMWWindowTitle *self) {
    switch (self->_st0) {
    case 0:
        ((beNDMWWindowTitleVirtuals *)self)->Setup();
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        break;
    case 1:
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        break;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Status background: the back plate and the background clear. */
extern "C" void Gap__Bec__beNDMWStatusTitle00__vfunc_22(beNDMWStatusTitle00 *self) {
    beNDMWWindow_PresentModelAtOrigin(self, i_stback_2, 0, SQ_OPEN_9, SQ_CLOSE_9);
    beNDMWWindow_PresentModelAtOrigin(self, i_bgclear, 0, SQ_OPEN_9, SQ_CLOSE_9);
}

/* Replaces the window's queued model closes with the face of the current player's Digimon: plays
 * and empties the close lists, refreshes the sub-window and game RAM for the player, then presents
 * i_stdigiface opening on the sequence of that Digimon (DIGIMONNO 0..15; anything else Agumon). */
extern "C" void beNDMWStatusTitle01_ShowDigimonFace(beNDMWWindow *self) {
    float position[3];
    unsigned int digimonNo;
    int player;

    beNDMWWindow_PlayQueuedModelClose(self);
    ClearStringList((igStringRefList *)self->_modelCloseInfoNameList);
    ((igIntList *)self->_modelCloseRamNoList)->_count = 0;
    ClearStringList((igStringRefList *)self->_modelCloseSeqNameList);
    beMessenger_SelectGroup(self->_messenger, SUBWND_4);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, UPDATE_2);
    beMessenger_SelectGroup(self->_messenger, GAMERAM_11);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_9);
    player = beMessenger_GetObject(self->_messenger, 0);
    {
        StringRef sequence(0);
        digimonNo = igProperty_GetRecord(player, DIGIMONNO_5)->_data;
        switch (digimonNo) {
        default: sequence.Set(InternLiteral(SQ_agumonOPEN)); break;
        case 1:  sequence.Set(InternLiteral(SQ_vmonOPEN)); break;
        case 2:  sequence.Set(InternLiteral(SQ_girumonOPEN)); break;
        case 3:  sequence.Set(InternLiteral(SQ_dorumonOPEN)); break;
        case 4:  sequence.Set(InternLiteral(SQ_weregaruOPEN)); break;
        case 5:  sequence.Set(InternLiteral(SQ_hekabutOPEN)); break;
        case 6:  sequence.Set(InternLiteral(SQ_wargreyOPEN)); break;
        case 7:  sequence.Set(InternLiteral(SQ_angelrOPEN)); break;
        case 8:  sequence.Set(InternLiteral(SQ_beelzebOPEN)); break;
        case 9:  sequence.Set(InternLiteral(SQ_alphaOPEN)); break;
        case 10: sequence.Set(InternLiteral(SQ_bwargreyOPEN)); break;
        case 11: sequence.Set(InternLiteral(SQ_impdrafmOPEN)); break;
        case 12: sequence.Set(InternLiteral(SQ_impdrapmOPEN)); break;
        case 13: sequence.Set(InternLiteral(SQ_metalgaruOPEN)); break;
        case 14: sequence.Set(InternLiteral(SQ_dukecrimOPEN)); break;
        case 15: sequence.Set(InternLiteral(SQ_susanooOPEN)); break;
        }
        position[2] = 0.0f;
        position[0] = -410.0f;
        position[1] = 240.0f;
        beNDMWWindow_PresentModel(self, i_stdigiface, self->_playerNo, (const char *)sequence.p, SQ_CLOSE_9,
                                  position);
    }
}

/* Status layout: the Digimon face and the status base plate, with every layout font shown and the
 * STWINFONT04 font001 element shown. */
extern "C" void beNDMWStatusTitle01_ShowStatusLayout(beNDMWStatusTitle01 *self) {
    FontNameList fonts;
    const char **font;
    beNDMWStatusTitle01_ShowDigimonFace((beNDMWWindow *)self);
    beNDMWWindow_PresentModelAtOrigin(self, i_stbase, self->_playerNo, SQ_LOPEN, SQ_CLOSE_9);
    fonts = g_statusLayoutFontNames;
    font = fonts.name;
    if (*font != 0) {
        do {
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_8);
            beMessenger_AppendString(self->_messenger, STWINFONT06_2);
            beMessenger_AppendString(self->_messenger, *font);
            beMessenger_AppendString(self->_messenger, DISPON_5);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_6);
            font++;
        } while (*font != 0);
    }
    beMessenger_SelectGroup(self->_messenger, TEXTCTL_8);
    beMessenger_AppendString(self->_messenger, STWINFONT04_2);
    beMessenger_AppendString(self->_messenger, font001_6);
    beMessenger_AppendString(self->_messenger, DISPON_5);
    beMessenger_DispatchSelected(self->_messenger, SWITCH_6);
}

/* Shop layout: the Digimon face on the shop base plate, with every layout font and the STWINFONT04
 * font001 element hidden. */
extern "C" void beNDMWStatusTitle01_ShowShopLayout(beNDMWStatusTitle01 *self) {
    FontNameList fonts;
    const char **font;
    beNDMWStatusTitle01_ShowDigimonFace((beNDMWWindow *)self);
    beNDMWWindow_PresentModelAtOrigin(self, j_shbase, self->_playerNo, SQ_OPEN_9, SQ_CLOSE_9);
    fonts = g_shopLayoutFontNames;
    font = fonts.name;
    if (fonts.name[0] != 0) {
        do {
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_8);
            beMessenger_AppendString(self->_messenger, STWINFONT06_2);
            beMessenger_AppendString(self->_messenger, *font);
            beMessenger_AppendString(self->_messenger, DISPOFF_5);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_6);
            font += 1;
        } while (*font != 0);
    }
    beMessenger_SelectGroup(self->_messenger, TEXTCTL_8);
    beMessenger_AppendString(self->_messenger, STWINFONT04_2);
    beMessenger_AppendString(self->_messenger, font001_6);
    beMessenger_AppendString(self->_messenger, DISPOFF_5);
    beMessenger_DispatchSelected(self->_messenger, SWITCH_6);
}

/* Message window plate. */
extern "C" void Gap__Bec__beNDMWStatusTitle02__vfunc_22(beNDMWStatusTitle02 *self) {
    beNDMWWindow_PresentModelAtOrigin(self, i_messwn_2, 0, SQ_STOPEN_2, SQ_STCLOSE);
}

/* Button-guide plate: queues its three STWINFONT34 texts (font000 Select, font001 Confirm, font002
 * Cancel) for closing and runs txt_status.lua call 0, which fills them. */
extern "C" void Gap__Bec__beNDMWStatusTitle03__vfunc_22(beNDMWStatusTitle03 *self) {
    beNDMWWindow_PresentModelAtOrigin(self, i_staccount, 0, SQ_OPEN_9, SQ_CLOSE_9);
    AppendInterned(self->_textCloseTypeList, STWINFONT34_3);
    AppendInterned(self->_textCloseNameList, font000_6);
    AppendInterned(self->_textCloseTypeList, STWINFONT34_3);
    AppendInterned(self->_textCloseNameList, font001_6);
    AppendInterned(self->_textCloseTypeList, STWINFONT34_3);
    AppendInterned(self->_textCloseNameList, font002_5);
    beNDMWWindow_RunMessageScript(self, txt_status_lua_3, 0);
}

/* Colours the plate's Cancel prompt (font002): DEFAULTCOLOR when enabled, CANCELCOLOR otherwise. */
extern "C" void beNDMWStatusTitle03_SetCancelPromptEnabled(beNDMWStatusTitle03 *self, int enabled) {
    beMessenger_SelectGroup(self->_messenger, TEXTCTL_8);
    beMessenger_AppendString(self->_messenger, STWINFONT34_3);
    beMessenger_AppendString(self->_messenger, font002_5);
    if (enabled != 0) {
        beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_6);
        return;
    }
    beMessenger_DispatchSelected(self->_messenger, CANCELCOLOR_5);
}

/* Title plate: queues its STWINFONT12 font000 text for closing and runs txt_status.lua with the
 * window's entry code as the call number. */
extern "C" void Gap__Bec__beNDMWStatusTitle04__vfunc_22(beNDMWStatusTitle04 *self) {
    beNDMWWindow_PresentModelAtOrigin(self, i_sttitle_2, 0, SQ_OPEN_9, SQ_CLOSE_9);
    AppendInterned(self->_textCloseTypeList, STWINFONT12_2);
    AppendInterned(self->_textCloseNameList, font000_6);
    beNDMWWindow_RunMessageScript(self, txt_status_lua_3, self->_entCode);
}

extern "C" int g_beNDMWStatusTitle04_metaObject[4];
extern "C" int g_beNDMWStatusTitle03_metaObject[4];
extern "C" int g_beNDMWStatusTitle02_metaObject[4];
extern "C" int g_beNDMWStatusTitle01_metaObject[4];
extern "C" int g_beNDMWStatusTitle00_metaObject[4];
extern "C" int g_beNDMWWindowTitle_metaObject[4];

/* vfunc_20 of each title class returns its class meta object. */
extern "C" int Gap__Bec__beNDMWStatusTitle04__vfunc_20(void) { return g_beNDMWStatusTitle04_metaObject[0]; }
extern "C" int Gap__Bec__beNDMWStatusTitle03__vfunc_20(void) { return g_beNDMWStatusTitle03_metaObject[0]; }
extern "C" int Gap__Bec__beNDMWStatusTitle02__vfunc_20(void) { return g_beNDMWStatusTitle02_metaObject[0]; }
extern "C" int Gap__Bec__beNDMWStatusTitle01__vfunc_20(void) { return g_beNDMWStatusTitle01_metaObject[0]; }
extern "C" int Gap__Bec__beNDMWStatusTitle00__vfunc_20(void) { return g_beNDMWStatusTitle00_metaObject[0]; }
extern "C" int Gap__Bec__beNDMWWindowTitle__vfunc_20(void) { return g_beNDMWWindowTitle_metaObject[0]; }

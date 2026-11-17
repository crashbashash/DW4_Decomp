#include "dw4/reflected.h"
#include "dw4/beNDMWWindowSelect.h"
#include "dw4/beNDMWWindowSetupDispatchView.h"
#include "dw4/StringPool.h"
#include "dw4/beMessenger.h"
#include "dw4/beNDMWStatusSelect00.h"
#include "dw4/beNDMWStatusSelect01.h"
#include "dw4/beNDMWStatusSelectE0.h"
#include "dw4/beNDMWStatusSelectE1.h"
#include "dw4/beNDMWWindow.h"
#include "dw4/list-services.h"

extern "C" char SELECTCTRL[];
extern "C" char NOCANCEL[];
extern "C" char GENERATE_4[];
extern "C" char GETSELECT[];
extern "C" char ISEND[];
extern "C" char FO2TOP[];
extern "C" char ISFO2TOP[];
extern "C" char i_stmenu01[];
extern "C" char SQ_3LINEUPOPEN[];
extern "C" char SQ_3LINEDOWNOPEN[];
extern "C" char SQ_4LINEOPEN[];
extern "C" char SQ_CLOSE_4[];
extern "C" char STWINFONT08[];
extern "C" char STWINFONT09[];
extern "C" char STWINFONT29_2[];
extern "C" char font000[];
extern "C" char font001[];
extern "C" char font002[];
extern "C" char font003[];
extern "C" char font100[];
extern "C" char txt_status_lua[];
extern "C" char i_stcursor01[];
extern "C" char i_stcursor02[];
extern "C" char i_stmesscr[];

/* The pooled-string singleton, created on first use. */
static inline StringPool *StringPool_Get(void) {
    if (g_stringPool == 0) {
        StringPool *pool = (StringPool *)StringPool_Allocate(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool = pool;
    }
    return g_stringPool;
}

/* Drops one share of a pooled string token (reference count at token[-1], chunk header at token[-2]). */
static inline void StringToken_Release(char *token) {
    if (token != 0) {
        int *header = (int *)token - 2;
        int refs = ((int *)token)[-1] - 1;
        ((int *)token)[-1] = refs;
        if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
    }
}

/* Owning stack reference to a pooled string token; releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    /* take a freshly interned token, dropping the share of the previous one */
    void Assign(char *fresh) { StringToken_Release(p); p = fresh; }
    ~StringRef() { StringToken_Release(p); }
};

/* Appends a pooled copy of `text` to a window string list; a null text appends a null token. */
#define INTERN_APPEND(list, text) { \
    char *token; \
    if ((text) == 0) { \
        token = 0; \
    } else { \
        token = StringPool_Intern(StringPool_Get(), (text)); \
    } \
    StringRef held(token); \
    StringList_AppendRetained((igStringRefList *)(list), &held.p); }

extern "C" void beNDMWWindowSelect_Update(beNDMWWindowSetupDispatchView *self);
extern "C" void beNDMWStatusSelect00_Setup(beNDMWStatusSelect00 *self);
extern "C" void beNDMWStatusSelect01_Setup(beNDMWStatusSelect01 *self);
extern "C" void beNDMWStatusSelectE0_Setup(beNDMWStatusSelectE0 *self);
extern "C" void beNDMWStatusSelectE1_Setup(beNDMWStatusSelectE1 *self);
extern "C" int beNDMWStatusSelectE1_GetMeta(void);
extern "C" int beNDMWStatusSelectE0_GetMeta(void);
extern "C" int beNDMWStatusSelect01_GetMeta(void);
extern "C" int beNDMWStatusSelect00_GetMeta(void);
extern "C" int beNDMWWindowSelect_GetMeta(void);

#pragma push
#pragma readonly_strings on

void beNDMWWindowSelect_Update(beNDMWWindowSetupDispatchView *view) {
    /* matching construct: typed view of the dummy-virtual receiver; data is reached only through s. */
    beNDMWWindowSelect *s = (beNDMWWindowSelect *)view;
    float offset[3];
    int i;
    igDataList *decide;
    switch (s->_st0) {
    case 0:
        view->Setup();
        beMessenger_SelectReceivers((beMessenger *)s->_messenger, SELECTCTRL, (const char *)s->_infoName, s->_playerNo);
        beMessenger_AppendInt((beMessenger *)s->_messenger, s->_selectMax);
        beMessenger_AppendInt((beMessenger *)s->_messenger, s->_startPoint);
        offset[0] = s->_offsetPos[0];
        offset[1] = s->_offsetPos[1];
        offset[2] = s->_offsetPos[2];
        beMessenger_AppendVec3((beMessenger *)s->_messenger, offset);
        if (s->_isNoCancel != 0) {
            beMessenger_AppendString((beMessenger *)s->_messenger, NOCANCEL);
        }
        decide = *(igDataList **)&s->_decideList; /* matching construct: reading the field as a pointer lvalue keeps the loop's per-pass reloads */
        if (decide != 0) {
            i = 0;
            if (0 < decide->_count) {
                do {
                    beMessenger_AppendBool((beMessenger *)s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                    i++;
                } while (i < ((igDataList *)s->_decideList)->_count);
            }
        }
        beMessenger_DispatchSelected((beMessenger *)s->_messenger, GENERATE_4);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 1:
        beMessenger_SendNamed((beMessenger *)s->_messenger, SELECTCTRL, (const char *)s->_infoName, s->_playerNo, GETSELECT);
        ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt((beMessenger *)s->_messenger, 0);
        beMessenger_SendNamed((beMessenger *)s->_messenger, SELECTCTRL, (const char *)s->_infoName, s->_playerNo, ISEND);
        if (beMessenger_GetBool((beMessenger *)s->_messenger, 0) == 0) {
            break;
        }
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 2:
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)s);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)s);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)s) != 0) {
            s->_isRun = 0;
        }
        break;
    case 4:
        if (beNDMWWindowSelect_CanRequestFO2TOP(s)) {
            beMessenger_SelectReceivers((beMessenger *)s->_messenger, SELECTCTRL, (const char *)s->_infoName, s->_playerNo);
            beMessenger_AppendInt((beMessenger *)s->_messenger, s->_selectMax);
            decide = *(igDataList **)&s->_decideList; /* matching construct: reading the field as a pointer lvalue keeps the loop's per-pass reloads */
            if (decide != 0) {
                i = 0;
                if (0 < decide->_count) {
                    do {
                        beMessenger_AppendBool((beMessenger *)s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                        i++;
                    } while (i < ((igDataList *)s->_decideList)->_count);
                }
            }
            beMessenger_DispatchSelected((beMessenger *)s->_messenger, FO2TOP);
            beMessenger_SendNamed((beMessenger *)s->_messenger, SELECTCTRL, (const char *)s->_infoName, s->_playerNo, GETSELECT);
            ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt((beMessenger *)s->_messenger, 0);
        }
        s->_st0 = 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
        break;
    }
}

bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self){
    beMessenger_SendNamed((beMessenger *)self->_messenger,SELECTCTRL,(const char *)self->_infoName,self->_playerNo,ISFO2TOP);
    return !beMessenger_GetBool((beMessenger *)self->_messenger,0);
}

void beNDMWStatusSelect00_Setup(beNDMWStatusSelect00 *self) {
    char *cursor;
    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu01, 0, SQ_3LINEUPOPEN, SQ_CLOSE_4);
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT08)
    INTERN_APPEND(self->_textCloseNameList, font000)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT08)
    INTERN_APPEND(self->_textCloseNameList, font001)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT08)
    INTERN_APPEND(self->_textCloseNameList, font002)
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua, 0xF);
    cursor = StringPool_Intern(StringPool_Get(), i_stcursor02);
    StringToken_Release((char *)self->_infoName);
    self->_infoName = (int)cursor;
    self->_selectMax = 3;
    self->_offsetPos[0] = -83.0f;
    self->_offsetPos[1] = 209.0f;
    self->_offsetPos[2] = 0.0f;
    self->_isNoCancel = 0;
}

void beNDMWStatusSelect01_Setup(beNDMWStatusSelect01 *self) {
    char *cursor;
    {
    /* the model sequence to open with: empty unless the entry code selects one */
    StringRef sequence(0);
    switch (self->_entCode) {
    case 0x1F:
    case 0x5B:
        sequence.Assign(StringPool_Intern(StringPool_Get(), SQ_3LINEDOWNOPEN));
        self->_selectMax = 3;
        break;
    case 0x3D:
        sequence.Assign(StringPool_Intern(StringPool_Get(), SQ_4LINEOPEN));
        self->_selectMax = 4;
        break;
    }
    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu01, 0, sequence.p, SQ_CLOSE_4);
    }
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_2, font100, " ", "LEFT");
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT09, font000, " ", "LEFT");
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT09, font001, " ", "LEFT");
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT09, font002, " ", "LEFT");
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT09, font003, " ", "LEFT");
    if (self->_entCode > 0) {
        beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua, self->_entCode);
    }
    cursor = StringPool_Intern(StringPool_Get(), i_stcursor02);
    StringToken_Release((char *)self->_infoName);
    self->_infoName = (int)cursor;
    self->_offsetPos[0] = -83.0f;
    self->_offsetPos[1] = 172.0f;
    self->_offsetPos[2] = 0.0f;
    self->_isNoCancel = 0;
}

void beNDMWStatusSelectE0_Setup(beNDMWStatusSelectE0 *self) {
    char *cursor;
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_2, font100, " ", "LEFT");
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_2, font000, " ", "LEFT");
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_2, font001, " ", "LEFT");
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_2, font002, " ", "LEFT");
    if (self->_entCode > 0) {
        beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua, self->_entCode);
    }
    cursor = StringPool_Intern(StringPool_Get(), i_stmesscr);
    StringToken_Release((char *)self->_infoName);
    self->_infoName = (int)cursor;
    self->_offsetPos[0] = 0;
    self->_offsetPos[1] = 0;
    self->_offsetPos[2] = 0;
    self->_startPoint = 0;
    self->_isNoCancel = 0;
}

void beNDMWStatusSelectE1_Setup(beNDMWStatusSelectE1 *self) {
    char *cursor = StringPool_Intern(StringPool_Get(), i_stcursor01);
    StringToken_Release((char *)self->_infoName);
    self->_infoName = (int)cursor;
    self->_isNoCancel = 0;
}

int beNDMWStatusSelectE1_GetMeta(void)
{
    return (int)g_beNDMWStatusSelectE1_metaObject;
}

int beNDMWStatusSelectE0_GetMeta(void)
{
    return (int)g_beNDMWStatusSelectE0_metaObject;
}

int beNDMWStatusSelect01_GetMeta(void)
{
    return (int)g_beNDMWStatusSelect01_metaObject;
}

int beNDMWStatusSelect00_GetMeta(void)
{
    return (int)g_beNDMWStatusSelect00_metaObject;
}

int beNDMWWindowSelect_GetMeta(void)
{
    return (int)g_beNDMWWindowSelect_metaObject;
}

#pragma pop

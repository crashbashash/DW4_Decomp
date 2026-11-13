#include "dw4/reflected.h"

extern "C" int beMessenger_AppendBool(int messenger, int value);
extern "C" int beMessenger_AppendInt(int messenger, int value);
extern "C" int beMessenger_AppendString(int messenger, const char *text);
extern "C" int beMessenger_AppendVec3(int messenger, float *vec);
extern "C" int beMessenger_DispatchSelected(int messenger, const char *message);
extern "C" int beMessenger_GetBool(int messenger, int index);
extern "C" int beMessenger_GetInt(int messenger, int index);
extern "C" int beMessenger_SelectReceivers(int messenger, const char *type, int name, int playerNo);
extern "C" int beMessenger_SendNamed(int messenger, const char *type, int name, int playerNo, const char *message);
extern "C" void *StringPool_Allocate(int size);
extern "C" void *StringPool_Construct(void *pool);
extern "C" char *StringPool_Intern(void *pool, const char *text);
extern "C" int StringChunk_ReleaseHeader(int chunk, int *header);
extern "C" void *g_stringPool[4];

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
extern "C" char single_space[];
extern "C" char LEFT[];
extern "C" char txt_status_lua[];
extern "C" char i_stcursor01[];
extern "C" char i_stcursor02[];
extern "C" char i_stmesscr[];

extern "C" int g_beNDMWStatusSelectE1_metaObject[4];
extern "C" int g_beNDMWStatusSelectE0_metaObject[4];
extern "C" int g_beNDMWStatusSelect01_metaObject[4];
extern "C" int g_beNDMWStatusSelect00_metaObject[4];
extern "C" int g_beNDMWWindowSelect_metaObject[4];

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
    /* take a freshly interned token, dropping the share of the previous one */
    void Assign(char *fresh) { StringToken_Release(p); p = fresh; }
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

/* matching construct: dummy-virtual view (22 slots) so Setup() compiles to the retail vtable call; it carries no data. */
class beNDMWWindowSelectVirtuals { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void Setup();
 };
extern "C" int beNDMWWindow_ClearQueuedText(beNDMWWindowSelect *self);
extern "C" int beNDMWWindow_PlayQueuedModelClose(beNDMWWindowSelect *self);
extern "C" int beNDMWWindow_PollCloseComplete(beNDMWWindowSelect *self);
extern "C" int beNDMWWindow_PresentModelAtOrigin(void *self, const char *model, int id, const char *sequence, const char *close);
extern "C" int beNDMWWindow_RunMessageScript(void *self, const char *script, int entCode);
extern "C" int beNDMWWindow_QueueText(void *self, const char *type, const char *name, const char *text, const char *align);
extern "C" void beNDMWWindowSelect_Update(beNDMWWindowSelectVirtuals *self);
extern "C" bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self);
extern "C" void beNDMWStatusSelect00_Setup(beNDMWStatusSelect00 *self);
extern "C" void beNDMWStatusSelect01_Setup(beNDMWStatusSelect01 *self);
extern "C" void beNDMWStatusSelectE0_Setup(beNDMWStatusSelectE0 *self);
extern "C" void beNDMWStatusSelectE1_Setup(beNDMWStatusSelectE1 *self);
extern "C" int beNDMWStatusSelectE1_GetMeta(void);
extern "C" int beNDMWStatusSelectE0_GetMeta(void);
extern "C" int beNDMWStatusSelect01_GetMeta(void);
extern "C" int beNDMWStatusSelect00_GetMeta(void);
extern "C" int beNDMWWindowSelect_GetMeta(void);

void beNDMWWindowSelect_Update(beNDMWWindowSelectVirtuals *view) {
    /* matching construct: typed view of the dummy-virtual receiver; data is reached only through s. */
    beNDMWWindowSelect *s = (beNDMWWindowSelect *)view;
    float offset[3];
    int i;
    igDataList *decide;
    switch (s->_st0) {
    case 0:
        view->Setup();
        beMessenger_SelectReceivers(s->_messenger, SELECTCTRL, s->_infoName, s->_playerNo);
        beMessenger_AppendInt(s->_messenger, s->_selectMax);
        beMessenger_AppendInt(s->_messenger, s->_startPoint);
        offset[0] = s->_offsetPos[0];
        offset[1] = s->_offsetPos[1];
        offset[2] = s->_offsetPos[2];
        beMessenger_AppendVec3(s->_messenger, offset);
        if (s->_isNoCancel != 0) {
            beMessenger_AppendString(s->_messenger, NOCANCEL);
        }
        decide = *(igDataList **)&s->_decideList; /* matching construct: reading the field as a pointer lvalue keeps the loop's per-pass reloads */
        if (decide != 0) {
            i = 0;
            if (0 < decide->_count) {
                do {
                    beMessenger_AppendBool(s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                    i++;
                } while (i < ((igDataList *)s->_decideList)->_count);
            }
        }
        beMessenger_DispatchSelected(s->_messenger, GENERATE_4);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 1:
        beMessenger_SendNamed(s->_messenger, SELECTCTRL, s->_infoName, s->_playerNo, GETSELECT);
        ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt(s->_messenger, 0);
        beMessenger_SendNamed(s->_messenger, SELECTCTRL, s->_infoName, s->_playerNo, ISEND);
        if ((beMessenger_GetBool(s->_messenger, 0) & 0xFF) == 0) {
            break;
        }
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(s);
        beNDMWWindow_ClearQueuedText(s);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 3:
        if (beNDMWWindow_PollCloseComplete(s) != 0) {
            s->_isRun = 0;
        }
        break;
    case 4:
        if (beNDMWWindowSelect_CanRequestFO2TOP(s)) {
            beMessenger_SelectReceivers(s->_messenger, SELECTCTRL, s->_infoName, s->_playerNo);
            beMessenger_AppendInt(s->_messenger, s->_selectMax);
            decide = *(igDataList **)&s->_decideList; /* matching construct: reading the field as a pointer lvalue keeps the loop's per-pass reloads */
            if (decide != 0) {
                i = 0;
                if (0 < decide->_count) {
                    do {
                        beMessenger_AppendBool(s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                        i++;
                    } while (i < ((igDataList *)s->_decideList)->_count);
                }
            }
            beMessenger_DispatchSelected(s->_messenger, FO2TOP);
            beMessenger_SendNamed(s->_messenger, SELECTCTRL, s->_infoName, s->_playerNo, GETSELECT);
            ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt(s->_messenger, 0);
        }
        s->_st0 = 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
        break;
    }
}

bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self){
    beMessenger_SendNamed(self->_messenger,SELECTCTRL,self->_infoName,self->_playerNo,ISFO2TOP);
    return !beMessenger_GetBool(self->_messenger,0);
}

void beNDMWStatusSelect00_Setup(beNDMWStatusSelect00 *self) {
    char *cursor;
    beNDMWWindow_PresentModelAtOrigin(self, i_stmenu01, 0, SQ_3LINEUPOPEN, SQ_CLOSE_4);
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT08)
    INTERN_APPEND(self->_textCloseNameList, font000)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT08)
    INTERN_APPEND(self->_textCloseNameList, font001)
    INTERN_APPEND(self->_textCloseTypeList, STWINFONT08)
    INTERN_APPEND(self->_textCloseNameList, font002)
    beNDMWWindow_RunMessageScript(self, txt_status_lua, 0xF);
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
    beNDMWWindow_PresentModelAtOrigin(self, i_stmenu01, 0, sequence.p, SQ_CLOSE_4);
    }
    beNDMWWindow_QueueText(self, STWINFONT29_2, font100, single_space, LEFT);
    beNDMWWindow_QueueText(self, STWINFONT09, font000, single_space, LEFT);
    beNDMWWindow_QueueText(self, STWINFONT09, font001, single_space, LEFT);
    beNDMWWindow_QueueText(self, STWINFONT09, font002, single_space, LEFT);
    beNDMWWindow_QueueText(self, STWINFONT09, font003, single_space, LEFT);
    if (self->_entCode > 0) {
        beNDMWWindow_RunMessageScript(self, txt_status_lua, self->_entCode);
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
    beNDMWWindow_QueueText(self, STWINFONT29_2, font100, single_space, LEFT);
    beNDMWWindow_QueueText(self, STWINFONT29_2, font000, single_space, LEFT);
    beNDMWWindow_QueueText(self, STWINFONT29_2, font001, single_space, LEFT);
    beNDMWWindow_QueueText(self, STWINFONT29_2, font002, single_space, LEFT);
    if (self->_entCode > 0) {
        beNDMWWindow_RunMessageScript(self, txt_status_lua, self->_entCode);
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
    return g_beNDMWStatusSelectE1_metaObject[0];
}

int beNDMWStatusSelectE0_GetMeta(void)
{
    return g_beNDMWStatusSelectE0_metaObject[0];
}

int beNDMWStatusSelect01_GetMeta(void)
{
    return g_beNDMWStatusSelect01_metaObject[0];
}

int beNDMWStatusSelect00_GetMeta(void)
{
    return g_beNDMWStatusSelect00_metaObject[0];
}

int beNDMWWindowSelect_GetMeta(void)
{
    return g_beNDMWWindowSelect_metaObject[0];
}

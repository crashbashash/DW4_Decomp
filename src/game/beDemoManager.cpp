#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/beDemoManager.h"

extern "C" {
int Memory_GetAllocatorBySelector(int selector);
int igObject_GetAllocator(void *object);
void ObjectList_AppendRetained(void *list, void *object);
int List_Reserve(igObjectList *list, int capacity, int elementSize);
void List_RemoveWordAt(void *list, int index);
void *StringPool_Allocate(int size);
void *StringPool_Construct(void *pool);
char *StringPool_Intern(void *pool, const char *text);
void StringChunk_ReleaseHeader(int owner, int *header);
int igInsightCore_FindManager(int insight, igMetaObject *meta);
void igInsightCore_AddToScheduler(int insight, void *object);
void igInsightCore_RemoveFromScheduler(int insight, void *object);
void beMessenger_SelectReceivers(beMessenger *self, const char *group, const char *infoName, int ramNo);
void beMessenger_DispatchSelected(beMessenger *self, const char *message);
void beMessenger_PrepareDelayedSelection(beMessenger *self, const char *group, const char *infoName, int ramNo);
void beMessenger_EnqueueSelected(beMessenger *self, const char *message, long long delay);
int beMessenger_GetBoolCount(beMessenger *self);
unsigned char beMessenger_GetBool(beMessenger *self, int index);
int beMessenger_GetIntCount(beMessenger *self);
int beMessenger_GetInt(beMessenger *self, int index);
void Lua_sd_OptionalArg(const char *args);
void beLua__RunNamedChunk(beLua *self, const char *chunk, int arg);
beDemoManagerWork *beDemoManagerWork_CreateInstance(int allocator);
beDemoKeepMes *beDemoKeepMes_CreateInstance(int allocator);
void beDemoManager_AddToScheduler(beDemoManager *self, int unused);
void beDemoManager_RemoveFromScheduler(beDemoManager *self, int unused);
void beDemoManager_Start(beDemoManager *self);
void beDemoManager_Stop(void);
int beDemoManager_AcceptInfo(void);
void beDemoManager_Reset(beDemoManager *self);
void beDemoManager_Update(beDemoManager *self);
igMetaObject *beDemoManager_GetMetaObject_Virtual(void);
extern int g_defaultAllocatorSelector[4];
extern unsigned char g_useOwnerAllocator;
extern void *g_stringPool[4];
extern igMetaObject *g_beMessenger_metaObject[4];
extern igMetaObject *g_beLua_metaObject[4];
extern igMetaObject *g_beDemoManager_metaObject[4];
extern int g_mdlEntity[4];
}

/* An insight manager's virtual functions, as far as the demo manager calls them. */
class InsightManagerSlots {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void getMetaObject(); virtual void addToScheduler(); virtual void removeFromScheduler();
    virtual void start(); virtual void stop(); virtual void acceptInfo();
    virtual void reset();
};

/* The allocator an object's new members come from: its own, or the default one. */
static inline int allocatorFor(void *object) {
    int allocator = igObject_GetAllocator(object);
    return g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
}

/* The game's string pool, created on first use. */
static inline void *stringPool(void) {
    if (g_stringPool[0] == 0) {
        void *pool = StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return g_stringPool[0];
}

/* A pooled string keeps its chunk owner and reference count in the two words before its text. */
static inline void releaseString(char *text) {
    if (text != 0) {
        int *header = (int *)(text - 8);
        int count = header[1] - 1;
        header[1] = count;
        if (count == 0) StringChunk_ReleaseHeader(header[0], header);
    }
}

/* Points a keep-message string field at the pooled copy of `text`, releasing the string it held. */
static inline void setKeepMesString(beDemoKeepMes *mes, int beDemoKeepMes::*field, const char *text) {
    char *token = StringPool_Intern(stringPool(), text);
    releaseString((char *)(mes->*field));
    mes->*field = (int)token;
}

/* Creates the build data the DM* calls append keep-messages to, if there is none yet. */
static inline void ensureBuildData(beDemoManager *self) {
    if (self->_buildData == 0) {
        int allocator = allocatorFor(self);
        igRelease((igObject *)self->_buildData);
        self->_buildData = (int)beDemoManagerWork_CreateInstance(allocator);
        self->_turningOK = 0;
    }
}

/* The build data, created on first use. */
static inline beDemoManagerWork *buildData(beDemoManager *self) {
    ensureBuildData(self);
    return (beDemoManagerWork *)self->_buildData;
}

static inline beDemoManagerWork *activeWork(beDemoManager *self, int index) {
    return ((beDemoManagerWork **)((beDemoManagerWorkList *)self->_activeDataList)->_data)[index];
}

static inline beDemoKeepMesList *keepMesList(beDemoManagerWork *work) {
    return (beDemoKeepMesList *)work->_keepMesList;
}

/* Opens a switch: the message is sent at play time and its int reply picks the case. Switches do
 * not nest. */
void beDemoManager_SwitchSD(beDemoManager *self, const char *group, const char *infoName, int ramNo, const char *message, const char *param) {
    if (self->_turningOK == 0) {
        self->_turningOK = 1;
    } else {
        return;
    }
    beDemoManager_AddKeepMes(self, DEMO_MES_SWITCH, group, infoName, ramNo, message, param, 0);
}

void beDemoManager_SwitchEnd(beDemoManager *self) {
    beDemoManagerWork *work;
    int allocator;
    if (self->_buildData != 0) {
        if (self->_turningOK == 1) {
            self->_turningOK = 0;
        } else {
            return;
        }
        {
            work = (beDemoManagerWork *)self->_buildData;
            allocator = allocatorFor(self);
            igSmartPointer<beDemoKeepMes> mes(beDemoKeepMes_CreateInstance(allocator));
            mes->_kind = DEMO_MES_SWITCH_END;
            ObjectList_AppendRetained((void *)work->_keepMesList, mes.p);
        }
    }
}

void beDemoManager_Case(beDemoManager *self, int ramNo) {
    beDemoManagerWork *work;
    int allocator;

    work = (beDemoManagerWork *)self->_buildData;
    if ((work != 0) && (self->_turningOK != 0)) {
        allocator = allocatorFor(self);
        igSmartPointer<beDemoKeepMes> mes(beDemoKeepMes_CreateInstance(allocator));
        mes->_kind = DEMO_MES_CASE;
        mes->_ramNo = ramNo;
        ObjectList_AppendRetained((void *)work->_keepMesList, mes.p);
    }
}

void beDemoManager_AddKeepMes(beDemoManager *self, int kind, const char *group, const char *infoName, int ramNo, const char *message, const char *param, long long sendTime) {
    beDemoManagerWork *work = buildData(self);
    int allocator = allocatorFor(self);
    igSmartPointer<beDemoKeepMes> mes(beDemoKeepMes_CreateInstance(allocator));
    mes->_kind = kind;
    mes->_sendTime = sendTime;
    setKeepMesString(mes, &beDemoKeepMes::_groupName, group);
    setKeepMesString(mes, &beDemoKeepMes::_infoName, infoName);
    mes->_ramNo = ramNo;
    setKeepMesString(mes, &beDemoKeepMes::_message, message);
    setKeepMesString(mes, &beDemoKeepMes::_mesParam, param);
    ObjectList_AppendRetained((void *)work->_keepMesList, mes.p);
}

void beDemoManager_SetLua(beDemoManager *self, const char *chunk) {
    beDemoManagerWork *work;
    beDemoKeepMes *target;
    char *token;
    ensureBuildData(self);
    work = (beDemoManagerWork *)self->_buildData;
    igSmartPointer<beDemoKeepMes> mes(beDemoKeepMes_CreateInstance(allocatorFor(self)));
    mes->_kind = DEMO_MES_LUA;
    target = mes.p;
    token = StringPool_Intern(stringPool(), chunk);
    releaseString((char *)target->_mesParam);
    target->_mesParam = (int)token;
    ObjectList_AppendRetained((void *)work->_keepMesList, mes.p);
}

void beDemoManager_MsgBox(beDemoManager *self, const char *text, int ramNo) {
    beDemoManagerWork *work = buildData(self);
    igSmartPointer<beDemoKeepMes> mes(beDemoKeepMes_CreateInstance(allocatorFor(self)));
    mes->_kind = DEMO_MES_MSGBOX;
    setKeepMesString(mes, &beDemoKeepMes::_mesParam, text);
    mes->_ramNo = ramNo;
    ObjectList_AppendRetained((void *)work->_keepMesList, mes.p);
}

/* Hands the build data over to play, unless a switch is still open. */
void beDemoManager_Run(beDemoManager *self) {
    igObject *work = (igObject *)self->_buildData;
    if ((work != 0) && (self->_turningOK != 1)) {
        ObjectList_AppendRetained((void *)self->_activeDataList, work);
        igRelease((igObject *)self->_buildData);
        self->_buildData = 0;
        self->_turningOK = 0;
    }
}

void beDemoManager_AddToScheduler(beDemoManager *self, int unused)
{
    igInsightCore_AddToScheduler(self->_insight, self);
}

void beDemoManager_RemoveFromScheduler(beDemoManager *self, int unused)
{
    igInsightCore_RemoveFromScheduler(self->_insight, self);
}

void beDemoManager_Start(beDemoManager *self) {
    self->_messenger = igInsightCore_FindManager(self->_insight, g_beMessenger_metaObject[0]);
    self->_lua = igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]);
}

void beDemoManager_Stop(void)
{
}

int beDemoManager_AcceptInfo(void) {
    return 0;
}

/* Zeroes every slot of the list and empties it. */
static inline void removeAll(igObjectList *list) {
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        ((igObject **)list->_data)[i] = 0;
    }
    list->_count = 0;
}

/* Drops the list's share of every object it holds and empties it. */
static inline void releaseAll(igObjectList *list) {
    int count = list->_count;
    int i;
    for (i = 0; i < count; i++) {
        igRelease(((igObject **)list->_data)[i]);
    }
    removeAll(list);
}

/* Resizes the list's storage to `capacity` items, unless it holds more than that. */
static inline void setCapacity(igObjectList *list, int capacity) {
    if (capacity >= list->_count) {
        List_Reserve(list, capacity, 4);
    }
}

/* Drops every playing and building demo. Called while an update plays, it waits for the update's end. */
void beDemoManager_Reset(beDemoManager *self) {
    if (self->_disableRemoveAll == 1) {
        self->_calledRemoveAll = 1;
        return;
    }
    releaseAll((igObjectList *)self->_activeDataList);
    setCapacity((igObjectList *)self->_activeDataList, 0);
    igRelease((igObject *)self->_buildData);
    self->_buildData = 0;
    self->_turningOK = 0;
    self->_calledRemoveAll = 0;
}

/* Plays each active demo from where it stopped until a wait holds it, then drops the finished ones. */
void beDemoManager_Update(beDemoManager *self) {
    int count;
    int i;
    int index;
    int end;
    int label;
    unsigned char held;
    beDemoKeepMes *mes;
    long long delay;
    int k;
    beDemoKeepMes *next;
    int offset;
    self->_disableRemoveAll = 1;
    count = ((beDemoManagerWorkList *)self->_activeDataList)->_count;
    for (i = count - 1; i >= 0; i--) {
        index = activeWork(self, i)->_advancec;
        end = keepMesList(activeWork(self, i))->_count;
        held = 0;
        for (; index < end; index++) {
            offset = index * 4;
            mes = *(beDemoKeepMes **)((char *)keepMesList(activeWork(self, i))->_data + offset);
            switch (mes->_kind) {
            case DEMO_MES_SEND:
            case DEMO_MES_SEND_UNTIL_TRUE:
            case DEMO_MES_SEND_UNTIL_FALSE:
            case DEMO_MES_SWITCH:
                delay = mes->_sendTime;
                if (delay <= 0) {
                    beMessenger_SelectReceivers((beMessenger *)self->_messenger, (const char *)mes->_groupName, (const char *)mes->_infoName, mes->_ramNo);
                    if (mes->_mesParam != 0) Lua_sd_OptionalArg((const char *)mes->_mesParam);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, (const char *)mes->_message);
                } else {
                    beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, (const char *)mes->_groupName, (const char *)mes->_infoName, mes->_ramNo);
                    if (mes->_mesParam != 0) Lua_sd_OptionalArg((const char *)mes->_mesParam);
                    beMessenger_EnqueueSelected((beMessenger *)self->_messenger, (const char *)mes->_message, delay);
                }
                switch (mes->_kind) {
                case DEMO_MES_SEND_UNTIL_TRUE:
                    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0) held = 1;
                    else if ((beMessenger_GetBool((beMessenger *)self->_messenger, 0) & 0xff) != 1) held = 1;
                    break;
                case DEMO_MES_SEND_UNTIL_FALSE:
                    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0) held = 1;
                    else if ((beMessenger_GetBool((beMessenger *)self->_messenger, 0) & 0xff) != 0) held = 1;
                    break;
                case DEMO_MES_SWITCH:
                    if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
                        while (index < end) {
                            index++;
                            offset += 4;
                            beDemoKeepMes *branch = *(beDemoKeepMes **)((char *)keepMesList(activeWork(self, i))->_data + offset);
                            if (index >= end) break;
                            if (branch->_kind == DEMO_MES_CASE) {
                                label = branch->_ramNo;
                                if (label == beMessenger_GetInt((beMessenger *)self->_messenger, 0)) break;
                            } else if (branch->_kind == DEMO_MES_SWITCH_END) break;
                        }
                    }
                    break;
                }
                break;
            case DEMO_MES_CASE:
                while (index < end) {
                    index++;
                    next = ((beDemoKeepMes **)keepMesList(activeWork(self, i))->_data)[index];
                    if (index >= end) break;
                    if (next->_kind == DEMO_MES_SWITCH_END) break;
                }
                break;
            case DEMO_MES_LUA:
                g_mdlEntity[0] = 0;
                beLua__RunNamedChunk((beLua *)self->_lua, (const char *)mes->_mesParam, 0);
                break;
            }
            if (held) break;
        }
        activeWork(self, i)->_advancec = index;
    }
    for (k = count - 1; k >= 0; k--) {
        beDemoManagerWorkList *list = (beDemoManagerWorkList *)self->_activeDataList;
        beDemoManagerWork *work = ((beDemoManagerWork **)list->_data)[k];
        if (work->_advancec < keepMesList(work)->_count) continue;
        igRelease((igObject *)work);
        List_RemoveWordAt(list, k);
        ((int *)list->_data)[list->_count] = 0;
    }
    self->_disableRemoveAll = 0;
    if (self->_calledRemoveAll != 0) ((InsightManagerSlots *)self)->reset();
}

igMetaObject *beDemoManager_GetMetaObject_Virtual(void)
{
    return g_beDemoManager_metaObject[0];
}

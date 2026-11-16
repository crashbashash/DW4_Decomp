#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define RET(o) { igObject *rt = (o); if (rt != 0) rt->_refCount = rt->_refCount + 1; }
#define SETP(T, panel, src, field) { igObject *c = (igObject *)(src); T *pp = (T *)(panel); if (c != 0) c->_refCount = c->_refCount + 1; { igObject *o = (igObject *)pp->field; REL(o) } pp->field = (int)c; }
#define HOOK(T, panel) SETP(T, panel, work->_textSetList, _textSetList) SETP(T, panel, work->_textColorList, _textColorList) ((T *)(panel))->_playerNo = ram->_ramNo; ((T *)(panel))->_manager = (int)self; ((T *)(panel))->_messenger = self->_messenger;

extern "C" int StringPool_Allocate(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringPool_Intern(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int strcmp(...);
extern "C" int beMessenger_SelectReceivers(int, const void *, int, int);
extern "C" void beNDMWPanelObject_Close(beNDMWPanelObject *panel);
extern "C" void igObject_Destroy(void *);
extern "C" int sprintf(...);
extern "C" int List_Reserve(...);
extern "C" int List_Resize(...);
extern "C" int ObjectList_AppendRetained(int, int);
extern "C" int beMessenger_AppendInt(...);
extern "C" void * beMessenger_GetObject(...);
extern "C" int beNDMWItemBase_GetRecordInt(...);
extern "C" int * beNDMWItemBase_GetRecordString(...);
extern "C" long long __divdi3(long long, int);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" int beMessenger_EnqueueSelected(int, const void *, int);
extern "C" int beMessenger_PrepareDelayedSelection(int, const void *, const char *, int);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" int beNDMWPanelWaza_GetInfoMeta(void);
extern "C" int beNDMWPanelWaza_GetMeta(void);
extern "C" int beMessenger_RegisterReceiver(int, void *, const void *, int, int);
extern "C" int beBaseInfoRam_StartTimer(...);
extern "C" int beBaseInfoRam_IsTimerExpired(void *, const char *);
extern "C" int beNDMWPanelWazaInfoWork_igIntList_SetAll(int, int *);
extern "C" int beNDMWPanelWazaInfoWork_GetTextColorList(void *);
extern "C" int beNDMWPanelWazaInfoWork_GetTextSetList(void *);
extern "C" void *beNDMWPanelWazaInfoWork_Create(void *);
extern "C" int beNDMWPanelObject_GetMessageEnum(...);
extern "C" void *Memory_GetAllocatorBySelector(int);
extern "C" void *igObject_GetAllocator(void *);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int beMessenger_AppendBool(int, unsigned char);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_GetBoolCount(int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_PopArgContext(int);
extern "C" int beMessenger_PushArgContext(int);
extern "C" int beMessenger_SendNamed(int, const void *, const void *, int, const void *);
extern "C" int beMessenger_SetBool(int, int, unsigned char);
extern "C" int beNDMWPanelObjectStat_GetMeta(void);
extern "C" void beNDMWPanelObjectStat_Fire(void);
extern "C" int beNDMWPanelObjectItem_GetMeta(void);
extern "C" int beNDMWPanelObjectWaza_GetMeta(void);
#pragma push
#pragma readonly_strings on

extern "C" {
int g_textColorNoneReset = -1;
/* Sequences by panel page (waza, item, status) and step (open 3, open 2, open 1, close). */
const char *g_panelPageSeqs[3][4] = {
    {"SQ_OPENWZ03", "SQ_OPENWZ02", "SQ_OPENWZ01", "SQ_CLOSEWZ"},
    {"SQ_OPENIT03", "SQ_OPENIT02", "SQ_OPENIT01", "SQ_CLOSEIT"},
    {"SQ_OPENST03", "SQ_OPENST02", "SQ_OPENST01", "SQ_CLOSEST"}
};
const char *g_panelLineSelectSeqs[4] = { "SQ_LINESL00", "SQ_LINESL01", "SQ_LINESL02", "SQ_LINESL03" };
const char *g_panelFontGroups[3] = { "WZSELFONT", "WZMPFONT", "WZXFONT" };
const char *g_panelFontNames[16] = { "font00", "font01", "font02", "font03", "font04", "font05", "font06", "font07", "font08", "font09", "font10", "font11", "font12", "font13", "font14", "font15" };
int g_textColorNone = -1;
}
extern "C" int g_stringPool[4];
extern "C" {
char g_textColorRgbReady;
float g_textColorRgb[12];
}
struct RecoveryString { void *p; RecoveryString() {} RecoveryString(void *q) { p = q; } ~RecoveryString() { if (p != 0) { int *t = (int *)((char *)p - 8); int v = *(int *)((char *)p - 4) - 1; *(int *)((char *)p - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*t, t); } } };
extern "C" RecoveryString StringList_CopyRetained(void *, int);
struct SetOp { static inline void go(igStringRefList *L, int idx, const RecoveryString &r) { int cnt; int *slot; int *t; int *a1; int c; cnt = L->_count; if (cnt != 0 && idx >= 0 && idx < cnt) { slot = (int *)L->_data + idx; t = (int *)r.p; if (t != 0) t[-1] = t[-1] + 1; t = (int *)(*slot); if (t != 0) { a1 = t - 2; c = t[-1] - 1; t[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); } *slot = (int)r.p; } } };
extern "C" void beNDMWPanelObject_SetCellText(beNDMWPanelObject *self, int g, int s, int *name, int val);
struct PanelPosition { float x; float y; float z; };
extern "C" void beNDMWPanelObject_GetBasePosition(beNDMWPanelObject *panel, struct PanelPosition *position);
extern "C" void beNDMWPanelObject_SendModelCommand(beNDMWPanelObject *panel, const void *target, const void *message, float *position, int sequence);
extern "C" void beNDMWPanelObject_Open(beNDMWPanelObject *panel, int generate, int silent);
extern "C" void beNDMWPanelObject_MoveCursorUp(beNDMWPanelObject *panel);
extern "C" void beNDMWPanelObject_MoveCursorDown(beNDMWPanelObject *panel);
/* An igProperty record: its value is the word at +12. */
struct PropertyRecord { char header[12]; int value; };
extern "C" PropertyRecord * igProperty_GetRecord(...);
extern "C" PropertyRecord * igProperty_GetRecordFolder(...);
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void beNDMWPanelObjectWaza_Refresh(beNDMWPanelObjectWaza *self);
extern "C" void beNDMWPanelObjectWaza_Fire(beNDMWPanelObjectWaza *self, int *label, long long *wait);
extern "C" int g_bePadManager_metaObject[4];
extern "C" void beNDMWPanelWaza_Prepare(beNDMWPanelWaza *self);
extern "C" int g_beNDMWPanelWazaInfo_metaObject[4];
extern "C" int g_beNDMWPanelWaza_metaObject[4];
extern "C" void beNDMWPanelWaza_OnAddRam(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram);
extern "C" bePadData *bePadManager_GetPadForPlayer(int, int);
class StringRef {
public:
    char *p;
    StringRef(const char *text);
    ~StringRef();
};
extern "C" int beNDMWPanelWazaInfoWork_igStringRefList_SetAll(int, StringRef *);
/* matching construct: dummy-virtual panel object; slot 21 refreshes, slot 22 asks for a fire request */
class PanelVt { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
 virtual void Refresh();
 virtual void GetFireRequest(int *label, long long *result);
};
/* matching construct: dummy-virtual info work; slot 16 is the "finished" notification */
class WorkVt { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
 virtual void Finished();
};
struct InfoWorkOps {
static void SetLabel(beNDMWPanelWazaInfoWork *w, int str)
{
    int pool;
    int fresh;
    int old;
    int *hd;
    int rc;

    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    fresh = StringPool_Intern(g_stringPool[0], str);
    old = w->_retWazaLabel;
    if (old != 0) {
        hd = (int *)(old - 8);
        rc = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    w->_retWazaLabel = fresh;
}
};
extern "C" void beNDMWPanelWaza_UpdateRam(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram);
extern "C" int beNDMWPanelWaza_FindEmergencyHealDisk(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram);
extern "C" int beNDMWPanelWaza_FindEmergencyHealWaza(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram);
extern "C" void beNDMWPanelWaza_OpenPanel(int self, beNDMWPanelWazaInfoRam *ram, int page, igObject *player);
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int beNDMWPanelWaza_OnMessage(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram, beMessengerWork *message);
extern "C" int g_beNDMWPanelObjectStat_metaObject[4];
extern "C" int g_beNDMWPanelObjectItem_metaObject[4];
extern "C" int g_beNDMWPanelObjectWaza_metaObject[4];
/* matching construct: dummy-virtual view of beNDMWItemDisk; slot 22 (beNDMWItemDisk_Use)
 * uses one disk on a player and reports whether it took effect */
class DiskUseShim {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21();
    virtual int Use(int manager, int playerNo);
};
extern "C" const float g_vec3Zero[4];
extern "C" void beNDMWPanelObjectItem_Refresh(beNDMWPanelObjectItem *self);
extern "C" void beNDMWPanelObjectItem_Fire(beNDMWPanelObjectItem *self, int *label, long long *wait);
extern "C" int beDataBase_GetRecordInt(beDataBase *, int, const void *);
extern "C" int beDataBase_GetRecordString(beDataBase *, int, const char *);
extern "C" void StringList_AppendRetained(void *, RecoveryString *);
extern "C" void beNDMWPanelObjectStat_Refresh(beNDMWPanelObjectStat *self);
static inline int listCount(const igIntList *list) { return list->_count; }

void beNDMWPanelObject_SetCellText(beNDMWPanelObject *self, int g, int s, int *name, int val) {
    float v[3];
    int idx;
    int pool;
    int ref;
    int cnt;
    bool x;
    float *p;
    int *slot;
    int *t;

    if (g_textColorRgbReady == 0) {
        g_textColorRgb[0] = 0.9f;
        g_textColorRgb[1] = 0.9f;
        g_textColorRgb[2] = 0.9f;
        g_textColorRgb[3] = 0.5f;
        g_textColorRgb[4] = 0.5f;
        g_textColorRgb[5] = 0.7f;
        g_textColorRgb[6] = 1.0f;
        g_textColorRgb[7] = 0.68f;
        g_textColorRgb[8] = 1.0f;
        g_textColorRgb[9] = 0.0f;
        g_textColorRgb[10] = 0.96f;
        g_textColorRgb[11] = 1.0f;
        g_textColorRgbReady = 1;
    }
    idx = s + g * 16;
    if (name != 0) {
        if ((t = (int *)StringList_CopyRetained(((igStringRefList *)self->_textSetList), idx).p, x = true, t != 0) && (strcmp((int *)StringList_CopyRetained(((igStringRefList *)self->_textSetList), idx).p, name) == 0 ? (x = false, 1) : 0)) {}
        if (x) {
            if (name == 0) {
                ref = 0;
            } else {
                if (g_stringPool[0] == 0) {
                    pool = StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                ref = StringPool_Intern(g_stringPool[0], name);
            }
            SetOp::go(((igStringRefList *)self->_textSetList), idx, RecoveryString((void *)ref));
            beMessenger_SelectGroup(self->_messenger, "TEXTCTL");
            beMessenger_AppendString(self->_messenger, g_panelFontGroups[g]);
            beMessenger_AppendString(self->_messenger, g_panelFontNames[s]);
            beMessenger_AppendString(self->_messenger, name);
            beMessenger_DispatchSelected(self->_messenger, "TEXTSET");
            if (g == 1) {
                beMessenger_SelectGroup(self->_messenger, "TEXTCTL");
                beMessenger_AppendString(self->_messenger, g_panelFontGroups[g]);
                beMessenger_AppendString(self->_messenger, g_panelFontNames[s]);
                beMessenger_AppendString(self->_messenger, "CENTER");
                beMessenger_DispatchSelected(self->_messenger, "ALIGN");
            }
            beMessenger_SelectGroup(self->_messenger, "TEXTCTL");
            beMessenger_AppendString(self->_messenger, g_panelFontGroups[g]);
            beMessenger_AppendString(self->_messenger, g_panelFontNames[s]);
            beMessenger_AppendString(self->_messenger, "SET");
            beMessenger_DispatchSelected(self->_messenger, "SWITCH");
        }
        slot = (int *)((igIntList *)self->_textColorList)->_data + idx;
        if (val != *slot) {
            cnt = ((igIntList *)self->_textColorList)->_count;
            if (cnt != 0 && idx >= 0 && idx < cnt) {
                *slot = val;
            }
            beMessenger_SelectGroup(self->_messenger, "TEXTCTL");
            beMessenger_AppendString(self->_messenger, g_panelFontGroups[g]);
            beMessenger_AppendString(self->_messenger, g_panelFontNames[s]);
            p = &g_textColorRgb[val * 3];
            v[0] = p[0]; v[1] = p[1]; v[2] = p[2];
            beMessenger_AppendVec3((int)self->_messenger, (float *)(&v[0]));
            beMessenger_DispatchSelected(self->_messenger, "COLOR");
        }
    } else {
        SetOp::go(((igStringRefList *)self->_textSetList), idx, RecoveryString((void *)0));
        cnt = ((igIntList *)self->_textColorList)->_count;
        if (cnt != 0 && idx >= 0 && idx < cnt) {
            *((int *)((igIntList *)self->_textColorList)->_data + idx) = g_textColorNone;
        }
        beMessenger_SelectGroup(self->_messenger, "TEXTCTL");
        beMessenger_AppendString(self->_messenger, g_panelFontGroups[g]);
        beMessenger_AppendString(self->_messenger, g_panelFontNames[s]);
        beMessenger_AppendString(self->_messenger, "CLR");
        beMessenger_DispatchSelected(self->_messenger, "SWITCH");
    }
}

void beNDMWPanelObject_GetBasePosition(beNDMWPanelObject *panel, struct PanelPosition *position) {
    position->x = 150.0f * (float) panel->_playerNo - 260.0f;
    position->y = -160.0f;
    position->z = 0.0f;
}

void beNDMWPanelObject_SendModelCommand(beNDMWPanelObject *panel, const void *target, const void *message, float *position, int sequence) {
    float spawnPosition[4];

    beMessenger_SelectReceivers(panel->_messenger, "MODELCTRL", (int)target, panel->_playerNo);
    if (position != 0) {
        spawnPosition[0] = position[0];
        spawnPosition[1] = position[1];
        spawnPosition[2] = position[2];
        beMessenger_AppendVec3(panel->_messenger, &spawnPosition[0]);
    }
    if (sequence != 0) {
        beMessenger_AppendString(panel->_messenger, sequence);
    }
    beMessenger_DispatchSelected(panel->_messenger, (int)message);
}

void beNDMWPanelObject_Open(beNDMWPanelObject *panel, int generate, int silent) {
    int origin[3];
    int lineMode;
    int k;

    switch (panel->_listKazu) {
    case 0:
    case 1:
    case 2:
        lineMode = 2;
        break;
    case 3:
        lineMode = 1;
        break;
    default:
        lineMode = 0;
        break;
    }
    panel->_lineMode = lineMode;
    if (generate != 0) {
        beNDMWPanelObject_GetBasePosition(panel, (struct PanelPosition *)origin);
        beNDMWPanelObject_SendModelCommand(panel, "i_wzslbase00", "GENERATE", (float *)origin, (int)g_panelPageSeqs[panel->_page][lineMode]);
    } else {
        beNDMWPanelObject_SendModelCommand(panel, "i_wzslbase00", g_panelPageSeqs[panel->_page][lineMode], (float *)0, 0);
    }
    if (!(silent & 0xFF)) {
        beMessenger_SelectGroup(panel->_messenger, "SOUND");
        beMessenger_AppendString(panel->_messenger, "WINDOW_OPEN");
        beMessenger_DispatchSelected(panel->_messenger, "PLAY");
    }
}

void beNDMWPanelObject_Close(beNDMWPanelObject *panel) {
    int i;
    int t;

    beNDMWPanelObject_SendModelCommand(panel, "i_wzslbase00", g_panelPageSeqs[panel->_page][3], (float *)0, 0);
    i = 0;
    do {
        t = i + panel->_playerNo * 4;
        beNDMWPanelObject_SetCellText(panel, 0, t, (int *)0, 0);
        beNDMWPanelObject_SetCellText(panel, 2, t, (int *)0, 0);
        if (i == 0) {
            beNDMWPanelObject_SetCellText(panel, 1, t / 4, (int *)0, 0);
        }
        i += 1;
    } while (i < 4);
}

void beNDMWPanelObject_MoveCursorUp(beNDMWPanelObject *panel) {
    int cursor;
    int offset;
    cursor = panel->_cursor;
    if (cursor != 0) {
        panel->_cursor = cursor - 1;
        beMessenger_SelectGroup(panel->_messenger, "SOUND");
        beMessenger_AppendString(panel->_messenger, "CURSOR_MOVE");
        beMessenger_DispatchSelected(panel->_messenger, "PLAY");
        return;
    }
    offset = panel->_offset;
    if (offset != 0) {
        panel->_offset = offset - 1;
        beMessenger_SelectGroup(panel->_messenger, "SOUND");
        beMessenger_AppendString(panel->_messenger, "CURSOR_MOVE");
        beMessenger_DispatchSelected(panel->_messenger, "PLAY");
    }
}

void beNDMWPanelObject_MoveCursorDown(beNDMWPanelObject *panel) {
    int n;
    int cur;
    int t;
    n = panel->_listKazu;
    if (n != 0 && (cur = panel->_cursor, cur != (n - 1))) {
        if (cur != 3) {
            panel->_cursor = cur + 1;
            beMessenger_SelectGroup(panel->_messenger, "SOUND");
            beMessenger_AppendString(panel->_messenger, "CURSOR_MOVE");
            beMessenger_DispatchSelected(panel->_messenger, "PLAY");
            return;
        }
        t = panel->_offset;
        if ((t + 4) < n) {
            panel->_offset = t + 1;
            beMessenger_SelectGroup(panel->_messenger, "SOUND");
            beMessenger_AppendString(panel->_messenger, "CURSOR_MOVE");
            beMessenger_DispatchSelected(panel->_messenger, "PLAY");
        }
    }
}

static inline int countOf(const igIntList *l) { return l->_count; }

void beNDMWPanelObjectWaza_Refresh(beNDMWPanelObjectWaza *self) {
    int pos[3];
    int mpText[2];
    if (self->_playerDataList == 0) {
        beMessenger_SelectGroup(self->_messenger, "GAMERAM");
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
        igObject *o = (igObject *)beMessenger_GetObject(self->_messenger, 0);
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        Rel::go((igObject *)self->_playerDataList);
        self->_playerDataList = (int)o;
    }
    igObjectList *wazaFolder = (igObjectList *)igProperty_GetRecordFolder(self->_playerDataList, "WAZALIST")->value;
    igObjectList *list = (igObjectList *)self->_listFolder;
    int n1 = list->_count;
    int i1 = 0;
    if (0 < n1) {
        do {
            Rel::go(((igObject **)list->_data)[i1]);
            i1++;
        } while (i1 < n1);
    }
    int m = list->_count;
    for (int j = 0; j < m; j++) {
        ((igObject **)list->_data)[j] = 0;
    }
    list->_count = 0;
    int n2 = wazaFolder->_count;
    for (int k = 0; k < n2; k++) {
        ObjectList_AppendRetained(self->_listFolder, (int)((igObject **)wazaFolder->_data)[k]);
    }
    int cnt = ((igObjectList *)self->_listFolder)->_count;
    igIntList *d = (igIntList *)self->_listColor;
    if (d->_count < cnt) {
        if (!(cnt < countOf(d))) List_Reserve(d, cnt, 4);
    }
    d = (igIntList *)self->_listColor;
    if (cnt >= 0) {
        if (cnt <= d->_capacity) {
            d->_count = cnt;
        } else {
            List_Resize(d, cnt, 4);
        }
    }
    int c2 = ((igObjectList *)self->_listFolder)->_count;
    if (c2 != self->_listKazu) {
        self->_cursor = 0;
        self->_offset = 0;
        self->_listKazu = c2;
    }
    beNDMWPanelObject_GetBasePosition((beNDMWPanelObject *)self, (struct PanelPosition *)pos);
    int i = 0;
    do {
        int slot = i + self->_playerNo * 4;
        int a = self->_lineMode;
        int row = (i + self->_offset) - a;
        if (a <= i) {
            igObjectList *folder = (igObjectList *)self->_listFolder;
            if (row < folder->_count) {
                int color = 0;
                beNDMWItemBase *waza = ((beNDMWItemBase **)folder->_data)[row];
                int *name = beNDMWItemBase_GetRecordString(waza, self->_manager, "NAME");
                int mp = igProperty_GetRecord(self->_playerDataList, "MP")->value;
                if (mp < beNDMWItemBase_GetRecordInt(waza, self->_manager, "MP")) {
                    color = 1;
                }
                if (self->_isNoHealing != 0) {
                    int t = waza->_recNo;
                    if (t >= 40 && t < 50) color = 2;
                }
                if (self->_isNoParaUp != 0) {
                    int t = waza->_recNo;
                    if (t >= 65 && t < 70) color = 2;
                    else if (t >= 75 && t < 85) color = 2;
                }
                if (self->_isNoCureling != 0) {
                    int t = waza->_recNo;
                    if (t >= 50 && t < 65) color = 2;
                }
                igIntList *colors = (igIntList *)self->_listColor;
                int nn = colors->_count;
                if (nn != 0 && row >= 0 && row < nn) {
                    ((int *)colors->_data)[row] = color;
                }
                beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, name, color);
            } else {
                beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, (int *)0, 0);
            }
        } else {
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, (int *)0, 0);
        }
        beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 2, slot, (int *)0, 0);
        if (i == 0) {
            sprintf(mpText, "%d", beNDMWItemBase_GetRecordInt(((beNDMWItemBase **)((igObjectList *)self->_listFolder)->_data)[self->_cursor + self->_offset], self->_manager, "MP"));
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 1, slot / 4, (int *)mpText, 0);
        }
        i++;
    } while (i < 4);
}

void beNDMWPanelObjectWaza_Fire(beNDMWPanelObjectWaza *self, int *label, long long *wait) {
    int waza;
    PropertyRecord *mp;
    int maxMp;
    int index;
    int mpCost;

    *wait = 0;
    *label = 0;
    index = self->_cursor + self->_offset;
    if (((int *)((igDataList *)self->_listColor)->_data)[index] == 0) {
        waza = ((int *)((igObjectList *)self->_listFolder)->_data)[index];
        mp = igProperty_GetRecord(self->_playerDataList, "MP");
        mpCost = beNDMWItemBase_GetRecordInt(waza, self->_manager, "MP");
        if (mp->value >= mpCost) {
            *wait = (long long)beNDMWItemBase_GetRecordInt(waza, self->_manager, "DELAY");
            *wait = __divdi3(*wait * 0x3B9ACA00LL, 0x3C);
            *label = ((int)beNDMWItemBase_GetRecordString(waza, self->_manager, "LABEL"));
            mp->value = mp->value - mpCost;
            maxMp = igProperty_GetRecord(self->_playerDataList, "MMP")->value;
            beMessenger_PrepareDelayedSelection(self->_messenger, "METERCTRL", "mpmt", self->_playerNo);
            beMessenger_AppendFloat(self->_messenger, (float)(mp->value * 100 / maxMp));
            beMessenger_EnqueueSelected(self->_messenger, "SETPERCENT", 1);
            beMessenger_PrepareDelayedSelection(self->_messenger, "NUMBERCTRL", "mpnm", self->_playerNo);
            beMessenger_AppendInt(self->_messenger, mp->value);
            beMessenger_EnqueueSelected(self->_messenger, "SETVALUE", 1);
            return;
        }
        beMessenger_SelectGroup(self->_messenger, "SOUND");
        beMessenger_AppendString(self->_messenger, "CURSOR_NG");
        beMessenger_DispatchSelected(self->_messenger, "PLAY");
        return;
    }
    beMessenger_SelectGroup(self->_messenger, "SOUND");
    beMessenger_AppendString(self->_messenger, "CURSOR_NG");
    beMessenger_DispatchSelected(self->_messenger, "PLAY");
}

void beNDMWPanelObjectItem_Refresh(beNDMWPanelObjectItem *self) {
    int pos[3];
    char kazuText[8];
    if (self->_playerDataList == 0) {
        beMessenger_SelectGroup(self->_messenger, "GAMERAM");
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
        igObject *o = (igObject *)beMessenger_GetObject(self->_messenger, 0);
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        Rel::go((igObject *)self->_playerDataList);
        self->_playerDataList = (int)o;
    }
    igObjectList *diskFolder = (igObjectList *)igProperty_GetRecordFolder(self->_playerDataList, "DISKFOLDER")->value;
    igObjectList *list = (igObjectList *)self->_listFolder;
    int n1 = list->_count;
    int i1 = 0;
    if (0 < n1) {
        do {
            Rel::go(((igObject **)list->_data)[i1]);
            i1++;
        } while (i1 < n1);
    }
    int m = list->_count;
    for (int j = 0; j < m; j++) {
        ((igObject **)list->_data)[j] = 0;
    }
    list->_count = 0;
    /* the last two folder entries are not listed */
    int n2 = diskFolder->_count - 2;
    for (int k = 0; k < n2; k++) {
        beNDMWItemDisk *disk = ((beNDMWItemDisk **)diskFolder->_data)[k];
        if (disk->_kazu != 0) {
            ObjectList_AppendRetained(self->_listFolder, (int)disk);
        }
    }
    int cnt = ((igObjectList *)self->_listFolder)->_count;
    igIntList *d = (igIntList *)self->_listColor;
    if (d->_count < cnt) {
        if (!(cnt < countOf(d))) List_Reserve(d, cnt, 4);
    }
    d = (igIntList *)self->_listColor;
    if (cnt >= 0) {
        if (cnt <= d->_capacity) {
            d->_count = cnt;
        } else {
            List_Resize(d, cnt, 4);
        }
    }
    int c2 = ((igObjectList *)self->_listFolder)->_count;
    if (c2 != self->_listKazu) {
        self->_cursor = 0;
        self->_offset = 0;
        self->_listKazu = c2;
    }
    beNDMWPanelObject_GetBasePosition((beNDMWPanelObject *)self, (struct PanelPosition *)pos);
    int i = 0;
    do {
        int slot = i + self->_playerNo * 4;
        int a = self->_lineMode;
        int row = (i + self->_offset) - a;
        if (a <= i) {
            igObjectList *folder = (igObjectList *)self->_listFolder;
            if (row < folder->_count) {
                beNDMWItemDisk *disk = ((beNDMWItemDisk **)folder->_data)[row];
                int *name = beNDMWItemBase_GetRecordString(disk, self->_manager, "NAME");
                int color = 0;
                if (self->_isNoGateDisk != 0 && disk->_recNo == 8) {
                    color = 2;
                }
                if (self->_isNoHealing != 0) {
                    int t = disk->_recNo;
                    if (t <= 5 || t == 9) color = 2;
                }
                if (self->_isNoCureling != 0) {
                    int t = disk->_recNo;
                    if (t >= 6 && t < 8) color = 2;
                }
                igIntList *w = (igIntList *)self->_listColor;
                int nn = w->_count;
                if (nn != 0 && row >= 0 && row < nn) {
                    ((int *)w->_data)[row] = color;
                }
                beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, name, ((int *)((igIntList *)self->_listColor)->_data)[row]);
            } else {
                beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, (int *)0, 0);
            }
        } else {
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, (int *)0, 0);
        }
        if (self->_lineMode <= i && row < ((igObjectList *)self->_listFolder)->_count) {
            sprintf(kazuText, "x%d", ((beNDMWItemDisk **)((igObjectList *)self->_listFolder)->_data)[row]->_kazu);
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 2, slot, (int *)kazuText, ((int *)((igIntList *)self->_listColor)->_data)[row]);
        } else {
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 2, slot, (int *)0, 0);
        }
        if (i == 0) {
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 1, slot / 4, (int *)0, 0);
        }
        i++;
    } while (i < 4);
}

void beNDMWPanelObjectItem_Fire(beNDMWPanelObjectItem *self, int *label, long long *wait) {
    int idx;
    beNDMWItemDisk *disk;
    int kazu;
    unsigned char used;

    *wait = 0;
    *label = 0;
    idx = self->_cursor + self->_offset;
    if (((int *)((igIntList *)self->_listColor)->_data)[idx] == 0) {
        disk = ((beNDMWItemDisk **)((igObjectList *)self->_listFolder)->_data)[idx];
        kazu = disk->_kazu;
        if (kazu != 0) {
            used = ((DiskUseShim *)disk)->Use(self->_manager, self->_playerNo);
            if (!used) {
                *wait = 1000000000;
            } else {
                *wait = -1;
            }
            disk->_kazu = kazu - 1;
            switch (disk->_recNo) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 7:
            case 9: {
                float pos[3];
                beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", 0, self->_playerNo);
                beMessenger_AppendString(self->_messenger, "x_250healhit00");
                beMessenger_AppendString(self->_messenger, "SQ_HEALEFONLY");
                beMessenger_AppendFloat(self->_messenger, 1.0f);
                pos[0] = g_vec3Zero[0];
                pos[1] = g_vec3Zero[1];
                pos[2] = g_vec3Zero[2];
                beMessenger_AppendVec3(self->_messenger, pos);
                beMessenger_AppendBool(self->_messenger, 0);
                beMessenger_AppendBool(self->_messenger, 1);
                beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
                break;
            }
            case 6: {
                float pos[3];
                beMessenger_PrepareDelayedSelection(self->_messenger, "PLAYER", 0, self->_playerNo);
                beMessenger_AppendString(self->_messenger, "x_250curehit00");
                beMessenger_AppendString(self->_messenger, "SQ_CUREEFONLY");
                beMessenger_AppendFloat(self->_messenger, 1.0f);
                pos[0] = g_vec3Zero[0];
                pos[1] = g_vec3Zero[1];
                pos[2] = g_vec3Zero[2];
                beMessenger_AppendVec3(self->_messenger, pos);
                beMessenger_AppendBool(self->_messenger, 0);
                beMessenger_AppendBool(self->_messenger, 1);
                beMessenger_EnqueueSelected(self->_messenger, "SETEFFECT", 1);
                break;
            }
            case 8:
            case 10:
            case 11:
                break;
            }
        } else {
            beMessenger_SelectGroup(self->_messenger, "SOUND");
            beMessenger_AppendString(self->_messenger, "CURSOR_NG");
            beMessenger_DispatchSelected(self->_messenger, "PLAY");
        }
    } else {
        beMessenger_SelectGroup(self->_messenger, "SOUND");
        beMessenger_AppendString(self->_messenger, "CURSOR_NG");
        beMessenger_DispatchSelected(self->_messenger, "PLAY");
    }
}

void beNDMWPanelObjectStat_Refresh(beNDMWPanelObjectStat *self) {
    int pos[3];
    if (self->_playerDataList == 0) {
        beMessenger_SelectGroup(self->_messenger, "GAMERAM");
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
        igObject *o = (igObject *)beMessenger_GetObject(self->_messenger, 0);
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        Rel::go((igObject *)self->_playerDataList);
        self->_playerDataList = (int)o;
    }
    igStringRefList *names = (igStringRefList *)self->_listFolder;
    int n = names->_count;
    for (int j = 0; j < n; j++) {
        int *slot = (int *)names->_data + j;
        int pool;
        if (g_stringPool[0] == 0) {
            pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        int fresh = StringPool_Intern(g_stringPool[0], 0);
        int old = *slot;
        if (old != 0) {
            int *hd = (int *)(old - 8);
            int rc = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = rc;
            if (rc == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
        *slot = fresh;
    }
    names->_count = 0;
    ((igIntList *)self->_listColor)->_count = 0;
    if (((beNDMWMdlPlayerInfoWork *)self->_playerWork)->_timerList != 0) {
        beMessenger_SendNamed(self->_messenger, "DATABASE", "wazaPanel", 0, "GETDATABASE");
        beDataBase *db = (beDataBase *)beMessenger_GetObject(self->_messenger, 0);
        for (int i = 0; i < 10; i++) {
            if (((int *)((igObjectList *)((beNDMWMdlPlayerInfoWork *)self->_playerWork)->_timerList)->_data)[i] != 0) {
                int color = beDataBase_GetRecordInt(db, i, "COLOR");
                if (color >= 0) {
                    int c;
                    igIntList *colors;
                    colors = (igIntList *)self->_listColor;
                    c = colors->_count;
                    if (c < colors->_capacity) colors->_count = listCount(colors) + 1; else List_Resize(colors, c + 1, 4);
                    ((int *)colors->_data)[c] = color;
                    int text = beDataBase_GetRecordString(db, i, "NAME");
                    int ref;
                    if (text == 0) {
                        ref = 0;
                    } else {
                        int pool;
                        if (g_stringPool[0] == 0) {
                            pool = StringPool_Allocate(16);
                            if (pool != 0) pool = StringPool_Construct(pool);
                            g_stringPool[0] = pool;
                        }
                        ref = StringPool_Intern(g_stringPool[0], text);
                    }
                    RecoveryString name((void *)ref);
                    StringList_AppendRetained((void *)self->_listFolder, &name);
                }
            }
        }
    }
    int c2 = ((igObjectList *)self->_listFolder)->_count;
    if (c2 != self->_listKazu) {
        self->_cursor = 0;
        self->_offset = 0;
        self->_listKazu = c2;
    }
    beNDMWPanelObject_GetBasePosition((beNDMWPanelObject *)self, (struct PanelPosition *)pos);
    int i = 0;
    do {
        int slot = i + self->_playerNo * 4;
        int a = self->_lineMode;
        int row = (i + self->_offset) - a;
        if (a <= i) {
            if (row < ((igStringRefList *)self->_listFolder)->_count) {
                int *name = (int *)StringList_CopyRetained((void *)self->_listFolder, row).p;
                beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, name, ((int *)((igIntList *)self->_listColor)->_data)[row]);
            } else {
                beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, (int *)0, 0);
            }
        } else {
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 0, slot, (int *)0, 0);
        }
        beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 2, slot, (int *)0, 0);
        if (i == 0) {
            beNDMWPanelObject_SetCellText((beNDMWPanelObject *)self, 1, slot / 4, (int *)0, 0);
        }
        i++;
    } while (i < 4);
}

void beNDMWPanelWaza_Prepare(beNDMWPanelWaza *self) {
    if (self->_padManager == 0) {
        self->_padManager = igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
    }
}

int beNDMWPanelWaza_GetInfoMeta(void)
{
    return g_beNDMWPanelWazaInfo_metaObject[0];
}

void beNDMWPanelWaza_OnAddRam(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram) {
    beMessenger_RegisterReceiver(self->_messenger, ram, "NDMWPANEL", 0, ram->_ramNo);
    ram->_isRun = 0;
}

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]). The constructor interns the text and the destructor releases the token on scope exit;
 * both are out of line. */
static inline int st3(const beNDMWPanelWazaInfoRam *ram) { return ram->_st3; }

void beNDMWPanelWaza_UpdateRam(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram)
{
    unsigned char show;
    beNDMWPanelWazaInfoRam *ramState;
    int sel;
    int both;
    beNDMWPanelObject *panel;
    int prevKazu;
    int vec[4];
    long long ret;
    igObjectList *moveList;
    unsigned char emg;
    bePadData *pad;
    unsigned char decide;
    int idx;
    int refStr;
    unsigned char blocked;
    beNDMWPanelWazaInfoWork *work;
    int rep;
    unsigned char cancel;
    int prevCursor;
    int trig;

    if (ram->_isRun == 1) {
        work = (beNDMWPanelWazaInfoWork *)ram->_work;
        ramState = (beNDMWPanelWazaInfoRam *)(int)ram;
        pad = (bePadData *)bePadManager_GetPadForPlayer(self->_padManager, ramState->_ramNo);
        trig = pad->_trigger;
        decide = 1;
        both = pad->_rTrg | pad->_rRpt;
        rep = pad->_repeat;
        if (!(both & 1) && !((trig | rep) & 0x10)) {
            decide = 0;
        }
        cancel = 1;
        if (!(both & 4) && !((trig | rep) & 0x40)) {
            cancel = 0;
        }
        switch (work->_page) {
        case 0:
            panel = (beNDMWPanelObject *)work->_panelWaza;
            break;
        case 1:
            panel = (beNDMWPanelObject *)work->_panelItem;
            break;
        case 2:
            panel = (beNDMWPanelObject *)work->_panelStat;
            break;
        }
        prevCursor = panel->_cursor;
        prevKazu = panel->_listKazu;
        idx = prevCursor + panel->_lineMode;
        moveList = (igObjectList *)((beNDMWMdlPlayerInfoWork *)work->_playerWork)->_moveObjectList;
        blocked = 0;
        if (moveList->_count != 0 && *(unsigned char *)(*(int *)((int)moveList->_data + 4) + 8) != 0) {
            blocked = 1;
        }
        switch (ramState->_st0) {
        case 0:
            {
                StringRef empty(0);
                beNDMWPanelWazaInfoWork_igStringRefList_SetAll(beNDMWPanelWazaInfoWork_GetTextSetList(work), &empty);
            }
            beNDMWPanelWazaInfoWork_igIntList_SetAll(beNDMWPanelWazaInfoWork_GetTextColorList(work), &g_textColorNoneReset);
            prevKazu = idx = -1;
            ramState->_st0 = ramState->_st0 + 1;
            ramState->_st3 = 0;
            ramState->_st2 = 0;
            ramState->_st1 = 0;
        case 1:
            emg = 1;
            switch (ramState->_st1) {
            case 0:
                if ((unsigned char)beBaseInfoRam_IsTimerExpired(ramState, "FIRE")) {
                    emg = 0;
                    if (panel->_isEmg != 0 ||
                        (blocked == 0 && (trig & 0x4000) && panel->_listKazu != 0 && work->_page != 2)) {
                        if (ramState->_st3 >= 2) {
                            ((PanelVt *)panel)->GetFireRequest(&refStr, &ret);
                            if (0 < ret) {
                                InfoWorkOps::SetLabel(work, refStr);
                                work->_retIsFire = 1;
                                beBaseInfoRam_StartTimer(ramState, "FIRE", ret);
                                ramState->_st1 = ramState->_st1 + 1;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                                panel->_isEmg = 0;
                            } else if (ret < 0) {
                                ramState->_st0 = 2;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                                ramState->_st1 = 0;
                            } else {
                                beBaseInfoRam_StartTimer(ramState, "FIRE", 0x0FE502AA);
                                ramState->_st1 = ramState->_st1 + 1;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                            }
                        }
                    } else if (decide) {
                        beNDMWPanelObject_MoveCursorUp(panel);
                    } else if (cancel) {
                        beNDMWPanelObject_MoveCursorDown(panel);
                    } else if (trig & 0x800) {
                        if (work->_page != 0) {
                            work->_page = 0;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            InfoWorkOps::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, "SOUND");
                            beMessenger_AppendString(self->_messenger, "CURSOR_CANCEL");
                            beMessenger_DispatchSelected(self->_messenger, "PLAY");
                        }
                    } else if (trig & 0x400) {
                        if (work->_page != 1) {
                            work->_page = 1;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            InfoWorkOps::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, "SOUND");
                            beMessenger_AppendString(self->_messenger, "CURSOR_CANCEL");
                            beMessenger_DispatchSelected(self->_messenger, "PLAY");
                        }
                    } else if (trig & 0x200) {
                        if (work->_page != 2) {
                            work->_page = 2;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            InfoWorkOps::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, "SOUND");
                            beMessenger_AppendString(self->_messenger, "CURSOR_CANCEL");
                            beMessenger_DispatchSelected(self->_messenger, "PLAY");
                        }
                    }
                    if (st3(ramState) < 2) {
                        ramState->_st3 = ramState->_st3 + 1;
                    }
                }
                break;
            case 1:
                if (beBaseInfoRam_IsTimerExpired(ramState, "FIRE") != 0) {
                    ramState->_st1 = 0;
                    ramState->_st3 = 0;
                    ramState->_st2 = 0;
                }
                break;
            }
            ((PanelVt *)panel)->Refresh();
            if (prevKazu != panel->_listKazu) {
                if (panel->_isEmg != 0 && emg) {
                    beNDMWPanelObject_Open(panel, work->_isWindowGenerate, 1);
                } else {
                    beNDMWPanelObject_Open(panel, work->_isWindowGenerate, 0);
                }
                work->_isWindowGenerate = 0;
            }
            show = 1;
            if (ramState->_st0 == 1 && ramState->_st1 == 1) {
                show = 0;
            } else if (panel->_listKazu == 0) {
                show = 0;
            } else if (blocked) {
                show = 0;
            }
            if (show) {
                sel = panel->_cursor + panel->_lineMode;
                if (work->_isCursorGenerate == 0) {
                    beNDMWPanelObject_GetBasePosition(panel, (struct PanelPosition *)vec);
                    beNDMWPanelObject_SendModelCommand(panel, "i_wzslcursel", "GENERATE", (float *)vec, (int)g_panelLineSelectSeqs[sel]);
                    work->_isCursorGenerate = 1;
                    return;
                }
                if (idx != sel) {
                    beNDMWPanelObject_SendModelCommand(panel, "i_wzslcursel", g_panelLineSelectSeqs[sel], (float *)0, 0);
                    return;
                }
            } else if (work->_isCursorGenerate != 0) {
                beNDMWPanelObject_SendModelCommand(panel, "i_wzslcursel", "SQ_CLOSE", (float *)0, 0);
                work->_isCursorGenerate = 0;
                return;
            }
            break;
        case 2:
            beMessenger_SelectGroup(self->_messenger, "SOUND");
            beMessenger_AppendString(self->_messenger, "WINDOW_CLOSE");
            beMessenger_DispatchSelected(self->_messenger, "PLAY");
            beNDMWPanelObject_Close(panel);
            if (work->_isCursorGenerate != 0) {
                beNDMWPanelObject_SendModelCommand(panel, "i_wzslcursel", "SQ_CLOSE", (float *)0, 0);
            }
            ramState->_st0 = 3;
            ramState->_st3 = 0;
            ramState->_st2 = 0;
            ramState->_st1 = 0;
            return;
        case 3:
            ramState->_isRun = 0;
            ((WorkVt *)work)->Finished();
            break;
        }
    }
}

int beNDMWPanelWaza_FindEmergencyHealDisk(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram) {
    int len;
    int start;
    beNDMWPanelWazaInfoWork *work;
    work = (beNDMWPanelWazaInfoWork *)ram->_work;
    if (((beNDMWPanelObjectItem *)work->_panelItem)->_isNoHealing != 0) {
        return 0;
    }
    beMessenger_SelectGroup(self->_messenger, "GAMERAM");
    beMessenger_AppendInt(self->_messenger, ram->_ramNo);
    beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
    int o = ((int)beMessenger_GetObject(self->_messenger, 0));
    igObjectList *arr = (igObjectList *)igProperty_GetRecordFolder(o, "DISKFOLDER")->value;
    int best = -1;
    int idx = 0;
    int n = arr->_count - 2;
    int j = 0;
    int t;
    beNDMWItemDisk *it;
    beNDMWItemDisk **p;
    if (j < n) {
        p = (beNDMWItemDisk **)arr->_data;
        do {
            it = *p;
            if (it->_kazu != 0) {
                t = it->_recNo;
                if ((t <= 2 || t == 9) && best < t) {
                    len = idx - 3;
                    best = t;
                    start = idx;
                    if (len < 0) {
                        len = 0;
                    } else {
                        start = idx - len;
                    }
                }
                idx += 1;
            }
            j += 1;
            p += 1;
        } while (j < n);
    }
    if (best != -1) {
        ((PanelVt *)work->_panelItem)->Refresh();
        ((beNDMWPanelObjectItem *)work->_panelItem)->_cursor = start;
        ((beNDMWPanelObjectItem *)work->_panelItem)->_offset = len;
        ((beNDMWPanelObjectItem *)work->_panelItem)->_isEmg = 1;
        return 1;
    }
    return 0;
}

int beNDMWPanelWaza_FindEmergencyHealWaza(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram) {
    igObjectList *s5 = 0;
    int s4 = 0;
    int s3 = 0;
    beNDMWPanelWazaInfoWork *work = 0;
    int s1 = 0;
    int s0 = 0;
    work = (beNDMWPanelWazaInfoWork *)ram->_work;
    if (((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoHealing != 0) {
        return 0;
    }
    beMessenger_SelectGroup(self->_messenger, "GAMERAM");
    beMessenger_AppendInt(self->_messenger, ram->_ramNo);
    beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
    int o = ((int)beMessenger_GetObject(self->_messenger, 0));
    s1 = igProperty_GetRecord(o, "MP")->value;
    s5 = (igObjectList *)igProperty_GetRecordFolder(o, "WAZALIST")->value;
    s4 = s5->_count;
    s3 = s4 - 1;
    s0 = s3 * 4;
    if (s3 >= 0) {
        do {
            beNDMWItemBase *it = ((beNDMWItemBase **)(s5->_data + s0))[0];
            int t = it->_recNo;
            s4 -= 1;
            if (t >= 40 && t < 50 && s1 >= beNDMWItemBase_GetRecordInt(it, self, "MP")) {
                int r = s4 - 3;
                if (r < 0) {
                    r = 0;
                } else {
                    s4 -= r;
                }
                ((PanelVt *)work->_panelWaza)->Refresh();
                ((beNDMWPanelObjectWaza *)work->_panelWaza)->_cursor = s4;
                ((beNDMWPanelObjectWaza *)work->_panelWaza)->_offset = r;
                ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isEmg = 1;
                return 1;
            }
            s3 -= 1;
            s0 -= 4;
        } while (s3 >= 0);
    }
    return 0;
}

void beNDMWPanelWaza_OpenPanel(int self, beNDMWPanelWazaInfoRam *ram, int page, igObject *player) {
    beNDMWPanelWazaInfoWork *work = (beNDMWPanelWazaInfoWork *)ram->_work;
    beNDMWPanelObjectStat *stat;
    if (ram->_isRun != 0) {
        if (ram->_st0 == 3) {
            ram->_isRun = 1;
            work->_isWindowGenerate = 1;
            work->_isCursorGenerate = 0;
        }
        ram->_st0 = 0;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
    } else {
        ram->_isRun = 1;
        work->_isWindowGenerate = 1;
        work->_isCursorGenerate = 0;
        ram->_st0 = 0;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
    }
    work->_page = page;
    work->_retIsFire = 0;
    if (player != 0) {
        player->_refCount = player->_refCount + 1;
    }
    Rel::go((igObject *)work->_playerWork);
    work->_playerWork = (int)player;
    stat = (beNDMWPanelObjectStat *)work->_panelStat;
    if (player != 0) {
        player->_refCount = player->_refCount + 1;
    }
    Rel::go((igObject *)stat->_playerWork);
    stat->_playerWork = (int)player;
}

/* Owning stack reference to the freshly created panel work; released on scope exit (reference
 * count in the low 23 bits of _refCount). */





/* matching constructs: ok is a C++ bool (daddiu); the AppendBool/SetBool bool arguments are unsigned char so
 * the byte load is scheduled like retail. */
int beNDMWPanelWaza_OnMessage(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram, beMessengerWork *message) {
    unsigned int kind;
    beNDMWPanelWazaInfoWork *work;
    bool ok;
    void *alloc;
    void *obj;
    kind = beMessenger_ResolveEnumValue(self->_messenger, beNDMWPanelObject_GetMessageEnum(), message->_message);
    work = (beNDMWPanelWazaInfoWork *)ram->_work;
    if (work == 0) {
        alloc = igObject_GetAllocator(self);
        alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igSmartPointer<igObject> created((igObject *)beNDMWPanelWazaInfoWork_Create(alloc));
        { igObject *n = created.p; RET(n) { igObject *o = (igObject *)ram->_work; REL(o) } ram->_work = (int)n; }
        work = (beNDMWPanelWazaInfoWork *)created.p;
        HOOK(beNDMWPanelObjectWaza, work->_panelWaza)
        HOOK(beNDMWPanelObjectItem, work->_panelItem)
        HOOK(beNDMWPanelObjectStat, work->_panelStat)
    }
    switch (kind) {
    case 1:
    case 0:
    case 2:
    case 3:
        ok = true;
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SendNamed(self->_messenger, "SUBWND", 0, 0, "ISRUN");
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            ok = false;
        } else if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
            ok = false;
        }
        beMessenger_PopArgContext(self->_messenger);
        if (ok) {
            return 1;
        }
        break;
    default:
        break;
    }
    switch (kind) {
    case 0:
    case 1:
    case 2:
        obj = beMessenger_GetObject(self->_messenger, 0);
        switch (kind) {
        case 1:
            beNDMWPanelWaza_OpenPanel((int)self, (beNDMWPanelWazaInfoRam *)ram, 0, (igObject *)obj);
            break;
        case 0:
            beNDMWPanelWaza_OpenPanel((int)self, (beNDMWPanelWazaInfoRam *)ram, 1, (igObject *)obj);
            break;
        case 2:
            beNDMWPanelWaza_OpenPanel((int)self, (beNDMWPanelWazaInfoRam *)ram, 2, (igObject *)obj);
            break;
        }
        ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isEmg = 0;
        ((beNDMWPanelObjectItem *)work->_panelItem)->_isEmg = 0;
        ((beNDMWPanelObjectStat *)work->_panelStat)->_isEmg = 0;
        beMessenger_AppendBool(self->_messenger, 1);
        return 1;
    case 3:
        obj = beMessenger_GetObject(self->_messenger, 0);
        if (beNDMWPanelWaza_FindEmergencyHealDisk((beNDMWPanelWaza *)self, (beNDMWPanelWazaInfoRam *)ram) != 0) {
            beNDMWPanelWaza_OpenPanel((int)self, (beNDMWPanelWazaInfoRam *)ram, 1, (igObject *)obj);
        } else if (beNDMWPanelWaza_FindEmergencyHealWaza((beNDMWPanelWaza *)self, (beNDMWPanelWazaInfoRam *)ram) != 0) {
            beNDMWPanelWaza_OpenPanel((int)self, (beNDMWPanelWazaInfoRam *)ram, 0, (igObject *)obj);
        } else if (beBaseInfoRam_IsTimerExpired(ram, (const char *)"EMGHEAL") != 0) {
            beMessenger_PushArgContext(self->_messenger);
            beMessenger_SelectGroup(self->_messenger, "SOUND");
            beMessenger_AppendString(self->_messenger, (int)"CURSOR_NG");
            beMessenger_DispatchSelected(self->_messenger, "PLAY");
            beMessenger_PopArgContext(self->_messenger);
            beBaseInfoRam_StartTimer(ram, "EMGHEAL", 0x0FE502AA);
        }
        beMessenger_AppendBool(self->_messenger, 1);
        return 1;
    case 5:
        if (ram->_isRun == 0) {
            return 1;
        }
        ram->_st0 = 2;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        work->_retIsFire = 0;
        return 1;
    case 10:
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            beMessenger_AppendBool(self->_messenger, ram->_isRun);
        } else if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
            beMessenger_SetBool(self->_messenger, 0, ram->_isRun);
        }
        return 1;
    case 4:
        beMessenger_AppendBool(self->_messenger, ram->_isRun);
        switch (work->_page) {
        case 0:
            beMessenger_AppendBool(self->_messenger, 0);
            beMessenger_AppendBool(self->_messenger, work->_retIsFire);
            beMessenger_AppendString(self->_messenger, work->_retWazaLabel);
            break;
        case 1:
            beMessenger_AppendBool(self->_messenger, 1);
            beMessenger_AppendBool(self->_messenger, work->_retIsFire);
            break;
        case 2:
            beMessenger_AppendBool(self->_messenger, 0);
            beMessenger_AppendBool(self->_messenger, 0);
            break;
        }
        work->_retIsFire = 0;
        return 1;
    case 6:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoGateDisk = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoGateDisk = 0;
        }
        return 1;
    case 7:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoHealing = 1;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoHealing = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoHealing = 0;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoHealing = 0;
        }
        return 1;
    case 8:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoParaUp = 1;
        } else {
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoParaUp = 0;
        }
        return 1;
    case 9:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoCureling = 1;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoCureling = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoCureling = 0;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoCureling = 0;
        }
        return 1;
    default:
        return 0;
    }
}

int beNDMWPanelWaza_GetMeta(void)
{
    return g_beNDMWPanelWaza_metaObject[0];
}

int beNDMWPanelObjectStat_GetMeta(void)
{
    return g_beNDMWPanelObjectStat_metaObject[0];
}

void beNDMWPanelObjectStat_Fire(void)
{
}

int beNDMWPanelObjectItem_GetMeta(void)
{
    return g_beNDMWPanelObjectItem_metaObject[0];
}

int beNDMWPanelObjectWaza_GetMeta(void)
{
    return g_beNDMWPanelObjectWaza_metaObject[0];
}

#pragma pop

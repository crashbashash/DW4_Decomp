#include "dw4/reflected.h"
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define MCU(common) ((beNDMWMcUtilCtrl *)(common)->_mcUtilCtrl)
#define MCSLOT(common, i) (((beNDMWMcSlot **)((beNDMWMcSlotList *)MCU(common)->_slot)->_data)[i])
/* matching construct: the code reads the reference count as a signed int (igObject._refCount is reflected unsigned) */
#define REFS(o) (*(int *)&(o)->_refCount)
#define SLOT_PLAYER(p) ((beNDMWLoadSlotPlayer *)(p))
#define DEGI(p) ((beNDMWDegiData *)(p))
#define DNAME(d) ((unsigned short *)(d)->_dmNameUni)
#define REL(o) { igObject *rr = (o); if (rr != 0) { REFS(rr) = REFS(rr) - 1; if (((unsigned long long)((long long)REFS(rr) << 0x29) >> 0x29) == 0) { igObject_Destroy((void *)rr); } } }
#define ALLOC(a, self) { a = ((void *)igObject_GetAllocator(self)); a = g_useOwnerAllocator ? a : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0])); }
#define PLW_AT(list, off) (*(beNDMWLoadSavePlWork **)((char *)((beNDMWLoadSavePlWorkList *)(list))->_data + (off)))
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#define IDS(DST, REC, CAP, RESIZE) { igObjectList *l = igProperty_GetRecordFolder(props, REC)->value; int i; if (RESIZE) { if (l->_count > CAP) ObjectList_ResizeRetained(l, CAP); } i = 0; if (0 < l->_count) { do { DST[i] = ((IdObject **)l->_data)[i]->GetId(); i++; } while (i < l->_count); } if (i < CAP) { do { DST[i] = -1; i++; } while (i < CAP); } }
#define BYTES(DST, FN, REC) { igTDataList<unsigned char> *l = FN(props, REC)->value; int i = 0; if (0 < l->_count) { do { DST[i] = l->_data[i]; i++; } while (i < l->_count); } }
#define FINDN(DST, REC, N) { igObjectList *l = igProperty_GetRecordFolder(props, REC)->value; igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value; int a; for (a = 0; a < N; a++) { IdObject *v = ((IdObject **)l->_data)[a]; if (v == 0) { DST[a] = -1; } else { DST[a] = t->find(v); } } }
#define FIND1(DSTV, REC) { igObjectList *l = igProperty_GetRecordFolder(props, REC)->value; igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value; IdObject *v = ((IdObject **)l->_data)[0]; if (v == 0) { DSTV = -1; } else { DSTV = t->find(v); } }
#define FINDV(DST, REC) { igObjectList *l = igProperty_GetRecordFolder(props, REC)->value; igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value; int a; for (a = 0; a < l->_count; a++) { IdObject *v = ((IdObject **)l->_data)[a]; if (v == 0) { DST[a] = -1; } else { DST[a] = t->find(v); } } }
#define INTS(DST, FN, REC) { igIntList *l = FN(props, REC)->value; int i = 0; if (0 < l->_count) { do { DST[i] = ((int *)l->_data)[i]; i++; } while (i < l->_count); } }
#define OWNER_ALLOCATOR(dst, obj) { int alloc = igObject_GetAllocator(obj); if (g_useOwnerAllocator != 0) { dst = alloc; } else { dst = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); } }

extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beLua__RunNamedChunk(int, const char *, int);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" unsigned char beMessenger_GetBool(int, int);
extern "C" int beBaseInfoRam_StartTimer(int, const char *, unsigned long long);
extern "C" unsigned char beBaseInfoRam_IsTimerExpired(int, const char *);
extern "C" int igInsightCore_FindManager(...);
extern "C" int beFont_ConvertToUnicode(...);
extern "C" void *beNDMWLoadSlotPlayer_Create(...);
extern "C" void * beNDMWDegiData_Create(...);
extern "C" int List_Resize(void *, int, int);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void igObject_Destroy(void *);
extern "C" int List_RemoveWordAt(void *, int);
extern "C" int memcpy(...);
extern "C" void beNDMWDegiData__CopyFrom(beNDMWDegiData *dst, beNDMWDegiData *src);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" void strcpy(void *, void *);
extern "C" void ObjectList_ResizeRetained(void *, int);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void * StringPool_Allocate(...);
extern "C" void * StringPool_Construct(...);
extern "C" char * StringPool_Intern(...);
extern "C" int beMessenger_GetBoolCount(int);
extern "C" int memset(int, int, int);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, int, const char *);
extern "C" int beNDMWLoadCtrl2__GetInfoMeta(void);
extern "C" int beNDMWLoadCtrl2__GetMeta(void);
extern "C" int beMessenger_SendGroup(int, const char *, const char *);
extern "C" void * beBaseInfoDataList_Create(...);
extern "C" void * igProperty_FindByName(...);
extern "C" int LoadCtrl2Message_GetMetaEnum(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_ResolveEnumValue(...);
extern "C" char TEXTCTL_4[];
extern "C" char SWITCH_3[];
extern "C" char CLR_3[];
extern "C" void TextOrder_Configure(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font, const char *text, int align, int color);
extern "C" void TextOrder_PublishLine(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font);
extern "C" void TextOrder_ConfigureFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, const char *text, int align, int color);
extern "C" void TextOrder_ClearFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex);
extern "C" void TextOrder_PublishLineListOnly(beNDMWLoadIntf2TextOrder *order, int messageId);
extern "C" void TextOrder_ConfigureUnicode(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, int unicodeText, int align, int color);
/* Font names by player (row) and font (column). */
extern "C" const char *g_loadFontNames[][20];
extern "C" char txt_mem_lua[];
extern "C" char txt_Tar_lua[];
extern "C" int g_mdlEntity[4];
extern "C" int g_txtCallNo[4];
extern "C" void beNDMWLoadIntf2TextOrder_PublishIdLines(beNDMWLoadIntf2TextOrder *order, int messageId, int withFollowUp);
/* One text line of a load-screen message: the text-control line it fills and the font it uses. */
struct LoadMessageLine { const char *line; int player; int fontIndex; };
/* A load-screen message: its id (group in bits 12-15), the text call number the txt_ script plays,
 * and its lines. A message with a follow-up also plays the next entry's call number. The table
 * ends with an id of -1. */
struct LoadMessage { unsigned int id:20; unsigned int hasFollowUp:1; unsigned int pad:11; int txtCallNo; LoadMessageLine *lines; };
extern "C" LoadMessage g_loadMessageTable[];
extern "C" char LEFT_2[];
extern "C" char ALIGN[];
extern "C" char CENTER[];
extern "C" char RIGHT[];
extern "C" char DEFAULTCOLOR[];
extern "C" char CANCELCOLOR[];
extern "C" char TEXTSET_2[];
extern "C" char SET_2[];
extern "C" char REPLACEUNKNOWN[];
extern "C" bePadData *bePadManager_GetPadForPlayer(...);
extern "C" char CHRSELFONT06[];
extern "C" char CHRSELFONT16[];
extern "C" char SQ_LINESL00_3[];
extern "C" char SQ_LINESL01_2[];
extern "C" char SQ_LINEUP00_3[];
extern "C" char SQ_LINEDW01_3[];
extern "C" char SQ_LINEON00_3[];
extern "C" char SQ_LINEON01_3[];
extern "C" char SQ_NEXTSL00[];
extern "C" char SQ_NEXTON00[];
extern "C" void beNDMWLoadIntf2MesWin__Update(beNDMWLoadIntf2MesWin *win);
extern "C" char MODELCTRL_6[];
extern "C" char ISSEQNAME_3[];
extern "C" unsigned char beNDMWLoadIntf2MesWin__IsSequencePlaying(beNDMWLoadIntf2MesWin *win, int player, const char *target, const char *sequence);
extern "C" void beNDMWLoadIntf2MesWin__RequestOpen(beNDMWLoadIntf2MesWin *win);
extern "C" void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *win);
extern "C" void beNDMWLoadIntf2MesWin__RequestMessage(beNDMWLoadIntf2MesWin *win, int messageNo);
extern "C" void beNDMWLoadIntf2MesWin__RequestQuestion(beNDMWLoadIntf2MesWin *win, int messageNo, int cursor);
extern "C" void beNDMWLoadIntf2MesWin__RequestPrompt(beNDMWLoadIntf2MesWin *win, int messageNo);
extern "C" char j_chrselmesswin_3[];
extern "C" char SQ_WAIT[];
extern "C" void beNDMWLoadIntf2MesWin__Cancel(beNDMWLoadIntf2MesWin *win);
extern "C" unsigned char beNDMWLoadIntf2MesWin__GetIsCtrl(beNDMWLoadIntf2MesWin *win);
extern "C" int beNDMWLoadIntf2MesWin__GetCurPoint(beNDMWLoadIntf2MesWin *win);
extern "C" void beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *win);
extern "C" void beNDMWLoadIntf2MesWin__RequestSystemMessage(beNDMWLoadIntf2MesWin *win, int messageNo);
extern "C" void beNDMWLoadIntf2MesWin__EndSystemMessage(beNDMWLoadIntf2MesWin *win);
extern "C" void beNDMWLoadCtrl2CommonIntf__UpdateCutConnect(beNDMWLoadCtrl2CommonIntf *intf);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int promptNo, int questionNo, int cursor, int depth);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth);
extern "C" char MakeDataTime[];
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth);
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" int g_beFont_metaObject[4];
extern "C" unsigned char g_useOwnerAllocator;

/* Owning stack reference to the new slot player: constructed from the creating call and released
 * on scope exit (reference count in the low 23 bits of _refCount). Its destructor is emitted out
 * of line. */
class SlotPlayerRef {
public:
    igObject *p;
    SlotPlayerRef(igObject *o) : p(o) {}
    ~SlotPlayerRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)o); } }
};
/* Owning stack reference to one Digimon record (a new one appended to the slot player, then each
 * one re-read from its list): released at the end of each loop pass. Its destructor is emitted out
 * of line. */
class DegiDataRef {
public:
    igObject *p;
    DegiDataRef(igObject *o) : p(o) {}
    ~DegiDataRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)o); } }
};
extern "C" int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *intf, int player, int mesWin, int slot, int depth);
extern "C" char SaveDataTime[];
extern "C" int beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int saveIndex, int depth);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth);
extern "C" void beNDMWLoadCtrl2CommonIntf__GiveCtrlTo(beNDMWLoadCtrl2CommonIntf *intf, int player);
extern "C" void beNDMWLoadCtrl2CommonIntf__StartUtilFor(beNDMWLoadCtrl2CommonIntf *intf, int player, int state);
extern "C" void beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(beNDMWLoadCtrl2CommonIntf *intf, int player);
extern "C" int g_stringPool[4];
/* A Digimon's save block: the data block of a beNDMWDegiData, one record per property of the
 * save. playerName[0] is 0xFFFF once the name has been converted to unicode. */
struct DegiSaveRecord {
    unsigned char isUse; char pad1[3];
    int unique;
    char digimonName[32];
    unsigned short playerName[16];
    int level, hp, maxHp, mp, maxMp, xdata, bit;
    int deviceFolder[36];
    int diskFolder[12];
    unsigned char cardList[50]; char pad294[2];
    int bankDevice[96];
    int bankBit;
    int powerSocket[3];
    int powerPocket[5];
    int mainSlot;
    int mainPocket[5];
    int subSlot;
    unsigned char baseFlag[1024];
    unsigned char baseFlagFolder[12];
    int baseCounter[16];
    unsigned char baseIsUse[16];
    int baseLevel[16];
    int baseExp[16];
    int baseSkill[144];
    int baseUpcnt[176];
};
extern "C" void beNDMWDegiData__UpdateFieldsFromData(beNDMWDegiData *degi);
extern "C" void beNDMWDegiData__LoadFromBuffer(beNDMWDegiData *degi, int buffer);
class IdObject {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22();
    virtual int GetId();
};
/* A property record: three header words, then the value. */
struct PropByteRecord { int header[3]; unsigned char value; };
struct PropIntRecord { int header[3]; int value; };
struct PropStringRecord { int header[3]; char *value; };
struct PropObjListRecord { int header[3]; igObjectList *value; };
struct PropByteListRecord { int header[3]; igTDataList<unsigned char> *value; };
struct PropIntListRecord { int header[3]; igIntList *value; };
extern "C" PropByteRecord * igProperty_GetRecordByte(...);
extern "C" PropIntRecord * igProperty_GetRecord(...);
extern "C" PropObjListRecord * igProperty_GetRecordFolder(...);
extern "C" PropByteListRecord * igProperty_GetRecordArray(...);
extern "C" PropStringRecord * igProperty_GetRecordString(...);
extern "C" PropIntListRecord * igProperty_GetRecordIntList(...);
extern "C" char ISUSE_5[];
extern "C" char UNIQUE_2[];
extern "C" char LEVEL_5[];
extern "C" char HP_3[];
extern "C" char MHP_2[];
extern "C" char MP_3[];
extern "C" char MMP_2[];
extern "C" char PLAYERNAME_2[];
extern "C" char DIGIMONNAME_3[];
extern "C" char XDATA_2[];
extern "C" char BIT_4[];
extern "C" char DEVICEFOLDER_2[];
extern "C" char DISKFOLDER_2[];
extern "C" char CARDLIST[];
extern "C" char BANKDEVICE[];
extern "C" char BANKBIT[];
extern "C" char POWERSOCKET_2[];
extern "C" char POWERPOCKET_2[];
extern "C" char MAINSLOT_2[];
extern "C" char MAINPOCKET_2[];
extern "C" char SUBSLOT_2[];
extern "C" char BASE_FLAG_2[];
extern "C" char BASE_FLAGFOLDER_2[];
extern "C" char BASE_COUNTER_2[];
extern "C" char BASE_ISUSE_2[];
extern "C" char BASE_LEVEL_2[];
extern "C" char BASE_EXP_2[];
extern "C" char BASE_SKILL_2[];
extern "C" char BASE_UPCNT_2[];
extern "C" void beNDMWDegiData__LoadFromProperties(beNDMWDegiData *degi, int props);

static inline int listCount(const igObjectList *l) { return l->_count; }
struct RefCounted { int vtable; int refCount; };
struct RefCountedOps {
    static inline void Release(RefCounted *o) {
        if (o) {
            --o->refCount;
            if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)o);
        }
    }
};
/* matching construct: one RAII releasing holder per retail destructor copy; the cleanup table at 0x544c5c names 0x3832d0 (chunk buffer) and 0x1363f0 (list element / created item) */
struct ChunkRef { RefCounted *p; ChunkRef(RefCounted *x) : p(x) {} ~ChunkRef() { RefCounted *o = p; if (o != 0) { --o->refCount; if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0) igObject_Destroy((void *)o); } } };
struct ItemRef { RefCounted *p; ItemRef() {} ItemRef(RefCounted *x) : p(x) {} ItemRef(RefCounted *x, RetainReference) : p(x) { RefCounted *o = p; if (o != 0) ++o->refCount; } ~ItemRef() { RefCounted *o = p; if (o != 0) { --o->refCount; if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0) igObject_Destroy((void *)o); } } };
struct ObjectListOps {
    static inline void ReleaseAll(igObjectList *l) {
        int n = l->_count;
        int i;
        for (i = 0; i < n; i++)
            RefCountedOps::Release(((RefCounted **)l->_data)[i]);
    }
    static inline void ZeroAll(igObjectList *l) {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++)
            ((RefCounted **)l->_data)[j] = 0;
    }
    static inline void Clear(igObjectList *l) {
        if (listCount(l) > 0) {
            ReleaseAll(l);
            ZeroAll(l);
            l->_count = 0;
        }
    }
};
extern "C" beUnicodeObj *beUnicodeObj_Create(int);
extern "C" void beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
extern "C" ItemRef beNDMWDegiData__CreateItem(void *owner, int id);
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" void beNDMWDegiData__StoreToProperties(beNDMWDegiData *degi, void *props, int font);
extern "C" void beNDMWLoadSlotPlayer__WriteToBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer, int replaceIndex, beNDMWDegiData *replacement);
extern "C" void beNDMWLoadSlotPlayer__ReadFromBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer);
extern "C" igObject *beNDMWMcSlotXbox_Create(int);
extern "C" igObject *beNDMWMcSlotGC_Create(int);
extern "C" igObject *beNDMWMcSlotPS2_Create(int);
/* Owning stack reference to a new slot window of one of the three slot classes (kind 0..2 follows
 * kindHard), released on scope exit (reference count in the low 23 bits of _refCount). */
template <int kind> class SlotRef {
public:
    igObject *p;
    SlotRef(igObject *o) : p(o) {}
    ~SlotRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)o); } }
};
extern "C" void beNDMWMcUtilCtrl__Init(beNDMWMcUtilCtrl *util, int messenger, int kindHard);
extern "C" char SAVEUTILITY[];
extern "C" char GENERATE_5[];
extern "C" void beNDMWMcUtilCtrl__Generate(beNDMWMcUtilCtrl *util);
extern "C" char ISRDY[];
extern "C" unsigned char beNDMWMcUtilCtrl__CheckReady(beNDMWMcUtilCtrl *util);
extern "C" char REMOVE[];
extern "C" void beNDMWMcUtilCtrl__Remove(beNDMWMcUtilCtrl *util);
extern "C" bool beNDMWMcUtilCtrl__IsRemoved(beNDMWMcUtilCtrl *util);
extern "C" void beNDMWMcUtilCtrl__Request(beNDMWMcUtilCtrl *util, int kind, int slot);
extern "C" char GETDELIVER[];
extern "C" char REQUEST_FILEMAKE[];
extern "C" char REQUEST_FILEFIND[];
extern "C" char REQUEST_FORMAT[];
extern "C" char REQUEST_USE_CHECK[];
extern "C" char REQUEST_READ_MEDIA[];
extern "C" char REQUEST_WRITE_MEDIA[];
extern "C" char REQUEST_GETFREESIZE[];
extern "C" char REPORT_GAMEDATA[];
extern "C" char ISBUSY[];
extern "C" char GETRESULT[];
extern "C" beSvDeliver * beMessenger_GetObject(...);
extern "C" void beNDMWMcUtilCtrl__Update(beNDMWMcUtilCtrl *util);
extern "C" int g_beNDMWLoadCtrl2Info_metaObject[4];
extern "C" int g_beNDMWLoadCtrl2_metaObject[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" char LOADCTRL2[];
extern "C" void beNDMWLoadCtrl2__ResolvePadManager(beNDMWLoadCtrl2 *self);
extern "C" void beNDMWLoadCtrl2__RegisterReceiver(beNDMWLoadCtrl2 *self, int info);
extern "C" char CTRL_4[];
extern "C" char COMMONINTF_3[];
extern "C" char j_chrselback[];
extern "C" char SQ_OPEN_4[];
extern "C" char i_fadewn01_2[];
extern "C" char ISRUN_3[];
extern "C" char SQ_WTIN60[];
extern "C" char LOADINTF2_ALL[];
extern "C" char SQ_BLOUT30_2[];
extern "C" char SQ_CLOSE_6[];
extern "C" char SETSELECT_DATA[];
extern "C" char GAMERAM_7[];
extern "C" char GETCOMMON_5[];
extern "C" char NINZU_3[];
extern "C" char DIFFICULTY_3[];
extern "C" char CAMERAMODE_3[];
extern "C" char LIGHTMODE_3[];
extern "C" char TITLE2_2[];
extern "C" char GAMESTART_3[];
extern "C" char PLAYERPOINT_2[];
extern "C" char SETGENERATEPOS[];
extern "C" char gameStart_lua[];
extern "C" char STAGECTL_2[];
extern "C" char stagML11[];
extern "C" char NEXTSTAGE_2[];
extern "C" int g_propertyNameField[4];
extern "C" int g_beLua_metaObject[4];
extern "C" void beNDMWLoadCtrl2__Update(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram);
extern "C" igObject *beNDMWLoadCtrl2CtrlData_Create(int);
extern "C" igObject *beNDMWLoadCtrl2CommonIntf_Create(int);
extern "C" igObject *beNDMWLoadSavePlWork_Create(int);
extern "C" char GAMEDATAINIT_2[];
extern "C" char GETPLAYER_4[];
extern "C" int g_beSystem_metaObject[4];
/* Owning stack references while the controller list is wired up; each releases its object on scope
 * exit. */

class CtrlDataRef {
public:
    igObject *p;
    CtrlDataRef(igObject *o) : p(o) {}
    ~CtrlDataRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class CommonIntfRef {
public:
    igObject *p;
    CommonIntfRef(igObject *o) : p(o) {}
    ~CommonIntfRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class FlagWorkRef {
public:
    igObject *p;
    FlagWorkRef(igObject *o) : p(o) {}
    ~FlagWorkRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Releases an object reference, used for the old list during the list install. */
struct ReleaseRef { static inline void Apply(igObject *object) {
    if (object) {
        --object->_refCount;
        if ((object->_refCount & 0x7fffff) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" int beNDMWLoadCtrl2__OnMessage(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram, beBaseInfo *info);

void TextOrder_Configure(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font, const char *text, int align, int color) {
    switch (align) {
    case 0:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_AppendString(order->_messenger, LEFT_2);
        beMessenger_DispatchSelected(order->_messenger, ALIGN);
        break;
    case 1:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_AppendString(order->_messenger, CENTER);
        beMessenger_DispatchSelected(order->_messenger, ALIGN);
        break;
    case 2:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_AppendString(order->_messenger, RIGHT);
        beMessenger_DispatchSelected(order->_messenger, ALIGN);
        break;
    }
    switch (color) {
    case 0:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_DispatchSelected(order->_messenger, DEFAULTCOLOR);
        break;
    case 1:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_DispatchSelected(order->_messenger, CANCELCOLOR);
        break;
    case 2:
        break;
    }
    beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
    beMessenger_AppendString(order->_messenger, line);
    beMessenger_AppendString(order->_messenger, font);
    beMessenger_AppendString(order->_messenger, text);
    beMessenger_DispatchSelected(order->_messenger, TEXTSET_2);
    beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
    beMessenger_AppendString(order->_messenger, line);
    beMessenger_AppendString(order->_messenger, font);
    beMessenger_AppendString(order->_messenger, SET_2);
    beMessenger_DispatchSelected(order->_messenger, SWITCH_3);
}

void TextOrder_PublishLine(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font) {
    beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
    beMessenger_AppendString(order->_messenger, line);
    beMessenger_AppendString(order->_messenger, font);
    beMessenger_AppendString(order->_messenger, CLR_3);
    beMessenger_DispatchSelected(order->_messenger, SWITCH_3);
}

void TextOrder_ConfigureFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, const char *text, int align, int color) {
    TextOrder_Configure(order, line, g_loadFontNames[player][fontIndex], text, align, color);
}

void TextOrder_ClearFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex) {
    TextOrder_PublishLine(order, line, g_loadFontNames[player][fontIndex]);
}

void beNDMWLoadIntf2TextOrder_PublishIdLines(beNDMWLoadIntf2TextOrder *order, int messageId, int withFollowUp) {
    int group;
    int index;
    int i;
    int off;
    LoadMessage *e;
    LoadMessageLine *p;
    index = -1;
    i = 0;
    e = g_loadMessageTable;
    for (;;) {
        if (*(int *)e == -1) break;
        if (e->id == messageId) { index = i; break; }
        e++;
        i++;
    }
    if (index != -1) {
        off = index * (int)sizeof(LoadMessage);
        p = *(LoadMessageLine **)((char *)&g_loadMessageTable->lines + off);
        for (;;) {
            if (p->line == 0) break;
            TextOrder_PublishLine(order, p->line, g_loadFontNames[p->player][p->fontIndex]);
            p++;
        }
        group = messageId & 0xF000;
        g_txtCallNo[0] = *(int *)((char *)&g_loadMessageTable->txtCallNo + off);
        g_mdlEntity[0] = 0;
        switch (group) {
        case 0:
            beLua__RunNamedChunk(order->_lua, txt_mem_lua, 0);
            break;
        case 0x1000:
        case 0x2000:
        case 0x3000:
            beLua__RunNamedChunk(order->_lua, txt_Tar_lua, 0);
            break;
        }
        if (withFollowUp == 1 && (*(int *)((char *)g_loadMessageTable + off) & 0x100000)) {
            g_txtCallNo[0] = *(int *)((char *)&g_loadMessageTable->txtCallNo + (index + 1) * (int)sizeof(LoadMessage));
            g_mdlEntity[0] = 0;
            switch (group) {
            case 0:
                beLua__RunNamedChunk(order->_lua, txt_mem_lua, 0);
                break;
            case 0x1000:
            case 0x2000:
            case 0x3000:
                beLua__RunNamedChunk(order->_lua, txt_Tar_lua, 0);
                break;
            }
        }
    }
}

void TextOrder_PublishLineListOnly(beNDMWLoadIntf2TextOrder *order, int messageId) {
    LoadMessage *e; int i; LoadMessageLine *q;
    i = 0;
    e = g_loadMessageTable;
    for (;;) { if (e->id == messageId) break; e = e + 1; i = i + 1; }
    if (i != -1) {
        q = g_loadMessageTable[i].lines;
        for (;;) {
            if (q->line == 0) break;
            TextOrder_PublishLine(order, q->line, g_loadFontNames[q->player][q->fontIndex]);
            q = q + 1;
        }
    }
}

void TextOrder_ConfigureUnicode(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, int unicodeText, int align, int color) {
    const char *font;

    beMessenger_SelectGroup(order->_messenger, TEXTCTL_4);
    beMessenger_AppendObject(order->_messenger, unicodeText);
    beMessenger_AppendInt(order->_messenger, 0x3F);
    beMessenger_DispatchSelected(order->_messenger, REPLACEUNKNOWN);
    font = g_loadFontNames[player][fontIndex];
    switch (align) {
    case 0:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_AppendString(order->_messenger, LEFT_2);
        beMessenger_DispatchSelected(order->_messenger, ALIGN);
        break;
    case 1:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_AppendString(order->_messenger, CENTER);
        beMessenger_DispatchSelected(order->_messenger, ALIGN);
        break;
    case 2:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_AppendString(order->_messenger, RIGHT);
        beMessenger_DispatchSelected(order->_messenger, ALIGN);
        break;
    }
    beMessenger_SelectGroup(order->_messenger, TEXTCTL_4);
    beMessenger_AppendString(order->_messenger, line);
    beMessenger_AppendString(order->_messenger, font);
    beMessenger_AppendObject(order->_messenger, unicodeText);
    beMessenger_DispatchSelected(order->_messenger, TEXTSET_2);
    beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
    beMessenger_AppendString(order->_messenger, line);
    beMessenger_AppendString(order->_messenger, font);
    beMessenger_AppendString(order->_messenger, SET_2);
    beMessenger_DispatchSelected(order->_messenger, SWITCH_3);
    switch (color) {
    case 0:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_DispatchSelected(order->_messenger, DEFAULTCOLOR);
        return;
    case 1:
        beMessenger_SelectReceivers(order->_messenger, TEXTCTL_4, 0, -1);
        beMessenger_AppendString(order->_messenger, line);
        beMessenger_AppendString(order->_messenger, font);
        beMessenger_DispatchSelected(order->_messenger, CANCELCOLOR);
    case 2:
        ;
    }
}

void beNDMWLoadIntf2MesWin__Update(beNDMWLoadIntf2MesWin *win) {
    int line;
    if (win->_isWinOpen == 1) {
        if (win->_isSystemMes != 1) {
            if (win->_isCtrl == 1) {
                switch (win->_kindCtrl) {
                case 0:
                    switch (win->_statCtrl) {
                    case 0:
                        if (win->_curPoint == 0) {
                            beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_LINESL00_3);
                        } else {
                            beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_LINESL01_2);
                        }
                        win->_statCtrl = win->_statCtrl + 1;
                        break;
                    case 1: {
                        bePadData *pad = bePadManager_GetPadForPlayer(win->_padManager, win->_ramNo, 1);
                        int trigger = pad->_trigger;
                        int repeat = pad->_repeat;
                        int stick = pad->_lTrg | pad->_lRpt;
                        bool up = true;
                        if (!(stick & 1) && !((trigger | repeat) & 0x10)) up = false;
                        bool down = true;
                        if (!(stick & 4) && !((trigger | repeat) & 0x40)) down = false;
                        if (up) {
                            if (win->_curPoint == 1) {
                                win->_curPoint = 0;
                                beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_LINEUP00_3);
                                win->_statCtrl = 2;
                            }
                        } else if (down) {
                            if (win->_curPoint == 0) {
                                win->_curPoint = 1;
                                beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_LINEDW01_3);
                                win->_statCtrl = 3;
                            }
                        } else if (trigger & 0x4000) {
                            if (win->_curPoint == 0) {
                                beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_LINEON00_3);
                            } else {
                                beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_LINEON01_3);
                            }
                            win->_statCtrl = 4;
                        }
                        break;
                    }
                    case 2:
                        if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, j_chrselmesswin_3, SQ_LINEUP00_3) == 0) win->_statCtrl = 1;
                        break;
                    case 3:
                        if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, j_chrselmesswin_3, SQ_LINEDW01_3) == 0) win->_statCtrl = 1;
                        break;
                    case 4:
                        if (win->_curPoint == 0) {
                            if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, j_chrselmesswin_3, SQ_LINEON00_3) == 0) {
                                beNDMWLoadIntf2MesWin__RequestMesErase(win);
                                win->_isSelect = 1;
                                win->_isCtrl = 0;
                            }
                        } else if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, j_chrselmesswin_3, SQ_LINEON01_3) == 0) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(win);
                            win->_isSelect = 1;
                            win->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                case 1:
                    switch (win->_statCtrl) {
                    case 0:
                        beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_NEXTSL00);
                        win->_statCtrl = win->_statCtrl + 1;
                        break;
                    case 1:
                        if (bePadManager_GetPadForPlayer(win->_padManager, win->_ramNo, 1)->_trigger & 0x4000) {
                            beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_NEXTON00);
                            win->_statCtrl = win->_statCtrl + 1;
                        }
                        break;
                    case 2:
                        if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, j_chrselmesswin_3, SQ_NEXTON00) == 0) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(win);
                            win->_isSelect = 1;
                            win->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                }
            }
        } else {
            switch (win->_sysStat) {
            case 0:
                beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_WAIT);
                win->_sysStat = win->_sysStat + 1;
                break;
            case 1:
                break;
            }
        }
        if (win->_isMesCom == 1) {
            if (win->_isSystemMes == 1) {
                beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)win->_textOrder, win->_sysMesNo, 1);
            } else if (win->_isMesErase == 0) {
                win->_isDisp = 1;
                beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)win->_textOrder, win->_mesNo, 1);
            } else {
                line = 0;
                do {
                    TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)win->_textOrder, CHRSELFONT06, win->_ramNo, line);
                    line += 1;
                } while (line < 4);
                line = 4;
                do {
                    TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)win->_textOrder, CHRSELFONT16, win->_ramNo, line - 4);
                    line += 1;
                } while (line < 6);
                win->_isMesErase = 0;
                win->_isDisp = 0;
                if (win->_isWinClose == 1) {
                    win->_isWinOpen = 0;
                }
            }
            win->_isMesCom = 0;
        }
    }
}

unsigned char beNDMWLoadIntf2MesWin__IsSequencePlaying(beNDMWLoadIntf2MesWin *win, int player, const char *target, const char *sequence) {
    beMessenger_SelectReceivers(win->_messenger, MODELCTRL_6, target, player);
    beMessenger_AppendString(win->_messenger, sequence);
    beMessenger_DispatchSelected(win->_messenger, ISSEQNAME_3);
    return beMessenger_GetBool(win->_messenger, 0);
}

void beNDMWLoadIntf2MesWin__RequestOpen(beNDMWLoadIntf2MesWin *win) {
    win->_isWinOpen = 1;
    win->_isWinClose = 0;
    win->_isSelect = 0;
    win->_isCtrl = 0;
    win->_isSystemMes = 0;
    win->_isMesErase = 0;
    win->_isMesCom = 0;
}

void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *win) {
    beNDMWLoadIntf2MesWin__RequestMesErase(win);
    win->_isWinClose = 1;
}

void beNDMWLoadIntf2MesWin__RequestMessage(beNDMWLoadIntf2MesWin *win, int messageNo) {
    win->_isMesCom = 1;
    win->_mesNo = messageNo;
}

void beNDMWLoadIntf2MesWin__RequestQuestion(beNDMWLoadIntf2MesWin *win, int messageNo, int cursor) {
    win->_isMesCom = 1;
    win->_isCtrl = 1;
    win->_mesNo = messageNo;
    win->_curPoint = cursor;
    win->_statCtrl = 0;
    win->_kindCtrl = 0;
}

void beNDMWLoadIntf2MesWin__RequestPrompt(beNDMWLoadIntf2MesWin *win, int messageNo) {
    win->_isMesCom = 1;
    win->_isCtrl = 1;
    win->_mesNo = messageNo;
    win->_statCtrl = 0;
    win->_kindCtrl = 1;
}

void beNDMWLoadIntf2MesWin__Cancel(beNDMWLoadIntf2MesWin *win) {
    win->_isCtrl = 0;
    beMessenger_SendNamed(win->_messenger, MODELCTRL_6, j_chrselmesswin_3, win->_ramNo, SQ_WAIT);
    beNDMWLoadIntf2MesWin__RequestMesErase(win);
}

/* Whether a question or prompt is still waiting for the player. */
unsigned char beNDMWLoadIntf2MesWin__GetIsCtrl(beNDMWLoadIntf2MesWin *win)
{
    return win->_isCtrl;
}

int beNDMWLoadIntf2MesWin__GetCurPoint(beNDMWLoadIntf2MesWin *win)
{
    return win->_curPoint;
}

void beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *win) {
    win->_isMesErase = 1;
    win->_isMesCom = 1;
}

void beNDMWLoadIntf2MesWin__RequestSystemMessage(beNDMWLoadIntf2MesWin *win, int messageNo) {
    win->_isMesCom = 1;
    win->_isSystemMes = 1;
    win->_sysMesNo = messageNo;
    win->_sysStat = 0;
}

void beNDMWLoadIntf2MesWin__EndSystemMessage(beNDMWLoadIntf2MesWin *win) {
    win->_isSystemMes = 0;
    if (win->_isDisp == 1) {
        if (win->_isCtrl == 1) {
            switch (win->_kindCtrl) {
            case 0:
                beNDMWLoadIntf2MesWin__RequestQuestion(win, win->_mesNo, win->_curPoint);
                return;
            case 1:
                beNDMWLoadIntf2MesWin__RequestPrompt(win, win->_mesNo);
                return;
            }
        } else {
            beNDMWLoadIntf2MesWin__RequestMessage(win, win->_mesNo);
        }
    } else {
        beNDMWLoadIntf2MesWin__RequestMesErase(win);
    }
}

/* The interface's const accessor for its memory-card utility; it takes the interface by reference, as
 * a member function takes `this`. The compiler does not reuse a loop guard's read of a const object
 * in the loop's body, so the loop below loads the utility again for each use. */
static inline beNDMWMcUtilCtrl *mcUtilCtrl(const beNDMWLoadCtrl2CommonIntf &intf) { return (beNDMWMcUtilCtrl *)intf._mcUtilCtrl; }

void beNDMWLoadCtrl2CommonIntf__UpdateCutConnect(beNDMWLoadCtrl2CommonIntf *intf) {
    int slot;
    int slotPlayer;
    igIntList *accessList;
    int k;
    beNDMWMcUtilCtrl__Update(mcUtilCtrl(*intf));
    PLW(intf, 0)->_isCutConnect = 0;
    PLW(intf, 1)->_isCutConnect = 0;
    PLW(intf, 2)->_isCutConnect = 0;
    PLW(intf, 3)->_isCutConnect = 0;
    for (slot = 0; slot < ((beNDMWMcSlotList *)mcUtilCtrl(*intf)->_slot)->_count; slot++) {
        if (((beNDMWMcSlot **)((beNDMWMcSlotList *)mcUtilCtrl(*intf)->_slot)->_data)[slot]->_isConnect == 0) {
            for (slotPlayer = 0; slotPlayer < ((beNDMWLoadSlotPlayerList *)intf->_slotSaveData)->_count; slotPlayer++) {
                if (slot == ((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)intf->_slotSaveData)->_data)[slotPlayer]->_connectNO) {
                    accessList = (igIntList *)((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)intf->_slotSaveData)->_data)[slotPlayer]->_accessPlList;
                    for (k = 0; k < accessList->_count; k++) {
                        PLW(intf, ((int *)accessList->_data)[k])->_isCutConnect = 1;
                    }
                }
            }
        }
    }
}

int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int promptNo, int questionNo, int cursor, int depth) {
    int point;
    int result;
    int state;
    beNDMWLoadSavePlWork *work;

    result = 0;
    state = 0;
    switch (depth) {
    case 0:
        state = PLW(intf, player)->_sysStat0;
        break;
    case 1:
        state = PLW(intf, player)->_sysStat1;
        break;
    case 2:
        state = PLW(intf, player)->_sysStat2;
        break;
    case 3:
        state = PLW(intf, player)->_sysStat3;
        break;
    }
    switch (state) {
    case 0:
        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, promptNo);
        state += 1;
        break;
    case 1:
        if (beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) == 0) {
            state += 1;
        }
        break;
    case 2:
        beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, questionNo, cursor);
        state += 1;
        break;
    case 3:
        if (beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) == 0) {
            point = beNDMWLoadIntf2MesWin__GetCurPoint(mesWin);
            switch (point) {
            case 0:
                result = 1;
                break;
            case 1:
                result = 2;
                break;
            }
        }
        break;
    }
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state;
        work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth) {
    int result;
    int state;
    beNDMWMcUtilCtrl *util;
    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 3, slot);
        state += 1;
        break;
    case 1:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: state += 1; break;
            default: result = 2; break;
            }
        }
        break;
    case 2:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 1, slot);
        state += 1;
        break;
    case 3:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: result = 1; break;
            default: result = 2; break;
            }
        }
        break;
    }
    switch (depth) {
    case 0: {
        beNDMWLoadSavePlWork *r = PLW(intf, player);
        r->_sysStat0 = state; r->_sysStat3 = 0; r->_sysStat2 = 0; r->_sysStat1 = 0;
        break; }
    case 1: {
        beNDMWLoadSavePlWork *r = PLW(intf, player);
        r->_sysStat1 = state; r->_sysStat3 = 0; r->_sysStat2 = 0;
        break; }
    case 2: {
        beNDMWLoadSavePlWork *r = PLW(intf, player);
        r->_sysStat2 = state; r->_sysStat3 = 0;
        break; }
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth) {
    int result;
    int state;
    int messageNo;
    beNDMWLoadSavePlWork *work;
    beNDMWMcUtilCtrl *util;
    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        messageNo = -1;
        switch (intf->_kindHard) {
        case 0: messageNo = (player << 16) | 0x1003; break;
        case 1: messageNo = (player << 16) | 0x2003; break;
        case 2: messageNo = (player << 16) | 0x3003; break;
        }
        beNDMWLoadIntf2MesWin__RequestMessage(mesWin, messageNo);
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 6, slot);
        state += 1;
        break;
    case 1:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: state += 1; break;
            default: result = 2; break;
            }
        }
        break;
    case 2:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 0, slot);
        beBaseInfoRam_StartTimer(intf->_inforam, MakeDataTime, 0xB2D05E00ULL);
        state += 1;
        break;
    case 3:
        if (MCSLOT(intf, slot)->_isConnect == 1) {
            if (beBaseInfoRam_IsTimerExpired(intf->_inforam, MakeDataTime) == 1) {
                state += 1;
                goto waitResult;
            }
            break;
        } else {
            state += 1;
        }
    case 4:
    waitResult:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: result = 1; break;
            default: result = 2; break;
            }
        }
        break;
    }
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state; work->_sysStat3 = 0; work->_sysStat2 = 0; work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state; work->_sysStat3 = 0; work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state; work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

static inline int countOf(const igIntList *list) { return list->_count; }

int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *intf, int player, int mesWin, int slot, int depth) {
    int result;
    int state;
    void *alloc;
    int count;
    igIntList *accessList;
    int i;
    int j;
    beNDMWLoadSavePlWork *work;
    unsigned short *unicodeText;
    int charIndex;
    int nextState;
    unsigned short *digimonName;

    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 4, (int)slot);
        nextState = state + 1;
        goto storeState;
    case 1:
        if (MCU(intf)->_isResult == 1) {
            result = 2;
            switch (MCU(intf)->_result) {
            case 2: {
                result = 1;
                ALLOC(alloc, intf);
                SlotPlayerRef slotPlayer((igObject *)beNDMWLoadSlotPlayer_Create(alloc));
                for (i = 0; i < 4; i++) {
                    ALLOC(alloc, intf);
                    DegiDataRef degi((igObject *)beNDMWDegiData_Create(alloc));
                    ObjectList_AppendRetained(SLOT_PLAYER(slotPlayer.p)->_saveDataList, degi.p);
                }
                beNDMWLoadSlotPlayer__ReadFromBuffer((beNDMWLoadSlotPlayer *)slotPlayer.p, (int)(((beSaveDataDeliver *)MCU(intf)->_svData)->_data));
                SLOT_PLAYER(slotPlayer.p)->_connectNO = slot;
                accessList = (igIntList *)SLOT_PLAYER(slotPlayer.p)->_accessPlList;
                count = accessList->_count;
                if (count < accessList->_capacity) accessList->_count = countOf(accessList) + 1;
                else List_Resize(accessList, count + 1, 4);
                ((int *)accessList->_data)[count] = player;
                ObjectList_AppendRetained(intf->_slotSaveData, slotPlayer.p);
                for (j = 0; j < 4; j++) {
                    DegiDataRef degi((igObject *)((beNDMWDegiData **)((igObjectList *)SLOT_PLAYER(slotPlayer.p)->_saveDataList)->_data)[j]);
                    if (degi.p != 0) REFS(degi.p) = REFS(degi.p) + 1;
                    if (DEGI(degi.p)->_isUse == 1 && DNAME(DEGI(degi.p))[0] != 0xFFFF) {
                        igObject *str; /* the unicode text beFont_ConvertToUnicode hands back (declared here: its slot sits below the record reference) */
                        digimonName = (unsigned short *)DEGI(degi.p)->_dmName;
                        {
                            int insightEntry = igInsightCore_FindManager(intf->_insight, g_beFont_metaObject[0]);
                            beFont_ConvertToUnicode(&str, insightEntry, digimonName);
                        }
                        unicodeText = (unsigned short *)((beUnicodeObj *)str)->_buffer;
                        for (charIndex = 0; ; ) {
                            ((unsigned short *)DEGI(degi.p) + 5)[charIndex] /* matching construct: object-based index keeps the addu operand order */ = unicodeText[charIndex];
                            if (unicodeText[charIndex] == 0) break;
                            charIndex++;
                            if (charIndex >= 8) break;
                        }
                        for (; charIndex < 8; charIndex++) {
                            ((unsigned short *)DEGI(degi.p) + 5)[charIndex] = 0;
                        }
                        DNAME(DEGI(degi.p))[0] = 0xFFFF;
                        REL(str);
                    }
                }
                PLW(intf, player)->_haveSaveData = (int)slotPlayer.p;
                /* matching construct: leaving the block through this jump to the state store releases the slot
                 * player on the jump path, which keeps retail's branch after the release; falling out of the
                 * switch folds it away */
                nextState = state;
                goto storeState;
            }
            }
        }
        break;
    }
    nextState = state;
storeState:
    state = nextState;
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state;
        work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

int beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int saveIndex, int depth) {
    int result;
    int state;
    beNDMWLoadSavePlWork *work;
    beNDMWMcUtilCtrl *util;
    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWLoadSlotPlayer__WriteToBuffer((beNDMWLoadSlotPlayer *)PLW(intf, player)->_haveSaveData, ((beSaveDataDeliver *)MCU(intf)->_svData)->_data, saveIndex, ((beNDMWDegiData **)((beNDMWDegiDataList *)intf->_gameUseData)->_data)[player]);
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 5, slot);
        beBaseInfoRam_StartTimer(intf->_inforam, SaveDataTime, 0xB2D05E00ULL);
        state += 1;
        break;
    case 1:
        if (MCSLOT(intf, slot)->_isConnect == 1) {
            if (beBaseInfoRam_IsTimerExpired(intf->_inforam, SaveDataTime) == 1) {
                state += 1;
                goto waitResult;
            }
            break;
        } else {
            state += 1;
        }
    case 2:
    waitResult:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: result = 1; beNDMWDegiData__CopyFrom(((beNDMWDegiData **)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)PLW(intf, player)->_haveSaveData)->_saveDataList)->_data)[saveIndex], ((beNDMWDegiData **)((beNDMWDegiDataList *)intf->_gameUseData)->_data)[player]); break;
            default: result = 2; break;
            }
        }
        break;
    }
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state; work->_sysStat3 = 0; work->_sysStat2 = 0; work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state; work->_sysStat3 = 0; work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state; work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth) {
    int result = 0;
    int state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 2, slot);
        state++;
        MCU(intf)->_isFormatRun = 1;
        break;
    case 1: {
        beNDMWMcUtilCtrl *util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) { case 2: result = 1; break; default: result = 2; break; }
        }
        break;
    }
    }
    switch (depth) {
    case 0: {
        beNDMWLoadSavePlWork *work = PLW(intf, player);
        work->_sysStat0 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        break;
    }
    case 1: {
        beNDMWLoadSavePlWork *work = PLW(intf, player);
        work->_sysStat1 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        break;
    }
    case 2: {
        beNDMWLoadSavePlWork *work = PLW(intf, player);
        work->_sysStat2 = state;
        work->_sysStat3 = 0;
        break;
    }
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

void beNDMWLoadCtrl2CommonIntf__GiveCtrlTo(beNDMWLoadCtrl2CommonIntf *intf, int player) {
    int i;
    beNDMWLoadSavePlWork *work;
    i = 0;
    do {
        work = PLW(intf, i);
        work->_sysStat0 = 1;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        PLW(intf, i)->_isCtrl = 0;
        PLW(intf, i)->_sysCount0 = 60;
        i++;
    } while (i < 4);
    work = PLW(intf, player);
    work->_sysStat0 = 0;
    work->_sysStat3 = 0;
    work->_sysStat2 = 0;
    work->_sysStat1 = 0;
    PLW(intf, player)->_isCtrl = 1;
    PLW(intf, player)->_sysCount0 = 0;
}

void beNDMWLoadCtrl2CommonIntf__StartUtilFor(beNDMWLoadCtrl2CommonIntf *intf, int player, int state) {
    int playerOffset;
    int i;
    int offset;
    int *count;
    beNDMWLoadSavePlWork *work;

    i = 0;
    offset = 0;
    do {
        work = PLW_AT(intf->_flagWork, offset);
        work->_sysStat0 = 1;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        PLW_AT(intf->_flagWork, offset)->_isCtrl = 0;
        work = PLW_AT(intf->_flagWork, offset);
        count = &work->_sysCount0;
        if (*count <= 0) {
            *count = 0xA;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    playerOffset = player * 4;
    work = PLW_AT(intf->_flagWork, playerOffset);
    work->_sysStat0 = state;
    work->_sysStat3 = 0;
    work->_sysStat2 = 0;
    work->_sysStat1 = 0;
    PLW_AT(intf->_flagWork, playerOffset)->_isCtrl = 1;
    PLW_AT(intf->_flagWork, playerOffset)->_sysCount0 = 0;
    intf->_utilUsePlNo = player;
}

void beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(beNDMWLoadCtrl2CommonIntf *intf, int player) {
    bool found = false;
    beNDMWLoadSlotPlayerList *slotPlayers = (beNDMWLoadSlotPlayerList *)intf->_slotSaveData;
    for (int i = slotPlayers->_count - 1; i >= 0; i--) {
        int offset; igIntList *accessList; int j; int count; igIntList *list;
        accessList = (igIntList *)((beNDMWLoadSlotPlayer **)slotPlayers->_data)[i]->_accessPlList; count = accessList->_count; list = accessList; j = 0;
        if (j < count) { offset = 0;
          do { if (player == *(int*)(list->_data + offset)) { List_RemoveWordAt(accessList, j); found = true; break; } j++; offset += 4; list = accessList; } while (j < count); }
        if (found == true) break;
    }
    if (found == true) {
        for (int i = slotPlayers->_count - 1; i >= 0; i--) {
            beNDMWLoadSlotPlayer *slotPlayer = ((beNDMWLoadSlotPlayer **)slotPlayers->_data)[i];
            if (((igIntList *)slotPlayer->_accessPlList)->_count == 0) {
                if (slotPlayer != 0) {
                    slotPlayer->_refCount = slotPlayer->_refCount - 1;
                    if ((slotPlayer->_refCount & 0x7FFFFF) == 0) igObject_Destroy(slotPlayer);
                }
                List_RemoveWordAt(slotPlayers, i);
                ((beNDMWLoadSlotPlayer **)slotPlayers->_data)[slotPlayers->_count] = 0;
            }
        }
    }
}

/* The size reads as unsigned, so it is loaded before the copy's other arguments. */
static inline unsigned dataSize(const beNDMWDegiData *data) { return data->_dataSize; }

void beNDMWDegiData__CopyFrom(beNDMWDegiData *dst, beNDMWDegiData *src) {
    memcpy(dst->_data, src->_data, dataSize(dst));
    beNDMWDegiData__UpdateFieldsFromData(dst);
}

void beNDMWDegiData__UpdateFieldsFromData(beNDMWDegiData *degi) {
    DegiSaveRecord *record;
    int name, v, old;
    int *header;
    record = (DegiSaveRecord *)degi->_data;
    degi->_isUse = record->isUse;
    degi->_lv = record->level;
    degi->_hp = record->hp;
    degi->_maxHp = record->maxHp;
    degi->_mp = record->mp;
    degi->_maxMp = record->maxMp;
    if (g_stringPool[0] == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct(v));
        g_stringPool[0] = v;
    }
    name = ((int)StringPool_Intern(g_stringPool[0], record->digimonName));
    old = degi->_dmkind;
    if (old != 0) {
        header = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*header, header);
    }
    degi->_dmkind = name;
    if (g_stringPool[0] == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct(v));
        g_stringPool[0] = v;
    }
    name = ((int)StringPool_Intern(g_stringPool[0], (char *)record->playerName));
    old = degi->_dmName;
    if (old != 0) {
        header = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*header, header);
    }
    degi->_dmName = name;
    {
        int n;
        unsigned short *pa;
        char *p;
        pa = record->playerName;
        n = 0;
        p = (char *)degi;
        degi->_id = record->unique;
        do {
            unsigned short v = *pa;
            if (v == 0) break;
            *(unsigned short *)(p + 8) = v;
            n += 1;
            pa += 1;
            p += 2;
        } while (n < 9);
        for (; n < 9; n++) {
            *(unsigned short *)((char *)degi + n * 2 + 8) = 0;
        }
    }
}


void beNDMWDegiData__LoadFromBuffer(beNDMWDegiData *degi, int buffer) {
    memcpy(degi->_data, buffer, dataSize(degi));
    beNDMWDegiData__UpdateFieldsFromData((beNDMWDegiData *)degi);
}

void beNDMWDegiData__LoadFromProperties(beNDMWDegiData *degi, int props) {
    DegiSaveRecord *record = (DegiSaveRecord *)degi->_data;
    record->isUse = igProperty_GetRecordByte(props, ISUSE_5)->value;
    record->unique = igProperty_GetRecord(props, UNIQUE_2)->value;
    record->level = igProperty_GetRecord(props, LEVEL_5)->value;
    record->hp = igProperty_GetRecord(props, HP_3)->value;
    record->maxHp = igProperty_GetRecord(props, MHP_2)->value;
    record->mp = igProperty_GetRecord(props, MP_3)->value;
    record->maxMp = igProperty_GetRecord(props, MMP_2)->value;
    {
        igStringObjList *sl = (igStringObjList *)igProperty_GetRecordFolder(props, PLAYERNAME_2)->value;
        if (sl->_count != 0) {
            igSmartPointer<beUnicodeObj> s(((beUnicodeObj **)sl->_data)[0]);
            if (s.p != 0) s.p->_refCount = s.p->_refCount + 1;
            {
                unsigned short *src;
                unsigned short *base;
                int i;
                unsigned short *dst;
                base = record->playerName;
                i = 0;
                dst = base;
                src = (unsigned short *)s.p->_buffer;
            L1: dst[1] = *src;
                if (*src == 0) { dst = base + i; goto T; }
                src++; dst++; i++; goto L1;
            B:  dst[1] = 0; dst++; i++;
            T:  if (i < 8) goto B;
                base[0] = 0xffff;
            }
        }
    }
    {
        PropStringRecord *rs = igProperty_GetRecordString(props, DIGIMONNAME_3);
        char *str = rs->value;
        if (str != 0) strcpy(record->digimonName, str);
    }
    record->xdata = igProperty_GetRecord(props, XDATA_2)->value;
    record->bit = igProperty_GetRecord(props, BIT_4)->value;
    IDS(record->deviceFolder, DEVICEFOLDER_2, 36, 1)
    IDS(record->diskFolder, DISKFOLDER_2, 12, 1)
    BYTES(record->cardList, igProperty_GetRecordArray, CARDLIST)
    IDS(record->bankDevice, BANKDEVICE, 96, 0)
    record->bankBit = igProperty_GetRecord(props, BANKBIT)->value;
    FINDN(record->powerSocket, POWERSOCKET_2, 3)
    FINDN(record->powerPocket, POWERPOCKET_2, 5)
    FIND1(record->mainSlot, MAINSLOT_2)
    FINDV(record->mainPocket, MAINPOCKET_2)
    FIND1(record->subSlot, SUBSLOT_2)
    BYTES(record->baseFlag, igProperty_GetRecordArray, BASE_FLAG_2)
    BYTES(record->baseFlagFolder, igProperty_GetRecordArray, BASE_FLAGFOLDER_2)
    INTS(record->baseCounter, igProperty_GetRecordIntList, BASE_COUNTER_2)
    BYTES(record->baseIsUse, igProperty_GetRecordArray, BASE_ISUSE_2)
    INTS(record->baseLevel, igProperty_GetRecordIntList, BASE_LEVEL_2)
    INTS(record->baseExp, igProperty_GetRecordIntList, BASE_EXP_2)
    INTS(record->baseSkill, igProperty_GetRecordIntList, BASE_SKILL_2)
    INTS(record->baseUpcnt, igProperty_GetRecordIntList, BASE_UPCNT_2)
    beNDMWDegiData__UpdateFieldsFromData((beNDMWDegiData *)degi);
}

extern "C" igObject *beNDMWItemDisk_Create(int);
extern "C" igObject *beNDMWItemAbilityChip_Create(int);
extern "C" igObject *beNDMWItemYellowArmor_Create(int);
extern "C" igObject *beNDMWItemBlueArmor_Create(int);
extern "C" igObject *beNDMWItemWeapon_Create(int);
/* matching construct: dummy virtual slots so InitFromId dispatches through the retail vtable offset */
struct ItemVirtual { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int InitFromId(int); };
/* matching construct: one releasing holder class per retail destructor copy (the table at 0x544c20 names 0x3d9d50, 0x3d9cd0, 0x3d9c50, 0x3d9bd0 and 0x3b9ba0; the last is not the copy other members of this file name for their holders) */
template <int K> struct CreatedItemRef { igObject *p; CreatedItemRef(igObject *o) : p(o) {} ~CreatedItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };

static inline int itemAllocator(void *owner) {
    int alloc = igObject_GetAllocator(owner);
    int a;
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    }
    return a;
}

ItemRef beNDMWDegiData__CreateItem(void *owner, int id) {
    int kind = (id >> 12) & 0xF;
    if (kind == 0) {
        {
            CreatedItemRef<1> item((igObject *)beNDMWItemWeapon_Create(itemAllocator(owner)));
            ((ItemVirtual *)item.p)->InitFromId(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 1) {
        {
            CreatedItemRef<2> item((igObject *)beNDMWItemBlueArmor_Create(itemAllocator(owner)));
            ((ItemVirtual *)item.p)->InitFromId(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 2) {
        {
            CreatedItemRef<3> item((igObject *)beNDMWItemYellowArmor_Create(itemAllocator(owner)));
            ((ItemVirtual *)item.p)->InitFromId(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 3) {
        {
            CreatedItemRef<4> item((igObject *)beNDMWItemAbilityChip_Create(itemAllocator(owner)));
            ((ItemVirtual *)item.p)->InitFromId(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 4) {
        {
            CreatedItemRef<5> item((igObject *)beNDMWItemDisk_Create(itemAllocator(owner)));
            ((ItemVirtual *)item.p)->InitFromId(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else {
        return ItemRef(0, kRetainReference);
    }
}

void beNDMWDegiData__StoreToProperties(beNDMWDegiData *degi, void *props, int font) {
    DegiSaveRecord *record = (DegiSaveRecord *)degi->_data;
    igProperty_GetRecordByte(props, ISUSE_5)->value = record->isUse;
    igProperty_GetRecord(props, UNIQUE_2)->value = record->unique;
    igProperty_GetRecord(props, LEVEL_5)->value = record->level;
    igProperty_GetRecord(props, HP_3)->value = record->hp;
    igProperty_GetRecord(props, MHP_2)->value = record->maxHp;
    igProperty_GetRecord(props, MP_3)->value = record->mp;
    igProperty_GetRecord(props, MMP_2)->value = record->maxMp;
    char *digimonName = record->digimonName;
    PropStringRecord *rs = igProperty_GetRecordString(props, DIGIMONNAME_3);
    if (((void * *)g_stringPool)[0] == 0) {
        void *p = StringPool_Allocate(16);
        if (p != 0)
            p = StringPool_Construct(p);
        ((void * *)g_stringPool)[0] = p;
    }
    char *interned = StringPool_Intern(((void * *)g_stringPool)[0], digimonName);
    char *old = rs->value;
    if (old != 0) {
        int *hdr = (int *)old - 2;
        int rc = hdr[1] - 1;
        hdr[1] = rc;
        if (rc == 0)
            StringChunk_ReleaseHeader(hdr[0], hdr);
    }
    rs->value = interned;
    igObjectList *playerNameList = igProperty_GetRecordFolder(props, PLAYERNAME_2)->value;
    ObjectListOps::Clear(playerNameList);
    int alloc = igObject_GetAllocator(degi);
    int a;
    if (g_useOwnerAllocator != 0)
        a = alloc;
    else
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    {
    ChunkRef nameText((RefCounted *)beUnicodeObj_Create(a));
    RefCounted * converted;
    beUnicodeObj_AllocateBuffer((beUnicodeObj *)nameText.p, 8);
    unsigned short *dst = (unsigned short *)((beUnicodeObj *)nameText.p)->_buffer;
    unsigned short *q = record->playerName;
    if (q[0] != 0xffff) {
        beFont_ConvertToUnicode((void *)&converted, font, degi->_dmName);
        unsigned short *src = (unsigned short *)((beUnicodeObj *)converted)->_buffer;
        int i = 0;
        for (; i < 8; i++) {
            dst[i] = src[i];
            if (src[i] == 0)
                break;
        }
        for (; i < 8; i++)
            dst[i] = 0;
        { RefCounted *r = converted; RefCountedOps::Release(r); }
    } else {
        int i = 0;
        for (; i < 8; i++) {
            dst[i] = (q + 1)[i];
            if (dst[i] == 0)
                break;
        }
        for (; i < 8; i++)
            dst[i] = 0;
    }
    ObjectList_AppendRetained(playerNameList, nameText.p);
    }
    igProperty_GetRecord(props, XDATA_2)->value = record->xdata;
    igProperty_GetRecord(props, BIT_4)->value = record->bit;
    igObjectList *deviceFolderList = igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value;
    ObjectListOps::Clear(deviceFolderList);
    for (int i = 0; i < 36; i++) {
        int id = record->deviceFolder[i];
        if (id == -1)
            break;
        ItemRef item = beNDMWDegiData__CreateItem(degi, id);
        ObjectList_AppendRetained(deviceFolderList, item.p);
    }
    igObjectList *diskFolderList = igProperty_GetRecordFolder(props, DISKFOLDER_2)->value;
    ObjectListOps::Clear(diskFolderList);
    for (int i = 0; i < 12; i++) {
        int id = record->diskFolder[i];
        if (id == -1)
            break;
        ItemRef item = beNDMWDegiData__CreateItem(degi, id);
        ObjectList_AppendRetained(diskFolderList, item.p);
    }
    igUnsignedCharList *cardList = (igUnsignedCharList *)igProperty_GetRecordArray(props, CARDLIST)->value;
    for (int i = 0; i < 50; i++) {
        unsigned char v = record->cardList[i];
        if (cardList->_count != 0 && i >= 0 && i < cardList->_count)
            ((unsigned char *)cardList->_data)[i] = v;
    }
    igObjectList *bankDeviceList = igProperty_GetRecordFolder(props, BANKDEVICE)->value;
    ObjectListOps::Clear(bankDeviceList);
    for (int i = 0; i < 96; i++) {
        int id = record->bankDevice[i];
        if (id == -1)
            break;
        ItemRef item = beNDMWDegiData__CreateItem(degi, id);
        ObjectList_AppendRetained(bankDeviceList, item.p);
    }
    igProperty_GetRecord(props, BANKBIT)->value = record->bankBit;
    igObjectList *powerSocketList = igProperty_GetRecordFolder(props, POWERSOCKET_2)->value;
    ObjectListOps::Clear(powerSocketList);
    for (int i = 0; i < 3; i++) {
        int id = record->powerSocket[i];
        if (id != -1) {
            ItemRef item(((RefCounted **)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ObjectList_AppendRetained(powerSocketList, item.p);
        } else {
            ObjectList_AppendRetained(powerSocketList, 0);
        }
    }
    igObjectList *powerPocketList = igProperty_GetRecordFolder(props, POWERPOCKET_2)->value;
    ObjectListOps::Clear(powerPocketList);
    for (int i = 0; i < 5; i++) {
        int id = record->powerPocket[i];
        if (id != -1) {
            ItemRef item(((RefCounted **)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ObjectList_AppendRetained(powerPocketList, item.p);
        } else {
            ObjectList_AppendRetained(powerPocketList, 0);
        }
    }
    igObjectList *mainSlotList = igProperty_GetRecordFolder(props, MAINSLOT_2)->value;
    ObjectListOps::Clear(mainSlotList);
    {
        int id = record->mainSlot;
        if (id != -1) {
            ItemRef item(((RefCounted **)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ObjectList_AppendRetained(mainSlotList, item.p);
        } else {
            ObjectList_AppendRetained(mainSlotList, 0);
        }
    }
    igObjectList *mainPocketList = igProperty_GetRecordFolder(props, MAINPOCKET_2)->value;
    ObjectListOps::Clear(mainPocketList);
    for (int i = 0; i < 5; i++) {
        int id = record->mainPocket[i];
        if (id != -1) {
            ItemRef item(((RefCounted **)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ObjectList_AppendRetained(mainPocketList, item.p);
        } else {
            ObjectList_AppendRetained(mainPocketList, 0);
        }
    }
    igObjectList *subSlotList = igProperty_GetRecordFolder(props, SUBSLOT_2)->value;
    int subSlotId = record->subSlot;
    ObjectListOps::Clear(subSlotList);
    if (subSlotId != -1) {
        ItemRef item(((RefCounted **)igProperty_GetRecordFolder(props, DEVICEFOLDER_2)->value->_data)[subSlotId]);
        if (item.p)
            item.p->refCount++;
        ObjectList_AppendRetained(subSlotList, item.p);
    } else {
        ObjectList_AppendRetained(subSlotList, 0);
    }
    igUnsignedCharList *baseFlagList = (igUnsignedCharList *)igProperty_GetRecordArray(props, BASE_FLAG_2)->value;
    for (int i = 0; i < 1024; i++) {
        unsigned char v = record->baseFlag[i];
        if (baseFlagList->_count != 0 && i >= 0 && i < baseFlagList->_count)
            ((unsigned char *)baseFlagList->_data)[i] = v;
    }
    igUnsignedCharList *baseFlagFolderList = (igUnsignedCharList *)igProperty_GetRecordArray(props, BASE_FLAGFOLDER_2)->value;
    for (int i = 0; i < 12; i++) {
        unsigned char v = record->baseFlagFolder[i];
        if (baseFlagFolderList->_count != 0 && i >= 0 && i < baseFlagFolderList->_count)
            ((unsigned char *)baseFlagFolderList->_data)[i] = v;
    }
    igIntList *baseCounterList = igProperty_GetRecordIntList(props, BASE_COUNTER_2)->value;
    for (int i = 0; i < 16; i++) {
        int v = record->baseCounter[i];
        if (baseCounterList->_count != 0 && i >= 0 && i < baseCounterList->_count)
            ((int *)baseCounterList->_data)[i] = v;
    }
    igUnsignedCharList *baseIsUseList = (igUnsignedCharList *)igProperty_GetRecordArray(props, BASE_ISUSE_2)->value;
    for (int i = 0; i < 16; i++) {
        unsigned char v = record->baseIsUse[i];
        if (baseIsUseList->_count != 0 && i >= 0 && i < baseIsUseList->_count)
            ((unsigned char *)baseIsUseList->_data)[i] = v;
    }
    igIntList *baseLevelList = igProperty_GetRecordIntList(props, BASE_LEVEL_2)->value;
    for (int i = 0; i < 16; i++) {
        int v = record->baseLevel[i];
        if (baseLevelList->_count != 0 && i >= 0 && i < baseLevelList->_count)
            ((int *)baseLevelList->_data)[i] = v;
    }
    igIntList *baseExpList = igProperty_GetRecordIntList(props, BASE_EXP_2)->value;
    for (int i = 0; i < 16; i++) {
        int v = record->baseExp[i];
        if (baseExpList->_count != 0 && i >= 0 && i < baseExpList->_count)
            ((int *)baseExpList->_data)[i] = v;
    }
    igIntList *baseSkillList = igProperty_GetRecordIntList(props, BASE_SKILL_2)->value;
    for (int i = 0; i < 144; i++) {
        int v = record->baseSkill[i];
        if (baseSkillList->_count != 0 && i >= 0 && i < baseSkillList->_count)
            ((int *)baseSkillList->_data)[i] = v;
    }
    igIntList *baseUpcntList = igProperty_GetRecordIntList(props, BASE_UPCNT_2)->value;
    for (int i = 0; i < 176; i++) {
        if (baseUpcntList->_count != 0 && i >= 0 && i < baseUpcntList->_count)
            ((int *)baseUpcntList->_data)[i] = record->baseUpcnt[i];
    }
}

void beNDMWLoadSlotPlayer__WriteToBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer, int replaceIndex, beNDMWDegiData *replacement) {
    int index = replaceIndex;
    beNDMWDegiData *record = replacement;
    int pos = buffer;
    beNDMWDegiDataList *list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
    int i = 0;
    int data, size;
    beNDMWDegiData *degi;
    while (i < list->_count) {
        if (i == index) {
            data = record->_data;
            size = record->_dataSize;
        } else {
            degi = ((beNDMWDegiData **)list->_data)[i];
            data = degi->_data;
            size = degi->_dataSize;
        }
        memcpy(pos, data, size);
        list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
        i++;
        pos += size;
    }
}

void beNDMWLoadSlotPlayer__ReadFromBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer) {
    int i;
    int offset;
    beNDMWDegiDataList *list;

    list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
    i = 0;
    if (0 < list->_count) {
        offset = 0;
        do {
            beNDMWDegiData__LoadFromBuffer((beNDMWDegiData *)(*(int *)(list->_data + offset)), buffer);
            list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
            i += 1;
            buffer += ((beNDMWDegiData *)*(int *)(list->_data + offset))->_dataSize;
            offset += 4;
        } while (i < list->_count);
    }
}

void beNDMWMcUtilCtrl__Init(beNDMWMcUtilCtrl *util, int messenger, int kindHard) {
    int i;

    util->_messenger = messenger;
    util->_isRun = 0;
    util->_isResult = 0;
    util->_isRdy = 0;
    switch (kindHard) {
    case 0:
        for (i = 0; i < 5; i++) {
            int owner = igObject_GetAllocator(util);
            int alloc = g_useOwnerAllocator ? owner : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
            SlotRef<0> slot(beNDMWMcSlotPS2_Create(alloc));
            ObjectList_AppendRetained(util->_slot, slot.p);
        }
        return;
    case 1:
        for (i = 0; i < 2; i++) {
            int owner = igObject_GetAllocator(util);
            int alloc = g_useOwnerAllocator ? owner : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
            SlotRef<1> slot(beNDMWMcSlotGC_Create(alloc));
            ObjectList_AppendRetained(util->_slot, slot.p);
        }
        return;
    case 2:
        for (i = 0; i < 9; i++) {
            int owner = igObject_GetAllocator(util);
            int alloc = g_useOwnerAllocator ? owner : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
            SlotRef<2> slot(beNDMWMcSlotXbox_Create(alloc));
            ObjectList_AppendRetained(util->_slot, slot.p);
        }
        break;
    }
}

void beNDMWMcUtilCtrl__Generate(beNDMWMcUtilCtrl *util) {
    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
    beMessenger_AppendInt(util->_messenger, 4);
    beMessenger_DispatchSelected(util->_messenger, GENERATE_5);
    if (beMessenger_GetBoolCount(util->_messenger) > 0) {
        util->_isUseUtil = 1;
    } else {
        util->_isUseUtil = 0;
    }
}

unsigned char beNDMWMcUtilCtrl__CheckReady(beNDMWMcUtilCtrl *util) {
    unsigned char ready = 0;
    if (util->_isUseUtil == 1) {
        beMessenger_SendNamed(util->_messenger, SAVEUTILITY, 0, -1, ISRDY);
        if (beMessenger_GetBool(util->_messenger, 0) == 1) {
            util->_isRdy = 1;
            ready = 1;
        }
    } else {
        util->_isRdy = 1;
        ready = 1;
    }
    return ready;
}

void beNDMWMcUtilCtrl__Remove(beNDMWMcUtilCtrl *util) {
    if (util->_isUseUtil == 1) {
        beMessenger_SendNamed(util->_messenger, SAVEUTILITY, 0, -1, REMOVE);
    }
}

bool beNDMWMcUtilCtrl__IsRemoved(beNDMWMcUtilCtrl *util) {
    bool removed = false;
    if (util->_isUseUtil == 1) {
        beMessenger_SendNamed(util->_messenger, SAVEUTILITY, 0, -1, ISRDY);
        if (beMessenger_GetBool(util->_messenger, 0) == 0) {
            removed = true;
        }
    } else {
        removed = true;
    }
    return removed;
}

void beNDMWMcUtilCtrl__Request(beNDMWMcUtilCtrl *util, int kind, int slot) {
    util->_tgCon = slot;
    util->_kind = kind;
    util->_result = 0;
    util->_isResult = 0;
    util->_isRun = 1;
    util->_isFormatRun = 0;
    util->_st0 = 0;
    util->_st3 = 0;
    util->_st2 = 0;
    util->_st1 = 0;
}

static inline unsigned int sizeOf(const beSaveDataDeliver *d) { return d->_size; }

void beNDMWMcUtilCtrl__Update(beNDMWMcUtilCtrl *util) {
    if (util->_isRdy == 1) {
        if (util->_isUseUtil == 1) {
            beSvDeliver *deliver;
            beNDMWMcSlotList *slots;
            int i;
            int off;
            beMessenger_SendNamed(util->_messenger, SAVEUTILITY, 0, -1, GETDELIVER);
            deliver = beMessenger_GetObject(util->_messenger, 0);
            slots = (beNDMWMcSlotList *)util->_slot;
            i = 0;
            if (i < slots->_count) {
                off = 0;
                do {
                    if (*(int *)((char *)((igIntList *)deliver->_actConnect)->_data + off) == 1) {
                        (*(beNDMWMcSlot **)((char *)slots->_data + off))->_isConnect = 1;
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_totalSize = *(int *)((char *)((igIntList *)deliver->_totalSizeList)->_data + off);
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_freeSize = *(int *)((char *)((igIntList *)deliver->_freeSizeList)->_data + off);
                        if (*(int *)((char *)((igIntList *)deliver->_formatList)->_data + off) == 1) {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_isFormat = 1;
                        } else {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_isFormat = 0;
                        }
                    } else {
                        (*(beNDMWMcSlot **)((char *)slots->_data + off))->_isConnect = 0;
                    }
                    slots = (beNDMWMcSlotList *)util->_slot;
                    i++;
                    off += 4;
                } while (i < slots->_count);
            }
            if (deliver->_useMtap == 1) {
                util->_isMtap = 1;
            } else {
                util->_isMtap = 0;
            }
        } else {
            int i;
            int offset;
            beNDMWMcSlotList *slots;
            util->_isMtap = 1;
            slots = (beNDMWMcSlotList *)util->_slot;
            i = 0;
            if (i < slots->_count) {
                offset = 0;
                do {
                    i++;
                    (*(beNDMWMcSlot **)((char *)slots->_data + offset))->_isConnect = 1;
                    slots = (beNDMWMcSlotList *)util->_slot;
                    offset += 4;
                } while (i < slots->_count);
            }
        }
    }
    if (util->_isRun == 1) {
        if (util->_isUseUtil == 1) {
            switch (util->_st0) {
            default:
                break;
            case 0:
                switch (util->_kind) {
                case 0:
                    memset(((beSaveDataDeliver *)util->_svData)->_data, 0, sizeOf((beSaveDataDeliver *)util->_svData));
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_AppendObject(util->_messenger, util->_svData);
                    beMessenger_DispatchSelected(util->_messenger, REQUEST_FILEMAKE);
                    break;
                case 1:
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected(util->_messenger, REQUEST_FILEFIND);
                    break;
                case 2:
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected(util->_messenger, REQUEST_FORMAT);
                    break;
                case 3:
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected(util->_messenger, REQUEST_USE_CHECK);
                    break;
                case 4:
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_AppendObject(util->_messenger, util->_svData);
                    beMessenger_DispatchSelected(util->_messenger, REQUEST_READ_MEDIA);
                    break;
                case 5:
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_AppendObject(util->_messenger, util->_svData);
                    beMessenger_DispatchSelected(util->_messenger, REQUEST_WRITE_MEDIA);
                    break;
                case 6:
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected(util->_messenger, REQUEST_GETFREESIZE);
                    break;
                case 7:
                    beMessenger_SelectReceivers(util->_messenger, SAVEUTILITY, 0, -1);
                    beMessenger_AppendInt(util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected(util->_messenger, REPORT_GAMEDATA);
                    break;
                }
                util->_st0 = util->_st0 + 1;
                util->_st3 = 0;
                util->_st2 = 0;
                util->_st1 = 0;
                break;
            case 1:
                beMessenger_SendNamed(util->_messenger, SAVEUTILITY, 0, -1, ISBUSY);
                if (beMessenger_GetBool(util->_messenger, 0) == 0) {
                    util->_st0 = util->_st0 + 1;
                    util->_st3 = 0;
                    util->_st2 = 0;
                    util->_st1 = 0;
                }
                break;
            case 2:
                beMessenger_SendNamed(util->_messenger, SAVEUTILITY, 0, -1, GETRESULT);
                util->_result = beMessenger_GetInt(util->_messenger, 0);
                util->_isRun = 0;
                util->_isResult = 1;
                util->_st0 = util->_st0 + 1;
                util->_st3 = 0;
                util->_st2 = 0;
                util->_st1 = 0;
                break;
            case 3:
                break;
            }
        } else {
            util->_result = 2;
            util->_isRun = 0;
            util->_isResult = 1;
        }
    }
}

void beNDMWLoadCtrl2__ResolvePadManager(beNDMWLoadCtrl2 *self) {
    igObject *found;
    igObject *previous;
    if (self->_padManager == 0) {
        found = (igObject *)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
        if (found != 0) {
            found->_refCount = found->_refCount + 1;
        }
        previous = (igObject *)self->_padManager;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_padManager = (int)found;
    }
}

static inline int st1(const beNDMWLoadCtrl2CtrlData *data) { return data->_st1; }

void beNDMWLoadCtrl2__Update(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram) {
    beNDMWLoadCtrl2CtrlData *ctrl;
    beNDMWLoadCtrl2CommonIntf *intf;
    int i;
    int readyCount;
    unsigned char allClosed;
    int j;
    beNDMWLoadSavePlWorkList *flagWork;
    int k;
    beNDMWLoadSavePlWorkList *flagList;

    if (ram->_dataList == 0) return;
    {
        if (ram->_dataList == 0) {
            igObject *o;
            igObject *old;
            int base = igObject_GetAllocator(ram);
            int a;
            if (g_useOwnerAllocator != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); }
            igSmartPointer<igObject> list((igObject *)beBaseInfoDataList_Create(a));
            o = list.p;
            if (o != 0) o->_refCount = o->_refCount + 1;
            old = (igObject *)ram->_dataList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(old);
                }
            }
            ram->_dataList = (int)o;
        }
        ctrl = (beNDMWLoadCtrl2CtrlData *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], CTRL_4);
        if (ram->_dataList == 0) {
            igObject *o;
            igObject *old;
            int base = igObject_GetAllocator(ram);
            int a;
            if (g_useOwnerAllocator != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); }
            igSmartPointer<igObject> list((igObject *)beBaseInfoDataList_Create(a));
            o = list.p;
            if (o != 0) o->_refCount = o->_refCount + 1;
            old = (igObject *)ram->_dataList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(old);
                }
            }
            ram->_dataList = (int)o;
        }
        intf = (beNDMWLoadCtrl2CommonIntf *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMONINTF_3);
        switch (ctrl->_st0) {
        case 0:
            break;
        case 1:
            switch (ctrl->_st1) {
            case 0:
                beNDMWMcUtilCtrl__Generate((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl);
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 1:
                if (beNDMWMcUtilCtrl__CheckReady((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl) == 1) {
                    ctrl->_st0 = 2;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                }
                break;
            }
            break;
        case 2:
            switch (st1(ctrl)) {
            case 0:
                beMessenger_SendNamed(self->_messenger, MODELCTRL_6, j_chrselback, 0, GENERATE_5);
                beMessenger_SendNamed(self->_messenger, MODELCTRL_6, j_chrselback, 0, SQ_OPEN_4);
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 1:
                switch (ctrl->_st2) {
                case 0:
                    beMessenger_SelectReceivers(self->_messenger, MODELCTRL_6, j_chrselback, 0);
                    beMessenger_AppendString(self->_messenger, SQ_OPEN_4);
                    beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_3);
                    if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                        if (ctrl->_isTitle == 1) {
                            ctrl->_st2 = ctrl->_st2 + 1;
                            ctrl->_st3 = 0;
                        } else {
                            ctrl->_st1 = ctrl->_st1 + 1;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                        }
                    }
                    break;
                case 1:
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_6, i_fadewn01_2, 0, ISRUN_3);
                    if (beMessenger_GetBool(self->_messenger, 0) == 1) {
                        beMessenger_SendNamed(self->_messenger, MODELCTRL_6, i_fadewn01_2, 0, SQ_WTIN60);
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    break;
                case 2:
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_6, i_fadewn01_2, 0, ISRUN_3);
                    if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                        ctrl->_st1 = ctrl->_st1 + 1;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                    }
                    break;
                }
                break;
            case 2:
                beMessenger_SendNamed(self->_messenger, LOADINTF2_ALL, 0, -1, GENERATE_5);
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 3:
                switch (intf->_intfStat) {
                case 0:
                    beNDMWLoadCtrl2CommonIntf__UpdateCutConnect(intf);
                    break;
                case 2:
                    break;
                case 3:
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    break;
                }
                break;
            case 4:
                switch (ctrl->_st2) {
                case 0:
                    i = 0;
                    do {
                        beNDMWLoadSavePlWork *u;
                        PLW(intf, i)->_isClose = 0;
                        u = PLW(intf, i);
                        i++;
                        u->_sysStat0 = 2;
                        u->_sysStat3 = 0;
                        u->_sysStat2 = 0;
                        u->_sysStat1 = 0;
                    } while (i < 4);
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    break;
                case 1:
                    allClosed = 1;
                    j = 0;
                    flagWork = (beNDMWLoadSavePlWorkList *)intf->_flagWork;
                    do {
                        if (((beNDMWLoadSavePlWork **)flagWork->_data)[j]->_isClose != 1) { allClosed = 0; break; }
                        j++;
                        flagWork = (beNDMWLoadSavePlWorkList *)intf->_flagWork;
                    } while (j < 4);
                    if (allClosed == 1) {
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                    }
                    break;
                case 2:
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_6, i_fadewn01_2, 0, GENERATE_5);
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_6, i_fadewn01_2, 0, SQ_BLOUT30_2);
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_6, j_chrselback, 0, SQ_CLOSE_6);
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    break;
                case 3:
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_6, j_chrselback, 0, ISRUN_3);
                    if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                    }
                    break;
                case 4: {
                    int common;
                    int difficulty, cameraMode, lightMode;
                    beMessenger_SendNamed(self->_messenger, LOADINTF2_ALL, 0, -1, SETSELECT_DATA);
                    {
                    readyCount = 0;
                    k = 0;
                    goto cnt_pre;
                cnt_body:
                    if (((beNDMWLoadSavePlWork **)flagList->_data)[k]->_isRdy == 1) readyCount++;
                    k++;
                cnt_test:
                    if (k < 4) goto cnt_body;
                    }
                    beMessenger_SendGroup(self->_messenger, GAMERAM_7, GETCOMMON_5);
                    common = ((int)beMessenger_GetObject(self->_messenger, 0));
                    igProperty_GetRecord(common, NINZU_3)->value = readyCount;
                    if (ctrl->_isTitle == 1) {
                        difficulty = intf->_difficultMode;
                        igProperty_GetRecord(common, DIFFICULTY_3)->value = difficulty;
                        cameraMode = self->_cameraMode;
                        igProperty_GetRecord(common, CAMERAMODE_3)->value = cameraMode;
                        lightMode = self->_lightMode;
                        igProperty_GetRecord(common, LIGHTMODE_3)->value = lightMode;
                        beMessenger_SendGroup(self->_messenger, TITLE2_2, GAMESTART_3);
                    }
                    ctrl->_st0 = 3;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                    break;
                }
                }
                break;
            }
            break;
        case 3:
            switch (ctrl->_st1) {
            case 0:
                beNDMWMcUtilCtrl__Remove((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl);
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 1:
                if (beNDMWMcUtilCtrl__IsRemoved((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl) == 1) {
                    if (ctrl->_isTitle == 0) {
                        beMessenger_SelectReceivers(self->_messenger, PLAYERPOINT_2, 0, -1);
                        beMessenger_AppendInt(self->_messenger, 4);
                        beMessenger_DispatchSelected(self->_messenger, SETGENERATEPOS);
                    } else {
                        g_mdlEntity[0] = 0;
                        beLua__RunNamedChunk(igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]), gameStart_lua, 0);
                        beMessenger_SelectReceivers(self->_messenger, PLAYERPOINT_2, 0, -1);
                        beMessenger_AppendInt(self->_messenger, 0);
                        beMessenger_DispatchSelected(self->_messenger, SETGENERATEPOS);
                    }
                    beMessenger_SelectGroup(self->_messenger, STAGECTL_2);
                    beMessenger_AppendString(self->_messenger, stagML11);
                    beMessenger_DispatchSelected(self->_messenger, NEXTSTAGE_2);
                    ctrl->_st0 = ctrl->_st0 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                }
                break;
            }
            break;
        }
    }
    return;
cnt_pre:
    flagList = (beNDMWLoadSavePlWorkList *)intf->_flagWork;
    goto cnt_test;
}

int beNDMWLoadCtrl2__GetInfoMeta(void)
{
    return g_beNDMWLoadCtrl2Info_metaObject[0];
}

/* Registers the load controller with its messenger as the LOADCTRL2 receiver. */
void beNDMWLoadCtrl2__RegisterReceiver(beNDMWLoadCtrl2 *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, LOADCTRL2);
}

int beNDMWLoadCtrl2__OnMessage(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram, beBaseInfo *info) {
    int message;
    int j;
    int i;
    message = beMessenger_ResolveEnumValue(self->_messenger, LoadCtrl2Message_GetMetaEnum(), info->_dataList);
    if (message == 0 || message == 1) {
        if (message == 1) {
            if (beMessenger_GetIntCount(self->_messenger) > 0) {
                self->_cameraMode = beMessenger_GetInt(self->_messenger, 0);
                self->_lightMode = beMessenger_GetInt(self->_messenger, 1);
            } else {
                self->_cameraMode = 0;
                self->_lightMode = 0;
            }
        }
        if (ram->_dataList == 0) {
            int a;
            OWNER_ALLOCATOR(a, self);
            {
            igSmartPointer<igObject> list(((igObject *)beBaseInfoDataList_Create(a)));
            igObject *t = list.p;
            if (t != 0) t->_refCount++;
            ReleaseRef::Apply((igObject *)ram->_dataList);
            ram->_dataList = (int)t;
            OWNER_ALLOCATOR(a, self);
            {
            CtrlDataRef ctrl(beNDMWLoadCtrl2CtrlData_Create(a));
            ObjectList_AppendRetained((int)(igObject *)ram->_dataList, (int)ctrl.p);
            beNDMWLoadCtrl2CtrlData *o = (beNDMWLoadCtrl2CtrlData *)ctrl.p;
            i = 1;
            o->_st0 = i;
            o->_st3 = 0;
            o->_st2 = 0;
            o->_st1 = 0;
            if (message == 1) {
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = i;
                j = 0;
                do {
                    beMessenger_SelectGroup(self->_messenger, GAMERAM_7);
                    beMessenger_AppendInt(self->_messenger, j);
                    beMessenger_DispatchSelected(self->_messenger, GAMEDATAINIT_2);
                    j++;
                } while (j < 4);
            } else {
                do {
                    beMessenger_SelectGroup(self->_messenger, GAMERAM_7);
                    beMessenger_AppendInt(self->_messenger, i);
                    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_4);
                    if (igProperty_GetRecordByte((int)beMessenger_GetObject(self->_messenger, 0), ISUSE_5)->value != 1) {
                        beMessenger_SelectGroup(self->_messenger, GAMERAM_7);
                        beMessenger_AppendInt(self->_messenger, i);
                        beMessenger_DispatchSelected(self->_messenger, GAMEDATAINIT_2);
                    }
                    i++;
                } while (i < 4);
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = 0;
            }
            }
            OWNER_ALLOCATOR(a, self);
            {
            CommonIntfRef common(beNDMWLoadCtrl2CommonIntf_Create(a));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_system = igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_inforam = (int)ram;
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_insight = self->_insight;
            if (message == 1) {
                ((beNDMWLoadCtrl2CommonIntf *)common.p)->_isTitle = 1;
            }
            i = 0;
            do {
                OWNER_ALLOCATOR(a, self);
                {
                DegiDataRef degi(((igObject *)beNDMWDegiData_Create(a)));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_gameUseData, (int)degi.p);
                }
                OWNER_ALLOCATOR(a, self);
                {
                FlagWorkRef flag(beNDMWLoadSavePlWork_Create(a));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_flagWork, (int)flag.p);
                }
                i++;
            } while (i < 4);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_kindHard = 0;
            beNDMWMcUtilCtrl__Init((beNDMWMcUtilCtrl *)(((beNDMWLoadCtrl2CommonIntf *)common.p)->_mcUtilCtrl), (int)self->_messenger, 0);
            ObjectList_AppendRetained((int)(igObject *)ram->_dataList, (int)common.p);
            }
            }
        }
        return 1;
    }
    igObject *p = (igObject *)ram->_dataList;
    if (p == 0) return 1;
    if (p == 0) {
        int a;
        OWNER_ALLOCATOR(a, ram);
        {
        igSmartPointer<igObject> fresh(((igObject *)beBaseInfoDataList_Create(a)));
        igObject *t = fresh.p;
        if (t != 0) t->_refCount++;
        ReleaseRef::Apply((igObject *)ram->_dataList);
        ram->_dataList = (int)t;
        }
    }
    igProperty_FindByName(ram->_dataList, g_propertyNameField[0], CTRL_4);
    switch (message) {
    case 2:
        return 1;
    case 3:
        if (beMessenger_GetObjectCount(self->_messenger) == 0) {
            if (ram->_dataList == 0) {
                int a;
                OWNER_ALLOCATOR(a, ram);
                {
                igSmartPointer<igObject> fresh(((igObject *)beBaseInfoDataList_Create(a)));
                igObject *t = fresh.p;
                if (t != 0) t->_refCount++;
                ReleaseRef::Apply((igObject *)ram->_dataList);
                ram->_dataList = (int)t;
                }
            }
            beMessenger_AppendObject(self->_messenger, ((int)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], COMMONINTF_3)));
        }
        return 1;
    default:
        return 0;
    }
}

int beNDMWLoadCtrl2__GetMeta(void)
{
    return g_beNDMWLoadCtrl2_metaObject[0];
}

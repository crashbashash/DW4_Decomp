#include "dw4/reflected.h"
#define RELS(o) { char *rs = (o); if (rs != 0) { int *hd = (int *)rs - 2; int rc = hd[1] - 1; hd[1] = rc; if (rc == 0) { StringChunk_ReleaseHeader(hd[0], hd); } } }
#include "dw4/igSmartPointer.h"
#include "dw4/igVec3f.h"
#include "dw4/igobject_release.h"
#define RELEASE(p) IG_OBJECT_RELEASE((igObject *)(p));
#define CHIPS_PER_PAGE 12

extern "C" void *beNDMWShopTitle01_Create(void *allocator);
extern "C" void *beNDMWShopTitle00_Create(void *allocator);
extern "C" void *beNDMWStatusTitle03_Create(void *allocator);
extern "C" void *beNDMWStatusTitle02_Create(void *allocator);
extern "C" void *beNDMWStatusTitle01_Create(void *allocator);
extern "C" void *beNDMWShopJunk_Create(void *allocator);
extern "C" void *beNDMWShopDevice_Create(void *allocator);
extern "C" void *beNDMWShopCtrl50_Create(void *allocator);
extern "C" void *beNDMWShopCtrl40_Create(void *allocator);
extern "C" void *beNDMWShopCtrl30_Create(void *allocator);
extern "C" void *beNDMWShopCtrl10_Create(void *allocator);
extern "C" void *Memory_GetAllocatorBySelector(int selector);
extern "C" void ObjectList_AppendRetained(igObjectList *list, void *object);
extern "C" void beMessenger_AppendString(int messenger, const char *text);
extern "C" void beMessenger_DispatchSelected(int messenger, const char *selector);
extern "C" int beMessenger_GetBool(int messenger, int index);
extern "C" void beMessenger_SelectReceivers(int messenger, const char *category, const char *name, int id);
extern "C" void beMessenger_SendNamed(int messenger, const char *category, const char *name, int id, const char *selector);
extern "C" void beNDMWWindow_BindContext(void *window, void *mother, int insight, int playerNo, int entCode);
extern "C" void beNDMWWindow_ClearQueuedText(void *window);
extern "C" void beNDMWWindow_PlayQueuedModelClose(void *window);
extern "C" int beNDMWWindow_PollCloseComplete(void *window);
extern "C" void beNDMWWindow_RequestChildrenClose(void *window);
extern "C" void *igObject_GetAllocator(void *object);
extern "C" int StringPool_Allocate(int size);
extern "C" int StringPool_Construct(int pool);
extern "C" char *StringPool_Intern(int pool, const char *text);
extern "C" void StringChunk_ReleaseHeader(int owner, int *header);
extern "C" void beNDMWWindow_RunMessageScript(void *window, const char *chunk, int callNo);
extern "C" void beNDMWWindow_QueueText(void *window, const char *textType, const char *textName, const char *text, const char *align);
extern "C" void *beNDMWShopSelect01_Create(void *allocator);
extern "C" void *beNDMWShopSelect11_Create(void *allocator);
extern "C" void *beNDMWShopSelect00_Create(void *allocator);
extern "C" void *beNDMWShopCtrlXdataChip_Create(void *allocator);
extern "C" void beMessenger_SelectGroup(int messenger, const char *group);
extern "C" void beMessenger_AppendInt(int messenger, int value);
extern "C" void beMessenger_AppendBool(int, int);
extern "C" int beMessenger_GetObject(int messenger, int index);
extern "C" int sprintf(char *buffer, const char *format, ...);
extern "C" int igObject_IsKindOf(void *object, int metaObject);
extern "C" void *beNDMWStatusCtrlD0_Create(void *allocator);
extern "C" void *beNDMWShopCtrlEditBit_Create(void *allocator);
extern "C" int beNDMWStatusCtrlD0_RefreshText(void *, int, int);
struct igResult { int value; };
extern "C" igResult ObjectList_RemoveFirstRetained(void *, void *, int);
extern "C" int beDataBase_GetRecordInt(int database, int record, const char *key);
extern "C" void *igInsightCore_FindManager(int insight, int metaObject);
extern "C" void *beNDMWShopSelect52_Create(void *allocator);
extern "C" void *beNDMWShopSelect34_Create(void *allocator);
extern "C" void *beNDMWShopCtrlEvolve_Create(void *allocator);
extern "C" void *beNDMWStatusSelectE1_Create(void *allocator);
extern "C" void beNDMWWindow_QueueNumberText(void *window, const char *textType, const char *textName, int number, const char *align);
extern "C" char *beDataBase_GetRecordString(int database, int record, const char *key);
extern "C" void beNDMWWindow_PresentModel(void *window, const char *model, int id, const char *sequence, const char *close, float *position);
extern "C" void beNDMWWindow_PresentModelAtOrigin(void *window, const char *model, int id, const char *sequence, const char *close);
extern "C" void beMessenger_AppendVec3(int, float *);
extern "C" void beNDMWShopCtrl50_MoveRowCursor(beNDMWWindow *window, int row);
extern "C" void *beNDMWShopCtrlSales_Create(void *allocator);
extern "C" void *igBoolList_Create(void *allocator);
extern "C" int beLua__RunNamedChunk(void *lua, const char *name, const char *given);
extern "C" int List_Resize(void *list, int count, int elementSize);
extern "C" int beMessenger_GetObjectCount(int messenger);
extern "C" int beMessenger_GetInt(int, int);
extern "C" void beMessenger_SendGroup(int messenger, const char *group, const char *selector);
extern "C" void *beNDMWShopTitle03_Create(void *allocator);
extern "C" void *beNDMWShopSelect02_Create(void *allocator);
extern "C" void *beNDMWShopCtrlA1_Create(void *allocator);
extern "C" void beNDMWStatusTitle01_ShowShopLayout(beNDMWStatusTitle01 *self);
extern "C" void beNDMWStatusTitle03_SetCancelPromptEnabled(beNDMWStatusTitle03 *self, int enabled);
extern "C" void *beNDMWShopSelect03_Create(void *allocator);
extern "C" beDataObjBoolList *igProperty_GetRecordArray(int object, const char *name);
extern "C" void beNDMWWindow_SendModelSequence(void *window, const char *model, int id, const char *sequence);
extern "C" int strcmp(const char *a, const char *b);
extern "C" int beDataBase_GetRecordCount(int);
extern "C" void beNDMWShinkaCtrl_Setup(beNDMWShinkaCtrl *self, int insight, int playerNo);
extern "C" int beNDMWWindowSelect_CanRequestFO2TOP(void *select);
extern "C" beDataObjStringList *igProperty_GetRecordStringList(int object, const char *name);
extern "C" void *beNDMWStatusCtrlEquip_Create(void *allocator);
extern "C" void beNDMWStatusTitle01_ShowStatusLayout(beNDMWStatusTitle01 *self);
extern "C" void *igIntList_Create(void *allocator);
extern "C" void beNDMWShopCtrlDigilabo_PresentMessageWindow(void *window);
extern "C" void beNDMWShopCtrlEditBit_ShowValueDigits(void *editBit, int mode, int value);
extern "C" void beNDMWWindow_ShowPaddedDigits(void *window, int value, unsigned int digits, const char *slotFormat);
extern "C" void *beNDMWShopSelectB0_Create(void *allocator);
extern "C" void *beNDMWShopCtrlDiskSell_Create(void *allocator);
extern "C" void *beNDMWShopCtrlDeviceSell_Create(void *allocator);
extern "C" void beNDMWShopCtrlSell_MoveRowCursor(beNDMWWindow *window, int row);
extern "C" unsigned int strlen(const char *text);
extern "C" void igStringObj_Set(igStringObj *self, const char *text);
extern "C" void igStringObj_Insert(igStringObj *self, const char *text, unsigned int at, unsigned int count);
extern "C" igVec3f beNDMWItemBase_GetRevisionColor(beNDMWItemBase *item);
extern "C" int beNDMWItemRevisionPocketBase_GetPrice(void *item, void *status, const char *key);
extern "C" char *beNDMWItemBase_GetRecordString(void *item, void *status, const char *key);
extern "C" int beNDMWItemBase_GetRecordInt(void *item, void *status, const char *key);
extern "C" void *beNDMWItemBaseList_Create(void *allocator);
extern "C" void beNDMWShopCtrlSales_MoveRowCursor(beNDMWWindow *window, int row);
extern "C" void *igStringRefList_Create(void *allocator);
extern "C" void *beNDMWItemAbilityChip_Create(void *allocator);
extern "C" void beNDMWItemAbilityChip_Set(beNDMWItemAbilityChip *self, int recNo);
extern "C" int beNDMWShopDevice_GetMeta(void);
extern "C" int beNDMWShopCtrlXdataChip_GetMeta(void);
extern "C" int beNDMWShopCtrlSales_GetMeta(void);
extern "C" int beNDMWShopCtrlDiskSell_GetMeta(void);
extern "C" int beNDMWShopCtrlDeviceSell_GetMeta(void);
extern "C" int beNDMWShopCtrlSell_GetMeta(void);
extern "C" int beNDMWShopCtrlEditBit_GetMeta(void);
extern "C" int beNDMWShopCtrlDigilabo_GetMeta(void);
extern "C" int beNDMWShopCtrlEvolve_GetMeta(void);
extern "C" int beNDMWShopCtrlA2_GetMeta(void);
extern "C" int beNDMWShopCtrlA1_GetMeta(void);
extern "C" int beNDMWShopCtrlA0_GetMeta(void);
extern "C" int beNDMWShopJunk_GetMeta(void);
extern "C" int beNDMWShopCtrl50_GetMeta(void);
extern "C" int beNDMWShopCtrl40_GetMeta(void);
extern "C" int beNDMWShopCtrl30_GetMeta(void);
extern "C" int beNDMWShopCtrl10_GetMeta(void);
extern "C" int beNDMWShopCtrl00_GetMeta(void);
extern "C" char MODELCTRL_16[];
extern "C" char i_messwn_3[];
extern "C" char SQ_STOPEN_3[];
extern "C" char ISSEQNAME_6[];
extern "C" char i_bgclear_2[];
extern "C" char OFFREEZE_3[];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef() : p(0) {}
    StringRef(int s) : p((char *)s) {}
    StringRef(const char *s) : p((char *)s) {}
    StringRef(void *s) : p((char *)s) {}
    ~StringRef() { release(); }
    void release() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    void Set(const char *n) { release(); p = (char *)n; }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" StringRef StringList_CopyRetained(igStringRefList *list, int index);
extern "C" void beNDMWShopCtrl00_Update(beNDMWShopCtrl00 *);

extern "C" char font011_3[];
extern "C" char font012[];
extern "C" char GAMERAM_14[];
extern "C" char RECALCPLAYER_5[];
extern "C" char txt_shop_lua_2[];
extern "C" char TEXTCTL_3[];
extern "C" char STWINFONT14[];
extern "C" char DEFAULTCOLOR_5[];
extern "C" char GETPLAYER_10[];
extern "C" char TSUYOSA_4[];
extern "C" char MAMORI_3[];
extern "C" char KASHIKOSA_4[];
extern "C" char SEISHIN_4[];
extern "C" char SUBAYASA_4[];
extern "C" char MHP_5[];
extern "C" char MMP_6[];
extern "C" char XDATA_4[];
extern "C" char STWINFONT41[];
extern "C" char plus1[];
extern "C" char RIGHT_3[];
extern "C" char percent_d[];
extern "C" char STWINFONT29[];
extern "C" char UPCNT_3[];
extern "C" char HP_6[];
extern "C" char MP_6[];
extern "C" char SUBWND_8[];
extern "C" char UPDATE_3[];
extern "C" int g_stringPool[4];
/* The seven stat rows of the X-data quote: their text fonts and their message prompt numbers. */
struct XdataStatFonts { const char *font[7]; };
struct XdataStatPrompts { int prompt[7]; };
extern "C" XdataStatFonts g_xdataStatFontNames;
extern "C" XdataStatPrompts g_xdataStatPromptIds;
extern "C" void beNDMWShopCtrl10_Update(beNDMWShopCtrl10 *self);
extern "C" beDataObjInt *igProperty_GetRecord(int object, const char *name);
extern "C" char DEVICEFOLDER_4[];
extern "C" char BANKDEVICE_3[];
extern "C" char font100_3[];
extern "C" char DISPOFF[];
extern "C" char SWITCH_2[];
extern "C" char BIT_7[];
extern "C" char BANKBIT_2[];
extern "C" int g_beNDMWStatusCtrlD0_metaObject[4];
extern "C" void beNDMWShopCtrl30_Update(beNDMWShopCtrl30 *);
extern "C" char space_2[];
extern "C" char LEFT_4[];
extern "C" char LEVEL_8[];
extern "C" char coweapon[];
extern "C" char coarmor1[];
extern "C" char coarmor2[];
extern "C" char DATABASE_11[];
extern "C" char GETDATABASE_10[];
extern "C" char ID[];
extern "C" char RATE[];
extern "C" char RANK[];
extern "C" int g_beNDMWStatus_metaObject[4];
extern "C" void beNDMWShopCtrl40_Update(beNDMWShopCtrl40 *);
extern "C" beDataObjObjectList *igProperty_GetRecordFolder(int object, const char *name);
extern "C" const char *g_fontNames[];
extern "C" char j_shwin[];
extern "C" char SQ_WAIT_5[];
extern "C" char SQ_CLOSE_10[];
extern "C" char i_stcursorleft_2[];
extern "C" char SQ_HIDE_2[];
extern "C" char i_stcursorright_2[];
extern "C" char conItem_2[];
extern "C" char STWINFONT13_2[];
extern "C" char NAME_2[];
extern "C" char STWINFONT17[];
extern "C" char HANBAI_2[];
extern "C" char SQ_CWINOPEN[];
extern "C" char TXT[];
extern "C" char TEXTSET[];
extern "C" char DISPON[];
extern "C" char DISKFOLDER_5[];
extern "C" char SQ_DWINOPEN[];

extern "C" void beNDMWShopCtrl50_Update(beNDMWShopCtrl50 *self);
extern "C" char font010_3[];
extern "C" char font021[];
extern "C" char STWINFONT32[];
extern "C" void beNDMWShopCtrl50_ShowQuantity(beNDMWShopCtrl50 *owner);
extern "C" char font020[];
extern "C" void beNDMWShopCtrl50_HideQuantity(beNDMWShopCtrl50 *);
/* The model sequence that places a list's row cursor on each of its rows. */
struct RowCursorSequences { const char *row[12]; } __attribute__((aligned(16)));
extern "C" RowCursorSequences g_diskListCursorSequences;
extern "C" char i_stcursor04_2[];
extern "C" char ISRUN_10[];
extern "C" char GENERATE_13[];
extern "C" beDataObjIntList *igProperty_GetRecordIntList(int object, const char *name);
extern "C" char GETSHOPDATA[];
extern "C" char CANCELCOLOR_4[];
extern "C" char GETCOMMON_10[];
extern "C" char COUNTER_4[];
extern "C" char junkexit_lua[];
extern "C" char stagML13_lua[];
extern "C" int g_beLua_metaObject[4];
extern "C" void beNDMWShopJunk_Update(beNDMWShopJunk *);
extern "C" beDataObjBool *igProperty_GetRecordByte(int object, const char *name);
extern "C" char j_shback[];
extern "C" char SQ_OPENCARD[];
extern "C" char SQ_OPEN_8[];
extern "C" char ISUSE_9[];
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beNDMWStatusTitle01_metaObject[4];
extern "C" void beNDMWShopCtrlA0_Update(beNDMWShopCtrlA0 *);
extern "C" igObject *beNDMWShopSelectA0_Create(void *);
extern "C" igObject *beNDMWShopCtrlA2_Create(void *);
extern "C" float g_vec3Zero[4];
extern "C" char font000_5[];
extern "C" char font001_5[];
extern "C" char j_shbase_2[];
extern "C" char SOUND_8[];
extern "C" char CURSOR_NG_4[];
extern "C" char PLAY_6[];
extern "C" char i_staccount_2[];
extern "C" char STWINFONT34_2[];
extern "C" char j_shcardwin[];
extern "C" char STWINFONT33[];
extern "C" char text_1[];
extern "C" char text_9[];
extern "C" char txt_status_lua_4[];
extern "C" void beNDMWShopCtrlA1_Update(beNDMWShopCtrlA1 *);
extern "C" char CARDLIST_3[];
extern "C" char card[];
extern "C" char CARDINFO[];
extern "C" char SQALBUM[];
extern "C" char j_shcard00[];
extern "C" void beNDMWShopCtrlA1_ShowFirstAlbumPage(beNDMWShopCtrlA1 *);
extern "C" char blank[];
/* Stores a retained card name into slot `index` of the card-info list. */
static inline void StoreCardName(beNDMWShopCtrlA1 *self, int index, int token) {
    StringRef name(token);
    igDataList *list = (igDataList *)self->_cardInfoList;
    int count = list->_count;
    if (count != 0 && index >= 0 && index < count) {
        int *slot = &((int *)list->_data)[index];
        int text = (int)name.p;
        if (text) *(int *)(text - 4) = *(int *)(text - 4) + 1;
        RELS((char *)*slot);
        *slot = (int)name.p;
    }
}
extern "C" void beNDMWShopCtrlA1_ShowAlbumPage(beNDMWShopCtrlA1 *);
extern "C" void beNDMWShopCtrlA1_CloseAlbumPage(beNDMWShopCtrlA1 *);
/* One text (font or model sequence name) per card of a booster pack. */
struct BoosterCardTexts { const char *text[3]; };
extern "C" BoosterCardTexts g_boosterCardNameTexts;
extern "C" BoosterCardTexts g_boosterCardOpenSequences;
extern "C" BoosterCardTexts g_boosterCardNameTextsReset;
extern "C" char SQ_OPEN00_2[];
extern "C" char SQ_OPEN01_3[];
extern "C" char SQ_OPEN02_3[];
extern "C" char SQ_OPEN03_2[];
extern "C" char SQ_OPEN04_2[];
extern "C" char SQ_OPEN05_2[];
extern "C" char SQ_OPEN06_2[];
extern "C" char SQ_OPEN07_2[];
extern "C" char SQ_OPEN08_2[];
extern "C" char j_shbooster[];
extern "C" char KAKURITSU[];
extern "C" char RARE[];
extern "C" char TALKFONT01[];
extern "C" char COLOR_4[];

extern "C" void beNDMWShopCtrlA2_Update(beNDMWShopCtrlA2 *);
extern "C" char *g_fontName1[];
extern "C" char *g_evolveStatRowTexts[];
extern "C" char SQ_STCLOSE_2[];
extern "C" char SQ_SINKAONOPEN[];
extern "C" char STWINFONT31[];
extern "C" char SQ_SINKAOFFOPEN[];
extern "C" char STWINFONT37[];
extern "C" char STWINFONT20[];
extern "C" char STWINFONT43[];
extern "C" char STWINFONT21[];
extern "C" char STWINFONT22[];
extern "C" char DIGIMONNO_6[];
extern "C" char WEAPONEQUIPCHECK[];
extern "C" char shinka_5[];
extern "C" char EXPLANATION_2[];
extern "C" int g_beNDMWStatusSelectE1_metaObject[4];
extern "C" void beNDMWShopCtrlEvolve_Update(beNDMWShopCtrlEvolve *self);
extern "C" char Lv_2[];
extern "C" void beNDMWShopCtrlEvolve_RefreshText(beNDMWShopCtrlEvolve *ctl, int sendNames, int sendStats);
extern "C" char CURRENT2BASE_2[];
extern "C" char MODEL_NAME_2[];
extern "C" char BASE2CURRENT_2[];
extern "C" char WEAPONEQUIPSTRONG[];
extern "C" char MAINSLOT_4[];
extern "C" char SUBSLOT_4[];
extern "C" char POWERPOCKET_4[];
extern "C" char MAINPOCKET_4[];
extern "C" void beNDMWShopCtrlEvolve_ApplyEvolution(beNDMWShopCtrlEvolve *);
extern "C" void beNDMWShopCtrlEvolve_ClearItemSlots(beNDMWShopCtrlEvolve *, igObjectList *);
extern "C" char POWERSOCKETNAME_5[];
extern "C" char PLAYERARMS_4[];
extern "C" char demo_digilab_lua[];
extern "C" char stagML12_lua[];
extern "C" void beNDMWShopCtrlDigilabo_Update(beNDMWShopCtrlDigilabo *self);
extern "C" char NINZU_5[];
extern "C" char POWERSOCKET_4[];
extern "C" void beNDMWShopCtrlDigilabo_SnapshotParty(beNDMWShopCtrlDigilabo *self);
extern "C" void beNDMWShopCtrlDigilabo_RecalcPlayers(beNDMWShopCtrlDigilabo *);
extern "C" int beNDMWShopCtrlDigilabo_HasPartyChanged(beNDMWShopCtrlDigilabo *);
extern "C" void beNDMWShopCtrlDigilabo_ShowPlayerTitle(beNDMWWindow *, int, int);
extern "C" bePadData *bePadManager_GetPadForPlayer(int padManager, int playerNo);
extern "C" char font002_4[];
extern "C" char SQ_BITPUTINOPEN[];
extern "C" char STWINFONT36[];
extern "C" char SQ_BITDRAWOUTOPEN[];
extern "C" char SQ_JUNKOPEN[];
extern "C" char font_03d_2[];
extern "C" char font01_d[];
extern "C" char font02_d[];
extern "C" char SELECTCTRL_4[];
extern "C" char i_stcursor03_2[];
extern "C" char ISSELECTNOW_2[];
extern "C" char CURSOR_MOVE_3[];
extern "C" char STWINFONT25[];
extern "C" void beNDMWShopCtrlEditBit_Update(beNDMWShopCtrlEditBit *self);
extern "C" void beNDMWShopCtrlSell_Update(beNDMWShopCtrlSell *self);
extern "C" RowCursorSequences g_sellCursorOpenSequences;
extern "C" char *g_stringObjEmptyText[4];
extern "C" char SQ_AWINOPEN[];
extern "C" char STWINFONT30[];
extern "C" char KAITORI_2[];
extern "C" char equippedMark_2[];
extern "C" char unequippedMark_2[];
extern "C" void beNDMWShopCtrlDeviceSell_Update(beNDMWShopCtrlDeviceSell *self);
extern "C" void beNDMWShopCtrlDeviceSell_RefreshText(beNDMWShopCtrlDeviceSell *self, int full, unsigned char sel);
extern "C" int beNDMWShopCtrlDeviceSell_UpdatePageCount(beNDMWShopCtrlDeviceSell *self);
extern "C" void beNDMWShopCtrlDeviceSell_ResetRowColors(beNDMWShopCtrlDeviceSell *self);
extern "C" char STWINFONT15_2[];
extern "C" char CENTER_4[];
extern "C" char SQ_EWINOPEN[];
extern "C" char SQ_BWINOPEN[];

extern "C" void beNDMWShopCtrlDiskSell_Update(beNDMWShopCtrlDiskSell *self);
extern "C" void beNDMWShopCtrlDiskSell_RefreshText(beNDMWShopCtrlDiskSell *, int, int);
extern "C" void beNDMWShopCtrlDiskSell_ShowQuantity(beNDMWShopCtrlDiskSell *);
extern "C" void beNDMWShopCtrlDiskSell_HideQuantity(beNDMWShopCtrlDiskSell *);
struct ChipPriceText { char text[5]; } __attribute__((aligned(16)));
extern "C" ChipPriceText dashdashdashdash_2;
extern "C" void beNDMWShopCtrlSales_RefreshText(beNDMWShopCtrlSales *, int, unsigned char);
extern "C" int beNDMWShopCtrlSales_UpdatePageCount(beNDMWShopCtrlSales *self);
extern "C" char SOUBI_3[];
extern "C" char SKILL_3[];
extern "C" char SKILLPOINT_3[];
extern "C" char LVPOINT_2[];
extern "C" bool beNDMWShopCtrlSales_CanPlayerUse(beNDMWShopCtrlSales *, beNDMWItemBase *);
extern "C" char ONPREVIEW_2[];
extern "C" char OFPREVIEW_2[];
/* The window's own allocator, or the default selector's when owner allocation is off. */
static inline void *OwnerAllocator(void *owner)
{
    void *allocator = igObject_GetAllocator(owner);
    if (g_useOwnerAllocator != 0) return allocator;
    return Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
}
extern "C" void beNDMWShopCtrlSales_PreviewSelected(beNDMWShopCtrlSales *, int);
extern "C" void beNDMWShopCtrlSales_StashEquipment(void *, igObjectList *, igObjectList *, igObjectList *, igObjectList *);
extern "C" void beNDMWShopCtrlSales_RestoreEquipment(void *, igDataList *, igDataList *, igDataList *, igDataList *);
extern "C" RowCursorSequences g_salesRowCursorSequences;
extern "C" int g_xdataChipStatPromptCodes[8];
extern "C" char STWINFONT35[];
extern "C" char SQ_XDATAITEMOPEN[];
extern "C" char NEXTX[];
extern "C" char RES_FIRE_3[];
extern "C" char RES_ICE_3[];
extern "C" char RES_THUNDER_3[];
extern "C" char RES_DARK_3[];
extern "C" char CHIMEIRITSU_3[];
extern "C" char HPDRAIN_3[];
extern "C" char MPDRAIN_3[];
extern "C" char CHOHATURITSU_3[];
extern "C" void beNDMWShopCtrlXdataChip_Update(beNDMWShopCtrlXdataChip *);
extern "C" int beNDMWShopCtrlXdataChip_UpdatePageCount(beNDMWShopCtrlXdataChip *self);
extern "C" void beNDMWShopCtrlXdataChip_RefreshText(beNDMWShopCtrlXdataChip *self, long long refreshRows, long long refreshDescription);
extern "C" void *beNDMWShopCtrlSell_Create(void *allocator);
extern "C" void beNDMWShopDevice_Update(beNDMWShopDevice *self);
extern "C" int g_beNDMWShopDevice_metaObject[4];
extern "C" int g_beNDMWShopCtrlXdataChip_metaObject[4];
extern "C" int g_beNDMWShopCtrlSales_metaObject[4];
extern "C" int g_beNDMWShopCtrlDiskSell_metaObject[4];
extern "C" int g_beNDMWShopCtrlDeviceSell_metaObject[4];
extern "C" int g_beNDMWShopCtrlSell_metaObject[4];
extern "C" int g_beNDMWShopCtrlEditBit_metaObject[4];
extern "C" int g_beNDMWShopCtrlDigilabo_metaObject[4];
extern "C" int g_beNDMWShopCtrlEvolve_metaObject[4];
extern "C" int g_beNDMWShopCtrlA2_metaObject[4];
extern "C" int g_beNDMWShopCtrlA1_metaObject[4];
extern "C" int g_beNDMWShopCtrlA0_metaObject[4];
extern "C" int g_beNDMWShopJunk_metaObject[4];
extern "C" int g_beNDMWShopCtrl50_metaObject[4];
extern "C" int g_beNDMWShopCtrl40_metaObject[4];
extern "C" int g_beNDMWShopCtrl30_metaObject[4];
extern "C" int g_beNDMWShopCtrl10_metaObject[4];
extern "C" int g_beNDMWShopCtrl00_metaObject[4];

/* `count` is declared ahead of the list it counts: MWCC numbers the locals in that order, which is
 * what gives the list the lower saved register where a caller keeps both across List_Resize. */
static inline void BoolList_Append(igObject *target, const bool &value)
{
    int count;
    igBoolList *list = (igBoolList *)target;
    count = list->_count;
    if (count < list->_capacity) {
        list->_count = count + 1;
    } else {
        List_Resize(list, count + 1, 1);
    }
    ((bool *)list->_data)[count] = value;
}

static inline void BoolList_Set(igBoolList *list, int index, const bool &value)
{
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((bool *)list->_data)[index] = value;
    }
}

/* _st0 of every shop window: build the window, run it, close it, wait for the close to finish.
 * _st1 is the step inside SHOP_STATE_RUN, _st2 the step's phase and _st3 a step-local word. */
enum ShopWindowState { SHOP_STATE_OPEN, SHOP_STATE_RUN, SHOP_STATE_CLOSE, SHOP_STATE_WAIT_CLOSED };
/* The phases (_st2) of a step that opens one child window and waits for it to close. */
enum ChildWindowPhase { CHILD_OPEN, CHILD_WAIT };
/* Answers of a yes/no window. */
enum ShopAnswer { ANSWER_YES, ANSWER_NO };
enum { MAX_PLAYERS = 4 };
/* beNDMWWindowSelect state that resends the selection size and moves the cursor to the top. */
enum { SELECT_STATE_RELOAD_TO_TOP = 4 };

#define NEXT_STATE(window) { (window)->_st0 = (window)->_st0 + 1; (window)->_st3 = 0; (window)->_st2 = 0; (window)->_st1 = 0; }
#define ENTER_STATE(window, state) { (window)->_st0 = (state); (window)->_st3 = 0; (window)->_st2 = 0; (window)->_st1 = 0; }
#define NEXT_STEP(window) { (window)->_st1 = (window)->_st1 + 1; (window)->_st3 = 0; (window)->_st2 = 0; }
#define ENTER_STEP(window, step) { (window)->_st1 = (step); (window)->_st3 = 0; (window)->_st2 = 0; }
#define NEXT_PHASE(window) { (window)->_st2 = (window)->_st2 + 1; (window)->_st3 = 0; }
#define ENTER_PHASE(window, phase) { (window)->_st2 = (phase); (window)->_st3 = 0; }

/* The window's state read afresh: `_st0 = CurrentState(self) + 1` reloads the value the switch tested. */
template <class Window> static inline int CurrentState(const Window *window)
{
    return window->_st0;
}

/* The owner's allocator, or the default selector's when owner allocation is off. */
#define PICK_ALLOCATOR(allocator, owner) { \
    allocator = igObject_GetAllocator(owner); \
    allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define CHILD_COUNT(window) (((igObjectList *)(window)->_subWindow)->_count)
#define ObjectList_Count(list) (((igObjectList *)(list))->_count)
/* Child `index` of the window's sub-window list, the list pointer re-read through its field. */
#define SUBWINDOW_AT(window, index) (((igObject **)((igObjectList *)*(int *)&(window)->_subWindow)->_data)[index])
/* Sets `found` to the first child window that the `AsKind` cast accepts, or null. */
#define FIND_CHILD(found, window, AsKind) { \
    int childIndex; \
    (found) = 0; \
    for (childIndex = 0; childIndex < CHILD_COUNT(window); childIndex++) { \
        (found) = AsKind(SUBWINDOW_AT(window, childIndex)); \
        if ((found) != 0) break; \
    } }

/* Sends `selector` to the `group` receivers with the window's player number. */
#define SEND_PLAYER_MESSAGE(window, group, selector) { \
    beMessenger_SelectGroup((window)->_messenger, group); \
    beMessenger_AppendInt((window)->_messenger, (window)->_playerNo); \
    beMessenger_DispatchSelected((window)->_messenger, selector); }
/* GAMERAM: select the player's data object (the reply's first object). */
#define REQUEST_PLAYER(window) SEND_PLAYER_MESSAGE(window, GAMERAM_14, GETPLAYER_10)
/* GAMERAM: recompute the player's derived stats. */
#define RECALC_PLAYER(window) SEND_PLAYER_MESSAGE(window, GAMERAM_14, RECALCPLAYER_5)
/* SUBWND: redraw the player's status windows. */
#define UPDATE_SUBWINDOW(window) SEND_PLAYER_MESSAGE(window, SUBWND_8, UPDATE_3)

/* The window player's data object. */
template <class Window> static inline int GetPlayer(Window *window)
{
    beMessenger_SelectGroup(window->_messenger, GAMERAM_14);
    beMessenger_AppendInt(window->_messenger, window->_playerNo);
    beMessenger_DispatchSelected(window->_messenger, GETPLAYER_10);
    return beMessenger_GetObject(window->_messenger, 0);
}

/* A player's integer record (BIT, LEVEL, MHP...). */
static inline beDataObjInt *PlayerInt(int player, const char *record)
{
    return igProperty_GetRecord(player, record);
}

/* The item list of a player's folder record (DEVICEFOLDER, DISKFOLDER...). */
static inline igObjectList *PlayerFolder(int player, const char *record)
{
    return (igObjectList *)igProperty_GetRecordFolder(player, record)->_data;
}

/* The pooled copy of `text` (null for null), creating the string pool on first use. */
static inline const char *InternString(const char *text)
{
    if (text == 0) return 0;
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], text);
}

/* InternString for a text that is never null. */
static inline const char *InternLiteral(const char *text)
{
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], text);
}

/* Drops one reference to a pooled string (reference count at text[-4], chunk header at text[-8]). */
static inline void ReleaseString(const char *text)
{
    if (text != 0) {
        int *header = (int *)text - 2;
        int references = header[1] - 1;
        header[1] = references;
        if (references == 0) StringChunk_ReleaseHeader(header[0], header);
    }
}

/* Appends the pooled copy of `text` to a string list. */
#define APPEND_INTERNED(list, text) { StringList_AppendRetained((int)(list), StringRef(InternString((const char *)(text)))); }

/* The paging virtuals (slots 22..24) a list window shares with beNDMWListCtrl. */
struct PagedWindow {
    virtual void vfunc_0();
    virtual void vfunc_1();
    virtual void vfunc_2();
    virtual void vfunc_3();
    virtual void vfunc_4();
    virtual void vfunc_5();
    virtual void vfunc_6();
    virtual void vfunc_7();
    virtual void vfunc_8();
    virtual void vfunc_9();
    virtual void vfunc_10();
    virtual void vfunc_11();
    virtual void vfunc_12();
    virtual void vfunc_13();
    virtual void vfunc_14();
    virtual void vfunc_15();
    virtual void vfunc_16();
    virtual void vfunc_17();
    virtual void vfunc_18();
    virtual void vfunc_19();
    virtual void vfunc_20();
    virtual void vfunc_21();
    virtual void PresentPageArrows(float *leftArrowPos, float *rightArrowPos);
    virtual int TurnPagePrev();
    virtual int TurnPageNext();
};

/* The window as a device list, or null when it is another kind of window. */
static inline beNDMWStatusCtrlD0 *AsDeviceList(igObject *window)
{
    if (window != 0 && igObject_IsKindOf(window, g_beNDMWStatusCtrlD0_metaObject[0]) != 0) {
        return (beNDMWStatusCtrlD0 *)window;
    }
    return 0;
}

/* The window as a player title, or null when it is another kind of window. */
static inline beNDMWStatusTitle01 *AsPlayerTitle(igObject *window)
{
    if (window != 0 && igObject_IsKindOf(window, g_beNDMWStatusTitle01_metaObject[0]) != 0) {
        return (beNDMWStatusTitle01 *)window;
    }
    return 0;
}

/* The page selector, when the first child window is one. */
static inline beNDMWWindowSelect *AsPageSelector(igObject *window)
{
    if (window != 0 && igObject_IsKindOf(window, g_beNDMWStatusSelectE1_metaObject[0]) != 0) {
        return (beNDMWWindowSelect *)window;
    }
    return 0;
}

/* Dispatch-only view of the system's igMersenneTwisterRandomNumber: genrand is vtable slot 22. */
class RandomNumberDispatch {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void sgenrand(unsigned int seed);
    virtual unsigned int genrand();
};


static inline void FillHpMp(int player)
{
    int value = PlayerInt(player, MHP_5)->_data;
    PlayerInt(player, HP_6)->_data = value;
    value = PlayerInt(player, MMP_6)->_data;
    PlayerInt(player, MP_6)->_data = value;
}

/* The service a shop root opens, by its entry code. */
enum ShopService {
    SHOP_SERVICE_XDATA = 1,
    SHOP_SERVICE_BANK = 3,
    SHOP_SERVICE_CNOS = 4,
    SHOP_SERVICE_DISK = 5,
    SHOP_SERVICE_WPU = 6,
    SHOP_SERVICE_APU = 7,
    SHOP_SERVICE_CHIP = 8,
    SHOP_SERVICE_JUNK = 9
};

/* Steps (_st1) of the root's run state. */
enum ShopRootStep {
    SHOP_ROOT_OPEN_SERVICE,
    SHOP_ROOT_WAIT_SERVICE
};

void beNDMWShopCtrl00_Update(beNDMWShopCtrl00 *self)
{
    void *allocator;

    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        PICK_ALLOCATOR(allocator, self);
        {
            igSmartPointer<beNDMWShopTitle00> shopTitle((beNDMWShopTitle00 *)beNDMWShopTitle00_Create(allocator));
            beNDMWWindow_BindContext(shopTitle.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained((igObjectList *)self->_subWindow, shopTitle.p);
        }
        PICK_ALLOCATOR(allocator, self);
        {
            igSmartPointer<beNDMWStatusTitle01> statusTitle1((beNDMWStatusTitle01 *)beNDMWStatusTitle01_Create(allocator));
            beNDMWWindow_BindContext(statusTitle1.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained((igObjectList *)self->_subWindow, statusTitle1.p);
        }
        PICK_ALLOCATOR(allocator, self);
        {
            igSmartPointer<beNDMWStatusTitle02> statusTitle2((beNDMWStatusTitle02 *)beNDMWStatusTitle02_Create(allocator));
            beNDMWWindow_BindContext(statusTitle2.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained((igObjectList *)self->_subWindow, statusTitle2.p);
        }
        PICK_ALLOCATOR(allocator, self);
        {
            igSmartPointer<beNDMWStatusTitle03> statusTitle3((beNDMWStatusTitle03 *)beNDMWStatusTitle03_Create(allocator));
            beNDMWWindow_BindContext(statusTitle3.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained((igObjectList *)self->_subWindow, statusTitle3.p);
        }
        PICK_ALLOCATOR(allocator, self);
        {
            igSmartPointer<beNDMWShopTitle01> serviceTitle((beNDMWShopTitle01 *)beNDMWShopTitle01_Create(allocator));
            beNDMWWindow_BindContext(serviceTitle.p, self, self->_insight, self->_playerNo, self->_entCode);
            ObjectList_AppendRetained((igObjectList *)self->_subWindow, serviceTitle.p);
        }
        NEXT_STATE(self);
        return;
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case SHOP_ROOT_OPEN_SERVICE:
            beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, i_messwn_3, 0);
            beMessenger_AppendString(self->_messenger, SQ_STOPEN_3);
            beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
            if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) == 1) {
                /* the message window is still playing its open sequence */
                return;
            }
            {
                igSmartPointer<beNDMWWindow> service;
                switch (self->_entCode) {
                case SHOP_SERVICE_XDATA:
                    PICK_ALLOCATOR(allocator, self);
                    service.release();
                    service.p = (beNDMWWindow *)beNDMWShopCtrl10_Create(allocator);
                    break;
                case SHOP_SERVICE_BANK:
                    PICK_ALLOCATOR(allocator, self);
                    service.release();
                    service.p = (beNDMWWindow *)beNDMWShopCtrl30_Create(allocator);
                    break;
                case SHOP_SERVICE_CNOS:
                    PICK_ALLOCATOR(allocator, self);
                    service.release();
                    service.p = (beNDMWWindow *)beNDMWShopCtrl40_Create(allocator);
                    break;
                case SHOP_SERVICE_DISK:
                    PICK_ALLOCATOR(allocator, self);
                    service.release();
                    service.p = (beNDMWWindow *)beNDMWShopCtrl50_Create(allocator);
                    break;
                case SHOP_SERVICE_WPU:
                case SHOP_SERVICE_APU:
                case SHOP_SERVICE_CHIP:
                    PICK_ALLOCATOR(allocator, self);
                    service.release();
                    service.p = (beNDMWWindow *)beNDMWShopDevice_Create(allocator);
                    break;
                case SHOP_SERVICE_JUNK:
                    PICK_ALLOCATOR(allocator, self);
                    service.release();
                    service.p = (beNDMWWindow *)beNDMWShopJunk_Create(allocator);
                    break;
                default:
                    PICK_ALLOCATOR(allocator, self);
                    service.release();
                    service.p = (beNDMWWindow *)beNDMWShopCtrl10_Create(allocator);
                    break;
                }
                beNDMWWindow_BindContext(service.p, self, self->_insight, self->_playerNo, self->_entCode);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, service.p);
            }
            self->_nowProcKazu = CHILD_COUNT(self);
            NEXT_STEP(self);
        case SHOP_ROOT_WAIT_SERVICE:
            if (CHILD_COUNT(self) != self->_nowProcKazu) {
                NEXT_STATE(self);
                return;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beMessenger_SendNamed(self->_messenger, MODELCTRL_16, i_bgclear_2, 0, OFFREEZE_3);
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* A selection window's result when nothing is chosen (cancelled, or no row highlighted). */
enum { SELECT_NONE = -1 };

/* Steps (_st1) of the XDATA service. */
enum XdataStep {
    XDATA_STEP_MAIN_MENU,
    XDATA_STEP_STATS,
    XDATA_STEP_CHIPS
};

/* Results of the XDATA main menu. */
enum XdataMenu {
    XDATA_MENU_STATS,
    XDATA_MENU_CHIPS,
    XDATA_MENU_LEAVE
};

/* Substeps (_st2) of the stat upgrade step. */
enum XdataStatsSubstep {
    XDATA_STATS_OPEN_LIST,
    XDATA_STATS_CHOOSE,
    XDATA_STATS_QUOTE,
    XDATA_STATS_CONFIRM,
    XDATA_STATS_UPGRADED,
    XDATA_STATS_CONTINUE
};

/* Stats on the XDATA stat list, in list order. */
enum XdataStat {
    XDATA_STAT_STRENGTH,
    XDATA_STAT_DEFENSE,
    XDATA_STAT_WISDOM,
    XDATA_STAT_SPIRIT,
    XDATA_STAT_SPEED,
    XDATA_STAT_MAX_HP,
    XDATA_STAT_MAX_MP,
    XDATA_STAT_COUNT
};

/* Slots of the player's UPCNT list: upgrades bought per stat. */
enum UpgradeCountSlot {
    UPCNT_MAX_HP,
    UPCNT_MAX_MP,
    UPCNT_STRENGTH,
    UPCNT_DEFENSE,
    UPCNT_WISDOM,
    UPCNT_SPIRIT,
    UPCNT_SPEED
};

/* txt_shop.lua message numbers of the XDATA service. */
enum XdataMessage {
    XDATA_MSG_MAIN_MENU = 1150,
    XDATA_MSG_STAT_HELP = 1154,
    XDATA_MSG_NOT_ENOUGH_XDATA = 1161,
    XDATA_MSG_STAT_AT_LIMIT = 1162,
    XDATA_MSG_CONFIRM = 1163,
    XDATA_MSG_UPGRADED = 1165,
    XDATA_MSG_CONTINUE = 1166
};

enum {
    XDATA_STAT_CAP = 9999,
    XDATA_HP_MP_CAP = 99999,
    XDATA_COST_FREE_STAT = 45,
    XDATA_COST_STEP = 5,
    XDATA_COST_MAX = 400,
    QUOTE_PROMPT_ROWS = 4
};

/* XDATA price of one upgrade of a stat: one per started step of 5 above 45, at most 400 (a
 * negative price becomes 1). */
static inline void ComputeXdataCost(int &cost, int stat)
{
    int remainder = (stat - XDATA_COST_FREE_STAT) % XDATA_COST_STEP;
    int steps = (stat - XDATA_COST_FREE_STAT - remainder) / XDATA_COST_STEP;
    cost = steps + (remainder != 0);
    cost = cost > XDATA_COST_MAX ? XDATA_COST_MAX : (cost < 0 ? 1 : cost);
}

/* Adds one to a list entry; the entry is read before the bounds test. */
static inline void IntList_Increment(igIntList *list, int index)
{
    int count;
    int *entries;
    int *slot;
    int incremented;
    entries = (int *)list->_data;
    slot = &entries[index];
    count = list->_count;
    incremented = *slot + 1;
    if (count != 0 && index < count) *slot = incremented;
}

void beNDMWShopCtrl10_Update(beNDMWShopCtrl10 *self)
{
    XdataStatFonts statFonts;
    char remainingText[128];
    XdataStatPrompts quotePrompts;
    void *allocator;

    switch (self->_st0) {
    default:
        return;
    case SHOP_STATE_OPEN:
        self->_st0 = CurrentState(self) + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        ENTER_STEP(self, XDATA_STEP_MAIN_MENU);
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case XDATA_STEP_MAIN_MENU:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect01> menu((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, XDATA_MSG_MAIN_MENU);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menu.p);
                    menu.p->_startPoint = self->_xdataMenu;
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    self->_parameter = XDATA_STAT_STRENGTH;
                    switch (self->_retCode) {
                    case XDATA_MENU_STATS:
                        self->_xdataMenu = XDATA_MENU_STATS;
                        ENTER_STEP(self, XDATA_STEP_STATS);
                        return;
                    case XDATA_MENU_CHIPS:
                        self->_xdataMenu = XDATA_MENU_CHIPS;
                        ENTER_STEP(self, XDATA_STEP_CHIPS);
                        return;
                    case XDATA_MENU_LEAVE:
                    default:
                        NEXT_STATE(self);
                        return;
                    }
                }
                break;
            }
            break;
        case XDATA_STEP_STATS:
            switch (self->_st2) {
            case XDATA_STATS_OPEN_LIST:
                beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_AppendBool(self->_messenger, 0);
                beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_5);
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect11> statList((beNDMWShopSelect11 *)beNDMWShopSelect11_Create(allocator));
                    beNDMWWindow_BindContext(statList.p, self, self->_insight, self->_playerNo, self->_parameter);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, statList.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
                /* _st3: the stat whose help text is shown */
                self->_st3 = self->_parameter;
                return;
            case XDATA_STATS_CHOOSE:
                if (CHILD_COUNT(self) == self->_nowProcKazu) {
                    int highlighted = self->_retCode;
                    if (highlighted != SELECT_NONE && highlighted != self->_st3) {
                        beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, highlighted + XDATA_MSG_STAT_HELP);
                        self->_st3 = self->_retCode;
                    }
                    break;
                }
                {
                    int player;
                    int statCap;
                    int cost;
                    int xdata;
                    int statValue;
                    const char *statKey;
                    int i;
                    statFonts = g_xdataStatFontNames;
                    for (i = 0; i < XDATA_STAT_COUNT; i++) {
                        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(self->_messenger, STWINFONT14);
                        beMessenger_AppendString(self->_messenger, statFonts.font[i]);
                        beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
                    }
                    REQUEST_PLAYER(self);
                    player = beMessenger_GetObject(self->_messenger, 0);
                    statCap = XDATA_STAT_CAP;
                    switch (self->_retCode) {
                    default:
                        ENTER_STEP(self, XDATA_STEP_MAIN_MENU);
                        return;
                    case XDATA_STAT_STRENGTH: statKey = TSUYOSA_4; break;
                    case XDATA_STAT_DEFENSE: statKey = MAMORI_3; break;
                    case XDATA_STAT_WISDOM: statKey = KASHIKOSA_4; break;
                    case XDATA_STAT_SPIRIT: statKey = SEISHIN_4; break;
                    case XDATA_STAT_SPEED: statKey = SUBAYASA_4; break;
                    case XDATA_STAT_MAX_HP: statKey = MHP_5; statCap = XDATA_HP_MP_CAP; break;
                    case XDATA_STAT_MAX_MP: statKey = MMP_6; statCap = XDATA_HP_MP_CAP; break;
                    }
                    statValue = PlayerInt(player, statKey)->_data;
                    ComputeXdataCost(cost, statValue);
                    self->_parameter = self->_retCode;
                    PICK_ALLOCATOR(allocator, self);
                    {
                        igSmartPointer<beNDMWShopSelect00> quote((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                        beNDMWWindow_BindContext(quote.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained((igObjectList *)self->_subWindow, quote.p);
                        NEXT_PHASE(self);
                        xdata = PlayerInt(player, XDATA_4)->_data;
                        /* _st3: whether the quote offers the upgrade */
                        if (statValue >= statCap) {
                            quote.p->_entCode = XDATA_MSG_STAT_AT_LIMIT;
                            self->_st3 = 0;
                        } else if (xdata < cost) {
                            quote.p->_entCode = XDATA_MSG_NOT_ENOUGH_XDATA;
                            self->_st3 = 0;
                        } else {
                            int j;
                            beNDMWWindow_QueueText(quote.p, STWINFONT41, font011_3, plus1, RIGHT_3);
                            sprintf(remainingText, percent_d, xdata - cost);
                            beNDMWWindow_QueueText(quote.p, STWINFONT41, font012, remainingText, RIGHT_3);
                            for (j = 0; j < QUOTE_PROMPT_ROWS; j++) {
                                StringList_AppendRetained(quote.p->_textCloseTypeList, StringRef(InternString(STWINFONT41)));
                                StringList_AppendRetained(quote.p->_textCloseNameList, StringRef(InternString(statFonts.font[j])));
                            }
                            StringList_AppendRetained(quote.p->_textCloseTypeList, StringRef(InternString(STWINFONT41)));
                            StringList_AppendRetained(quote.p->_textCloseNameList, StringRef(InternString(font011_3)));
                            StringList_AppendRetained(quote.p->_textCloseTypeList, StringRef(InternString(STWINFONT41)));
                            StringList_AppendRetained(quote.p->_textCloseNameList, StringRef(InternString(font012)));
                            StringList_AppendRetained(quote.p->_textCloseTypeList, StringRef(InternString(STWINFONT29)));
                            StringList_AppendRetained(quote.p->_textCloseNameList, StringRef(InternString(statFonts.font[2])));
                            quotePrompts = g_xdataStatPromptIds;
                            quote.p->_entCode = quotePrompts.prompt[self->_retCode];
                            self->_st3 = 1;
                        }
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    return;
                }
                break;
            case XDATA_STATS_QUOTE:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_st3) {
                    case 0:
                    default:
                        ENTER_STEP(self, XDATA_STEP_STATS);
                        return;
                    case 1:
                        break;
                    }
                    PICK_ALLOCATOR(allocator, self);
                    {
                        igSmartPointer<beNDMWShopSelect01> confirm((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                        beNDMWWindow_BindContext(confirm.p, self, self->_insight, self->_playerNo, XDATA_MSG_CONFIRM);
                        ObjectList_AppendRetained((igObjectList *)self->_subWindow, confirm.p);
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    NEXT_PHASE(self);
                    return;
                }
                break;
            case XDATA_STATS_CONFIRM:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case ANSWER_YES: {
                        int player;
                        const char *statKey;
                        int cost;
                        int xdata;
                        igIntList *upgradeCounts;
                        REQUEST_PLAYER(self);
                        player = beMessenger_GetObject(self->_messenger, 0);
                        switch (self->_parameter) {
                        case XDATA_STAT_STRENGTH: statKey = TSUYOSA_4; break;
                        case XDATA_STAT_DEFENSE: statKey = MAMORI_3; break;
                        case XDATA_STAT_WISDOM: statKey = KASHIKOSA_4; break;
                        case XDATA_STAT_SPIRIT: statKey = SEISHIN_4; break;
                        case XDATA_STAT_SPEED: statKey = SUBAYASA_4; break;
                        case XDATA_STAT_MAX_HP: statKey = MHP_5; break;
                        case XDATA_STAT_MAX_MP: statKey = MMP_6; break;
                        }
                        ComputeXdataCost(cost, PlayerInt(player, statKey)->_data);
                        xdata = PlayerInt(player, XDATA_4)->_data;
                        PlayerInt(player, XDATA_4)->_data = xdata - cost;
                        upgradeCounts = (igIntList *)igProperty_GetRecordIntList(player, UPCNT_3)->_data;
                        switch (self->_parameter) {
                        case XDATA_STAT_STRENGTH: IntList_Increment(upgradeCounts, UPCNT_STRENGTH); break;
                        case XDATA_STAT_DEFENSE: IntList_Increment(upgradeCounts, UPCNT_DEFENSE); break;
                        case XDATA_STAT_WISDOM: IntList_Increment(upgradeCounts, UPCNT_WISDOM); break;
                        case XDATA_STAT_SPIRIT: IntList_Increment(upgradeCounts, UPCNT_SPIRIT); break;
                        case XDATA_STAT_SPEED: IntList_Increment(upgradeCounts, UPCNT_SPEED); break;
                        case XDATA_STAT_MAX_HP: IntList_Increment(upgradeCounts, UPCNT_MAX_HP); break;
                        case XDATA_STAT_MAX_MP: IntList_Increment(upgradeCounts, UPCNT_MAX_MP); break;
                        }
                        RECALC_PLAYER(self);
                        REQUEST_PLAYER(self);
                        player = beMessenger_GetObject(self->_messenger, 0);
                        FillHpMp(player);
                        UPDATE_SUBWINDOW(self);
                        PICK_ALLOCATOR(allocator, self);
                        {
                            igSmartPointer<beNDMWShopSelect00> notice((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                            beNDMWWindow_BindContext(notice.p, self, self->_insight, self->_playerNo, XDATA_MSG_UPGRADED);
                            ObjectList_AppendRetained((igObjectList *)self->_subWindow, notice.p);
                        }
                        self->_nowProcKazu = CHILD_COUNT(self);
                        NEXT_PHASE(self);
                        return;
                    }
                    case ANSWER_NO:
                    default:
                        ENTER_STEP(self, XDATA_STEP_STATS);
                        return;
                    }
                }
                break;
            case XDATA_STATS_UPGRADED:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    PICK_ALLOCATOR(allocator, self);
                    {
                        igSmartPointer<beNDMWShopSelect01> question((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                        beNDMWWindow_BindContext(question.p, self, self->_insight, self->_playerNo, XDATA_MSG_CONTINUE);
                        ObjectList_AppendRetained((igObjectList *)self->_subWindow, question.p);
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    NEXT_PHASE(self);
                    return;
                }
                break;
            case XDATA_STATS_CONTINUE:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case ANSWER_YES:
                        ENTER_STEP(self, XDATA_STEP_STATS);
                        return;
                    case ANSWER_NO:
                    default:
                        ENTER_STEP(self, XDATA_STEP_MAIN_MENU);
                        return;
                    }
                }
                break;
            }
            break;
        case XDATA_STEP_CHIPS:
            switch (self->_st2) {
            case CHILD_OPEN:
                RECALC_PLAYER(self);
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopCtrlXdataChip> chips((beNDMWShopCtrlXdataChip *)beNDMWShopCtrlXdataChip_Create(allocator));
                    beNDMWWindow_BindContext(chips.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, chips.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ENTER_STEP(self, XDATA_STEP_MAIN_MENU);
                    self->_st3 = 1;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE: {
        int player;
        RECALC_PLAYER(self);
        REQUEST_PLAYER(self);
        player = beMessenger_GetObject(self->_messenger, 0);
        FillHpMp(player);
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        return;
    }
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Steps (_st1) of the BANK service. */
enum BankStep {
    BANK_STEP_MAIN_MENU,
    BANK_STEP_KIND_MENU,
    BANK_STEP_DEPOSIT_DEVICES,
    BANK_STEP_WITHDRAW_DEVICES,
    BANK_STEP_DEPOSIT_BITS,
    BANK_STEP_WITHDRAW_BITS,
    BANK_STEP_NOTICE
};

/* Results of the BANK main menu (kept in _bankMenu). */
enum BankMenu {
    BANK_MENU_DEPOSIT,
    BANK_MENU_WITHDRAW,
    BANK_MENU_LEAVE
};

/* Results of the BANK "what to move" menu. */
enum BankKind {
    BANK_KIND_DEVICES,
    BANK_KIND_BITS
};

/* Substeps (_st2) of the device deposit/withdraw steps. */
enum BankDevicesSubstep {
    BANK_DEVICES_OPEN_LIST,
    BANK_DEVICES_CHOOSE,
    BANK_DEVICES_OPEN_NOTICE,
    BANK_DEVICES_WAIT_NOTICE,
    BANK_DEVICES_WAIT_LIST_CLOSED = 5
};

/* txt_shop.lua message numbers of the BANK service. */
enum BankMessage {
    BANK_MSG_MAIN_MENU = 1350,
    BANK_MSG_KIND_MENU = 1355,
    BANK_MSG_DEPOSIT_DEVICE = 1357,
    BANK_MSG_BANK_FULL = 1358,
    BANK_MSG_WITHDRAW_DEVICE = 1364,
    BANK_MSG_DEVICE_FOLDER_FULL = 1365,
    BANK_MSG_BANK_EMPTY = 1374
};

enum {
    BANK_DEVICE_CAPACITY = 96,
    DEVICE_FOLDER_CAPACITY = 36
};

/* The beNDMWStatusCtrlD0 run step in which a row has been picked, and the substep of it that
 * reopens the list. */
enum {
    DEVICE_LIST_STEP_PICKED = 2,
    DEVICE_LIST_REOPEN = 1
};

/* Hides the device step's prompt (the STWINFONT29 font100 text of messages 1357/1364). */
template <class Window> static inline void HideDevicePrompt(Window *window)
{
    beMessenger_SelectGroup(window->_messenger, TEXTCTL_3);
    beMessenger_AppendString(window->_messenger, STWINFONT29);
    beMessenger_AppendString(window->_messenger, font100_3);
    beMessenger_AppendString(window->_messenger, DISPOFF);
    beMessenger_DispatchSelected(window->_messenger, SWITCH_2);
}

void beNDMWShopCtrl30_Update(beNDMWShopCtrl30 *self)
{
    void *allocator;

    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        self->_st0 = CurrentState(self) + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case BANK_STEP_MAIN_MENU:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect01> menu((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, BANK_MSG_MAIN_MENU);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menu.p);
                    menu.p->_startPoint = self->_bankMenu;
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case BANK_MENU_DEPOSIT:
                    case BANK_MENU_WITHDRAW:
                        self->_bankMenu = self->_retCode;
                        ENTER_STEP(self, BANK_STEP_KIND_MENU);
                        return;
                    case BANK_MENU_LEAVE:
                    default:
                        NEXT_STATE(self);
                        return;
                    }
                }
                break;
            }
            break;
        case BANK_STEP_KIND_MENU:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect01> menu((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, BANK_MSG_KIND_MENU);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menu.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case BANK_KIND_DEVICES: {
                        int player;
                        igObjectList *bank;
                        REQUEST_PLAYER(self);
                        player = beMessenger_GetObject(self->_messenger, 0);
                        igProperty_GetRecordFolder(player, DEVICEFOLDER_4);
                        bank = (igObjectList *)igProperty_GetRecordFolder(player, BANKDEVICE_3)->_data;
                        if (self->_bankMenu == BANK_MENU_DEPOSIT) {
                            ENTER_STEP(self, BANK_STEP_DEPOSIT_DEVICES);
                            return;
                        }
                        if (bank->_count <= 0) {
                            ENTER_STEP(self, BANK_STEP_NOTICE);
                            /* _st3: the notice's message */
                            self->_st3 = BANK_MSG_BANK_EMPTY;
                            return;
                        }
                        ENTER_STEP(self, BANK_STEP_WITHDRAW_DEVICES);
                        return;
                    }
                    case BANK_KIND_BITS:
                        if (self->_bankMenu == BANK_MENU_DEPOSIT) {
                            ENTER_STEP(self, BANK_STEP_DEPOSIT_BITS);
                            return;
                        }
                        ENTER_STEP(self, BANK_STEP_WITHDRAW_BITS);
                        return;
                    default:
                        ENTER_STEP(self, BANK_STEP_MAIN_MENU);
                        return;
                    }
                }
                break;
            }
            break;
        case BANK_STEP_DEPOSIT_DEVICES:
        case BANK_STEP_WITHDRAW_DEVICES:
            switch (self->_st2) {
            case BANK_DEVICES_OPEN_LIST:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWStatusCtrlD0> list((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create(allocator));
                    beNDMWWindow_BindContext(list.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, list.p);
                    list.p->_isAutoClose = 0;
                    list.p->_isEquipDisable = 1;
                    if (self->_st1 == BANK_STEP_WITHDRAW_DEVICES) list.p->_isBankFolder = 1;
                }
                switch (self->_st1) {
                case BANK_STEP_DEPOSIT_DEVICES:
                    beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, BANK_MSG_DEPOSIT_DEVICE);
                    break;
                case BANK_STEP_WITHDRAW_DEVICES:
                    beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, BANK_MSG_WITHDRAW_DEVICE);
                    break;
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
                return;
            case BANK_DEVICES_CHOOSE: {
                beNDMWStatusCtrlD0 *list;
                FIND_CHILD(list, self, AsDeviceList)
                if (list != 0) {
                    if (self->_retCode == SELECT_NONE) {
                        NEXT_STATE(list);
                        ENTER_PHASE(self, BANK_DEVICES_WAIT_LIST_CLOSED);
                        HideDevicePrompt(self);
                        return;
                    }
                    if (list->_st0 == SHOP_STATE_RUN && list->_st1 == DEVICE_LIST_STEP_PICKED) {
                        int player;
                        igObjectList *folder;
                        igObjectList *bank;
                        beNDMWItemBase *device;
                        int picked;
                        REQUEST_PLAYER(self);
                        player = beMessenger_GetObject(self->_messenger, 0);
                        folder = (igObjectList *)igProperty_GetRecordFolder(player, DEVICEFOLDER_4)->_data;
                        bank = (igObjectList *)igProperty_GetRecordFolder(player, BANKDEVICE_3)->_data;
                        picked = self->_retCode;
                        switch (self->_st1) {
                        case BANK_STEP_DEPOSIT_DEVICES:
                            device = (beNDMWItemBase *)((int *)folder->_data)[picked];
                            if (bank->_count >= BANK_DEVICE_CAPACITY) {
                                ENTER_PHASE(self, BANK_DEVICES_OPEN_NOTICE);
                                self->_st3 = BANK_MSG_BANK_FULL;
                                return;
                            }
                            if (device->_isEquip == 0) {
                                ObjectList_AppendRetained(bank, device);
                                ObjectList_RemoveFirstRetained(folder, device, 0);
                            }
                            ENTER_PHASE(list, DEVICE_LIST_REOPEN);
                            return;
                        case BANK_STEP_WITHDRAW_DEVICES:
                            device = (beNDMWItemBase *)((int *)bank->_data)[picked];
                            if (folder->_count >= DEVICE_FOLDER_CAPACITY) {
                                ENTER_PHASE(self, BANK_DEVICES_OPEN_NOTICE);
                                self->_st3 = BANK_MSG_DEVICE_FOLDER_FULL;
                                return;
                            }
                            ObjectList_AppendRetained(folder, device);
                            ObjectList_RemoveFirstRetained(bank, device, 0);
                            if (bank->_count <= 0) {
                                ENTER_PHASE(self, BANK_DEVICES_OPEN_NOTICE);
                                self->_st3 = BANK_MSG_BANK_EMPTY;
                                beNDMWStatusCtrlD0_RefreshText(list, 1, 0);
                                return;
                            }
                            ENTER_PHASE(list, DEVICE_LIST_REOPEN);
                            return;
                        }
                    }
                }
                break;
            }
            case BANK_DEVICES_OPEN_NOTICE:
                HideDevicePrompt(self);
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect00> notice((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(notice.p, self, self->_insight, self->_playerNo, self->_st3);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, notice.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case BANK_DEVICES_WAIT_NOTICE:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    beNDMWStatusCtrlD0 *list;
                    FIND_CHILD(list, self, AsDeviceList)
                    if (list != 0) {
                        NEXT_STATE(list);
                        ENTER_PHASE(self, BANK_DEVICES_WAIT_LIST_CLOSED);
                        return;
                    }
                }
                break;
            case BANK_DEVICES_WAIT_LIST_CLOSED: {
                beNDMWStatusCtrlD0 *list;
                FIND_CHILD(list, self, AsDeviceList)
                if (list == 0) {
                    ENTER_STEP(self, BANK_STEP_MAIN_MENU);
                    return;
                }
                break;
            }
            }
            break;
        case BANK_STEP_DEPOSIT_BITS:
        case BANK_STEP_WITHDRAW_BITS:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopCtrlEditBit> editor((beNDMWShopCtrlEditBit *)beNDMWShopCtrlEditBit_Create(allocator));
                    beNDMWWindow_BindContext(editor.p, self, self->_insight, self->_playerNo, self->_bankMenu);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, editor.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    if (self->_retCode != SELECT_NONE) {
                        int amount;
                        int player;
                        int bits;
                        int bankBits;
                        REQUEST_PLAYER(self);
                        player = beMessenger_GetObject(self->_messenger, 0);
                        amount = self->_retCode;
                        if (self->_bankMenu == BANK_MENU_DEPOSIT) {
                            bits = PlayerInt(player, BIT_7)->_data;
                            bankBits = PlayerInt(player, BANKBIT_2)->_data;
                            bits = bits - amount;
                            bankBits = bankBits + amount;
                            PlayerInt(player, BIT_7)->_data = bits;
                            PlayerInt(player, BANKBIT_2)->_data = bankBits;
                        } else {
                            bits = PlayerInt(player, BIT_7)->_data;
                            bankBits = PlayerInt(player, BANKBIT_2)->_data;
                            bits = bits + amount;
                            bankBits = bankBits - amount;
                            PlayerInt(player, BIT_7)->_data = bits;
                            PlayerInt(player, BANKBIT_2)->_data = bankBits;
                        }
                        UPDATE_SUBWINDOW(self);
                    }
                    ENTER_STEP(self, BANK_STEP_MAIN_MENU);
                    return;
                }
                break;
            }
            break;
        case BANK_STEP_NOTICE:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect00> notice((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(notice.p, self, self->_insight, self->_playerNo, self->_st3);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, notice.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ENTER_STEP(self, BANK_STEP_MAIN_MENU);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Switches a text label of a font window off. */
#define HIDE_TEXT(window, font, label) { \
    beMessenger_SelectGroup((window)->_messenger, TEXTCTL_3); \
    beMessenger_AppendString((window)->_messenger, font); \
    beMessenger_AppendString((window)->_messenger, label); \
    beMessenger_AppendString((window)->_messenger, DISPOFF); \
    beMessenger_DispatchSelected((window)->_messenger, SWITCH_2); }

/* beNDMWStatusCtrlD0::_st1 while its selection is paused on a decided row, and the substep that
 * reopens the selection. */
enum { DEVICE_LIST_DECIDED = 2, DEVICE_LIST_RESELECT = 1 };

/* beNDMWShopCtrl40::_st1 */
enum CnosStep { CNOS_SELECT_DEVICE, CNOS_CONVERT, CNOS_SHORT_OF_BITS, CNOS_CLOSE_LIST };

/* beNDMWShopCtrl40::_st2 in CNOS_SELECT_DEVICE. */
enum CnosSelectSubstep { SELECT_OPEN_LIST, SELECT_WAIT_DECISION };

/* beNDMWItemBase::_kindNo of a device. */
enum DeviceKind { DEVICE_WEAPON, DEVICE_BLUE_ARMOR, DEVICE_YELLOW_ARMOR };

#define CNOS_PRICE 300
#define RATE_TOTAL 10000U

/* Makes `name` hold `token`, already retained by the caller. */
static inline void AssignString(StringRef &name, const char *token)
{
    ReleaseString(name.p);
    name.p = (char *)token;
}

void beNDMWShopCtrl40_Update(beNDMWShopCtrl40 *self) {
    void *allocator;
    beNDMWStatusCtrlD0 *decidedList;
    beNDMWStatusCtrlD0 *convertedList;
    beNDMWStatusCtrlD0 *closingList;
    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        beNDMWWindow_QueueText(self, STWINFONT29, font100_3, space_2, LEFT_4);
        NEXT_STATE(self)
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case CNOS_SELECT_DEVICE:
            switch (self->_st2) {
            case SELECT_OPEN_LIST:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWStatusCtrlD0> list((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create(allocator));
                    beNDMWWindow_BindContext(list.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, list.p);
                    list.p->_isAutoClose = 0;
                    list.p->_isUnknownEnable = 1;
                }
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x5AA);
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
                return;
            case SELECT_WAIT_DECISION:
                FIND_CHILD(decidedList, self, AsDeviceList)
                if (decidedList != 0) {
                    if (self->_retCode == -1) {
                        ENTER_STEP(self, CNOS_CLOSE_LIST)
                        return;
                    }
                    if (decidedList->_st0 == SHOP_STATE_RUN && decidedList->_st1 == DEVICE_LIST_DECIDED) {
                        self->_selectCursor = self->_retCode;
                        REQUEST_PLAYER(self)
                        if (PlayerInt(beMessenger_GetObject(self->_messenger, 0), BIT_7)->_data < CNOS_PRICE) {
                            ENTER_STEP(self, CNOS_SHORT_OF_BITS)
                        } else {
                            ENTER_STEP(self, CNOS_CONVERT)
                        }
                        HIDE_TEXT(self, STWINFONT29, font100_3)
                        return;
                    }
                }
                break;
            }
            break;
        case CNOS_CONVERT:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect00> message((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, 0x5AC);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) == self->_nowProcKazu) break;
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect01> yesNo((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(yesNo.p, self, self->_insight, self->_playerNo, 0x5AD);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, yesNo.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 2:
                if (ObjectList_Count(self->_subWindow) == self->_nowProcKazu) break;
                if (self->_retCode == ANSWER_YES) {
                    int bandRow;
                    int table;
                    int level;
                    unsigned int roll;
                    int band;
                    int rateSum;
                    int entryCount;
                    int entry;
                    int player;
                    beNDMWItemBase *device;
                    int row;
                    REQUEST_PLAYER(self)
                    player = beMessenger_GetObject(self->_messenger, 0);
                    {
                        int bits = PlayerInt(player, BIT_7)->_data;
                        beDataObjInt *money = PlayerInt(player, BIT_7);
                        money->_data = bits - CNOS_PRICE;
                    }
                    UPDATE_SUBWINDOW(self)
                    device = ((beNDMWItemBase **)PlayerFolder(player, DEVICEFOLDER_4)->_data)[self->_selectCursor];
                    level = PlayerInt(player, LEVEL_8)->_data;
                    if (level <= 40) band = 1;
                    else if (level <= 100) band = 2;
                    else if (level <= 200) band = 3;
                    else if (level <= 300) band = 4;
                    else if (level <= 400) band = 5;
                    else band = 6;
                    StringRef tableName(0);
                    if (device->_kindNo == DEVICE_WEAPON) {
                        AssignString(tableName, InternLiteral(coweapon));
                    } else if (device->_kindNo == DEVICE_BLUE_ARMOR) {
                        AssignString(tableName, InternLiteral(coarmor1));
                    } else if (device->_kindNo == DEVICE_YELLOW_ARMOR) {
                        AssignString(tableName, InternLiteral(coarmor2));
                    }
                    beMessenger_SendNamed(self->_messenger, DATABASE_11, tableName.p, 0, GETDATABASE_10);
                    table = beMessenger_GetObject(self->_messenger, 0);
                    /* Row band*100 holds the band's entry count; its entries follow it. */
                    bandRow = band * 100;
                    entryCount = beDataBase_GetRecordInt(table, bandRow, ID);
                    roll = ((RandomNumberDispatch *)((beSystem *)((beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]))->_system)->_random)->genrand() % RATE_TOTAL;
                    rateSum = 0;
                    entry = 1;
                    if (entryCount > 0) {
                        do {
                            row = bandRow + entry;
                            rateSum += beDataBase_GetRecordInt(table, row, RATE);
                            if (rateSum >= (int)roll) {
                                int id = beDataBase_GetRecordInt(table, row, ID);
                                beDataBase_GetRecordInt(table, row, RANK);
                                device->_recNo = id;
                                break;
                            }
                            entry++;
                        } while (entryCount >= entry);
                    }
                }
                self->_retCode = self->_selectCursor;
                FIND_CHILD(convertedList, self, AsDeviceList)
                if (convertedList != 0) {
                    ENTER_STEP(self, CNOS_SELECT_DEVICE)
                    ENTER_PHASE(self, SELECT_WAIT_DECISION)
                    ENTER_PHASE(convertedList, DEVICE_LIST_RESELECT)
                    HIDE_TEXT(self, STWINFONT29, font100_3)
                    return;
                }
                break;
            }
            break;
        case CNOS_SHORT_OF_BITS:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect00> message((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, 0x5AB);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    ENTER_STEP(self, CNOS_CLOSE_LIST)
                    return;
                }
                break;
            }
            break;
        case CNOS_CLOSE_LIST:
            FIND_CHILD(closingList, self, AsDeviceList)
            switch (self->_st2) {
            case 0:
                if (closingList != 0) {
                    ENTER_STATE(closingList, SHOP_STATE_CLOSE)
                }
                NEXT_PHASE(self)
                return;
            case 1:
                if (closingList == 0) {
                    NEXT_STATE(self)
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* beNDMWShopCtrl50::_st1 */
enum DiskShopStep { DISK_MENU, DISK_LIST, DISK_QUANTITY, DISK_PURCHASE, DISK_SELL, DISK_NOTICE };

/* beNDMWShopCtrl50 menu choices (the menu's _retCode). */
enum DiskMenuChoice { DISK_MENU_BUY, DISK_MENU_SELL, DISK_MENU_EXIT };

/* beNDMWShopCtrl50::_st2 in DISK_LIST. */
enum DiskListSubstep { LIST_PRESENT, LIST_SELECT, LIST_DESCRIBE, LIST_WAIT };

/* beNDMWShopCtrl50::_st2 in DISK_PURCHASE. */
enum DiskPurchaseSubstep { PURCHASE_CHECK_BITS, PURCHASE_ANNOUNCE, PURCHASE_CONFIRM, PURCHASE_APPLY };

#define DISK_ROWS 10
#define DISK_STACK_MAX 9

/* Points every slot of a string list at the pooled empty string, releasing what each held. */
#define EMPTY_STRING_SLOTS(list) { \
    int count; \
    int slotIndex; \
    char **slot; \
    char *empty; \
    int offset; \
    char *old; \
    count = (list)->_count; \
    slotIndex = 0; \
    if (0 < count) { \
        offset = 0; \
        do { \
            slot = (char **)((int)(list)->_data + offset); \
            if (g_stringPool[0] == 0) { \
                int pool = StringPool_Allocate(0x10); \
                if (pool != 0) pool = StringPool_Construct(pool); \
                g_stringPool[0] = pool; \
            } \
            empty = StringPool_Intern(g_stringPool[0], 0); \
            old = *slot; \
            ReleaseString(old); \
            slotIndex += 1; \
            *slot = empty; \
            offset += 4; \
        } while (slotIndex < count); \
    } }

/* Appends field `key` of `database` record `record` to the selected message. */
static inline void AppendRecordString(int messenger, int database, int record, const char *key)
{
    beMessenger_AppendString(messenger, beDataBase_GetRecordString(database, record, key));
}

/* How many of a disk item the player holds. */
static inline int DiskCount(const beNDMWItemDisk *disk) { return disk->_kazu; }

void beNDMWShopCtrl50_Update(beNDMWShopCtrl50 *self) {
    float leftArrowPos[3];
    float rightArrowPos[3];
    const igObjectList *heldDisks;
    void *allocator;
    int conItems;
    int row;
    int cost;
    int totalPrice;
    int player;
    int heldCount;
    int slot;
    int bits;
    beDataObjInt *money;
    const igObjectList *ownedDisks;
    int ownedSlot;
    beNDMWItemDisk *disk;
    beNDMWItemDisk *ownedDisk;
    const char **font;
    igStringRefList *closeInfoNames;
    igStringRefList *closeSequenceNames;

    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        beNDMWWindow_PlayQueuedModelClose(self);
        closeInfoNames = (igStringRefList *)self->_modelCloseInfoNameList;
        EMPTY_STRING_SLOTS(closeInfoNames)
        closeInfoNames->_count = 0;
        ((igIntList *)self->_modelCloseRamNoList)->_count = 0;
        closeSequenceNames = (igStringRefList *)self->_modelCloseSeqNameList;
        EMPTY_STRING_SLOTS(closeSequenceNames)
        closeSequenceNames->_count = 0;
        beNDMWWindow_ClearQueuedText(self);
        NEXT_STATE(self)
        ENTER_STEP(self, DISK_MENU)
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case DISK_MENU:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect01> menu((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, 0x60E);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menu.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case DISK_MENU_BUY:
                        ENTER_STEP(self, DISK_LIST)
                        self->_cursor = 0;
                        return;
                    case DISK_MENU_SELL:
                        ENTER_STEP(self, DISK_SELL)
                        return;
                    case DISK_MENU_EXIT:
                    default:
                        NEXT_STATE(self)
                        return;
                    }
                }
                break;
            }
            break;
        case DISK_LIST:
            switch (self->_st2) {
            case LIST_PRESENT:
                beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_WAIT_5, SQ_CLOSE_10);
                leftArrowPos[0] = -146.0f;
                leftArrowPos[1] = 25.0f;
                leftArrowPos[2] = 0.0f;
                beNDMWWindow_PresentModel(self, i_stcursorleft_2, 0, SQ_HIDE_2, SQ_CLOSE_10, leftArrowPos);
                rightArrowPos[0] = 236.0f;
                rightArrowPos[1] = 25.0f;
                rightArrowPos[2] = 0.0f;
                beNDMWWindow_PresentModel(self, i_stcursorright_2, 0, SQ_HIDE_2, SQ_CLOSE_10, rightArrowPos);
                beMessenger_SendNamed(self->_messenger, DATABASE_11, conItem_2, 0, GETDATABASE_10);
                conItems = beMessenger_GetObject(self->_messenger, 0);
                StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT13_2)));
                StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_fontNames[0])));
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x5DD);
                row = 0;
                font = g_fontNames;
                do {
                    beNDMWWindow_QueueText(self, STWINFONT14, *font, beDataBase_GetRecordString(conItems, row, NAME_2), LEFT_4);
                    beNDMWWindow_QueueNumberText(self, STWINFONT17, *font, beDataBase_GetRecordInt(conItems, row, HANBAI_2), RIGHT_3);
                    row += 1;
                    font += 1;
                } while (row < DISK_ROWS);
                beNDMWWindow_QueueText(self, STWINFONT29, g_fontNames[0], space_2, LEFT_4);
                NEXT_PHASE(self)
            case LIST_SELECT:
                beNDMWShopCtrl50_MoveRowCursor((beNDMWWindow *)self, -1);
                beMessenger_SendNamed(self->_messenger, MODELCTRL_16, j_shwin, 0, SQ_CWINOPEN);
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWStatusSelectE1> select((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(allocator));
                    beNDMWStatusSelectE1 *selectWindow;
                    beNDMWWindow_BindContext(select.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, select.p);
                    selectWindow = select.p;
                    selectWindow->_offsetPos[0] = -121.0f;
                    selectWindow->_offsetPos[1] = 128.0f;
                    selectWindow->_offsetPos[2] = 0.0f;
                    select.p->_startPoint = self->_cursor;
                    select.p->_selectMax = DISK_ROWS;
                    StringList_AppendRetained(select.p->_textCloseTypeList, StringRef(InternString(STWINFONT29)));
                    StringList_AppendRetained(select.p->_textCloseNameList, StringRef(InternString(font100_3)));
                    beNDMWWindow_RunMessageScript(select.p, txt_shop_lua_2, 0x611);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
                self->_retCode = self->_cursor;
            case LIST_DESCRIBE:
                if (self->_retCode != -1) {
                    beMessenger_SendNamed(self->_messenger, DATABASE_11, conItem_2, 0, GETDATABASE_10);
                    conItems = beMessenger_GetObject(self->_messenger, 0);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, g_fontNames[0]);
                    AppendRecordString(self->_messenger, conItems, self->_retCode, TXT);
                    beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, g_fontNames[0]);
                    beMessenger_AppendString(self->_messenger, DISPON);
                    beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
                }
                NEXT_PHASE(self)
                self->_st3 = self->_retCode;
            case LIST_WAIT:
                if (ObjectList_Count(self->_subWindow) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_retCode != self->_st3) {
                            ENTER_PHASE(self, LIST_DESCRIBE)
                            return;
                        }
                    }
                } else {
                    if (self->_retCode != -1) {
                        self->_cursor = self->_retCode;
                        beNDMWShopCtrl50_MoveRowCursor((beNDMWWindow *)self, self->_cursor);
                        self->_conItemNo = self->_retCode;
                        REQUEST_PLAYER(self)
                        heldDisks = PlayerFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_5);
                        heldCount = 0;
                        slot = 0;
                        if (0 < heldDisks->_count) {
                            do {
                                disk = ((beNDMWItemDisk **)heldDisks->_data)[slot];
                                if (disk != 0 && self->_conItemNo == disk->_recNo) {
                                    heldCount = DiskCount(disk);
                                    break;
                                }
                                slot += 1;
                            } while (slot < heldDisks->_count);
                        }
                        if (heldCount == DISK_STACK_MAX) {
                            ENTER_STEP(self, DISK_NOTICE)
                            self->_st3 = 0x623;
                            return;
                        }
                        ENTER_STEP(self, DISK_QUANTITY)
                        self->_diskCnt = heldCount;
                        return;
                    }
                    ENTER_STATE(self, SHOP_STATE_OPEN)
                    return;
                }
                break;
            }
            break;
        case DISK_QUANTITY:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, MODELCTRL_16, j_shwin, 0, SQ_DWINOPEN);
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect52> quantity((beNDMWShopSelect52 *)beNDMWShopSelect52_Create(allocator));
                    beNDMWShopSelect52 *quantityWindow;
                    beNDMWWindow_BindContext(quantity.p, self, self->_insight, self->_playerNo, DISK_STACK_MAX - self->_diskCnt);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, quantity.p);
                    quantityWindow = quantity.p;
                    quantityWindow->_offsetPos[0] = 52.0f;
                    quantityWindow->_offsetPos[1] = -69.0f;
                    quantityWindow->_offsetPos[2] = 0.0f;
                    StringList_AppendRetained(quantity.p->_textCloseTypeList, StringRef(InternString(STWINFONT29)));
                    StringList_AppendRetained(quantity.p->_textCloseNameList, StringRef(InternString(font100_3)));
                    beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x624);
                    beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x5DE);
                    self->_retCode = (DISK_STACK_MAX - 1) - self->_diskCnt;
                    beNDMWShopCtrl50_ShowQuantity(self);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            beNDMWShopCtrl50_ShowQuantity(self);
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    switch (self->_retCode) {
                    default:
                        ENTER_STEP(self, DISK_PURCHASE)
                        self->_st3 = (DISK_STACK_MAX - self->_diskCnt) - self->_retCode;
                        return;
                    case -1:
                        beNDMWShopCtrl50_HideQuantity(self);
                        ENTER_STEP(self, DISK_LIST)
                        ENTER_PHASE(self, LIST_SELECT)
                    }
                    return;
                }
                break;
            }
            break;
        case DISK_PURCHASE:
            switch (self->_st2) {
            case PURCHASE_CHECK_BITS:
                beMessenger_SendNamed(self->_messenger, DATABASE_11, conItem_2, 0, GETDATABASE_10);
                self->_tanka = beDataBase_GetRecordInt(beMessenger_GetObject(self->_messenger, 0), self->_conItemNo, HANBAI_2);
                self->_kazu = self->_st3;
                cost = self->_tanka * self->_kazu;
                REQUEST_PLAYER(self)
                if (cost <= PlayerInt(beMessenger_GetObject(self->_messenger, 0), BIT_7)->_data) {
                    NEXT_PHASE(self)
                    return;
                }
                ENTER_STEP(self, DISK_NOTICE)
                self->_st3 = 0x622;
                return;
            case PURCHASE_ANNOUNCE:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect00> message((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, 0x613);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case PURCHASE_CONFIRM:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    PICK_ALLOCATOR(allocator, self)
                    {
                        igSmartPointer<beNDMWShopSelect01> yesNo((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                        beNDMWWindow_BindContext(yesNo.p, self, self->_insight, self->_playerNo, 0x614);
                        ObjectList_AppendRetained((igObjectList *)self->_subWindow, yesNo.p);
                    }
                    self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                    NEXT_PHASE(self)
                    return;
                }
                break;
            case PURCHASE_APPLY:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    beNDMWShopCtrl50_HideQuantity(self);
                    switch (self->_retCode) {
                    case ANSWER_YES:
                        totalPrice = self->_tanka * self->_kazu;
                        REQUEST_PLAYER(self)
                        player = beMessenger_GetObject(self->_messenger, 0);
                        bits = PlayerInt(player, BIT_7)->_data;
                        money = PlayerInt(player, BIT_7);
                        money->_data = bits - totalPrice;
                        UPDATE_SUBWINDOW(self)
                        ownedDisks = PlayerFolder(player, DISKFOLDER_5);
                        ownedSlot = 0;
                        if (0 < ownedDisks->_count) {
                            do {
                                ownedDisk = ((beNDMWItemDisk **)ownedDisks->_data)[ownedSlot];
                                if (ownedDisk != 0 && self->_conItemNo == ownedDisk->_recNo) {
                                    ownedDisk->_kazu = DiskCount(ownedDisk) + self->_kazu;
                                    break;
                                }
                                ownedSlot += 1;
                            } while (ownedSlot < ownedDisks->_count);
                        }
                        break;
                    case ANSWER_NO:
                    default:
                        break;
                    }
                    ENTER_STEP(self, DISK_LIST)
                    ENTER_PHASE(self, LIST_SELECT)
                    return;
                }
                break;
            }
            break;
        case DISK_NOTICE:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect00> message((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, self->_st3);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    beNDMWShopCtrl50_HideQuantity(self);
                    ENTER_STEP(self, DISK_LIST)
                    return;
                }
                break;
            }
            break;
        case DISK_SELL:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopCtrlSell> sell((beNDMWShopCtrlSell *)beNDMWShopCtrlSell_Create(allocator));
                    beNDMWWindow_BindContext(sell.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, sell.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    ENTER_STEP(self, DISK_MENU)
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Shows the chosen quantity (font010) and its total price (font021) in the quantity window. */
void beNDMWShopCtrl50_ShowQuantity(beNDMWShopCtrl50 *self) {
    char text[16];
    int conItems;
    int quantity;
    int unitPrice;

    beMessenger_SendNamed(self->_messenger, DATABASE_11, conItem_2, 0, GETDATABASE_10);
    conItems = beMessenger_GetObject(self->_messenger, 0);
    quantity = (DISK_STACK_MAX - self->_diskCnt) - self->_retCode;
    unitPrice = beDataBase_GetRecordInt(conItems, self->_conItemNo, HANBAI_2);
    sprintf(text, percent_d, quantity);
    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
    beMessenger_AppendString(self->_messenger, STWINFONT32);
    beMessenger_AppendString(self->_messenger, font010_3);
    beMessenger_AppendString(self->_messenger, text);
    beMessenger_DispatchSelected(self->_messenger, TEXTSET);
    sprintf(text, percent_d, quantity * unitPrice);
    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
    beMessenger_AppendString(self->_messenger, STWINFONT32);
    beMessenger_AppendString(self->_messenger, font021);
    beMessenger_AppendString(self->_messenger, text);
    beMessenger_DispatchSelected(self->_messenger, TEXTSET);
}

/* Hides the quantity window's labels: the caption (font020), the quantity and the total price. */
void beNDMWShopCtrl50_HideQuantity(beNDMWShopCtrl50 *self) {
    HIDE_TEXT(self, STWINFONT32, font020)
    HIDE_TEXT(self, STWINFONT32, font010_3)
    HIDE_TEXT(self, STWINFONT32, font021)
}

/* Moves the disk list's row cursor model to `row` (generating it on first use), or closes it
 * for a negative row. */
void beNDMWShopCtrl50_MoveRowCursor(beNDMWWindow *window, int row) {
    RowCursorSequences rowSequences;
    float position[3];
    if (row > -1) {
        rowSequences = g_diskListCursorSequences;
        beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, ISRUN_10);
        if (beMessenger_GetBool(window->_messenger, 0) != 0) {
            beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, rowSequences.row[row]);
            return;
        }
        beMessenger_SelectReceivers(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0);
        beMessenger_AppendString(window->_messenger, rowSequences.row[row]);
        position[2] = 0;
        position[0] = -121.0f;
        position[1] = 128.0f;
        beMessenger_AppendVec3(window->_messenger, position);
        beMessenger_DispatchSelected(window->_messenger, GENERATE_13);
        return;
    }
    beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, ISRUN_10);
    if (beMessenger_GetBool(window->_messenger, 0) != 0) {
        beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, SQ_CLOSE_10);
    }
}

/* Retains `object`, releases the reference held in `field` and stores `object` there. */
#define SET_OBJECT_REF(field, object) { \
    igObject *retained = (igObject *)(object); \
    if (retained != 0) retained->_refCount = (int)retained->_refCount + 1; \
    { igObject *previous = (igObject *)(field); RELEASE(previous) } \
    (field) = (int)retained; }

/* _retCode of a child window closed with cancel. */
enum { RET_CANCEL = -1 };

enum SubWndMode { SUBWND_MODE_JUNK = 9, SUBWND_MODE_CARD = 10 };

enum JunkStep { JUNK_STEP_MENU, JUNK_STEP_DONATE, JUNK_STEP_BUY, JUNK_STEP_FAREWELL };
enum JunkMenuChoice { JUNK_CHOICE_DONATE, JUNK_CHOICE_BUY, JUNK_CHOICE_LEAVE, JUNK_MENU_CHOICES };
/* Index of the lifetime junk donation total in the GAMERAM common COUNTER list. */
enum { COUNTER_JUNK_GIFT = 1 };
/* Donating stops once the lifetime total reaches the last reward threshold. */
enum { JUNK_GIFT_MAX = 3956000 };
/* beNDMWShopCtrlEditBit entry code: 0 deposit and 1 withdraw at the bank, 2 donate here. */
enum { EDITBIT_MODE_DONATE = 2 };

void beNDMWShopJunk_Update(beNDMWShopJunk *self) {
    void *allocator;
    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        beMessenger_SelectGroup(self->_messenger, SUBWND_8);
        beMessenger_AppendInt(self->_messenger, SUBWND_MODE_JUNK);
        beMessenger_DispatchSelected(self->_messenger, GETSHOPDATA);
        if (beMessenger_GetObjectCount(self->_messenger) > 0) {
            SET_OBJECT_REF(self->_junkItemList, beMessenger_GetObject(self->_messenger, 0));
            self->_totalGift = beMessenger_GetInt(self->_messenger, 1);
        }
        NEXT_STATE(self);
        ENTER_STEP(self, JUNK_STEP_MENU);
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case JUNK_STEP_MENU:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect01> menu((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, 0x79e);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menu.p);
                    menu.p->_startPoint = self->_junkMenu;
                    PICK_ALLOCATOR(allocator, self);
                    igSmartPointer<igBoolList> enabled((igBoolList *)igBoolList_Create(allocator));
                    if (self->_totalGift >= JUNK_GIFT_MAX) {
                        BoolList_Append(enabled.p, false);
                    } else {
                        BoolList_Append(enabled.p, true);
                    }
                    if (((igObjectList *)self->_junkItemList)->_count <= 0) {
                        BoolList_Append(enabled.p, false);
                    } else {
                        BoolList_Append(enabled.p, true);
                    }
                    BoolList_Append(enabled.p, true);
                    int i;
                    for (i = 0; i < enabled.p->_count; i++) {
                        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(self->_messenger, STWINFONT29);
                        beMessenger_AppendString(self->_messenger, g_fontNames[i]);
                        if (*(bool *)(enabled.p->_data + i)) {
                            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
                        } else {
                            beMessenger_DispatchSelected(self->_messenger, CANCELCOLOR_4);
                        }
                    }
                    beNDMWShopSelect01 *window = menu.p;
                    SET_OBJECT_REF(window->_decideList, enabled.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    {
                        int i;
                        for (i = 0; i < JUNK_MENU_CHOICES; i++) {
                            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                            beMessenger_AppendString(self->_messenger, STWINFONT29);
                            beMessenger_AppendString(self->_messenger, g_fontNames[i]);
                            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
                        }
                    }
                    switch (self->_retCode) {
                    case JUNK_CHOICE_DONATE:
                        self->_junkMenu = JUNK_CHOICE_DONATE;
                        ENTER_STEP(self, JUNK_STEP_DONATE);
                        return;
                    case JUNK_CHOICE_BUY:
                        self->_junkMenu = JUNK_CHOICE_BUY;
                        ENTER_STEP(self, JUNK_STEP_BUY);
                        return;
                    default:
                    case JUNK_CHOICE_LEAVE:
                        NEXT_STATE(self);
                        return;
                    }
                }
                break;
            }
            break;
        case JUNK_STEP_DONATE:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopCtrlEditBit> amount((beNDMWShopCtrlEditBit *)beNDMWShopCtrlEditBit_Create(allocator));
                    beNDMWWindow_BindContext(amount.p, self, self->_insight, self->_playerNo, EDITBIT_MODE_DONATE);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, amount.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    if (self->_retCode != RET_CANCEL) {
                        igIntList *counters;
                        beMessenger_SendGroup(self->_messenger, GAMERAM_14, GETCOMMON_10);
                        counters = (igIntList *)igProperty_GetRecordIntList(beMessenger_GetObject(self->_messenger, 0), COUNTER_4)->_data;
                        {
                            int count = counters->_count;
                            int *giftTotal = &((int *)counters->_data)[COUNTER_JUNK_GIFT];
                            int newTotal = *giftTotal + (int)self->_retCode;
                            if (count != 0 && count > COUNTER_JUNK_GIFT) *giftTotal = newTotal;
                        }
                        beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
                        {
                            int player = beMessenger_GetObject(self->_messenger, 0);
                            int bitsLeft = igProperty_GetRecord(player, BIT_7)->_data - self->_retCode;
                            igProperty_GetRecord(player, BIT_7)->_data = bitsLeft;
                        }
                        beMessenger_SelectGroup(self->_messenger, SUBWND_8);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, UPDATE_3);
                        ENTER_STEP(self, JUNK_STEP_MENU);
                        {
                            int thresholds[] = { 1000, 6000, 26000, 86000, 206000, 456000, 956000, 1956000, 3956000, -1 };
                            int *threshold = thresholds;
                            if (*threshold != -1) {
                                do {
                                    if (self->_totalGift < *threshold && ((int *)counters->_data)[COUNTER_JUNK_GIFT] >= *threshold) {
                                        beLua__RunNamedChunk(igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]), junkexit_lua, stagML13_lua);
                                        ENTER_STEP(self, JUNK_STEP_FAREWELL);
                                        return;
                                    }
                                    threshold++;
                                } while (*threshold != -1);
                            }
                        }
                    } else {
                        ENTER_STEP(self, JUNK_STEP_MENU);
                        return;
                    }
                }
                break;
            }
            break;
        case JUNK_STEP_BUY:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopCtrlSales> sales((beNDMWShopCtrlSales *)beNDMWShopCtrlSales_Create(allocator));
                    beNDMWWindow_BindContext(sales.p, self, self->_insight, self->_playerNo, SUBWND_MODE_JUNK);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, sales.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ENTER_STEP(self, JUNK_STEP_MENU);
                    return;
                }
                break;
            }
            break;
        case JUNK_STEP_FAREWELL:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect00> message((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, 0x7b2);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    NEXT_STATE(self);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Reads the count again instead of reusing a value already loaded. */
static inline int countOf(const igIntList *l) { return l->_count; }

/* Appends `value` to an igIntList, given as a pointer or as a reflected object-reference field;
 * `value` is read after the list has grown. */
template <class ListRef> static inline void IntList_Append(ListRef listRef, const int &value)
{
    int count;
    igIntList *list;
    list = (igIntList *)listRef;
    count = list->_count;
    if (count < list->_capacity) {
        list->_count = countOf(list) + 1;
    } else {
        List_Resize(list, count + 1, 4);
    }
    ((int *)list->_data)[count] = value;
}

static inline const int &IntList_Get(igIntList *list, int index)
{
    return ((int *)list->_data)[index];
}

/* The same, for the igIntList held in a reflected object-reference field. */
static inline const int &IntList_Get(int listField, int index)
{
    return ((int *)((igIntList *)listField)->_data)[index];
}

enum CardSetupStep { CARD_SETUP_PRESENT, CARD_SETUP_TITLES };
enum CardStep { CARD_STEP_WAIT_OPEN, CARD_STEP_MENU, CARD_STEP_PICK_PLAYER, CARD_STEP_PLAYER_MENU };
enum CardMenuChoice { CARD_CHOICE_ENTER, CARD_CHOICE_LEAVE };

void beNDMWShopCtrlA0_Update(beNDMWShopCtrlA0 *self) {
    void *allocator;
    int i;

    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        switch (self->_st1) {
        case CARD_SETUP_PRESENT:
            beNDMWWindow_PresentModelAtOrigin(self, j_shback, 0, SQ_OPENCARD, SQ_CLOSE_10);
            beNDMWWindow_PresentModelAtOrigin(self, i_bgclear_2, 0, SQ_OPEN_8, SQ_CLOSE_10);
            NEXT_STEP(self);
            return;
        case CARD_SETUP_TITLES:
            beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, j_shback, 0);
            beMessenger_AppendString(self->_messenger, SQ_OPENCARD);
            beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
            if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopTitle03> shopTitle((beNDMWShopTitle03 *)beNDMWShopTitle03_Create(allocator));
                    beNDMWWindow_BindContext(shopTitle.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, shopTitle.p);
                }
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWStatusTitle03> account((beNDMWStatusTitle03 *)beNDMWStatusTitle03_Create(allocator));
                    beNDMWWindow_BindContext(account.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, account.p);
                    SET_OBJECT_REF(self->_account, account.p);
                    beNDMWStatusTitle03_SetCancelPromptEnabled((beNDMWStatusTitle03 *)self->_account, 0);
                }
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopTitle01> serviceTitle((beNDMWShopTitle01 *)beNDMWShopTitle01_Create(allocator));
                    beNDMWWindow_BindContext(serviceTitle.p, self, self->_insight, self->_playerNo, self->_entCode);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, serviceTitle.p);
                }
                for (i = 0; i < MAX_PLAYERS; i++) {
                    beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
                    beMessenger_AppendInt(self->_messenger, i);
                    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
                    if (igProperty_GetRecordByte(beMessenger_GetObject(self->_messenger, 0), ISUSE_9)->_data != 0) {
                        IntList_Append(self->_playerNoList, i);
                    }
                }
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWStatusTitle01> playerTitle((beNDMWStatusTitle01 *)beNDMWStatusTitle01_Create(allocator));
                    beNDMWWindow_BindContext(playerTitle.p, self, self->_insight, self->_playerNo, 1);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, playerTitle.p);
                }
                NEXT_STATE(self);
                return;
            }
            break;
        }
        break;
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case CARD_STEP_WAIT_OPEN:
            beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, i_messwn_3, 0);
            beMessenger_AppendString(self->_messenger, SQ_OPEN_8);
            beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
            if (((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) && (self->_entCode == SUBWND_MODE_CARD)) {
                ENTER_STEP(self, CARD_STEP_MENU);
                return;
            }
            break;
        case CARD_STEP_MENU:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect02> menu((beNDMWShopSelect02 *)beNDMWShopSelect02_Create(allocator));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, 0x7D3);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menu.p);
                    beNDMWStatusTitle03_SetCancelPromptEnabled((beNDMWStatusTitle03 *)self->_account, 0);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case CARD_CHOICE_ENTER:
                        ENTER_STEP(self, CARD_STEP_PICK_PLAYER);
                        return;
                    default:
                    case CARD_CHOICE_LEAVE:
                        NEXT_STATE(self);
                        ((beSystem *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]))->_isSResetEnable = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case CARD_STEP_PICK_PLAYER:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect02> picker((beNDMWShopSelect02 *)beNDMWShopSelect02_Create(allocator));
                    beNDMWWindow_BindContext(picker.p, self, self->_insight, self->_playerNo, -1);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, picker.p);
                    {
                        int j;
                        for (j = 0; j < ((igIntList *)self->_playerNoList)->_count; j++) {
                            IntList_Append(picker.p->_playerNoList, IntList_Get(self->_playerNoList, j));
                        }
                    }
                }
                beNDMWStatusTitle03_SetCancelPromptEnabled((beNDMWStatusTitle03 *)self->_account, 1);
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        {
                            beNDMWStatusTitle01 *playerTitle;
                            FIND_CHILD(playerTitle, self, AsPlayerTitle)
                            if (playerTitle != 0) {
                                playerTitle->_playerNo = IntList_Get(self->_playerNoList, self->_retCode);
                                beNDMWStatusTitle01_ShowShopLayout(playerTitle);
                                self->_playerNo = IntList_Get(self->_playerNoList, self->_retCode);
                            }
                        }
                        PICK_ALLOCATOR(allocator, self);
                        {
                            igSmartPointer<beNDMWShopCtrlA1> playerMenu((beNDMWShopCtrlA1 *)beNDMWShopCtrlA1_Create(allocator));
                            beNDMWWindow_BindContext(playerMenu.p, self, self->_insight, IntList_Get(self->_playerNoList, self->_retCode), 0);
                            ObjectList_AppendRetained((igObjectList *)self->_subWindow, playerMenu.p);
                        }
                        self->_nowProcKazu = CHILD_COUNT(self);
                        ENTER_STEP(self, CARD_STEP_PLAYER_MENU);
                        return;
                    default:
                        ENTER_STEP(self, CARD_STEP_MENU);
                        return;
                    }
                }
                break;
            }
            break;
        case CARD_STEP_PLAYER_MENU:
            if (CHILD_COUNT(self) != self->_nowProcKazu) {
                ENTER_STEP(self, CARD_STEP_PICK_PLAYER);
                return;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        {
            igObject *account = (igObject *)self->_account;
            RELEASE(account)
        }
        self->_account = 0;
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* The steps of beNDMWShopCtrlA1 continue the numbering of beNDMWShopCtrlA0's; beNDMWShopCtrlA2
 * returns the step to resume with as its _retCode. */
enum CardPlayerStep { CARD_PLAYER_STEP_MENU = 4, CARD_PLAYER_STEP_BOOSTER = 5, CARD_PLAYER_STEP_ALBUM = 6 };
enum CardPlayerChoice { CARD_PLAYER_CHOICE_BOOSTER, CARD_PLAYER_CHOICE_ALBUM };
enum AlbumPhase { ALBUM_OPEN, ALBUM_SHOW_PAGE_COUNT, ALBUM_BROWSE };
/* _recNo of the card booster disk in the player's DISKFOLDER. */
enum { CARD_BOOSTER_REC_NO = 10 };

void beNDMWShopCtrlA1_Update(beNDMWShopCtrlA1 *self) {
    void *allocator;
    float accountOrigin[3];
    float messageOrigin[3];
    const igObjectList *disks;
    int boosters;
    int i;
    beNDMWItemDisk *disk;
    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        self->_st0 = CurrentState(self) + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        ENTER_STEP(self, CARD_PLAYER_STEP_MENU);
        return;
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case CARD_PLAYER_STEP_MENU:
            switch (self->_st2) {
            case CHILD_OPEN:
                beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, j_shbase_2, self->_playerNo);
                beMessenger_AppendString(self->_messenger, SQ_OPEN_8);
                beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) == 1) {
                    return;
                }
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect02> menu((beNDMWShopSelect02 *)beNDMWShopSelect02_Create(allocator));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, 0x7D5);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menu.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case CARD_PLAYER_CHOICE_BOOSTER:
                        ENTER_STEP(self, CARD_PLAYER_STEP_BOOSTER);
                        return;
                    case CARD_PLAYER_CHOICE_ALBUM:
                        ENTER_STEP(self, CARD_PLAYER_STEP_ALBUM);
                        return;
                    default:
                        NEXT_STATE(self);
                        return;
                    }
                }
                break;
            }
            break;
        case CARD_PLAYER_STEP_BOOSTER:
            switch (self->_st2) {
            case CHILD_OPEN:
                beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
                disks = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_5)->_data;
                boosters = 0;
                i = 0;
                while (i < disks->_count) {
                    disk = ((beNDMWItemDisk **)disks->_data)[i];
                    if (disk != 0 && disk->_recNo == CARD_BOOSTER_REC_NO) {
                        boosters = DiskCount(disk);
                        break;
                    }
                    i++;
                }
                if (boosters > 0) {
                    PICK_ALLOCATOR(allocator, self);
                    igSmartPointer<beNDMWShopCtrlA2> opener((beNDMWShopCtrlA2 *)beNDMWShopCtrlA2_Create(allocator));
                    beNDMWWindow_BindContext(opener.p, self, self->_insight, self->_playerNo, boosters);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, opener.p);
                } else {
                    PICK_ALLOCATOR(allocator, self);
                    igSmartPointer<beNDMWShopSelect03> message((beNDMWShopSelect03 *)beNDMWShopSelect03_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, 0x7D7);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                    beMessenger_SelectGroup(self->_messenger, SOUND_8);
                    beMessenger_AppendString(self->_messenger, CURSOR_NG_4);
                    beMessenger_DispatchSelected(self->_messenger, PLAY_6);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case CARD_PLAYER_STEP_ALBUM:
                        ENTER_STEP(self, CARD_PLAYER_STEP_ALBUM);
                        return;
                    case CARD_PLAYER_STEP_MENU:
                        ENTER_STEP(self, CARD_PLAYER_STEP_MENU);
                        return;
                    default:
                    case 0:
                        ENTER_STEP(self, CARD_PLAYER_STEP_MENU);
                        return;
                    }
                }
                break;
            }
            break;
        case CARD_PLAYER_STEP_ALBUM:
            switch (self->_st2) {
            case ALBUM_OPEN:
                beMessenger_SendNamed(self->_messenger, MODELCTRL_16, i_staccount_2, 0, SQ_CLOSE_10);
                beMessenger_SendNamed(self->_messenger, MODELCTRL_16, i_messwn_3, 0, SQ_CLOSE_10);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT34_2);
                beMessenger_AppendString(self->_messenger, g_fontNames[2]);
                beMessenger_AppendString(self->_messenger, DISPOFF);
                beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelectA0> pager((beNDMWShopSelectA0 *)beNDMWShopSelectA0_Create(allocator));
                    beNDMWWindow_BindContext(pager.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, pager.p);
                }
                beNDMWShopCtrlA1_ShowFirstAlbumPage(self);
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
                return;
            case ALBUM_SHOW_PAGE_COUNT:
                beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, j_shcardwin, 0);
                beMessenger_AppendString(self->_messenger, SQ_OPEN_8);
                beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) == 1) {
                    return;
                }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT33);
                beMessenger_AppendString(self->_messenger, font000_5);
                beMessenger_AppendString(self->_messenger, text_1);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT33);
                beMessenger_AppendString(self->_messenger, font001_5);
                beMessenger_AppendString(self->_messenger, text_9);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                NEXT_PHASE(self);
            case ALBUM_BROWSE:
                /* While the page selector is open its _retCode is the selected page; _st3 holds the page shown. */
                if (CHILD_COUNT(self) == self->_nowProcKazu) {
                    if (self->_retCode != RET_CANCEL && self->_st3 != self->_retCode) {
                        beNDMWShopCtrlA1_ShowAlbumPage(self);
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    beNDMWShopCtrlA1_CloseAlbumPage(self);
                    beNDMWWindow_RunMessageScript(self, txt_status_lua_4, 0);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT34_2);
                    beMessenger_AppendString(self->_messenger, g_fontNames[2]);
                    beMessenger_AppendString(self->_messenger, DISPON);
                    beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
                    beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, i_staccount_2, 0);
                    beMessenger_AppendString(self->_messenger, SQ_OPEN_8);
                    accountOrigin[0] = g_vec3Zero[0];
                    accountOrigin[1] = g_vec3Zero[1];
                    accountOrigin[2] = g_vec3Zero[2];
                    beMessenger_AppendVec3(self->_messenger, accountOrigin);
                    beMessenger_DispatchSelected(self->_messenger, GENERATE_13);
                    beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, i_messwn_3, 0);
                    beMessenger_AppendString(self->_messenger, SQ_OPEN_8);
                    messageOrigin[0] = g_vec3Zero[0];
                    messageOrigin[1] = g_vec3Zero[1];
                    messageOrigin[2] = g_vec3Zero[2];
                    beMessenger_AppendVec3(self->_messenger, messageOrigin);
                    beMessenger_DispatchSelected(self->_messenger, GENERATE_13);
                    ENTER_STEP(self, CARD_PLAYER_STEP_MENU);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* The pooled empty string token. */
static inline const char *EmptyString()
{
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], 0);
}

/* Pooled strings keep their reference count in the word before the text and their chunk header
 * in the word before that. */
static inline void RetainString(const char *text)
{
    if (text) ((int *)text)[-1] = ((int *)text)[-1] + 1;
}

/* Stores a retained `name` into slot `index` of the igStringRefList held in `listField`. */
static inline void StringList_SetRetained(int listField, int index, const StringRef &name)
{
    igStringRefList *list = (igStringRefList *)listField;
    int count = list->_count;
    if (count != 0 && index >= 0 && index < count) {
        const char **slot = &((const char **)list->_data)[index];
        RetainString(name.p);
        ReleaseString(*slot);
        *slot = name.p;
    }
}

static inline void IntList_SetAt(int listField, int index, const int &value)
{
    igIntList *list = (igIntList *)listField;
    int count = list->_count;
    if (count != 0 && index >= 0 && index < count) ((int *)list->_data)[index] = value;
}

/* The album shows CARDS_PER_PAGE cards a page: models at ram number 0 for owned cards, the blank
 * card j_shcard00 at the slot's own ram number otherwise. */
enum { CARDS_PER_PAGE = 6, ALBUM_PAGES = 9, CARD_COUNT = 50, LAST_CARD_NO = CARD_COUNT - 1 };
/* _cardRamNoList entry of a slot with no model. */
enum { NO_MODEL = -1 };

void beNDMWShopCtrlA1_ShowFirstAlbumPage(beNDMWShopCtrlA1 *self) {
    igBoolList *owned;
    int database;
    int slot;
    beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
    owned = (igBoolList *)igProperty_GetRecordArray(beMessenger_GetObject(self->_messenger, 0), CARDLIST_3)->_data;
    beMessenger_SendNamed(self->_messenger, DATABASE_11, card, 0, GETDATABASE_10);
    if (beMessenger_GetObjectCount(self->_messenger) > 0) {
        database = beMessenger_GetObject(self->_messenger, 0);
    } else {
        return;
    }
    for (slot = 0; slot < CARDS_PER_PAGE; slot++) {
        /* Both lookups are repeated below; these results are unused. */
        beDataBase_GetRecordString(database, slot, CARDINFO);
        beDataBase_GetRecordString(database, slot, SQALBUM);
        if (*(unsigned char *)(owned->_data + slot) != 0) {
            StringRef name(InternString(beDataBase_GetRecordString(database, slot, CARDINFO)));
            beNDMWWindow_PresentModelAtOrigin(self, name.p, 0, beDataBase_GetRecordString(database, slot, SQALBUM), 0);
            {
                StringRef copy(name.p);
                RetainString(copy.p);
                StringList_AppendRetained(self->_cardInfoList, copy);
            }
            IntList_Append(self->_cardRamNoList, 0);
        } else {
            beNDMWWindow_PresentModelAtOrigin(self, j_shcard00, slot, beDataBase_GetRecordString(database, slot, SQALBUM), 0);
            StringList_AppendRetained(self->_cardInfoList, StringRef(InternString(j_shcard00)));
            IntList_Append(self->_cardRamNoList, slot);
        }
    }
}

void beNDMWShopCtrlA1_ShowAlbumPage(beNDMWShopCtrlA1 *self) {
    char pageText[2];
    igBoolList *owned;
    int page;
    int database;
    int slot;
    beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
    owned = (igBoolList *)igProperty_GetRecordArray(beMessenger_GetObject(self->_messenger, 0), CARDLIST_3)->_data;
    page = self->_retCode;
    beMessenger_SendNamed(self->_messenger, DATABASE_11, card, 0, GETDATABASE_10);
    if (beMessenger_GetObjectCount(self->_messenger) > 0) {
        database = beMessenger_GetObject(self->_messenger, 0);
    } else {
        return;
    }
    pageText[1] = 0;
    pageText[0] = page + '1';
    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
    beMessenger_AppendString(self->_messenger, STWINFONT33);
    beMessenger_AppendString(self->_messenger, font000_5);
    beMessenger_AppendString(self->_messenger, pageText);
    beMessenger_DispatchSelected(self->_messenger, TEXTSET);
    switch (page) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        for (slot = 0; slot < CARDS_PER_PAGE; slot++) {
            StringRef shown = StringList_CopyRetained(((igStringRefList *)self->_cardInfoList), slot);
            int cardNo = page * CARDS_PER_PAGE + slot;
            int ramNo = IntList_Get(self->_cardRamNoList, slot);
            if (cardNo > LAST_CARD_NO) {
                beNDMWWindow_SendModelSequence(self, shown.p, ramNo, SQ_CLOSE_10);
                StringList_SetRetained(self->_cardInfoList, slot, StringRef(InternString(blank)));
                IntList_SetAt(self->_cardRamNoList, slot, NO_MODEL);
            } else if (*(unsigned char *)(owned->_data + cardNo) != 0) {
                if (ramNo != NO_MODEL) beNDMWWindow_SendModelSequence(self, shown.p, ramNo, SQ_CLOSE_10);
                StringRef name(InternString(beDataBase_GetRecordString(database, cardNo, CARDINFO)));
                beNDMWWindow_PresentModelAtOrigin(self, name.p, 0, beDataBase_GetRecordString(database, cardNo, SQALBUM), 0);
                StringList_SetRetained(self->_cardInfoList, slot, name);
                IntList_SetAt(self->_cardRamNoList, slot, 0);
            } else {
                if (ramNo != NO_MODEL) {
                    if (strcmp(shown.p, j_shcard00) == 0)
                        continue;
                    beNDMWWindow_SendModelSequence(self, shown.p, ramNo, SQ_CLOSE_10);
                }
                beNDMWWindow_PresentModelAtOrigin(self, j_shcard00, slot, beDataBase_GetRecordString(database, slot, SQALBUM), 0);
                StringList_SetRetained(self->_cardInfoList, slot, StringRef(InternString(j_shcard00)));
                IntList_SetAt(self->_cardRamNoList, slot, slot);
            }
        }
        break;
    }
}

void beNDMWShopCtrlA1_CloseAlbumPage(beNDMWShopCtrlA1 *self) {
    igStringRefList *names;
    igStringRefList *cleared;
    int count;
    int slot;
    int index;

    names = (igStringRefList *)self->_cardInfoList;
    for (slot = 0; slot < names->_count; slot++) {
        {
            StringRef name = StringList_CopyRetained(names, slot);
            int ramNo = IntList_Get(self->_cardRamNoList, slot);
            if (ramNo != NO_MODEL) {
                beNDMWWindow_SendModelSequence(self, name.p, ramNo, SQ_CLOSE_10);
            }
        }
        names = (igStringRefList *)self->_cardInfoList;
    }
    cleared = (igStringRefList *)names;
    count = cleared->_count;
    for (index = 0; index < count; index++) {
        const char **entry = &((const char **)cleared->_data)[index];
        const char *empty = EmptyString();
        ReleaseString(*entry);
        *entry = empty;
    }
    cleared->_count = 0;
    ((igIntList *)self->_cardRamNoList)->_count = 0;
}


/* Replaces every entry of a string list with the pool's interned null string and empties the list. */
#define CLEAR_STRING_LIST(list) { \
    igStringRefList *strings = (igStringRefList *)(list); \
    int count = strings->_count; \
    int i; \
    for (i = 0; i < count; i++) { \
        char **slot = (char **)strings->_data + i; \
        char *empty = (char *)InternLiteral(0); \
        ReleaseString(*slot); \
        *slot = empty; \
    } \
    strings->_count = 0; }

#define PLAY_CURSOR_NG(window) { \
    beMessenger_SelectGroup((window)->_messenger, SOUND_8); \
    beMessenger_AppendString((window)->_messenger, CURSOR_NG_4); \
    beMessenger_DispatchSelected((window)->_messenger, PLAY_6); }

enum BoosterStep { BOOSTER_STEP_OFFER = 7, BOOSTER_STEP_OPEN_PACK = 8 };
enum BoosterOfferSubstep { OFFER_SHOW_PACKS, OFFER_WAIT_DESCRIPTION, OFFER_ASK, OFFER_WAIT_ANSWER };
enum BoosterOpenSubstep { OPEN_DRAW_CARDS, OPEN_WAIT_RESULT };
enum BoosterChoice { BOOSTER_CHOICE_OPEN = 0, BOOSTER_CHOICE_ALBUM = 1 };
/* Results the card shop (beNDMWShopCtrlA1) reads back from the booster window. */
enum BoosterResult { BOOSTER_RESULT_MENU = 4, BOOSTER_RESULT_ALBUM = 6 };
enum CardRarity { CARD_RARITY_NORMAL, CARD_RARITY_RARE, CARD_RARITY_SUPER_RARE };
enum {
    BOOSTER_PACK_REC_NO = 10, /* the booster-pack disk in the player's disk folder */
    BOOSTER_PACK_CARDS = 3,
    CARD_CHANCE_SCALE = 1000  /* KAKURITSU is in thousandths */
};

enum EvolveOpenStep { EVOLVE_OPEN_MESSAGE_WINDOW, EVOLVE_SET_UP_LIST };
enum EvolveStep {
    EVOLVE_STEP_OPEN_LIST,
    EVOLVE_STEP_SHOW_SELECTION,
    EVOLVE_STEP_SELECT,
    EVOLVE_STEP_CONFIRM,
    EVOLVE_STEP_REFUSE
};
enum EvolveConfirmSubstep {
    CONFIRM_ASK,
    CONFIRM_WAIT_ANSWER,
    CONFIRM_NOTICE,
    CONFIRM_WAIT_NOTICE,
    CONFIRM_ASK_AGAIN,
    CONFIRM_WAIT_SECOND_ANSWER,
    CONFIRM_EVOLVE,
    CONFIRM_WAIT_EVOLVED
};
/* EVOLVE_STEP_REFUSE keeps the reason in _st2 and counts its substeps in _st3. */
enum EvolveRefusal { REFUSE_CURRENT_SPECIES, REFUSE_EQUIPMENT };
enum EvolveRefuseSubstep { REFUSE_SHOW_MESSAGE, REFUSE_WAIT_MESSAGE };
/* Result the Digilabo window (beNDMWShopCtrlDigilabo) reads back: the player's Digimon changed. */
enum { EVOLVE_RESULT_EVOLVED = 1 };
enum {
    EVOLVE_PAGE_ROWS = 8,
    EVOLVE_MAX_PAGES = 2,
    EVOLVE_EMPTY_SELECT_MAX = 2,
    EVOLVE_STAT_ROWS = 16
};

static inline beNDMWShinkaObjectList *EvolutionList(const beNDMWShopCtrlEvolve *self)
{
    return (beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list;
}

/* Sends TEXTCTL `command` with `value` to text element `name` of text type `type`. */
#define TEXT_CONTROL(window, type, name, value, command) { \
    beMessenger_SelectGroup((window)->_messenger, TEXTCTL_3); \
    beMessenger_AppendString((window)->_messenger, type); \
    beMessenger_AppendString((window)->_messenger, name); \
    beMessenger_AppendString((window)->_messenger, value); \
    beMessenger_DispatchSelected((window)->_messenger, command); }
#define EVOLUTION_AT(list, index) (((beNDMWShinkaObject **)(list)->_data)[index])

/* The two text-element names of one stat row: its label and its value. */
struct StatRowNames {
    const char *label;
    const char *value;
};

/* The booster-pack window: shows the player's unopened packs, offers to open one and deals three
 * cards drawn by their KAKURITSU weights into the player's CARDLIST. */
void beNDMWShopCtrlA2_Update(beNDMWShopCtrlA2 *self) {
    void *allocator;
    const char *packSequence;
    unsigned cardRolls[BOOSTER_PACK_CARDS];
    BoosterCardTexts cardTextNames;
    BoosterCardTexts cardModelSequences;
    BoosterCardTexts cardTextNamesToReset;
    float rarityColor[3];
    int player;
    beNDMWStatus *status;
    int bestRarity;
    int i;
    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        self->_st0 = CurrentState(self) + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        ENTER_STEP(self, BOOSTER_STEP_OFFER);
        return;
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case BOOSTER_STEP_OFFER:
            switch (self->_st2) {
            case OFFER_SHOW_PACKS:
                /* The entry code is the number of packs the player holds. */
                switch ((unsigned)self->_entCode) {
                case 1: packSequence = SQ_OPEN00_2; break;
                case 2: packSequence = SQ_OPEN01_3; break;
                case 3: packSequence = SQ_OPEN02_3; break;
                case 4: packSequence = SQ_OPEN03_2; break;
                case 5: packSequence = SQ_OPEN04_2; break;
                case 6: packSequence = SQ_OPEN05_2; break;
                case 7: packSequence = SQ_OPEN06_2; break;
                case 8: packSequence = SQ_OPEN07_2; break;
                case 9: packSequence = SQ_OPEN08_2; break;
                }
                beNDMWWindow_PresentModelAtOrigin(self, j_shbooster, 0, packSequence, SQ_CLOSE_10);
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect03> description((beNDMWShopSelect03 *)beNDMWShopSelect03_Create(allocator));
                    beNDMWWindow_BindContext(description.p, self, self->_insight, self->_playerNo, 0x7DD);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, description.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case OFFER_WAIT_DESCRIPTION:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    NEXT_PHASE(self);
                }
                break;
            case OFFER_ASK:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect02> question((beNDMWShopSelect02 *)beNDMWShopSelect02_Create(allocator));
                    beNDMWWindow_BindContext(question.p, self, self->_insight, self->_playerNo, 0x7D8);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, question.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case OFFER_WAIT_ANSWER:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case BOOSTER_CHOICE_OPEN:
                        beNDMWWindow_PlayQueuedModelClose(self);
                        CLEAR_STRING_LIST(self->_modelCloseInfoNameList)
                        ((igIntList *)self->_modelCloseRamNoList)->_count = 0;
                        CLEAR_STRING_LIST(self->_modelCloseSeqNameList)
                        ENTER_STEP(self, BOOSTER_STEP_OPEN_PACK);
                        return;
                    case BOOSTER_CHOICE_ALBUM:
                        ((beNDMWWindow *)self->_mother)->_retCode = BOOSTER_RESULT_ALBUM;
                        NEXT_STATE(self);
                        return;
                    default:
                        ((beNDMWWindow *)self->_mother)->_retCode = BOOSTER_RESULT_MENU;
                        NEXT_STATE(self);
                        return;
                    }
                }
                break;
            }
            break;
        case BOOSTER_STEP_OPEN_PACK:
            switch (self->_st2) {
            case OPEN_DRAW_CARDS:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect03> result((beNDMWShopSelect03 *)beNDMWShopSelect03_Create(allocator));
                    beNDMWWindow_BindContext(result.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, result.p);
                    SEND_PLAYER_MESSAGE(self, GAMERAM_14, GETPLAYER_10);
                    player = beMessenger_GetObject(self->_messenger, 0);
                    {
                        const igObjectList *disks = (igObjectList *)igProperty_GetRecordFolder(player, DISKFOLDER_5)->_data;
                        int slot;
                        for (slot = 0; slot < disks->_count; slot++) {
                            beNDMWItemDisk *disk = ((beNDMWItemDisk **)disks->_data)[slot];
                            if (disk != 0 && disk->_recNo == BOOSTER_PACK_REC_NO) {
                                if (DiskCount(disk) > 0) disk->_kazu = DiskCount(disk) - 1;
                                break;
                            }
                        }
                    }
                    beMessenger_SendNamed(self->_messenger, DATABASE_11, card, 0, GETDATABASE_10);
                    {
                        int cards = beMessenger_GetObject(self->_messenger, 0);
                        status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                        bestRarity = 0;
                        cardTextNames = g_boosterCardNameTexts;
                        cardModelSequences = g_boosterCardOpenSequences;
                        for (i = 0; i < BOOSTER_PACK_CARDS; i++) {
                            unsigned char drawn;
                            int chance;
                            int card;
                            int cardCount;
                            cardRolls[i] = (((RandomNumberDispatch *)((beSystem *)status->_system)->_random)->genrand() % CARD_CHANCE_SCALE) * CARD_CHANCE_SCALE;
                            drawn = 0;
                            chance = 0;
                            card = 0;
                            cardCount = beDataBase_GetRecordCount(cards);
                            for (; card < cardCount; card++) {
                                chance += beDataBase_GetRecordInt(cards, card, KAKURITSU) * CARD_CHANCE_SCALE;
                                if (cardRolls[i] < (unsigned)chance) { drawn = 1; break; }
                            }
                            if (drawn == 0) card = cardCount - 1;
                            {
                                igBoolList *obtainedCards = (igBoolList *)igProperty_GetRecordArray(player, CARDLIST_3)->_data;
                                BoolList_Set(obtainedCards, card, true);
                            }
                            if (bestRarity < beDataBase_GetRecordInt(cards, card, RARE)) bestRarity = beDataBase_GetRecordInt(cards, card, RARE);
                            beNDMWWindow_QueueText(result.get(), TALKFONT01, cardTextNames.text[i], beDataBase_GetRecordString(cards, card, NAME_2), LEFT_4);
                            beNDMWWindow_PresentModelAtOrigin(result.p, beDataBase_GetRecordString(cards, card, CARDINFO), i, cardModelSequences.text[i], SQ_CLOSE_10);
                            {
                                float red, green, blue;
                                switch (beDataBase_GetRecordInt(cards, card, RARE)) {
                                case CARD_RARITY_SUPER_RARE: red = 0.0f; green = 1.0f; blue = 0.0f; break;
                                case CARD_RARITY_RARE: red = 1.0f; green = 1.0f; blue = 0.0f; break;
                                default: red = 1.0f; green = 1.0f; blue = 1.0f; break;
                                }
                                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                                beMessenger_AppendString(self->_messenger, TALKFONT01);
                                beMessenger_AppendString(self->_messenger, cardTextNames.text[i]);
                                rarityColor[0] = red; rarityColor[1] = green; rarityColor[2] = blue;
                                beMessenger_AppendVec3(self->_messenger, rarityColor);
                                beMessenger_DispatchSelected(self->_messenger, COLOR_4);
                            }
                        }
                    }
                    switch (bestRarity) {
                    case CARD_RARITY_SUPER_RARE: result->_entCode = 0x7DA; break;
                    case CARD_RARITY_RARE: result->_entCode = 0x7DB; break;
                    default: result->_entCode = 0x7DC; break;
                    }
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case OPEN_WAIT_RESULT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    int k;
                    cardTextNamesToReset = g_boosterCardNameTextsReset;
                    for (k = 0; k < BOOSTER_PACK_CARDS; k++) {
                        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(self->_messenger, TALKFONT01);
                        beMessenger_AppendString(self->_messenger, cardTextNamesToReset.text[k]);
                        beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
                    }
                    ((beNDMWWindow *)self->_mother)->_retCode = BOOSTER_RESULT_MENU;
                    NEXT_STATE(self);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* The Digivolution menu of the Digilabo: lists the evolutions the player's Digimon can take, eight
 * to a page with the selected one's stats and explanation, and evolves after two confirmations. */
void beNDMWShopCtrlEvolve_Update(beNDMWShopCtrlEvolve *self) {
    float leftArrowPos[3];
    float rightArrowPos[3];
    void *allocator;
    int count;
    beNDMWShinkaObject *evolution;
    int currentSpecies;

    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        switch (self->_st1) {
        case EVOLVE_OPEN_MESSAGE_WINDOW:
            beNDMWWindow_PresentModelAtOrigin(self, i_messwn_3, 0, SQ_STOPEN_3, SQ_STCLOSE_2);
            NEXT_STEP(self);
        case EVOLVE_SET_UP_LIST:
            beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, i_messwn_3, 0);
            beMessenger_AppendString(self->_messenger, SQ_STOPEN_3);
            beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
            if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                beNDMWShinkaCtrl_Setup((beNDMWShinkaCtrl *)self->_shinkaCtrl, self->_insight, self->_playerNo);
                if (EvolutionList(self)->_count > EVOLVE_PAGE_ROWS) {
                    self->_maxPage = EVOLVE_MAX_PAGES;
                } else {
                    self->_maxPage = 1;
                }
                self->_nowPage = 0;
                self->_cursor = 0;
                if (self->_maxPage > 1) {
                    beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_SINKAONOPEN, SQ_CLOSE_10);
                    rightArrowPos[0] = -51.0f;
                    rightArrowPos[2] = 0.0f;
                    rightArrowPos[1] = 25.0f;
                    leftArrowPos[0] = -308.0f;
                    leftArrowPos[1] = 25.0f;
                    leftArrowPos[2] = 0.0f;
                    ((PagedWindow *)self)->PresentPageArrows(leftArrowPos, rightArrowPos);
                    beNDMWWindow_QueueText(self, STWINFONT31, g_fontNames[0], space_2, RIGHT_3);
                    beNDMWWindow_QueueText(self, STWINFONT31, g_fontName1[0], space_2, RIGHT_3);
                } else {
                    beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_SINKAOFFOPEN, SQ_CLOSE_10);
                }
                APPEND_INTERNED(self->_textCloseTypeList, STWINFONT29);
                APPEND_INTERNED(self->_textCloseNameList, font100_3);
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x4E6);
                APPEND_INTERNED(self->_textCloseTypeList, STWINFONT37);
                APPEND_INTERNED(self->_textCloseNameList, g_fontNames[0]);
                APPEND_INTERNED(self->_textCloseTypeList, STWINFONT37);
                APPEND_INTERNED(self->_textCloseNameList, g_fontName1[0]);
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x4C2);
                {
                    int row;
                    const char **rowName;
                    for (row = 0, rowName = g_fontNames; row < EVOLVE_PAGE_ROWS; row++, rowName++) {
                        beNDMWWindow_QueueText(self, STWINFONT20, *rowName, space_2, LEFT_4);
                        beNDMWWindow_QueueText(self, STWINFONT43, *rowName, space_2, LEFT_4);
                        beNDMWWindow_QueueText(self, STWINFONT21, *rowName, space_2, RIGHT_3);
                    }
                }
                {
                    int stat;
                    const StatRowNames *statRow;
                    for (stat = 0, statRow = (const StatRowNames *)g_evolveStatRowTexts; stat < EVOLVE_STAT_ROWS; stat++, statRow++) {
                        beNDMWWindow_QueueText(self, STWINFONT22, statRow->label, space_2, LEFT_4);
                        beNDMWWindow_QueueText(self, STWINFONT22, statRow->value, space_2, RIGHT_3);
                    }
                }
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x4B2);
                beNDMWWindow_QueueText(self, STWINFONT29, g_fontNames[0], space_2, LEFT_4);
                NEXT_STATE(self);
                ENTER_STEP(self, EVOLVE_STEP_OPEN_LIST);
                return;
            }
            break;
        }
        break;
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case EVOLVE_STEP_OPEN_LIST:
            PICK_ALLOCATOR(allocator, self);
            {
                igSmartPointer<beNDMWStatusSelectE1> selector((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(allocator));
                beNDMWWindow_BindContext(selector.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, selector.p);
                {
                    float *offset = selector->_offsetPos;
                    offset[0] = -283.0f;
                    offset[1] = 92.0f;
                    offset[2] = 0.0f;
                    selector->_startPoint = self->_cursor;
                    count = EvolutionList(self)->_count;
                    if (count == 0) {
                        selector->_selectMax = EVOLVE_EMPTY_SELECT_MAX;
                    } else {
                        switch (self->_nowPage) {
                        case 0:
                            if (count > EVOLVE_PAGE_ROWS) {
                                selector->_selectMax = EVOLVE_PAGE_ROWS;
                            } else {
                                selector->_selectMax = count;
                            }
                            break;
                        case 1:
                            selector->_selectMax = count - EVOLVE_PAGE_ROWS;
                            break;
                        }
                    }
                }
            }
            self->_nowProcKazu = CHILD_COUNT(self);
            NEXT_STEP(self);
            self->_retCode = self->_cursor;
            beNDMWShopCtrlEvolve_RefreshText(self, 1, 0);
        case EVOLVE_STEP_SHOW_SELECTION:
            if (self->_retCode != -1) {
                beNDMWShopCtrlEvolve_RefreshText(self, 0, 1);
            }
            NEXT_STEP(self);
            self->_st3 = self->_retCode;
        case EVOLVE_STEP_SELECT:
            if (CHILD_COUNT(self) == self->_nowProcKazu) {
                if (self->_retCode != -1) {
                    if (self->_st3 != self->_retCode) {
                        ENTER_STEP(self, EVOLVE_STEP_SHOW_SELECTION);
                        return;
                    }
                    {
                        beNDMWWindowSelect *selector;
                        FIND_CHILD(selector, self, AsPageSelector)
                        if (beNDMWWindowSelect_CanRequestFO2TOP(selector) != 0) {
                            bool pageTurned = false;
                            if (((PagedWindow *)self)->TurnPagePrev() != 0) {
                                pageTurned = true;
                            } else if (((PagedWindow *)self)->TurnPageNext() != 0) {
                                pageTurned = true;
                            }
                            if (pageTurned) {
                                ENTER_STATE(selector, SELECT_STATE_RELOAD_TO_TOP);
                                count = EvolutionList(self)->_count;
                                if (count == 0) {
                                    selector->_selectMax = EVOLVE_EMPTY_SELECT_MAX;
                                } else {
                                    switch (self->_nowPage) {
                                    case 0:
                                        if (count > EVOLVE_PAGE_ROWS) {
                                            selector->_selectMax = EVOLVE_PAGE_ROWS;
                                        } else {
                                            selector->_selectMax = count;
                                        }
                                        break;
                                    case 1:
                                        selector->_selectMax = count - EVOLVE_PAGE_ROWS;
                                        break;
                                    }
                                }
                                ENTER_STEP(self, EVOLVE_STEP_SHOW_SELECTION);
                                self->_retCode = 0;
                                beNDMWShopCtrlEvolve_RefreshText(self, 1, 0);
                                return;
                            }
                        }
                    }
                }
            } else {
                switch (self->_retCode) {
                case -1:
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    NEXT_STATE(self);
                    return;
                default:
                    self->_cursor = self->_retCode;
                    evolution = EVOLUTION_AT(EvolutionList(self), self->_cursor + self->_nowPage * EVOLVE_PAGE_ROWS);
                    currentSpecies = igProperty_GetRecord(GetPlayer(self), DIGIMONNO_6)->_data;
                    beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_AppendInt(self->_messenger, evolution->_id);
                    beMessenger_DispatchSelected(self->_messenger, WEAPONEQUIPCHECK);
                    if (currentSpecies == evolution->_id) {
                        ENTER_STEP(self, EVOLVE_STEP_REFUSE);
                        self->_st2 = REFUSE_CURRENT_SPECIES;
                        self->_st3 = REFUSE_SHOW_MESSAGE;
                        PLAY_CURSOR_NG(self);
                        return;
                    }
                    if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
                        ENTER_STEP(self, EVOLVE_STEP_REFUSE);
                        self->_st2 = REFUSE_EQUIPMENT;
                        self->_st3 = REFUSE_SHOW_MESSAGE;
                        PLAY_CURSOR_NG(self);
                        return;
                    }
                    ENTER_STEP(self, EVOLVE_STEP_CONFIRM);
                    return;
                }
            }
            break;
        case EVOLVE_STEP_CONFIRM:
            switch (self->_st2) {
            case CONFIRM_ASK:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect01> question((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(question.p, self, self->_insight, self->_playerNo, 0x4E7);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, question.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CONFIRM_WAIT_ANSWER:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case ANSWER_YES:
                        NEXT_PHASE(self);
                        return;
                    case ANSWER_NO:
                    default:
                        ENTER_STEP(self, EVOLVE_STEP_OPEN_LIST);
                        return;
                    }
                }
                break;
            case CONFIRM_NOTICE:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect00> notice((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(notice.p, self, self->_insight, self->_playerNo, 0x4E9);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, notice.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CONFIRM_WAIT_NOTICE:
                if (CHILD_COUNT(self) == self->_nowProcKazu) break;
                NEXT_PHASE(self);
            case CONFIRM_ASK_AGAIN:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect01> question((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(question.p, self, self->_insight, self->_playerNo, 0x4EA);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, question.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            case CONFIRM_WAIT_SECOND_ANSWER:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case ANSWER_YES:
                        NEXT_PHASE(self);
                        return;
                    case ANSWER_NO:
                    default:
                        ENTER_STEP(self, EVOLVE_STEP_OPEN_LIST);
                        return;
                    }
                }
                break;
            case CONFIRM_EVOLVE: {
                beNDMWShinkaObjectList *evolutions;
                int evolutionCount;
                int index;
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect00> message((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                    APPEND_INTERNED(message->_textCloseTypeList, STWINFONT29);
                    APPEND_INTERNED(message->_textCloseNameList, font100_3);
                    beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x4EC);
                }
                evolutions = EvolutionList(self);
                index = self->_cursor + self->_nowPage * EVOLVE_PAGE_ROWS;
                evolutionCount = evolutions->_count;
                if (evolutionCount > 0 && index < evolutionCount) {
                    beNDMWShinkaObject *chosen = EVOLUTION_AT(evolutions, index);
                    char *explanation;
                    beMessenger_SendNamed(self->_messenger, DATABASE_11, shinka_5, 0, GETDATABASE_10);
                    explanation = beDataBase_GetRecordString(beMessenger_GetObject(self->_messenger, 0), chosen->_id, EXPLANATION_2);
                    TEXT_CONTROL(self, STWINFONT29, g_fontNames[0], explanation, TEXTSET);
                    TEXT_CONTROL(self, STWINFONT29, g_fontNames[0], DISPON, SWITCH_2);
                    beNDMWShopCtrlEvolve_ApplyEvolution(self);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self);
            }
            case CONFIRM_WAIT_EVOLVED:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ((beNDMWWindow *)self->_mother)->_retCode = EVOLVE_RESULT_EVOLVED;
                    NEXT_STATE(self);
                    return;
                }
                break;
            }
            break;
        case EVOLVE_STEP_REFUSE:
            switch (self->_st3) {
            case REFUSE_SHOW_MESSAGE:
                PICK_ALLOCATOR(allocator, self);
                {
                    igSmartPointer<beNDMWShopSelect00> message((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(message.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, message.p);
                    APPEND_INTERNED(message->_textCloseTypeList, STWINFONT29);
                    APPEND_INTERNED(message->_textCloseNameList, font000_5);
                    if (self->_st2 == REFUSE_CURRENT_SPECIES) {
                        beNDMWWindow_RunMessageScript(message.p, txt_shop_lua_2, 0x7E4);
                    } else {
                        beNDMWWindow_RunMessageScript(message.p, txt_shop_lua_2, 0x7E5);
                    }
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                self->_st3 = self->_st3 + 1;
            case REFUSE_WAIT_MESSAGE:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ENTER_STEP(self, EVOLVE_STEP_OPEN_LIST);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Rewrites the Digivolution window texts: with `refreshList`, the eight rows of the current page
 * (name, "Lv" and level, hidden past the end of the list) and the page counter; with
 * `refreshSelection`, the stats and explanation of the evolution under the cursor. */
void beNDMWShopCtrlEvolve_RefreshText(beNDMWShopCtrlEvolve *self, int refreshList, int refreshSelection) {
    char levelText[28];
    int stats[EVOLVE_STAT_ROWS];
    char statText[16];
    char pageText[4];
    beNDMWShinkaObjectList *evolutions;
    int row;
    char *name;
    const char **rowName;
    int stat;
    int pageStart;
    int cursor;
    int selected;
    beNDMWShinkaObjectList *selectionList;
    int index;
    beNDMWShinkaObject *evolution;
    beNDMWShinkaObject *selection;
    char *explanation;
    int *statValue;
    const StatRowNames *statRow;
    if (refreshList != 0) {
        evolutions = EvolutionList(self);
        for (row = 0, rowName = g_fontNames; row < EVOLVE_PAGE_ROWS; row++, rowName++) {
            index = row + self->_nowPage * EVOLVE_PAGE_ROWS;
            if (evolutions->_count - 1 < index) {
                TEXT_CONTROL(self, STWINFONT20, *rowName, DISPOFF, SWITCH_2);
                TEXT_CONTROL(self, STWINFONT43, *rowName, DISPOFF, SWITCH_2);
                TEXT_CONTROL(self, STWINFONT21, *rowName, DISPOFF, SWITCH_2);
            } else {
                evolution = EVOLUTION_AT(evolutions, index);
                name = (char *)evolution->_name;
                TEXT_CONTROL(self, STWINFONT20, *rowName, name, TEXTSET);
                TEXT_CONTROL(self, STWINFONT20, *rowName, DISPON, SWITCH_2);
                TEXT_CONTROL(self, STWINFONT43, *rowName, Lv_2, TEXTSET);
                TEXT_CONTROL(self, STWINFONT43, *rowName, DISPON, SWITCH_2);
                sprintf(levelText, percent_d, EVOLUTION_AT(evolutions, index)->_level);
                TEXT_CONTROL(self, STWINFONT21, *rowName, levelText, TEXTSET);
                TEXT_CONTROL(self, STWINFONT21, *rowName, DISPON, SWITCH_2);
            }
        }
        if (self->_maxPage > 1) {
            pageText[1] = 0;
            pageText[0] = '1' + self->_nowPage;
            TEXT_CONTROL(self, STWINFONT31, g_fontNames[0], pageText, TEXTSET);
            pageText[0] = '0' + self->_maxPage;
            TEXT_CONTROL(self, STWINFONT31, g_fontNames[1], pageText, TEXTSET);
        }
    }
    if (refreshSelection != 0) {
        cursor = self->_retCode;
        if (cursor != -1) {
            selectionList = EvolutionList(self);
            pageStart = self->_nowPage * EVOLVE_PAGE_ROWS;
            selected = pageStart + cursor;
            if (selected < selectionList->_count) {
                selection = EVOLUTION_AT(selectionList, selected);
                stats[0] = selection->_hpMax;
                stats[1] = selection->_mpMax;
                stats[2] = selection->_tsuyosa;
                stats[3] = selection->_mamori;
                stats[4] = selection->_kashikosa;
                stats[5] = selection->_seishin;
                stats[6] = selection->_subayasa;
                stats[7] = selection->_blunt;
                stats[8] = selection->_slash;
                stats[9] = selection->_stab;
                stats[10] = selection->_bash;
                stats[11] = selection->_shot;
                stats[12] = selection->_crush;
                stats[13] = selection->_blast;
                stats[14] = selection->_heal;
                stats[15] = selection->_force;
                for (stat = 0, statValue = stats, statRow = (const StatRowNames *)g_evolveStatRowTexts; stat < EVOLVE_STAT_ROWS; stat++, statValue++, statRow++) {
                    sprintf(statText, percent_d, *statValue);
                    TEXT_CONTROL(self, STWINFONT22, statRow->value, statText, TEXTSET);
                }
                beMessenger_SendNamed(self->_messenger, DATABASE_11, shinka_5, 0, GETDATABASE_10);
                explanation = beDataBase_GetRecordString(beMessenger_GetObject(self->_messenger, 0), selection->_id, EXPLANATION_2);
                TEXT_CONTROL(self, STWINFONT29, g_fontNames[0], explanation, TEXTSET);
                TEXT_CONTROL(self, STWINFONT29, g_fontNames[0], DISPON, SWITCH_2);
            }
        }
    }
}

/* Evolves the player's Digimon into the evolution under the cursor: keeps the current stats as the
 * base, switches the model to the evolution's MODEL_NAME, re-equips the strongest weapons, empties
 * the four item slot lists and refreshes the status windows. */
void beNDMWShopCtrlEvolve_ApplyEvolution(beNDMWShopCtrlEvolve *self) {
    int player;
    int shinkaDataBase;
    beNDMWShinkaObject *evolution;

    player = GetPlayer(self);
    evolution = EVOLUTION_AT(EvolutionList(self), self->_cursor + self->_nowPage * EVOLVE_PAGE_ROWS);
    beMessenger_SendNamed(self->_messenger, DATABASE_11, shinka_5, 0, GETDATABASE_10);
    shinkaDataBase = beMessenger_GetObject(self->_messenger, 0);
    SEND_PLAYER_MESSAGE(self, GAMERAM_14, CURRENT2BASE_2);
    beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    AppendRecordString(self->_messenger, shinkaDataBase, evolution->_id, MODEL_NAME_2);
    beMessenger_DispatchSelected(self->_messenger, BASE2CURRENT_2);
    beMessenger_SelectReceivers(self->_messenger, GAMERAM_14, 0, 0);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_5);
    SEND_PLAYER_MESSAGE(self, GAMERAM_14, GETPLAYER_10);
    SEND_PLAYER_MESSAGE(self, GAMERAM_14, WEAPONEQUIPSTRONG);
    beNDMWShopCtrlEvolve_ClearItemSlots(self, PlayerFolder(player, MAINSLOT_4));
    beNDMWShopCtrlEvolve_ClearItemSlots(self, PlayerFolder(player, SUBSLOT_4));
    beNDMWShopCtrlEvolve_ClearItemSlots(self, PlayerFolder(player, POWERPOCKET_4));
    beNDMWShopCtrlEvolve_ClearItemSlots(self, PlayerFolder(player, MAINPOCKET_4));
    beMessenger_SelectReceivers(self->_messenger, GAMERAM_14, 0, 0);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_5);
    SEND_PLAYER_MESSAGE(self, SUBWND_8, UPDATE_3);
    beNDMWShopCtrlDigilabo_ShowPlayerTitle((beNDMWWindow *)self->_mother, self->_playerNo, 1);
}

/* Unequips every item of an item slot list, drops the list's reference to it and empties the slot.
 * The entry test sits after the loop, as in the retail block order. */
void beNDMWShopCtrlEvolve_ClearItemSlots(beNDMWShopCtrlEvolve *self, igObjectList *slots) {
    int i;
    beNDMWItemBase *item;
    beNDMWItemBase *held;
    i = 0;
    goto check_first;
clear_slot:
    item = ((beNDMWItemBase **)slots->_data)[i];
    if (item != 0) item->_isEquip = 0;
    held = ((beNDMWItemBase **)slots->_data)[i];
    IG_OBJECT_RELEASE(held);
    if (slots->_count != 0 && i >= 0 && i < slots->_count) ((beNDMWItemBase **)slots->_data)[i] = 0;
    i++;
check_next:
    if (i < slots->_count) goto clear_slot;
done:
    return;
check_first:
    if (0 < slots->_count) goto check_next;
    goto done;
}


#define PLAYER_COUNT(self) (((igIntList *)(self)->_playerNoList)->_count)
#define PLAYER_NO(self, index) (((int *)((igIntList *)(self)->_playerNoList)->_data)[index])

/* Creates a child window of `Type` for this window's player and adds it to the sub-windows. */
#define OPEN_CHILD(Type, entCode) { \
    void *allocator; \
    PICK_ALLOCATOR(allocator, self) \
    igSmartPointer<Type> child((Type *)Type##_Create(allocator)); \
    beNDMWWindow_BindContext(child.p, self, self->_insight, self->_playerNo, entCode); \
    ObjectList_AppendRetained((igObjectList *)self->_subWindow, child.p); }
/* Remembers the child count and moves on to the phase that waits for the child to close. */
#define AWAIT_CHILD(window) { (window)->_nowProcKazu = CHILD_COUNT(window); NEXT_PHASE(window) }
#define CHILD_CLOSED(window) (CHILD_COUNT(window) != (window)->_nowProcKazu)

enum DigilaboStep { LABO_MENU, LABO_EVOLVE, LABO_EQUIP, LABO_OFFER_EQUIP, LABO_SWITCH_PLAYER = 5, LABO_LEAVE };
enum DigilaboChoice { LABO_CHOICE_EVOLVE, LABO_CHOICE_EQUIP, LABO_CHOICE_SWITCH_PLAYER, LABO_CHOICE_LEAVE };
enum { EVOLVE_DONE = 1, EQUIP_CHANGED = 100 };

enum { NO_WEAPON = -1 };

static inline void IntList_Set(igIntList *list, int index, const int &value)
{
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((int *)list->_data)[index] = value;
    }
}

/* Queues a text that the window switches off when it closes. */
#define QUEUE_TEXT_CLOSE(window, type, name) \
    StringList_AppendRetained((window)->_textCloseTypeList, StringRef(InternString((const char *)(type)))); \
    StringList_AppendRetained((window)->_textCloseNameList, StringRef(InternString((const char *)(name))));

enum EditBitMode { EDITBIT_DEPOSIT, EDITBIT_WITHDRAW, EDITBIT_JUNK };
enum EditBitPhase {
    EDITBIT_OPEN_INPUT, EDITBIT_SHOW_AMOUNTS, EDITBIT_EDIT, EDITBIT_OPEN_CONFIRM, EDITBIT_AWAIT_CONFIRM,
    EDITBIT_OPEN_JUNK_NOTICE, EDITBIT_AWAIT_JUNK_NOTICE
};
enum { BIT_DIGITS = 7, MAX_BANK_BIT = 9999999, MAX_JUNK_BIT = 999999999 };
enum { STICK_UP = 0x1, STICK_DOWN = 0x4, PAD_UP = 0x10, PAD_DOWN = 0x40 };

/* The window's phase read afresh, as CurrentState does for _st0. */
static inline int CurrentPhase(const beNDMWShopCtrlEditBit *self) { return self->_st2; }

void beNDMWShopCtrlDigilabo_Update(beNDMWShopCtrlDigilabo *self) {
    beNDMWStatusTitle01 *title;
    int p;
    int j;
    int index;
    int *playerNo;
    igIntList *choices;

    switch (self->_st0) {
    default:
        return;
    case SHOP_STATE_OPEN:
        self->_isDigimonChange = 0;
        self->_isWeaponChange = 0;
        beNDMWShopCtrlDigilabo_SnapshotParty(self);
        OPEN_CHILD(beNDMWShopTitle00, 0)
        OPEN_CHILD(beNDMWStatusTitle03, 0)
        OPEN_CHILD(beNDMWShopTitle01, self->_entCode)
        NEXT_STATE(self)
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case LABO_MENU:
            switch (self->_st2) {
            case 0:
                beNDMWShopCtrlDigilabo_PresentMessageWindow(self);
                beNDMWShopCtrlDigilabo_ShowPlayerTitle((beNDMWWindow *)self, self->_playerNo, 0);
                NEXT_PHASE(self)
                return;
            case 1:
                beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, i_messwn_3, 0);
                beMessenger_AppendString(self->_messenger, SQ_OPEN_8);
                beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
                if (((unsigned char)beMessenger_GetBool(self->_messenger, 0)) != 1) {
                    OPEN_CHILD(beNDMWShopSelect02, PLAYER_COUNT(self))
                    AWAIT_CHILD(self)
                }
                break;
            case 2:
                if (CHILD_CLOSED(self)) {
                    switch (self->_retCode) {
                    case LABO_CHOICE_EVOLVE:
                        ENTER_STEP(self, LABO_EVOLVE)
                        break;
                    case LABO_CHOICE_EQUIP:
                        ENTER_STEP(self, LABO_EQUIP)
                        break;
                    case LABO_CHOICE_SWITCH_PLAYER:
                        if (PLAYER_COUNT(self) == 1) {
                            ENTER_STEP(self, LABO_LEAVE)
                        } else {
                            ENTER_STEP(self, LABO_SWITCH_PLAYER)
                        }
                        break;
                    default:
                    case LABO_CHOICE_LEAVE:
                        ENTER_STEP(self, LABO_LEAVE)
                        break;
                    }
                    self->_topMenu = self->_retCode;
                    return;
                }
                break;
            }
            break;
        case LABO_EVOLVE:
            switch (self->_st2) {
            case 0:
                OPEN_CHILD(beNDMWShopCtrlEvolve, 0)
                AWAIT_CHILD(self)
            case 1:
                if (CHILD_CLOSED(self)) {
                    switch (self->_retCode) {
                    case EVOLVE_DONE:
                        self->_isDigimonChange = 1;
                        ENTER_STEP(self, LABO_OFFER_EQUIP)
                        break;
                    default:
                        ENTER_STEP(self, LABO_MENU)
                        break;
                    }
                    beNDMWShopCtrlDigilabo_PresentMessageWindow(self);
                    return;
                }
                break;
            }
            break;
        case LABO_EQUIP:
            switch (self->_st2) {
            case 0:
                FIND_CHILD(title, self, AsPlayerTitle)
                if (title != 0) {
                    title->_playerNo = self->_playerNo;
                    beNDMWStatusTitle01_ShowStatusLayout(title);
                }
                NEXT_PHASE(self)
                return;
            case 1:
                {
                    void *allocator;
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<beNDMWStatusCtrlEquip> equip((beNDMWStatusCtrlEquip *)beNDMWStatusCtrlEquip_Create(allocator));
                    beNDMWWindow_BindContext(equip.p, self, self->_insight, self->_playerNo, 1);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, equip.p);
                    beNDMWWindow_PresentModelAtOrigin(equip.p, i_messwn_3, 0, SQ_STOPEN_3, SQ_STCLOSE_2);
                }
                AWAIT_CHILD(self)
            case 2:
                if (CHILD_CLOSED(self)) {
                    switch (self->_retCode) {
                    case EQUIP_CHANGED:
                        self->_isWeaponChange = 1;
                        break;
                    }
                    ENTER_STEP(self, LABO_MENU)
                    beNDMWShopCtrlDigilabo_PresentMessageWindow(self);
                    return;
                }
                break;
            }
            break;
        case LABO_OFFER_EQUIP:
            switch (self->_st2) {
            case 0:
                beMessenger_SelectReceivers(self->_messenger, MODELCTRL_16, i_messwn_3, 0);
                beMessenger_AppendString(self->_messenger, SQ_OPEN_8);
                beMessenger_DispatchSelected(self->_messenger, ISSEQNAME_6);
                if (((unsigned char)beMessenger_GetBool(self->_messenger, 0)) == 1) break;
                OPEN_CHILD(beNDMWShopSelect03, 0x4ED)
                AWAIT_CHILD(self)
            case 1:
                if (!CHILD_CLOSED(self)) break;
                OPEN_CHILD(beNDMWShopSelect02, 0x4EE)
                AWAIT_CHILD(self)
            case 2:
                if (!CHILD_CLOSED(self)) break;
                switch (self->_retCode) {
                case 0:
                    ENTER_STEP(self, LABO_EQUIP)
                    return;
                default:
                    ENTER_STEP(self, LABO_MENU)
                    return;
                }
                break;
            }
            break;
        case LABO_SWITCH_PLAYER:
            switch (self->_st2) {
            case 0:
                if (1 < PLAYER_COUNT(self)) {
                    OPEN_CHILD(beNDMWShopSelect03, 0x4E2)
                    AWAIT_CHILD(self)
                    return;
                }
                ENTER_STEP(self, LABO_MENU)
                return;
            case 1:
                if (!CHILD_CLOSED(self)) break;
                {
                    void *allocator;
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<beNDMWShopSelect02> chooser((beNDMWShopSelect02 *)beNDMWShopSelect02_Create(allocator));
                    beNDMWWindow_BindContext(chooser.p, self, self->_insight, self->_playerNo, -1);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, chooser.p);
                    for (j = 0; j < PLAYER_COUNT(self); j++) {
                        playerNo = &PLAYER_NO(self, j);
                        choices = (igIntList *)chooser.p->_playerNoList;
                        index = choices->_count;
                        if (index < choices->_capacity) {
                            choices->_count = countOf(choices) + 1;
                        } else {
                            List_Resize(choices, index + 1, 4);
                        }
                        ((int *)choices->_data)[index] = *playerNo;
                    }
                }                AWAIT_CHILD(self)
            case 2:
                if (CHILD_CLOSED(self)) {
                    switch (self->_retCode) {
                    default:
                        self->_playerNo = PLAYER_NO(self, self->_retCode);
                        ENTER_STEP(self, LABO_MENU)
                        return;
                    case -1:
                        ENTER_STEP(self, LABO_MENU)
                        return;
                    }
                }
                break;
            }
            break;
        case LABO_LEAVE:
            switch (self->_st2) {
            case 0:
                if (beNDMWShopCtrlDigilabo_HasPartyChanged(self) != 0) {
                    ENTER_PHASE(self, 2)
                    return;
                }
                OPEN_CHILD(beNDMWShopSelect03, 0x4FB)
                AWAIT_CHILD(self)
                beNDMWShopCtrlDigilabo_RecalcPlayers(self);
                p = 0;
                if (0 < PLAYER_COUNT(self)) {
                    do {
                        beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
                        beMessenger_AppendInt(self->_messenger, PLAYER_NO(self, p));
                        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
                        igStringRefList *socketNames = (igStringRefList *)igProperty_GetRecordStringList(beMessenger_GetObject(self->_messenger, 0), POWERSOCKETNAME_5)->_data;
                        beMessenger_SendNamed(self->_messenger, PLAYERARMS_4, StringList_CopyRetained(socketNames, 0).p, PLAYER_NO(self, p), GENERATE_13);
                        p += 1;
                    } while (p < PLAYER_COUNT(self));
                }
                break;
            case 1:
                if (CHILD_CLOSED(self)) {
                    NEXT_STATE(self)
                }
                break;
            case 2:
                OPEN_CHILD(beNDMWShopSelect03, 0x4F3)
                AWAIT_CHILD(self)
            case 3:
                if (!CHILD_CLOSED(self)) break;
                OPEN_CHILD(beNDMWShopSelect02, 0x4F4)
                AWAIT_CHILD(self)
            case 4:
                if (CHILD_CLOSED(self)) {
                    switch (self->_retCode) {
                    case 0:
                        NEXT_PHASE(self)
                        ((beSystem *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]))->_isSResetEnable = 0;
                        break;
                    default:
                        ENTER_STEP(self, LABO_SWITCH_PLAYER)
                        break;
                    }
                }
                break;
            case 5:
                beNDMWShopCtrlDigilabo_RecalcPlayers(self);
                self->_isDemoRun = 1;
                NEXT_STATE(self)
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beMessenger_SendNamed(self->_messenger, MODELCTRL_16, i_bgclear_2, 0, OFFREEZE_3);
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        if (self->_isDemoRun != 0) {
            beLua__RunNamedChunk(igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]), demo_digilab_lua, stagML12_lua);
            return;
        }
        break;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}



/* Remembers every active player's digimon and the weapons in its power sockets, so that leaving
 * the lab can tell whether anything changed. */
void beNDMWShopCtrlDigilabo_SnapshotParty(beNDMWShopCtrlDigilabo *self) {
    int playerNo;
    int player;
    void *allocator;
    igObjectList *sockets;
    int i;
    int digimonNo;
    int weaponNo;

    beMessenger_SendGroup(self->_messenger, GAMERAM_14, GETCOMMON_10);
    igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), NINZU_5);
    playerNo = 0;
    do {
        beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
        beMessenger_AppendInt(self->_messenger, playerNo);
        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
        player = beMessenger_GetObject(self->_messenger, 0);
        if (igProperty_GetRecordByte(player, ISUSE_9)->_data != 0) {
            IntList_Append(self->_playerNoList, playerNo);
            digimonNo = igProperty_GetRecord(player, DIGIMONNO_6)->_data;
            IntList_Append(self->_digimonNoList, digimonNo);
            sockets = (igObjectList *)igProperty_GetRecordFolder(player, POWERSOCKET_4)->_data;
            PICK_ALLOCATOR(allocator, self)
            igSmartPointer<igIntList> weaponNos((igIntList *)igIntList_Create(allocator));
            for (i = 0; i < sockets->_count; i++) {
                beNDMWItemBase *weapon = ((beNDMWItemBase **)sockets->_data)[i];
                if (weapon != 0) {
                    weaponNo = weapon->_recNo;
                    IntList_Append(weaponNos.p, weaponNo);
                }
            }
            ObjectList_AppendRetained((igObjectList *)self->_wpuNoListList, weaponNos.p);
        }
        playerNo += 1;
    } while (playerNo < MAX_PLAYERS);
}

void beNDMWShopCtrlDigilabo_RecalcPlayers(beNDMWShopCtrlDigilabo *self) {
    int i;
    for (i = 0; i < PLAYER_COUNT(self); i++) {
        beMessenger_SelectReceivers(self->_messenger, GAMERAM_14, 0, 0);
        beMessenger_AppendInt(self->_messenger, PLAYER_NO(self, i));
        beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_5);
    }
}

/* Whether the party differs from the snapshot taken on entry: another digimon, or another set of
 * power-socket weapons. Only checked after an evolution or an equipment change was confirmed. */
int beNDMWShopCtrlDigilabo_HasPartyChanged(beNDMWShopCtrlDigilabo *self) {
    int p;
    int player;
    igObjectList *sockets;
    igIntList *savedWeaponNos;
    void *allocator;
    int weaponCount;
    int i;
    int s;
    int k;
    int m;
    int weaponNo;

    if (self->_isDigimonChange != 0 || self->_isWeaponChange != 0) {
        for (p = 0; p < PLAYER_COUNT(self); p++) {
            int playerNo = PLAYER_NO(self, p);
            beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
            beMessenger_AppendInt(self->_messenger, playerNo);
            beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
            player = beMessenger_GetObject(self->_messenger, 0);
            beDataObjInt *digimon = igProperty_GetRecord(player, DIGIMONNO_6);
            if (digimon->_data != ((int *)((igIntList *)self->_digimonNoList)->_data)[p]) return 1;
            sockets = (igObjectList *)igProperty_GetRecordFolder(player, POWERSOCKET_4)->_data;
            savedWeaponNos = ((igIntList **)((igObjectList *)self->_wpuNoListList)->_data)[p];
            PICK_ALLOCATOR(allocator, self)
            igSmartPointer<igIntList> unmatched((igIntList *)igIntList_Create(allocator));
            for (i = 0; i < savedWeaponNos->_count; i++) {
                IntList_Append(unmatched.p, IntList_Get(savedWeaponNos, i));
            }
            /* Strike every equipped weapon off the saved list. */
            weaponCount = 0;
            for (s = 0; s < sockets->_count; s++) {
                beNDMWItemBase *weapon = ((beNDMWItemBase **)sockets->_data)[s];
                if (weapon != 0) {
                    weaponNo = weapon->_recNo;
                    weaponCount++;
                    for (k = 0; k < countOf(unmatched); k++) {
                        int saved = IntList_Get(unmatched, k);
                        if (saved != NO_WEAPON && weaponNo == saved) {
                            IntList_Set(unmatched, k, NO_WEAPON);
                            break;
                        }
                    }
                }
            }
            if (weaponCount != savedWeaponNos->_count) return 1;
            for (m = 0; m < countOf(unmatched); m++) {
                if (IntList_Get(unmatched, m) != NO_WEAPON) return 1;
            }
        }
    }
    return 0;
}


void beNDMWShopCtrlDigilabo_ShowPlayerTitle(beNDMWWindow *self, int playerNo, int unused) {
    beNDMWStatusTitle01 *title;

    FIND_CHILD(title, self, AsPlayerTitle)
    if (title == 0) {
        void *allocator;
        PICK_ALLOCATOR(allocator, self)
        igSmartPointer<beNDMWStatusTitle01> created((beNDMWStatusTitle01 *)beNDMWStatusTitle01_Create(allocator));
        beNDMWWindow_BindContext(created.p, self, self->_insight, playerNo, 1);
        ObjectList_AppendRetained((igObjectList *)self->_subWindow, created.p);
    } else {
        title->_playerNo = playerNo;
        beNDMWStatusTitle01_ShowShopLayout(title);
    }
}

void beNDMWShopCtrlDigilabo_PresentMessageWindow(void *window)
{
    beNDMWWindow_PresentModelAtOrigin(window, i_messwn_3, 0, SQ_OPEN_8, SQ_CLOSE_10);
}

void beNDMWShopCtrlEditBit_Update(beNDMWShopCtrlEditBit *self) {
    char slotName[20];
    int player;
    beNDMWShopCtrlEditBit *input;
    int carried;
    int banked;
    int i;
    int step;
    int stick;
    bePadData *pad;
    int pressed;
    int repeated;
    int previous;
    int room;
    int digits;
    int column;

    switch (self->_st0) {
    default:
        return;
    case SHOP_STATE_OPEN:
        switch (self->_entCode) {
        case EDITBIT_DEPOSIT:
            beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_BITPUTINOPEN, SQ_CLOSE_10);
            QUEUE_TEXT_CLOSE(self, STWINFONT36, font000_5)
            QUEUE_TEXT_CLOSE(self, STWINFONT36, font001_5)
            beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x515);
            QUEUE_TEXT_CLOSE(self, STWINFONT29, font100_3)
            beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x550);
            break;
        case EDITBIT_WITHDRAW:
            beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_BITDRAWOUTOPEN, SQ_CLOSE_10);
            QUEUE_TEXT_CLOSE(self, STWINFONT36, font000_5)
            QUEUE_TEXT_CLOSE(self, STWINFONT36, font001_5)
            QUEUE_TEXT_CLOSE(self, STWINFONT36, font002_4)
            beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x55F);
            QUEUE_TEXT_CLOSE(self, STWINFONT29, font100_3)
            beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x557);
            break;
        case EDITBIT_JUNK:
            beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_JUNKOPEN, SQ_CLOSE_10);
            QUEUE_TEXT_CLOSE(self, STWINFONT36, font000_5)
            beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x562);
            break;
        }
        NEXT_STATE(self)
    case SHOP_STATE_RUN:
        switch (self->_st2) {
        case EDITBIT_OPEN_INPUT:
            OPEN_CHILD(beNDMWShopSelect34, self->_entCode)
            AWAIT_CHILD(self)
            return;
        case EDITBIT_SHOW_AMOUNTS:
            beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
            beMessenger_AppendInt(self->_messenger, self->_playerNo);
            beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
            player = beMessenger_GetObject(self->_messenger, 0);
            self->_editBit = 0;
            input = ((beNDMWShopCtrlEditBit **)((igObjectList *)self->_subWindow)->_data)[0];
            carried = igProperty_GetRecord(player, BIT_7)->_data;
            banked = igProperty_GetRecord(player, BANKBIT_2)->_data;
            switch (self->_entCode) {
            case EDITBIT_DEPOSIT:
                beNDMWWindow_ShowPaddedDigits(input, self->_editBit, 1, font_03d_2);
                room = MAX_BANK_BIT - banked;
                carried = carried < room ? carried : room;
                self->_editMax = carried;
                beNDMWShopCtrlEditBit_ShowValueDigits(input, self->_entCode, banked);
                break;
            case EDITBIT_WITHDRAW:
                beNDMWWindow_ShowPaddedDigits(input, self->_editBit, 1, font01_d);
                room = MAX_BANK_BIT - carried;
                self->_editMax = banked < room ? banked : room;
                beNDMWShopCtrlEditBit_ShowValueDigits(input, self->_entCode, carried);
                beNDMWWindow_ShowPaddedDigits(input, banked, 1, font02_d);
                break;
            case EDITBIT_JUNK:
                beNDMWWindow_ShowPaddedDigits(input, self->_editBit, 1, font_03d_2);
                room = MAX_JUNK_BIT - carried;
                carried = carried < room ? carried : room;
                self->_editMax = carried;
                break;
            }
            NEXT_PHASE(self)
            return;
        case EDITBIT_EDIT:
            if (CHILD_COUNT(self) == self->_nowProcKazu) {
                column = self->_retCode;
                if (column != -1) {
                    if (self->_st3 == column) {
                        beMessenger_SendNamed(self->_messenger, SELECTCTRL_4, i_stcursor03_2, self->_playerNo, ISSELECTNOW_2);
                        if (beMessenger_GetBool(self->_messenger, 0) & 0xFF) {
                            pad = bePadManager_GetPadForPlayer(self->_padManager, self->_playerNo);
                            pressed = pad->_trigger;
                            repeated = pad->_repeat;
                            stick = pad->_lTrg | pad->_lRpt;
                            bool up = (stick & STICK_UP) || ((pressed | repeated) & PAD_UP);
                            bool down = (stick & STICK_DOWN) || ((pressed | repeated) & PAD_DOWN);
                            if (up || down) {
                                previous = self->_editBit;
                                step = 1;
                                digits = BIT_DIGITS - self->_retCode;
                                for (i = digits; i > 1; i--) step *= 10;
                                if (up) {
                                    self->_editBit = self->_editBit + step;
                                    if (self->_editBit >= self->_editMax) self->_editBit = self->_editMax;
                                } else if (down) {
                                    self->_editBit = self->_editBit - step;
                                    if (self->_editBit <= 0) self->_editBit = 0;
                                }
                                if (self->_editBit != previous) {
                                    input = ((beNDMWShopCtrlEditBit **)((igObjectList *)self->_subWindow)->_data)[0];
                                    switch (self->_entCode) {
                                    case EDITBIT_JUNK:
                                    case EDITBIT_DEPOSIT:
                                        beNDMWWindow_ShowPaddedDigits(input, self->_editBit, digits, font_03d_2);
                                        break;
                                    case EDITBIT_WITHDRAW:
                                        beNDMWWindow_ShowPaddedDigits(input, self->_editBit, digits, font01_d);
                                        break;
                                    }
                                    beMessenger_SelectGroup(self->_messenger, SOUND_8);
                                    beMessenger_AppendString(self->_messenger, CURSOR_MOVE_3);
                                    beMessenger_DispatchSelected(self->_messenger, PLAY_6);
                                    return;
                                }
                            }
                        }
                    } else {
                        input = ((beNDMWShopCtrlEditBit **)((igObjectList *)self->_subWindow)->_data)[0];
                        digits = BIT_DIGITS - column;
                        switch (self->_entCode) {
                        case EDITBIT_JUNK:
                        case EDITBIT_DEPOSIT:
                            beNDMWWindow_ShowPaddedDigits(input, self->_editBit, digits, font_03d_2);
                            break;
                        case EDITBIT_WITHDRAW:
                            beNDMWWindow_ShowPaddedDigits(input, self->_editBit, digits, font01_d);
                            break;
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                }
            } else {
                if (self->_retCode == -1 || self->_editBit <= 0) {
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    NEXT_STATE(self)
                    return;
                } else {
                    ((beNDMWWindow *)self->_mother)->_retCode = self->_editBit;
                    NEXT_PHASE(self)
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, font100_3);
                    beMessenger_AppendString(self->_messenger, DISPOFF);
                    beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
                    return;
                }
            }
            break;
        case EDITBIT_OPEN_CONFIRM:
            {
                void *allocator;
                PICK_ALLOCATOR(allocator, self)
                igSmartPointer<beNDMWShopSelect00> confirm((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                beNDMWWindow_BindContext(confirm.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, confirm.p);
                switch (self->_entCode) {
                case EDITBIT_DEPOSIT:
                    confirm.p->_entCode = 0x552;
                    break;
                case EDITBIT_WITHDRAW:
                    confirm.p->_entCode = 0x559;
                    break;
                case EDITBIT_JUNK:
                    confirm.p->_entCode = 0x7A9;
                    break;
                }
            }
            AWAIT_CHILD(self)
            return;
        case EDITBIT_AWAIT_CONFIRM:
            if (CHILD_CLOSED(self)) {
                if (self->_entCode == EDITBIT_JUNK) {
                    self->_st2 = CurrentPhase(self) + 1;
                    self->_st3 = 0;
                    return;
                }
                NEXT_STATE(self)
                return;
            }
            break;
        case EDITBIT_OPEN_JUNK_NOTICE:
            OPEN_CHILD(beNDMWShopSelect01, 0x7AA)
            AWAIT_CHILD(self)
            return;
        case EDITBIT_AWAIT_JUNK_NOTICE:
            if (CHILD_CLOSED(self)) {
                if (self->_retCode != 0) {
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                }
                NEXT_STATE(self)
                return;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        i = 0;
        NEXT_STATE(self)
        do {
            sprintf(slotName, font_03d_2, i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT25);
            beMessenger_AppendString(self->_messenger, slotName);
            beMessenger_AppendString(self->_messenger, DISPOFF);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            sprintf(slotName, font01_d, i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT25);
            beMessenger_AppendString(self->_messenger, slotName);
            beMessenger_AppendString(self->_messenger, DISPOFF);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            sprintf(slotName, font02_d, i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT25);
            beMessenger_AppendString(self->_messenger, slotName);
            beMessenger_AppendString(self->_messenger, DISPOFF);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            i += 1;
        } while (i < BIT_DIGITS);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Retain `list` and store it in the window's `_decideList`, releasing the previous one. */
#define SET_DECIDE_LIST(window, list) { \
    igBoolList *retained = (igBoolList *)(list); \
    beNDMWWindowSelect *target = (beNDMWWindowSelect *)(window); \
    if (retained != 0) retained->_refCount = retained->_refCount + 1; \
    { igObject *previous = (igObject *)target->_decideList; RELEASE(previous) } \
    target->_decideList = (int)retained; }

/* The rows a sell list shows per page. */
enum { SELL_PAGE_ROWS = 12 };
/* Money is capped at this amount. */
enum { MONEY_MAX = 9999999 };

/* beNDMWShopCtrlSell's steps (_st1) while running. */
enum SellStep { SELL_STEP_CHOOSE = 0, SELL_STEP_DEVICES = 1, SELL_STEP_DISKS = 2, SELL_STEP_NOTHING = 3 };
/* beNDMWShopCtrlSell's _st3 in SELL_STEP_CHOOSE: which choice to grey out. */
enum SellChoiceLimit { SELL_CHOICE_ALL = 0, SELL_CHOICE_NO_DEVICES = 1, SELL_CHOICE_NO_DISKS = 2 };

/* beNDMWShopCtrlDeviceSell's steps (_st1) while running. */
enum DeviceSellStep { DEVICESELL_STEP_LIST = 4, DEVICESELL_STEP_CONFIRM = 5 };

/* The object list held by the player's folder record `name` (DEVICEFOLDER, DISKFOLDER). */
#define PlayerFolder(player, name) ((igObjectList *)igProperty_GetRecordFolder(player, name)->_data)

void beNDMWShopCtrlSell_Update(beNDMWShopCtrlSell *self) {
    void *allocator;
    igObjectList *devices;
    const igObjectList *disks;
    beNDMWItemDisk *disk;
    bool hasDevice;
    bool hasDisk;
    int i;
    int player;

    switch (CurrentState(self)) {
    case SHOP_STATE_OPEN:
        NEXT_STATE(self)
        beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
        player = beMessenger_GetObject(self->_messenger, 0);
        devices = PlayerFolder(player, DEVICEFOLDER_4);
        disks = PlayerFolder(player, DISKFOLDER_5);
        hasDevice = false;
        if (devices->_count > 0) {
            hasDevice = true;
        }
        hasDisk = false;
        for (i = 0; i < disks->_count; i++) {
            disk = ((beNDMWItemDisk **)disks->_data)[i];
            if (disk != 0 && DiskCount(disk) > 0) {
                hasDisk = true;
                break;
            }
        }
        if (hasDevice || hasDisk) {
            ENTER_STEP(self, SELL_STEP_CHOOSE)
            if (hasDevice == 0) {
                self->_st3 = SELL_CHOICE_NO_DEVICES;
            } else if (hasDisk == 0) {
                self->_st3 = SELL_CHOICE_NO_DISKS;
            }
        } else {
            ENTER_STEP(self, SELL_STEP_NOTHING)
        }
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case SELL_STEP_CHOOSE:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                igSmartPointer<beNDMWShopSelectB0> choice((beNDMWShopSelectB0 *)beNDMWShopSelectB0_Create(allocator));
                beNDMWWindow_BindContext(choice.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, choice.p);
                switch (self->_st3) {
                case SELL_CHOICE_NO_DEVICES: {
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<igBoolList> enabled((igBoolList *)igBoolList_Create(allocator));
                    BoolList_Append(enabled.p, false);
                    BoolList_Append(enabled.p, true);
                    SET_DECIDE_LIST(choice.p, enabled.p)
                    break;
                }
                case SELL_CHOICE_NO_DISKS: {
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<igBoolList> enabled((igBoolList *)igBoolList_Create(allocator));
                    BoolList_Append(enabled.p, true);
                    BoolList_Append(enabled.p, false);
                    SET_DECIDE_LIST(choice.p, enabled.p)
                    break;
                }
                }
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, g_fontNames[0]);
                    beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, g_fontName1[0]);
                    beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
                    switch (self->_retCode) {
                    case 0:
                        ENTER_STEP(self, SELL_STEP_DEVICES)
                        return;
                    case 1:
                        ENTER_STEP(self, SELL_STEP_DISKS)
                        return;
                    default:
                        NEXT_STATE(self)
                        return;
                    }
                }
                break;
            }
            break;
        case SELL_STEP_DEVICES:
        case SELL_STEP_DISKS:
            switch (self->_st2) {
            case 0:
                if (self->_st1 == SELL_STEP_DEVICES) {
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<beNDMWShopCtrlDeviceSell> list((beNDMWShopCtrlDeviceSell *)beNDMWShopCtrlDeviceSell_Create(allocator));
                    beNDMWWindow_BindContext(list.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, list.p);
                } else {
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<beNDMWShopCtrlDiskSell> list((beNDMWShopCtrlDiskSell *)beNDMWShopCtrlDiskSell_Create(allocator));
                    beNDMWWindow_BindContext(list.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, list.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    ENTER_STATE(self, SHOP_STATE_OPEN)
                    return;
                }
                break;
            }
            break;
        case SELL_STEP_NOTHING:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                igSmartPointer<beNDMWShopSelect00> notice((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                beNDMWWindow_BindContext(notice.p, self, self->_insight, self->_playerNo, 0x628);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, notice.p);
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    NEXT_STATE(self)
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

void beNDMWShopCtrlSell_MoveRowCursor(beNDMWWindow *window, int row) {
    RowCursorSequences rowSequences;
    float position[3];
    if (row > -1) {
        rowSequences = g_sellCursorOpenSequences;
        beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, ISRUN_10);
        if (beMessenger_GetBool(window->_messenger, 0) != 0) {
            beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, rowSequences.row[row]);
            return;
        }
        beMessenger_SelectReceivers(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0);
        beMessenger_AppendString(window->_messenger, rowSequences.row[row]);
        position[2] = 0;
        position[0] = -121.0f;
        position[1] = 128.0f;
        beMessenger_AppendVec3(window->_messenger, position);
        beMessenger_DispatchSelected(window->_messenger, GENERATE_13);
        return;
    }
    beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, ISRUN_10);
    if (beMessenger_GetBool(window->_messenger, 0) != 0) {
        beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, SQ_CLOSE_10);
    }
}

void beNDMWShopCtrlDeviceSell_Update(beNDMWShopCtrlDeviceSell *self)
{
    switch (self->_st0) {
    case SHOP_STATE_OPEN: {
        float leftArrowPos[3];
        float rightArrowPos[3];
        int row;
        beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_AWINOPEN, SQ_CLOSE_10);
        beNDMWShopCtrlDeviceSell_UpdatePageCount(self);
        rightArrowPos[0] = 236.0f;
        rightArrowPos[2] = 0.0f;
        rightArrowPos[1] = 25.0f;
        leftArrowPos[0] = -146.0f;
        leftArrowPos[1] = 25.0f;
        leftArrowPos[2] = 0.0f;
        ((PagedWindow *)self)->PresentPageArrows(leftArrowPos, rightArrowPos);
        APPEND_INTERNED(self->_textCloseTypeList, STWINFONT29)
        APPEND_INTERNED(self->_textCloseNameList, font100_3)
        beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x676);
        APPEND_INTERNED(self->_textCloseTypeList, STWINFONT13_2)
        APPEND_INTERNED(self->_textCloseNameList, g_fontNames[0])
        beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 0x3E8);
        row = 0;
        {
            const char **rowFont = g_fontNames;
            do {
                beNDMWWindow_QueueText(self, STWINFONT14, *rowFont, space_2, LEFT_4);
                beNDMWWindow_QueueText(self, STWINFONT17, *rowFont, space_2, RIGHT_3);
                row++;
                rowFont++;
            } while (row < SELL_PAGE_ROWS);
        }
        beNDMWWindow_QueueText(self, STWINFONT30, g_fontNames[0], space_2, RIGHT_3);
        beNDMWWindow_QueueText(self, STWINFONT30, g_fontName1[0], space_2, RIGHT_3);
        self->_cursor = 0;
        self->_nowPage = 0;
        NEXT_STATE(self)
        ENTER_STEP(self, DEVICESELL_STEP_LIST)
    }
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case DEVICESELL_STEP_LIST:
            switch (self->_st2) {
            case 0: {
                void *allocator;
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWStatusSelectE1> selectWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(allocator));
                    self->_retCode = self->_cursor;
                    beNDMWWindow_BindContext(selectWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, selectWin.p);
                    {
                        beNDMWStatusSelectE1 *select = selectWin.p;
                        select->_offsetPos[0] = -121.0f;
                        select->_offsetPos[1] = 128.0f;
                        select->_offsetPos[2] = 0.0f;
                    }
                    selectWin.p->_startPoint = self->_cursor;
                    beNDMWWindow_QueueText(selectWin.p, STWINFONT29, g_fontNames[0], space_2, LEFT_4);
                    selectWin.p->_selectMax = beNDMWShopCtrlDeviceSell_UpdatePageCount(self);
                    SET_DECIDE_LIST(selectWin.p, (igBoolList *)self->_decideList)
                }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            }
            case 1:
                beNDMWShopCtrlDeviceSell_RefreshText(self, 1, 1);
                NEXT_PHASE(self)
                return;
            case 2: {
                igObjectList *subWindows = (igObjectList *)self->_subWindow;
                if (subWindows->_count == self->_nowProcKazu) {
                    int selected = self->_retCode;
                    if (selected != -1) {
                        if (selected != self->_st3) {
                            beNDMWShopCtrlDeviceSell_RefreshText(self, 0, 1);
                            self->_st3 = self->_retCode;
                            return;
                        }
                        {
                            beNDMWStatusSelectE1 *selectWin = ((beNDMWStatusSelectE1 **)subWindows->_data)[0];
                            if (beNDMWWindowSelect_CanRequestFO2TOP(selectWin) != 0) {
                                bool pageTurned = false;
                                if (((PagedWindow *)self)->TurnPagePrev() != 0) {
                                    pageTurned = true;
                                } else if (((PagedWindow *)self)->TurnPageNext() != 0) {
                                    pageTurned = true;
                                }
                                if (pageTurned) {
                                    ENTER_STATE(selectWin, 4)
                                    selectWin->_selectMax = beNDMWShopCtrlDeviceSell_UpdatePageCount(self);
                                    SET_DECIDE_LIST(selectWin, (igBoolList *)self->_decideList)
                                    self->_st2 = 1;
                                    self->_st3 = 0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    switch (self->_retCode) {
                    default:
                        ENTER_STEP(self, DEVICESELL_STEP_CONFIRM)
                        self->_cursor = self->_retCode;
                        beNDMWShopCtrlSell_MoveRowCursor((beNDMWWindow *)self->_mother, self->_cursor);
                        return;
                    case -1:
                        ((beNDMWWindow *)self->_mother)->_retCode = -1;
                        NEXT_STATE(self)
                        return;
                    }
                }
                break;
            }
            }
            break;
        case DEVICESELL_STEP_CONFIRM:
            switch (self->_st2) {
            case 0: {
                void *allocator;
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect00> priceWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(priceWin.p, self, self->_insight, self->_playerNo, 0x619);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, priceWin.p);
                }
            }
                self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                NEXT_PHASE(self)
            case 1:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    void *allocator;
                    PICK_ALLOCATOR(allocator, self)
                    {
                        igSmartPointer<beNDMWShopSelect01> yesNoWin((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                        beNDMWWindow_BindContext(yesNoWin.p, self, self->_insight, self->_playerNo, 0x61A);
                        ObjectList_AppendRetained((igObjectList *)self->_subWindow, yesNoWin.p);
                    }
                    self->_nowProcKazu = ObjectList_Count(self->_subWindow);
                    NEXT_PHASE(self)
                    return;
                }
                break;
            case 2:
                if (ObjectList_Count(self->_subWindow) != self->_nowProcKazu) {
                    int answer = self->_retCode;
                    switch (answer) {
                    case 0: {
                        int player;
                        igObjectList *devices;
                        int remaining;
                        int index;
                        int money;
                        int price;
                        beNDMWStatus *status;
                        beNDMWItemBase *device;
                        beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
                        player = beMessenger_GetObject(self->_messenger, 0);
                        devices = PlayerFolder(player, DEVICEFOLDER_4);
                        index = self->_cursor + self->_nowPage * SELL_PAGE_ROWS;
                        if (index < devices->_count) {
                            status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                            device = ((beNDMWItemBase **)devices->_data)[index];
                            price = beNDMWItemRevisionPocketBase_GetPrice(device, status, KAITORI_2);
                            money = igProperty_GetRecord(player, BIT_7)->_data;
                            money = money + price;
                            if (money > MONEY_MAX) money = MONEY_MAX;
                            igProperty_GetRecord(player, BIT_7)->_data = money;
                            ObjectList_RemoveFirstRetained(devices, (void *)device, 0);
                            beMessenger_SelectGroup(self->_messenger, SUBWND_8);
                            beMessenger_AppendInt(self->_messenger, self->_playerNo);
                            beMessenger_DispatchSelected(self->_messenger, UPDATE_3);
                            remaining = devices->_count;
                            if (remaining <= 0) {
                                NEXT_STATE(self)
                            } else {
                                if (index >= remaining) {
                                    if (self->_cursor == 0) {
                                        if (self->_nowPage > 0) self->_nowPage = self->_nowPage - 1;
                                    } else {
                                        self->_cursor = self->_cursor - 1;
                                    }
                                }
                                if (self->_nowPage == 0)
                                    beMessenger_SendNamed(self->_messenger, MODELCTRL_16, i_stcursorleft_2, 0, SQ_HIDE_2);
                                if (devices->_count <= (self->_nowPage + 1) * SELL_PAGE_ROWS)
                                    beMessenger_SendNamed(self->_messenger, MODELCTRL_16, i_stcursorright_2, 0, SQ_HIDE_2);
                            }
                        } else {
                            NEXT_STATE(self)
                        }
                        break;
                    }
                    case 1:
                        break;
                    }
                    ENTER_STEP(self, DEVICESELL_STEP_LIST)
                    beNDMWShopCtrlSell_MoveRowCursor((beNDMWWindow *)self->_mother, -1);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        beNDMWShopCtrlDeviceSell_ResetRowColors(self);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Shows the page's device names, buy-back prices and page numbers (drawRows) and the selected device's description (drawDescription). */
void beNDMWShopCtrlDeviceSell_RefreshText(beNDMWShopCtrlDeviceSell *self, int drawRows, unsigned char drawDescription)
{
    beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
    igObjectList *devices = PlayerFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_4);
    igSmartPointer<igStringObj> text((igStringObj *)((beSystem *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]))->_globalStrObj);
    if (text.p != 0) text.p->_refCount = text.p->_refCount + 1;
    char pageText[2];
    char pocketText[2];
    char chipPocketText[2];
    char priceText[16];
    if (drawRows != 0) {
        int row = 0;
        do {
            int index = row + self->_nowPage * SELL_PAGE_ROWS;
            const char *visibility;
            if (index < devices->_count) {
                beNDMWStatus *status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                beNDMWItemBase *device = ((beNDMWItemBase **)devices->_data)[index];
                igStringObj_Set(text.p, beNDMWItemBase_GetRecordString(device, status, NAME_2));
                if (device->_isEquip != 0) { igStringObj *name = text.p; igStringObj_Insert(name, equippedMark_2, 0, strlen(equippedMark_2)); }
                else { igStringObj *name = text.p; igStringObj_Insert(name, unequippedMark_2, 0, strlen(unequippedMark_2)); }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT14);
                beMessenger_AppendString(self->_messenger, g_fontNames[row]);
                {
                    int messenger = self->_messenger;
                    char *buffer = (char *)text.p->_buffer;
                    beMessenger_AppendString(messenger, buffer == 0 ? g_stringObjEmptyText[0] : buffer);
                }
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                sprintf(priceText, percent_d, beNDMWItemRevisionPocketBase_GetPrice(device, status, KAITORI_2));
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT17);
                beMessenger_AppendString(self->_messenger, g_fontNames[row]);
                beMessenger_AppendString(self->_messenger, priceText);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                igVec3f revisionColor = beNDMWItemBase_GetRevisionColor(device);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT14);
                beMessenger_AppendString(self->_messenger, g_fontNames[row]);
                igVec3f colorArgument(revisionColor);
                beMessenger_AppendVec3(self->_messenger, (float *)&colorArgument);
                beMessenger_DispatchSelected(self->_messenger, COLOR_4);
                if (*(unsigned char *)(((igBoolList *)self->_decideList)->_data + row) != 0) {
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT17);
                    beMessenger_AppendString(self->_messenger, g_fontNames[row]);
                    beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
                } else {
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT17);
                    beMessenger_AppendString(self->_messenger, g_fontNames[row]);
                    beMessenger_DispatchSelected(self->_messenger, CANCELCOLOR_4);
                }
                visibility = DISPON;
            } else {
                visibility = DISPOFF;
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT14);
            beMessenger_AppendString(self->_messenger, g_fontNames[row]);
            beMessenger_AppendString(self->_messenger, visibility);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT17);
            beMessenger_AppendString(self->_messenger, g_fontNames[row]);
            beMessenger_AppendString(self->_messenger, visibility);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            row++;
        } while (row < SELL_PAGE_ROWS);
        pageText[1] = 0;
        pageText[0] = self->_nowPage + '1';
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, STWINFONT30);
        beMessenger_AppendString(self->_messenger, g_fontNames[0]);
        beMessenger_AppendString(self->_messenger, pageText);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET);
        pageText[0] = self->_maxPage + '0';
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, STWINFONT30);
        beMessenger_AppendString(self->_messenger, g_fontName1[0]);
        beMessenger_AppendString(self->_messenger, pageText);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET);
    }
    if (drawDescription) {
        int selected = self->_retCode;
        int pageStart = self->_nowPage * SELL_PAGE_ROWS;
        int index = pageStart + selected;
        const char *visibility;
        if (index < devices->_count) {
            char *description;
            beNDMWStatus *status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
            beNDMWItemBase *device = ((beNDMWItemBase **)devices->_data)[index];
            int kind;
            description = beNDMWItemBase_GetRecordString(device, status, TXT);
            kind = device->_kindNo;
            if (kind == 0) {
                if (device->_recNo != 0x114) {
                    pocketText[1] = 0;
                    pocketText[0] = ((beNDMWItemRevisionPocketBase *)device)->_pocket + '0';
                    igStringObj_Set(text.p, description);
                    {
                        int described = (int)text.p;
                        int length = ((igStringObj *)described)->_length;
                        igStringObj_Insert((igStringObj *)described, pocketText, length, strlen(pocketText));
                    }
                    { char *buffer = (char *)text.p->_buffer; description = (buffer == 0) ? g_stringObjEmptyText[0] : buffer; }
                }
            } else if (kind == 1 && device->_recNo != 0x1f) {
                chipPocketText[1] = 0;
                chipPocketText[0] = ((beNDMWItemRevisionPocketBase *)device)->_pocket + '0';
                igStringObj_Set(text.p, description);
                {
                    int described = (int)text.p;
                    int length = ((igStringObj *)described)->_length;
                    igStringObj_Insert((igStringObj *)described, chipPocketText, length, strlen(chipPocketText));
                }
                { char *buffer = (char *)text.p->_buffer; description = (buffer == 0) ? g_stringObjEmptyText[0] : buffer; }
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT29);
            beMessenger_AppendString(self->_messenger, g_fontNames[0]);
            beMessenger_AppendString(self->_messenger, description);
            beMessenger_DispatchSelected(self->_messenger, TEXTSET);
            visibility = DISPON;
        } else {
            visibility = DISPOFF;
        }
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, STWINFONT29);
        beMessenger_AppendString(self->_messenger, g_fontNames[0]);
        beMessenger_AppendString(self->_messenger, visibility);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
    }
}

int beNDMWShopCtrlDeviceSell_UpdatePageCount(beNDMWShopCtrlDeviceSell *self) {
    igObjectList *devices; int count; int pages; int remaining; int rows; int row; int index; beNDMWStatus *status;
    beNDMWItemBase *device; bool sellable; int slot; igBoolList *decide;
    beMessenger_SelectGroup(self->_messenger, GAMERAM_14);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_10);
    devices = PlayerFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_4);
    count = devices->_count;
    if (count % SELL_PAGE_ROWS != 0) pages = count / SELL_PAGE_ROWS + 1; else pages = count / SELL_PAGE_ROWS;
    self->_maxPage = pages;
    remaining = count - self->_nowPage * SELL_PAGE_ROWS;
    rows = (remaining >= SELL_PAGE_ROWS) ? SELL_PAGE_ROWS : remaining % SELL_PAGE_ROWS;
    row = 0;
    ((igBoolList *)self->_decideList)->_count = 0;
    do {
        index = row + self->_nowPage * SELL_PAGE_ROWS;
        if (index < count) {
            status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
            device = ((beNDMWItemBase **)devices->_data)[index];
            sellable = true;
            if (device->_isEquip != 0) sellable = false;
            else if (beNDMWItemRevisionPocketBase_GetPrice(device, status, KAITORI_2) <= 0) sellable = false;
            decide = (igBoolList *)self->_decideList;
            slot = decide->_count;
            if (slot < decide->_capacity) decide->_count = slot + 1; else List_Resize(decide, slot + 1, 1);
            ((unsigned char *)decide->_data)[slot] = sellable;
        }
        row++;
    } while (row < SELL_PAGE_ROWS);
    return rows;
}

void beNDMWShopCtrlDeviceSell_ResetRowColors(beNDMWShopCtrlDeviceSell *self) {
    int row;
    const char **rowFont = g_fontNames;
    for (row = 0; row < SELL_PAGE_ROWS; row++) {
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, STWINFONT14);
        beMessenger_AppendString(self->_messenger, *rowFont);
        beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, STWINFONT17);
        beMessenger_AppendString(self->_messenger, *rowFont);
        beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_5);
        rowFont++;
    }
}

#define SET_TEXT(window, font, label, text) { \
    beMessenger_SelectGroup((window)->_messenger, TEXTCTL_3); \
    beMessenger_AppendString((window)->_messenger, font); \
    beMessenger_AppendString((window)->_messenger, label); \
    beMessenger_AppendString((window)->_messenger, text); \
    beMessenger_DispatchSelected((window)->_messenger, TEXTSET); }
#define SWITCH_TEXT(window, font, label, display) { \
    beMessenger_SelectGroup((window)->_messenger, TEXTCTL_3); \
    beMessenger_AppendString((window)->_messenger, font); \
    beMessenger_AppendString((window)->_messenger, label); \
    beMessenger_AppendString((window)->_messenger, display); \
    beMessenger_DispatchSelected((window)->_messenger, SWITCH_2); }

enum { MAX_BITS = 9999999 };

static inline void ReleaseObject(igObject *o)
{
    if (o) {
        --o->_refCount;
        if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o);
    }
}

enum DiskSellStep { DISKSELL_PICK_DISK = 6, DISKSELL_PICK_QUANTITY, DISKSELL_CONFIRM };

void beNDMWShopCtrlDiskSell_Update(beNDMWShopCtrlDiskSell *self) {
    float leftCursorPos[3];
    float rightCursorPos[3];
    void *allocator;
    igObjectList *disks;
    igObjectList *offered;
    beNDMWItemDisk *disk;
    int i;
    int j;
    int player;
    igObjectList *stock;
    int sale;
    int bits;

    switch (self->_st0) {
    default:
        return;
    case SHOP_STATE_OPEN:
        beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_WAIT_5, SQ_CLOSE_10);
        leftCursorPos[0] = -146.0f;
        leftCursorPos[1] = 25.0f;
        leftCursorPos[2] = 0.0f;
        beNDMWWindow_PresentModel(self, i_stcursorleft_2, 0, SQ_HIDE_2, SQ_CLOSE_10, leftCursorPos);
        rightCursorPos[0] = 236.0f;
        rightCursorPos[1] = 25.0f;
        rightCursorPos[2] = 0.0f;
        beNDMWWindow_PresentModel(self, i_stcursorright_2, 0, SQ_HIDE_2, SQ_CLOSE_10, rightCursorPos);
        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT29)));
        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(font100_3)));
        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT13_2)));
        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_fontNames[0])));
        beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 1001);
        disks = PlayerFolder(GetPlayer(self), DISKFOLDER_5);
        for (i = 0; i < disks->_count; i++) {
            beNDMWWindow_QueueText(self, STWINFONT14, g_fontNames[i], space_2, LEFT_4);
            beNDMWWindow_QueueText(self, STWINFONT15_2, g_fontNames[i], space_2, CENTER_4);
            beNDMWWindow_QueueText(self, STWINFONT17, g_fontNames[i], space_2, RIGHT_3);
        }
        self->_cursor = 0;
        NEXT_STATE(self)
        ENTER_STEP(self, DISKSELL_PICK_DISK)
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case DISKSELL_PICK_DISK:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, MODELCTRL_16, j_shwin, 0, SQ_EWINOPEN);
                beNDMWShopCtrlSell_MoveRowCursor((beNDMWWindow *)self->_mother, -1);
                PICK_ALLOCATOR(allocator, self)
                {
                igSmartPointer<beNDMWStatusSelectE1> selector((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(allocator));
                self->_retCode = self->_cursor;
                beNDMWWindow_BindContext(selector.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, selector.p);
                {
                    beNDMWStatusSelectE1 *window = selector.p;
                    window->_offsetPos[0] = -121.0f;
                    window->_offsetPos[1] = 128.0f;
                    window->_offsetPos[2] = 0.0f;
                }
                selector.p->_startPoint = self->_cursor;
                beNDMWWindow_QueueText(selector.p, STWINFONT29, g_fontNames[0], space_2, LEFT_4);
                offered = PlayerFolder(GetPlayer(self), DISKFOLDER_5);
                selector.p->_selectMax = offered->_count;
                PICK_ALLOCATOR(allocator, self)
                igSmartPointer<igBoolList> sellable((igBoolList *)igBoolList_Create(allocator));
                for (j = 0; j < offered->_count; j++) {
                    if (DiskCount(((beNDMWItemDisk **)offered->_data)[j]) > 0) {
                        BoolList_Append(sellable.p, true);
                    } else {
                        BoolList_Append(sellable.p, false);
                    }
                }
                {
                    igBoolList *decide = (igBoolList *)sellable.p;
                    beNDMWStatusSelectE1 *window = selector.p;
                    if (decide != 0) {
                        decide->_refCount = decide->_refCount + 1;
                    }
                    ReleaseObject((igObject *)window->_decideList);
                    window->_decideList = (int)decide;
                }
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 1654);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case 1:
                beNDMWShopCtrlDiskSell_RefreshText(self, 1, 1);
                NEXT_PHASE(self)
                return;
            case 2:
                if (CHILD_COUNT(self) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            beNDMWShopCtrlDiskSell_RefreshText(self, 0, 1);
                            self->_st3 = self->_retCode;
                            return;
                        }
                    }
                } else {
                    if (self->_retCode != -1) {
                        ENTER_STEP(self, DISKSELL_PICK_QUANTITY)
                        self->_cursor = self->_retCode;
                        beNDMWShopCtrlSell_MoveRowCursor((beNDMWWindow *)self->_mother, self->_cursor);
                        self->_maxSell = DiskCount(((beNDMWItemDisk **)PlayerFolder(GetPlayer(self), DISKFOLDER_5)->_data)[self->_cursor]);
                        if (self->_maxSell == 0) {
                            ENTER_STEP(self, DISKSELL_PICK_DISK)
                            return;
                        }
                        break;
                    }
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    NEXT_STATE(self)
                    return;
                }
                break;
            }
            break;
        case DISKSELL_PICK_QUANTITY:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, MODELCTRL_16, j_shwin, 0, SQ_BWINOPEN);
                PICK_ALLOCATOR(allocator, self)
                {
                igSmartPointer<beNDMWShopSelect52> quantity((beNDMWShopSelect52 *)beNDMWShopSelect52_Create(allocator));
                beNDMWWindow_BindContext(quantity.p, self, self->_insight, self->_playerNo, self->_maxSell);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, quantity.p);
                {
                    beNDMWShopSelect52 *window = quantity.p;
                    window->_offsetPos[0] = 52.0f;
                    window->_offsetPos[1] = -104.0f;
                    window->_offsetPos[2] = 0.0f;
                }
                StringList_AppendRetained(quantity.p->_textCloseTypeList, StringRef(InternString(STWINFONT29)));
                StringList_AppendRetained(quantity.p->_textCloseNameList, StringRef(InternString(font100_3)));
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 1572);
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, 1505);
                self->_retCode = self->_maxSell - 1;
                beNDMWShopCtrlDiskSell_ShowQuantity(self);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case 1:
                if (CHILD_COUNT(self) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            beNDMWShopCtrlDiskSell_ShowQuantity(self);
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    if (self->_retCode != -1) {
                        ENTER_STEP(self, DISKSELL_CONFIRM)
                        self->_kazu = self->_maxSell - self->_retCode;
                        return;
                    }
                    beNDMWShopCtrlDiskSell_HideQuantity(self);
                    ENTER_STEP(self, DISKSELL_PICK_DISK)
                    return;
                }
                break;
            }
            break;
        case DISKSELL_CONFIRM:
            switch (self->_st2) {
            case 0:
                PICK_ALLOCATOR(allocator, self)
                {
                igSmartPointer<beNDMWShopSelect00> question((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                beNDMWWindow_BindContext(question.p, self, self->_insight, self->_playerNo, 1561);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, question.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case 1:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    PICK_ALLOCATOR(allocator, self)
                    {
                    igSmartPointer<beNDMWShopSelect01> answer((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(answer.p, self, self->_insight, self->_playerNo, 1562);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, answer.p);
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    NEXT_PHASE(self)
                    return;
                }
                break;
            case 2:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    beNDMWShopCtrlDiskSell_HideQuantity(self);
                    switch (self->_retCode) {
                    case ANSWER_YES:
                        player = GetPlayer(self);
                        stock = PlayerFolder(player, DISKFOLDER_5);
                        sale = self->_tanka * self->_kazu;
                        bits = PlayerInt(player, BIT_7)->_data;
                        bits += sale;
                        if (bits > MAX_BITS) {
                            bits = MAX_BITS;
                        }
                        PlayerInt(player, BIT_7)->_data = bits;
                        beMessenger_SelectGroup(self->_messenger, SUBWND_8);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, UPDATE_3);
                        disk = ((beNDMWItemDisk **)stock->_data)[self->_cursor];
                        disk->_kazu = DiskCount(disk) - self->_kazu;
                        break;
                    case ANSWER_NO:
                        break;
                    }
                    ENTER_STEP(self, DISKSELL_PICK_DISK)
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        beNDMWShopCtrlSell_MoveRowCursor((beNDMWWindow *)self->_mother, -1);
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Writes the disk rows (name, count, buy-back price) and/or the selected disk's description. */
void beNDMWShopCtrlDiskSell_RefreshText(beNDMWShopCtrlDiskSell *self, int refreshRows, int refreshSelection) {
    char price[28];
    char count[2];
    igObjectList *disks;
    beNDMWStatus *status;
    int i;
    beNDMWItemDisk *disk;
    char *text;

    disks = PlayerFolder(GetPlayer(self), DISKFOLDER_5);
    status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
    if (refreshRows != 0) {
        for (i = 0; i < disks->_count; i++) {
            disk = ((beNDMWItemDisk **)disks->_data)[i];
            text = beNDMWItemBase_GetRecordString(disk, status, NAME_2);
            SET_TEXT(self, STWINFONT14, g_fontNames[i], text)
            count[0] = '0' + DiskCount(disk);
            count[1] = 0;
            SET_TEXT(self, STWINFONT15_2, g_fontNames[i], count)
            sprintf(price, percent_d, beNDMWItemRevisionPocketBase_GetPrice(disk, status, KAITORI_2));
            SET_TEXT(self, STWINFONT17, g_fontNames[i], price)
            SWITCH_TEXT(self, STWINFONT14, g_fontNames[i], DISPON)
            SWITCH_TEXT(self, STWINFONT15_2, g_fontNames[i], DISPON)
            SWITCH_TEXT(self, STWINFONT17, g_fontNames[i], DISPON)
        }
    }
    if (refreshSelection != 0) {
        int row = self->_retCode;
        disk = 0;
        if (row != -1) {
            disk = ((beNDMWItemDisk **)disks->_data)[row];
        }
        if (disk != 0) {
            text = beNDMWItemBase_GetRecordString(disk, status, TXT);
            SET_TEXT(self, STWINFONT29, g_fontNames[0], text)
            SWITCH_TEXT(self, STWINFONT29, g_fontNames[0], DISPON)
            self->_tanka = beNDMWItemRevisionPocketBase_GetPrice(disk, status, KAITORI_2);
            return;
        }
        SWITCH_TEXT(self, STWINFONT29, g_fontNames[0], DISPOFF)
    }
}

/* Shows how many disks the quantity window sells and what they fetch. */
void beNDMWShopCtrlDiskSell_ShowQuantity(beNDMWShopCtrlDiskSell *self) {
    char text[16];
    int quantity;

    quantity = self->_maxSell - self->_retCode;
    sprintf(text, percent_d, quantity);
    SET_TEXT(self, STWINFONT30, font010_3, text)
    sprintf(text, percent_d, quantity * self->_tanka);
    SET_TEXT(self, STWINFONT30, font021, text)
}

void beNDMWShopCtrlDiskSell_HideQuantity(beNDMWShopCtrlDiskSell *self) {
    SWITCH_TEXT(self, STWINFONT30, font020, DISPOFF)
    SWITCH_TEXT(self, STWINFONT30, font010_3, DISPOFF)
    SWITCH_TEXT(self, STWINFONT30, font021, DISPOFF)
}

enum { SALES_PAGE_ROWS = 12 };
enum ItemKind { ITEM_WEAPON, ITEM_BLUE_ARMOR, ITEM_YELLOW_ARMOR, ITEM_ABILITY_CHIP };
/* This ability chip is listed without a price and cannot be chosen. */
enum { UNPRICED_CHIP_RECORD = 185 };
/* Puts `item` (retained) into slot 0, releasing what was there. */
#define EQUIP_FIRST_SLOT(slots, item) { \
    beNDMWItemBase *replaced; \
    if ((item) != 0) (item)->_refCount++; \
    replaced = ((beNDMWItemBase **)(slots)->_data)[0]; \
    ReleaseObject(replaced); \
    if ((slots)->_count != 0 && 0 < (slots)->_count) ((beNDMWItemBase **)(slots)->_data)[0] = (item); }
#define SALES_ITEMS(self) ((igObjectList *)(self)->_salesItemList)

/* Writes the page's rows (name in its revision colour, price) and page numbers, and/or the
 * selected item's description. */
void beNDMWShopCtrlSales_RefreshText(beNDMWShopCtrlSales *self, int refreshRows, unsigned char refreshSelection) {
    beNDMWStatus *status;
    int row;
    beNDMWItemRevisionPocketBase *item;
    char *text;
    status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
    if (refreshRows != 0) {
        row = 0;
        do {
            StringRef display;
            item = 0;
            int index = row + self->_nowPage * SALES_PAGE_ROWS;
            if (index < SALES_ITEMS(self)->_count) item = ((beNDMWItemRevisionPocketBase **)SALES_ITEMS(self)->_data)[index];
            if (item != 0) {
                ChipPriceText price;
                text = beNDMWItemBase_GetRecordString(item, status, NAME_2);
                SET_TEXT(self, STWINFONT14, g_fontNames[row], text)
                igVec3f color = beNDMWItemBase_GetRevisionColor((beNDMWItemBase *)item);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT14);
                beMessenger_AppendString(self->_messenger, g_fontNames[row]);
                igVec3f colorArgument(color);
                beMessenger_AppendVec3(self->_messenger, (float *)&colorArgument);
                beMessenger_DispatchSelected(self->_messenger, COLOR_4);
                if (item->_kindNo == ITEM_ABILITY_CHIP && item->_recNo == UNPRICED_CHIP_RECORD) {
                    price = dashdashdashdash_2;
                } else {
                    sprintf(price.text, percent_d, beNDMWItemRevisionPocketBase_GetPrice(item, status, HANBAI_2));
                }
                SET_TEXT(self, STWINFONT17, g_fontNames[row], (char *)&price)
                display.Set(InternLiteral(DISPON));
            } else {
                display.Set(InternLiteral(DISPOFF));
            }
            SWITCH_TEXT(self, STWINFONT14, g_fontNames[row], display.p)
            SWITCH_TEXT(self, STWINFONT17, g_fontNames[row], display.p)
        } while (++row < SALES_PAGE_ROWS);
        char digit[2];
        digit[1] = 0;
        digit[0] = '1' + self->_nowPage;
        SET_TEXT(self, STWINFONT30, g_fontNames[0], digit)
        digit[0] = '0' + self->_maxPage;
        SET_TEXT(self, STWINFONT30, g_fontNames[1], digit)
    }
    if (refreshSelection) {
        int base = self->_nowPage * SALES_PAGE_ROWS;
        item = ((beNDMWItemRevisionPocketBase **)SALES_ITEMS(self)->_data)[base + self->_retCode];
        char *shown;
        if (item != 0) {
            text = beNDMWItemBase_GetRecordString(item, status, TXT);
            if (item->_kindNo == ITEM_WEAPON || item->_kindNo == ITEM_BLUE_ARMOR) {
                char pocket[2];
                pocket[1] = 0;
                pocket[0] = '0' + item->_pocket;
                igSmartPointer<igStringObj> label((igStringObj *)((beSystem *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]))->_globalStrObj, kRetainReference);
                igStringObj_Set(label.p, text);
                igStringObj *labelText = label.p;
                row = labelText->_length;
                igStringObj_Insert(labelText, pocket, row, strlen(pocket));
                text = (label.p->_buffer == 0) ? g_stringObjEmptyText[0] : (char *)label.p->_buffer;
            }
            SET_TEXT(self, STWINFONT29, g_fontNames[0], text)
            shown = DISPON;
            beNDMWShopCtrlSales_PreviewSelected(self, 1);
        } else {
            shown = DISPOFF;
            beNDMWShopCtrlSales_PreviewSelected(self, 0);
        }
        SWITCH_TEXT(self, STWINFONT29, g_fontNames[0], shown)
    }
}

/* Counts the pages, returns how many rows the current page shows and refills the decide list
 * (an empty row or the unpriced chip cannot be chosen). */
int beNDMWShopCtrlSales_UpdatePageCount(beNDMWShopCtrlSales *self) {
    int listed;
    int pages;
    int row;
    int i;
    int offset;
    int index;
    int base;
    int rows;
    igObjectList *items;
    int j;
    beNDMWItemBase *item;
    igObjectList *scan;
    scan = SALES_ITEMS(self);
    listed = scan->_count;
    i = 0;
    if (i < listed) {
        offset = 0;
        do {
            if (*(int *)(scan->_data + offset) != 0) listed = i + 1;
            i++;
            offset += 4;
            scan = SALES_ITEMS(self);
        } while (i < scan->_count);
    }
    if (listed % SALES_PAGE_ROWS != 0) pages = listed / SALES_PAGE_ROWS + 1;
    else pages = listed / SALES_PAGE_ROWS;
    self->_maxPage = pages;
    rows = SALES_PAGE_ROWS;
    base = self->_nowPage * SALES_PAGE_ROWS;
    items = SALES_ITEMS(self);
    for (row = 0; row < SALES_PAGE_ROWS; row++) {
        index = base + row;
        if (index > items->_count - 1 || ((int *)items->_data)[index] == 0) { rows = row; break; }
        items = SALES_ITEMS(self);
    }
    if (rows <= 0) rows = 1;
    else if (rows > SALES_PAGE_ROWS) rows = SALES_PAGE_ROWS;
    ((igBoolList *)self->_decideList)->_count = 0;
    for (j = 0; j < rows; j++) {
        item = ((beNDMWItemBase **)SALES_ITEMS(self)->_data)[base + j];
        if (item == 0) {
            BoolList_Append((igObject *)self->_decideList, false);
        } else if (item->_kindNo == ITEM_ABILITY_CHIP && item->_recNo == UNPRICED_CHIP_RECORD) {
            BoolList_Append((igObject *)self->_decideList, false);
        } else {
            BoolList_Append((igObject *)self->_decideList, true);
        }
    }
    return rows;
}

/* Whether `player` can use `item`: a weapon needs the digimon's equip bit and enough points in
 * its skill, armour enough level; kind 3 always can. */
static inline bool PlayerCanUse(beNDMWShopCtrlSales *self, beNDMWItemBase *item, int player)
{
    beNDMWStatus *status;
    if (item == 0) return false;
    if (item->_kindNo == 3) return true;
    status = (beNDMWStatus *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
    if (item->_kindNo == 0) {
        int digimonNo = PlayerInt(player, DIGIMONNO_6)->_data;
        int equippable = (1 << digimonNo) & beNDMWItemBase_GetRecordInt(item, status, SOUBI_3);
        igIntList *skills = (igIntList *)igProperty_GetRecordIntList(player, SKILL_3)->_data;
        int skill = beNDMWItemBase_GetRecordInt(item, status, SKILL_3);
        int required = beNDMWItemBase_GetRecordInt(item, status, SKILLPOINT_3);
        if (equippable != 0 && ((int *)skills->_data)[skill] >= required) return true;
        return false;
    } else if (item->_kindNo == 1 || item->_kindNo == 2) {
        int level = PlayerInt(player, LEVEL_8)->_data;
        if (level >= beNDMWItemBase_GetRecordInt(item, status, LVPOINT_2)) return true;
        return false;
    }
    return false;
}

bool beNDMWShopCtrlSales_CanPlayerUse(beNDMWShopCtrlSales *self, beNDMWItemBase *item) {
    return PlayerCanUse(self, item, GetPlayer(self));
}

/* Previews the selected item: equips it with the slot's current equipment stashed, has GAMERAM
 * recalculate the player for SUBWND's preview, then puts the equipment back. */
void beNDMWShopCtrlSales_PreviewSelected(beNDMWShopCtrlSales *self, int preview) {
    int player;
    beNDMWItemBase *item;
    igObjectList *weaponSockets, *mainSlots, *subSlots;
    igObjectList *weaponPockets, *mainPockets;
    int kind;
    int base;
    int show;
    player = GetPlayer(self);
    show = (unsigned char)preview;
    item = 0;
    if (show == 1) {
        base = self->_nowPage * SALES_PAGE_ROWS;
        item = ((beNDMWItemBase **)SALES_ITEMS(self)->_data)[base + self->_retCode];
    }
    if (show == 1 && item != 0) {
        weaponSockets = PlayerFolder(player, POWERSOCKET_4);
        weaponPockets = PlayerFolder(player, POWERPOCKET_4);
        mainSlots = PlayerFolder(player, MAINSLOT_4);
        mainPockets = PlayerFolder(player, MAINPOCKET_4);
        subSlots = PlayerFolder(player, SUBSLOT_4);
        igSmartPointer<beNDMWItemBaseList> stashedSlots((beNDMWItemBaseList *)beNDMWItemBaseList_Create(OwnerAllocator(self)));
        igSmartPointer<beNDMWItemBaseList> stashedPockets((beNDMWItemBaseList *)beNDMWItemBaseList_Create(OwnerAllocator(self)));
        kind = item->_kindNo;
        if (kind == ITEM_WEAPON) {
            beNDMWShopCtrlSales_StashEquipment(self, weaponSockets, (igObjectList *)stashedSlots.p, weaponPockets, (igObjectList *)stashedPockets.p);
            EQUIP_FIRST_SLOT(weaponSockets, item)
        } else if (kind == ITEM_BLUE_ARMOR) {
            beNDMWShopCtrlSales_StashEquipment(self, mainSlots, (igObjectList *)stashedSlots.p, mainPockets, (igObjectList *)stashedPockets.p);
            EQUIP_FIRST_SLOT(mainSlots, item)
        } else if (kind == ITEM_YELLOW_ARMOR) {
            beNDMWShopCtrlSales_StashEquipment(self, subSlots, (igObjectList *)stashedSlots.p, 0, 0);
            EQUIP_FIRST_SLOT(subSlots, item)
        }
        beMessenger_SelectReceivers(self->_messenger, GAMERAM_14, 0, 0);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_5);
        beMessenger_SelectGroup(self->_messenger, SUBWND_8);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, ONPREVIEW_2);
        kind = item->_kindNo;
        if (kind == ITEM_WEAPON) beNDMWShopCtrlSales_RestoreEquipment(self, (igDataList *)weaponSockets, (igDataList *)stashedSlots.p, (igDataList *)weaponPockets, (igDataList *)stashedPockets.p);
        else if (kind == ITEM_BLUE_ARMOR) beNDMWShopCtrlSales_RestoreEquipment(self, (igDataList *)mainSlots, (igDataList *)stashedSlots.p, (igDataList *)mainPockets, (igDataList *)stashedPockets.p);
        else if (kind == ITEM_YELLOW_ARMOR) beNDMWShopCtrlSales_RestoreEquipment(self, (igDataList *)subSlots, (igDataList *)stashedSlots.p, 0, 0);
        beMessenger_SelectReceivers(self->_messenger, GAMERAM_14, 0, 0);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, RECALCPLAYER_5);
    } else {
        beMessenger_SelectGroup(self->_messenger, SUBWND_8);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, OFPREVIEW_2);
    }
}

/* Moves every item of the slot list (and of the pocket list, when given) into the stash lists,
 * unequipped, and empties the slots. */
void beNDMWShopCtrlSales_StashEquipment(void *owner, igObjectList *slots, igObjectList *stashedSlots, igObjectList *pockets, igObjectList *stashedPockets) {
    int pocket;
    igObject *held;
    int slot;
    beNDMWItemBase *item;
    slot = 0;
    goto enterSlots;
nextSlot:
    item = ((beNDMWItemBase **)slots->_data)[slot];
    ObjectList_AppendRetained(stashedSlots, item);
    if (item != 0) item->_isEquip = 0;
    held = ((igObject **)slots->_data)[slot];
    ReleaseObject(held);
    if (slots->_count != 0 && slot >= 0 && slot < slots->_count) {
        ((igObject **)slots->_data)[slot] = 0;
    }
    slot++;
testSlot:
    if (slot < slots->_count) goto nextSlot;
slotsDone:
    if (pockets != 0) {
        if (stashedPockets != 0) {
            pocket = 0;
            goto enterPockets;
nextPocket:
            item = ((beNDMWItemBase **)pockets->_data)[pocket];
            ObjectList_AppendRetained(stashedPockets, item);
            if (item != 0) item->_isEquip = 0;
            held = ((igObject **)pockets->_data)[pocket];
            ReleaseObject(held);
            if (pockets->_count != 0 && pocket >= 0 && pocket < pockets->_count) {
                ((igObject **)pockets->_data)[pocket] = 0;
            }
            pocket++;
testPocket:
            if (pocket < pockets->_count) goto nextPocket;
        }
    }
done:
    return;
enterPockets:
    if (0 < pockets->_count) goto testPocket;
    goto done;
enterSlots:
    if (0 < slots->_count) goto testSlot;
    goto slotsDone;
}

/* Puts the stashed items back into their slots (and pockets), equipped, and empties the stash. */
void beNDMWShopCtrlSales_RestoreEquipment(void *owner, igDataList *slots, igDataList *stashedSlots, igDataList *pockets, igDataList *stashedPockets) {
    int pocket;
    beNDMWItemBase *pocketItem;
    int slot;
    igObject *pocketHeld;
    igObject *held;
    beNDMWItemBase *item;
    slot = 0;
    goto enterSlots;
nextSlot:
    item = ((beNDMWItemBase **)stashedSlots->_data)[slot];
    if (item != 0) item->_refCount++;
    held = ((igObject **)slots->_data)[slot];
    ReleaseObject(held);
    if (slots->_count != 0 && slot >= 0 && slot < slots->_count) {
        ((beNDMWItemBase **)slots->_data)[slot] = item;
    }
    if (item != 0) item->_isEquip = 1;
    held = ((igObject **)stashedSlots->_data)[slot];
    ReleaseObject(held);
    if (stashedSlots->_count != 0 && slot >= 0 && slot < stashedSlots->_count) {
        ((igObject **)stashedSlots->_data)[slot] = 0;
    }
    slot++;
testSlot:
    if (slot < stashedSlots->_count) goto nextSlot;
slotsDone:
    if (pockets != 0) {
        if (stashedPockets != 0) {
            pocket = 0;
            goto enterPockets;
nextPocket:
            pocketItem = ((beNDMWItemBase **)stashedPockets->_data)[pocket];
            if (pocketItem != 0) pocketItem->_refCount++;
            pocketHeld = ((igObject **)pockets->_data)[pocket];
            ReleaseObject(pocketHeld);
            if (pockets->_count != 0 && pocket >= 0 && pocket < pockets->_count) {
                ((beNDMWItemBase **)pockets->_data)[pocket] = pocketItem;
            }
            if (pocketItem != 0) pocketItem->_isEquip = 1;
            pocketHeld = ((igObject **)stashedPockets->_data)[pocket];
            ReleaseObject(pocketHeld);
            if (stashedPockets->_count != 0 && pocket >= 0 && pocket < stashedPockets->_count) {
                ((igObject **)stashedPockets->_data)[pocket] = 0;
            }
            pocket++;
testPocket:
            if (pocket < stashedPockets->_count) goto nextPocket;
        }
    }
done:
    return;
enterPockets:
    if (0 < stashedPockets->_count) goto testPocket;
    goto done;
enterSlots:
    if (0 < stashedSlots->_count) goto testSlot;
    goto slotsDone;
}

/* Moves the row cursor model to `row` (opening it at the list's origin first), or closes it for -1. */
void beNDMWShopCtrlSales_MoveRowCursor(beNDMWWindow *window, int row) {
    RowCursorSequences rowSequences;
    float origin[3];
    if (row > -1) {
        rowSequences = g_salesRowCursorSequences;
        beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, ISRUN_10);
        if (beMessenger_GetBool(window->_messenger, 0) != 0) {
            beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, rowSequences.row[row]);
            return;
        }
        beMessenger_SelectReceivers(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0);
        beMessenger_AppendString(window->_messenger, rowSequences.row[row]);
        origin[2] = 0.0f;
        origin[0] = -121.0f;
        origin[1] = 128.0f;
        beMessenger_AppendVec3(window->_messenger, origin);
        beMessenger_DispatchSelected(window->_messenger, GENERATE_13);
        return;
    }
    beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, ISRUN_10);
    if (beMessenger_GetBool(window->_messenger, 0) != 0) {
        beMessenger_SendNamed(window->_messenger, MODELCTRL_16, i_stcursor04_2, 0, SQ_CLOSE_10);
    }
}

#define RECALC_PLAYER_SELECTED(window) { \
    beMessenger_SelectReceivers((window)->_messenger, GAMERAM_14, 0, 0); \
    beMessenger_AppendInt((window)->_messenger, (window)->_playerNo); \
    beMessenger_DispatchSelected((window)->_messenger, RECALCPLAYER_5); }

/* _st1 of beNDMWShopCtrlXdataChip in SHOP_STATE_RUN. */
enum XdataChipStep {
    CHIP_STEP_LIST = 0,
    CHIP_STEP_REFRESH_PAGE = 1,
    CHIP_STEP_SELECT = 2,
    CHIP_STEP_CHECK_COST = 3,
    CHIP_STEP_UPGRADE = 4,
    CHIP_STEP_NO_CHIPS = 10,
    CHIP_STEP_REFUSED = 11
};

/* _st2 substeps: the list step opens the window only on LIST_OPEN; the dialogs open then wait. */
enum XdataChipSubstep {
    LIST_OPEN = 0,
    LIST_REBUILD = 1,
    UPGRADE_SHOW_INFO = 0,
    UPGRADE_CONFIRM = 1,
    UPGRADE_COMMIT = 2,
    NOTICE_OPEN = 0,
    NOTICE_WAIT = 1
};

/* Shop message codes shown by the chip upgrade dialogs. */
enum XdataChipMessage {
    CHIP_MSG_GUIDE_SCRIPT = 1110,
    CHIP_MSG_SHORT_OF_XDATA = 1161,
    CHIP_MSG_NO_CHIPS = 1169,
    CHIP_MSG_MAX_LEVEL = 1170,
    CHIP_MSG_CONFIRM = 1171
};

enum { CHIP_KIND = 3, CHIP_STAT_PROMPTS = 8 };

#define CHIP_AT(window, index) (((beNDMWItemBase **)((igObjectList *)(window)->_itemBaseList)->_data)[index])

/* Info-window message codes for the first stat a chip raises, in statKeys order (resistances last);
 * the table is copied by quadwords. */
union ChipStatPrompts { int code[CHIP_STAT_PROMPTS]; unsigned __int128 quad[2]; };

/* XDATA chip upgrade shop: lists the player's ability chips twelve to a page with their next-level
 * XDATA cost, previews the highlighted chip one level up and, on confirmation, spends the XDATA and
 * raises the chip's level. */
void beNDMWShopCtrlXdataChip_Update(beNDMWShopCtrlXdataChip *self) {
    float leftArrowPos[3];
    float rightArrowPos[3];
    char numberText[16];
    ChipStatPrompts statPrompts;
    void *allocator;
    int row;
    int count;
    const char **font;
    igObjectList *deviceFolder;
    igObjectList *chips;
    beDataObjObjectList *folderRecord;
    int rowsOnPage;
    int nextCost;
    int balance;
    int remaining;
    bool pageTurned;
    void *statusManager;
    int index;
    int result;
    beNDMWWindowList *subWindows;
    beNDMWWindowSelect *selector;
    int slot;
    int statIndex;
    int statValue;
    int folderIndex;

    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        APPEND_INTERNED(self->_textCloseTypeList, STWINFONT13_2);
        APPEND_INTERNED(self->_textCloseNameList, font000_5);
        APPEND_INTERNED(self->_textCloseTypeList, STWINFONT35);
        APPEND_INTERNED(self->_textCloseNameList, font000_5);
        for (row = 0, font = g_fontNames; row < CHIPS_PER_PAGE; row++, font++) {
            beNDMWWindow_QueueText(self, STWINFONT14, *font, space_2, LEFT_4);
            beNDMWWindow_QueueText(self, STWINFONT17, *font, space_2, RIGHT_3);
        }
        beNDMWWindow_QueueText(self, STWINFONT29, g_fontNames[0], space_2, LEFT_4);
        beNDMWWindow_QueueText(self, STWINFONT29, font100_3, space_2, LEFT_4);
        beNDMWWindow_QueueText(self, STWINFONT30, g_fontNames[0], space_2, CENTER_4);
        beNDMWWindow_QueueText(self, STWINFONT30, g_fontName1[0], space_2, CENTER_4);
        NEXT_STATE(self)
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case CHIP_STEP_LIST:
            SEND_PLAYER_MESSAGE(self, GAMERAM_14, GETPLAYER_10)
            folderRecord = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_4);
            chips = (igObjectList *)self->_itemBaseList;
            deviceFolder = (igObjectList *)folderRecord->_data;
            count = chips->_count;
            for (slot = 0; slot < count; slot++) {
                igObject *held = ((igObject **)chips->_data)[slot];
                RELEASE(held)
            }
            {
                int clearCount = chips->_count;
                int clearSlot;
                for (clearSlot = 0; clearSlot < clearCount; clearSlot++) {
                    ((igObject **)chips->_data)[clearSlot] = 0;
                }
            }
            chips->_count = 0;
            for (folderIndex = 0; folderIndex < deviceFolder->_count; folderIndex++) {
                beNDMWItemBase *device = ((beNDMWItemBase **)deviceFolder->_data)[folderIndex];
                if (device != 0) {
                    int isChip = device->_kindNo == CHIP_KIND;
                    if (isChip) ObjectList_AppendRetained((igObjectList *)self->_itemBaseList, device);
                }
            }
            if (((igObjectList *)self->_itemBaseList)->_count <= 0) {
                ENTER_STEP(self, CHIP_STEP_NO_CHIPS)
                self->_st3 = CHIP_MSG_NO_CHIPS;
                return;
            }
            rowsOnPage = beNDMWShopCtrlXdataChip_UpdatePageCount(self);
            if (self->_st2 == LIST_OPEN) {
                beNDMWWindow_PresentModelAtOrigin(self, j_shwin, 0, SQ_XDATAITEMOPEN, SQ_CLOSE_10);
                beNDMWWindow_RunMessageScript(self, txt_shop_lua_2, CHIP_MSG_GUIDE_SCRIPT);
                rightArrowPos[0] = 236.0f;
                rightArrowPos[2] = 0.0f;
                rightArrowPos[1] = 25.0f;
                leftArrowPos[0] = -146.0f;
                leftArrowPos[1] = 25.0f;
                leftArrowPos[2] = 0.0f;
                ((PagedWindow *)self)->PresentPageArrows(leftArrowPos, rightArrowPos);
            }
            PICK_ALLOCATOR(allocator, self)
            {
                igSmartPointer<beNDMWStatusSelectE1> pageWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(allocator));
                beNDMWWindow_BindContext(pageWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained((igObjectList *)self->_subWindow, pageWin.p);
                {
                    beNDMWStatusSelectE1 *window = pageWin.p;
                    window->_offsetPos[0] = -121.0f;
                    window->_offsetPos[1] = 128.0f;
                    window->_offsetPos[2] = 0.0f;
                }
                pageWin.p->_selectMax = rowsOnPage;
                pageWin.p->_startPoint = self->_cursor;
            }
            self->_nowProcKazu = CHILD_COUNT(self);
            NEXT_STEP(self)
            return;
        case CHIP_STEP_REFRESH_PAGE:
            if (self->_retCode != -1) {
                beNDMWShopCtrlXdataChip_RefreshText(self, 1, 1);
            }
            NEXT_STEP(self)
        case CHIP_STEP_SELECT:
            subWindows = (beNDMWWindowList *)self->_subWindow;
            if (subWindows->_count == self->_nowProcKazu) {
                result = self->_retCode;
                if (result != -1) {
                    /* _st3 remembers the row whose description is shown. */
                    if (self->_st3 != result) {
                        beNDMWShopCtrlXdataChip_RefreshText(self, 0, 1);
                        self->_st3 = self->_retCode;
                        return;
                    }
                    selector = AsPageSelector(((igObject **)subWindows->_data)[0]);
                    if (selector != 0 && beNDMWWindowSelect_CanRequestFO2TOP(selector) != 0) {
                        pageTurned = false;
                        if (((PagedWindow *)self)->TurnPagePrev() != 0) {
                            pageTurned = true;
                        } else if (((PagedWindow *)self)->TurnPageNext() != 0) {
                            pageTurned = true;
                        }
                        if (pageTurned) {
                            ENTER_STATE(selector, SELECT_STATE_RELOAD_TO_TOP)
                            ENTER_STEP(self, CHIP_STEP_REFRESH_PAGE)
                            selector->_selectMax = beNDMWShopCtrlXdataChip_UpdatePageCount(self);
                            return;
                        }
                    }
                }
            } else {
                result = self->_retCode;
                switch (result) {
                case -1:
                    NEXT_STATE(self)
                    return;
                default:
                    self->_cursor = result;
                    NEXT_STEP(self)
                    return;
                }
            }
            break;
        case CHIP_STEP_CHECK_COST:
            SEND_PLAYER_MESSAGE(self, GAMERAM_14, GETPLAYER_10)
            balance = igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), XDATA_4)->_data;
            index = self->_cursor + self->_nowPage * CHIPS_PER_PAGE;
            nextCost = beNDMWItemBase_GetRecordInt(CHIP_AT(self, index), igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]), NEXTX);
            if (nextCost == -1) {
                ENTER_STEP(self, CHIP_STEP_REFUSED)
                self->_st3 = CHIP_MSG_MAX_LEVEL;
                return;
            }
            if (balance < nextCost) {
                ENTER_STEP(self, CHIP_STEP_REFUSED)
                self->_st3 = CHIP_MSG_SHORT_OF_XDATA;
                return;
            }
            NEXT_STEP(self)
            return;
        case CHIP_STEP_UPGRADE:
            switch (self->_st2) {
            case UPGRADE_SHOW_INFO: {
                beNDMWItemBase *chip;
                void *chipStatusManager;
                int level;
                {
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<beNDMWShopSelect00> infoWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(infoWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, infoWin.p);
                    int chipIndex = self->_cursor + self->_nowPage * CHIPS_PER_PAGE;
                    chipStatusManager = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                    chip = CHIP_AT(self, chipIndex);
                    level = chip->_recNo;
                    if (chip->_isEquip != 0) {
                        /* Preview the equipped chip one level up, then restore it. */
                        chip->_recNo = level + 1;
                        RECALC_PLAYER_SELECTED(self)
                        SEND_PLAYER_MESSAGE(self, SUBWND_8, ONPREVIEW_2)
                        chip->_recNo = level;
                        RECALC_PLAYER_SELECTED(self)
                    }
                    PICK_ALLOCATOR(allocator, self)
                    igSmartPointer<beNDMWItemAbilityChip> nextLevel((beNDMWItemAbilityChip *)beNDMWItemAbilityChip_Create(allocator));
                    beNDMWItemAbilityChip_Set(nextLevel.p, level + 1);
                    beNDMWWindow_QueueText(infoWin.p, STWINFONT29, g_fontNames[0], beNDMWItemBase_GetRecordString(nextLevel.p, chipStatusManager, NAME_2), LEFT_4);
                    beNDMWWindow_QueueText(infoWin.p, STWINFONT41, g_fontName1[0], space_2, LEFT_4);
                    beNDMWWindow_QueueText(infoWin.p, STWINFONT41, g_fontNames[2], space_2, LEFT_4);
                    beNDMWWindow_QueueText(infoWin.p, STWINFONT41, g_fontNames[3], space_2, LEFT_4);
                    beNDMWWindow_QueueText(infoWin.p, STWINFONT29, g_fontNames[2], space_2, LEFT_4);
                    {
                        PICK_ALLOCATOR(allocator, self)
                        igSmartPointer<igStringRefList> statKeys((igStringRefList *)igStringRefList_Create(allocator));
                        APPEND_INTERNED(statKeys.p, TSUYOSA_4);
                        APPEND_INTERNED(statKeys.p, KASHIKOSA_4);
                        APPEND_INTERNED(statKeys.p, SEISHIN_4);
                        APPEND_INTERNED(statKeys.p, SUBAYASA_4);
                        APPEND_INTERNED(statKeys.p, RES_FIRE_3);
                        APPEND_INTERNED(statKeys.p, RES_ICE_3);
                        APPEND_INTERNED(statKeys.p, RES_THUNDER_3);
                        APPEND_INTERNED(statKeys.p, RES_DARK_3);
                        APPEND_INTERNED(statKeys.p, CHIMEIRITSU_3);
                        APPEND_INTERNED(statKeys.p, HPDRAIN_3);
                        APPEND_INTERNED(statKeys.p, MPDRAIN_3);
                        APPEND_INTERNED(statKeys.p, CHOHATURITSU_3);
                        statusManager = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                        PICK_ALLOCATOR(allocator, self)
                        igSmartPointer<igIntList> unusedValues = igSmartPointer<igIntList>((igIntList *)igIntList_Create(allocator));
                        /* Show the first stat the next level raises, with its explanation. */
                        for (statIndex = 0; statIndex < statKeys.p->_count; statIndex++) {
                            statValue = beNDMWItemBase_GetRecordInt(nextLevel.p, statusManager, StringList_CopyRetained(statKeys.p, statIndex).p);
                            if (statValue > 0) {
                                sprintf(numberText, percent_d, statValue);
                                beNDMWWindow_QueueText(infoWin.p, STWINFONT41, font011_3, numberText, RIGHT_3);
                                if (statIndex >= CHIP_STAT_PROMPTS) statIndex = CHIP_STAT_PROMPTS - 1;
                                statPrompts = *(const ChipStatPrompts *)g_xdataChipStatPromptCodes;
                                infoWin.p->_entCode = statPrompts.code[statIndex];
                                break;
                            }
                        }
                    }
                    SEND_PLAYER_MESSAGE(self, GAMERAM_14, GETPLAYER_10)
                    remaining = igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), XDATA_4)->_data;
                    sprintf(numberText, percent_d, remaining - beNDMWItemBase_GetRecordInt(chip, chipStatusManager, NEXTX));
                    beNDMWWindow_QueueText(infoWin.p, STWINFONT41, font012, numberText, RIGHT_3);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            }
            case UPGRADE_CONFIRM:
                if (CHILD_COUNT(self) == self->_nowProcKazu) break;
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect01> confirmWin((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(confirmWin.p, self, self->_insight, self->_playerNo, CHIP_MSG_CONFIRM);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, confirmWin.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case UPGRADE_COMMIT:
                if (CHILD_COUNT(self) == self->_nowProcKazu) break;
                SEND_PLAYER_MESSAGE(self, SUBWND_8, OFPREVIEW_2)
                switch (self->_retCode) {
                case ANSWER_YES: {
                    beNDMWItemBase *upgraded;
                    void *upgradeStatusManager;
                    int cost;
                    int player;
                    int held;
                    int chipIndex = self->_cursor + self->_nowPage * CHIPS_PER_PAGE;
                    upgradeStatusManager = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                    upgraded = CHIP_AT(self, chipIndex);
                    SEND_PLAYER_MESSAGE(self, GAMERAM_14, GETPLAYER_10)
                    player = beMessenger_GetObject(self->_messenger, 0);
                    held = igProperty_GetRecord(player, XDATA_4)->_data;
                    cost = beNDMWItemBase_GetRecordInt(upgraded, upgradeStatusManager, NEXTX);
                    beDataObjInt *xdata = igProperty_GetRecord(player, XDATA_4);
                    xdata->_data = held - cost;
                    upgraded->_recNo = upgraded->_recNo + 1;
                    SEND_PLAYER_MESSAGE(self, GAMERAM_14, RECALCPLAYER_5)
                    SEND_PLAYER_MESSAGE(self, SUBWND_8, UPDATE_3)
                    break;
                }
                default:
                    break;
                }
                ENTER_STEP(self, CHIP_STEP_LIST)
                ENTER_PHASE(self, LIST_REBUILD)
                return;
            }
            break;
        case CHIP_STEP_NO_CHIPS:
            switch (self->_st2) {
            case NOTICE_OPEN:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect00> noticeWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(noticeWin.p, self, self->_insight, self->_playerNo, self->_st3);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, noticeWin.p);
                    beNDMWShopSelect00 *window = noticeWin.p;
                    const char *panelName = InternLiteral(font100_3);
                    ReleaseString((const char *)window->_panelName);
                    window->_panelName = (int)panelName;
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case NOTICE_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    NEXT_STATE(self)
                    return;
                }
                break;
            }
            break;
        case CHIP_STEP_REFUSED:
            switch (self->_st2) {
            case NOTICE_OPEN:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect00> noticeWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(allocator));
                    beNDMWWindow_BindContext(noticeWin.p, self, self->_insight, self->_playerNo, self->_st3);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, noticeWin.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case NOTICE_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ENTER_STEP(self, CHIP_STEP_LIST)
                    ENTER_PHASE(self, LIST_REBUILD)
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* The row the page's select window reported in _retCode. */
static inline int SelectedRow(const beNDMWShopCtrlXdataChip *self) { return self->_retCode; }

/* Recomputes _maxPage and returns how many chips the current page shows (at least one). */
int beNDMWShopCtrlXdataChip_UpdatePageCount(beNDMWShopCtrlXdataChip *self)
{
    int count = ((igObjectList *)self->_itemBaseList)->_count;
    int pages;
    int remaining;
    int rows;

    if (count % CHIPS_PER_PAGE) {
        pages = count / CHIPS_PER_PAGE + 1;
    } else {
        pages = count / CHIPS_PER_PAGE;
    }
    self->_maxPage = pages;
    remaining = ((igObjectList *)self->_itemBaseList)->_count - self->_nowPage * CHIPS_PER_PAGE;
    if (remaining >= CHIPS_PER_PAGE) {
        rows = CHIPS_PER_PAGE;
    } else {
        rows = remaining % CHIPS_PER_PAGE;
    }
    if (rows < 1) {
        rows = 1;
    }
    return rows;
}

/* Sends `value` to the text cell (`textType`, `cell`) through TEXTCTL: TEXTSET sets the text,
 * SWITCH shows (DISPON) or hides (DISPOFF) it. */
#define SEND_TEXT(window, textType, cell, value, selector) { \
    beMessenger_SelectGroup((window)->_messenger, TEXTCTL_3); \
    beMessenger_AppendString((window)->_messenger, textType); \
    beMessenger_AppendString((window)->_messenger, cell); \
    beMessenger_AppendString((window)->_messenger, value); \
    beMessenger_DispatchSelected((window)->_messenger, selector); }

/* Rewrites the chip names and next-level XDATA costs of the current page with the page counter
 * ("n" of "max"), and the description of the highlighted chip. */
void beNDMWShopCtrlXdataChip_RefreshText(beNDMWShopCtrlXdataChip *self, long long refreshRows,
                                         long long refreshDescription) {
    char pageDigit[4];
    ChipPriceText priceText;
    void *statusManager;
    int row;
    int index;
    char *name;
    beNDMWItemBase *item;
    int nextCost;
    char *visibility;
    const char **font;
    int selectedIndex;
    beNDMWItemBase *selectedItem;
    char *description;

    statusManager = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
    if (refreshRows != 0) {
        font = g_fontNames;
        for (row = 0; row < CHIPS_PER_PAGE; row++, font++) {
            index = row + self->_nowPage * CHIPS_PER_PAGE;
            if (index < ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
                item = CHIP_AT(self, index);
                if (item == 0) {
                    continue;
                }
                name = beNDMWItemBase_GetRecordString(item, statusManager, NAME_2);
                nextCost = beNDMWItemBase_GetRecordInt(item, statusManager, NEXTX);
                SEND_TEXT(self, STWINFONT14, *font, name, TEXTSET)
                if (nextCost > 0) {
                    sprintf(priceText.text, percent_d, nextCost);
                } else {
                    priceText = dashdashdashdash_2;
                }
                SEND_TEXT(self, STWINFONT17, *font, priceText.text, TEXTSET)
                visibility = DISPON;
            } else {
                visibility = DISPOFF;
            }
            SEND_TEXT(self, STWINFONT14, *font, visibility, SWITCH_2)
            SEND_TEXT(self, STWINFONT17, *font, visibility, SWITCH_2)
        }
        pageDigit[1] = 0;
        pageDigit[0] = self->_nowPage + '1';
        SEND_TEXT(self, STWINFONT30, g_fontNames[0], pageDigit, TEXTSET)
        pageDigit[0] = self->_maxPage + '0';
        SEND_TEXT(self, STWINFONT30, g_fontName1[0], pageDigit, TEXTSET)
    }
    if (refreshDescription != 0) {
        selectedIndex = self->_nowPage * CHIPS_PER_PAGE + SelectedRow(self);
        if (selectedIndex < ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
            selectedItem = CHIP_AT(self, selectedIndex);
            if (selectedItem != 0) {
                description = beNDMWItemBase_GetRecordString(selectedItem, statusManager, TXT);
                SEND_TEXT(self, STWINFONT29, g_fontNames[0], description, TEXTSET)
                SEND_TEXT(self, STWINFONT29, g_fontNames[0], DISPON, SWITCH_2)
            }
        }
    }
}

/* Shop entry codes (_entCode) served by beNDMWShopDevice. */
enum DeviceShop {
    DEVICE_SHOP_WPU = 6,
    DEVICE_SHOP_APU = 7,
    DEVICE_SHOP_CHIP = 8
};

/* Message codes of each device shop's buy / sell / leave menu. */
enum DeviceShopMenuMessage {
    WPU_MENU_MESSAGE = 1650,
    APU_MENU_MESSAGE = 1750,
    CHIP_MENU_MESSAGE = 1850
};

/* _st1 of beNDMWShopDevice in SHOP_STATE_RUN; the menu's result picks the next step. */
enum DeviceShopStep {
    DEVICE_STEP_MENU = 0,
    DEVICE_STEP_BUY = 1,
    DEVICE_STEP_SELL = 2
};

enum DeviceShopChoice { DEVICE_CHOICE_BUY = 0, DEVICE_CHOICE_SELL = 1, DEVICE_CHOICE_LEAVE = 2 };

/* WPU / APU / chip device shop: a buy / sell / leave menu that opens the sales or sell controller
 * and comes back to the menu when it closes. */
void beNDMWShopDevice_Update(beNDMWShopDevice *self) {
    void *allocator;
    switch (self->_st0) {
    case SHOP_STATE_OPEN:
        self->_st0 = CurrentState(self) + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        ENTER_STEP(self, DEVICE_STEP_MENU)
    case SHOP_STATE_RUN:
        switch (self->_st1) {
        case DEVICE_STEP_MENU:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopSelect01> menuWin((beNDMWShopSelect01 *)beNDMWShopSelect01_Create(allocator));
                    beNDMWWindow_BindContext(menuWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, menuWin.p);
                    switch (self->_entCode) {
                    case DEVICE_SHOP_WPU: menuWin.p->_entCode = WPU_MENU_MESSAGE; break;
                    case DEVICE_SHOP_APU: menuWin.p->_entCode = APU_MENU_MESSAGE; break;
                    case DEVICE_SHOP_CHIP: menuWin.p->_entCode = CHIP_MENU_MESSAGE; break;
                    }
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case DEVICE_CHOICE_BUY:
                        ENTER_STEP(self, DEVICE_STEP_BUY)
                        return;
                    case DEVICE_CHOICE_SELL:
                        ENTER_STEP(self, DEVICE_STEP_SELL)
                        return;
                    default:
                    case DEVICE_CHOICE_LEAVE:
                        NEXT_STATE(self)
                        return;
                    }
                }
                break;
            }
            break;
        case DEVICE_STEP_BUY:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopCtrlSales> salesWin((beNDMWShopCtrlSales *)beNDMWShopCtrlSales_Create(allocator));
                    beNDMWWindow_BindContext(salesWin.p, self, self->_insight, self->_playerNo, self->_entCode);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, salesWin.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ENTER_STEP(self, DEVICE_STEP_MENU)
                    return;
                }
                break;
            }
            break;
        case DEVICE_STEP_SELL:
            switch (self->_st2) {
            case CHILD_OPEN:
                PICK_ALLOCATOR(allocator, self)
                {
                    igSmartPointer<beNDMWShopCtrlSell> sellWin((beNDMWShopCtrlSell *)beNDMWShopCtrlSell_Create(allocator));
                    beNDMWWindow_BindContext(sellWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained((igObjectList *)self->_subWindow, sellWin.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                NEXT_PHASE(self)
            case CHILD_WAIT:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    ENTER_STEP(self, DEVICE_STEP_MENU)
                    return;
                }
                break;
            }
            break;
        }
        break;
    case SHOP_STATE_CLOSE:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_STATE(self)
        return;
    case SHOP_STATE_WAIT_CLOSED:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Metadata accessors: each returns its class's registered meta object. */
int beNDMWShopDevice_GetMeta(void)
{
    return g_beNDMWShopDevice_metaObject[0];
}

int beNDMWShopCtrlXdataChip_GetMeta(void)
{
    return g_beNDMWShopCtrlXdataChip_metaObject[0];
}

int beNDMWShopCtrlSales_GetMeta(void)
{
    return g_beNDMWShopCtrlSales_metaObject[0];
}

int beNDMWShopCtrlDiskSell_GetMeta(void)
{
    return g_beNDMWShopCtrlDiskSell_metaObject[0];
}

int beNDMWShopCtrlDeviceSell_GetMeta(void)
{
    return g_beNDMWShopCtrlDeviceSell_metaObject[0];
}

int beNDMWShopCtrlSell_GetMeta(void)
{
    return g_beNDMWShopCtrlSell_metaObject[0];
}

int beNDMWShopCtrlEditBit_GetMeta(void)
{
    return g_beNDMWShopCtrlEditBit_metaObject[0];
}

int beNDMWShopCtrlDigilabo_GetMeta(void)
{
    return g_beNDMWShopCtrlDigilabo_metaObject[0];
}

int beNDMWShopCtrlEvolve_GetMeta(void)
{
    return g_beNDMWShopCtrlEvolve_metaObject[0];
}

int beNDMWShopCtrlA2_GetMeta(void)
{
    return g_beNDMWShopCtrlA2_metaObject[0];
}

int beNDMWShopCtrlA1_GetMeta(void)
{
    return g_beNDMWShopCtrlA1_metaObject[0];
}

int beNDMWShopCtrlA0_GetMeta(void)
{
    return g_beNDMWShopCtrlA0_metaObject[0];
}

int beNDMWShopJunk_GetMeta(void)
{
    return g_beNDMWShopJunk_metaObject[0];
}

int beNDMWShopCtrl50_GetMeta(void)
{
    return g_beNDMWShopCtrl50_metaObject[0];
}

int beNDMWShopCtrl40_GetMeta(void)
{
    return g_beNDMWShopCtrl40_metaObject[0];
}

int beNDMWShopCtrl30_GetMeta(void)
{
    return g_beNDMWShopCtrl30_metaObject[0];
}

int beNDMWShopCtrl10_GetMeta(void)
{
    return g_beNDMWShopCtrl10_metaObject[0];
}

int beNDMWShopCtrl00_GetMeta(void)
{
    return g_beNDMWShopCtrl00_metaObject[0];
}

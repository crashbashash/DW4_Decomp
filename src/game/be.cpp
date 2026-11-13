/* be: the game object scripts call as `be:<function>(...)`. The Lua class `be` binds the 116
 * native functions below to one dispatcher; the C++ class `be` is the insight manager that
 * finds the other managers those functions talk to. */
#include "src/engine/lua/LuaLibrary.h"
#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/beDemoManager.h"

/* bePlayer_GetStruct's record slots: the shared record, then one per player (index + 1). */
#define PLAYER_SLOT_COMMON 0
#define PLAYER_SLOT_FIRST 1

/* A bullet kind is group * 10000 + sub-kind. */
#define BULLET_KIND_GROUP_SIZE 10000
#define BULLET_KIND_TECHNIQUE_GROUP 4
#define BULLET_KIND_RANK_BONUS_GROUP_A 2
#define BULLET_KIND_RANK_BONUS_GROUP_B 3
#define BULLET_SUBKIND_POISON 20
#define BULLET_SUBKIND_ATTACK_DOWN 70
#define BULLET_SUBKIND_POWER_DOWN 85
#define BULLET_SUBKIND_SLEEP 90
#define BULLET_SUBKIND_BIND 95
#define PLAYER_BULLET_WEAPON_END 1000
#define PLAYER_BULLET_RANGE_A_END 60000
#define PLAYER_BULLET_RANGE_B_BEGIN 80000
#define PLAYER_BULLET_RANGE_B_END 90000
#define DAMAGE_RANK2_FRACTION 0.5f
#define DAMAGE_RANK1_FRACTION 0.25f

/* FLGisOn's pseudo-flag: on while any player has joined. */
#define FLAG_PLAYERS_JOINED 1000

#define RADIANS_TO_DEGREES 57.29578f

/* Rows of g_floatingNumberStyles. */
enum FloatingNumberStyle {
    FLOATING_NUMBER_DAMAGE,
    FLOATING_NUMBER_EXP,
    FLOATING_NUMBER_HEAL,
    FLOATING_NUMBER_PLAYER_DAMAGE,
    FLOATING_NUMBER_BIT
};

/* A floating number: the MODELCTRL info that finds it a free slot and plays its sequence, the
 * NUMBERCTRL info that shows the value, and the sequence for each digit count (1 to 5). */
struct FloatingNumberStyleData {
    const char *modelInfoName;
    const char *numberInfoName;
    const char *digitSequences[5];
};

/* Dispatch-only ABI projection of the system's igMersenneTwisterRandomNumber: genrand is vtable
 * slot 22. */
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

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    void *p;
    StringRef(void *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader((void *)*h, h); } }
};

/* The Lua class `be`, the object scripts call the native API through; its registerFunctions slot
 * is LuaAPI_Register. */
struct LuaAPIClass : LuaClass {
    static void *operator new(unsigned int size, igObject *pool) { return Memory_AllocateBufferDirect(size, pool); }
    static void operator delete(void *memory, igObject *) { Memory_FreeBufferWithAllocator(memory, g_luaGluePool); }
    LuaAPIClass();
};

/* The Lua class `Bec`, the namespace the game's classes are bound under. */
struct BecLuaClass : LuaClass {
    static void *operator new(unsigned int size, igObject *pool) { return Memory_AllocateBufferDirect(size, pool); }
    static void operator delete(void *memory, igObject *) { Memory_FreeBufferWithAllocator(memory, g_luaGluePool); }
    BecLuaClass();
};

extern "C" {
/* This file. */
int LuaAPI_Dispatch(lua_State *L);
LuaClass *LuaAPIClass_Create(void);
LuaClass *BecLuaClass_Create(void);
void LuaAPI_RegisterClasses(void);
void LuaAPI_Register(LuaClass *luaClass);
int be_GetMetaObject_Virtual(void);
void be_AddToScheduler(void);
void be_RemoveFromScheduler(void);
void be_Start(be *self);
void be_Stop(void);
int be_AcceptInfo(void);
void be_Reset(void);
void be_Update(void);
int bePlayer_GetStruct(int slot);
unsigned char SYSisJoinPlayer(int playerIndex);
const char *SYSgetPlayerName(int playerIndex);
const char *SYSgetWeaponName(int playerIndex, int slot);
int SYSgetPlayerNinzu(void);
int SYSgetDifficulty(void);
void SYSsetDifficulty(int difficulty);
int SYSgetCameraMode(void);
int SYSgetLightMode(void);
int SYSgetArea(void);
int SYSgetCountry(void);
int SYSgetTarget(void);
int SYSgetIsPackOnly(void);
unsigned int SYSgetRandom(unsigned int range);
void SYSsetGateStage(const char *stageName, int stageNo);
const char *SYSgetGateStageName(void);
int SYSgetGateStageNo(void);
unsigned char SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1);
unsigned char SYSctlDiskFolder(const char *command, int index, int itemId, int count);
unsigned char SYSctlFlagFolder(const char *command, int index);
int SYSctlBit(const char *command, int index, int value);
int SYSgetPlayerLevel(int playerIndex);
int SYSgetPlayerDigimon(int playerIndex);
unsigned char SYSisGetShinkaDigimon(int playerIndex, int species);
int SYSctlCardFolder(const char *command, int index);
int SYSctlShinka(const char *command, int playerIndex, int species);
int SYSctlPlayer(const char *property, const char *command, int playerIndex, int value);
void CFLclear(void);
void CFLsetName(const char *name);
const char *CFLgetFolderName(void);
void Lua_sd_OptionalArg(const char *args);
void sd_29(const char *group, const char *infoName, int ramNo, const char *message, const char *args);
void sd_30(const char *group, const char *infoName, int ramNo, const char *message);
void sd_31(const char *group, const char *infoName, int ramNo, const char *message, const char *args, long long delay);
void sd_32(const char *group, const char *infoName, int ramNo, const char *message, long long delay);
unsigned char MATisPlayer(void);
unsigned char MATisAllPlayer(void);
int MATgetPlayerNo(void);
unsigned char MATisRidePlayer(int player);
unsigned char MATisRideOffPlayer(int player);
int MATgetPlayerMatStat(int player);
void MATsetRun(int run);
void DMsetSD_40(const char *group, const char *infoName, int ramNo, const char *message, const char *param, long long sendTime);
void DMsetSD_41(const char *group, const char *infoName, int ramNo, const char *message, const char *param);
void DMsetSD_42(const char *group, const char *infoName, int ramNo, const char *message, long long sendTime);
void DMsetSD_43(const char *group, const char *infoName, int ramNo, const char *message);
void DMchkSD_44(const char *group, const char *infoName, int ramNo, const char *message, const char *param, const char *condition);
void DMchkSD_45(const char *group, const char *infoName, int ramNo, const char *message, const char *condition);
void DMsetLua(const char *chunk);
void DMmsgBox(const char *text, int ramNo);
void DMswtSD_46(const char *group, const char *infoName, int ramNo, const char *message, const char *param);
void DMswtSD_47(const char *group, const char *infoName, int ramNo, const char *message);
void DMswtEnd(void);
void DMcase(int ramNo);
void DMrun(void);
int DMgetCount(void);
unsigned char FLGisOn(int flagNo);
void FLGset(int flagNo, unsigned char on);
void FLGflip(int flagNo);
void COUNTERset(int counterNo, int value);
int COUNTERget(int counterNo);
int MDLgetRamNo(void);
const char *MDLgetInfoName(void);
char *MDLgetPosStr(float x, float y, float z);
char *MDLgetRotStr(float x, float y, float z);
int MDLgetMHp(void);
int MDLgetHp(void);
void MDLaddHp(int amount);
void MDLsetSeq(const char *sequence);
void MDLsetSD(const char *message, const char *args);
unsigned char MDLisLive(const char *infoName, int ramNo);
int MDLgetBulletKind(void);
const char *MDLgetBulletName(void);
int MDLgetBulletBoxNo(void);
void FloatingNumber_Spawn(int value, int style);
void MDLdspDamage(int damage);
void MDLdspDamageP(int damage);
void MDLdspExp(int exp);
void MDLsetDMGTurn(int value);
unsigned char MDLisCallName(const char *name);
void MDLsetWorldPosTarget_78(float x, float y, float z);
void MDLsetWorldPosTarget_79(const char *text);
float MDLgetKyoriSquare(float x, float y, float z);
int MDLgetRecNo(void);
unsigned char MDLisSeqName(const char *sequence);
unsigned char MDLisStatus(const char *infoName, int ramNo, const char *status);
int PLAYERgetPos(void);
char *PLAYERgetDataStr(int point, int index, float yaw);
char *PLAYERgetPosStr(int ramNo, float x, float y, float z);
void MsgBox(const char *text, int ramNo);
void ShutDown(void);
int TXTgetCallNo(void);
unsigned char BLTisPlayerBullet(void);
int BLTgetShootRamNo(void);
unsigned char BLTisHitCheck(void);
unsigned char BLTisCritical(void);
int BLTgetDamageValue(unsigned char critical);
int BLTgetDamageRank(int currentHp, unsigned char rankBonus);
const char *BLTgetAttributeStr(void);
int BLTgetStunTime(int stunValue, unsigned char rankBonus);
int BLTgetPoisonTime(const char *effectKey);
int BLTgetSleepTime(void);
int BLTgetBindTime(void);
int BLTgetAttackDownTime(const char *effectKey);
int BLTgetPowerDownTime(const char *effectKey);
void BLTcalcSkillUp(unsigned char first, unsigned char second);
int BLTcalcEXPUp(void);
unsigned char BLPisHitCheck(void);
int BLPgetDamageValue(void);
const char *BLPgetAttackZokusei(void);
int BLPgetDamageRank(int scriptArg1, int scriptArg2);
int BLPgetStunTime(int scriptArg1, int scriptArg2);
int BLPgetPoisonTime(const char *effectKey);
int BLPgetSleepTime(void);
int BLPgetBindTime(void);
int BLPgetAttackDownTime(const char *effectKey);
int BLPgetPowerDownTime(const char *effectKey);
int BLPcalcKoukaMagic(void);
void LISsetDifficultMax(int maxDifficulty);

/* Other files. */
void be_EnsureRegistered(void);
int igInsightCore_FindManager(int insight, igMetaObject *meta);
void *StringPool_Allocate(int size);
void *StringPool_Construct(void *pool);
void *StringPool_Intern(void *pool, const char *text);
void List_Reserve(void *list, int count, int capacity);
void StringList_AppendRetained(igStringRefList *list, StringRef *value);
StringRef StringList_CopyRetained(igStringRefList *list, int index);
beDataObjInt *igProperty_GetRecord(int record, const char *name);
beDataObjBool *igProperty_GetRecordByte(int record, const char *name);
beDataObjString *igProperty_GetRecordString(int record, const char *name);
beDataObjBoolList *igProperty_GetRecordArray(int record, const char *name);
beDataObjIntList *igProperty_GetRecordIntList(int record, const char *name);
beDataObjStringList *igProperty_GetRecordStringList(int record, const char *name);
beModelCtrlInfoRamData *igProperty_FindByName(int list, int nameField, const char *name);
igObject *beBaseInfoDataList_Create(int allocator);
void beMessenger_SelectReceivers(beMessenger *self, const char *group, const char *infoName, int ramNo);
void beMessenger_DispatchSelected(beMessenger *self, const char *message);
void beMessenger_SelectGroup(beMessenger *self, const char *group);
void beMessenger_SendNamed(beMessenger *self, const char *group, const char *infoName, int ramNo, const char *message);
void beMessenger_SendGroup(beMessenger *self, const char *group, const char *message);
void beMessenger_PrepareDelayedSelection(beMessenger *self, const char *group, const char *infoName, int ramNo);
void beMessenger_EnqueueSelected(beMessenger *self, const char *message, long long delay);
void beMessenger_SendDelayedNamed(beMessenger *self, const char *group, const char *infoName, int ramNo, const char *message, long long delay);
int beMessenger_GetBoolCount(beMessenger *self);
unsigned char beMessenger_GetBool(beMessenger *self, int index);
void beMessenger_AppendInt(beMessenger *self, int value);
int beMessenger_GetInt(beMessenger *self, int index);
void beMessenger_AppendFloat(beMessenger *self, float value);
void beMessenger_AppendLong(beMessenger *self, long long value);
void beMessenger_AppendVec3(beMessenger *self, float *value);
int beMessenger_GetMatrixCount(beMessenger *self);
void beMessenger_GetMatrix(float *out, beMessenger *self, int index);
int beMessenger_GetObjectCount(beMessenger *self);
void beMessenger_AppendObject(beMessenger *self, void *object);
int beMessenger_GetObject(beMessenger *self, int index);
void beMessenger_AppendString(beMessenger *self, const char *text);
unsigned char beMatCtrl_IsPlayer(beMatCtrl *self);
unsigned char beMatCtrl_IsAllPlayer(beMatCtrl *self);
int beMatCtrl_GetPlayerNo(beMatCtrl *self);
unsigned char beMatCtrl_IsRidePlayer(beMatCtrl *self, int player);
unsigned char beMatCtrl_IsRideOffPlayer(beMatCtrl *self, int player);
int beMatCtrl_GetPlayerMatStat(beMatCtrl *self, int player);
void beMatCtrl_SetRun(beMatCtrl *self, int run);
void igMatrix44f_SetIdentity(float *matrix);
void Matrix44_Copy(float *matrix, const float *source);
void Matrix44_GetTranslation(const float *matrix, float *vector);
void Matrix44_TranslateLocal(float *matrix, const float *offset);
void Vec3f_TransformDirection(float *out, const float *vector, const float *matrix);
int Vec3f_FromString(const char *text, float *vector, const char *format);
void igStringObj_Set(igStringObj *string, const char *text);
void igStringObj_ToFloat(igStringObj *string, float *value);
void igStringObj_Erase(igStringObj *string, unsigned int position, unsigned int length);
float atan2f(float y, float x);

/* The managers be_Start finds, and the be itself. */
extern beSystem *g_beSystem[4];
extern beMessenger *g_beMessenger[4];
extern beMatCtrl *g_matCtrl[4];
extern beDemoManager *g_beDemoManager[4];
extern be *g_be[4];
extern igMetaObject *g_be_metaObject[4];
extern igMetaObject *g_beSystem_metaObject[4];
extern igMetaObject *g_beMessenger_metaObject[4];
extern igMetaObject *g_beMatCtrl_metaObject[4];
extern igMetaObject *g_beDemoManager_metaObject[4];
extern void *g_stringPool[4];
extern int g_defaultAllocatorSelector[4];
extern unsigned char g_useOwnerAllocator;
extern int g_propertyNameField[4];

/* The model the running MDL / BLT / BLP script is about, cached by beModelCtrl before it calls
 * the script, and the hitter of the bullet that struck it. */
extern beBaseInfoRam *g_mdlEntity[4];
extern int g_mdlRamNo[4];
extern float *g_mdlMatrix[4];
extern int g_mdlMaxHp[4];
extern int g_mdlHp[4];
extern int g_mdlRecNo[4];
extern const char *g_mdlInfoName[4];
extern int g_mdlBulletKind[4];
extern int g_mdlBulletBoxNo[4];
extern const char *g_hitterInfoName[4];
extern int g_bltShootRamNo[4];
extern int g_hitterRecNo[4];
extern const char *g_mdlCallName[4];
extern float *g_mdlWorldPosTarget[4];
extern int g_txtCallNo[4];

/* The last FIGHTCALC damage reply: damage, attribute index and rank flag. */
extern int g_damageResult[4];
extern int g_attackZokusei[4];
extern int g_damageFlag[4];

/* The Lua class tables LuaAPI_Register hands the binding, and the classes' vtables. */
extern const char *g_luaApiFunctionNames[116];
extern const unsigned int g_luaApiFunctionCodes[];
extern const int g_LuaAPIClass_vtable[4];
extern const int g_BecLuaClass_vtable[4];

extern const char *g_getRecordCommands[5];
extern const char *g_bulletKindNames[9];
extern const char *g_attributeNameDefault[1];
extern const char *g_attributeNames[4];
extern const FloatingNumberStyleData g_floatingNumberStyles[5];
extern const float g_vec3ZAxis[4];
extern unsigned char g_mdlDmgTurn[4];
extern unsigned char g_cardFolderSetValue;
extern unsigned char g_cardFolderClearValue;
extern unsigned char g_shinkaSetValue;
extern unsigned char g_flagFlipOffValue;
extern unsigned char g_flagFlipOnValue;

/* Result strings the string getters return. */
extern char g_mdlPosStrBuffer[64];
extern char g_mdlRotStrBuffer[64];
extern char g_playerDataStrBuffer[64];
extern char g_playerPosStrBuffer[64];

extern const char Can_t_find_method_s_s[];
extern const char text_be[];
extern const char text_igInfoManager[];
extern const char Bec[];
extern const char GAMERAM[];
extern const char GETCOMMON[];
extern const char ISUSE[];
extern const char DIGIMONNAME[];
extern const char POWERSOCKETNAME_4[];
extern const char NINZU[];
extern const char DIFFICULTY[];
extern const char CAMERAMODE[];
extern const char LIGHTMODE[];
extern const char GATESTAGENAME[];
extern const char GATESTAGENO[];
extern const char EMPTY[];
extern const char DEVICE[];
extern const char CTRLITEM[];
extern const char DISK[];
extern const char FLAG[];
extern const char BIT[];
extern const char LEVEL[];
extern const char DIGIMONNO[];
extern const char BASE_ISUSE_4[];
extern const char CARDLIST_2[];
extern const char KAZU[];
extern const char SET_3[];
extern const char CLR_4[];
extern const char GETEXP[];
extern const char BASE_EXP_3[];
extern const char GETLEVEL[];
extern const char BASE_LEVEL_3[];
extern const char SETSHINKA[];
extern const char CTRLPLAYER[];
extern const char text_vec3Format[];
extern const char text_ne0[];
extern const char text_eq1[];
extern const char text_eq0[];
extern const char text_ne1[];
extern const char SUBWND_3[];
extern const char ISRUN_6[];
extern const char COUNTER_2[];
extern const char V_f_f_f[];
extern const char MODELCTRL_9[];
extern const char FIND_SPACE_2[];
extern const char GENERATE_8[];
extern const char NUMBERCTRL_3[];
extern const char SETVALUE_3[];
extern const char ONE_7[];
extern const char CHECKSTATUS[];
extern const char PLAYERPOINT[];
extern const char GETGENERATEPOS[];
extern const char GETMATRIXDIRECT[];
extern const char V_f_f_f_V_0_f_0[];
extern const char PLAYER_7[];
extern const char GETMATRIX_4[];
extern const char ENEMY[];
extern const char GETPEBASEWORK[];
extern const char FIGHTCALC[];
extern const char P2EISHITCHECK[];
extern const char P2EISCRITICAL[];
extern const char P2EDAMAGE[];
extern const char P2ESTUNTIME[];
extern const char P2EPOISONTIME[];
extern const char P2ESLEEPTIME[];
extern const char P2EBINDTIME[];
extern const char P2EATKDWNTIME[];
extern const char P2EPOWDWNTIME[];
extern const char P2ESKILLUP[];
extern const char P2EEXPUP[];
extern const char E2PISHITCHECK[];
extern const char E2PDAMAGE[];
extern const char GETPATKZOKUSEI[];
extern const char E2PDAMAGERANK[];
extern const char E2PSTUNTIME[];
extern const char E2PPOISONTIME[];
extern const char E2PSLEEPTIME[];
extern const char E2PBINDTIME[];
extern const char E2PATKDWNTIME[];
extern const char E2PPOWDWNTIME[];
extern const char P2PKOUKAMAGIC[];
extern const char LOADINTF2[];
extern const char SETDIFFICULTMAX[];
}

/* The game's string pool, created on first use. */
static inline void *stringPool(void) {
    if (g_stringPool[0] == 0) {
        void *pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return g_stringPool[0];
}

/* Points a string field at the pooled copy of `text`, releasing the string it held. */
static inline void setPooledString(int &field, const char *text) {
    char *token = (char *)StringPool_Intern(stringPool(), text);
    releaseString((char *)field);
    field = (int)token;
}

/* Points a property record's string at the pooled copy of `text`, releasing the one it held. */
static inline void setRecordString(beDataObjString *record, const char *text) {
    char *token = (char *)StringPool_Intern(stringPool(), text);
    releaseString((char *)record->_data);
    record->_data = (int)token;
}

/* Empties a string list, releasing its strings. */
static inline void clearStringList(igStringRefList *list) {
    int count;
    int i;
    char **slot;
    char *empty;
    int offset;
    count = list->_count;
    i = 0;
    if (0 < count) {
        offset = 0;
        do {
            slot = (char **)((char *)list->_data + offset);
            empty = (char *)StringPool_Intern(stringPool(), 0);
            releaseString(*slot);
            i += 1;
            *slot = empty;
            offset += 4;
        } while (i < count);
    }
    list->_count = 0;
}

/* The allocator an object's new members come from: its own, or the default one. */
static inline int allocatorFor(void *object) {
    int allocator = (int)igObject_GetAllocator(object);
    return g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
}

int LuaAPI_Dispatch(lua_State *L) {
    LuaFunction *function = (LuaFunction *)lua_touserdata(L, -1);
    LuaValue *args;
    if (function->argCount) args = (LuaValue *)lua_touserdata(L, -2); else args = 0;
    switch (function->id) {
    case 0:
        lua_pushnumber(L, (unsigned int)SYSisJoinPlayer(args[0].data.i)); return 1;
    case 1:
        LuaType_PushString(&function->result, L, SYSgetPlayerName(args[0].data.i)); return 1;
    case 2:
        lua_pushnumber(L, SYSgetPlayerNinzu()); return 1;
    case 3:
        LuaType_PushString(&function->result, L, SYSgetWeaponName(args[0].data.i, args[1].data.i)); return 1;
    case 4:
        lua_pushnumber(L, (int)SYSgetRandom(args[0].data.i)); return 1;
    case 5:
        lua_pushnumber(L, SYSgetDifficulty()); return 1;
    case 6:
        SYSsetDifficulty(args[0].data.i); return 0;
    case 7:
        lua_pushnumber(L, SYSgetCameraMode()); return 1;
    case 8:
        lua_pushnumber(L, SYSgetLightMode()); return 1;
    case 9:
        lua_pushnumber(L, SYSgetArea()); return 1;
    case 10:
        lua_pushnumber(L, SYSgetCountry()); return 1;
    case 11:
        lua_pushnumber(L, SYSgetTarget()); return 1;
    case 12:
        lua_pushnumber(L, SYSgetIsPackOnly()); return 1;
    case 13:
        SYSsetGateStage(args[0].data.string, args[1].data.i); return 0;
    case 14:
        LuaType_PushString(&function->result, L, SYSgetGateStageName()); return 1;
    case 15:
        lua_pushnumber(L, SYSgetGateStageNo()); return 1;
    case 16:
        lua_pushnumber(L, (unsigned int)SYSctlDeviceFolder(args[0].data.string, args[1].data.i, args[2].data.string, args[3].data.i, args[4].data.i, args[5].data.i)); return 1;
    case 17:
        lua_pushnumber(L, (unsigned int)SYSctlDiskFolder(args[0].data.string, args[1].data.i, args[2].data.i, args[3].data.i)); return 1;
    case 18:
        lua_pushnumber(L, (unsigned int)SYSctlFlagFolder(args[0].data.string, args[1].data.i)); return 1;
    case 19:
        lua_pushnumber(L, SYSgetPlayerLevel(args[0].data.i)); return 1;
    case 20:
        lua_pushnumber(L, SYSgetPlayerDigimon(args[0].data.i)); return 1;
    case 21:
        lua_pushnumber(L, (unsigned int)SYSisGetShinkaDigimon(args[0].data.i, args[1].data.i)); return 1;
    case 22:
        lua_pushnumber(L, SYSctlCardFolder(args[0].data.string, args[1].data.i)); return 1;
    case 23:
        lua_pushnumber(L, SYSctlBit(args[0].data.string, args[1].data.i, args[2].data.i)); return 1;
    case 24:
        lua_pushnumber(L, SYSctlShinka(args[0].data.string, args[1].data.i, args[2].data.i)); return 1;
    case 25:
        lua_pushnumber(L, SYSctlPlayer(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.i)); return 1;
    case 26:
        CFLclear(); return 0;
    case 27:
        CFLsetName(args[0].data.string); return 0;
    case 28:
        LuaType_PushString(&function->result, L, CFLgetFolderName()); return 1;
    case 29:
        sd_29(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.string); return 0;
    case 30:
        sd_30(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string); return 0;
    case 31:
        sd_31(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.string, args[5].data.ll); return 0;
    case 32:
        sd_32(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.ll); return 0;
    case 33:
        lua_pushnumber(L, (unsigned int)MATisPlayer()); return 1;
    case 34:
        lua_pushnumber(L, (unsigned int)MATisAllPlayer()); return 1;
    case 35:
        lua_pushnumber(L, MATgetPlayerNo()); return 1;
    case 36:
        lua_pushnumber(L, (int)MATisRidePlayer(args[0].data.i)); return 1;
    case 37:
        lua_pushnumber(L, (int)MATisRideOffPlayer(args[0].data.i)); return 1;
    case 38:
        lua_pushnumber(L, MATgetPlayerMatStat(args[0].data.i)); return 1;
    case 39:
        MATsetRun(args[0].data.uc); return 0;
    case 40:
        DMsetSD_40(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.string, args[5].data.ll); return 0;
    case 41:
        DMsetSD_41(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.string); return 0;
    case 42:
        DMsetSD_42(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.ll); return 0;
    case 43:
        DMsetSD_43(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string); return 0;
    case 44:
        DMchkSD_44(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.string, args[5].data.string); return 0;
    case 45:
        DMchkSD_45(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.string); return 0;
    case 46:
        DMswtSD_46(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string, args[4].data.string); return 0;
    case 47:
        DMswtSD_47(args[0].data.string, args[1].data.string, args[2].data.i, args[3].data.string); return 0;
    case 48:
        DMswtEnd(); return 0;
    case 49:
        DMcase(args[0].data.i); return 0;
    case 50:
        DMsetLua(args[0].data.string); return 0;
    case 51:
        DMmsgBox(args[0].data.string, args[1].data.i); return 0;
    case 52:
        DMrun(); return 0;
    case 53:
        lua_pushnumber(L, DMgetCount()); return 1;
    case 54:
        lua_pushnumber(L, (unsigned int)FLGisOn(args[0].data.i)); return 1;
    case 55:
        FLGset(args[0].data.i, args[1].data.uc); return 0;
    case 56:
        FLGflip(args[0].data.i); return 0;
    case 57:
        COUNTERset(args[0].data.i, args[1].data.i); return 0;
    case 58:
        lua_pushnumber(L, COUNTERget(args[0].data.i)); return 1;
    case 59:
        LuaType_PushString(&function->result, L, MDLgetInfoName()); return 1;
    case 60:
        lua_pushnumber(L, MDLgetRamNo()); return 1;
    case 61:
        lua_pushnumber(L, MDLgetRecNo()); return 1;
    case 62:
        lua_pushnumber(L, MDLgetMHp()); return 1;
    case 63:
        lua_pushnumber(L, MDLgetHp()); return 1;
    case 64:
        LuaType_PushString(&function->result, L, MDLgetPosStr(args[0].data.f, args[1].data.f, args[2].data.f)); return 1;
    case 65:
        LuaType_PushString(&function->result, L, MDLgetRotStr(args[0].data.f, args[1].data.f, args[2].data.f)); return 1;
    case 66:
        MDLaddHp(args[0].data.i); return 0;
    case 67:
        MDLsetSeq(args[0].data.string); return 0;
    case 68:
        MDLsetSD(args[0].data.string, args[1].data.string); return 0;
    case 69:
        lua_pushnumber(L, (unsigned int)MDLisLive(args[0].data.string, args[1].data.i)); return 1;
    case 70:
        lua_pushnumber(L, MDLgetBulletKind()); return 1;
    case 71:
        LuaType_PushString(&function->result, L, MDLgetBulletName()); return 1;
    case 72:
        lua_pushnumber(L, MDLgetBulletBoxNo()); return 1;
    case 73:
        MDLdspDamage(args[0].data.i); return 0;
    case 74:
        MDLdspDamageP(args[0].data.i); return 0;
    case 75:
        MDLdspExp(args[0].data.i); return 0;
    case 76:
        MDLsetDMGTurn(args[0].data.i); return 0;
    case 77:
        lua_pushnumber(L, (unsigned int)MDLisCallName(args[0].data.string)); return 1;
    case 78:
        MDLsetWorldPosTarget_78(args[0].data.f, args[1].data.f, args[2].data.f); return 0;
    case 79:
        MDLsetWorldPosTarget_79(args[0].data.string); return 0;
    case 80:
        lua_pushnumber(L, MDLgetKyoriSquare(args[0].data.f, args[1].data.f, args[2].data.f)); return 1;
    case 81:
        lua_pushnumber(L, (unsigned int)MDLisSeqName(args[0].data.string)); return 1;
    case 82:
        lua_pushnumber(L, (unsigned int)MDLisStatus(args[0].data.string, args[1].data.i, args[2].data.string)); return 1;
    case 83:
        lua_pushnumber(L, (unsigned int)BLTisPlayerBullet()); return 1;
    case 84:
        lua_pushnumber(L, BLTgetShootRamNo()); return 1;
    case 85:
        lua_pushnumber(L, (unsigned int)BLTisHitCheck()); return 1;
    case 86:
        lua_pushnumber(L, BLTgetDamageValue(args[0].data.uc)); return 1;
    case 87:
        lua_pushnumber(L, BLTgetDamageRank(args[0].data.i, args[1].data.uc)); return 1;
    case 88:
        lua_pushnumber(L, (unsigned int)BLTisCritical()); return 1;
    case 89:
        lua_pushnumber(L, BLTgetStunTime(args[0].data.i, args[1].data.uc)); return 1;
    case 90:
        lua_pushnumber(L, BLTgetPoisonTime(args[0].data.string)); return 1;
    case 91:
        lua_pushnumber(L, BLTgetSleepTime()); return 1;
    case 92:
        lua_pushnumber(L, BLTgetBindTime()); return 1;
    case 93:
        lua_pushnumber(L, BLTgetAttackDownTime(args[0].data.string)); return 1;
    case 94:
        lua_pushnumber(L, BLTgetPowerDownTime(args[0].data.string)); return 1;
    case 95:
        BLTcalcSkillUp(args[0].data.uc, args[1].data.uc); return 0;
    case 96:
        lua_pushnumber(L, BLTcalcEXPUp()); return 1;
    case 97:
        LuaType_PushString(&function->result, L, BLTgetAttributeStr()); return 1;
    case 98:
        lua_pushnumber(L, (unsigned int)BLPisHitCheck()); return 1;
    case 99:
        lua_pushnumber(L, BLPgetDamageValue()); return 1;
    case 100:
        LuaType_PushString(&function->result, L, BLPgetAttackZokusei()); return 1;
    case 101:
        lua_pushnumber(L, BLPgetDamageRank(args[0].data.i, args[1].data.i)); return 1;
    case 102:
        lua_pushnumber(L, BLPgetStunTime(args[0].data.i, args[1].data.i)); return 1;
    case 103:
        lua_pushnumber(L, BLPgetPoisonTime(args[0].data.string)); return 1;
    case 104:
        lua_pushnumber(L, BLPgetSleepTime()); return 1;
    case 105:
        lua_pushnumber(L, BLPgetBindTime()); return 1;
    case 106:
        lua_pushnumber(L, BLPgetAttackDownTime(args[0].data.string)); return 1;
    case 107:
        lua_pushnumber(L, BLPgetPowerDownTime(args[0].data.string)); return 1;
    case 108:
        lua_pushnumber(L, BLPcalcKoukaMagic()); return 1;
    case 109:
        lua_pushnumber(L, TXTgetCallNo()); return 1;
    case 110:
        lua_pushnumber(L, PLAYERgetPos()); return 1;
    case 111:
        LuaType_PushString(&function->result, L, PLAYERgetDataStr(args[0].data.i, args[1].data.i, args[2].data.f)); return 1;
    case 112:
        LuaType_PushString(&function->result, L, PLAYERgetPosStr(args[0].data.i, args[1].data.f, args[2].data.f, args[3].data.f)); return 1;
    case 113:
        LISsetDifficultMax(args[0].data.i); return 0;
    case 114:
        MsgBox(args[0].data.string, args[1].data.i); return 0;
    case 115:
        ShutDown(); return 0;
    default:
        LuaError(Can_t_find_method_s_s, function->owner->name, function->name);
        return 0;
    }
}

LuaAPIClass::LuaAPIClass() : LuaClass(text_be, text_igInfoManager, 0, 0, 0, 0, 0) {
    vtable = g_LuaAPIClass_vtable;
}

/* The start-up hook's factory for the `be` class. */
LuaClass *LuaAPIClass_Create(void) {
    be_EnsureRegistered();
    return new (g_luaGluePool) LuaAPIClass;
}

BecLuaClass::BecLuaClass() : LuaClass(Bec, 0, 0, 0, 0, 0, 0) {
    vtable = g_BecLuaClass_vtable;
}

/* The start-up hook's factory for the `Bec` class. */
LuaClass *BecLuaClass_Create(void) {
    return new (g_luaGluePool) BecLuaClass;
}

/* The game's per-library class registration; this file registers no reflected class. */
void LuaAPI_RegisterClasses(void)
{
}

void LuaAPI_Register(LuaClass *luaClass) {
    LuaClass_BindFunctions(luaClass, 0, LuaAPI_Dispatch, g_luaApiFunctionNames,
                           sizeof(g_luaApiFunctionNames) / sizeof(g_luaApiFunctionNames[0]),
                           g_luaApiFunctionCodes, 0);
}

void be_AddToScheduler(void)
{
}

void be_RemoveFromScheduler(void)
{
}

/* Finds the managers the script functions talk to and records itself as the game's be. */
void be_Start(be *self) {
    int demoManager;

    g_beSystem[0] = (beSystem *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]);
    g_beMessenger[0] = (beMessenger *)igInsightCore_FindManager(self->_insight, g_beMessenger_metaObject[0]);
    g_matCtrl[0] = (beMatCtrl *)igInsightCore_FindManager(self->_insight, g_beMatCtrl_metaObject[0]);
    demoManager = igInsightCore_FindManager(self->_insight, g_beDemoManager_metaObject[0]);
    g_be[0] = self;
    g_beDemoManager[0] = (beDemoManager *)demoManager;
}

void be_Stop(void)
{
}

/* Keeps no info the insight core offers. */
int be_AcceptInfo(void) {
    return 0;
}

/* Empties the be's string list. */
void be_Reset(void) {
    clearStringList((igStringRefList *)g_be[0]->_stringRefList);
    {
        igStringRefList *list = (igStringRefList *)g_be[0]->_stringRefList;
        if (!(0 < list->_count)) {
            List_Reserve(list, 0, 4);
        }
    }
}

void be_Update(void)
{
}

/* Asks GAMERAM for a property record: the shared one (PLAYER_SLOT_COMMON) or a player's. */
int bePlayer_GetStruct(int slot) {
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, g_getRecordCommands[slot]);
    return beMessenger_GetObject(g_beMessenger[0], 0);
}

unsigned char SYSisJoinPlayer(int playerIndex) {
    return igProperty_GetRecordByte(bePlayer_GetStruct(playerIndex + 1), ISUSE)->_data;
}

const char *SYSgetPlayerName(int playerIndex) {
    return (const char *)igProperty_GetRecordString(bePlayer_GetStruct(playerIndex + 1), DIGIMONNAME)->_data;
}

/* The name of a player's power-socket weapon, or 0 past the end of the list. */
const char *SYSgetWeaponName(int playerIndex, int slot) {
    const char *name;
    igStringRefList *list;

    list = (igStringRefList *)igProperty_GetRecordStringList(bePlayer_GetStruct(playerIndex + 1), POWERSOCKETNAME_4)->_data;
    if (list->_count <= slot) {
        return 0;
    }
    {
        StringRef copy = StringList_CopyRetained(list, slot);
        name = (const char *)copy.p;
    }
    return name;
}

/* NINZU: "number of people", the joined-player count. */
int SYSgetPlayerNinzu(void) {
    return igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), NINZU)->_data;
}

int SYSgetDifficulty(void) {
    return igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), DIFFICULTY)->_data;
}

void SYSsetDifficulty(int difficulty) {
    igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), DIFFICULTY)->_data = difficulty;
}

int SYSgetCameraMode(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return igProperty_GetRecord(beMessenger_GetObject(g_beMessenger[0], 0), CAMERAMODE)->_data;
}

int SYSgetLightMode(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return igProperty_GetRecord(beMessenger_GetObject(g_beMessenger[0], 0), LIGHTMODE)->_data;
}

int SYSgetArea(void)
{
    return 1;
}

int SYSgetCountry(void)
{
    return 1;
}

int SYSgetTarget(void)
{
    return 1;
}

int SYSgetIsPackOnly(void)
{
    return 1;
}

/* The game's only random-number entry point: genrand() % range. */
unsigned int SYSgetRandom(unsigned int range) {
    return ((RandomNumberDispatch *)g_beSystem[0]->_random)->genrand() % range;
}

/* Records the gate stage; a null name stores the empty string. */
void SYSsetGateStage(const char *stageName, int stageNo) {
    int common;

    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    common = beMessenger_GetObject(g_beMessenger[0], 0);
    igProperty_GetRecord(common, GATESTAGENO)->_data = stageNo;
    if (stageName == 0) {
        setRecordString(igProperty_GetRecordString(common, GATESTAGENAME), EMPTY);
        return;
    }
    setRecordString(igProperty_GetRecordString(common, GATESTAGENAME), stageName);
}

const char *SYSgetGateStageName(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return (const char *)igProperty_GetRecordString(beMessenger_GetObject(g_beMessenger[0], 0), GATESTAGENAME)->_data;
}

int SYSgetGateStageNo(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return igProperty_GetRecord(beMessenger_GetObject(g_beMessenger[0], 0), GATESTAGENO)->_data;
}

/* GAMERAM CTRLITEM requests: a kind, a command, an item database, then four integers. */
unsigned char SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], DEVICE);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], itemDb);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], itemId);
    beMessenger_AppendInt(g_beMessenger[0], extra0);
    beMessenger_AppendInt(g_beMessenger[0], extra1);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

unsigned char SYSctlDiskFolder(const char *command, int index, int itemId, int count) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], DISK);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], EMPTY);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], itemId);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], count);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

unsigned char SYSctlFlagFolder(const char *command, int index) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], FLAG);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], EMPTY);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

int SYSctlBit(const char *command, int index, int value) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], BIT);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], EMPTY);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], value);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int SYSgetPlayerLevel(int playerIndex) {
    return igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), LEVEL)->_data;
}

int SYSgetPlayerDigimon(int playerIndex) {
    return igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), DIGIMONNO)->_data;
}

/* SHINKA: "evolution". Whether the player has obtained the species (BASE_ISUSE). */
unsigned char SYSisGetShinkaDigimon(int playerIndex, int species)
{
    igBoolList *obtained = (igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(playerIndex + 1), BASE_ISUSE_4)->_data;
    return *(unsigned char *)(obtained->_data + species);
}

/* The first player's card list: KAZU counts the cards held, SET and CLR take or give back the
 * card at `index` and report whether it changed. */
int SYSctlCardFolder(const char *command, int index) {
    igBoolList *cards = (igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(PLAYER_SLOT_FIRST), CARDLIST_2)->_data;
    if (strcmp(command, KAZU) == 0) {
        int count = cards->_count;
        int total = 0;
        int i;
        for (i = 0; i < count; i++) {
            if (((unsigned char *)cards->_data)[i] == 1) total += 1;
        }
        return total;
    }
    if (strcmp(command, SET_3) == 0) {
        unsigned char *card = (unsigned char *)cards->_data + index;
        if (*card != 0) return 0;
        if (cards->_count != 0 && index >= 0 && index < cards->_count) *card = g_cardFolderSetValue;
        return 1;
    }
    if (strcmp(command, CLR_4) == 0) {
        unsigned char *card = (unsigned char *)cards->_data + index;
        if (*card == 0) return 0;
        if (cards->_count != 0 && index >= 0 && index < cards->_count) *card = g_cardFolderClearValue;
        return 1;
    }
    return 0;
}

/* A player's evolution species: GETEXP and GETLEVEL read its experience and level (-1 when not
 * obtained), SETSHINKA marks it obtained and reports whether it was new. */
int SYSctlShinka(const char *command, int playerIndex, int species) {
    int obtained;
    int result;
    igBoolList *obtainedList;
    unsigned char *obtainedFlags;
    obtainedFlags = (unsigned char *)((igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(playerIndex + 1), BASE_ISUSE_4)->_data)->_data; /* matching construct: byte base held in a pointer local keeps the retail operand order of the index add */
    obtained = obtainedFlags[species];
    if (strcmp(command, GETEXP) == 0) {
        if (obtained != 0) result = ((int *)((igIntList *)igProperty_GetRecordIntList(bePlayer_GetStruct(playerIndex + 1), BASE_EXP_3)->_data)->_data)[species];
        else result = -1;
    } else if (strcmp(command, GETLEVEL) == 0) {
        if (obtained != 0) result = ((int *)((igIntList *)igProperty_GetRecordIntList(bePlayer_GetStruct(playerIndex + 1), BASE_LEVEL_3)->_data)->_data)[species];
        else result = -1;
    } else if (strcmp(command, SETSHINKA) == 0) {
        if (obtained != 0) result = 0;
        else {
            obtainedList = (igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(playerIndex + 1), BASE_ISUSE_4)->_data;
            if (obtainedList->_count != 0 && species >= 0 && species < obtainedList->_count) ((unsigned char *)obtainedList->_data)[species] = g_shinkaSetValue;
            result = 1;
        }
    } else result = 0;
    return result;
}

/* GAMERAM CTRLPLAYER request: a property, a command, a player and a value. */
int SYSctlPlayer(const char *property, const char *command, int playerIndex, int value) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], property);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendInt(g_beMessenger[0], playerIndex);
    beMessenger_AppendInt(g_beMessenger[0], value);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLPLAYER);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* CFL: the system's list of files read for the stage. */
void CFLclear(void) {
    clearStringList((igStringRefList *)g_beSystem[0]->_readFileList);
    {
        igStringRefList *list = (igStringRefList *)g_beSystem[0]->_readFileList;
        if (!(0 < list->_count)) {
            List_Reserve(list, 0, 4);
        }
    }
}

/* Adds a name to the read-file list unless it is already there. */
void CFLsetName(const char *name) {
    const char *pooled;
    igStringRefList *list;
    int count;
    bool found;
    int i;

    found = false;
    list = (igStringRefList *)g_beSystem[0]->_readFileList;
    count = list->_count;
    i = 0;
    if (0 < count) {
    do {
        {
            StringRef entry = StringList_CopyRetained(list, i);
            if (strcmp((const char *)entry.p, name) == 0) {
                found = true;
                break;
            }
        }
        i++;
    } while (i < count);
    }
    if (!((int)found & 0xff)) {
        if (name == 0) {
            pooled = 0;
        } else {
            pooled = (const char *)StringPool_Intern(stringPool(), name);
        }
        {
            StringRef entry((void *)pooled);
            StringList_AppendRetained(list, &entry);
        }
    }
}

const char *CFLgetFolderName(void) {
    return (const char *)g_beSystem[0]->_stageName;
}

/* Appends sd's argument string to the selected message. The string is '/'-separated; a part of
 * the form X<...> is a typed value (I<int>, L<long>, V<vector>, F<float>), any other part a
 * string. */
void Lua_sd_OptionalArg(const char *args) {
    char *parts[12];
    char buffer[1024];
    float parsed[3];
    float vector[3];
    float floatValue;
    char *out;
    char *part;
    int c;
    int intValue;
    bool negative;
    int k;
    long long longValue;
    int partCount;
    int i;
    igStringObj *text;
    char **cursor;
    char *in;

    if (*args != 0) {
        in = (char *)args;
        if (strlen(in) > sizeof(buffer)) {
            in[sizeof(buffer) - 1] = 0;
        }
        partCount = 0;
        out = buffer;
        parts[partCount++] = out;
        cursor = &parts[0];
        for (;;) {
            c = *in;
            if (c == 0) {
                *out = 0;
                break;
            }
            if (c == '/') {
                *out = 0;
                in++;
                out++;
                parts[partCount++] = out;
            } else {
                *out = c;
                in++;
                out++;
            }
        }
        {
            for (i = 0; i < partCount; i++, cursor++) {
                part = *cursor;
                if (part[1] != '<') {
                    beMessenger_AppendString(g_beMessenger[0], part);
                } else {
                    switch (part[0]) {
                    case 'I':
                        intValue = 0;
                        negative = false;
                        k = 2;
                        if (part[2] == '-') {
                            negative = true;
                            k++;
                        }
                        while (part[k] != '>') {
                            intValue = intValue * 10;
                            intValue += part[k] - '0';
                            k++;
                        }
                        if (negative) intValue = -intValue;
                        beMessenger_AppendInt(g_beMessenger[0], intValue);
                        break;
                    case 'L':
                        longValue = 0;
                        k = 2;
                        while (part[k] != '>') {
                            longValue = longValue * 10;
                            longValue += part[k] - '0';
                            k++;
                        }
                        beMessenger_AppendLong(g_beMessenger[0], longValue);
                        break;
                    case 'V':
                        Vec3f_FromString(part + 1, parsed, text_vec3Format);
                        vector[0] = parsed[0];
                        vector[1] = parsed[1];
                        vector[2] = parsed[2];
                        beMessenger_AppendVec3(g_beMessenger[0], vector);
                        break;
                    case 'F':
                        text = (igStringObj *)g_beSystem[0]->_globalStrObj;
                        igStringObj_Set(text, part + 2);
                        igStringObj_Erase(text, text->_length - 1, 1);
                        igStringObj_ToFloat(text, &floatValue);
                        beMessenger_AppendFloat(g_beMessenger[0], floatValue);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

/* sd: send a message to the receivers a group, info name and ram number select, with an
 * optional argument string (Lua_sd_OptionalArg) and, for the delayed forms, a delay. */
void sd_29(const char *group, const char *infoName, int ramNo, const char *message, const char *args) {
    beMessenger_SelectReceivers(g_beMessenger[0], group, infoName, ramNo);
    if (args != 0) {
        Lua_sd_OptionalArg(args);
    }
    beMessenger_DispatchSelected(g_beMessenger[0], message);
}

void sd_30(const char *group, const char *infoName, int ramNo, const char *message) {
    beMessenger_SendNamed(g_beMessenger[0], group, infoName, ramNo, message);
}

void sd_31(const char *group, const char *infoName, int ramNo, const char *message, const char *args, long long delay) {
    beMessenger_PrepareDelayedSelection(g_beMessenger[0], group, infoName, ramNo);
    if (args != 0) {
        Lua_sd_OptionalArg(args);
    }
    beMessenger_EnqueueSelected(g_beMessenger[0], message, delay);
}

void sd_32(const char *group, const char *infoName, int ramNo, const char *message, long long delay) {
    beMessenger_SendDelayedNamed(g_beMessenger[0], group, infoName, ramNo, message, delay);
}

unsigned char MATisPlayer(void) { return beMatCtrl_IsPlayer(g_matCtrl[0]); }

unsigned char MATisAllPlayer(void) { return beMatCtrl_IsAllPlayer(g_matCtrl[0]); }

int MATgetPlayerNo(void) { return beMatCtrl_GetPlayerNo(g_matCtrl[0]); }

unsigned char MATisRidePlayer(int player) { return beMatCtrl_IsRidePlayer(g_matCtrl[0], player); }

unsigned char MATisRideOffPlayer(int player) { return beMatCtrl_IsRideOffPlayer(g_matCtrl[0], player); }

int MATgetPlayerMatStat(int player) { return beMatCtrl_GetPlayerMatStat(g_matCtrl[0], player); }

void MATsetRun(int run) { beMatCtrl_SetRun(g_matCtrl[0], run); }

/* DM: queue messages on the demo manager's build data; DMrun hands the queue over to play. */
void DMsetSD_40(const char *group, const char *infoName, int ramNo, const char *message, const char *param, long long sendTime) {
    beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND, group, infoName, ramNo, message, param, sendTime);
}

void DMsetSD_41(const char *group, const char *infoName, int ramNo, const char *message, const char *param) {
    beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND, group, infoName, ramNo, message, param, 0);
}

void DMsetSD_42(const char *group, const char *infoName, int ramNo, const char *message, long long sendTime) {
    beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND, group, infoName, ramNo, message, 0, sendTime);
}

void DMsetSD_43(const char *group, const char *infoName, int ramNo, const char *message)
{
    beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND, group, infoName, ramNo, message, 0, 0);
}

/* A wait: the message is sent again every update while its bool reply meets the condition ("!=0" and
 * "==1" wait out a true reply, "==0" and "!=1" a false one). */
void DMchkSD_44(const char *group, const char *infoName, int ramNo, const char *message, const char *param, const char *condition) {
    if (strcmp(text_ne0, condition) == 0 || strcmp(text_eq1, condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND_UNTIL_FALSE, group, infoName, ramNo, message, param, 0);
    } else if (strcmp(text_eq0, condition) == 0 || strcmp(text_ne1, condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND_UNTIL_TRUE, group, infoName, ramNo, message, param, 0);
    }
}

void DMchkSD_45(const char *group, const char *infoName, int ramNo, const char *message, const char *condition) {
    if (strcmp(text_ne0, condition) == 0 || strcmp(text_eq1, condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND_UNTIL_FALSE, group, infoName, ramNo, message, 0, 0);
    } else if (strcmp(text_eq0, condition) == 0 || strcmp(text_ne1, condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager[0], DEMO_MES_SEND_UNTIL_TRUE, group, infoName, ramNo, message, 0, 0);
    }
}

void DMsetLua(const char *chunk)
{
    beDemoManager_SetLua(g_beDemoManager[0], chunk);
}

void DMmsgBox(const char *text, int ramNo) {
    beDemoManager_MsgBox(g_beDemoManager[0], text, ramNo);
}

void DMswtSD_46(const char *group, const char *infoName, int ramNo, const char *message, const char *param) {
    beDemoManager_SwitchSD(g_beDemoManager[0], group, infoName, ramNo, message, param);
}

void DMswtSD_47(const char *group, const char *infoName, int ramNo, const char *message) {
    beDemoManager_SwitchSD(g_beDemoManager[0], group, infoName, ramNo, message, 0);
}

void DMswtEnd(void)
{
    beDemoManager_SwitchEnd(g_beDemoManager[0]);
}

void DMcase(int ramNo)
{
    beDemoManager_Case(g_beDemoManager[0], ramNo);
}

void DMrun(void)
{
    beDemoManager_Run(g_beDemoManager[0]);
}

/* The number of queued demos; with none queued, -1 while the SUBWND window runs, else 0. */
int DMgetCount(void) {
    int count;
    count = ((beDemoManagerWorkList *)g_beDemoManager[0]->_activeDataList)->_count;
    if (count != 0) { return count; }
    beMessenger_SendNamed(g_beMessenger[0], SUBWND_3, 0, 0, ISRUN_6);
    if (beMessenger_GetBoolCount(g_beMessenger[0]) == 0) { return 0; }
    count = beMessenger_GetBool(g_beMessenger[0], 0);
    count = (count & 0xFF) != 0;
    return -count;
}

/* FLG / COUNTER: the shared record's FLAG bool list and COUNTER int list. */
unsigned char FLGisOn(int flagNo) {
    int common;

    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    common = beMessenger_GetObject(g_beMessenger[0], 0);
    if (flagNo == FLAG_PLAYERS_JOINED) {
        return SYSgetPlayerNinzu() != 0;
    }
    igBoolList *flags = (igBoolList *)igProperty_GetRecordArray(common, FLAG)->_data;
    return *(unsigned char *)(flags->_data + flagNo);
}

void FLGset(int flagNo, unsigned char on) {
    igBoolList *flags;
    int count;

    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    flags = (igBoolList *)igProperty_GetRecordArray(beMessenger_GetObject(g_beMessenger[0], 0), FLAG)->_data;
    count = flags->_count;
    if ((count != 0) && (flagNo >= 0) && (flagNo < count)) {
        *(char *)(flagNo + flags->_data) = on;
    }
}

void FLGflip(int flagNo) {
    int common;
    igBoolList *flags;
    int count;
    unsigned char *values;
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    common = beMessenger_GetObject(g_beMessenger[0], 0);
    values = (unsigned char *)((igBoolList *)igProperty_GetRecordArray(common, FLAG)->_data)->_data;
    if (values[flagNo] != 0) {
        flags = (igBoolList *)igProperty_GetRecordArray(common, FLAG)->_data;
        count = flags->_count;
        if (count != 0 && flagNo >= 0 && flagNo < count) {
            ((unsigned char *)flags->_data)[flagNo] = g_flagFlipOffValue;
        }
    } else {
        flags = (igBoolList *)igProperty_GetRecordArray(common, FLAG)->_data;
        count = flags->_count;
        if (count != 0 && flagNo >= 0 && flagNo < count) {
            ((unsigned char *)flags->_data)[flagNo] = g_flagFlipOnValue;
        }
    }
}

void COUNTERset(int counterNo, int value) {
    igIntList *counters;
    int count;
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    counters = (igIntList *)igProperty_GetRecordIntList(beMessenger_GetObject(g_beMessenger[0], 0), COUNTER_2)->_data;
    count = counters->_count;
    if ((count != 0) && (counterNo >= 0) && (counterNo < count)) {
        *(int *)(counters->_data + (counterNo * 4)) = value;
    }
}

int COUNTERget(int counterNo)
{
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    return ((int *)((igIntList *)igProperty_GetRecordIntList(beMessenger_GetObject(g_beMessenger[0], 0), COUNTER_2)->_data)->_data)[counterNo];
}

int MDLgetRamNo(void)
{
    return g_mdlRamNo[0];
}

const char *MDLgetInfoName(void)
{
    return g_mdlInfoName[0];
}

/* The model's position moved by a local offset, as "V<x,y,z>". */
char *MDLgetPosStr(float x, float y, float z) {
    float matrix[16];
    float offset[3];
    float position[3];

    igMatrix44f_SetIdentity(matrix);
    Matrix44_Copy(matrix, g_mdlMatrix[0]);
    offset[0] = x;
    offset[1] = y;
    offset[2] = z;
    Matrix44_TranslateLocal(matrix, offset);
    Matrix44_GetTranslation(matrix, position);
    sprintf(g_mdlPosStrBuffer, V_f_f_f, position[0], position[1], position[2]);
    return g_mdlPosStrBuffer;
}

/* A rotation as "V<x,y,z>": `y` turned by the model's heading, in degrees. */
char *MDLgetRotStr(float x, float y, float z) {
    float forward[4];
    float matrix[16];
    float heading;
    igMatrix44f_SetIdentity(matrix);
    Matrix44_Copy(matrix, g_mdlMatrix[0]);
    Vec3f_TransformDirection(forward, g_vec3ZAxis, matrix);
    heading = atan2f(forward[0], forward[2]);
    sprintf(g_mdlRotStrBuffer, V_f_f_f, x, RADIANS_TO_DEGREES * heading + y, z);
    return g_mdlRotStrBuffer;
}

int MDLgetMHp(void)
{
    return g_mdlMaxHp[0];
}

int MDLgetHp(void)
{
    return g_mdlHp[0];
}

void MDLaddHp(int amount) {
    g_mdlHp[0] = g_mdlHp[0] + amount;
    if (g_mdlHp[0] < 0) {
        g_mdlHp[0] = 0;
    }
}

void MDLsetSeq(const char *sequence)
{
    beMessenger_SendNamed(g_beMessenger[0], MODELCTRL_9, g_mdlInfoName[0], g_mdlRamNo[0], sequence);
}

void MDLsetSD(const char *message, const char *args)
{
    sd_29(MODELCTRL_9, g_mdlInfoName[0], g_mdlRamNo[0], message, args);
}

/* Whether any of the named models still runs. */
unsigned char MDLisLive(const char *infoName, int ramNo) {
    int count;
    bool live;
    int i;
    beMessenger_SendNamed(g_beMessenger[0], MODELCTRL_9, infoName, ramNo, ISRUN_6);
    count = beMessenger_GetBoolCount(g_beMessenger[0]);
    live = false;
    for (i = 0; i < count; i++) {
        if (beMessenger_GetBool(g_beMessenger[0], i)) {
            live = true;
            break;
        }
    }
    return live;
}

int MDLgetBulletKind(void)
{
    return g_mdlBulletKind[0];
}

const char *MDLgetBulletName(void) {
    return g_bulletKindNames[g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE];
}

int MDLgetBulletBoxNo(void)
{
    return g_mdlBulletBoxNo[0];
}

/* Pops a number up at the model: a free floating-number model plays the sequence for the digit
 * count at the model's position, and its number control shows the value (capped at 99999). */
void FloatingNumber_Spawn(int value, int style) {
    const char *modelInfoName = g_floatingNumberStyles[style].modelInfoName;
    const char *numberInfoName = g_floatingNumberStyles[style].numberInfoName;
    beBaseInfoRam *number;
    int digits;
    const char *sequence;
    float position[3];
    float at[3];
    beMessenger_SendNamed(g_beMessenger[0], MODELCTRL_9, modelInfoName, -1, FIND_SPACE_2);
    if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
        number = (beBaseInfoRam *)beMessenger_GetObject(g_beMessenger[0], 0);
        if (value < 10) digits = 0;
        else if (value < 100) digits = 1;
        else if (value < 1000) digits = 2;
        else if (value < 10000) digits = 3;
        else if (value < 100000) digits = 4;
        else { digits = 4; value = 99999; }
        sequence = g_floatingNumberStyles[style].digitSequences[digits];
        beMessenger_SelectReceivers(g_beMessenger[0], MODELCTRL_9, modelInfoName, number->_ramNo);
        beMessenger_AppendString(g_beMessenger[0], sequence);
        Matrix44_GetTranslation(g_mdlMatrix[0], position);
        at[0] = position[0]; at[1] = position[1]; at[2] = position[2];
        beMessenger_AppendVec3(g_beMessenger[0], at);
        beMessenger_DispatchSelected(g_beMessenger[0], GENERATE_8);
        beMessenger_SelectReceivers(g_beMessenger[0], NUMBERCTRL_3, numberInfoName, number->_ramNo);
        beMessenger_AppendInt(g_beMessenger[0], value);
        beMessenger_DispatchSelected(g_beMessenger[0], SETVALUE_3);
    }
}

void MDLdspDamage(int damage)
{
    FloatingNumber_Spawn(damage, FLOATING_NUMBER_DAMAGE);
}

void MDLdspDamageP(int damage)
{
    FloatingNumber_Spawn(damage, FLOATING_NUMBER_PLAYER_DAMAGE);
}

void MDLdspExp(int exp)
{
    FloatingNumber_Spawn(exp, FLOATING_NUMBER_EXP);
}

void MDLsetDMGTurn(int value) {
    g_mdlDmgTurn[0] = value == 1;
}

static inline int isZero(int value) { return value == 0; }

/* Whether the model was called by `name`; with no call name, whether `name` is null. */
unsigned char MDLisCallName(const char *name) {
    const char *callName = g_mdlCallName[0];
    if (callName == 0) return isZero((int)name);
    return isZero(strcmp(callName, name));
}

void MDLsetWorldPosTarget_78(float x, float y, float z) {
    float *target = g_mdlWorldPosTarget[0];
    if (target != 0) {
        target[0] = x;
        target[1] = y;
        target[2] = z;
    }
}

/* The same from a "V<x,y,z>" string. */
void MDLsetWorldPosTarget_79(const char *text) {
    float parsed[3];
    float x, y, z;
    float *target;

    if (g_mdlWorldPosTarget[0] != 0) {
        Vec3f_FromString(text, parsed, V_f_f_f);
        x = parsed[0]; z = parsed[2]; y = parsed[1];
        target = g_mdlWorldPosTarget[0];
        target[0] = x;
        target[1] = y;
        target[2] = z;
    }
}

/* KYORI: "distance". The squared distance from the model to a point. */
float MDLgetKyoriSquare(float x, float y, float z) {
    float position[3];
    float dx, dy, dz;
    Matrix44_GetTranslation(g_mdlMatrix[0], position);
    dy = position[1] - y;
    dx = position[0] - x;
    dz = position[2] - z;
    return dx * dx + dy * dy + dz * dz;
}

int MDLgetRecNo(void)
{
    return g_mdlRecNo[0];
}

/* Whether the model's current sequence is `sequence`; creates the model's data list if it has none. */
unsigned char MDLisSeqName(const char *sequence) {
    beBaseInfoRam *model = g_mdlEntity[0];
    if (model->_dataList == 0) {
        igObject *old;
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(allocatorFor(model)));
        igObject *list = created.get();
        if (list != 0) {
            list->_refCount = list->_refCount + 1;
        }
        old = (igObject *)model->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        model->_dataList = (int)list;
    }
    beModelCtrlInfoRamData *data = igProperty_FindByName(model->_dataList, g_propertyNameField[0], ONE_7);
    return strcmp((const char *)((beModelCtrlInfoWork *)data->_work)->_seqCodeName, sequence) == 0;
}

/* Asks the named model whether it is in a status (CHECKSTATUS); false without exactly one reply. */
unsigned char MDLisStatus(const char *infoName, int ramNo, const char *status) {
    beMessenger_SelectReceivers(g_beMessenger[0], MODELCTRL_9, infoName, ramNo);
    beMessenger_AppendString(g_beMessenger[0], status);
    beMessenger_DispatchSelected(g_beMessenger[0], CHECKSTATUS);
    if (beMessenger_GetBoolCount(g_beMessenger[0]) == 1) {
        return beMessenger_GetBool(g_beMessenger[0], 0);
    }
    return 0;
}

int PLAYERgetPos(void) {
    beMessenger_SendGroup(g_beMessenger[0], PLAYERPOINT, GETGENERATEPOS);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* A player point's position and heading, as "V<x,y,z>/V<0,heading,0>" with `yaw` added. */
char *PLAYERgetDataStr(int point, int index, float yaw) {
    float heading;
    float forward[3];
    float matrix[16];
    float position[3];
    beMessenger_SelectGroup(g_beMessenger[0], PLAYERPOINT);
    beMessenger_AppendInt(g_beMessenger[0], point);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_DispatchSelected(g_beMessenger[0], GETMATRIXDIRECT);
    beMessenger_GetMatrix(matrix, g_beMessenger[0], 0);
    Matrix44_GetTranslation(matrix, position);
    Vec3f_TransformDirection(forward, g_vec3ZAxis, matrix);
    heading = atan2f(forward[0], forward[2]);
    sprintf(g_playerDataStrBuffer, V_f_f_f_V_0_f_0, position[0], position[1], position[2], (RADIANS_TO_DEGREES * heading) + yaw);
    return g_playerDataStrBuffer;
}

/* A player model's position moved by a local offset, as "V<x,y,z>"; 0 when it has no matrix. */
char *PLAYERgetPosStr(int ramNo, float x, float y, float z) {
    float offset[3];
    float position[4];
    float matrix[16];

    beMessenger_SendNamed(g_beMessenger[0], PLAYER_7, 0, ramNo, GETMATRIX_4);
    if (beMessenger_GetMatrixCount(g_beMessenger[0]) != 0) {
        beMessenger_GetMatrix(matrix, g_beMessenger[0], 0);
        offset[0] = x;
        offset[1] = y;
        offset[2] = z;
        Matrix44_TranslateLocal(matrix, offset);
        Matrix44_GetTranslation(matrix, position);
        sprintf(g_playerPosStrBuffer, V_f_f_f, position[0], position[1], position[2]);
        return g_playerPosStrBuffer;
    }
    return 0;
}

void MsgBox(const char *, int)
{
}

/* Ends the game loop: no next stage. */
void ShutDown(void) {
    beSystem *system;
    system = g_beSystem[0];
    system->_isShutDown = 1;
    system->_isStageLoop = 0;
    setPooledString(system->_nextStage, 0);
}

int TXTgetCallNo(void)
{
    return g_txtCallNo[0];
}

/* True below 1000, for 10000..59999 and for 80000..89999. The cached code is signed and not range-
 * checked, so a negative code also counts. */
unsigned char BLTisPlayerBullet(void) {
    if (g_mdlBulletKind[0] < BULLET_KIND_GROUP_SIZE) {
        if (g_mdlBulletKind[0] < PLAYER_BULLET_WEAPON_END) {
            return 1;
        }
        /* The early return and this jump are not interchangeable with a plain `return 0`. */
        goto notPlayerBullet;
    }
    if (g_mdlBulletKind[0] < PLAYER_BULLET_RANGE_A_END) {
        return 1;
    }
    if ((g_mdlBulletKind[0] >= PLAYER_BULLET_RANGE_B_BEGIN) && (g_mdlBulletKind[0] < PLAYER_BULLET_RANGE_B_END)) {
        return 1;
    }
notPlayerBullet:
    return 0;
}

int BLTgetShootRamNo(void)
{
    return g_bltShootRamNo[0];
}

/* BLT: a player bullet hitting the cached model; BLP: an enemy bullet hitting the player. Each
 * asks FIGHTCALC through GAMERAM. */

/* Whether the cached player attack hits (P2EISHITCHECK). When the model has an info name, the
 * named ENEMY's base work (GETPEBASEWORK reply, object 1) goes with it. */
unsigned char BLTisHitCheck(void) {
    int baseWork;

    baseWork = 0;
    if (g_mdlInfoName[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_mdlInfoName[0], g_mdlRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EISHITCHECK);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendObject(g_beMessenger[0], (void *)baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

unsigned char BLTisCritical(void) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EISCRITICAL);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

/* P2EDAMAGE with the script's critical flag. The reply's three integers (damage, attribute
 * index, rank flag) are cached for BLTgetDamageRank and BLTgetAttributeStr, and the damage is
 * returned. */
int BLTgetDamageValue(unsigned char critical) {
    int baseWork;

    baseWork = 0;
    if (g_mdlInfoName[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_mdlInfoName[0], g_mdlRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EDAMAGE);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], critical);
    beMessenger_AppendObject(g_beMessenger[0], (void *)baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_damageResult[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 1);
    g_damageFlag[0] = beMessenger_GetInt(g_beMessenger[0], 2);
    return g_damageResult[0];
}

/* Damage rank 0..3 of the last BLTgetDamageValue result. `currentHp` is what the script passes
 * (BLTgetDamageRank(MDLgetHp(), ...)); a nonpositive value is rank 3. Otherwise the damage / max-
 * HP fraction picks rank 2 above one half, rank 1 above one quarter, else 0. A rank of 0 or 1 is
 * raised by one when the cached rank flag is 1 (rank 0 only), when `rankBonus` is set, or for
 * attack groups 2 and 3. */
int BLTgetDamageRank(int currentHp, unsigned char rankBonus) {
    float damageFraction;
    int group;
    int rank;

    if (currentHp <= 0) {
        return 3;
    }
    rank = 0;
    damageFraction = (float) g_damageResult[0] / (float) g_mdlMaxHp[0];
    if (!(damageFraction <= DAMAGE_RANK2_FRACTION)) {
        rank = 2;
    } else if (!(damageFraction <= DAMAGE_RANK1_FRACTION)) {
        rank = 1;
    }
    if ((rank == 0) && (g_damageFlag[0] == 1)) {
        return rank + 1;
    }
    if ((rank == 0) || (rank == 1)) {
        if (rankBonus) {
            return rank + 1;
        }
        group = g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE;
        if ((group == BULLET_KIND_RANK_BONUS_GROUP_A) || (group == BULLET_KIND_RANK_BONUS_GROUP_B)) {
            rank += 1;
        }
    }
    return rank;
}

/* Name of the cached damage attribute ("fire", "ice", "thunder", "dark"); any index of 4 or more
 * gives "common". Scripts build the "SQ_LDMG/<attribute>" sequence label from it. */
const char *BLTgetAttributeStr(void)
{
    if (g_attackZokusei[0] >= 4)
        return g_attributeNameDefault[0];
    return g_attributeNames[g_attackZokusei[0]];
}

int BLTgetStunTime(int stunValue, unsigned char rankBonus) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2ESTUNTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlMaxHp[0]);
    beMessenger_AppendInt(g_beMessenger[0], stunValue);
    beMessenger_AppendInt(g_beMessenger[0], rankBonus);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* The five BLTget*Time helpers share one shape: only a technique attack (group 4) of the matching
 * sub-kind carries the status effect; otherwise 0 without messaging. Then the matching P2E*TIME
 * command is sent to FIGHTCALC with the cached arguments and its first integer is the duration.
 * Poison, attack-down and power-down also pass the script's `effectKey` string. */

int BLTgetPoisonTime(const char *effectKey) {
    if ((g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POISON) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EPOISONTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLTgetSleepTime(void) {
    if ((g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_SLEEP) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2ESLEEPTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLTgetBindTime(void) {
    if ((g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_BIND) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EBINDTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLTgetAttackDownTime(const char *effectKey) {
    if ((g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_ATTACK_DOWN) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EATKDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLTgetPowerDownTime(const char *effectKey) {
    if ((g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POWER_DOWN) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EPOWDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

void BLTcalcSkillUp(unsigned char first, unsigned char second) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2ESKILLUP);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], first);
    beMessenger_AppendInt(g_beMessenger[0], second);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
}

int BLTcalcEXPUp(void) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EEXPUP);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

unsigned char BLPisHitCheck(void) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PISHITCHECK);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_hitterRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

/* E2PDAMAGE, the enemy-to-player counterpart of BLTgetDamageValue: the hitter's base work goes
 * with it, and the reply is cached the same way. */
int BLPgetDamageValue(void) {
    int baseWork;

    baseWork = 0;
    if (g_hitterInfoName[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_hitterInfoName[0], g_bltShootRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PDAMAGE);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_hitterRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendObject(g_beMessenger[0], (void *)baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_damageResult[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 1);
    g_damageFlag[0] = beMessenger_GetInt(g_beMessenger[0], 2);
    return g_damageResult[0];
}

/* ZOKUSEI: "attribute". Asks FIGHTCALC for the attack's attribute and returns its name. */
const char *BLPgetAttackZokusei(void) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], GETPATKZOKUSEI);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    return BLTgetAttributeStr();
}

/* E2PDAMAGERANK. The reply's rank is raised from 0 to 1 when the cached rank flag from the last
 * E2PDAMAGE is 1. The two integers are the script's arguments, appended unchanged. */
int BLPgetDamageRank(int scriptArg1, int scriptArg2) {
    int rank;

    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PDAMAGERANK);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg1);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg2);
    beMessenger_AppendObject(g_beMessenger[0], g_mdlEntity[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    rank = beMessenger_GetInt(g_beMessenger[0], 0);
    if ((rank == 0) && (g_damageFlag[0] == 1)) {
        rank += 1;
    }
    return rank;
}

/* E2PSTUNTIME. `scriptArg1`/`scriptArg2` are appended unchanged; the reply's first integer is the
 * stun duration. */
int BLPgetStunTime(int scriptArg1, int scriptArg2) {
    int baseWork;

    baseWork = 0;
    if (g_hitterInfoName[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_hitterInfoName[0], g_bltShootRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PSTUNTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_hitterRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg1);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg2);
    beMessenger_AppendObject(g_beMessenger[0], (void *)baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetPoisonTime(const char *effectKey) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PPOISONTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetSleepTime(void) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PSLEEPTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_hitterRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetBindTime(void) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PBINDTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_hitterRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetAttackDownTime(const char *effectKey) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PATKDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_hitterRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetPowerDownTime(const char *effectKey) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PPOWDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], effectKey);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_hitterRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* KOUKA: "effect". */
int BLPcalcKoukaMagic(void) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2PKOUKAMAGIC);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

void LISsetDifficultMax(int maxDifficulty) {
    beMessenger_SelectReceivers(g_beMessenger[0], LOADINTF2, 0, 0);
    beMessenger_AppendInt(g_beMessenger[0], maxDifficulty);
    beMessenger_DispatchSelected(g_beMessenger[0], SETDIFFICULTMAX);
}

int be_GetMetaObject_Virtual(void)
{
    return (int)g_be_metaObject[0];
}

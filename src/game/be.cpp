/* be: the game object scripts call as `be:<function>(...)`. The Lua class `be` binds the 116
 * native functions below to one dispatcher; the C++ class `be` is the insight manager that
 * finds the other managers those functions talk to. */
#include "dw4/lua/lua.h"
#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/datapump/igRandomNumberDispatchView.h"
#include "dw4/game/beDemoManager.h"
#include "dw4/game/ndmw/listSet.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/game/be.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beMatCtrl.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igStringObj.h"
#include "dw4/support/list-services.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* A reference-counted string: the text follows its chunk owner and its count. */
static inline void releaseString(char *text) {
    if (text != 0) {
        int *header = (int *)(text - 8);
        int count = header[1] - 1;
        header[1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
        }
    }
}

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

namespace Gap {
namespace Bec {
/* The Lua class `be`, the object scripts call the native API through. */
struct beLuaWrapper : igLuaGlue::Class {
    static void *operator new(unsigned int size, ::igObject *pool) {
        return Memory_AllocateBufferDirect(size, (igMemoryPoolView *)pool);
    }
    static void operator delete(void *memory, ::igObject *) {
        Memory_FreeBufferWithAllocator(memory, (igMemoryPoolView *)g_luaGluePool);
    }
    beLuaWrapper();
    void registerFunctions();
};
}

/* The Lua class `Bec`, the namespace the game's classes are bound under. */
struct BecLuaWrapper : igLuaGlue::Class {
    static void *operator new(unsigned int size, ::igObject *pool) {
        return Memory_AllocateBufferDirect(size, (igMemoryPoolView *)pool);
    }
    static void operator delete(void *memory, ::igObject *) {
        Memory_FreeBufferWithAllocator(memory, (igMemoryPoolView *)g_luaGluePool);
    }
    BecLuaWrapper();
};
}

extern "C" {
/* This file. */
int LuaAPI_Dispatch(lua_State *L);
igLuaGlue::Class *beLuaWrapper_Create(void);
igLuaGlue::Class *BecLuaWrapper_Create(void);
int be_GetMetaObject_Virtual(void);
void be_Activate(void);
void be_Deactivate(void);
void be_Start(be *self);
void be_Stop(void);
int be_AddInfo(void);
void be_RemoveAllInfo(void);
void be_Update(void);
igObject *bePlayer_GetStruct(int slot);
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
void MATsetRun(unsigned char run);
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

/* The managers be_Start finds, and the be itself. */
extern beSystem *g_beSystem;
extern beMessenger *g_beMessenger;
extern beMatCtrl *g_matCtrl;
extern beDemoManager *g_beDemoManager;
extern be *g_be;

/* The last FIGHTCALC damage reply: damage, attribute index and rank flag. */
extern int g_damageResult;
extern int g_attackZokusei;
extern int g_damageFlag;

/* Result strings the string getters return. */
extern char g_mdlPosStrBuffer[64];
extern char g_mdlRotStrBuffer[64];
extern char g_playerDataStrBuffer[64];
extern char g_playerPosStrBuffer[64];

}

/* The game's string pool, created on first use. */
static inline StringPool *stringPool(void) {
    if (g_stringPool == 0) {
        StringPool *pool = (StringPool *)StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool = pool;
    }
    return g_stringPool;
}

/* Points a string field at the pooled copy of `text`, releasing the string it held. */
static inline void setPooledString(int &field, const char *text) {
    char *token = StringPool_Intern(stringPool(), text);
    releaseString((char *)field);
    field = (int)token;
}

/* Points a property record's string at the pooled copy of `text`, releasing the one it held. */
static inline void setRecordString(beDataObjString *record, const char *text) {
    char *token = StringPool_Intern(stringPool(), text);
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
            empty = StringPool_Intern(stringPool(), (const char *)0);
            releaseString(*slot);
            i += 1;
            *slot = empty;
            offset += 4;
        } while (i < count);
    }
    list->_count = 0;
}

/* The allocator an object's new members come from: its own, or the default one. */
static inline int allocatorFor(igObject *object) {
    int allocator = (int)((Gap::Core::igObject *)object)->getMemoryPool();
    return g_useOwnerAllocator != 0 ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
}

/* The Lua functions `be` hands the binding, with the argument codes of each. */
/* 116 functions share 109 names: overloads bind under one. */
const int LUA_API_FUNCTION_COUNT = 116;

const char *g_luaApiFunctionNames[109] = {
    "MATsetRun", "sd", "MDLisLive", "BLPcalcKoukaMagic",
    "BLTisPlayerBullet", "MDLisCallName", "BLPgetAttackDownTime", "MDLsetSeq",
    "BLTgetDamageValue", "SYSctlPlayer", "SYSisGetShinkaDigimon", "MDLdspDamageP",
    "MDLgetPosStr", "SYSgetArea", "MDLgetRecNo", "SYSctlCardFolder",
    "MDLgetMHp", "BLTgetBindTime", "SYSgetLightMode", "BLTgetDamageRank",
    "SYSgetIsPackOnly", "MDLisSeqName", "MDLsetDMGTurn", "DMrun",
    "BLPgetPoisonTime", "Bec", "CFLsetName", "LISsetDifficultMax",
    "SYSgetRandom", "BLTgetShootRamNo", "COUNTERset", "MATisPlayer",
    "MsgBox", "MATisRidePlayer", "MDLsetSD", "PLAYERgetPosStr",
    "PLAYERgetDataStr", "MDLgetBulletName", "TXTgetCallNo", "MDLgetRotStr",
    "MATgetPlayerMatStat", "SYSsetDifficulty", "BLPgetSleepTime", "BLTgetStunTime",
    "MDLgetInfoName", "MDLgetRamNo", "BLPgetBindTime", "MDLaddHp",
    "BLPgetStunTime", "SYSisJoinPlayer", "BLTisCritical", "MDLgetBulletBoxNo",
    "BLPgetDamageRank", "BLPgetAttackZokusei", "DMchkSD", "BLPisHitCheck",
    "SYSgetPlayerName", "SYSgetPlayerLevel", "BLPgetDamageValue", "BLTgetAttributeStr",
    "BLTcalcEXPUp", "BLTcalcSkillUp", "SYSgetCountry", "BLTgetPowerDownTime",
    "SYSgetDifficulty", "BLTisHitCheck", "FLGflip", "BLTgetSleepTime",
    "SYSgetPlayerDigimon", "BLTgetPoisonTime", "MDLisStatus", "SYSctlDeviceFolder",
    "SYSgetGateStageName", "DMswtEnd", "MDLgetKyoriSquare", "MDLsetWorldPosTarget",
    "ShutDown", "MDLdspDamage", "SYSctlDiskFolder", "MATisRideOffPlayer",
    "PLAYERgetPos", "MDLgetBulletKind", "MATisAllPlayer", "MATgetPlayerNo",
    "SYSctlBit", "DMmsgBox", "FLGisOn", "SYSgetGateStageNo",
    "SYSgetPlayerNinzu", "SYSctlFlagFolder", "CFLclear", "DMswtSD",
    "MDLgetHp", "CFLgetFolderName", "be", "SYSgetCameraMode",
    "BLPgetPowerDownTime", "DMsetSD", "DMgetCount", "FLGset",
    "MDLdspExp", "DMsetLua", "DMcase", "COUNTERget",
    "SYSgetTarget", "SYSsetGateStage", "SYSctlShinka", "BLTgetAttackDownTime",
    "SYSgetWeaponName",
};

const unsigned int g_luaApiFunctionCodes[400] = {
    0x62100, 0x209, 0x5, 0x70101, 0x20d, 0x5, 0xb0002, 0x205,
    0xd8203, 0x20d, 0x5, 0x5, 0x38104, 0x205, 0x5, 0x80005,
    0x205, 0x52106, 0x20f, 0x5, 0xbe007, 0x205, 0x24008, 0x205,
    0x1a009, 0x205, 0x7c00a, 0x205, 0xd000b, 0x205, 0x2800c, 0x205,
    0xd220d, 0x20f, 0xd, 0x5, 0x9000e, 0x20d, 0xae00f, 0x205,
    0x8e610, 0x209, 0xd, 0x5, 0xd, 0x5, 0x5, 0x5,
    0x9c411, 0x209, 0xd, 0x5, 0x5, 0x5, 0xb2212, 0x209,
    0xd, 0x5, 0x72113, 0x205, 0x5, 0x88114, 0x205, 0x5,
    0x14215, 0x209, 0x5, 0x5, 0x1e216, 0x205, 0xd, 0x5,
    0xa8317, 0x205, 0xd, 0x5, 0x5, 0xd4318, 0x205, 0xd,
    0x5, 0x5, 0x12419, 0x205, 0xd, 0xd, 0x5, 0x5,
    0xb401a, 0x20f, 0x3411b, 0x20f, 0xd, 0xba01c, 0x20d, 0x251d,
    0x20f, 0xd, 0xd, 0x5, 0xd, 0xd, 0x241e, 0x20f,
    0xd, 0xd, 0x5, 0xd, 0x261f, 0x20f, 0xd, 0xd,
    0x5, 0xd, 0xd, 0x7, 0x2520, 0x20f, 0xd, 0xd,
    0x5, 0xd, 0x7, 0x3e021, 0x209, 0xa4022, 0x209, 0xa6023,
    0x205, 0x42124, 0x205, 0x5, 0x9e125, 0x205, 0x5, 0x50126,
    0x205, 0x5, 0x127, 0x20f, 0x9, 0xc2628, 0x20f, 0xd,
    0xd, 0x5, 0xd, 0xd, 0x7, 0xc2529, 0x20f, 0xd,
    0xd, 0x5, 0xd, 0xd, 0xc252a, 0x20f, 0xd, 0xd,
    0x5, 0xd, 0x7, 0xc242b, 0x20f, 0xd, 0xd, 0x5,
    0xd, 0x6c62c, 0x20f, 0xd, 0xd, 0x5, 0xd, 0xd,
    0xd, 0x6c52d, 0x20f, 0xd, 0xd, 0x5, 0xd, 0xd,
    0xb652e, 0x20f, 0xd, 0xd, 0x5, 0xd, 0xd, 0xb642f,
    0x20f, 0xd, 0xd, 0x5, 0xd, 0x92030, 0x20f, 0xcc131,
    0x20f, 0x5, 0xca132, 0x20f, 0xd, 0xaa233, 0x20f, 0xd,
    0x5, 0x2e034, 0x20f, 0xc4035, 0x205, 0xac136, 0x209, 0x5,
    0xc6237, 0x20f, 0x5, 0x9, 0x84138, 0x20f, 0x5, 0x3c239,
    0x20f, 0x5, 0x5, 0xce13a, 0x205, 0x5, 0x5803b, 0x20d,
    0x5a03c, 0x205, 0x1c03d, 0x205, 0x2003e, 0x205, 0xb803f, 0x205,
    0x18340, 0x20d, 0xb, 0xb, 0xb, 0x4e341, 0x20d, 0xb,
    0xb, 0xb, 0x5e142, 0x20f, 0x5, 0xe143, 0x20f, 0xd,
    0x44244, 0x20f, 0xd, 0xd, 0x4245, 0x209, 0xd, 0x5,
    0xa2046, 0x205, 0x4a047, 0x20d, 0x66048, 0x205, 0x9a149, 0x20f,
    0x5, 0x1614a, 0x20f, 0x5, 0xc814b, 0x20f, 0x5, 0x2c14c,
    0x20f, 0x5, 0xa14d, 0x209, 0xd, 0x9634e, 0x20f, 0xb,
    0xb, 0xb, 0x9614f, 0x20f, 0xd, 0x94350, 0x20b, 0xb,
    0xb, 0xb, 0x2a151, 0x209, 0xd, 0x8c352, 0x209, 0xd,
    0x5, 0xd, 0x8053, 0x209, 0x3a054, 0x205, 0x82055, 0x209,
    0x10156, 0x205, 0x9, 0x26257, 0x205, 0x5, 0x9, 0x64058,
    0x209, 0x56259, 0x205, 0x5, 0x9, 0x8a15a, 0x205, 0xd,
    0x8605b, 0x205, 0x2205c, 0x205, 0xd615d, 0x205, 0xd, 0x7e15e,
    0x205, 0xd, 0x7a25f, 0x20f, 0x9, 0x9, 0x78060, 0x205,
    0x76061, 0x20d, 0x6e062, 0x209, 0x74063, 0x205, 0x6a064, 0x20d,
    0x68265, 0x205, 0x5, 0x5, 0x60266, 0x205, 0x5, 0x5,
    0x30167, 0x205, 0xd, 0x54068, 0x205, 0x5c069, 0x205, 0xc16a,
    0x205, 0xd, 0xc016b, 0x205, 0xd, 0x606c, 0x205, 0x4c06d,
    0x205, 0xa006e, 0x205, 0x4836f, 0x20d, 0x5, 0x5, 0xb,
    0x46470, 0x20d, 0x5, 0xb, 0xb, 0xb, 0x36171, 0x20f,
    0x5, 0x40272, 0x20f, 0xd, 0x5, 0x98073, 0x20f, 0x0,
};

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
        LuaError("Can't find method %s::%s", function->owner->name, function->name);
        return 0;
    }
}

namespace Gap {
namespace Bec {

beLuaWrapper::beLuaWrapper() : Class("be", "igInfoManager", 0, 0, 0, 0, 0) {
}
}
}

/* The start-up hook's factory for the `be` class. */
igLuaGlue::Class *beLuaWrapper_Create(void) {
    be_EnsureRegistered();
    return new (g_luaGluePool) Gap::Bec::beLuaWrapper;
}

Gap::BecLuaWrapper::BecLuaWrapper() : Class("Bec", 0, 0, 0, 0, 0, 0) {
}

/* The start-up hook's factory for the `Bec` class. */
igLuaGlue::Class *BecLuaWrapper_Create(void) {
    return new (g_luaGluePool) Gap::BecLuaWrapper;
}

/* The glue creates the `be` and `Bec` classes when it starts. */
static LuaStartupHook beLuaStartupHook(beLuaWrapper_Create, 0);
static LuaStartupHook BecLuaStartupHook(BecLuaWrapper_Create, 0);

/* The managers be_Start finds, then the model, hit and damage state the queries below read. */
beSystem *g_beSystem;
beMessenger *g_beMessenger;
beMatCtrl *g_matCtrl;
beDemoManager *g_beDemoManager;
be *g_be;
beBaseInfoRam *g_mdlEntity;
int g_mdlRamNo;
float *g_mdlMatrix;
int g_mdlMaxHp;
int g_mdlHp;
int g_mdlRecNo;
const char *g_mdlInfoName;
int g_mdlBulletKind;
int g_mdlBulletBoxNo;
const char *g_hitterInfoName;
int g_bltShootRamNo;
int g_hitterRecNo;
unsigned char g_mdlDmgTurn[4];
const char *g_mdlCallName;
float *g_mdlWorldPosTarget;
int g_txtCallNo;
char g_mdlPosStrBuffer[64];
char g_mdlRotStrBuffer[64];
char g_playerDataStrBuffer[64];
char g_playerPosStrBuffer[64];
int g_damageResult;
int g_attackZokusei;
int g_damageFlag;

/* The game's per-library class registration; this file registers no reflected class. */
void LuaAPI_RegisterClasses(void)
{
}

namespace Gap {
namespace Bec {

void beLuaWrapper::registerFunctions() {
    LuaClass_BindFunctions(this, 0, LuaAPI_Dispatch, g_luaApiFunctionNames,
                           LUA_API_FUNCTION_COUNT, g_luaApiFunctionCodes, 0);
}
}
}

void be_Activate(void)
{
}

void be_Deactivate(void)
{
}

/* Finds the managers the script functions talk to and records itself as the game's be. */
void be_Start(be *self) {
    beDemoManager *demoManager;

    g_beSystem = (beSystem *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject);
    g_beMessenger = (beMessenger *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beMessenger_metaObject);
    g_matCtrl = (beMatCtrl *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beMatCtrl_metaObject);
    demoManager = (beDemoManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beDemoManager_metaObject);
    g_be = self;
    g_beDemoManager = demoManager;
}

void be_Stop(void)
{
}

/* Keeps no info the insight core offers. */
int be_AddInfo(void) {
    return 0;
}

/* Empties the be's string list. */
void be_RemoveAllInfo(void) {
    clearStringList((igStringRefList *)g_be->_stringRefList);
    {
        igStringRefList *list = (igStringRefList *)g_be->_stringRefList;
        if (!(0 < list->_count)) {
            ((Gap::Core::igDataList *)list)->setCapacity(0, 4);
        }
    }
}

void be_Update(void)
{
}

/* Asks GAMERAM for a property record: the shared one (PLAYER_SLOT_COMMON) or a player's. */
const char *g_getRecordCommands[5] = {"GETCOMMON", "GETPLAYER1", "GETPLAYER2", "GETPLAYER3", "GETPLAYER4"};

igObject *bePlayer_GetStruct(int slot) {
    beMessenger_SendNamed(g_beMessenger, "GAMERAM", 0, 0, g_getRecordCommands[slot]);
    return beMessenger_GetObject(g_beMessenger, 0);
}

unsigned char SYSisJoinPlayer(int playerIndex) {
    return igProperty_GetRecordByte(bePlayer_GetStruct(playerIndex + 1), "ISUSE")->_data;
}

const char *SYSgetPlayerName(int playerIndex) {
    return (const char *)igProperty_GetRecordString(bePlayer_GetStruct(playerIndex + 1), "DIGIMONNAME")->_data;
}

/* The name of a player's power-socket weapon, or 0 past the end of the list. */
const char *SYSgetWeaponName(int playerIndex, int slot) {
    const char *name;
    igStringRefList *list;

    list = (igStringRefList *)igProperty_GetRecordStringList(bePlayer_GetStruct(playerIndex + 1), "POWERSOCKETNAME")->_data;
    if (list->_count <= slot) {
        return 0;
    }
    {
        igStringRef copy = StringList_CopyRetained(list, slot);
        name = copy.p;
    }
    return name;
}

/* NINZU: "number of people", the joined-player count. */
int SYSgetPlayerNinzu(void) {
    return igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), "NINZU")->_data;
}

int SYSgetDifficulty(void) {
    return igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), "DIFFICULTY")->_data;
}

void SYSsetDifficulty(int difficulty) {
    igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), "DIFFICULTY")->_data = difficulty;
}

int SYSgetCameraMode(void) {
    beMessenger_SendGroup(g_beMessenger, "GAMERAM", "GETCOMMON");
    return igProperty_GetRecord(beMessenger_GetObject(g_beMessenger, 0), "CAMERAMODE")->_data;
}

int SYSgetLightMode(void) {
    beMessenger_SendGroup(g_beMessenger, "GAMERAM", "GETCOMMON");
    return igProperty_GetRecord(beMessenger_GetObject(g_beMessenger, 0), "LIGHTMODE")->_data;
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
    return ((igRandomNumberDispatchView *)g_beSystem->_random)->genrand() % range;
}

/* Records the gate stage; a null name stores the empty string. */
void SYSsetGateStage(const char *stageName, int stageNo) {
    igObject *common;

    beMessenger_SendGroup(g_beMessenger, "GAMERAM", "GETCOMMON");
    common = beMessenger_GetObject(g_beMessenger, 0);
    igProperty_GetRecord(common, "GATESTAGENO")->_data = stageNo;
    if (stageName == 0) {
        setRecordString(igProperty_GetRecordString(common, "GATESTAGENAME"), "");
        return;
    }
    setRecordString(igProperty_GetRecordString(common, "GATESTAGENAME"), stageName);
}

const char *SYSgetGateStageName(void) {
    beMessenger_SendGroup(g_beMessenger, "GAMERAM", "GETCOMMON");
    return (const char *)igProperty_GetRecordString(beMessenger_GetObject(g_beMessenger, 0), "GATESTAGENAME")->_data;
}

int SYSgetGateStageNo(void) {
    beMessenger_SendGroup(g_beMessenger, "GAMERAM", "GETCOMMON");
    return igProperty_GetRecord(beMessenger_GetObject(g_beMessenger, 0), "GATESTAGENO")->_data;
}

/* GAMERAM CTRLITEM requests: a kind, a command, an item database, then four integers. */
unsigned char SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "DEVICE");
    beMessenger_AppendString(g_beMessenger, command);
    beMessenger_AppendString(g_beMessenger, itemDb);
    beMessenger_AppendInt(g_beMessenger, index);
    beMessenger_AppendInt(g_beMessenger, itemId);
    beMessenger_AppendInt(g_beMessenger, extra0);
    beMessenger_AppendInt(g_beMessenger, extra1);
    beMessenger_DispatchSelected(g_beMessenger, "CTRLITEM");
    return beMessenger_GetBool(g_beMessenger, 0);
}

unsigned char SYSctlDiskFolder(const char *command, int index, int itemId, int count) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "DISK");
    beMessenger_AppendString(g_beMessenger, command);
    beMessenger_AppendString(g_beMessenger, "");
    beMessenger_AppendInt(g_beMessenger, index);
    beMessenger_AppendInt(g_beMessenger, itemId);
    beMessenger_AppendInt(g_beMessenger, 0);
    beMessenger_AppendInt(g_beMessenger, count);
    beMessenger_DispatchSelected(g_beMessenger, "CTRLITEM");
    return beMessenger_GetBool(g_beMessenger, 0);
}

unsigned char SYSctlFlagFolder(const char *command, int index) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "FLAG");
    beMessenger_AppendString(g_beMessenger, command);
    beMessenger_AppendString(g_beMessenger, "");
    beMessenger_AppendInt(g_beMessenger, 0);
    beMessenger_AppendInt(g_beMessenger, index);
    beMessenger_AppendInt(g_beMessenger, 0);
    beMessenger_AppendInt(g_beMessenger, 0);
    beMessenger_DispatchSelected(g_beMessenger, "CTRLITEM");
    return beMessenger_GetBool(g_beMessenger, 0);
}

int SYSctlBit(const char *command, int index, int value) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "BIT");
    beMessenger_AppendString(g_beMessenger, command);
    beMessenger_AppendString(g_beMessenger, "");
    beMessenger_AppendInt(g_beMessenger, index);
    beMessenger_AppendInt(g_beMessenger, value);
    beMessenger_AppendInt(g_beMessenger, 0);
    beMessenger_AppendInt(g_beMessenger, 0);
    beMessenger_DispatchSelected(g_beMessenger, "CTRLITEM");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int SYSgetPlayerLevel(int playerIndex) {
    return igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), "LEVEL")->_data;
}

int SYSgetPlayerDigimon(int playerIndex) {
    return igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), "DIGIMONNO")->_data;
}

/* SHINKA: "evolution". Whether the player has obtained the species (BASE_ISUSE). */
unsigned char SYSisGetShinkaDigimon(int playerIndex, int species)
{
    igBoolList *obtained = (igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(playerIndex + 1), "BASE_ISUSE")->_data;
    return *(unsigned char *)(obtained->_data + species);
}

/* The first player's card list: KAZU counts the cards held, SET and CLR take or give back the
 * card at `index` and report whether it changed. */
int SYSctlCardFolder(const char *command, int index) {
    igBoolList *cards = (igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(PLAYER_SLOT_FIRST), "CARDLIST")->_data;
    if (strcmp(command, "KAZU") == 0) {
        int count = cards->_count;
        int total = 0;
        int i;
        for (i = 0; i < count; i++) {
            if (((unsigned char *)cards->_data)[i] == 1) total += 1;
        }
        return total;
    }
    if (strcmp(command, "SET") == 0) {
        unsigned char *card = (unsigned char *)cards->_data + index;
        if (*card != 0) return 0;
        ListSet(cards, index, true);
        return 1;
    }
    if (strcmp(command, "CLR") == 0) {
        unsigned char *card = (unsigned char *)cards->_data + index;
        if (*card == 0) return 0;
        ListSet(cards, index, false);
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
    obtainedFlags = (unsigned char *)((igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(playerIndex + 1), "BASE_ISUSE")->_data)->_data; /* matching construct: byte base held in a pointer local keeps the retail operand order of the index add */
    obtained = obtainedFlags[species];
    if (strcmp(command, "GETEXP") == 0) {
        if (obtained != 0) result = ((int *)((igIntList *)igProperty_GetRecordIntList(bePlayer_GetStruct(playerIndex + 1), "BASE_EXP")->_data)->_data)[species];
        else result = -1;
    } else if (strcmp(command, "GETLEVEL") == 0) {
        if (obtained != 0) result = ((int *)((igIntList *)igProperty_GetRecordIntList(bePlayer_GetStruct(playerIndex + 1), "BASE_LEVEL")->_data)->_data)[species];
        else result = -1;
    } else if (strcmp(command, "SETSHINKA") == 0) {
        if (obtained != 0) result = 0;
        else {
            obtainedList = (igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(playerIndex + 1), "BASE_ISUSE")->_data;
            ListSet(obtainedList, species, true);
            result = 1;
        }
    } else result = 0;
    return result;
}

/* GAMERAM CTRLPLAYER request: a property, a command, a player and a value. */
int SYSctlPlayer(const char *property, const char *command, int playerIndex, int value) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, property);
    beMessenger_AppendString(g_beMessenger, command);
    beMessenger_AppendInt(g_beMessenger, playerIndex);
    beMessenger_AppendInt(g_beMessenger, value);
    beMessenger_DispatchSelected(g_beMessenger, "CTRLPLAYER");
    return beMessenger_GetInt(g_beMessenger, 0);
}

/* CFL: the system's list of files read for the stage. */
void CFLclear(void) {
    clearStringList((igStringRefList *)g_beSystem->_readFileList);
    {
        igStringRefList *list = (igStringRefList *)g_beSystem->_readFileList;
        if (!(0 < list->_count)) {
            ((Gap::Core::igDataList *)list)->setCapacity(0, 4);
        }
    }
}

/* Adds a name to the read-file list unless it is already there. */
void CFLsetName(const char *name) {
    igStringRefList *list;
    int count;
    bool found;
    int i;

    found = false;
    list = (igStringRefList *)g_beSystem->_readFileList;
    count = list->_count;
    i = 0;
    if (0 < count) {
    do {
        {
            igStringRef entry = StringList_CopyRetained(list, i);
            if (strcmp(entry.p, name) == 0) {
                found = true;
                break;
            }
        }
        i++;
    } while (i < count);
    }
    if (!((int)found & 0xff)) {
        igStringRef entry((char *)name);
        StringList_AppendRetained(list, &entry.p);
    }
}

const char *CFLgetFolderName(void) {
    return (const char *)g_beSystem->_stageName;
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
                    beMessenger_AppendString(g_beMessenger, part);
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
                        beMessenger_AppendInt(g_beMessenger, intValue);
                        break;
                    case 'L':
                        longValue = 0;
                        k = 2;
                        while (part[k] != '>') {
                            longValue = longValue * 10;
                            longValue += part[k] - '0';
                            k++;
                        }
                        beMessenger_AppendLong(g_beMessenger, longValue);
                        break;
                    case 'V':
                        igConvertString_Vec3f(part + 1, parsed, " < %f , %f , %f > ");
                        vector[0] = parsed[0];
                        vector[1] = parsed[1];
                        vector[2] = parsed[2];
                        beMessenger_AppendVec3(g_beMessenger, vector);
                        break;
                    case 'F':
                        text = (igStringObj *)g_beSystem->_globalStrObj;
                        igStringObj_Set(text, part + 2);
                        igStringObj_Erase(text, text->_length - 1, 1);
                        igStringObj_ToFloat(text, &floatValue);
                        beMessenger_AppendFloat(g_beMessenger, floatValue);
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
    beMessenger_SelectReceivers(g_beMessenger, group, infoName, ramNo);
    if (args != 0) {
        Lua_sd_OptionalArg(args);
    }
    beMessenger_DispatchSelected(g_beMessenger, message);
}

void sd_30(const char *group, const char *infoName, int ramNo, const char *message) {
    beMessenger_SendNamed(g_beMessenger, group, infoName, ramNo, message);
}

void sd_31(const char *group, const char *infoName, int ramNo, const char *message, const char *args, long long delay) {
    beMessenger_PrepareDelayedSelection(g_beMessenger, group, infoName, ramNo);
    if (args != 0) {
        Lua_sd_OptionalArg(args);
    }
    beMessenger_EnqueueSelected(g_beMessenger, message, delay);
}

void sd_32(const char *group, const char *infoName, int ramNo, const char *message, long long delay) {
    beMessenger_SendDelayedNamed(g_beMessenger, group, infoName, ramNo, message, delay);
}

unsigned char MATisPlayer(void) { return beMatCtrl_IsPlayer(g_matCtrl); }

unsigned char MATisAllPlayer(void) { return beMatCtrl_IsAllPlayer(g_matCtrl); }

int MATgetPlayerNo(void) { return beMatCtrl_GetPlayerNo(g_matCtrl); }

unsigned char MATisRidePlayer(int player) { return beMatCtrl_IsRidePlayer(g_matCtrl, player); }

unsigned char MATisRideOffPlayer(int player) { return beMatCtrl_IsRideOffPlayer(g_matCtrl, player); }

int MATgetPlayerMatStat(int player) { return beMatCtrl_GetPlayerMatStat(g_matCtrl, player); }

void MATsetRun(unsigned char run) { beMatCtrl_SetRun(g_matCtrl, run); }

/* DM: queue messages on the demo manager's build data; DMrun hands the queue over to play. */
void DMsetSD_40(const char *group, const char *infoName, int ramNo, const char *message, const char *param, long long sendTime) {
    beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND, group, infoName, ramNo, message, param, sendTime);
}

void DMsetSD_41(const char *group, const char *infoName, int ramNo, const char *message, const char *param) {
    beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND, group, infoName, ramNo, message, param, 0);
}

void DMsetSD_42(const char *group, const char *infoName, int ramNo, const char *message, long long sendTime) {
    beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND, group, infoName, ramNo, message, 0, sendTime);
}

void DMsetSD_43(const char *group, const char *infoName, int ramNo, const char *message)
{
    beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND, group, infoName, ramNo, message, 0, 0);
}

/* A wait: the message is sent again every update while its bool reply meets the condition ("!=0" and
 * "==1" wait out a true reply, "==0" and "!=1" a false one). */
void DMchkSD_44(const char *group, const char *infoName, int ramNo, const char *message, const char *param, const char *condition) {
    if (strcmp("!=0", condition) == 0 || strcmp("==1", condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND_UNTIL_FALSE, group, infoName, ramNo, message, param, 0);
    } else if (strcmp("==0", condition) == 0 || strcmp("!=1", condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND_UNTIL_TRUE, group, infoName, ramNo, message, param, 0);
    }
}

void DMchkSD_45(const char *group, const char *infoName, int ramNo, const char *message, const char *condition) {
    if (strcmp("!=0", condition) == 0 || strcmp("==1", condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND_UNTIL_FALSE, group, infoName, ramNo, message, 0, 0);
    } else if (strcmp("==0", condition) == 0 || strcmp("!=1", condition) == 0) {
        beDemoManager_AddKeepMes(g_beDemoManager, DEMO_MES_SEND_UNTIL_TRUE, group, infoName, ramNo, message, 0, 0);
    }
}

void DMsetLua(const char *chunk)
{
    beDemoManager_SetLua(g_beDemoManager, chunk);
}

void DMmsgBox(const char *text, int ramNo) {
    beDemoManager_MsgBox(g_beDemoManager, text, ramNo);
}

void DMswtSD_46(const char *group, const char *infoName, int ramNo, const char *message, const char *param) {
    beDemoManager_SwitchSD(g_beDemoManager, group, infoName, ramNo, message, param);
}

void DMswtSD_47(const char *group, const char *infoName, int ramNo, const char *message) {
    beDemoManager_SwitchSD(g_beDemoManager, group, infoName, ramNo, message, 0);
}

void DMswtEnd(void)
{
    beDemoManager_SwitchEnd(g_beDemoManager);
}

void DMcase(int ramNo)
{
    beDemoManager_Case(g_beDemoManager, ramNo);
}

void DMrun(void)
{
    beDemoManager_Run(g_beDemoManager);
}

/* The number of queued demos; with none queued, -1 while the SUBWND window runs, else 0. */
int DMgetCount(void) {
    int count;
    count = ((beDemoManagerWorkList *)g_beDemoManager->_activeDataList)->_count;
    if (count != 0) { return count; }
    beMessenger_SendNamed(g_beMessenger, "SUBWND", 0, 0, "ISRUN");
    if (beMessenger_GetBoolCount(g_beMessenger) == 0) { return 0; }
    count = beMessenger_GetBool(g_beMessenger, 0);
    count = (count & 0xFF) != 0;
    return -count;
}

/* FLG / COUNTER: the shared record's FLAG bool list and COUNTER int list. */
unsigned char FLGisOn(int flagNo) {
    igObject *common;

    beMessenger_SendNamed(g_beMessenger, "GAMERAM", 0, 0, "GETCOMMON");
    common = beMessenger_GetObject(g_beMessenger, 0);
    if (flagNo == FLAG_PLAYERS_JOINED) {
        return SYSgetPlayerNinzu() != 0;
    }
    igBoolList *flags = (igBoolList *)igProperty_GetRecordArray(common, "FLAG")->_data;
    return *(unsigned char *)(flags->_data + flagNo);
}

void FLGset(int flagNo, unsigned char on) {
    igBoolList *flags;
    int count;

    beMessenger_SendNamed(g_beMessenger, "GAMERAM", 0, 0, "GETCOMMON");
    flags = (igBoolList *)igProperty_GetRecordArray(beMessenger_GetObject(g_beMessenger, 0), "FLAG")->_data;
    count = flags->_count;
    if ((count != 0) && (flagNo >= 0) && (flagNo < count)) {
        *(char *)(flagNo + flags->_data) = on;
    }
}

void FLGflip(int flagNo) {
    igObject *common;
    unsigned char *values;
    beMessenger_SendNamed(g_beMessenger, "GAMERAM", 0, 0, "GETCOMMON");
    common = beMessenger_GetObject(g_beMessenger, 0);
    values = (unsigned char *)((igBoolList *)igProperty_GetRecordArray(common, "FLAG")->_data)->_data;
    if (values[flagNo] != 0) {
        ListSet((igBoolList *)igProperty_GetRecordArray(common, "FLAG")->_data, flagNo, false);
    } else {
        ListSet((igBoolList *)igProperty_GetRecordArray(common, "FLAG")->_data, flagNo, true);
    }
}

void COUNTERset(int counterNo, int value) {
    igIntList *counters;
    int count;
    beMessenger_SendNamed(g_beMessenger, "GAMERAM", 0, 0, "GETCOMMON");
    counters = (igIntList *)igProperty_GetRecordIntList(beMessenger_GetObject(g_beMessenger, 0), "COUNTER")->_data;
    count = counters->_count;
    if ((count != 0) && (counterNo >= 0) && (counterNo < count)) {
        *(int *)(counters->_data + (counterNo * 4)) = value;
    }
}

int COUNTERget(int counterNo)
{
    beMessenger_SendNamed(g_beMessenger, "GAMERAM", 0, 0, "GETCOMMON");
    return ((int *)((igIntList *)igProperty_GetRecordIntList(beMessenger_GetObject(g_beMessenger, 0), "COUNTER")->_data)->_data)[counterNo];
}

int MDLgetRamNo(void)
{
    return g_mdlRamNo;
}

const char *MDLgetInfoName(void)
{
    return g_mdlInfoName;
}

/* The model's position moved by a local offset, as "V<x,y,z>". */
char *MDLgetPosStr(float x, float y, float z) {
    float matrix[16];
    igVec3f offset;
    float position[3];

    igMatrix44f_SetIdentity(matrix);
    igMatrix44f_Copy(matrix, g_mdlMatrix);
    offset[0] = x;
    offset[1] = y;
    offset[2] = z;
    igMatrix44f_TranslateLocal(matrix, offset);
    igMatrix44f_GetTranslation(matrix, position);
    sprintf(g_mdlPosStrBuffer, "V<%f,%f,%f>", position[0], position[1], position[2]);
    return g_mdlPosStrBuffer;
}

/* A rotation as "V<x,y,z>": `y` turned by the model's heading, in degrees. */
char *MDLgetRotStr(float x, float y, float z) {
    float forward[4];
    float matrix[16];
    float heading;
    igMatrix44f_SetIdentity(matrix);
    igMatrix44f_Copy(matrix, g_mdlMatrix);
    Vec3f_TransformDirection(forward, g_vec3ZAxis.vec, matrix);
    heading = atan2f(forward[0], forward[2]);
    sprintf(g_mdlRotStrBuffer, "V<%f,%f,%f>", x, RADIANS_TO_DEGREES * heading + y, z);
    return g_mdlRotStrBuffer;
}

int MDLgetMHp(void)
{
    return g_mdlMaxHp;
}

int MDLgetHp(void)
{
    return g_mdlHp;
}

void MDLaddHp(int amount) {
    g_mdlHp = g_mdlHp + amount;
    if (g_mdlHp < 0) {
        g_mdlHp = 0;
    }
}

void MDLsetSeq(const char *sequence)
{
    beMessenger_SendNamed(g_beMessenger, "MODELCTRL", g_mdlInfoName, g_mdlRamNo, sequence);
}

void MDLsetSD(const char *message, const char *args)
{
    sd_29("MODELCTRL", g_mdlInfoName, g_mdlRamNo, message, args);
}

/* Whether any of the named models still runs. */
unsigned char MDLisLive(const char *infoName, int ramNo) {
    int count;
    bool live;
    int i;
    beMessenger_SendNamed(g_beMessenger, "MODELCTRL", infoName, ramNo, "ISRUN");
    count = beMessenger_GetBoolCount(g_beMessenger);
    live = false;
    for (i = 0; i < count; i++) {
        if (beMessenger_GetBool(g_beMessenger, i)) {
            live = true;
            break;
        }
    }
    return live;
}

int MDLgetBulletKind(void)
{
    return g_mdlBulletKind;
}

const char *g_bulletKindNames[9] = {0, "PCWA", "PCCA", "PCSA", "PCMA", "PCBA", "PCTK", "ENAT", "PCMK"};

const char *MDLgetBulletName(void) {
    return g_bulletKindNames[g_mdlBulletKind / BULLET_KIND_GROUP_SIZE];
}

int MDLgetBulletBoxNo(void)
{
    return g_mdlBulletBoxNo;
}

FloatingNumberStyleData g_floatingNumberStyles[5] = {
    {"i_dmgnum", "dmgnm0", {"SQ_DMGNM01", "SQ_DMGNM02", "SQ_DMGNM03", "SQ_DMGNM04", "SQ_DMGNM05"}},
    {"i_expnum", "expnm0", {"SQ_EXPNM01", "SQ_EXPNM02", "SQ_EXPNM03", "SQ_EXPNM04", "SQ_EXPNM04"}},
    {"i_healnum", "healnm0", {"SQ_HEALNM01", "SQ_HEALNM02", "SQ_HEALNM03", "SQ_HEALNM04", "SQ_HEALNM05"}},
    {"i_pcdmgnum", "dmgnm1", {"SQ_DMGNM01", "SQ_DMGNM02", "SQ_DMGNM03", "SQ_DMGNM04", "SQ_DMGNM05"}},
    {"i_bitnum", "bitnum0", {"SQ_BITNM01", "SQ_BITNM02", "SQ_BITNM03", "SQ_BITNM04", "SQ_BITNM04"}},
};

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
    beMessenger_SendNamed(g_beMessenger, "MODELCTRL", modelInfoName, -1, "FIND_SPACE");
    if (beMessenger_GetObjectCount(g_beMessenger) != 0) {
        number = (beBaseInfoRam *)beMessenger_GetObject(g_beMessenger, 0);
        if (value < 10) digits = 0;
        else if (value < 100) digits = 1;
        else if (value < 1000) digits = 2;
        else if (value < 10000) digits = 3;
        else if (value < 100000) digits = 4;
        else { digits = 4; value = 99999; }
        sequence = g_floatingNumberStyles[style].digitSequences[digits];
        beMessenger_SelectReceivers(g_beMessenger, "MODELCTRL", modelInfoName, number->_ramNo);
        beMessenger_AppendString(g_beMessenger, sequence);
        igMatrix44f_GetTranslation(g_mdlMatrix, position);
        at[0] = position[0]; at[1] = position[1]; at[2] = position[2];
        beMessenger_AppendVec3(g_beMessenger, at);
        beMessenger_DispatchSelected(g_beMessenger, "GENERATE");
        beMessenger_SelectReceivers(g_beMessenger, "NUMBERCTRL", numberInfoName, number->_ramNo);
        beMessenger_AppendInt(g_beMessenger, value);
        beMessenger_DispatchSelected(g_beMessenger, "SETVALUE");
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
    const char *callName = g_mdlCallName;
    if (callName == 0) return isZero((int)name);
    return isZero(strcmp(callName, name));
}

void MDLsetWorldPosTarget_78(float x, float y, float z) {
    float *target = g_mdlWorldPosTarget;
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

    if (g_mdlWorldPosTarget != 0) {
        igConvertString_Vec3f(text, parsed, "V<%f,%f,%f>");
        x = parsed[0]; z = parsed[2]; y = parsed[1];
        target = g_mdlWorldPosTarget;
        target[0] = x;
        target[1] = y;
        target[2] = z;
    }
}

/* KYORI: "distance". The squared distance from the model to a point. */
float MDLgetKyoriSquare(float x, float y, float z) {
    float position[3];
    float dx, dy, dz;
    igMatrix44f_GetTranslation(g_mdlMatrix, position);
    dy = position[1] - y;
    dx = position[0] - x;
    dz = position[2] - z;
    return dx * dx + dy * dy + dz * dz;
}

int MDLgetRecNo(void)
{
    return g_mdlRecNo;
}

/* Whether the model's current sequence is `sequence`; creates the model's data list if it has none. */
unsigned char MDLisSeqName(const char *sequence) {
    beBaseInfoRam *model = g_mdlEntity;
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
    beModelCtrlInfoRamData *data = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)model->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE");
    return strcmp((const char *)((beModelCtrlInfoWork *)data->_work)->_seqCodeName, sequence) == 0;
}

/* Asks the named model whether it is in a status (CHECKSTATUS); false without exactly one reply. */
unsigned char MDLisStatus(const char *infoName, int ramNo, const char *status) {
    beMessenger_SelectReceivers(g_beMessenger, "MODELCTRL", infoName, ramNo);
    beMessenger_AppendString(g_beMessenger, status);
    beMessenger_DispatchSelected(g_beMessenger, "CHECKSTATUS");
    if (beMessenger_GetBoolCount(g_beMessenger) == 1) {
        return beMessenger_GetBool(g_beMessenger, 0);
    }
    return 0;
}

int PLAYERgetPos(void) {
    beMessenger_SendGroup(g_beMessenger, "PLAYERPOINT", "GETGENERATEPOS");
    return beMessenger_GetInt(g_beMessenger, 0);
}

/* A player point's position and heading, as "V<x,y,z>/V<0,heading,0>" with `yaw` added. */
char *PLAYERgetDataStr(int point, int index, float yaw) {
    float heading;
    float forward[3];
    float matrix[16];
    float position[3];
    beMessenger_SelectGroup(g_beMessenger, "PLAYERPOINT");
    beMessenger_AppendInt(g_beMessenger, point);
    beMessenger_AppendInt(g_beMessenger, index);
    beMessenger_DispatchSelected(g_beMessenger, "GETMATRIXDIRECT");
    beMessenger_GetMatrix(matrix, g_beMessenger, 0);
    igMatrix44f_GetTranslation(matrix, position);
    Vec3f_TransformDirection(forward, g_vec3ZAxis.vec, matrix);
    heading = atan2f(forward[0], forward[2]);
    sprintf(g_playerDataStrBuffer, "V<%f,%f,%f>/V<0,%f,0>", position[0], position[1], position[2], (RADIANS_TO_DEGREES * heading) + yaw);
    return g_playerDataStrBuffer;
}

/* A player model's position moved by a local offset, as "V<x,y,z>"; 0 when it has no matrix. */
char *PLAYERgetPosStr(int ramNo, float x, float y, float z) {
    igVec3f offset;
    float position[4];
    float matrix[16];

    beMessenger_SendNamed(g_beMessenger, "PLAYER", 0, ramNo, "GETMATRIX");
    if (beMessenger_GetMatrixCount(g_beMessenger) != 0) {
        beMessenger_GetMatrix(matrix, g_beMessenger, 0);
        offset[0] = x;
        offset[1] = y;
        offset[2] = z;
        igMatrix44f_TranslateLocal(matrix, offset);
        igMatrix44f_GetTranslation(matrix, position);
        sprintf(g_playerPosStrBuffer, "V<%f,%f,%f>", position[0], position[1], position[2]);
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
    system = g_beSystem;
    system->_isShutDown = 1;
    system->_isStageLoop = 0;
    setPooledString(system->_nextStage, 0);
}

int TXTgetCallNo(void)
{
    return g_txtCallNo;
}

/* True below 1000, for 10000..59999 and for 80000..89999. The cached code is signed and not range-
 * checked, so a negative code also counts. */
unsigned char BLTisPlayerBullet(void) {
    if (g_mdlBulletKind < BULLET_KIND_GROUP_SIZE) {
        if (g_mdlBulletKind < PLAYER_BULLET_WEAPON_END) {
            return 1;
        }
        /* The early return and this jump are not interchangeable with a plain `return 0`. */
        goto notPlayerBullet;
    }
    if (g_mdlBulletKind < PLAYER_BULLET_RANGE_A_END) {
        return 1;
    }
    if ((g_mdlBulletKind >= PLAYER_BULLET_RANGE_B_BEGIN) && (g_mdlBulletKind < PLAYER_BULLET_RANGE_B_END)) {
        return 1;
    }
notPlayerBullet:
    return 0;
}

int BLTgetShootRamNo(void)
{
    return g_bltShootRamNo;
}

/* BLT: a player bullet hitting the cached model; BLP: an enemy bullet hitting the player. Each
 * asks FIGHTCALC through GAMERAM. */

/* Whether the cached player attack hits (P2EISHITCHECK). When the model has an info name, the
 * named ENEMY's base work (GETPEBASEWORK reply, object 1) goes with it. */
unsigned char BLTisHitCheck(void) {
    igObject *baseWork;

    baseWork = 0;
    if (g_mdlInfoName != 0) {
        beMessenger_SendNamed(g_beMessenger, "ENEMY", g_mdlInfoName, g_mdlRamNo, "GETPEBASEWORK");
        if (beMessenger_GetObjectCount(g_beMessenger) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger, 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EISHITCHECK");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_AppendObject(g_beMessenger, baseWork);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetBool(g_beMessenger, 0);
}

unsigned char BLTisCritical(void) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EISCRITICAL");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetBool(g_beMessenger, 0);
}

/* P2EDAMAGE with the script's critical flag. The reply's three integers (damage, attribute
 * index, rank flag) are cached for BLTgetDamageRank and BLTgetAttributeStr, and the damage is
 * returned. */
int BLTgetDamageValue(unsigned char critical) {
    igObject *baseWork;

    baseWork = 0;
    if (g_mdlInfoName != 0) {
        beMessenger_SendNamed(g_beMessenger, "ENEMY", g_mdlInfoName, g_mdlRamNo, "GETPEBASEWORK");
        if (beMessenger_GetObjectCount(g_beMessenger) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger, 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EDAMAGE");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_AppendInt(g_beMessenger, critical);
    beMessenger_AppendObject(g_beMessenger, baseWork);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    g_damageResult = beMessenger_GetInt(g_beMessenger, 0);
    g_attackZokusei = beMessenger_GetInt(g_beMessenger, 1);
    g_damageFlag = beMessenger_GetInt(g_beMessenger, 2);
    return g_damageResult;
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
    damageFraction = (float) g_damageResult / (float) g_mdlMaxHp;
    if (!(damageFraction <= DAMAGE_RANK2_FRACTION)) {
        rank = 2;
    } else if (!(damageFraction <= DAMAGE_RANK1_FRACTION)) {
        rank = 1;
    }
    if ((rank == 0) && (g_damageFlag == 1)) {
        return rank + 1;
    }
    if ((rank == 0) || (rank == 1)) {
        if (rankBonus) {
            return rank + 1;
        }
        group = g_mdlBulletKind / BULLET_KIND_GROUP_SIZE;
        if ((group == BULLET_KIND_RANK_BONUS_GROUP_A) || (group == BULLET_KIND_RANK_BONUS_GROUP_B)) {
            rank += 1;
        }
    }
    return rank;
}

const char *g_attributeNameDefault[1] = {"common"};
const char *g_attributeNames[4] = {"fire", "ice", "thunder", "dark"};

/* Name of the cached damage attribute ("fire", "ice", "thunder", "dark"); any index of 4 or more
 * gives "common". Scripts build the "SQ_LDMG/<attribute>" sequence label from it. */
const char *BLTgetAttributeStr(void)
{
    if (g_attackZokusei >= 4)
        return g_attributeNameDefault[0];
    return g_attributeNames[g_attackZokusei];
}

int BLTgetStunTime(int stunValue, unsigned char rankBonus) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2ESTUNTIME");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlMaxHp);
    beMessenger_AppendInt(g_beMessenger, stunValue);
    beMessenger_AppendInt(g_beMessenger, rankBonus);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

/* The five BLTget*Time helpers share one shape: only a technique attack (group 4) of the matching
 * sub-kind carries the status effect; otherwise 0 without messaging. Then the matching P2E*TIME
 * command is sent to FIGHTCALC with the cached arguments and its first integer is the duration.
 * Poison, attack-down and power-down also pass the script's `effectKey` string. */

int BLTgetPoisonTime(const char *effectKey) {
    if ((g_mdlBulletKind / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POISON) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EPOISONTIME");
    beMessenger_AppendString(g_beMessenger, effectKey);
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLTgetSleepTime(void) {
    if ((g_mdlBulletKind / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_SLEEP) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2ESLEEPTIME");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLTgetBindTime(void) {
    if ((g_mdlBulletKind / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_BIND) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EBINDTIME");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLTgetAttackDownTime(const char *effectKey) {
    if ((g_mdlBulletKind / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_ATTACK_DOWN) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EATKDWNTIME");
    beMessenger_AppendString(g_beMessenger, effectKey);
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLTgetPowerDownTime(const char *effectKey) {
    if ((g_mdlBulletKind / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if ((g_mdlBulletKind % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POWER_DOWN) {
        return 0;
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EPOWDWNTIME");
    beMessenger_AppendString(g_beMessenger, effectKey);
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

void BLTcalcSkillUp(unsigned char first, unsigned char second) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2ESKILLUP");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_AppendInt(g_beMessenger, first);
    beMessenger_AppendInt(g_beMessenger, second);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
}

int BLTcalcEXPUp(void) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2EEXPUP");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlRecNo);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

unsigned char BLPisHitCheck(void) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PISHITCHECK");
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_hitterRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetBool(g_beMessenger, 0);
}

/* E2PDAMAGE, the enemy-to-player counterpart of BLTgetDamageValue: the hitter's base work goes
 * with it, and the reply is cached the same way. */
int BLPgetDamageValue(void) {
    igObject *baseWork;

    baseWork = 0;
    if (g_hitterInfoName != 0) {
        beMessenger_SendNamed(g_beMessenger, "ENEMY", g_hitterInfoName, g_bltShootRamNo, "GETPEBASEWORK");
        if (beMessenger_GetObjectCount(g_beMessenger) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger, 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PDAMAGE");
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_hitterRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_AppendObject(g_beMessenger, baseWork);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    g_damageResult = beMessenger_GetInt(g_beMessenger, 0);
    g_attackZokusei = beMessenger_GetInt(g_beMessenger, 1);
    g_damageFlag = beMessenger_GetInt(g_beMessenger, 2);
    return g_damageResult;
}

/* ZOKUSEI: "attribute". Asks FIGHTCALC for the attack's attribute and returns its name. */
const char *BLPgetAttackZokusei(void) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "GETPATKZOKUSEI");
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    g_attackZokusei = beMessenger_GetInt(g_beMessenger, 0);
    return BLTgetAttributeStr();
}

/* E2PDAMAGERANK. The reply's rank is raised from 0 to 1 when the cached rank flag from the last
 * E2PDAMAGE is 1. The two integers are the script's arguments, appended unchanged. */
int BLPgetDamageRank(int scriptArg1, int scriptArg2) {
    int rank;

    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PDAMAGERANK");
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_AppendInt(g_beMessenger, scriptArg1);
    beMessenger_AppendInt(g_beMessenger, scriptArg2);
    beMessenger_AppendObject(g_beMessenger, g_mdlEntity);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    rank = beMessenger_GetInt(g_beMessenger, 0);
    if ((rank == 0) && (g_damageFlag == 1)) {
        rank += 1;
    }
    return rank;
}

/* E2PSTUNTIME. `scriptArg1`/`scriptArg2` are appended unchanged; the reply's first integer is the
 * stun duration. */
int BLPgetStunTime(int scriptArg1, int scriptArg2) {
    igObject *baseWork;

    baseWork = 0;
    if (g_hitterInfoName != 0) {
        beMessenger_SendNamed(g_beMessenger, "ENEMY", g_hitterInfoName, g_bltShootRamNo, "GETPEBASEWORK");
        if (beMessenger_GetObjectCount(g_beMessenger) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger, 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PSTUNTIME");
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_hitterRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_AppendInt(g_beMessenger, scriptArg1);
    beMessenger_AppendInt(g_beMessenger, scriptArg2);
    beMessenger_AppendObject(g_beMessenger, baseWork);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLPgetPoisonTime(const char *effectKey) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PPOISONTIME");
    beMessenger_AppendString(g_beMessenger, effectKey);
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLPgetSleepTime(void) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PSLEEPTIME");
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_hitterRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLPgetBindTime(void) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PBINDTIME");
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_hitterRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLPgetAttackDownTime(const char *effectKey) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PATKDWNTIME");
    beMessenger_AppendString(g_beMessenger, effectKey);
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_hitterRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

int BLPgetPowerDownTime(const char *effectKey) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "E2PPOWDWNTIME");
    beMessenger_AppendString(g_beMessenger, effectKey);
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_hitterRecNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

/* KOUKA: "effect". */
int BLPcalcKoukaMagic(void) {
    beMessenger_SelectGroup(g_beMessenger, "GAMERAM");
    beMessenger_AppendString(g_beMessenger, "P2PKOUKAMAGIC");
    beMessenger_AppendInt(g_beMessenger, g_mdlRamNo);
    beMessenger_AppendInt(g_beMessenger, g_bltShootRamNo);
    beMessenger_AppendInt(g_beMessenger, g_mdlBulletKind);
    beMessenger_DispatchSelected(g_beMessenger, "FIGHTCALC");
    return beMessenger_GetInt(g_beMessenger, 0);
}

void LISsetDifficultMax(int maxDifficulty) {
    beMessenger_SelectReceivers(g_beMessenger, "LOADINTF2", 0, 0);
    beMessenger_AppendInt(g_beMessenger, maxDifficulty);
    beMessenger_DispatchSelected(g_beMessenger, "SETDIFFICULTMAX");
}

int be_GetMetaObject_Virtual(void)
{
    return (int)g_be_metaObject;
}

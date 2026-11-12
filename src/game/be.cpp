#include "dw4/reflected.h"
#define PLAYER_SLOT_COMMON 0
#include "dw4/igSmartPointer.h"
#define BULLET_KIND_GROUP_SIZE 10000
#define BULLET_KIND_TECHNIQUE_GROUP 4
#define BULLET_KIND_RANK_BONUS_GROUP_A 2
#define BULLET_KIND_RANK_BONUS_GROUP_B 3
#define DAMAGE_RANK2_FRACTION 0.5f
#define DAMAGE_RANK1_FRACTION 0.25f
#define PLAYER_BULLET_WEAPON_END 1000
#define PLAYER_BULLET_RANGE_A_END 60000
#define PLAYER_BULLET_RANGE_B_BEGIN 80000
#define PLAYER_BULLET_RANGE_B_END 90000
#define BULLET_SUBKIND_POISON 0x14
#define BULLET_SUBKIND_ATTACK_DOWN 0x46
#define BULLET_SUBKIND_POWER_DOWN 0x55
#define BULLET_SUBKIND_SLEEP 0x5A
#define BULLET_SUBKIND_BIND 0x5F

extern "C" void lua_pushnumber(void *, long long);
extern "C" long long litodp(int);
extern "C" long long FUN_00100290(int);
extern "C" void FUN_0023d070(char *, void *, char *);
extern "C" void FUN_002467a0(char *, ...);
extern "C" long long fptodp(float);
extern "C" int LuaAPI_Dispatch(void *L);
extern "C" int FUN_00241930(...);
extern "C" void *FUN_003717e0(void *arg0);
extern "C" void FUN_0036e160(void);
extern "C" void *Memory_AllocateBufferDirect(unsigned int size, void *pool);
extern "C" void FUN_002ed4c0(void *ptr, void *pool);
extern "C" void *FUN_003718d0(void *arg0);
extern "C" void FUN_003719c0(void);
extern "C" int FUN_0023f4f0(int, int, void *, void *, int, void *, int);
extern "C" void LuaAPI_Register(int arg0);
extern "C" void Gap__Bec__be__vfunc_21(void);
extern "C" void Gap__Bec__be__vfunc_22(void);
extern "C" void Gap__Bec__be__vfunc_24(void);
extern "C" int Gap__Bec__be__vfunc_25(void);
extern "C" void Gap__Bec__be__vfunc_27(void);
extern "C" int Gap__Bec__be__vfunc_20(void);
extern "C" int FUN_00236f80(int, int);
extern "C" int FUN_002eb010(int);
extern "C" int List_Reserve(...);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" void Gap__Bec__be__vfunc_26(void);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int bePlayer_GetStruct(int playerNo);
extern "C" void *igProperty_GetRecordByte(int, char *);
extern "C" void * FUN_003a92e0(...);
extern "C" void * igProperty_GetRecord(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" unsigned char SYSisJoinPlayer(int playerIndex);
extern "C" int SYSgetPlayerName(int playerIndex);
extern "C" int SYSgetPlayerNinzu(void);
extern "C" int SYSgetDifficulty(void);
extern "C" void SYSsetDifficulty(int difficulty);
extern "C" int SYSgetCameraMode(void);
extern "C" int SYSgetLightMode(void);
extern "C" int SYSgetArea(void);
extern "C" int SYSgetCountry(void);
extern "C" int SYSgetTarget(void);
extern "C" int SYSgetIsPackOnly(void);
extern "C" int SYSgetGateStageName(void);
extern "C" int SYSgetGateStageNo(void);
extern "C" int SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1);
extern "C" int SYSctlDiskFolder(const char *command, int index, int itemId, int count);
extern "C" int SYSctlFlagFolder(const char *command, int index);
extern "C" int SYSctlBit(const char *command, int index, int value);
extern "C" int SYSgetPlayerLevel(int playerIndex);
extern "C" int SYSgetPlayerDigimon(int playerIndex);
extern "C" int SYSctlPlayer(const char *property, const char *command, int playerIndex, int value);
extern "C" int CFLgetFolderName(void);
extern "C" int MDLgetRamNo(void);
extern "C" int MDLgetInfoName(void);
extern "C" int MDLgetMHp(void);
extern "C" int MDLgetHp(void);
extern "C" void MDLaddHp(int amount);
extern "C" int MDLgetBulletKind(void);
extern "C" int MDLgetBulletBoxNo(void);
extern "C" void MDLsetDMGTurn(int value);
extern "C" int MDLgetRecNo(void);
extern "C" int PLAYERgetPos(void);
extern "C" void MsgBox(int, int);
extern "C" int TXTgetCallNo(void);
extern "C" int BLTgetShootRamNo(void);
extern "C" int BLTisCritical(void);
extern "C" int BLTgetStunTime(int intArg, unsigned char byteArg);
extern "C" void BLTcalcSkillUp(int firstByte, int secondByte);
extern "C" int BLTcalcEXPUp(void);
extern "C" int BLPisHitCheck(void);
extern "C" int BLPgetAttackZokusei(void);
extern "C" int BLPgetPoisonTime(const char *stringArg);
extern "C" int BLPgetSleepTime(void);
extern "C" int BLPgetBindTime(void);
extern "C" int BLPgetAttackDownTime(const char *stringArg);
extern "C" int BLPgetPowerDownTime(const char *stringArg);
extern "C" int BLPcalcKoukaMagic(void);
extern "C" void LISsetDifficultMax(int maxDifficulty);
extern "C" char *SYSgetWeaponName(int arg0, int arg1);
extern "C" unsigned int SYSgetRandom(unsigned int arg0);
extern "C" void * StringPool_Intern(...);
extern "C" void SYSsetGateStage(int *arg0, int arg1);
extern "C" void * igProperty_GetRecordArray(...);
extern "C" unsigned char SYSisGetShinkaDigimon(int arg0, int arg1);
extern "C" int strcmp(...);
extern "C" int SYSctlCardFolder(int name, int idx);
extern "C" int SYSctlShinka(int arg0, int arg1, int arg2);
extern "C" void CFLclear(void);
extern "C" void CFLsetName(int arg0);
extern "C" unsigned strlen(char *);
extern "C" int FUN_001e6d30(char *, float *, int *);
extern "C" int FUN_0030b3c0(void *, char *);
extern "C" int FUN_0030b630(void *, float *);
extern "C" int FUN_0030bbf0(void *, int, int);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" int beMessenger_AppendLong(int, long long);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" void Lua_sd_OptionalArg(int arg0);
extern "C" void sd_29(int arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void sd_30(int arg0, int arg1, int arg2, int arg3);
extern "C" int beMessenger_EnqueueSelected(int, int, long long);
extern "C" int beMessenger_PrepareDelayedSelection(int, int, int, int);
extern "C" void sd_31(int arg0, int arg1, int arg2, int arg3, int arg4, long long arg5);
extern "C" int beMessenger_SendDelayedNamed(...);
extern "C" void sd_32(int arg0, int arg1, int arg2, int arg3, long long arg4);
extern "C" unsigned char MATisPlayer(void);
extern "C" bool MATisAllPlayer(void);
extern "C" int MATgetPlayerNo(void);
extern "C" bool MATisRidePlayer(int player);
extern "C" bool MATisRideOffPlayer(int player);
extern "C" int MATgetPlayerMatStat(int player);
extern "C" void MATsetRun(int value);
extern "C" int FUN_0037e3a0(...);
extern "C" void DMsetSD_40(int arg0, int arg1, int arg2, int arg3, int arg4, long long arg5);
extern "C" void DMsetSD_41(int arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void DMsetSD_42(int arg0, int arg1, int arg2, int arg3, long long arg4);
extern "C" void DMsetSD_43(char * p0, int p1, int p2, int p3);
extern "C" void DMchkSD_44(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" void DMchkSD_45(int arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void FUN_0037e6e0(int, char *);
extern "C" void DMsetLua(char * p0);
extern "C" int FUN_0037e890(int, int, int);
extern "C" void DMmsgBox(int arg0, int arg1);
extern "C" int FUN_0037e110(int, int, int, int, int, int);
extern "C" void DMswtSD_46(int arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void DMswtSD_47(int arg0, int arg1, int arg2, int arg3);
extern "C" void FUN_0037e180(int);
extern "C" void DMswtEnd(void);
extern "C" void FUN_0037e2d0(int, char *);
extern "C" void DMcase(char * p0);
extern "C" void FUN_0037ea50(int);
extern "C" void DMrun(void);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int DMgetCount(void);
extern "C" unsigned char FLGisOn(int arg0);
extern "C" void FLGset(int arg0, unsigned char arg1);
extern "C" void FLGflip(int arg0);
extern "C" void * FUN_003a9250(...);
extern "C" void COUNTERset(int arg0, int arg1);
extern "C" int COUNTERget(int arg0);
extern "C" int sprintf(...);
extern "C" int igMatrix44f_SetIdentity(float *);
extern "C" int Matrix44_GetTranslation(int, float *);
extern "C" int Matrix44_TranslateLocal(float *, float *);
extern "C" char *MDLgetPosStr(float fparg0, float fparg1, float fparg2);
extern "C" float atan2f(float, float);
extern "C" int FUN_001908f0(float *, int);
extern "C" int FUN_00192f50(float *, int *, float *);
extern "C" int *MDLgetRotStr(float fparg0, float fparg1, float fparg2);
extern "C" void MDLsetSeq(char * p0);
extern "C" void MDLsetSD(char * p0, char * p1);
extern "C" bool MDLisLive(int arg0, int arg1);
extern "C" int MDLgetBulletName(void);
extern "C" int beMessenger_GetObjectCount(int);
extern "C" void FloatingNumber_Spawn(int dmg, int row);
extern "C" void MDLdspDamage(int p0);
extern "C" void MDLdspDamageP(int p0);
extern "C" void MDLdspExp(int p0);
extern "C" int MDLisCallName(char *name);
extern "C" void MDLsetWorldPosTarget_78(float fparg0, float fparg1, float fparg2);
extern "C" void MDLsetWorldPosTarget_79(int arg0);
extern "C" float MDLgetKyoriSquare(float x, float y, float z);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int MDLisSeqName(char *arg0);
extern "C" int MDLisStatus(int arg0, int arg1, int arg2);
extern "C" int beMessenger_GetMatrix(float *, int, int);
extern "C" int *PLAYERgetDataStr(int arg0, int arg1, float fparg0);
extern "C" int beMessenger_GetMatrixCount(int);
extern "C" int *PLAYERgetPosStr(int arg0, float fparg0, float fparg1, float fparg2);
extern "C" void ShutDown(void);
extern "C" void beMessenger_AppendObject(int, ...);
extern "C" int BLTisPlayerBullet(void);
extern "C" int BLTisHitCheck(void);
extern "C" int BLTgetDamageValue(int criticalFlag);
extern "C" int BLTgetDamageRank(int currentHp, unsigned char rankBonus);
extern "C" char *BLTgetAttributeStr(void);
extern "C" int BLTgetPoisonTime(const char *effectKey);
extern "C" int BLTgetSleepTime(void);
extern "C" int BLTgetBindTime(void);
extern "C" int BLTgetAttackDownTime(const char *effectKey);
extern "C" int BLTgetPowerDownTime(const char *effectKey);
extern "C" int BLPgetDamageValue(void);
extern "C" int BLPgetDamageRank(int scriptArg1, int scriptArg2);
extern "C" int BLPgetStunTime(int scriptArg1, int scriptArg2);
/* Lua native-API dispatcher: fn->id (short at +40) selects one of 116 API functions through a jump
 * table; arguments are read from the Lua argument array (24-byte slots, first value at +16) and
 * results are pushed on the Lua state. */

struct LuaV { union { int i; unsigned char b; float f; long long l; } u; char pad[16]; };
struct LuaArgs { char pad[16]; struct LuaV v[8]; };
struct LuaFnP { int pad[3]; int f12; };
struct LuaFn { char pad0[12]; int f12; char name[12]; struct LuaFnP *p; char pad1[8]; short id; unsigned short flags; };
extern "C" struct LuaFn *lua_touserdata(void *, int);
extern "C" char DAT_0050d600[];
extern "C" int DAT_0050ceb8[4];
extern "C" int DAT_0050d7f0[4];
extern "C" int DAT_00539f00[4];
extern "C" void *DAT_0056de30;
struct PoolAllocated {
    static void *operator new(unsigned int size, void *pool) { return Memory_AllocateBufferDirect(size, pool); }
    static void operator delete(void *ptr, void *) { FUN_002ed4c0(ptr, DAT_0056de30); }
};
struct PooledNode : PoolAllocated {
    char body[92];
    PooledNode();
};
extern "C" PooledNode *FUN_00371840(void);
extern "C" int DAT_0050c908[4];
extern "C" int DAT_00539ef0[4];
extern "C" int DAT_004c8560[4];
extern "C" int DAT_0050cfc0[4];
extern "C" int g_be_metaObject[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" int g_beMatCtrl_metaObject[4];
extern "C" int g_beDemoManager_metaObject[4];
extern "C" int g_beMessenger[4];
extern "C" void Gap__Bec__be__vfunc_23(be *arg0);
extern "C" int g_stringPool[4];
extern "C" be *DAT_0058a1d8[4];
extern "C" char GAMERAM[];
extern "C" char *g_getRecordCommands[5];
extern "C" int g_beMessenger[4];
/* Native functions behind the game scripts' `be:` calls. */




typedef struct PropertyRecord {
    char unknown0[12];
    int value;
} PropertyRecord;
extern "C" char ISUSE[];
extern "C" char DIGIMONNAME[];
extern "C" char NINZU[];
extern "C" char DIFFICULTY[];
extern "C" char GETCOMMON[];
extern "C" char CAMERAMODE[];
extern "C" char LIGHTMODE[];
extern "C" char GATESTAGENAME[];
extern "C" char GATESTAGENO[];
extern "C" char DEVICE[];
extern "C" char CTRLITEM[];
extern "C" char EMPTY[];
extern "C" char DISK[];
extern "C" char FLAG[];
extern "C" char BIT[];
extern "C" char LEVEL[];
extern "C" char DIGIMONNO[];
extern "C" char CTRLPLAYER[];
extern "C" char PLAYERPOINT[];
extern "C" char GETGENERATEPOS[];
extern "C" char P2EISCRITICAL[];
extern "C" char P2ESTUNTIME[];
extern "C" char P2ESKILLUP[];
extern "C" char P2EEXPUP[];
extern "C" char E2PISHITCHECK[];
extern "C" char GETPATKZOKUSEI[];
extern "C" char E2PPOISONTIME[];
extern "C" char E2PSLEEPTIME[];
extern "C" char E2PBINDTIME[];
extern "C" char E2PATKDWNTIME[];
extern "C" char E2PPOWDWNTIME[];
extern "C" char P2PKOUKAMAGIC[];
extern "C" char LOADINTF2[];
extern "C" char SETDIFFICULTMAX[];
extern "C" int g_mdlRamNo[4];
extern "C" int g_mdlMaxHp[4];
extern "C" int g_mdlHp[4];
extern "C" int g_mdlRecNo[4];
extern "C" int g_mdlInfoName[4];
extern "C" int g_mdlBulletKind[4];
extern "C" int g_mdlBulletBoxNo[4];
extern "C" int g_bltShootRamNo[4];
extern "C" int g_blpStatus[4];
extern "C" int g_txtCallNo[4];
extern "C" int g_attackZokusei[4];
struct T { char pad[12]; igStringRefList *list; };
extern "C" struct T *FUN_003a9310(int, int *);
extern "C" int DAT_0050d960[4];
extern "C" beSystem *g_beSystem[4];
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
typedef struct R { char p[12]; int *f12; } R;
extern "C" int DAT_0050da18[4];
typedef struct CardFolderFlags { int pad0; int pad1; int count; int pad3; unsigned char *flags; } CardFolderFlags;
typedef struct CardRecord { int pad0; int pad1; int pad2; CardFolderFlags *folder; } CardRecord;
extern "C" int DAT_0050da28[4];
extern "C" int DAT_0050da38[4];
extern "C" int DAT_0050da40[4];
extern "C" int DAT_0050da48[4];
extern "C" unsigned char GPR_005549bc;
extern "C" unsigned char GPR_005549c0;
extern "C" int DAT_0050da50[4];
extern "C" int DAT_0050da58[4];
extern "C" int DAT_0050da68[4];
extern "C" int DAT_0050da78[4];
extern "C" int DAT_0050da88[4];
extern "C" unsigned char GPR_005549c4;
typedef struct L { char p[8]; int n; char q[4]; int **data; } L;
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    void *p;
    StringRef(void *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(void *, StringRef *);
extern "C" StringRef StringList_CopyRetained(void *, int);
extern "C" int DAT_0050dab0[4];
extern "C" beMatCtrl *g_matCtrl[4];
extern "C" bool beMatCtrl_IsPlayer(beMatCtrl *);
extern "C" bool beMatCtrl_IsAllPlayer(beMatCtrl *);
extern "C" int beMatCtrl_GetPlayerNo(beMatCtrl *);
extern "C" bool beMatCtrl_IsRidePlayer(beMatCtrl *, int);
extern "C" bool beMatCtrl_IsRideOffPlayer(beMatCtrl *, int);
extern "C" int beMatCtrl_GetPlayerMatStat(beMatCtrl *, int);
extern "C" void beMatCtrl_SetRun(beMatCtrl *, int);
extern "C" int DAT_0050dac8[4];
extern "C" int DAT_0050dad0[4];
extern "C" int DAT_0050dad8[4];
extern "C" int DAT_0050dae0[4];
extern "C" int DAT_0050dae8[4];
extern "C" int DAT_0050daf0[4];
typedef struct { char pad[28]; struct { char pad[8]; int f8; } *f1c; } O;
extern "C" O *DAT_0058a1d0[4];
/* Bounds-checked byte set chosen by the current byte. */


struct Rec { char pad[12]; igUnsignedCharList *f12; };
extern "C" unsigned char GPR_005549c8;
extern "C" unsigned char GPR_005549cc;
extern "C" int DAT_0050daf8[4];
struct M { float m[16]; };
struct V3 { float x, y, z; };
extern "C" int Matrix44_Copy(struct M *, void *);
extern "C" char DAT_0058a230[32];
extern "C" int DAT_0058a270[];
extern "C" int DAT_0050db10[4];
extern "C" int DAT_004c873c[4];
struct DmgVec { float x; float y; float z; };
struct DmgRow { int w[7]; };
extern "C" struct DmgRow DAT_004c8770[];
extern "C" struct DmgRow DAT_004c8774[];
extern "C" struct DmgRow DAT_004c8778[];
extern "C" int DAT_0050dd00[4];
extern "C" int DAT_0050dd10[4];
extern "C" int DAT_0050dd20[4];
extern "C" int DAT_0050dd30[4];
extern "C" int DAT_0058a1e8[4];
extern "C" char *DAT_0058a214[4];
extern "C" int DAT_0050db00[4];
extern "C" V3 * DAT_0058a218[4];
extern "C" igObject *beBaseInfoDataList_Create(...);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
extern "C" beBaseInfoRam *g_mdlEntity[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int DAT_0050dd40[4];
extern "C" unsigned char GPR_00554c14;
extern "C" int DAT_0050dd48[4];
extern "C" int DAT_004e1098[4];
extern "C" int DAT_0050dd80[4];
extern "C" int DAT_0050dd90[4];
extern "C" int DAT_0058a2b0[4];
extern "C" int DAT_0050dda8[4];
extern "C" int DAT_0050ddb0[4];
extern "C" int DAT_0058a2f0[4];
extern "C" char ENEMY[];
extern "C" char GETPEBASEWORK[];
extern "C" char FIGHTCALC[];
extern "C" char P2EISHITCHECK[];
extern "C" char P2EDAMAGE[];
extern "C" char P2EPOISONTIME[];
extern "C" char P2ESLEEPTIME[];
extern "C" char P2EBINDTIME[];
extern "C" char P2EATKDWNTIME[];
extern "C" char P2EPOWDWNTIME[];
extern "C" char E2PDAMAGE[];
extern "C" char E2PDAMAGERANK[];
extern "C" char E2PSTUNTIME[];
extern "C" int g_statusFieldA[4];
extern "C" int g_damageResult[4];
extern "C" int g_damageFlag[4];
extern "C" char *g_attributeNameDefault[4];
extern "C" char *g_attributeNames[4];

int LuaAPI_Dispatch(void *L) {
    struct LuaFn *fn = lua_touserdata(L, -1);
    struct LuaArgs *a;
    if (fn->flags & 0xfff) a = (struct LuaArgs *)lua_touserdata(L, -2); else a = 0;
    switch (fn->id) {
    case 0x0:
        lua_pushnumber(L, FUN_00100290(SYSisJoinPlayer(a->v[0].u.i))); return 1;
    case 0x1:
        FUN_0023d070(fn->name, L, ((char *)SYSgetPlayerName(a->v[0].u.i))); return 1;
    case 0x2:
        lua_pushnumber(L, litodp(SYSgetPlayerNinzu())); return 1;
    case 0x3:
        FUN_0023d070(fn->name, L, SYSgetWeaponName(a->v[0].u.i, a->v[1].u.i)); return 1;
    case 0x4:
        lua_pushnumber(L, litodp(((int)SYSgetRandom((unsigned int)(a->v[0].u.i))))); return 1;
    case 0x5:
        lua_pushnumber(L, litodp(SYSgetDifficulty())); return 1;
    case 0x6:
        SYSsetDifficulty(a->v[0].u.i); return 0;
    case 0x7:
        lua_pushnumber(L, litodp(SYSgetCameraMode())); return 1;
    case 0x8:
        lua_pushnumber(L, litodp(SYSgetLightMode())); return 1;
    case 0x9:
        lua_pushnumber(L, litodp(SYSgetArea())); return 1;
    case 0xa:
        lua_pushnumber(L, litodp(SYSgetCountry())); return 1;
    case 0xb:
        lua_pushnumber(L, litodp(SYSgetTarget())); return 1;
    case 0xc:
        lua_pushnumber(L, litodp(SYSgetIsPackOnly())); return 1;
    case 0xd:
        SYSsetGateStage((int *)(a->v[0].u.i), a->v[1].u.i); return 0;
    case 0xe:
        FUN_0023d070(fn->name, L, ((char *)SYSgetGateStageName())); return 1;
    case 0xf:
        lua_pushnumber(L, litodp(SYSgetGateStageNo())); return 1;
    case 0x10:
        lua_pushnumber(L, FUN_00100290(((unsigned char)SYSctlDeviceFolder((const char *)(a->v[0].u.i), a->v[1].u.i, (const char *)(a->v[2].u.i), a->v[3].u.i, a->v[4].u.i, a->v[5].u.i)))); return 1;
    case 0x11:
        lua_pushnumber(L, FUN_00100290(((unsigned char)SYSctlDiskFolder((const char *)(a->v[0].u.i), a->v[1].u.i, a->v[2].u.i, a->v[3].u.i)))); return 1;
    case 0x12:
        lua_pushnumber(L, FUN_00100290(((unsigned char)SYSctlFlagFolder((const char *)(a->v[0].u.i), a->v[1].u.i)))); return 1;
    case 0x13:
        lua_pushnumber(L, litodp(SYSgetPlayerLevel(a->v[0].u.i))); return 1;
    case 0x14:
        lua_pushnumber(L, litodp(SYSgetPlayerDigimon(a->v[0].u.i))); return 1;
    case 0x15:
        lua_pushnumber(L, FUN_00100290(SYSisGetShinkaDigimon(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x16:
        lua_pushnumber(L, litodp(SYSctlCardFolder(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x17:
        lua_pushnumber(L, litodp(SYSctlBit((const char *)(a->v[0].u.i), a->v[1].u.i, a->v[2].u.i))); return 1;
    case 0x18:
        lua_pushnumber(L, litodp(SYSctlShinka(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i))); return 1;
    case 0x19:
        lua_pushnumber(L, litodp(SYSctlPlayer((const char *)(a->v[0].u.i), (const char *)(a->v[1].u.i), a->v[2].u.i, a->v[3].u.i))); return 1;
    case 0x1a:
        CFLclear(); return 0;
    case 0x1b:
        CFLsetName(a->v[0].u.i); return 0;
    case 0x1c:
        FUN_0023d070(fn->name, L, ((char *)CFLgetFolderName())); return 1;
    case 0x1d:
        sd_29(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i); return 0;
    case 0x1e:
        sd_30(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i); return 0;
    case 0x1f:
        sd_31(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i, a->v[5].u.l); return 0;
    case 0x20:
        sd_32(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.l); return 0;
    case 0x21:
        lua_pushnumber(L, FUN_00100290(((unsigned char)MATisPlayer()))); return 1;
    case 0x22:
        lua_pushnumber(L, FUN_00100290(((unsigned char)MATisAllPlayer()))); return 1;
    case 0x23:
        lua_pushnumber(L, litodp(MATgetPlayerNo())); return 1;
    case 0x24:
        lua_pushnumber(L, litodp(((unsigned char)MATisRidePlayer(a->v[0].u.i)))); return 1;
    case 0x25:
        lua_pushnumber(L, litodp(((unsigned char)MATisRideOffPlayer(a->v[0].u.i)))); return 1;
    case 0x26:
        lua_pushnumber(L, litodp(MATgetPlayerMatStat(a->v[0].u.i))); return 1;
    case 0x27:
        MATsetRun((int)(a->v[0].u.b)); return 0;
    case 0x28:
        DMsetSD_40(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i, a->v[5].u.l); return 0;
    case 0x29:
        DMsetSD_41(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i); return 0;
    case 0x2a:
        DMsetSD_42(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.l); return 0;
    case 0x2b:
        DMsetSD_43((char *)(a->v[0].u.i), a->v[1].u.i, a->v[2].u.i, a->v[3].u.i); return 0;
    case 0x2c:
        DMchkSD_44(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i, a->v[5].u.i); return 0;
    case 0x2d:
        DMchkSD_45(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i); return 0;
    case 0x2e:
        DMswtSD_46(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i); return 0;
    case 0x2f:
        DMswtSD_47(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i); return 0;
    case 0x30:
        DMswtEnd(); return 0;
    case 0x31:
        DMcase((char *)(a->v[0].u.i)); return 0;
    case 0x32:
        DMsetLua((char *)(a->v[0].u.i)); return 0;
    case 0x33:
        DMmsgBox(a->v[0].u.i, a->v[1].u.i); return 0;
    case 0x34:
        DMrun(); return 0;
    case 0x35:
        lua_pushnumber(L, litodp(DMgetCount())); return 1;
    case 0x36:
        lua_pushnumber(L, FUN_00100290(FLGisOn(a->v[0].u.i))); return 1;
    case 0x37:
        FLGset(a->v[0].u.i, a->v[1].u.b); return 0;
    case 0x38:
        FLGflip(a->v[0].u.i); return 0;
    case 0x39:
        COUNTERset(a->v[0].u.i, a->v[1].u.i); return 0;
    case 0x3a:
        lua_pushnumber(L, litodp(COUNTERget(a->v[0].u.i))); return 1;
    case 0x3b:
        FUN_0023d070(fn->name, L, ((char *)MDLgetInfoName())); return 1;
    case 0x3c:
        lua_pushnumber(L, litodp(MDLgetRamNo())); return 1;
    case 0x3d:
        lua_pushnumber(L, litodp(MDLgetRecNo())); return 1;
    case 0x3e:
        lua_pushnumber(L, litodp(MDLgetMHp())); return 1;
    case 0x3f:
        lua_pushnumber(L, litodp(MDLgetHp())); return 1;
    case 0x40:
        FUN_0023d070(fn->name, L, MDLgetPosStr(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f)); return 1;
    case 0x41:
        FUN_0023d070(fn->name, L, ((char *)MDLgetRotStr(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f))); return 1;
    case 0x42:
        MDLaddHp(a->v[0].u.i); return 0;
    case 0x43:
        MDLsetSeq((char *)(a->v[0].u.i)); return 0;
    case 0x44:
        MDLsetSD((char *)(a->v[0].u.i), (char *)(a->v[1].u.i)); return 0;
    case 0x45:
        lua_pushnumber(L, FUN_00100290(((unsigned char)MDLisLive(a->v[0].u.i, a->v[1].u.i)))); return 1;
    case 0x46:
        lua_pushnumber(L, litodp(MDLgetBulletKind())); return 1;
    case 0x47:
        FUN_0023d070(fn->name, L, ((char *)MDLgetBulletName())); return 1;
    case 0x48:
        lua_pushnumber(L, litodp(MDLgetBulletBoxNo())); return 1;
    case 0x49:
        MDLdspDamage(a->v[0].u.i); return 0;
    case 0x4a:
        MDLdspDamageP(a->v[0].u.i); return 0;
    case 0x4b:
        MDLdspExp(a->v[0].u.i); return 0;
    case 0x4c:
        MDLsetDMGTurn(a->v[0].u.i); return 0;
    case 0x4d:
        lua_pushnumber(L, FUN_00100290(((unsigned char)MDLisCallName((char *)(a->v[0].u.i))))); return 1;
    case 0x4e:
        MDLsetWorldPosTarget_78(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f); return 0;
    case 0x4f:
        MDLsetWorldPosTarget_79(a->v[0].u.i); return 0;
    case 0x50:
        lua_pushnumber(L, fptodp(MDLgetKyoriSquare(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f))); return 1;
    case 0x51:
        lua_pushnumber(L, FUN_00100290(((unsigned char)MDLisSeqName((char *)(a->v[0].u.i))))); return 1;
    case 0x52:
        lua_pushnumber(L, FUN_00100290(((unsigned char)MDLisStatus(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i)))); return 1;
    case 0x53:
        lua_pushnumber(L, FUN_00100290(((unsigned char)BLTisPlayerBullet()))); return 1;
    case 0x54:
        lua_pushnumber(L, litodp(BLTgetShootRamNo())); return 1;
    case 0x55:
        lua_pushnumber(L, FUN_00100290(((unsigned char)BLTisHitCheck()))); return 1;
    case 0x56:
        lua_pushnumber(L, litodp(BLTgetDamageValue((int)(a->v[0].u.b)))); return 1;
    case 0x57:
        lua_pushnumber(L, litodp(BLTgetDamageRank(a->v[0].u.i, a->v[1].u.b))); return 1;
    case 0x58:
        lua_pushnumber(L, FUN_00100290(((unsigned char)BLTisCritical()))); return 1;
    case 0x59:
        lua_pushnumber(L, litodp(BLTgetStunTime(a->v[0].u.i, a->v[1].u.b))); return 1;
    case 0x5a:
        lua_pushnumber(L, litodp(BLTgetPoisonTime((const char *)(a->v[0].u.i)))); return 1;
    case 0x5b:
        lua_pushnumber(L, litodp(BLTgetSleepTime())); return 1;
    case 0x5c:
        lua_pushnumber(L, litodp(BLTgetBindTime())); return 1;
    case 0x5d:
        lua_pushnumber(L, litodp(BLTgetAttackDownTime((const char *)(a->v[0].u.i)))); return 1;
    case 0x5e:
        lua_pushnumber(L, litodp(BLTgetPowerDownTime((const char *)(a->v[0].u.i)))); return 1;
    case 0x5f:
        BLTcalcSkillUp((int)(a->v[0].u.b), (int)(a->v[1].u.b)); return 0;
    case 0x60:
        lua_pushnumber(L, litodp(BLTcalcEXPUp())); return 1;
    case 0x61:
        FUN_0023d070(fn->name, L, BLTgetAttributeStr()); return 1;
    case 0x62:
        lua_pushnumber(L, FUN_00100290(((unsigned char)BLPisHitCheck()))); return 1;
    case 0x63:
        lua_pushnumber(L, litodp(BLPgetDamageValue())); return 1;
    case 0x64:
        FUN_0023d070(fn->name, L, ((char *)BLPgetAttackZokusei())); return 1;
    case 0x65:
        lua_pushnumber(L, litodp(BLPgetDamageRank(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x66:
        lua_pushnumber(L, litodp(BLPgetStunTime(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x67:
        lua_pushnumber(L, litodp(BLPgetPoisonTime((const char *)(a->v[0].u.i)))); return 1;
    case 0x68:
        lua_pushnumber(L, litodp(BLPgetSleepTime())); return 1;
    case 0x69:
        lua_pushnumber(L, litodp(BLPgetBindTime())); return 1;
    case 0x6a:
        lua_pushnumber(L, litodp(BLPgetAttackDownTime((const char *)(a->v[0].u.i)))); return 1;
    case 0x6b:
        lua_pushnumber(L, litodp(BLPgetPowerDownTime((const char *)(a->v[0].u.i)))); return 1;
    case 0x6c:
        lua_pushnumber(L, litodp(BLPcalcKoukaMagic())); return 1;
    case 0x6d:
        lua_pushnumber(L, litodp(TXTgetCallNo())); return 1;
    case 0x6e:
        lua_pushnumber(L, litodp(PLAYERgetPos())); return 1;
    case 0x6f:
        FUN_0023d070(fn->name, L, ((char *)PLAYERgetDataStr(a->v[0].u.i, a->v[1].u.i, a->v[2].u.f))); return 1;
    case 0x70:
        FUN_0023d070(fn->name, L, ((char *)PLAYERgetPosStr(a->v[0].u.i, a->v[1].u.f, a->v[2].u.f, a->v[3].u.f))); return 1;
    case 0x71:
        LISsetDifficultMax(a->v[0].u.i); return 0;
    case 0x72:
        MsgBox(a->v[0].u.i, a->v[1].u.i); return 0;
    case 0x73:
        ShutDown(); return 0;
    default:
        FUN_002467a0(DAT_0050d600, fn->p->f12, fn->f12);
        return 0;
    }
}

void *FUN_003717e0(void *arg0) {
    FUN_00241930(arg0, &DAT_0050ceb8[0], &DAT_0050d7f0[0], 0, 0, 0, 0, 0);
    *(int *)((char *)(arg0) + 88) = (int)(&DAT_00539f00[0]);
    return arg0;
}

PooledNode *FUN_00371840(void) {
    FUN_0036e160();
    return new (DAT_0056de30) PooledNode;
}

void *FUN_003718d0(void *arg0) {
    FUN_00241930(arg0, &DAT_0050c908[0], 0, 0, 0, 0, 0, 0);
    *(int *)((char *)(arg0) + 88) = (int)(&DAT_00539ef0[0]);
    return arg0;
}

void FUN_003719c0(void)
{
}

void LuaAPI_Register(int arg0) {
    FUN_0023f4f0(arg0, 0, (void *)&LuaAPI_Dispatch, &DAT_004c8560[0], 0x74, &DAT_0050cfc0[0], 0);
}

/* Default body of slot 21, does nothing. */
void Gap__Bec__be__vfunc_21(void)
{
}

/* Default body of slot 22, does nothing. */
void Gap__Bec__be__vfunc_22(void)
{
}

void Gap__Bec__be__vfunc_23(be *arg0) {
    int temp_v0;

    g_beSystem[0] = (beSystem *)FUN_00236f80(arg0->_insight, g_beSystem_metaObject[0]);
    g_beMessenger[0] = FUN_00236f80(arg0->_insight, g_beMessenger_metaObject[0]);
    g_matCtrl[0] = (beMatCtrl *)FUN_00236f80(arg0->_insight, g_beMatCtrl_metaObject[0]);
    temp_v0 = FUN_00236f80(arg0->_insight, g_beDemoManager_metaObject[0]);
    ((void * *)DAT_0058a1d8)[0] = (void *)(arg0);
    ((int *)DAT_0058a1d0)[0] = temp_v0;
}

/* Default body of slot 24, does nothing. */
void Gap__Bec__be__vfunc_24(void)
{
}

/* Default body of slot 25, returns 0. */
int Gap__Bec__be__vfunc_25(void) {
    return 0;
}

/* the Game this pointer */
void Gap__Bec__be__vfunc_26(void) {
    igStringRefList *s5;
    int s4;
    int i;
    int **slot;
    int *s1;
    int off;
    int *old;
    int v;
    s5 = (igStringRefList *)DAT_0058a1d8[0]->_stringRefList;
    s4 = s5->_count;
    i = 0;
    if (0 < s4) {
        off = 0;
        do {
            slot = (int **)((char *)s5->_data + off);
            if (g_stringPool[0] == 0) {
                v = FUN_002eb010(0x10);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                g_stringPool[0] = v;
            }
            s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
            old = *slot;
            if (old != 0) {
                int *hdr = old - 2;
                int r = old[-1] - 1;
                old[-1] = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*hdr, hdr);
                }
            }
            i += 1;
            *slot = s1;
            off += 4;
        } while (i < s4);
    }
    s5->_count = 0;
    {
        igStringRefList *l2 = (igStringRefList *)DAT_0058a1d8[0]->_stringRefList;
        if (!(0 < l2->_count)) {
            List_Reserve(l2, 0, 4);
        }
    }
}

/* Default body of slot 27, does nothing. */
void Gap__Bec__be__vfunc_27(void)
{
}

int bePlayer_GetStruct(int playerNo) {
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, g_getRecordCommands[playerNo]);
    return beMessenger_GetObject(g_beMessenger[0], 0);
}

/* ZOKUSEI: attack attribute */

unsigned char SYSisJoinPlayer(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecordByte(bePlayer_GetStruct(playerIndex + 1), (char *)ISUSE))->value;
}

int SYSgetPlayerName(int playerIndex) {
    return ((PropertyRecord *)FUN_003a92e0(bePlayer_GetStruct(playerIndex + 1), DIGIMONNAME))->value;
}

char *SYSgetWeaponName(int arg0, int arg1) {
    char *s;
    igStringRefList *list;

    list = FUN_003a9310(bePlayer_GetStruct(arg0 + 1), &DAT_0050d960[0])->list;
    if (list->_count <= arg1) {
        return 0;
    }
    {
        StringRef str = StringList_CopyRetained(list, arg1);
        s = (char *)str.p;
    }
    return s;
}

/* NINZU: "number of people", the joined-player count. */
int SYSgetPlayerNinzu(void) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), NINZU))->value;
}

int SYSgetDifficulty(void) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), DIFFICULTY))->value;
}

void SYSsetDifficulty(int difficulty) {
    ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), DIFFICULTY))->value = difficulty;
}

int SYSgetCameraMode(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return ((PropertyRecord *)igProperty_GetRecord(beMessenger_GetObject(g_beMessenger[0], 0), CAMERAMODE))->value;
}

int SYSgetLightMode(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return ((PropertyRecord *)igProperty_GetRecord(beMessenger_GetObject(g_beMessenger[0], 0), LIGHTMODE))->value;
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

unsigned int SYSgetRandom(unsigned int arg0) {
    DW4VC_96_0 *temp_a0;

    temp_a0 = (DW4VC_96_0 *)g_beSystem[0]->_random;
    return temp_a0->vX() % arg0;
}

void SYSsetGateStage(int *arg0, int arg1) {
    int obj;
    int v;
    R *rec;
    int *s0;
    int *old;
    int *hd;
    int v1;

    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    obj = beMessenger_GetObject(g_beMessenger[0], 0);
    *(int *)((char *)igProperty_GetRecord(obj, GATESTAGENO) + 12) = arg1;
    if (arg0 == 0) {
        rec = (R *)FUN_003a92e0(obj, GATESTAGENAME);
        if (g_stringPool[0] == 0) {
            v = FUN_002eb010(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            g_stringPool[0] = v;
        }
        s0 = (int *)StringPool_Intern(g_stringPool[0], EMPTY);
        old = rec->f12;
        if (old != 0) {
            hd = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        rec->f12 = s0;
        return;
    }
    rec = (R *)FUN_003a92e0(obj, GATESTAGENAME);
    if (g_stringPool[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    s0 = (int *)StringPool_Intern(g_stringPool[0], arg0);
    old = rec->f12;
    if (old != 0) {
        hd = old - 2;
        v1 = old[-1] - 1;
        old[-1] = v1;
        if (v1 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    rec->f12 = s0;
}

int SYSgetGateStageName(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return ((PropertyRecord *)FUN_003a92e0(beMessenger_GetObject(g_beMessenger[0], 0), GATESTAGENAME))->value;
}

int SYSgetGateStageNo(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return ((PropertyRecord *)igProperty_GetRecord(beMessenger_GetObject(g_beMessenger[0], 0), GATESTAGENO))->value;
}

int SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1) {
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

int SYSctlDiskFolder(const char *command, int index, int itemId, int count) {
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

int SYSctlFlagFolder(const char *command, int index) {
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
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), LEVEL))->value;
}

int SYSgetPlayerDigimon(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), DIGIMONNO))->value;
}

unsigned char SYSisGetShinkaDigimon(int arg0, int arg1)
{
  char *new_var;
  new_var = ((char *) igProperty_GetRecordArray(bePlayer_GetStruct(arg0 + 1), &DAT_0050da18[0])) + 12;
  return *((int *) ((*((int *) (((char *) (*((int *) new_var))) + 16))) + arg1));
}

int SYSctlCardFolder(int name, int idx) {
    CardFolderFlags *f = ((CardRecord *)igProperty_GetRecordArray(bePlayer_GetStruct(1), DAT_0050da28))->folder;
    if (strcmp(name, DAT_0050da38) == 0) {
        int n = f->count;
        int total = 0;
        int i;
        for (i = 0; i < n; i++) {
            if (f->flags[i] == 1) total += 1;
        }
        return total;
    }
    if (strcmp(name, DAT_0050da40) == 0) {
        unsigned char *q = f->flags + idx;
        if (*q != 0) return 0;
        if (f->count != 0 && idx >= 0 && idx < f->count) *q = GPR_005549bc;
        return 1;
    }
    if (strcmp(name, DAT_0050da48) == 0) {
        unsigned char *q = f->flags + idx;
        if (*q == 0) return 0;
        if (f->count != 0 && idx >= 0 && idx < f->count) *q = GPR_005549c0;
        return 1;
    }
    return 0;
}

int SYSctlShinka(int arg0, int arg1, int arg2) {
    int has;
    int ret;
    igBoolList *b;
    unsigned char *d;
    d = (unsigned char *)((igBoolList *)((beDataObjBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(arg1 + 1), &DAT_0050da18[0]))->_data)->_data; /* matching construct: byte base held in a pointer local keeps the retail operand order of the index add */
    has = d[arg2];
    if (strcmp(arg0, &DAT_0050da50[0]) == 0) {
        if (has != 0) ret = ((int *)((igIntList *)((beDataObjIntList *)FUN_003a9250(bePlayer_GetStruct(arg1 + 1), &DAT_0050da58[0]))->_data)->_data)[arg2];
        else ret = -1;
    } else if (strcmp(arg0, &DAT_0050da68[0]) == 0) {
        if (has != 0) ret = ((int *)((igIntList *)((beDataObjIntList *)FUN_003a9250(bePlayer_GetStruct(arg1 + 1), &DAT_0050da78[0]))->_data)->_data)[arg2];
        else ret = -1;
    } else if (strcmp(arg0, &DAT_0050da88[0]) == 0) {
        if (has != 0) ret = 0;
        else {
            b = (igBoolList *)((beDataObjBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(arg1 + 1), &DAT_0050da18[0]))->_data;
            if (b->_count != 0 && arg2 >= 0 && arg2 < b->_count) ((unsigned char *)b->_data)[arg2] = GPR_005549c4;
            ret = 1;
        }
    } else ret = 0;
    return ret;
}

int SYSctlPlayer(const char *property, const char *command, int playerIndex, int value) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], property);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendInt(g_beMessenger[0], playerIndex);
    beMessenger_AppendInt(g_beMessenger[0], value);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLPLAYER);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

void CFLclear(void) {
    L *s5;
    int s4;
    int i;
    int **slot;
    int *s1;
    int off;
    int *old;
    int v;
    s5 = (L *)g_beSystem[0]->_readFileList;
    s4 = s5->n;
    i = 0;
    if (0 < s4) {
        off = 0;
        do {
            slot = (int **)((char *)s5->data + off);
            if (g_stringPool[0] == 0) {
                v = FUN_002eb010(0x10);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                g_stringPool[0] = v;
            }
            s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
            old = *slot;
            if (old != 0) {
                int *hdr = old - 2;
                int r = old[-1] - 1;
                old[-1] = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*hdr, hdr);
                }
            }
            i += 1;
            *slot = s1;
            off += 4;
        } while (i < s4);
    }
    s5->n = 0;
    {
        L *l2 = (L *)g_beSystem[0]->_readFileList;
        if (!(0 < l2->n)) {
            List_Reserve(l2, 0, 4);
        }
    }
}

void CFLsetName(int arg0) {
    int v2;
    void *v;
    igStringRefList *list;
    int n;
    bool found;
    int i;

    found = false;
    list = (igStringRefList *)g_beSystem[0]->_readFileList;
    n = list->_count;
    i = 0;
    if (0 < n) {
    do {
        {
            StringRef name = StringList_CopyRetained(list, i);
            if (strcmp(name.p, arg0) == 0) {
                found = true;
                break;
            }
        }
        i++;
    } while (i < n);
    }
    if (!((int)found & 0xff)) {
        if (arg0 == 0) {
            v = 0;
        } else {
            if (g_stringPool[0] == 0) {
                v2 = FUN_002eb010(16);
                if (v2 != 0) {
                    v2 = StringPool_Construct(v2);
                }
                g_stringPool[0] = v2;
            }
            v = StringPool_Intern(g_stringPool[0], arg0);
        }
        {
            StringRef fresh(v);
            StringList_AppendRetained(list, &fresh);
        }
    }
}

int CFLgetFolderName(void) {
    return g_beSystem[0]->_stageName;
}

void Lua_sd_OptionalArg(int arg0) {
    char *parts[12];
    char buf[1024];
    float tmp[3];
    float vec[3];
    float fv;
    char *q;
    char *s;
    int c;
    int iv;
    bool sign;
    int k;
    long long lv;
    int n;
    int i;
    igStringObj *seq;
    char **pp;
    char *p;

    if (*(char *)arg0 != 0) {
        p = (char *)arg0;
        if (strlen(p) > 0x400) {
            p[1023] = 0;
        }
        n = 0;
        q = buf;
        parts[n++] = q;
        pp = &parts[0];
        for (;;) {
            c = *p;
            if (c == 0) {
                *q = 0;
                break;
            }
            if (c == 0x2F) {
                *q = 0;
                p++;
                q++;
                parts[n++] = q;
            } else {
                *q = c;
                p++;
                q++;
            }
        }
        {
            for (i = 0; i < n; i++, pp++) {
                s = *pp;
                if (s[1] != 0x3C) {
                    beMessenger_AppendString(g_beMessenger[0], s);
                } else {
                    switch (s[0]) {
                    case 0x49:
                        iv = 0;
                        sign = false;
                        k = 2;
                        if (s[2] == 0x2D) {
                            sign = true;
                            k++;
                        }
                        while (s[k] != 0x3E) {
                            iv = iv * 10;
                            iv += s[k] - 0x30;
                            k++;
                        }
                        if (sign) iv = -iv;
                        beMessenger_AppendInt(g_beMessenger[0], iv);
                        break;
                    case 0x4C:
                        lv = 0;
                        k = 2;
                        while (s[k] != 0x3E) {
                            lv = lv * 10;
                            lv += s[k] - 0x30;
                            k++;
                        }
                        beMessenger_AppendLong(g_beMessenger[0], lv);
                        break;
                    case 0x56:
                        FUN_001e6d30(s + 1, tmp, &DAT_0050dab0[0]);
                        vec[0] = tmp[0];
                        vec[1] = tmp[1];
                        vec[2] = tmp[2];
                        beMessenger_AppendVec3(g_beMessenger[0], vec);
                        break;
                    case 0x46:
                        seq = (igStringObj *)g_beSystem[0]->_globalStrObj;
                        FUN_0030b3c0(seq, s + 2);
                        FUN_0030bbf0(seq, seq->_length - 1, 1);
                        FUN_0030b630(seq, &fv);
                        beMessenger_AppendFloat(g_beMessenger[0], fv);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

void sd_29(int arg0, int arg1, int arg2, int arg3, int arg4) {
    beMessenger_SelectReceivers(g_beMessenger[0], arg0, arg1, arg2);
    if (arg4 != 0) {
        Lua_sd_OptionalArg(arg4);
    }
    beMessenger_DispatchSelected(g_beMessenger[0], arg3);
}

void sd_30(int arg0, int arg1, int arg2, int arg3) {
    beMessenger_SendNamed(g_beMessenger[0], arg0, arg1, arg2, arg3);
}

void sd_31(int arg0, int arg1, int arg2, int arg3, int arg4, long long arg5) {
    beMessenger_PrepareDelayedSelection(g_beMessenger[0], arg0, arg1, arg2);
    if (arg4 != 0) {
        Lua_sd_OptionalArg(arg4);
    }
    beMessenger_EnqueueSelected(g_beMessenger[0], arg3, arg5);
}

void sd_32(int arg0, int arg1, int arg2, int arg3, long long arg4) {
    beMessenger_SendDelayedNamed(g_beMessenger[0], arg0, arg1, arg2, arg3, arg4);
}

unsigned char MATisPlayer(void) { return beMatCtrl_IsPlayer(g_matCtrl[0]); }

bool MATisAllPlayer(void) { return beMatCtrl_IsAllPlayer(g_matCtrl[0]); }

int MATgetPlayerNo(void) { return beMatCtrl_GetPlayerNo(g_matCtrl[0]); }

bool MATisRidePlayer(int player) { return beMatCtrl_IsRidePlayer(g_matCtrl[0], player); }

bool MATisRideOffPlayer(int player) { return beMatCtrl_IsRideOffPlayer(g_matCtrl[0], player); }

int MATgetPlayerMatStat(int player) { return beMatCtrl_GetPlayerMatStat(g_matCtrl[0], player); }

void MATsetRun(int value) { beMatCtrl_SetRun(g_matCtrl[0], value); }

void DMsetSD_40(int arg0, int arg1, int arg2, int arg3, int arg4, long long arg5) {
    FUN_0037e3a0(((int *)DAT_0058a1d0)[0], 0, arg0, arg1, arg2, arg3, arg4, arg5);
}

void DMsetSD_41(int arg0, int arg1, int arg2, int arg3, int arg4) {
    FUN_0037e3a0(((int *)DAT_0058a1d0)[0], 0, arg0, arg1, arg2, arg3, arg4, 0);
}

void DMsetSD_42(int arg0, int arg1, int arg2, int arg3, long long arg4) {
    FUN_0037e3a0(((int *)DAT_0058a1d0)[0], 0, arg0, arg1, arg2, arg3, 0, arg4);
}

void DMsetSD_43(char * p0, int p1, int p2, int p3)
{
    FUN_0037e3a0(*(int *)0x0058a1d0, 0, p0, p1, p2, p3, 0, 0);
}

void DMchkSD_44(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    if (strcmp(&DAT_0050dac8[0], arg5) == 0 || strcmp(&DAT_0050dad0[0], arg5) == 0) {
        FUN_0037e3a0(((int *)DAT_0058a1d0)[0], 2, arg0, arg1, arg2, arg3, arg4, 0);
    } else if (strcmp(&DAT_0050dad8[0], arg5) == 0 || strcmp(&DAT_0050dae0[0], arg5) == 0) {
        FUN_0037e3a0(((int *)DAT_0058a1d0)[0], 1, arg0, arg1, arg2, arg3, arg4, 0);
    }
}

void DMchkSD_45(int arg0, int arg1, int arg2, int arg3, int arg4) {
    if (strcmp(&DAT_0050dac8[0], arg4) == 0 || strcmp(&DAT_0050dad0[0], arg4) == 0) {
        FUN_0037e3a0(((int *)DAT_0058a1d0)[0], 2, arg0, arg1, arg2, arg3, 0, 0);
    } else if (strcmp(&DAT_0050dad8[0], arg4) == 0 || strcmp(&DAT_0050dae0[0], arg4) == 0) {
        FUN_0037e3a0(((int *)DAT_0058a1d0)[0], 1, arg0, arg1, arg2, arg3, 0, 0);
    }
}

void DMsetLua(char * p0)
{
    FUN_0037e6e0(*(int *)0x0058a1d0, p0);
}

void DMmsgBox(int arg0, int arg1) {
    FUN_0037e890(((int *)DAT_0058a1d0)[0], arg0, arg1);
}

void DMswtSD_46(int arg0, int arg1, int arg2, int arg3, int arg4) {
    FUN_0037e110(((int *)DAT_0058a1d0)[0], arg0, arg1, arg2, arg3, arg4);
}

void DMswtSD_47(int arg0, int arg1, int arg2, int arg3) {
    FUN_0037e110(((int *)DAT_0058a1d0)[0], arg0, arg1, arg2, arg3, 0);
}

void DMswtEnd(void)
{
    FUN_0037e180(*(int *)0x0058a1d0);
}

void DMcase(char * p0)
{
    FUN_0037e2d0(*(int *)0x0058a1d0, p0);
}

void DMrun(void)
{
    FUN_0037ea50(*(int *)0x0058a1d0);
}

int DMgetCount(void) {
    int temp_v0;
    temp_v0 = DAT_0058a1d0[0]->f1c->f8;
    if (temp_v0 != 0) { return temp_v0; }
    beMessenger_SendNamed(g_beMessenger[0], &DAT_0050dae8[0], 0, 0, &DAT_0050daf0[0]);
    if (beMessenger_GetBoolCount(g_beMessenger[0]) == 0) { return 0; }
    temp_v0 = beMessenger_GetBool(g_beMessenger[0], 0);
    temp_v0 = (temp_v0 & 0xFF) != 0;
    return -temp_v0;
}

unsigned char FLGisOn(int arg0) {
    int temp_v0;
    int *r;

    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    temp_v0 = beMessenger_GetObject(g_beMessenger[0], 0);
    if (arg0 == 0x3E8) {
        return SYSgetPlayerNinzu() != 0;
    }
    r = ((int *)igProperty_GetRecordArray(temp_v0, FLAG));
    return *(unsigned char *)(((igDataList *)r[3])->_data + arg0);
}

void FLGset(int arg0, unsigned char arg1) {
    igDataList *temp_a0;
    int temp_v1;

    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    temp_a0 = (igDataList *)(*(int *)((char *)(igProperty_GetRecordArray(beMessenger_GetObject(g_beMessenger[0], 0), FLAG)) + 12));
    temp_v1 = temp_a0->_count;
    if ((temp_v1 != 0) && (arg0 >= 0) && (arg0 < temp_v1)) {
        *(char *)(arg0 + temp_a0->_data) = arg1;
    }
}

void FLGflip(int arg0) {
    int obj;
    igUnsignedCharList *a;
    int cnt;
    unsigned char *p;
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    obj = beMessenger_GetObject(g_beMessenger[0], 0);
    p = (unsigned char *)((struct Rec *)igProperty_GetRecordArray(obj, FLAG))->f12->_data;
    if (p[arg0] != 0) {
        a = ((struct Rec *)igProperty_GetRecordArray(obj, FLAG))->f12;
        cnt = a->_count;
        if (cnt != 0 && arg0 >= 0 && arg0 < cnt) {
            ((unsigned char *)a->_data)[arg0] = GPR_005549c8;
        }
    } else {
        a = ((struct Rec *)igProperty_GetRecordArray(obj, FLAG))->f12;
        cnt = a->_count;
        if (cnt != 0 && arg0 >= 0 && arg0 < cnt) {
            ((unsigned char *)a->_data)[arg0] = GPR_005549cc;
        }
    }
}

void COUNTERset(int arg0, int arg1) {
    igIntList *temp_a1;
    int temp_v1;
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, GETCOMMON);
    temp_a1 = (igIntList *)(*(int *)((char *)(FUN_003a9250(beMessenger_GetObject(g_beMessenger[0], 0), &DAT_0050daf8[0])) + 12));
    temp_v1 = temp_a1->_count;
    if ((temp_v1 != 0) && (arg0 >= 0) && (arg0 < temp_v1)) {
        *(int *)(temp_a1->_data + (arg0 * 4)) = arg1;
    }
}

int COUNTERget(int arg0)
{
  int *new_var;
  beMessenger_SendNamed(g_beMessenger[0, 0], GAMERAM, 0, 0, GETCOMMON);
  new_var = (int *) (((char *) FUN_003a9250(beMessenger_GetObject(g_beMessenger[0], 0), &DAT_0050daf8[0])) + 12);
  return *((int *) ((*((int *) (((char *) (*new_var)) + 16))) + (arg0 * 4)));
}

int MDLgetRamNo(void)
{
    return g_mdlRamNo[0];
}

int MDLgetInfoName(void)
{
    return g_mdlInfoName[0];
}

char *MDLgetPosStr(float fparg0, float fparg1, float fparg2) {
    struct M m;
    struct V3 b;
    struct V3 a;
    long long s1;
    long long s0;

    igMatrix44f_SetIdentity((float *)&m);
    Matrix44_Copy(&m, ((void * *)DAT_0058a1e8)[0]);
    b.x = fparg0;
    b.y = fparg1;
    b.z = fparg2;
    Matrix44_TranslateLocal((float *)&m, (float *)&b);
    Matrix44_GetTranslation((int)&m, (float *)&a);
    s1 = fptodp(a.x);
    s0 = fptodp(a.y);
    sprintf(DAT_0058a230, ((char *)DAT_0050db00), s1, s0, fptodp(a.z));
    return DAT_0058a230;
}

int *MDLgetRotStr(float fparg0, float fparg1, float fparg2) {
    float vec[4];
    float mat[16];
    float ang;
    long long a;
    long long b;
    igMatrix44f_SetIdentity(mat);
    FUN_001908f0(mat, DAT_0058a1e8[0]);
    FUN_00192f50(vec, DAT_004e1098, mat);
    ang = atan2f(vec[0], vec[2]);
    a = fptodp(fparg0);
    b = fptodp(57.29578f * ang + fparg1);
    sprintf(DAT_0058a270, DAT_0050db00, a, b, fptodp(fparg2));
    return DAT_0058a270;
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
    g_mdlHp[0] = (int) (g_mdlHp[0] + amount);
    if (g_mdlHp[0] < 0) {
        g_mdlHp[0] = 0;
    }
}

void MDLsetSeq(char * p0)
{
    beMessenger_SendNamed(*(int *)0x0058a1c0, ((char *)DAT_0050db10), *(int *)0x0058a1f8, *(int *)0x0058a1e4, p0);
}

void MDLsetSD(char * p0, char * p1)
{
    sd_29((int)(((char *)DAT_0050db10)), *(int *)0x0058a1f8, *(int *)0x0058a1e4, (int)p0, (int)p1);
}

bool MDLisLive(int arg0, int arg1) {
    int n;
    bool r;
    int i;
    beMessenger_SendNamed(g_beMessenger[0], DAT_0050db10, arg0, arg1, DAT_0050daf0);
    n = beMessenger_GetBoolCount(g_beMessenger[0]);
    r = false;
    for (i = 0; i < n; i++) {
        if (beMessenger_GetBool(g_beMessenger[0], i)) {
            r = true;
            break;
        }
    }
    return r;
}

int MDLgetBulletKind(void)
{
    return g_mdlBulletKind[0];
}

int MDLgetBulletName(void) {
    return DAT_004c873c[(int) g_mdlBulletKind[0] / 10000];
}

int MDLgetBulletBoxNo(void)
{
    return g_mdlBulletBoxNo[0];
}

void FloatingNumber_Spawn(int dmg, int row) {
    int a = DAT_004c8770[row].w[0];
    int b = DAT_004c8774[row].w[0];
    beBaseInfoRam *obj;
    int idx;
    int s;
    struct DmgVec v;
    struct DmgVec w;
    beMessenger_SendNamed(g_beMessenger[0], DAT_0050db10, a, -1, DAT_0050dd00);
    if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
        obj = ((beBaseInfoRam *)beMessenger_GetObject(g_beMessenger[0], 0));
        if (dmg < 10) idx = 0;
        else if (dmg < 100) idx = 1;
        else if (dmg < 1000) idx = 2;
        else if (dmg < 10000) idx = 3;
        else if (dmg < 100000) idx = 4;
        else { idx = 4; dmg = 99999; }
        s = DAT_004c8778[row].w[idx];
        beMessenger_SelectReceivers(g_beMessenger[0], DAT_0050db10, a, obj->_ramNo);
        beMessenger_AppendString(g_beMessenger[0], s);
        Matrix44_GetTranslation(DAT_0058a1e8[0], (float *)&v);
        w.x = v.x; w.y = v.y; w.z = v.z;
        beMessenger_AppendVec3(g_beMessenger[0], (float *)&w);
        beMessenger_DispatchSelected(g_beMessenger[0], DAT_0050dd10);
        beMessenger_SelectReceivers(g_beMessenger[0], DAT_0050dd20, b, obj->_ramNo);
        beMessenger_AppendInt(g_beMessenger[0], dmg);
        beMessenger_DispatchSelected(g_beMessenger[0], DAT_0050dd30);
    }
}

void MDLdspDamage(int p0)
{
    FloatingNumber_Spawn(p0, 0);
}

void MDLdspDamageP(int p0)
{
    FloatingNumber_Spawn(p0, 3);
}

void MDLdspExp(int p0)
{
    FloatingNumber_Spawn(p0, 1);
}

/* matching construct: a named extern byte changes the address materialisation. */
void MDLsetDMGTurn(int value) {
    *(char *)0x58A210 = value == 1;
}

static inline int isZero(int value) { return value == 0; }

int MDLisCallName(char *name) {
    char *s = DAT_0058a214[0];
    if (s == 0) return isZero((int)name);
    return isZero(strcmp(s, name));
}

void MDLsetWorldPosTarget_78(float fparg0, float fparg1, float fparg2) {
    float *p = ((float * *)DAT_0058a218)[0];
    if (p != 0) {
        p[0] = fparg0;
        p[1] = fparg1;
        p[2] = fparg2;
    }
}

void MDLsetWorldPosTarget_79(int arg0) {
    V3 sp10;
    float a, b, c;
    V3 *t;

    if (DAT_0058a218[0] != 0) {
        FUN_001e6d30((char *)arg0, (float *)&sp10, &DAT_0050db00[0]);
        a = sp10.x; c = sp10.z; b = sp10.y;
        t = DAT_0058a218[0];
        t->x = a;
        t->y = b;
        t->z = c;
    }
}

float MDLgetKyoriSquare(float x, float y, float z) {
    float v[3];
    float dx, dy, dz;
    Matrix44_GetTranslation(DAT_0058a1e8[0], v);
    dy = v[1] - y;
    dx = v[0] - x;
    dz = v[2] - z;
    return dx * dx + dy * dy + dz * dz;
}

int MDLgetRecNo(void)
{
    return g_mdlRecNo[0];
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

int MDLisSeqName(char *arg0) {
    beBaseInfoRam *h = g_mdlEntity[0];
    if (h->_dataList == 0) {
        int al;
        igObject *o;
        al = igObject_GetAllocator(h);
        al = GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(al));
        igObject *s0 = ref.get();
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        o = (igObject *)h->_dataList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        h->_dataList = (int)s0;
    }
    beModelCtrlInfoRamData *p = igProperty_FindByName(h->_dataList, g_propertyNameField[0], &DAT_0050dd40[0]);
    return strcmp((const char *)((beModelCtrlInfoWork *)p->_work)->_seqCodeName, arg0) == 0;
}

int MDLisStatus(int arg0, int arg1, int arg2) {
    beMessenger_SelectReceivers(g_beMessenger[0], &DAT_0050db10[0], arg0, arg1);
    beMessenger_AppendString(g_beMessenger[0], arg2);
    beMessenger_DispatchSelected(g_beMessenger[0], &DAT_0050dd48[0]);
    if (beMessenger_GetBoolCount(g_beMessenger[0]) == 1) {
        return beMessenger_GetBool(g_beMessenger[0], 0);
    }
    return 0;
}

int PLAYERgetPos(void) {
    beMessenger_SendGroup(g_beMessenger[0], PLAYERPOINT, GETGENERATEPOS);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int *PLAYERgetDataStr(int arg0, int arg1, float fparg0) {
    float ang;
    float v[3];
    float mat[16];
    float t[3];
    int c, b, a;

    beMessenger_SelectGroup(g_beMessenger[0], PLAYERPOINT);
    beMessenger_AppendInt(g_beMessenger[0], arg0);
    beMessenger_AppendInt(g_beMessenger[0], arg1);
    beMessenger_DispatchSelected(g_beMessenger[0], &DAT_0050dd80[0]);
    beMessenger_GetMatrix(mat, g_beMessenger[0], 0);
    Matrix44_GetTranslation((int)mat, t);
    FUN_00192f50(v, &DAT_004e1098[0], mat);
    ang = atan2f(v[0], v[2]);
    sprintf(&DAT_0058a2b0[0], &DAT_0050dd90[0], (fptodp(t[0])), (fptodp(t[1])), (fptodp(t[2])), fptodp((57.29578f * ang) + fparg0));
    return &DAT_0058a2b0[0];
}

int *PLAYERgetPosStr(int arg0, float fparg0, float fparg1, float fparg2) {
    float sp90[3];
    float sp80[4];
    float sp40[16];
    long long temp_s1;
    long long temp_s0;

    beMessenger_SendNamed(g_beMessenger[0], &DAT_0050dda8[0], 0, arg0, &DAT_0050ddb0[0]);
    if (beMessenger_GetMatrixCount(g_beMessenger[0]) != 0) {
        beMessenger_GetMatrix(sp40, g_beMessenger[0], 0);
        sp90[0] = fparg0;
        sp90[1] = fparg1;
        sp90[2] = fparg2;
        Matrix44_TranslateLocal(sp40, sp90);
        Matrix44_GetTranslation((int)sp40, sp80);
        temp_s1 = fptodp(sp80[0]);
        temp_s0 = fptodp(sp80[1]);
        sprintf(&DAT_0058a2f0[0], &DAT_0050db00[0], temp_s1, temp_s0, fptodp(sp80[2]));
        return &DAT_0058a2f0[0];
    }
    return 0;
}

void MsgBox(int, int)
{
}

void ShutDown(void) {
    beSystem *s0;
    int s1;
    int *a0;
    int *hdr;
    int v;
    int obj;
    s0 = g_beSystem[0];
    s0->_isShutDown = 1;
    s0->_isStageLoop = 0;
    if (g_stringPool[0] == 0) {
        obj = FUN_002eb010(0x10);
        if (obj != 0) {
            obj = StringPool_Construct(obj);
        }
        g_stringPool[0] = obj;
    }
    s1 = ((int)StringPool_Intern(g_stringPool[0], 0));
    a0 = (int *)s0->_nextStage;
    if (a0 != 0) {
        hdr = a0 - 2;
        v = a0[-1] - 1;
        a0[-1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    s0->_nextStage = s1;
}

int TXTgetCallNo(void)
{
    return g_txtCallNo[0];
}

/* True below 1000, for 10000..59999 and for 80000..89999. The cached code is signed and not range-
 * checked, so a negative code also counts. */
int BLTisPlayerBullet(void) {
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

/* Ask FIGHTCALC (P2EISHITCHECK) whether the cached player attack hits. When an InfoName is cached,
 * the named ENEMY object's base work (GETPEBASEWORK reply, index 1) is passed to FIGHTCALC as an
 * object argument. */
int BLTisHitCheck(void) {
    extern int g_mdlRecNo[4];
    extern int g_bltShootRamNo[4];
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
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

/* The bool reply is read but not returned. */
int BLTisCritical(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EISCRITICAL);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

/* P2EDAMAGE. The Lua caller supplies the critical flag (masked to 8 bits, arg3). The reply's three
 * integers (damage, attribute index, rank flag) are cached for BLTgetDamageRank and
 * BLTgetAttributeStr, and the damage is returned. */
int BLTgetDamageValue(int criticalFlag) {
    extern int g_mdlRecNo[4];
    extern int g_bltShootRamNo[4];
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
    beMessenger_AppendInt(g_beMessenger[0], criticalFlag & 0xFF);
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
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
        group = (int)((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE);
        if ((group == BULLET_KIND_RANK_BONUS_GROUP_A) || (group == BULLET_KIND_RANK_BONUS_GROUP_B)) {
            rank += 1;
        }
    }
    return rank;
}

/* Name of the cached damage attribute ("fire", "ice", "thunder", "dark"); any index of 4 or more
 * gives "common". Scripts build the "SQ_LDMG/<attribute>" sequence label from it. */
char *BLTgetAttributeStr(void)
{
    if (g_attackZokusei[0] >= 4)
        return g_attributeNameDefault[0];
    return g_attributeNames[g_attackZokusei[0]];
}

int BLTgetStunTime(int intArg, unsigned char byteArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2ESTUNTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlMaxHp[0]);
    beMessenger_AppendInt(g_beMessenger[0], intArg);
    beMessenger_AppendInt(g_beMessenger[0], byteArg & 0xFF);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* The five BLTget*Time helpers share one shape: only a technique attack (group 4) of the matching
 * sub-kind carries the status effect; otherwise 0 without messaging. Then the matching P2E*TIME
 * command is sent to FIGHTCALC with the cached arguments and its first integer is the duration.
 * Poison, attack-down and power-down also pass the script's `effectKey` string. */

/* Poison duration (P2EPOISONTIME). */
int BLTgetPoisonTime(const char *effectKey) {
    extern int g_mdlRecNo[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POISON) {
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

/* Sleep duration (P2ESLEEPTIME). */
int BLTgetSleepTime(void) {
    extern int g_mdlRecNo[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_SLEEP) {
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

/* Bind duration (P2EBINDTIME). */
int BLTgetBindTime(void) {
    extern int g_mdlRecNo[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_BIND) {
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

/* Attack-down duration (P2EATKDWNTIME). */
int BLTgetAttackDownTime(const char *effectKey) {
    extern int g_mdlRecNo[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_ATTACK_DOWN) {
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

/* Power-down duration (P2EPOWDWNTIME). */
int BLTgetPowerDownTime(const char *effectKey) {
    extern int g_mdlRecNo[4];
    extern int g_bltShootRamNo[4];
    if (((int) g_mdlBulletKind[0] / BULLET_KIND_GROUP_SIZE) != BULLET_KIND_TECHNIQUE_GROUP) {
        return 0;
    }
    if (((int) g_mdlBulletKind[0] % BULLET_KIND_GROUP_SIZE) != BULLET_SUBKIND_POWER_DOWN) {
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

void BLTcalcSkillUp(int firstByte, int secondByte) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2ESKILLUP);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], firstByte & 0xFF);
    beMessenger_AppendInt(g_beMessenger[0], secondByte & 0xFF);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
}

int BLTcalcEXPUp(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EEXPUP);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* The bool reply is read but not returned. */
int BLPisHitCheck(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PISHITCHECK);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetBool(g_beMessenger[0], 0);
}

/* E2PDAMAGE, the enemy-to-player counterpart of BLTgetDamageValue. Same caching of the reply
 * (damage, attribute, rank flag); the argument order differs from the P2E command. */
int BLPgetDamageValue(void) {
    extern int g_bltShootRamNo[4];
    int baseWork;

    baseWork = 0;
    if (g_statusFieldA[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_statusFieldA[0], g_bltShootRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PDAMAGE);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_damageResult[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 1);
    g_damageFlag[0] = beMessenger_GetInt(g_beMessenger[0], 2);
    return g_damageResult[0];
}

int BLPgetAttackZokusei(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], GETPATKZOKUSEI);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    return ((int)BLTgetAttributeStr());
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
    extern int g_bltShootRamNo[4];
    int baseWork;

    baseWork = 0;
    if (g_statusFieldA[0] != 0) {
        beMessenger_SendNamed(g_beMessenger[0], ENEMY, g_statusFieldA[0], g_bltShootRamNo[0], GETPEBASEWORK);
        if (beMessenger_GetObjectCount(g_beMessenger[0]) != 0) {
            baseWork = beMessenger_GetObject(g_beMessenger[0], 1);
        }
    }
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PSTUNTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg1);
    beMessenger_AppendInt(g_beMessenger[0], scriptArg2);
    beMessenger_AppendObject(g_beMessenger[0], baseWork);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetPoisonTime(const char *stringArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PPOISONTIME);
    beMessenger_AppendString(g_beMessenger[0], stringArg);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetSleepTime(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PSLEEPTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetBindTime(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PBINDTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetAttackDownTime(const char *stringArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PATKDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], stringArg);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

int BLPgetPowerDownTime(const char *stringArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PPOWDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], stringArg);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    return beMessenger_GetInt(g_beMessenger[0], 0);
}

/* KOUKA: "effect". */
int BLPcalcKoukaMagic(void) {
    extern char FIGHTCALC[];
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

int Gap__Bec__be__vfunc_20(void)
{
    return g_be_metaObject[0];
}


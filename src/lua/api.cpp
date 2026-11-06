/* Native functions behind the game scripts' `be:` calls. */
#include "dw4/reflected.h"

#define PLAYER_SLOT_COMMON 0
extern "C" {
typedef struct PropertyRecord {
    char unknown0[12];
    int value;
} PropertyRecord;

/* Player slot 0 is the shared GETCOMMON record; Lua player index N is slot N + 1. */

int bePlayer_GetStruct(int);
void *igProperty_GetRecordByte(int, char *);
void *FUN_003a92e0(int, char *);
void *igProperty_GetRecord(int, char *);
int beMessenger_SendGroup(int, char *, char *);
int beMessenger_GetObject(int, int);
int beMessenger_DispatchSelected(int, char *);
int beMessenger_SelectGroup(int, char *);
int beMessenger_GetBool(int, int);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, const void *);
int beMessenger_GetInt(int, int);
int BLTgetAttributeStr();
int beMessenger_SelectReceivers(int, char *, int, int);

extern char ISUSE[];
extern char DIGIMONNAME[];
extern char NINZU[];
extern char DIFFICULTY[];
extern char GAMERAM[];
extern char GETCOMMON[];
extern char CAMERAMODE[];
extern char LIGHTMODE[];
extern char GATESTAGENAME[];
extern char GATESTAGENO[];
extern char DEVICE[];
extern char CTRLITEM[];
extern char EMPTY[];
extern char DISK[];
extern char FLAG[];
extern char BIT[];
extern char LEVEL[];
extern char DIGIMONNO[];
extern char CTRLPLAYER[];
extern char PLAYERPOINT[];
extern char GETGENERATEPOS[];
extern char P2EISCRITICAL[];
extern char P2ESTUNTIME[];
extern char P2ESKILLUP[];
extern char P2EEXPUP[];
extern char E2PISHITCHECK[];
extern char GETPATKZOKUSEI[];
extern char E2PPOISONTIME[];
extern char E2PSLEEPTIME[];
extern char E2PBINDTIME[];
extern char E2PATKDWNTIME[];
extern char E2PPOWDWNTIME[];
extern char P2PKOUKAMAGIC[];
extern char LOADINTF2[];
extern char SETDIFFICULTMAX[];

/* The array form keeps the access an absolute load, as retail does. */
extern int g_beSystem[4];
extern int g_beMessenger[4];

/* The "MDL" block: values the damage and item controllers leave for the next `be:` call. */
extern int g_mdlRamNo[4];
extern int g_mdlMaxHp[4];
extern int g_mdlHp[4];
extern int g_mdlRecNo[4];
extern int g_mdlInfoName[4];
extern int g_mdlBulletKind[4];
extern int g_mdlBulletBoxNo[4];
extern int g_bltShootRamNo[4];
extern int g_blpStatus[4];
extern int g_txtCallNo[4];
extern int g_attackZokusei[4];        
unsigned char SYSisJoinPlayer(int playerIndex);
int SYSgetPlayerName(int playerIndex);
int SYSgetPlayerNinzu(void);
int SYSgetDifficulty(void);
void SYSsetDifficulty(int difficulty);
int SYSgetCameraMode(void);
int SYSgetLightMode(void);
int SYSgetArea(void);
int SYSgetCountry(void);
int SYSgetTarget(void);
int SYSgetIsPackOnly(void);
int SYSgetGateStageName(void);
int SYSgetGateStageNo(void);
void SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1);
void SYSctlDiskFolder(const char *command, int index, int itemId, int count);
void SYSctlFlagFolder(const char *command, int index);
void SYSctlBit(const char *command, int index, int value);
int SYSgetPlayerLevel(int playerIndex);
int SYSgetPlayerDigimon(int playerIndex);
void SYSctlPlayer(const char *property, const char *command, int playerIndex, int value);
int CFLgetFolderName(void);
int MDLgetRamNo(void);
int MDLgetInfoName(void);
int MDLgetMHp(void);
int MDLgetHp(void);
void MDLaddHp(int amount);
int MDLgetBulletKind(void);
int MDLgetBulletBoxNo(void);
void MDLsetDMGTurn(int value);
int MDLgetRecNo(void);
void PLAYERgetPos(void);
void MsgBox(void);
int TXTgetCallNo(void);
int BLTgetShootRamNo(void);
void BLTisCritical(void);
void BLTgetStunTime(int intArg, int byteArg);
void BLTcalcSkillUp(int firstByte, int secondByte);
void BLTcalcEXPUp(void);
void BLPisHitCheck(void);
void BLPgetAttackZokusei(void);
void BLPgetPoisonTime(const char *stringArg);
void BLPgetSleepTime(void);
void BLPgetBindTime(void);
void BLPgetAttackDownTime(const char *stringArg);
void BLPgetPowerDownTime(const char *stringArg);
void BLPcalcKoukaMagic(void);
void LISsetDifficultMax(int maxDifficulty);
}

/* ZOKUSEI: attack attribute */

unsigned char SYSisJoinPlayer(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecordByte(bePlayer_GetStruct(playerIndex + 1), ISUSE))->value;
}

int SYSgetPlayerName(int playerIndex) {
    return ((PropertyRecord *)FUN_003a92e0(bePlayer_GetStruct(playerIndex + 1), DIGIMONNAME))->value;
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

int SYSgetGateStageName(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return ((PropertyRecord *)FUN_003a92e0(beMessenger_GetObject(g_beMessenger[0], 0), GATESTAGENAME))->value;
}

int SYSgetGateStageNo(void) {
    beMessenger_SendGroup(g_beMessenger[0], GAMERAM, GETCOMMON);
    return ((PropertyRecord *)igProperty_GetRecord(beMessenger_GetObject(g_beMessenger[0], 0), GATESTAGENO))->value;
}

void SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], DEVICE);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], itemDb);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], itemId);
    beMessenger_AppendInt(g_beMessenger[0], extra0);
    beMessenger_AppendInt(g_beMessenger[0], extra1);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    beMessenger_GetBool(g_beMessenger[0], 0);
}

void SYSctlDiskFolder(const char *command, int index, int itemId, int count) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], DISK);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], EMPTY);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], itemId);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], count);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    beMessenger_GetBool(g_beMessenger[0], 0);
}

void SYSctlFlagFolder(const char *command, int index) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], FLAG);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], EMPTY);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    beMessenger_GetBool(g_beMessenger[0], 0);
}

void SYSctlBit(const char *command, int index, int value) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], BIT);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendString(g_beMessenger[0], EMPTY);
    beMessenger_AppendInt(g_beMessenger[0], index);
    beMessenger_AppendInt(g_beMessenger[0], value);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_AppendInt(g_beMessenger[0], 0);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLITEM);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

int SYSgetPlayerLevel(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), LEVEL))->value;
}

int SYSgetPlayerDigimon(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), DIGIMONNO))->value;
}

void SYSctlPlayer(const char *property, const char *command, int playerIndex, int value) {
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], property);
    beMessenger_AppendString(g_beMessenger[0], command);
    beMessenger_AppendInt(g_beMessenger[0], playerIndex);
    beMessenger_AppendInt(g_beMessenger[0], value);
    beMessenger_DispatchSelected(g_beMessenger[0], CTRLPLAYER);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

int CFLgetFolderName(void) {
    return ((beSystem *)g_beSystem[0])->_stageName;
}

int MDLgetRamNo(void)
{
    return g_mdlRamNo[0];
}

int MDLgetInfoName(void)
{
    return g_mdlInfoName[0];
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

int MDLgetBulletKind(void)
{
    return g_mdlBulletKind[0];
}

int MDLgetBulletBoxNo(void)
{
    return g_mdlBulletBoxNo[0];
}

/* matching construct: a named extern byte changes the address materialisation. */
void MDLsetDMGTurn(int value) {
    *(char *)0x58A210 = value == 1;
}

int MDLgetRecNo(void)
{
    return g_mdlRecNo[0];
}

void PLAYERgetPos(void) {
    beMessenger_SendGroup(g_beMessenger[0], PLAYERPOINT, GETGENERATEPOS);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

void MsgBox(void)
{
}

int TXTgetCallNo(void)
{
    return g_txtCallNo[0];
}

int BLTgetShootRamNo(void)
{
    return g_bltShootRamNo[0];
}

/* The bool reply is read but not returned. */
void BLTisCritical(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EISCRITICAL);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetBool(g_beMessenger[0], 0);
}

void BLTgetStunTime(int intArg, int byteArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2ESTUNTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlMaxHp[0]);
    beMessenger_AppendInt(g_beMessenger[0], intArg);
    beMessenger_AppendInt(g_beMessenger[0], byteArg & 0xFF);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
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

void BLTcalcEXPUp(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2EEXPUP);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRecNo[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

/* The bool reply is read but not returned. */
void BLPisHitCheck(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PISHITCHECK);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetBool(g_beMessenger[0], 0);
}

void BLPgetAttackZokusei(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], GETPATKZOKUSEI);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    g_attackZokusei[0] = beMessenger_GetInt(g_beMessenger[0], 0);
    BLTgetAttributeStr();
}

void BLPgetPoisonTime(const char *stringArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PPOISONTIME);
    beMessenger_AppendString(g_beMessenger[0], stringArg);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

void BLPgetSleepTime(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PSLEEPTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

void BLPgetBindTime(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PBINDTIME);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

void BLPgetAttackDownTime(const char *stringArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PATKDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], stringArg);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

void BLPgetPowerDownTime(const char *stringArg) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], E2PPOWDWNTIME);
    beMessenger_AppendString(g_beMessenger[0], stringArg);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_blpStatus[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

/* KOUKA: "effect". */
void BLPcalcKoukaMagic(void) {
    extern char FIGHTCALC[];
    beMessenger_SelectGroup(g_beMessenger[0], GAMERAM);
    beMessenger_AppendString(g_beMessenger[0], P2PKOUKAMAGIC);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_bltShootRamNo[0]);
    beMessenger_AppendInt(g_beMessenger[0], g_mdlBulletKind[0]);
    beMessenger_DispatchSelected(g_beMessenger[0], FIGHTCALC);
    beMessenger_GetInt(g_beMessenger[0], 0);
}

void LISsetDifficultMax(int maxDifficulty) {
    beMessenger_SelectReceivers(g_beMessenger[0], LOADINTF2, 0, 0);
    beMessenger_AppendInt(g_beMessenger[0], maxDifficulty);
    beMessenger_DispatchSelected(g_beMessenger[0], SETDIFFICULTMAX);
}

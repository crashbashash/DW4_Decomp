/* src/lua/api.c — the Lua native-API implementations
 *
 * One translation unit: 47 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time.
 *
 * Almost every function here is a thin shim behind a `be:` call in the game
 * scripts (lua/).  Three shapes recur:
 *   - property reads: look a named record up in a property container and
 *     return its value (docs/engine/property-system.md);
 *   - controller requests: select a receiver group on the main beMessenger,
 *     append arguments, dispatch to a named controller and read the result
 *     back (docs/engine/script-engine-lua.md);
 *   - cache reads: return one word of the "MDL" scratch block at 0x0058a1e0
 *     that the damage/item controllers fill (docs/engine/game-state.md). */
#include "dw4/reflected.h"

/* An igProperty record: the value of a named property sits at +12
 * (docs/engine/property-system.md, "record->value = new value"). */
#define PLAYER_SLOT_COMMON 0
extern "C" {
typedef struct PropertyRecord {
    char unknown0[12];
    int value;
} PropertyRecord;

/* Player slot 0 is the shared GETCOMMON record; Lua player index N is slot
 * N + 1 (bePlayer_GetStruct, docs/engine/property-system.md). */

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

/* Property names and controller keys (see the key vocabulary in
 * docs/engine/property-system.md). */
extern char s_ISUSE_0050d948[];
extern char s_DIGIMONNAME_0050d950[];
extern char s_NINZU_0050d970[];
extern char s_DIFFICULTY_0050d978[];
extern char s_GAMERAM_0050d940[];
extern char s_GETCOMMON_0050d8f0[];
extern char s_CAMERAMODE_0050d988[];
extern char s_LIGHTMODE_0050d998[];
extern char s_GATESTAGENAME_0050d9b8[];
extern char s_GATESTAGENO_0050d9a8[];
extern char s_DEVICE_0050d9d0[];
extern char s_CTRLITEM_0050d9d8[];
/* The empty string: 0x0050d9c8 holds a lone NUL in the retail image. */
extern char s_EMPTY_0050d9c8[];
extern char s_DISK_0050d9e8[];
extern char s_FLAG_0050d9f0[];
extern char s_BIT_0050d9f8[];
extern char s_LEVEL_0050da00[];
extern char s_DIGIMONNO_0050da08[];
extern char s_CTRLPLAYER_0050da98[];
extern char s_PLAYERPOINT_0050dd58[];
extern char s_GETGENERATEPOS_0050dd68[];
extern char s_P2EISCRITICAL_0050ddf8[];
extern char s_P2ESTUNTIME_0050de40[];
extern char s_P2ESKILLUP_0050dea0[];
extern char s_P2EEXPUP_0050deb0[];
extern char s_E2PISHITCHECK_0050dec0[];
extern char s_GETPATKZOKUSEI_0050dee0[];
extern char s_E2PPOISONTIME_0050df10[];
extern char s_E2PSLEEPTIME_0050df20[];
extern char s_E2PBINDTIME_0050df30[];
extern char s_E2PATKDWNTIME_0050df40[];
extern char s_E2PPOWDWNTIME_0050df50[];
extern char s_P2PKOUKAMAGIC_0050df60[];
extern char s_LOADINTF2_0050df70[];
extern char s_SETDIFFICULTMAX_0050df80[];

/* Engine globals (docs/engine/game-state.md).  The array form keeps the
 * access an absolute load, as the retail code does. */
extern int g_beSystem_0058a1b8[4];       /* game singleton, object #1 */
extern int g_beMessenger_0058a1c0[4];          /* main GAMERAM beMessenger (finding #415) */

/* The "MDL" block: values the damage and item controllers leave behind for
 * the next `be:` call to pick up. */
extern int g_mdlRamNo_0058a1e4[4];
extern int g_mdlMaxHp_0058a1ec[4];
extern int g_mdlHp_0058a1f0[4];
extern int g_mdlRecNo_0058a1f4[4];
extern int g_mdlInfoName_0058a1f8[4];
extern int g_mdlBulletKind_0058a1fc[4];
extern int g_mdlBulletBoxNo_0058a200[4];
extern int g_bltShootRamNo_0058a208[4];        /* "BLT/BLP status field", returned by BLTgetShootRamNo */
extern int g_blpStatus_0058a20c[4];            /* "BLP status field" in the doc */
extern int g_txtCallNo_0058a220[4];
extern int g_attackZokusei_0058a338[4];        
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

/* attack attribute (ZOKUSEI) last returned by GETPATKZOKUSEI */

/* 0x00371c70 */
/* be:SYSisJoinPlayer(player): whether player slot `player` is in use (ISUSE). */
unsigned char SYSisJoinPlayer(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecordByte(bePlayer_GetStruct(playerIndex + 1), s_ISUSE_0050d948))->value;
}

/* 0x00371ca0 */
/* be:SYSgetPlayerName(player): the DIGIMONNAME of the player's slot (used by
 * the scripts as a model name such as "p_wargrey"). */
int SYSgetPlayerName(int playerIndex) {
    return ((PropertyRecord *)FUN_003a92e0(bePlayer_GetStruct(playerIndex + 1), s_DIGIMONNAME_0050d950))->value;
}

/* 0x00371d70 */
/* be:SYSgetPlayerNinzu(): NINZU ("number of people"), the joined-player count,
 * kept on the common player record. */
int SYSgetPlayerNinzu(void) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), s_NINZU_0050d970))->value;
}

/* 0x00371da0 */
/* be:SYSgetDifficulty(): DIFFICULTY on the common player record. */
int SYSgetDifficulty(void) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), s_DIFFICULTY_0050d978))->value;
}

/* 0x00371dd0 */
/* be:SYSsetDifficulty(difficulty): the matching store ("record->value = new
 * value", docs/engine/property-system.md). */
void SYSsetDifficulty(int difficulty) {
    ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(PLAYER_SLOT_COMMON), s_DIFFICULTY_0050d978))->value = difficulty;
}

/* 0x00371e10 */
/* be:SYSgetCameraMode(): refresh the GETCOMMON object of the GAMERAM group,
 * then read its CAMERAMODE record. */
int SYSgetCameraMode(void) {
    beMessenger_SendGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940, s_GETCOMMON_0050d8f0);
    return ((PropertyRecord *)igProperty_GetRecord(beMessenger_GetObject(g_beMessenger_0058a1c0[0], 0), s_CAMERAMODE_0050d988))->value;
}

/* 0x00371e70 */
/* be:SYSgetLightMode(): as SYSgetCameraMode, for LIGHTMODE. */
int SYSgetLightMode(void) {
    beMessenger_SendGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940, s_GETCOMMON_0050d8f0);
    return ((PropertyRecord *)igProperty_GetRecord(beMessenger_GetObject(g_beMessenger_0058a1c0[0], 0), s_LIGHTMODE_0050d998))->value;
}

/* 0x00371ed0 */
/* be:SYSgetArea(): constant in this (USA) build. */
int SYSgetArea(void)
{
    return 1;
}

/* 0x00371ee0 */
/* be:SYSgetCountry(): constant in this (USA) build. */
int SYSgetCountry(void)
{
    return 1;
}

/* 0x00371ef0 */
/* be:SYSgetTarget(): constant in this build. */
int SYSgetTarget(void)
{
    return 1;
}

/* 0x00371f00 */
/* be:SYSgetIsPackOnly(): constant in this build. */
int SYSgetIsPackOnly(void)
{
    return 1;
}

/* 0x003720f0 */
/* be:SYSgetGateStageName(): GATESTAGENAME of the GETCOMMON object. */
int SYSgetGateStageName(void) {
    beMessenger_SendGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940, s_GETCOMMON_0050d8f0);
    return ((PropertyRecord *)FUN_003a92e0(beMessenger_GetObject(g_beMessenger_0058a1c0[0], 0), s_GATESTAGENAME_0050d9b8))->value;
}

/* 0x00372150 */
/* be:SYSgetGateStageNo(): GATESTAGENO of the GETCOMMON object. */
int SYSgetGateStageNo(void) {
    beMessenger_SendGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940, s_GETCOMMON_0050d8f0);
    return ((PropertyRecord *)igProperty_GetRecord(beMessenger_GetObject(g_beMessenger_0058a1c0[0], 0), s_GATESTAGENO_0050d9a8))->value;
}

/* 0x003721b0 */
/* be:SYSctlDeviceFolder(command, index, itemDb, itemId, extra0, extra1):
 * forwards to the CTRLITEM controller with the DEVICE selector.  Scripts call
 * it as ("ISMAX", 0, nil, 0, 0, 0), ("CLR", 0, g_SItemDB, g_SItemID, 0, 0) and
 * ("SET", 0, g_TItemDB, g_TItemID, 0, 0): the two strings are the command and
 * the item database, the four ints follow in the order index, id, extra0,
 * extra1.  The reply is read but not returned. */
void SYSctlDeviceFolder(const char *command, int index, const char *itemDb, int itemId, int extra0, int extra1) {
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_DEVICE_0050d9d0);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], command);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], itemDb);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], index);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], itemId);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], extra0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], extra1);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_CTRLITEM_0050d9d8);
    beMessenger_GetBool(g_beMessenger_0058a1c0[0], 0);
}

/* 0x003722c0 */
/* be:SYSctlDiskFolder(command, index, itemId, count): the DISK selector of
 * the CTRLITEM controller; scripts call it as ("CLR", 0, itemId, 1) and
 * ("SET", 0, itemId, 1). */
void SYSctlDiskFolder(const char *command, int index, int itemId, int count) {
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_DISK_0050d9e8);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], command);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_EMPTY_0050d9c8);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], index);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], itemId);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], 0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], count);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_CTRLITEM_0050d9d8);
    beMessenger_GetBool(g_beMessenger_0058a1c0[0], 0);
}

/* 0x003723c0 */
/* be:SYSctlFlagFolder(command, index): the FLAG selector of the CTRLITEM
 * controller; scripts call it as ("CLR", n) and ("SET", 0..10). */
void SYSctlFlagFolder(const char *command, int index) {
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_FLAG_0050d9f0);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], command);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_EMPTY_0050d9c8);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], 0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], index);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], 0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], 0);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_CTRLITEM_0050d9d8);
    beMessenger_GetBool(g_beMessenger_0058a1c0[0], 0);
}

/* 0x003724a0 */
/* be:SYSctlBit(command, index, value): the BIT selector of the CTRLITEM
 * controller; scripts call it as ("ADD", 0..3, 5000).  The reply is an int. */
void SYSctlBit(const char *command, int index, int value) {
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_BIT_0050d9f8);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], command);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_EMPTY_0050d9c8);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], index);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], value);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], 0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], 0);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_CTRLITEM_0050d9d8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00372590 */
/* be:SYSgetPlayerLevel(player): LEVEL of the player's slot. */
int SYSgetPlayerLevel(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), s_LEVEL_0050da00))->value;
}

/* 0x003725c0 */
/* be:SYSgetPlayerDigimon(player): DIGIMONNO of the player's slot. */
int SYSgetPlayerDigimon(int playerIndex) {
    return ((PropertyRecord *)igProperty_GetRecord(bePlayer_GetStruct(playerIndex + 1), s_DIGIMONNO_0050da08))->value;
}

/* 0x00372970 */
/* be:SYSctlPlayer(property, command, playerIndex, value): the CTRLPLAYER
 * controller; scripts call it as ("HP", "GETHP", n, 0) and ("EXP", "SET", n,
 * v).  The reply is an int. */
void SYSctlPlayer(const char *property, const char *command, int playerIndex, int value) {
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], property);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], command);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], playerIndex);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], value);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_CTRLPLAYER_0050da98);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00372ce0 */
/* be:CFLgetFolderName(): the stage name held by the game singleton. */
int CFLgetFolderName(void) {
    return ((beSystem *)g_beSystem_0058a1b8[0])->_stageName;
}

/* 0x00373b20 */
/* be:MDLgetRamNo(): RamNo of the current MDL model entity. */
int MDLgetRamNo(void)
{
    return g_mdlRamNo_0058a1e4[0];
}

/* 0x00373b30 */
/* be:MDLgetInfoName(): InfoName of the current MDL model entity. */
int MDLgetInfoName(void)
{
    return g_mdlInfoName_0058a1f8[0];
}

/* 0x00373d00 */
/* be:MDLgetMHp(): max HP of the current MDL model entity. */
int MDLgetMHp(void)
{
    return g_mdlMaxHp_0058a1ec[0];
}

/* 0x00373d10 */
/* be:MDLgetHp(): current HP of the current MDL model entity. */
int MDLgetHp(void)
{
    return g_mdlHp_0058a1f0[0];
}

/* 0x00373d20 */
/* be:MDLaddHp(amount): add to the cached HP, clamping at zero. */
void MDLaddHp(int amount) {
    g_mdlHp_0058a1f0[0] = (int) (g_mdlHp_0058a1f0[0] + amount);
    if (g_mdlHp_0058a1f0[0] < 0) {
        g_mdlHp_0058a1f0[0] = 0;
    }
}

/* 0x00373e80 */
/* be:MDLgetBulletKind(): BulletKind of the current MDL entity. */
int MDLgetBulletKind(void)
{
    return g_mdlBulletKind_0058a1fc[0];
}

/* 0x00373ee0 */
/* be:MDLgetBulletBoxNo(): BulletBoxNo of the current MDL entity. */
int MDLgetBulletBoxNo(void)
{
    return g_mdlBulletBoxNo_0058a200[0];
}

/* 0x00374160 */
/* be:MDLsetDMGTurn(value): the DMGTurn byte flag (0x0058a210, docs/engine/game-state.md)
 * is set only for the value 1.  Kept as an absolute store: a named extern
 * byte changes the address materialisation. */
void MDLsetDMGTurn(int value) {
    *(char *)0x58A210 = value == 1;
}

/* 0x003742d0 */
/* be:MDLgetRecNo(): RecNo of the current MDL model entity. */
int MDLgetRecNo(void)
{
    return g_mdlRecNo_0058a1f4[0];
}

/* 0x003744a0 */
/* be:PLAYERgetPos(): ask the PLAYERPOINT group for GETGENERATEPOS and read
 * the reply. */
void PLAYERgetPos(void) {
    beMessenger_SendGroup(g_beMessenger_0058a1c0[0], s_PLAYERPOINT_0050dd58, s_GETGENERATEPOS_0050dd68);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00374730 */
/* be:MsgBox(): a stub in the retail build. */
void MsgBox(void)
{
}

/* 0x003747f0 */
/* be:TXTgetCallNo(): the text call number cached at 0x0058a220. */
int TXTgetCallNo(void)
{
    return g_txtCallNo_0058a220[0];
}

/* 0x00374880 */
/* be:BLTgetShootRamNo(): the RamNo of the shooter, cached at 0x0058a208. */
int BLTgetShootRamNo(void)
{
    return g_bltShootRamNo_0058a208[0];
}

/* 0x003749a0 */
/* be:BLTisCritical(): ask FIGHTCALC (P2EISCRITICAL) whether the shot is a
 * critical, from the cached shooter, record and bullet kind.  The bool reply
 * is read but not returned (combat-damage.md). */
void BLTisCritical(void) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_P2EISCRITICAL_0050ddf8);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_bltShootRamNo_0058a208[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRecNo_0058a1f4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetBool(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00374d00 */
/* be:BLTgetStunTime(intArg, byteArg): FIGHTCALC P2ESTUNTIME.  The byte
 * argument is masked to 8 bits before it is sent. */
void BLTgetStunTime(int intArg, int byteArg) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_P2ESTUNTIME_0050de40);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_bltShootRamNo_0058a208[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRecNo_0058a1f4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlMaxHp_0058a1ec[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], intArg);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], byteArg & 0xFF);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375360 */
/* be:BLTcalcSkillUp(firstByte, secondByte): FIGHTCALC P2ESKILLUP; both
 * arguments are masked to 8 bits.  Scripts call it as (0, 0), (1, 0), (1, n). */
void BLTcalcSkillUp(int firstByte, int secondByte) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_P2ESKILLUP_0050dea0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_bltShootRamNo_0058a208[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], firstByte & 0xFF);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], secondByte & 0xFF);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
}

/* 0x00375410 */
/* be:BLTcalcEXPUp(): FIGHTCALC P2EEXPUP for the cached shooter and record. */
void BLTcalcEXPUp(void) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_P2EEXPUP_0050deb0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_bltShootRamNo_0058a208[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRecNo_0058a1f4[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x003754a0 */
/* be:BLPisHitCheck(): FIGHTCALC E2PISHITCHECK for the cached target, BLP
 * status field and bullet kind; the bool reply is read but not returned. */
void BLPisHitCheck(void) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_E2PISHITCHECK_0050dec0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRamNo_0058a1e4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_blpStatus_0058a20c[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetBool(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375690 */
/* be:BLPgetAttackZokusei(): FIGHTCALC GETPATKZOKUSEI; the attribute (zokusei)
 * it returns is cached at 0x0058a338 and then turned into its display string
 * by BLTgetAttributeStr. */
void BLPgetAttackZokusei(void) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_GETPATKZOKUSEI_0050dee0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_bltShootRamNo_0058a208[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    g_attackZokusei_0058a338[0] = beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
    BLTgetAttributeStr();
}

/* 0x00375980 */
/* be:BLPgetPoisonTime(stringArg): FIGHTCALC E2PPOISONTIME; the argument is
 * appended as a string. */
void BLPgetPoisonTime(const char *stringArg) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_E2PPOISONTIME_0050df10);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], stringArg);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRamNo_0058a1e4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375a30 */
/* be:BLPgetSleepTime(): FIGHTCALC E2PSLEEPTIME. */
void BLPgetSleepTime(void) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_E2PSLEEPTIME_0050df20);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRamNo_0058a1e4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_blpStatus_0058a20c[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375ad0 */
/* be:BLPgetBindTime(): FIGHTCALC E2PBINDTIME. */
void BLPgetBindTime(void) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_E2PBINDTIME_0050df30);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRamNo_0058a1e4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_blpStatus_0058a20c[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375b70 */
/* be:BLPgetAttackDownTime(stringArg): FIGHTCALC E2PATKDWNTIME; the argument
 * is appended as a string. */
void BLPgetAttackDownTime(const char *stringArg) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_E2PATKDWNTIME_0050df40);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], stringArg);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRamNo_0058a1e4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_blpStatus_0058a20c[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375c30 */
/* be:BLPgetPowerDownTime(stringArg): FIGHTCALC E2PPOWDWNTIME; the argument
 * is appended as a string. */
void BLPgetPowerDownTime(const char *stringArg) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_E2PPOWDWNTIME_0050df50);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], stringArg);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRamNo_0058a1e4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_blpStatus_0058a20c[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375cf0 */
/* be:BLPcalcKoukaMagic(): FIGHTCALC P2PKOUKAMAGIC ("effect magic"). */
void BLPcalcKoukaMagic(void) {
    extern char s_FIGHTCALC_0050dde8[];
    beMessenger_SelectGroup(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940);
    beMessenger_AppendString(g_beMessenger_0058a1c0[0], s_P2PKOUKAMAGIC_0050df60);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlRamNo_0058a1e4[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_bltShootRamNo_0058a208[0]);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], g_mdlBulletKind_0058a1fc[0]);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_FIGHTCALC_0050dde8);
    beMessenger_GetInt(g_beMessenger_0058a1c0[0], 0);
}

/* 0x00375d90 */
/* be:LISsetDifficultMax(maxDifficulty): tell the LOADINTF2 receivers the
 * highest selectable difficulty; scripts pass 0, 1 or 2. */
void LISsetDifficultMax(int maxDifficulty) {
    beMessenger_SelectReceivers(g_beMessenger_0058a1c0[0], s_LOADINTF2_0050df70, 0, 0);
    beMessenger_AppendInt(g_beMessenger_0058a1c0[0], maxDifficulty);
    beMessenger_DispatchSelected(g_beMessenger_0058a1c0[0], s_SETDIFFICULTMAX_0050df80);
}

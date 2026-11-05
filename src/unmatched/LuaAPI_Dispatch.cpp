/* LuaAPI_Dispatch - 0x00370780. Lua native-API dispatcher: fn->id (short at +40) selects one of 116 API functions through a jump table; arguments are read from the Lua argument array (24-byte slots, first value at +16) and results are pushed on the Lua state. Alternate compiler, -O3,p -Iinclude. */
extern "C" {
struct LuaV { union { int i; unsigned char b; float f; long long l; } u; char pad[16]; };
struct LuaArgs { char pad[16]; struct LuaV v[8]; };
struct LuaFnP { int pad[3]; int f12; };
struct LuaFn { char pad0[12]; int f12; char name[12]; struct LuaFnP *p; char pad1[8]; short id; unsigned short flags; };
extern struct LuaFn *lua_touserdata(void *, int);
extern void lua_pushnumber(void *, long long);
extern long long __floatsidf(int);
extern long long FUN_00100290(int);
extern void FUN_0023d070(char *, void *, char *);
extern void FUN_002467a0(char *, ...);
extern char DAT_0050d600[];
extern unsigned char SYSisJoinPlayer(int);
extern char * SYSgetPlayerName(int);
extern int SYSgetPlayerNinzu(void);
extern char * SYSgetWeaponName(int, int);
extern int SYSgetRandom(int);
extern int SYSgetDifficulty(void);
extern void SYSsetDifficulty(int);
extern int SYSgetCameraMode(void);
extern int SYSgetLightMode(void);
extern int SYSgetArea(void);
extern int SYSgetCountry(void);
extern int SYSgetTarget(void);
extern int SYSgetIsPackOnly(void);
extern void SYSsetGateStage(int, int);
extern char * SYSgetGateStageName(void);
extern int SYSgetGateStageNo(void);
extern unsigned char SYSctlDeviceFolder(int, int, int, int, int, int);
extern unsigned char SYSctlDiskFolder(int, int, int, int);
extern unsigned char SYSctlFlagFolder(int, int);
extern int SYSgetPlayerLevel(int);
extern int SYSgetPlayerDigimon(int);
extern unsigned char SYSisGetShinkaDigimon(int, int);
extern int SYSctlCardFolder(int, int);
extern int SYSctlBit(int, int, int);
extern int SYSctlShinka(int, int, int);
extern int SYSctlPlayer(int, int, int, int);
extern void CFLclear(void);
extern void CFLsetName(int);
extern char * CFLgetFolderName(void);
extern void sd_29(int, int, int, int, int);
extern void sd_30(int, int, int, int);
extern void sd_31(int, int, int, int, int, long long);
extern void sd_32(int, int, int, int, long long);
extern unsigned char MATisPlayer(void);
extern unsigned char MATisAllPlayer(void);
extern int MATgetPlayerNo(void);
extern unsigned char MATisRidePlayer(int);
extern unsigned char MATisRideOffPlayer(int);
extern int MATgetPlayerMatStat(int);
extern void MATsetRun(unsigned char);
extern void DMsetSD_40(int, int, int, int, int, long long);
extern void DMsetSD_41(int, int, int, int, int);
extern void DMsetSD_42(int, int, int, int, long long);
extern void DMsetSD_43(int, int, int, int);
extern void DMchkSD_44(int, int, int, int, int, int);
extern void DMchkSD_45(int, int, int, int, int);
extern void DMswtSD_46(int, int, int, int, int);
extern void DMswtSD_47(int, int, int, int);
extern void DMswtEnd(void);
extern void DMcase(int);
extern void DMsetLua(int);
extern void DMmsgBox(int, int);
extern void DMrun(void);
extern int DMgetCount(void);
extern unsigned char FLGisOn(int);
extern void FLGset(int, unsigned char);
extern void FLGflip(int);
extern void COUNTERset(int, int);
extern int COUNTERget(int);
extern char * MDLgetInfoName(void);
extern int MDLgetRamNo(void);
extern int MDLgetRecNo(void);
extern int MDLgetMHp(void);
extern int MDLgetHp(void);
extern char * MDLgetPosStr(float, float, float);
extern char * MDLgetRotStr(float, float, float);
extern void MDLaddHp(int);
extern void MDLsetSeq(int);
extern void MDLsetSD(int, int);
extern unsigned char MDLisLive(int, int);
extern int MDLgetBulletKind(void);
extern char * MDLgetBulletName(void);
extern int MDLgetBulletBoxNo(void);
extern void MDLdspDamage(int);
extern void MDLdspDamageP(int);
extern void MDLdspExp(int);
extern void MDLsetDMGTurn(int);
extern unsigned char MDLisCallName(int);
extern void MDLsetWorldPosTarget_78(float, float, float);
extern void MDLsetWorldPosTarget_79(int);
extern long long FUN_00230298(float);
extern float MDLgetKyoriSquare(float, float, float);
extern unsigned char MDLisSeqName(int);
extern unsigned char MDLisStatus(int, int, int);
extern unsigned char BLTisPlayerBullet(void);
extern int BLTgetShootRamNo(void);
extern unsigned char BLTisHitCheck(void);
extern int BLTgetDamageValue(unsigned char);
extern int BLTgetDamageRank(int, unsigned char);
extern unsigned char BLTisCritical(void);
extern int BLTgetStunTime(int, unsigned char);
extern int BLTgetPoisonTime(int);
extern int BLTgetSleepTime(void);
extern int BLTgetBindTime(void);
extern int BLTgetAttackDownTime(int);
extern int BLTgetPowerDownTime(int);
extern void BLTcalcSkillUp(unsigned char, unsigned char);
extern int BLTcalcEXPUp(void);
extern char * BLTgetAttributeStr(void);
extern unsigned char BLPisHitCheck(void);
extern int BLPgetDamageValue(void);
extern char * BLPgetAttackZokusei(void);
extern int BLPgetDamageRank(int, int);
extern int BLPgetStunTime(int, int);
extern int BLPgetPoisonTime(int);
extern int BLPgetSleepTime(void);
extern int BLPgetBindTime(void);
extern int BLPgetAttackDownTime(int);
extern int BLPgetPowerDownTime(int);
extern int BLPcalcKoukaMagic(void);
extern int TXTgetCallNo(void);
extern int PLAYERgetPos(void);
extern char * PLAYERgetDataStr(int, int, float);
extern char * PLAYERgetPosStr(int, float, float, float);
extern void LISsetDifficultMax(int);
extern void MsgBox(int, int);
extern void ShutDown(void);
int LuaAPI_Dispatch(void *L);
}

int LuaAPI_Dispatch(void *L) {
    struct LuaFn *fn = lua_touserdata(L, -1);
    struct LuaArgs *a;
    if (fn->flags & 0xfff) a = (struct LuaArgs *)lua_touserdata(L, -2); else a = 0;
    switch (fn->id) {
    case 0x0:
        lua_pushnumber(L, FUN_00100290(SYSisJoinPlayer(a->v[0].u.i))); return 1;
    case 0x1:
        FUN_0023d070(fn->name, L, SYSgetPlayerName(a->v[0].u.i)); return 1;
    case 0x2:
        lua_pushnumber(L, __floatsidf(SYSgetPlayerNinzu())); return 1;
    case 0x3:
        FUN_0023d070(fn->name, L, SYSgetWeaponName(a->v[0].u.i, a->v[1].u.i)); return 1;
    case 0x4:
        lua_pushnumber(L, __floatsidf(SYSgetRandom(a->v[0].u.i))); return 1;
    case 0x5:
        lua_pushnumber(L, __floatsidf(SYSgetDifficulty())); return 1;
    case 0x6:
        SYSsetDifficulty(a->v[0].u.i); return 0;
    case 0x7:
        lua_pushnumber(L, __floatsidf(SYSgetCameraMode())); return 1;
    case 0x8:
        lua_pushnumber(L, __floatsidf(SYSgetLightMode())); return 1;
    case 0x9:
        lua_pushnumber(L, __floatsidf(SYSgetArea())); return 1;
    case 0xa:
        lua_pushnumber(L, __floatsidf(SYSgetCountry())); return 1;
    case 0xb:
        lua_pushnumber(L, __floatsidf(SYSgetTarget())); return 1;
    case 0xc:
        lua_pushnumber(L, __floatsidf(SYSgetIsPackOnly())); return 1;
    case 0xd:
        SYSsetGateStage(a->v[0].u.i, a->v[1].u.i); return 0;
    case 0xe:
        FUN_0023d070(fn->name, L, SYSgetGateStageName()); return 1;
    case 0xf:
        lua_pushnumber(L, __floatsidf(SYSgetGateStageNo())); return 1;
    case 0x10:
        lua_pushnumber(L, FUN_00100290(SYSctlDeviceFolder(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i, a->v[5].u.i))); return 1;
    case 0x11:
        lua_pushnumber(L, FUN_00100290(SYSctlDiskFolder(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i))); return 1;
    case 0x12:
        lua_pushnumber(L, FUN_00100290(SYSctlFlagFolder(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x13:
        lua_pushnumber(L, __floatsidf(SYSgetPlayerLevel(a->v[0].u.i))); return 1;
    case 0x14:
        lua_pushnumber(L, __floatsidf(SYSgetPlayerDigimon(a->v[0].u.i))); return 1;
    case 0x15:
        lua_pushnumber(L, FUN_00100290(SYSisGetShinkaDigimon(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x16:
        lua_pushnumber(L, __floatsidf(SYSctlCardFolder(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x17:
        lua_pushnumber(L, __floatsidf(SYSctlBit(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i))); return 1;
    case 0x18:
        lua_pushnumber(L, __floatsidf(SYSctlShinka(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i))); return 1;
    case 0x19:
        lua_pushnumber(L, __floatsidf(SYSctlPlayer(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i))); return 1;
    case 0x1a:
        CFLclear(); return 0;
    case 0x1b:
        CFLsetName(a->v[0].u.i); return 0;
    case 0x1c:
        FUN_0023d070(fn->name, L, CFLgetFolderName()); return 1;
    case 0x1d:
        sd_29(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i); return 0;
    case 0x1e:
        sd_30(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i); return 0;
    case 0x1f:
        sd_31(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i, a->v[5].u.l); return 0;
    case 0x20:
        sd_32(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.l); return 0;
    case 0x21:
        lua_pushnumber(L, FUN_00100290(MATisPlayer())); return 1;
    case 0x22:
        lua_pushnumber(L, FUN_00100290(MATisAllPlayer())); return 1;
    case 0x23:
        lua_pushnumber(L, __floatsidf(MATgetPlayerNo())); return 1;
    case 0x24:
        lua_pushnumber(L, __floatsidf(MATisRidePlayer(a->v[0].u.i))); return 1;
    case 0x25:
        lua_pushnumber(L, __floatsidf(MATisRideOffPlayer(a->v[0].u.i))); return 1;
    case 0x26:
        lua_pushnumber(L, __floatsidf(MATgetPlayerMatStat(a->v[0].u.i))); return 1;
    case 0x27:
        MATsetRun(a->v[0].u.b); return 0;
    case 0x28:
        DMsetSD_40(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i, a->v[5].u.l); return 0;
    case 0x29:
        DMsetSD_41(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.i); return 0;
    case 0x2a:
        DMsetSD_42(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i, a->v[4].u.l); return 0;
    case 0x2b:
        DMsetSD_43(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i, a->v[3].u.i); return 0;
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
        DMcase(a->v[0].u.i); return 0;
    case 0x32:
        DMsetLua(a->v[0].u.i); return 0;
    case 0x33:
        DMmsgBox(a->v[0].u.i, a->v[1].u.i); return 0;
    case 0x34:
        DMrun(); return 0;
    case 0x35:
        lua_pushnumber(L, __floatsidf(DMgetCount())); return 1;
    case 0x36:
        lua_pushnumber(L, FUN_00100290(FLGisOn(a->v[0].u.i))); return 1;
    case 0x37:
        FLGset(a->v[0].u.i, a->v[1].u.b); return 0;
    case 0x38:
        FLGflip(a->v[0].u.i); return 0;
    case 0x39:
        COUNTERset(a->v[0].u.i, a->v[1].u.i); return 0;
    case 0x3a:
        lua_pushnumber(L, __floatsidf(COUNTERget(a->v[0].u.i))); return 1;
    case 0x3b:
        FUN_0023d070(fn->name, L, MDLgetInfoName()); return 1;
    case 0x3c:
        lua_pushnumber(L, __floatsidf(MDLgetRamNo())); return 1;
    case 0x3d:
        lua_pushnumber(L, __floatsidf(MDLgetRecNo())); return 1;
    case 0x3e:
        lua_pushnumber(L, __floatsidf(MDLgetMHp())); return 1;
    case 0x3f:
        lua_pushnumber(L, __floatsidf(MDLgetHp())); return 1;
    case 0x40:
        FUN_0023d070(fn->name, L, MDLgetPosStr(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f)); return 1;
    case 0x41:
        FUN_0023d070(fn->name, L, MDLgetRotStr(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f)); return 1;
    case 0x42:
        MDLaddHp(a->v[0].u.i); return 0;
    case 0x43:
        MDLsetSeq(a->v[0].u.i); return 0;
    case 0x44:
        MDLsetSD(a->v[0].u.i, a->v[1].u.i); return 0;
    case 0x45:
        lua_pushnumber(L, FUN_00100290(MDLisLive(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x46:
        lua_pushnumber(L, __floatsidf(MDLgetBulletKind())); return 1;
    case 0x47:
        FUN_0023d070(fn->name, L, MDLgetBulletName()); return 1;
    case 0x48:
        lua_pushnumber(L, __floatsidf(MDLgetBulletBoxNo())); return 1;
    case 0x49:
        MDLdspDamage(a->v[0].u.i); return 0;
    case 0x4a:
        MDLdspDamageP(a->v[0].u.i); return 0;
    case 0x4b:
        MDLdspExp(a->v[0].u.i); return 0;
    case 0x4c:
        MDLsetDMGTurn(a->v[0].u.i); return 0;
    case 0x4d:
        lua_pushnumber(L, FUN_00100290(MDLisCallName(a->v[0].u.i))); return 1;
    case 0x4e:
        MDLsetWorldPosTarget_78(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f); return 0;
    case 0x4f:
        MDLsetWorldPosTarget_79(a->v[0].u.i); return 0;
    case 0x50:
        lua_pushnumber(L, FUN_00230298(MDLgetKyoriSquare(a->v[0].u.f, a->v[1].u.f, a->v[2].u.f))); return 1;
    case 0x51:
        lua_pushnumber(L, FUN_00100290(MDLisSeqName(a->v[0].u.i))); return 1;
    case 0x52:
        lua_pushnumber(L, FUN_00100290(MDLisStatus(a->v[0].u.i, a->v[1].u.i, a->v[2].u.i))); return 1;
    case 0x53:
        lua_pushnumber(L, FUN_00100290(BLTisPlayerBullet())); return 1;
    case 0x54:
        lua_pushnumber(L, __floatsidf(BLTgetShootRamNo())); return 1;
    case 0x55:
        lua_pushnumber(L, FUN_00100290(BLTisHitCheck())); return 1;
    case 0x56:
        lua_pushnumber(L, __floatsidf(BLTgetDamageValue(a->v[0].u.b))); return 1;
    case 0x57:
        lua_pushnumber(L, __floatsidf(BLTgetDamageRank(a->v[0].u.i, a->v[1].u.b))); return 1;
    case 0x58:
        lua_pushnumber(L, FUN_00100290(BLTisCritical())); return 1;
    case 0x59:
        lua_pushnumber(L, __floatsidf(BLTgetStunTime(a->v[0].u.i, a->v[1].u.b))); return 1;
    case 0x5a:
        lua_pushnumber(L, __floatsidf(BLTgetPoisonTime(a->v[0].u.i))); return 1;
    case 0x5b:
        lua_pushnumber(L, __floatsidf(BLTgetSleepTime())); return 1;
    case 0x5c:
        lua_pushnumber(L, __floatsidf(BLTgetBindTime())); return 1;
    case 0x5d:
        lua_pushnumber(L, __floatsidf(BLTgetAttackDownTime(a->v[0].u.i))); return 1;
    case 0x5e:
        lua_pushnumber(L, __floatsidf(BLTgetPowerDownTime(a->v[0].u.i))); return 1;
    case 0x5f:
        BLTcalcSkillUp(a->v[0].u.b, a->v[1].u.b); return 0;
    case 0x60:
        lua_pushnumber(L, __floatsidf(BLTcalcEXPUp())); return 1;
    case 0x61:
        FUN_0023d070(fn->name, L, BLTgetAttributeStr()); return 1;
    case 0x62:
        lua_pushnumber(L, FUN_00100290(BLPisHitCheck())); return 1;
    case 0x63:
        lua_pushnumber(L, __floatsidf(BLPgetDamageValue())); return 1;
    case 0x64:
        FUN_0023d070(fn->name, L, BLPgetAttackZokusei()); return 1;
    case 0x65:
        lua_pushnumber(L, __floatsidf(BLPgetDamageRank(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x66:
        lua_pushnumber(L, __floatsidf(BLPgetStunTime(a->v[0].u.i, a->v[1].u.i))); return 1;
    case 0x67:
        lua_pushnumber(L, __floatsidf(BLPgetPoisonTime(a->v[0].u.i))); return 1;
    case 0x68:
        lua_pushnumber(L, __floatsidf(BLPgetSleepTime())); return 1;
    case 0x69:
        lua_pushnumber(L, __floatsidf(BLPgetBindTime())); return 1;
    case 0x6a:
        lua_pushnumber(L, __floatsidf(BLPgetAttackDownTime(a->v[0].u.i))); return 1;
    case 0x6b:
        lua_pushnumber(L, __floatsidf(BLPgetPowerDownTime(a->v[0].u.i))); return 1;
    case 0x6c:
        lua_pushnumber(L, __floatsidf(BLPcalcKoukaMagic())); return 1;
    case 0x6d:
        lua_pushnumber(L, __floatsidf(TXTgetCallNo())); return 1;
    case 0x6e:
        lua_pushnumber(L, __floatsidf(PLAYERgetPos())); return 1;
    case 0x6f:
        FUN_0023d070(fn->name, L, PLAYERgetDataStr(a->v[0].u.i, a->v[1].u.i, a->v[2].u.f)); return 1;
    case 0x70:
        FUN_0023d070(fn->name, L, PLAYERgetPosStr(a->v[0].u.i, a->v[1].u.f, a->v[2].u.f, a->v[3].u.f)); return 1;
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

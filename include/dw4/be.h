#ifndef DW4_BE_H
#define DW4_BE_H

struct be;
struct beBaseInfoRam;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void FloatingNumber_Spawn(int value, int style);
void Lua_sd_OptionalArg(const char *args);
void SYSsetGateStage(const char *stageName, int stageNo);
struct be *be_CreateInstance(int allocator);
void be_EnsureRegistered(void);

extern struct igMetaObject *g_be_metaObject;

/* The model the running MDL / BLT / BLP script is about, cached by beModelCtrl before it calls
 * the script, and the hitter of the bullet that struck it. */
extern struct beBaseInfoRam *g_mdlEntity;
extern int g_mdlRamNo;
extern float *g_mdlMatrix;
extern int g_mdlMaxHp;
extern int g_mdlHp;
extern int g_mdlRecNo;
extern const char *g_mdlInfoName;
extern int g_mdlBulletKind;
extern int g_mdlBulletBoxNo;
extern const char *g_hitterInfoName;
extern int g_bltShootRamNo;
extern int g_hitterRecNo;
extern unsigned char g_mdlDmgTurn[4];
extern const char *g_mdlCallName;
extern float *g_mdlWorldPosTarget;
extern int g_txtCallNo;

#ifdef __cplusplus
}
#endif

#endif

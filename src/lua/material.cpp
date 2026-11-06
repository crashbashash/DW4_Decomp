/* Complete contiguous Lua MAT binding group, 0x373160..0x373274.
 * All seven wrappers verify byte-identically with MWCC's C++ front end.
 * C mode turns these calls into tail jumps and loses the retail frames.
 * Receiver: the beMatCtrl instance stored in global 0x58a1c8 (g_matCtrl),
 * built by constructor 0x371a30 with class handle 0x589160 (g_beMatCtrl_metaObject).
 * Callee semantics: docs/engine/material-contact.md, findings #859.
 */
#include "dw4/reflected.h"
extern beMatCtrl *g_matCtrl[4];
extern "C" bool beMatCtrl_IsPlayer(beMatCtrl *);
extern "C" bool beMatCtrl_IsAllPlayer(beMatCtrl *);
extern "C" int beMatCtrl_GetPlayerNo(beMatCtrl *);
extern "C" bool beMatCtrl_IsRidePlayer(beMatCtrl *, int);
extern "C" bool beMatCtrl_IsRideOffPlayer(beMatCtrl *, int);
extern "C" int beMatCtrl_GetPlayerMatStat(beMatCtrl *, int);
extern "C" void beMatCtrl_SetRun(beMatCtrl *, int);

/* 0x00373160 */
extern "C" bool MATisPlayer(void) { return beMatCtrl_IsPlayer(g_matCtrl[0]); }
/* 0x00373180 */
extern "C" bool MATisAllPlayer(void) { return beMatCtrl_IsAllPlayer(g_matCtrl[0]); }
/* 0x003731a0 */
extern "C" int MATgetPlayerNo(void) { return beMatCtrl_GetPlayerNo(g_matCtrl[0]); }
/* 0x003731c0 */
extern "C" bool MATisRidePlayer(int player) { return beMatCtrl_IsRidePlayer(g_matCtrl[0], player); }
/* 0x003731f0 */
extern "C" bool MATisRideOffPlayer(int player) { return beMatCtrl_IsRideOffPlayer(g_matCtrl[0], player); }
/* 0x00373220 */
extern "C" int MATgetPlayerMatStat(int player) { return beMatCtrl_GetPlayerMatStat(g_matCtrl[0], player); }
/* 0x00373250 */
extern "C" void MATsetRun(int value) { beMatCtrl_SetRun(g_matCtrl[0], value); }

/* Contiguous Lua MAT binding group. C mode turns these calls into tail jumps, so they stay C++.
 * Receiver: the beMatCtrl instance stored in global g_matCtrl, built with class handle
 * g_beMatCtrl_metaObject. */
#include "dw4/reflected.h"
extern beMatCtrl *g_matCtrl[4];
extern "C" bool beMatCtrl_IsPlayer(beMatCtrl *);
extern "C" bool beMatCtrl_IsAllPlayer(beMatCtrl *);
extern "C" int beMatCtrl_GetPlayerNo(beMatCtrl *);
extern "C" bool beMatCtrl_IsRidePlayer(beMatCtrl *, int);
extern "C" bool beMatCtrl_IsRideOffPlayer(beMatCtrl *, int);
extern "C" int beMatCtrl_GetPlayerMatStat(beMatCtrl *, int);
extern "C" void beMatCtrl_SetRun(beMatCtrl *, int);

extern "C" bool MATisPlayer(void) { return beMatCtrl_IsPlayer(g_matCtrl[0]); }
extern "C" bool MATisAllPlayer(void) { return beMatCtrl_IsAllPlayer(g_matCtrl[0]); }
extern "C" int MATgetPlayerNo(void) { return beMatCtrl_GetPlayerNo(g_matCtrl[0]); }
extern "C" bool MATisRidePlayer(int player) { return beMatCtrl_IsRidePlayer(g_matCtrl[0], player); }
extern "C" bool MATisRideOffPlayer(int player) { return beMatCtrl_IsRideOffPlayer(g_matCtrl[0], player); }
extern "C" int MATgetPlayerMatStat(int player) { return beMatCtrl_GetPlayerMatStat(g_matCtrl[0], player); }
extern "C" void MATsetRun(int value) { beMatCtrl_SetRun(g_matCtrl[0], value); }

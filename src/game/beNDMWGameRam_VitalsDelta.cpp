/* Player HP / MP gauge updates; 0x003f9c80 (408 bytes) and 0x003f9e20 (344 bytes).
 * Both clamp the player's property between 0 and its maximum, then publish the
 * new value to the HUD through METERCTRL (percent) and NUMBERCTRL (value).
 * HP accepts an absolute value (anything but -1) or a delta; a delta on a dead
 * player (HP 0) is ignored and reports failure.  MP is delta only.
 */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {

typedef struct PropertyRecord {
    char pad[12];
    int value;
} PropertyRecord;
PropertyRecord *igProperty_GetRecord(int, const char *);
void beMessenger_SelectReceivers(int, const char *, const char *, int);
void beMessenger_AppendFloat(int, float);
void beMessenger_AppendInt(int, int);
void beMessenger_DispatchSelected(int, const char *);
extern const char s_HP_00518890[]; /* HP */
extern const char s_MHP_00518898[]; /* MHP */
extern const char s_MP_005188a0[]; /* MP */
extern const char s_MMP_005188a8[]; /* MMP */
extern const char s_METERCTRL_00518c28[]; /* METERCTRL */
extern const char s_hpmt_00518c38[]; /* hpmt */
extern const char s_SETPERCENT_00518c40[]; /* SETPERCENT */
extern const char s_NUMBERCTRL_00518c50[]; /* NUMBERCTRL */
extern const char s_hpnm_00518c60[]; /* hpnm */
extern const char s_SETVALUE_00518c68[]; /* SETVALUE */
extern const char s_mpmt_00518c78[]; /* mpmt */
extern const char s_mpnm_00518c80[]; /* mpnm */

/* Sentinel for the `absolute` argument of the HP update: apply `delta` instead. */
#define NO_ABSOLUTE_HP (-1)

/* 0x003f9c80: HP update.  Returns 0 when a delta is applied to a dead player (HP 0), else 1. */
int FUN_003f9c80(beNDMWGameRam *self, int player_index, int delta, int absolute)
{
    int hp;
    int player;
    int max_hp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_hp = igProperty_GetRecord(player, s_MHP_00518898)->value;
    hp = igProperty_GetRecord(player, s_HP_00518890)->value;
    if (absolute == NO_ABSOLUTE_HP) {
        if (hp == 0)
            return 0;
        hp += delta;
    } else {
        hp = absolute;
    }
    if (hp < 0)
        hp = 0;
    if (hp > max_hp)
        hp = max_hp;
    igProperty_GetRecord(player, s_HP_00518890)->value = hp;
    beMessenger_SelectReceivers(self->_messenger, s_METERCTRL_00518c28, s_hpmt_00518c38, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)hp / (float)max_hp);
    beMessenger_DispatchSelected(self->_messenger, s_SETPERCENT_00518c40);
    beMessenger_SelectReceivers(self->_messenger, s_NUMBERCTRL_00518c50, s_hpnm_00518c60, player_index);
    beMessenger_AppendInt(self->_messenger, hp);
    beMessenger_DispatchSelected(self->_messenger, s_SETVALUE_00518c68);
    return 1;
}

/* 0x003f9e20: MP update by delta. */
void FUN_003f9e20(beNDMWGameRam *self, int player_index, int delta)
{
    int mp;
    int player;
    int max_mp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_mp = igProperty_GetRecord(player, s_MMP_005188a8)->value;
    mp = igProperty_GetRecord(player, s_MP_005188a0)->value;
    mp += delta;
    if (mp < 0)
        mp = 0;
    if (mp > max_mp)
        mp = max_mp;
    igProperty_GetRecord(player, s_MP_005188a0)->value = mp;
    beMessenger_SelectReceivers(self->_messenger, s_METERCTRL_00518c28, s_mpmt_00518c78, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)mp / (float)max_mp);
    beMessenger_DispatchSelected(self->_messenger, s_SETPERCENT_00518c40);
    beMessenger_SelectReceivers(self->_messenger, s_NUMBERCTRL_00518c50, s_mpnm_00518c80, player_index);
    beMessenger_AppendInt(self->_messenger, mp);
    beMessenger_DispatchSelected(self->_messenger, s_SETVALUE_00518c68);
}
} /* extern "C" */

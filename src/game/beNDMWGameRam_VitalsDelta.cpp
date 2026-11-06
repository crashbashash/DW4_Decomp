/* Player HP / MP gauge updates. Both clamp the player's property between 0 and its maximum, then
 * publish the new value to the HUD through METERCTRL (percent) and NUMBERCTRL (value). HP accepts
 * an absolute value (anything but -1) or a delta; a delta on a dead player (HP 0) is ignored and
 * reports failure. MP is delta only. */
#include "dw4/reflected.h"
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
extern const char HP[]; /* HP */
extern const char MHP[]; /* MHP */
extern const char MP[]; /* MP */
extern const char MMP[]; /* MMP */
extern const char METERCTRL[]; /* METERCTRL */
extern const char hpmt[]; /* hpmt */
extern const char SETPERCENT[]; /* SETPERCENT */
extern const char NUMBERCTRL[]; /* NUMBERCTRL */
extern const char hpnm[]; /* hpnm */
extern const char SETVALUE[]; /* SETVALUE */
extern const char mpmt[]; /* mpmt */
extern const char mpnm[]; /* mpnm */

/* Sentinel for the `absolute` argument of the HP update: apply `delta` instead. */
#define NO_ABSOLUTE_HP (-1)

/* HP update. Returns 0 when a delta is applied to a dead player (HP 0), else 1. */
int FUN_003f9c80(beNDMWGameRam *self, int player_index, int delta, int absolute)
{
    int hp;
    int player;
    int max_hp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_hp = igProperty_GetRecord(player, MHP)->value;
    hp = igProperty_GetRecord(player, HP)->value;
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
    igProperty_GetRecord(player, HP)->value = hp;
    beMessenger_SelectReceivers(self->_messenger, METERCTRL, hpmt, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)hp / (float)max_hp);
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL, hpnm, player_index);
    beMessenger_AppendInt(self->_messenger, hp);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE);
    return 1;
}

/* MP update by delta. */
void FUN_003f9e20(beNDMWGameRam *self, int player_index, int delta)
{
    int mp;
    int player;
    int max_mp;

    player = ((int *)((igIntList *)self->_playerDataListList)->_data)[player_index];
    max_mp = igProperty_GetRecord(player, MMP)->value;
    mp = igProperty_GetRecord(player, MP)->value;
    mp += delta;
    if (mp < 0)
        mp = 0;
    if (mp > max_mp)
        mp = max_mp;
    igProperty_GetRecord(player, MP)->value = mp;
    beMessenger_SelectReceivers(self->_messenger, METERCTRL, mpmt, player_index);
    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)mp / (float)max_mp);
    beMessenger_DispatchSelected(self->_messenger, SETPERCENT);
    beMessenger_SelectReceivers(self->_messenger, NUMBERCTRL, mpnm, player_index);
    beMessenger_AppendInt(self->_messenger, mp);
    beMessenger_DispatchSelected(self->_messenger, SETVALUE);
}
}

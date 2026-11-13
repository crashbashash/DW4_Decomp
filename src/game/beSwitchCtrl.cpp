#include "dw4/reflected.h"

/* beSwitchCtrl shows or hides a whole igSwitch, its info's _switchNode: the MsgAction message ALLON
 * enables every child of the switch and ALLOF disables every child. */

enum MsgAction { MSG_ALLON, MSG_ALLOF };

extern "C" int beSwitchCtrl_GetMessageEnum(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int messenger, beBaseInfoRam *ram, char *group);
extern "C" int beMessenger_ResolveEnumValue(int messenger, int messageEnum, int message);
extern "C" int igSwitch_EnableAllChildren(igSwitch *node);
extern "C" int igSwitch_DisableAllChildren(igSwitch *node);
extern "C" char SWITCHCTRL[];
extern "C" int g_beSwitchCtrlInfo_metaObject[4];
extern "C" int g_beSwitchCtrl_metaObject[4];

extern "C" void beSwitchCtrl__Prepare(void);
extern "C" int beSwitchCtrl__GetInfoMeta(void);
extern "C" void beSwitchCtrl__RegisterReceiver(beSwitchCtrl *self, beBaseInfoRam *ram);
extern "C" void beSwitchCtrl__Update(void);
extern "C" int beSwitchCtrl__OnMessage(beSwitchCtrl *self, beBaseInfoRam *ram, int message);
extern "C" int beSwitchCtrl__GetMeta(void);

void beSwitchCtrl__Prepare(void)
{
}

int beSwitchCtrl__GetInfoMeta(void)
{
    return g_beSwitchCtrlInfo_metaObject[0];
}

void beSwitchCtrl__RegisterReceiver(beSwitchCtrl *self, beBaseInfoRam *ram)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, SWITCHCTRL);
}

void beSwitchCtrl__Update(void)
{
}

int beSwitchCtrl__OnMessage(beSwitchCtrl *self, beBaseInfoRam *ram, int message)
{
    beSwitchCtrlInfo *info = (beSwitchCtrlInfo *)ram->_parentInfo;

    switch (beMessenger_ResolveEnumValue(self->_messenger, beSwitchCtrl_GetMessageEnum(), message)) {
    case MSG_ALLON:
        igSwitch_EnableAllChildren((igSwitch *)info->_switchNode);
        return 1;
    case MSG_ALLOF:
        igSwitch_DisableAllChildren((igSwitch *)info->_switchNode);
        return 1;
    default:
        return 0;
    }
}

int beSwitchCtrl__GetMeta(void)
{
    return g_beSwitchCtrl_metaObject[0];
}

#include "dw4/reflected.h"
#include "dw4/beMessenger.h"
#include "dw4/beSwitchCtrl.h"
#include "dw4/beSwitchCtrlInfo.h"
#include "dw4/igSwitch.h"

/* beSwitchCtrl shows or hides a whole igSwitch, its info's _switchNode: the MsgAction message ALLON
 * enables every child of the switch and ALLOF disables every child. */

enum MsgAction { MSG_ALLON, MSG_ALLOF };

extern "C" char SWITCHCTRL[];

extern "C" void beSwitchCtrl_Prepare(void);
extern "C" igMetaObject *beSwitchCtrl__GetInfoMeta(void);
extern "C" void beSwitchCtrl_OnAddRam(beSwitchCtrl *self, beBaseInfoRam *ram);
extern "C" void beSwitchCtrl_UpdateRam(void);
extern "C" int beSwitchCtrl_OnMessageText(beSwitchCtrl *self, beBaseInfoRam *ram, int message);
extern "C" igMetaObject *beSwitchCtrl__GetMeta(void);

void beSwitchCtrl_Prepare(void)
{
}

igMetaObject *beSwitchCtrl__GetInfoMeta(void)
{
    return g_beSwitchCtrlInfo_metaObject;
}

void beSwitchCtrl_OnAddRam(beSwitchCtrl *self, beBaseInfoRam *ram)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, ram, SWITCHCTRL);
}

void beSwitchCtrl_UpdateRam(void)
{
}

int beSwitchCtrl_OnMessageText(beSwitchCtrl *self, beBaseInfoRam *ram, int message)
{
    beSwitchCtrlInfo *info = (beSwitchCtrlInfo *)ram->_parentInfo;

    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beSwitchCtrl_GetMessageEnum(), (const char *)message)) {
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

igMetaObject *beSwitchCtrl__GetMeta(void)
{
    return g_beSwitchCtrl_metaObject;
}

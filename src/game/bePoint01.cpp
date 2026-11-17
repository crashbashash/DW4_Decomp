#include "dw4/reflected.h"
#include "dw4/beMessenger.h"
#include "dw4/bePoint01.h"
#include "dw4/bePoint01Info.h"
#include "dw4/igBitMask.h"
#include "dw4/igMathConstants.h"
#include "dw4/emptyString.h"
#include "dw4/igMatrix44f.h"

extern "C" void bePoint01_Prepare(void);
extern "C" igMetaObject *bePoint01_GetInfoMeta(void);
extern "C" void bePoint01_UpdateRam(void);
extern "C" igMetaObject *bePoint01_GetMeta(void);
extern "C" char PLAYERPOINT_4[];
extern "C" void bePoint01_OnAddRam(bePoint01 * p0, int p1, char * p2);
extern "C" void bePoint01_GetMatrix(bePoint01 *self, bePoint01Info *info, int pointIndex, int childIndex);
extern "C" int bePoint01_OnMessage(bePoint01 *self, beBaseInfoRam *ram, beMessengerWork *work);

void bePoint01_Prepare(void)
{
}

igMetaObject *bePoint01_GetInfoMeta(void)
{
    return g_bePoint01Info_metaObject;
}

void bePoint01_OnAddRam(bePoint01 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)p0->_messenger, (beBaseInfoRam *)p1, PLAYERPOINT_4);
}

void bePoint01_UpdateRam(void)
{
}

void bePoint01_GetMatrix(bePoint01 *self, bePoint01Info *info, int pointIndex, int childIndex) {
    float identity[16];
    beGroupKeepList *keeps;
    beGroupKeep *keep;
    keeps = (beGroupKeepList *)info->_dataList_;
    if (keeps->_count - 1 < pointIndex) {
        pointIndex = 0;
    }
    keep = ((beGroupKeep **)keeps->_data)[pointIndex];
    if (keep != 0) {
        beMessenger_AppendMatrix((beMessenger *)self->_messenger, ((igTransform **)((igObjectList *)keep->_childList)->_data)[childIndex]->_m);
        return;
    }
    igMatrix44f_Copy(identity, (float *)&g_matrix44Identity);
    beMessenger_AppendMatrix((beMessenger *)self->_messenger, identity);
}

int bePoint01_OnMessage(bePoint01 *self, beBaseInfoRam *ram, beMessengerWork *work) {
    unsigned int command;
    bePoint01Info *info;
    info = (bePoint01Info *)ram->_parentInfo;
    command = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, bePoint01_GetMsgActionEnum(), (const char *)work->_message);
    switch (command) {
    case 0:
        igBitMask_SetAll((igBitMask *)(((igSwitch *)info->_switch)->_childMask));
        return 1;
    case 1:
        igBitMask_ClearAll((igBitMask *)(((igSwitch *)info->_switch)->_childMask));
        return 1;
    case 2: {
        int pointNo = self->_pointNo;
        bePoint01_GetMatrix(self, info, pointNo, beMessenger_GetInt((beMessenger *)self->_messenger, 1));
        return 1;
    }
    case 3: {
        int pointNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        bePoint01_GetMatrix(self, info, pointNo, beMessenger_GetInt((beMessenger *)self->_messenger, 1));
        return 1;
    }
    case 4: {
        igObjectList *points = (igObjectList *)info->_dataList_;
        int count = points->_count;
        int i = 0;
        if (0 < count) {
            int offset = 0;
            do {
                int *name = (int *)(((beBaseInfoData *)(*(int *)((char *)points->_data + offset)))->_name);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)(name ? name : (int *)emptyString));
                i += 1;
                offset += 4;
            } while (i < count);
        }
        return 1;
    }
    case 5:
        self->_pointNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        return 1;
    case 6:
        beMessenger_AppendInt((beMessenger *)self->_messenger, self->_pointNo);
        return 1;
    default:
        return 0;
    }
}

igMetaObject *bePoint01_GetMeta(void)
{
    return g_bePoint01_metaObject;
}

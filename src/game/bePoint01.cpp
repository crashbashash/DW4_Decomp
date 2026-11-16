#include "dw4/reflected.h"

extern "C" void bePoint01_Prepare(void);
extern "C" int bePoint01_GetInfoMeta(void);
extern "C" void bePoint01_UpdateRam(void);
extern "C" int bePoint01_GetMeta(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int igMatrix44f_Copy(float *, float *);
extern "C" int beMessenger_AppendMatrix(int, void *);
extern "C" int igBitMask_SetAll(int);
extern "C" int igBitMask_ClearAll(int);
extern "C" int bePoint01_GetMsgActionEnum(...);
extern "C" int beMessenger_AppendInt(int, int);
extern "C" int beMessenger_AppendString(int, int *);
extern "C" int beMessenger_GetInt(int, int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int g_bePoint01Info_metaObject[4];
extern "C" int g_bePoint01_metaObject[4];
extern "C" char PLAYERPOINT_4[];
extern "C" void bePoint01_OnAddRam(bePoint01 * p0, int p1, char * p2);
extern "C" int g_matrix44Identity[4];
extern "C" void bePoint01_GetMatrix(bePoint01 *self, bePoint01Info *info, int pointIndex, int childIndex);
extern "C" int emptyString[4];
extern "C" int bePoint01_OnMessage(bePoint01 *self, beBaseInfoRam *ram, beMessengerWork *work);

void bePoint01_Prepare(void)
{
}

int bePoint01_GetInfoMeta(void)
{
    return g_bePoint01Info_metaObject[0];
}

void bePoint01_OnAddRam(bePoint01 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, PLAYERPOINT_4);
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
        beMessenger_AppendMatrix(self->_messenger, ((igTransform **)((igObjectList *)keep->_childList)->_data)[childIndex]->_m);
        return;
    }
    igMatrix44f_Copy(identity, (float *)&g_matrix44Identity[0]);
    beMessenger_AppendMatrix(self->_messenger, identity);
}

int bePoint01_OnMessage(bePoint01 *self, beBaseInfoRam *ram, beMessengerWork *work) {
    unsigned int command;
    bePoint01Info *info;
    info = (bePoint01Info *)ram->_parentInfo;
    command = beMessenger_ResolveEnumValue(self->_messenger, bePoint01_GetMsgActionEnum(), work->_message);
    switch (command) {
    case 0:
        igBitMask_SetAll(((igSwitch *)info->_switch)->_childMask);
        return 1;
    case 1:
        igBitMask_ClearAll(((igSwitch *)info->_switch)->_childMask);
        return 1;
    case 2: {
        int pointNo = self->_pointNo;
        bePoint01_GetMatrix(self, info, pointNo, beMessenger_GetInt(self->_messenger, 1));
        return 1;
    }
    case 3: {
        int pointNo = beMessenger_GetInt(self->_messenger, 0);
        bePoint01_GetMatrix(self, info, pointNo, beMessenger_GetInt(self->_messenger, 1));
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
                beMessenger_AppendString(self->_messenger, name ? name : &emptyString[0]);
                i += 1;
                offset += 4;
            } while (i < count);
        }
        return 1;
    }
    case 5:
        self->_pointNo = beMessenger_GetInt(self->_messenger, 0);
        return 1;
    case 6:
        beMessenger_AppendInt(self->_messenger, self->_pointNo);
        return 1;
    default:
        return 0;
    }
}

int bePoint01_GetMeta(void)
{
    return g_bePoint01_metaObject[0];
}

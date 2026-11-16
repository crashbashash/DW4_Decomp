#include "dw4/reflected.h"
#include "dw4/igObjectDispatchView.h"
#include "dw4/igTDataList.h"

extern "C" void beActionStarter_Prepare(void);
extern "C" int beActionStarter_GetInfoMeta(void);
extern "C" void beActionStarter_UpdateRam(void);
extern "C" int beActionStarter_GetMeta(void);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_AppendFloat(int, float);
extern "C" void beMessenger_AppendString(int, int *);
extern "C" void beMessenger_AppendVec3(int, float *);
extern "C" void beMessenger_DispatchSelected(int, int *);
extern "C" void beMessenger_SelectReceivers(int, int *, int, int);
extern "C" void beMessenger_SetRunCheck(int, unsigned char);
extern "C" int beBaseInfoManager_OnMessageText(void);
extern "C" int g_beActionStarterInfo_metaObject[4];
extern "C" int g_beActionStarter_metaObject[4];
extern "C" char ACTION_BROADCAST_2[];
extern "C" void beActionStarter_OnAddRam(beActionStarter * p0, int p1, char * p2, int p3, int p4);
extern "C" int emptyString[4];
extern "C" int MODELCTRL_10[4];
extern "C" int SETEFFECT_3[4];
extern "C" igMetaObject *g_beActionStarterData2_metaObject;
/* One entry of an info's model list: the model's name and the data list of its commands. */
struct ActionStarterModel {
    int _vtable;
    unsigned int _refCount;
    int _name;
    int _dataList;
};
extern "C" int beActionStarter_OnMessage(beActionStarter *self, beActionStarterInfoRam *ram, beMessengerWork *work);

void beActionStarter_Prepare(void)
{
}

void beActionStarter_OnAddRam(beActionStarter * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, ACTION_BROADCAST_2, 0, -1);
}

int beActionStarter_GetInfoMeta(void)
{
    return g_beActionStarterInfo_metaObject[0];
}

void beActionStarter_UpdateRam(void)
{
}

int beActionStarter_OnMessage(beActionStarter *self, beActionStarterInfoRam *ram, beMessengerWork *work) {
    float offset[3];
    float rotation[3];
    beActionStarterInfo *info = (beActionStarterInfo *)ram->_parentInfo;
    bool found = false;
    int commandName = work->_message;
    int infoName = work->_infoName;
    int ramNo = work->_ramNo;
    int modelIndex;
    igTDataList<ActionStarterModel *> *models = (igTDataList<ActionStarterModel *> *)info->_modelList;
    for (modelIndex = 0; modelIndex < models->count(); modelIndex++) {
        int *name = (int *)models->get(modelIndex)->_name;
        name = name != 0 ? name : &emptyString[0];
        if (infoName == (int)name) {
            found = true;
            break;
        }
    }
    if (!found) {
        return 1;
    }
    {
        igDataList *commands = (igDataList *)models->get(modelIndex)->_dataList;
        int commandIndex = 0;
        if (0 < commands->_count) {
            int offsetInList = 0;
            do {
                beActionStarterData2 *command = ((beActionStarterData2 **)commands->_data)[offsetInList];
                int *name = (int *)command->_name;
                name = name != 0 ? name : &emptyString[0];
                if ((int)name == commandName) {
                    int *infoNameString;
                    beMessenger_SelectReceivers(self->_messenger, &MODELCTRL_10[0], infoName, ramNo);
                    infoNameString = (int *)info->_name;
                    infoNameString = infoNameString != 0 ? infoNameString : &emptyString[0];
                    beMessenger_AppendString(self->_messenger, infoNameString);
                    beMessenger_AppendString(self->_messenger, (int *)command->_message);
                    beMessenger_AppendFloat(self->_messenger, (float)command->_delay);
                    offset[0] = ((float *)command->_offset)[0];
                    offset[1] = ((float *)command->_offset)[1];
                    offset[2] = ((float *)command->_offset)[2];
                    beMessenger_AppendVec3(self->_messenger, offset);
                    beMessenger_AppendBool(self->_messenger, command->_isSeqDead);
                    beMessenger_AppendBool(self->_messenger, command->_isPositionLock);
                    {
                        igMetaObject *rotatedMeta = g_beActionStarterData2_metaObject;
                        if (rotatedMeta == ((igObjectDispatchView *)command)->GetMeta()) {
                            rotation[0] = ((float *)&command->_rotation)[0];
                            rotation[1] = ((float *)&command->_rotation)[1];
                            rotation[2] = ((float *)&command->_rotation)[2];
                            beMessenger_AppendVec3(self->_messenger, rotation);
                        }
                    }
                    beMessenger_SetRunCheck(self->_messenger, 1);
                    beMessenger_DispatchSelected(self->_messenger, &SETEFFECT_3[0]);
                }
                commandIndex += 1;
                offsetInList += 1;
            } while (commandIndex < commands->_count);
        }
    }
    return 1;
}

int beActionStarter_GetMeta(void)
{
    return g_beActionStarter_metaObject[0];
}

/* Slot 33 default: always 0. */
int beBaseInfoManager_OnMessageText(void) {
    return 0;
}


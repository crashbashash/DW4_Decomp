#include "dw4/reflected.h"
#include "dw4/beBaseInfoManagerVirtuals.h"

extern "C" int beBaseInfoManager_Stop(...);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" int beStaticInfoCtl_GetInfoMeta(void);
extern "C" void beStaticInfoCtl_UpdateRam(void);
extern "C" int beStaticInfoCtl_GetMeta(void);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_RegisterReceiver(...);
extern "C" int beStaticInfoCtl_GetMessageEnum(...);
extern "C" int beMessenger_AppendObject(int, int);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" void igObject_Destroy(igObject *);
/* matching construct: the inlined refcount release is a static member so the compiler expands it as retail does */
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void beStaticInfoCtl_Stop(beStaticInfoCtl *self);
extern "C" int g_beMessenger_metaObject[4];
extern "C" void beStaticInfoCtl_Prepare(beStaticInfoCtl *self);
extern "C" int g_beStaticInfoCtl_metaObject[4];
extern "C" int g_beStaticInfo_metaObject[4];
extern "C" int emptyString[4];
extern "C" int STATICINFO_2[4];
extern "C" void beStaticInfoCtl_OnAddRam(beStaticInfoCtl *self, beBaseInfoRam *ram);
extern "C" int beStaticInfoCtl_OnMessage(beStaticInfoCtl *self, beBaseInfoRam *ram, beMessengerWork *work);

void beStaticInfoCtl_Stop(beStaticInfoCtl *self) {
    igDataList *infos = (igDataList *)self->_staticInfoList;
    int count = infos->_count;
    int i = 0;
    if (0 < count) {
        do {
            ReleaseRefInline::go(((igObject **)infos->_data)[i]);
            i++;
        } while (i < count);
    }
    int clearCount = infos->_count;
    int v = 0;
    if (0 < clearCount) {
        int unrolledEnd;
        if (clearCount > 8) {
            unrolledEnd = clearCount - 8;
            do {
                ((int *)infos->_data)[v] = 0;
                ((int *)infos->_data)[v + 1] = 0;
                ((int *)infos->_data)[v + 2] = 0;
                ((int *)infos->_data)[v + 3] = 0;
                ((int *)infos->_data)[v + 4] = 0;
                ((int *)infos->_data)[v + 5] = 0;
                ((int *)infos->_data)[v + 6] = 0;
                ((int *)infos->_data)[v + 7] = 0;
                v += 8;
            } while (v < unrolledEnd);
        }
        if (v < clearCount) {
            do {
                ((int *)infos->_data)[v] = 0;
                v++;
            } while (v < clearCount);
        }
    }
    infos->_count = 0;
    beBaseInfoManager_Stop(self);
}

void beStaticInfoCtl_Prepare(beStaticInfoCtl *self) {
    if (self->_messenger == 0) {
        self->_messenger = igInsightCore_FindManager(self->_insight, g_beMessenger_metaObject[0]);
    }
}

int beStaticInfoCtl_GetInfoMeta(void)
{
    return g_beStaticInfo_metaObject[0];
}

void beStaticInfoCtl_UpdateRam(void)
{
}

void beStaticInfoCtl_OnAddRam(beStaticInfoCtl *self, beBaseInfoRam *ram) {
    int messenger;
    beBaseInfo *info;
    int *name;
    int ramNo;
    int unresolved;
    /* matching construct: hand search — the unresolved flag is computed as (messenger != 0) ^ 1 and tested twice, as retail does */
    messenger = self->_messenger;
    info = (beBaseInfo *)ram->_parentInfo;
    unresolved = ((messenger != 0) ^ 1);
    if (unresolved) {
        do {
            ((beBaseInfoManagerVirtuals *)self)->prepare();
            messenger = self->_messenger;
            unresolved = ((messenger != 0) ^ 1);
        } while (unresolved);
    }
    name = (int *)info->_name;
    ramNo = ram->_ramNo;
    name = name != 0 ? name : &emptyString[0];
    beMessenger_RegisterReceiver(messenger, ram, &STATICINFO_2[0], name, ramNo);
    ObjectList_AppendRetained(self->_staticInfoList, info);
}

int beStaticInfoCtl_OnMessage(beStaticInfoCtl *self, beBaseInfoRam *ram, beMessengerWork *work) {
    switch (beMessenger_ResolveEnumValue(self->_messenger, beStaticInfoCtl_GetMessageEnum(), work->_message)) {
    case 0:
        beMessenger_AppendObject(self->_messenger, self->_staticInfoList);
        goto one;
    default:
        return 0;
    }
one:
    return 1;
}

int beStaticInfoCtl_GetMeta(void)
{
    return g_beStaticInfoCtl_metaObject[0];
}

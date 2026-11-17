#include "dw4/reflected.h"
#include "dw4/beBaseInfoManagerDispatchView.h"
#include "dw4/beBaseInfoManager.h"
#include "dw4/beMessenger.h"
#include "dw4/beStaticInfo.h"
#include "dw4/beStaticInfoCtl.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igObject.h"
#include "dw4/emptyString.h"

extern "C" igMetaObject *beStaticInfoCtl_GetInfoMeta(void);
extern "C" void beStaticInfoCtl_UpdateRam(void);
extern "C" igMetaObject *beStaticInfoCtl_GetMeta(void);
/* matching construct: the inlined refcount release is a static member so the compiler expands it as retail does */
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void beStaticInfoCtl_Stop(beStaticInfoCtl *self);
extern "C" void beStaticInfoCtl_Prepare(beStaticInfoCtl *self);
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
    beBaseInfoManager_Stop((beBaseInfoManager *)self);
}

void beStaticInfoCtl_Prepare(beStaticInfoCtl *self) {
    if (self->_messenger == 0) {
        self->_messenger = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beMessenger_metaObject));
    }
}

igMetaObject *beStaticInfoCtl_GetInfoMeta(void)
{
    return g_beStaticInfo_metaObject;
}

void beStaticInfoCtl_UpdateRam(void)
{
}

void beStaticInfoCtl_OnAddRam(beStaticInfoCtl *self, beBaseInfoRam *ram) {
    int messenger;
    beBaseInfo *info;
    int *name;
    int ramNo;
    info = (beBaseInfo *)ram->_parentInfo;
    /* matching construct: the reference is tested through a bool conversion; retail materialises the flag
       (sltu, xori) before each branch, where a test of the int or of a pointer branches on the field itself */
    while (!(bool)self->_messenger) {
        ((beBaseInfoManagerDispatchView *)self)->Prepare();
    }
    messenger = self->_messenger;
    name = (int *)info->_name;
    ramNo = ram->_ramNo;
    name = name != 0 ? name : (int *)emptyString;
    beMessenger_RegisterReceiver((beMessenger *)messenger, ram, (const char *)&STATICINFO_2[0], (const char *)name, ramNo);
    ObjectList_AppendRetained((igObjectList *)self->_staticInfoList, (igObject *)info);
}

int beStaticInfoCtl_OnMessage(beStaticInfoCtl *self, beBaseInfoRam *ram, beMessengerWork *work) {
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beStaticInfoCtl_GetMessageEnum(), (const char *)work->_message)) {
    case 0:
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)self->_staticInfoList);
        goto one;
    default:
        return 0;
    }
one:
    return 1;
}

igMetaObject *beStaticInfoCtl_GetMeta(void)
{
    return g_beStaticInfoCtl_metaObject;
}

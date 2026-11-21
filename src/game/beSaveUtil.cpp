#include "dw4/support/reflected.h"
#include "dw4/core/igobject_release.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beSaveApiDispatchView.h"
#include "dw4/core/igTDataList.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beSaveUtil.h"
#include "dw4/game/beSaveUtilInfo.h"
#include "dw4/game/beSvConnectCheck.h"
#include "dw4/game/beSvEndApi.h"
#include "dw4/game/beSvFileFindApi.h"
#include "dw4/game/beSvFileMakeApi.h"
#include "dw4/game/beSvFormatApi.h"
#include "dw4/game/beSvGetFreeSizeApi.h"
#include "dw4/game/beSvReadMediaApi.h"
#include "dw4/game/beSvStartApi.h"
#include "dw4/game/beSvUseCheckApi.h"
#include "dw4/game/beSvWriteMediaApi.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"

extern "C" igMetaObject *beSaveUtil_GetInfoMeta(void);
extern "C" igMetaObject *beSaveUtil_GetMeta(void);
extern "C" unsigned char beSaveUtil_StartApi(beSaveUtil *self, beSaveUtilInfoRam *info, beSaveApi *request);
extern "C" void beSaveUtil_PollConnectCheck(beSaveUtil *self, beSaveUtilInfoRam *info);
extern "C" void beSaveUtil_Prepare(beSaveUtil *self);
extern "C" char SAVEUTILITY_2[];
extern "C" void beSaveUtil_OnAddRam(beSaveUtil * p0, int p1, char * p2);
extern "C" int beSaveUtil_OnMessage(beSaveUtil *self, beSaveUtilInfoRam *info, beMessengerWork *message);

extern "C" void beSaveUtil_UpdateRam(beSaveUtil *self, beSaveUtilInfoRam *info);

#define ALLOC(a, self) { int base_ = (int)((Gap::Core::igObject *)(self))->getMemoryPool(); if (g_useOwnerAllocator != 0) { a = base_; } else { a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); } }

#define DELIVERY(info) ((beSvDeliver *)(info)->_deliver)
#define API(self) ((beSaveApiDispatchView *)(self)->_api)

unsigned char beSaveUtil_StartApi(beSaveUtil *self, beSaveUtilInfoRam *info, beSaveApi *request) {
    unsigned char started;
    igObject *old;

    started = 0;
    if (self->_api == 0) {
        igObject::ref(request);
        old = (igObject *)self->_api;
        IG_OBJECT_RELEASE(old);
        self->_api = (int)request;
        API(self)->start(DELIVERY(info));
        DELIVERY(info)->_operate = ((beSaveApi *)self->_api)->_orderType;
        DELIVERY(info)->_isEndOperat = 0;
        info->_st0 = 1;
        info->_st3 = 0;
        info->_st2 = 0;
        info->_st1 = 0;
        info->_st1 = 1;
        info->_st3 = 0;
        info->_st2 = 0;
        info->_st2 = 1;
        info->_st3 = 0;
        started = 1;
    }
    return started;
}

void beSaveUtil_PollConnectCheck(beSaveUtil *self, beSaveUtilInfoRam *info) {
    beSvConnectCheck_PollMultitap(self->_connectCheck, (beSvDeliver *)info->_deliver);
    beSvConnectCheck_Poll((beSvConnectCheckWork *)self->_connectCheck);
    beSvConnectCheck_FillDeliver((int *)self->_connectCheck, (beSvDeliver *)info->_deliver);
}

void beSaveUtil_Prepare(beSaveUtil *self) {
    igObject *api;
    igObject *connectCheck;

    api = (igObject *)self->_api;
    if (api != 0) {
        IG_OBJECT_RELEASE(api);
        self->_api = 0;
    }
    connectCheck = (igObject *)self->_connectCheck;
    if (connectCheck != 0) {
        IG_OBJECT_RELEASE(connectCheck);
        self->_connectCheck = 0;
    }
}

/* The deliver's per-slot int lists (connected slots, free size, free files, format state, total size). */
struct SlotList : igTDataList<int> {
    void clear() {
        if (_count > 0) {
            _count = 0;
        }
    }
    void append(const int &value) {
        int n = count();
        if (n < _capacity) {
            _count = _count + 1;
        } else {
            ((Gap::Core::igDataList *)this)->resizeAndSetCount(n + 1, sizeof(int));
        }
        _data[n] = value;
    }
};


/* Steps one save request through its life: _st1 0 starts the card session (the connect-check object
 * and the slot lists are made, then a start request is issued), 1 serves requests (polling the
 * cards, one request at a time) and 2 ends the session with an end request; _st2 is the sub-step
 * of a request, issued at 0 and polled at 1. _st0 3 is idle once the session has ended. */
void beSaveUtil_UpdateRam(beSaveUtil *self, beSaveUtilInfoRam *info) {
    int allocator;
    int i;
    SlotList *list;
    igObject *old;
    switch (info->_st0) {
    case 0:
        break;
    case 1:
        switch (info->_st1) {
        case 0:
            switch (info->_st2) {
            case 0:
                if (self->_connectCheck == 0) {
                    ALLOC(allocator, self)
                    old = (igObject *)self->_connectCheck;
                    IG_OBJECT_RELEASE(old);
                    self->_connectCheck = (int)beSvConnectCheck_Create(allocator);
                }
                /* matching construct: register trace — one `list` re-pointed at each deliver list: the appends'
                 * lists are its later lifetimes, numbered after the append's count, so they take s3 and the count s4 */
                list = (SlotList *)DELIVERY(info)->_actConnect;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_freeSizeList;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_freeFileList;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_formatList;
                list->clear();
                list = (SlotList *)DELIVERY(info)->_totalSizeList;
                list->clear();
                /* The test reads the deliver through the reference field's `operator->() const`, a temporary of its
                 * own that is not shared with the body's plain read of the field. */
                for (i = 0; i < ((beSvPlatBaseData *)((igSmartPointer<beSvDeliver> &)info->_deliver)->_platformData)->_connectMax; i++) {
                    list = (SlotList *)DELIVERY(info)->_actConnect;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_freeSizeList;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_freeFileList;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_formatList;
                    list->append(0);
                    list = (SlotList *)DELIVERY(info)->_totalSizeList;
                    list->append(0);
                }
                {
                    ALLOC(allocator, self)
                    igSmartPointer<beSvStartApi> request(beSvStartApi_Create(allocator));
                    ((beSaveApiDispatchView *)request.p)->start(DELIVERY(info));
                    *(igSmartPointer<igObject> *)&self->_api = (igObject *)request.p;
                    info->_st2 = info->_st2 + 1;
                    info->_st3 = 0;
                }
                break;
            case 1:
                if (API(self)->poll() != 0) {
                    *(igSmartPointer<igObject> *)&self->_api = 0;
                    info->_isRdy = 1;
                    info->_st1 = 1;
                    info->_st3 = 0;
                    info->_st2 = 0;
                }
                break;
            }
            break;
        case 1:
            beSaveUtil_PollConnectCheck(self, info);
            switch (info->_st2) {
            case 0:
                break;
            case 1:
                if (self->_api == 0) {
                    info->_st2 = 0;
                    info->_st3 = 0;
                } else if (API(self)->poll() != 0) {
                    API(self)->report(DELIVERY(info));
                    info->_st2 = 0;
                    info->_st3 = 0;
                    *(igSmartPointer<igObject> *)&self->_api = 0;
                }
                break;
            }
            break;
        case 2:
            switch (info->_st2) {
            case 0: {
                ALLOC(allocator, self)
                igSmartPointer<beSvEndApi> request(beSvEndApi_Create(allocator));
                ((beSaveApiDispatchView *)request.p)->start(DELIVERY(info));
                *(igSmartPointer<igObject> *)&self->_api = (igObject *)request.p;
                info->_st2 = info->_st2 + 1;
                info->_st3 = 0;
                break;
            }
            case 1:
                if (API(self)->poll() != 0) {
                    *(igSmartPointer<igObject> *)&self->_api = 0;
                    info->_st0 = 2;
                    info->_st3 = 0;
                    info->_st2 = 0;
                    info->_st1 = 0;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        list = (SlotList *)DELIVERY(info)->_actConnect;
        list->clear();
        list = (SlotList *)DELIVERY(info)->_freeSizeList;
        list->clear();
        list = (SlotList *)DELIVERY(info)->_freeFileList;
        list->clear();
        list = (SlotList *)DELIVERY(info)->_formatList;
        list->clear();
        info->_isRdy = 0;
        info->_st0 = 3;
        info->_st3 = 0;
        info->_st2 = 0;
        info->_st1 = 0;
        break;
    case 3:
        break;
    }
}


igMetaObject *beSaveUtil_GetInfoMeta(void)
{
    return g_beSaveUtilInfo_metaObject;
}

void beSaveUtil_OnAddRam(beSaveUtil *self, int info, char *unused)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, SAVEUTILITY_2);
}

#define NEW_REQUEST(r, T, create) ALLOC(a, self); igSmartPointer<T> r(create(a));
#define TAKE_SLOT_ARGUMENT(self, info) \
    DELIVERY(info)->_targetConnect = -1; \
    for (i = 0; i < beMessenger_GetIntCount((beMessenger *)(self)->_messenger); i++) { \
        int v = beMessenger_GetInt((beMessenger *)(self)->_messenger, i); \
        switch (i) { case 0: DELIVERY(info)->_targetConnect = v; break; } \
    }
int beSaveUtil_OnMessage(beSaveUtil *self, beSaveUtilInfoRam *info, beMessengerWork *message) {
    int a;
    int i;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beSaveUtil_GetMessageEnum(), (const char *)message->_message)) {
    case 3: {
        NEW_REQUEST(request, beSvFileFindApi, beSvFileFindApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        beSaveUtil_StartApi(self, info, (beSaveApi *)request.p);
        break;
    }
    case 5: {
        NEW_REQUEST(request, beSvUseCheckApi, beSvUseCheckApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        beSaveUtil_StartApi(self, info, (beSaveApi *)request.p);
        break;
    }
    case 8: {
        NEW_REQUEST(request, beSvGetFreeSizeApi, beSvGetFreeSizeApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        beSaveUtil_StartApi(self, info, (beSaveApi *)request.p);
        break;
    }
    case 2: {
        NEW_REQUEST(request, beSvFileMakeApi, beSvFileMakeApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) != 0) {
            DELIVERY(info)->_gameData = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        }
        beSaveUtil_StartApi(self, info, (beSaveApi *)request.p);
        break;
    }
    case 4: {
        NEW_REQUEST(request, beSvFormatApi, beSvFormatApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        beSaveUtil_StartApi(self, info, (beSaveApi *)request.p);
        break;
    }
    case 7: {
        NEW_REQUEST(request, beSvWriteMediaApi, beSvWriteMediaApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) != 0) {
            DELIVERY(info)->_gameData = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        }
        beSaveUtil_StartApi(self, info, (beSaveApi *)request.p);
        break;
    }
    case 6: {
        NEW_REQUEST(request, beSvReadMediaApi, beSvReadMediaApi_Create)
        TAKE_SLOT_ARGUMENT(self, info)
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) != 0) {
            DELIVERY(info)->_gameData = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        }
        beSaveUtil_StartApi(self, info, (beSaveApi *)request.p);
        break;
    }
    case 9:
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)info->_deliver);
        }
        break;
    case 0:
        info->_st0 = 1;
        info->_st3 = 0; info->_st2 = 0; info->_st1 = 0;
        info->_st1 = 0; info->_st3 = 0; info->_st2 = 0;
        {
            beSvDeliver *deliver = DELIVERY(info);
            if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
                deliver->_saveVer = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            }
        }
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        }
        break;
    case 1:
        info->_st0 = 1;
        info->_st3 = 0; info->_st2 = 0; info->_st1 = 0;
        info->_st1 = 2;
        info->_st3 = 0; info->_st2 = 0;
        break;
    case 11:
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0) {
            if (DELIVERY(info)->_isEndOperat == 1) {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
            } else {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
            }
        }
        break;
    case 12:
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendInt((beMessenger *)self->_messenger, DELIVERY(info)->_result);
        }
        break;
    case 13:
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0) {
            if (info->_isRdy == 1) {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
            } else {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
            }
        }
        break;
    case 14:
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendInt((beMessenger *)self->_messenger, DELIVERY(info)->_memCapa);
            beMessenger_AppendInt((beMessenger *)self->_messenger, DELIVERY(info)->_fileCapa);
            if (DELIVERY(info)->_isMemCapaOK == 1) {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
            } else {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
            }
            if (DELIVERY(info)->_isfileCapaOK == 1) {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
            } else {
                beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
            }
        }
        break;
    case 15:
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendInt((beMessenger *)self->_messenger, DELIVERY(info)->_result);
        }
        break;
    case 17:
        break;
    default:
        return 0;
    }
    return 1;
}

#undef TAKE_SLOT_ARGUMENT
#undef NEW_REQUEST
#undef API
#undef DELIVERY

igMetaObject *beSaveUtil_GetMeta(void)
{
    return g_beSaveUtil_metaObject;
}

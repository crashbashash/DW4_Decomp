#include "dw4/reflected.h"
#include "dw4/igMath.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igobject_release.h"
#include "dw4/igControllerDispatchView.h"

extern "C" void igInsightCore_AddToScheduler(int, char *);
extern "C" void igInsightCore_RemoveFromScheduler(int, char *);
extern "C" void *igInsightCore_FindManager(...);
extern "C" void *bePadData_Create(...);
extern "C" int igEventDispatcher_AddReceiver(...);
extern "C" int igEventDispatcher_AddReceiverOrder(...);
extern "C" int igHotKeyEventReceiver_RemoveBinding(...);
extern "C" int igViewerSceneInfoManager_CycleGuiVisibility(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int igEventDispatcher_RemoveReceiver(int, int);
extern "C" int igEventDispatcher_RemoveReceiverOrder(int, int, int);
extern "C" int bePadManager_AddInfo(void);
extern "C" void bePadManager_RemoveAllInfo(void);
extern "C" int bePadManager_GetMeta(void);
extern "C" int bePadData_UpdateButtons(...);
extern "C" void bePadManager_Activate(bePadManager *self, int unusedArg);
extern "C" void bePadManager_Deactivate(bePadManager *self, int unusedArg);
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void bePadManager_Start(bePadManager *self);
extern "C" void bePadManager_Stop(bePadManager *self);
extern "C" int g_bePadManager_metaObject[4];
extern "C" int bePadData_UpdateLeftStick(bePadData *, igVec2f *);
extern "C" int bePadData_UpdateRightStick(bePadData *, igVec2f *);
extern "C" void bePadManager_Update(bePadManager *self);
extern "C" int bePadManager_GetPadForPlayer(bePadManager *self, int player);

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void bePadManager_Activate(bePadManager *self, int unusedArg)
{
    igInsightCore_AddToScheduler(self->_insight, (char *)self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void bePadManager_Deactivate(bePadManager *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, (char *)self);
}

void bePadManager_Start(bePadManager *self) {
    igObject *system = (igObject *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]);
    if (system != 0) system->_refCount = system->_refCount + 1;
    {
        igObject *old = (igObject *)self->_system;
        IG_OBJECT_RELEASE(old);
    }
    self->_system = (int)system;
    for (int i = 0; i < 5; i++) {
        int ownerAllocator = igObject_GetAllocator(self);
        igSmartPointer<igObject> padData((igObject *)bePadData_Create(g_useOwnerAllocator != 0 ? ownerAllocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0])));
        ObjectList_AppendRetained(self->_padList, padData.p);
    }
    igInsightCore *insight = (igInsightCore *)self->_insight;
    int dispatcher = insight->_dispatcher;
    igEventDispatcher_AddReceiverOrder(dispatcher, self->_kbReceiver, insight->_windowResizeReceiver);
    igEventDispatcher_AddReceiver(dispatcher, self->_kbReceiver);
    igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
    int hotKeys = viewer->_hotKeyReceiver;
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 15);
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 3);
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 0);
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 10);
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 11);
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 1);
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 2);
    igHotKeyEventReceiver_RemoveBinding(hotKeys, 12);
    igViewerSceneInfoManager_CycleGuiVisibility(viewer);
}

void bePadManager_Stop(bePadManager *self) {
    igInsightCore *insight;
    int dispatcher;

    insight = (igInsightCore *)self->_insight;
    dispatcher = insight->_dispatcher;
    igEventDispatcher_RemoveReceiverOrder(dispatcher, self->_kbReceiver, insight->_windowResizeReceiver);
    igEventDispatcher_RemoveReceiver(dispatcher, self->_kbReceiver);
}

int bePadManager_AddInfo(void) {
    return 0;
}

void bePadManager_RemoveAllInfo(void)
{
}

void bePadManager_Update(bePadManager *self) {
    int connected;
    bool keyboardTaken;
    int i;
    unsigned short id;
    igControllerList *list;
    igControllerDispatchView *pad;
    bePadData *slot;
    igVec2f stick;
    igVec2f left;
    igVec2f right;
    igVec2f noLeft;
    igVec2f noRight;
    if (((beSystem *)self->_system)->_isFrameSkip == 0) {
        keyboardTaken = false;
        list = (igControllerList *)((igControllerManager *)((igEventDispatcher *)((igInsightCore *)self->_insight)->_dispatcher)->_controllerManager)->_controllers;
        for (i = 0; i < list->_count; i++) {
            pad = ((igControllerDispatchView **)list->_data)[i];
            id = pad->getId();
            connected = (unsigned char)pad->isConnected();
            if (id == 2) {
                if (connected == 0) continue;
                keyboardTaken = true;
            }
            if (id == 1) {
                if (keyboardTaken) continue;
                keyboardTaken = true;
                id = 2;
            }
            if ((unsigned short)((unsigned)id >> 1) < 4) {
                bePadDataList *pads = (bePadDataList *)self->_padList;
                slot = ((bePadData **)pads->_data)[(unsigned short)((unsigned)id >> 1)];
                slot->_isConnect = connected;
                if (connected != 0) {
                    pad->getStick(0, &stick.x, &stick.y);
                    left.x = stick.x; left.y = stick.y;
                    bePadData_UpdateLeftStick(slot, &left);
                    pad->getStick(1, &stick.x, &stick.y);
                    right.x = stick.x; right.y = stick.y;
                    bePadData_UpdateRightStick(slot, &right);
                    bePadData_UpdateButtons(slot, pad->getButtons());
                } else {
                    noLeft.x = 0; noLeft.y = 0;
                    bePadData_UpdateLeftStick(slot, &noLeft);
                    noRight.x = 0; noRight.y = 0;
                    bePadData_UpdateRightStick(slot, &noRight);
                    bePadData_UpdateButtons(slot, 0);
                }
            }
        }
    }
}

/* _padList is a bePadDataList whose backing array (_data) holds the pad record pointers */
int bePadManager_GetPadForPlayer(bePadManager *self, int player) {
    if (self->_isPadDisable != 0) {
        return *(int *)(((bePadDataList *)self->_padList)->_data + 16);
    }
    if (player < 4) {
        return *(int *)(((bePadDataList *)self->_padList)->_data + (player * 4));
    }
    return *(int *)(((bePadDataList *)self->_padList)->_data + 16);
}

int bePadManager_GetMeta(void)
{
    return g_bePadManager_metaObject[0];
}

#include "dw4/support/reflected.h"
#include "dw4/maths/igMath.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igobject_release.h"
#include "dw4/windowinput/igControllerDispatchView.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/bePadData.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/gui/igEventDispatcher.h"
#include "dw4/gui/igHotKeyEventReceiver.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"

extern "C" int bePadManager_AddInfo(void);
extern "C" void bePadManager_RemoveAllInfo(void);
extern "C" igMetaObject *bePadManager_GetMeta(void);
extern "C" void bePadManager_Activate(bePadManager *self, int unusedArg);
extern "C" void bePadManager_Deactivate(bePadManager *self, int unusedArg);
extern "C" void bePadManager_Start(bePadManager *self);
extern "C" void bePadManager_Stop(bePadManager *self);
extern "C" void bePadManager_Update(bePadManager *self);

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void bePadManager_Activate(bePadManager *self, int unusedArg)
{
    igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void bePadManager_Deactivate(bePadManager *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

void bePadManager_Start(bePadManager *self) {
    igObject *system = (igObject *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject);
    if (system != 0) system->_refCount = system->_refCount + 1;
    {
        igObject *old = (igObject *)self->_system;
        IG_OBJECT_RELEASE(old);
    }
    self->_system = (int)system;
    for (int i = 0; i < 5; i++) {
        int ownerAllocator = (int)igObject_GetAllocator(self);
        igSmartPointer<igObject> padData((igObject *)bePadData_Create((int)(g_useOwnerAllocator != 0 ? ownerAllocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0))));
        ObjectList_AppendRetained((igObjectList *)self->_padList, padData.p);
    }
    igInsightCore *insight = (igInsightCore *)self->_insight;
    int dispatcher = insight->_dispatcher;
    igEventDispatcher_AddReceiverOrder((igEventDispatcher *)dispatcher, (igObject *)self->_kbReceiver, (igObject *)insight->_windowResizeReceiver);
    igEventDispatcher_AddReceiver((igEventDispatcher *)dispatcher, (igObject *)self->_kbReceiver);
    igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
    int hotKeys = viewer->_hotKeyReceiver;
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 15);
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 3);
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 0);
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 10);
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 11);
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 1);
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 2);
    igHotKeyEventReceiver_RemoveBinding((igHotKeyEventReceiver *)hotKeys, 12);
    igViewerSceneInfoManager_CycleGuiVisibility(viewer);
}

void bePadManager_Stop(bePadManager *self) {
    igInsightCore *insight;
    int dispatcher;

    insight = (igInsightCore *)self->_insight;
    dispatcher = insight->_dispatcher;
    igEventDispatcher_RemoveReceiverOrder((igEventDispatcher *)dispatcher, (igObject *)self->_kbReceiver, (igObject *)insight->_windowResizeReceiver);
    igEventDispatcher_RemoveReceiver((igEventDispatcher *)dispatcher, (igObject *)self->_kbReceiver);
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
                    bePadData_UpdateLeftStick(slot, (float *)&left);
                    pad->getStick(1, &stick.x, &stick.y);
                    right.x = stick.x; right.y = stick.y;
                    bePadData_UpdateRightStick(slot, (float *)&right);
                    bePadData_UpdateButtons(slot, pad->getButtons());
                } else {
                    noLeft.x = 0; noLeft.y = 0;
                    bePadData_UpdateLeftStick(slot, (float *)&noLeft);
                    noRight.x = 0; noRight.y = 0;
                    bePadData_UpdateRightStick(slot, (float *)&noRight);
                    bePadData_UpdateButtons(slot, 0);
                }
            }
        }
    }
}

/* _padList is a bePadDataList whose backing array (_data) holds the pad record pointers */
bePadData *bePadManager_GetPadForPlayer(bePadManager *self, int player) {
    if (self->_isPadDisable != 0) {
        return *(bePadData **)(((bePadDataList *)self->_padList)->_data + 16);
    }
    if (player < 4) {
        return *(bePadData **)(((bePadDataList *)self->_padList)->_data + (player * 4));
    }
    return *(bePadData **)(((bePadDataList *)self->_padList)->_data + 16);
}

igMetaObject *bePadManager_GetMeta(void)
{
    return g_bePadManager_metaObject;
}

#include "dw4/reflected.h"
extern "C" {
void *FUN_00236f80(int, int);
beCameraMode *FUN_003689f0(void *);
void FUN_0037a690(beCameraMode *, int);
void FUN_00463fd0(int, beCameraMode *);
void *Memory_GetAllocatorBySelector(int);
void *igObject_GetAllocator(void *);
void igObject_Destroy(void *);
extern int DAT_00587110[4];
extern int DAT_0058c790[4];
extern unsigned char GPR_00554c14;
void FUN_00379a90(beCameraCtrl *self, beBaseInfoRam *act);
}

struct CameraModeRef {
    igObject *p;
    CameraModeRef(void *x) { p = (igObject *)x; }
    ~CameraModeRef() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q); } }
};

void FUN_00379a90(beCameraCtrl *self, beBaseInfoRam *act) {
    beCameraDemoData *demo = (beCameraDemoData *)((beCameraCtrlInfo *)act->_parentInfo)->_data;
    switch (act->_st0) {
    case 0: {
        if (self->_viewerMang == 0) {
            igViewerSceneInfoManager *vm = (igViewerSceneInfoManager *)FUN_00236f80(self->_insight, DAT_0058c790[0]);
            self->_viewerPara = vm->_parameters;
            self->_viewerMang = (int)vm;
        }
        beCameraMode *cm = (beCameraMode *)self->_cameraMode;
        if (cm == 0) {
            void *alloc = igObject_GetAllocator(self);
            alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            CameraModeRef created(FUN_003689f0(alloc));
            igObject *r = created.p;
            if (r != 0) r->_refCount = r->_refCount + 1;
            igObject *old = (igObject *)self->_cameraMode;
            if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
            self->_cameraMode = (int)r;
            cm = (beCameraMode *)created.p;
        }
        FUN_0037a690(cm, demo->_cameraPath);
        cm->_timeLength = demo->_endTime;
        cm->_insight = self->_insight;
        cm->_isEnd = 0;
        cm->_nowTimeL = 0;
        cm->_svWorldTimeL = 0;
        FUN_00463fd0(((igViewerSceneInfoManager *)self->_viewerMang)->_viewManager, cm);
        act->_st0 = act->_st0 + 1;
        act->_st3 = 0;
        act->_st2 = 0;
        act->_st1 = 0;
        break;
    }
    case 1:
        break;
    }
}

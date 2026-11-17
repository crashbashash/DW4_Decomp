#include "dw4/reflected.h"
#include "dw4/igObjectDispatchView.h"
#include "dw4/beTime.h"
#include "dw4/StringPool.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beBaseInfoRam.h"
#include "dw4/beCameraBoxData.h"
#include "dw4/beCameraCtrl.h"
#include "dw4/beCameraCtrlInfo.h"
#include "dw4/beCameraCtrlInfoRamShake.h"
#include "dw4/beCameraDemoData.h"
#include "dw4/beCameraMode.h"
#include "dw4/beMessenger.h"
#include "dw4/igBitMask.h"
#include "dw4/igCamera.h"
#include "dw4/igDataLists.h"
#include "dw4/igGraphPath.h"
#include "dw4/igInsightCore.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include "dw4/igViewManager.h"
#include "dw4/igViewerSceneInfoManager.h"
#include <string.h>
#include "dw4/igAABox.h"
#include "dw4/igVec3f.h"
#pragma push
#pragma readonly_strings on
#define SELECT_ALLOCATOR(var, owner) { var = (int)igObject_GetAllocator((igObject *)owner); var = g_useOwnerAllocator ? var : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }
#define RELEASE(q) { igObject *o_ = (q); if (o_ != 0) { o_->_refCount = o_->_refCount - 1; if (((unsigned long long)((long long)(int)o_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o_); } } }
#define OBJECT_LIST(handle) ((igObjectList *)(handle))
#define TRANSFORM_AT(list, i) ((igTransform *)((int *)OBJECT_LIST(list)->_data)[i])
#define NAME_OR_EMPTY(n) ((n) != 0 ? (n) : emptyString)
#define ENSURE_DATA_LIST(ram) if ((ram)->_dataList == 0) { int alloc; SELECT_ALLOCATOR(alloc, ram) DataList::Install(ram, DataListRef(beBaseInfoDataList_Create(alloc))); }

/* The messages a beCameraCtrl answers, in the order of its message enum (beCameraCtrl_GetMessageEnum). */
enum beCameraCtrlMessage {
    MSG_SHOWPOLYGON,
    MSG_HIDEPOLYGON,
    MSG_GETPOSITION,
    MSG_ENABLE,
    MSG_DISABLE,
    MSG_SETBOXCAMERA,
    MSG_SETDEMOCAMERA,
    MSG_GETDEMONAME,
    MSG_ISDEMOCAMERA,
    MSG_SHAKE,
    MSG_ONFREEZE,
    MSG_OFFREEZE,
    MSG_DBGZOOMCLEAR,
    MSG_DBGZOOMIN,
    MSG_DBGZOOMOUT,
};

extern "C" {
igMetaObject *beCameraCtrl_GetInfoMeta(void);
igMetaObject *beCameraCtrl_GetMeta(void);
void beCameraCtrl_OnAddRam(beCameraCtrl *self, int ram, char *unused);
void beCameraCtrl_UpdateRam(beCameraCtrl *self, beBaseInfoRam *ram);
void beCameraCtrl_Prepare(beCameraCtrl *self);
int beCameraCtrl_OnMessageText(beCameraCtrl *self, beBaseInfoRam *ram, int message);
int beCameraCtrl_IsBoxCamera(beCameraCtrl *self, beCameraCtrlInfo *info);
int beCameraCtrl_IsDemoCamera(beCameraCtrl *self, beCameraCtrlInfo *info);
void beCameraCtrl_EnableDebugZoom(beCameraCtrl *self, beBaseInfoRam *ram, int on);
void beCameraCtrl_UpdateBoxCamera(beCameraCtrl *self, beBaseInfoRam *ram);
void beCameraCtrl_UpdateDemoCamera(beCameraCtrl *self, beBaseInfoRam *ram);
void beCameraMode_SetCameraPath(beCameraMode *mode, igObject *path);

int ObjectList_RemoveFirstRetained(...);

extern char emptyString[];
/* per shake step: the eye and interest offsets along x and y, indexed by the move code digit */
float g_cameraShakeOffsetX[12] = {0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f};
float g_cameraShakeOffsetY[12] = {0.0f, 1.0f, 1.0f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
}

/* Read-only parameters are const. b52 binds an inlined function's const parameter to its argument before the
 * body, so the field is loaded ahead of the body's other operands; a plain parameter is folded into the body. */
/* moves one coordinate by a shake step: the step's table direction times the shake's value */
static inline void AddShakeOffset(float *coord, const float *direction, const float value) { *coord += *direction * value; }

/* Strong references to a newly created object, one class per emitted destructor copy. The exception range
 * starts where each one is constructed, so only the calls after construction are covered. */
struct DataListRef { igObject *p; DataListRef(void *created) { p = (igObject *)created; } ~DataListRef() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
struct CameraModeRef { igObject *p; CameraModeRef(void *created) { p = (igObject *)created; } ~CameraModeRef() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
struct ShakeRef { igObject *p; ShakeRef(void *created) { p = (igObject *)created; } ~ShakeRef() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };

/* the per-ram data list, created on first use */
struct DataList {
    static inline void Install(beBaseInfoRam *ram, const DataListRef &created) {
        igObject *r = created.p;
        if (r != 0) r->_refCount = r->_refCount + 1;
        { igObject *o = (igObject *)ram->_dataList; RELEASE(o) }
        ram->_dataList = (int)r;
    }
    /* matching construct: hand-written — this one is an inline member, while the first and third holders in the
     * SHAKE message are written out as blocks; that orders the three holder stack slots as retail has them. */
    static inline void Ensure(void *owner, beBaseInfoRam *ram) {
        if (ram->_dataList == 0) {
            int alloc;
            SELECT_ALLOCATOR(alloc, owner)
            DataListRef created(beBaseInfoDataList_Create(alloc));
            igObject *r = created.p;
            if (r != 0) r->_refCount = r->_refCount + 1;
            { igObject *o = (igObject *)ram->_dataList; RELEASE(o) }
            ram->_dataList = (int)r;
        }
    }
};

igMetaObject *beCameraCtrl_GetInfoMeta(void)
{
    return g_beCameraCtrlInfo_metaObject;
}

void beCameraCtrl_OnAddRam(beCameraCtrl *self, int ram, char *unused)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)ram, "CAMERA");
}

void beCameraCtrl_Prepare(beCameraCtrl *self) {
    igObject *mode;

    self->_cameraNow = 0;
    self->_cameraOld = 0;
    if (self->_viewerMang != 0) {
        igViewerSceneInfoManager_ResetOperationMode((igViewerSceneInfoManager *)self->_viewerMang);
    }
    mode = (igObject *)self->_cameraMode;
    if (mode != 0) {
        mode->_refCount -= 1;
        if ((mode->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(mode);
        }
    }
    self->_cameraMode = 0;
}

int beCameraCtrl_IsBoxCamera(beCameraCtrl *self, beCameraCtrlInfo *info) {
    igObjectDispatchView *data = (igObjectDispatchView *)info->_data;
    igMetaObject *boxMeta = g_beCameraBoxData_metaObject;
    return boxMeta == data->GetMeta();
}

int beCameraCtrl_IsDemoCamera(beCameraCtrl *self, beCameraCtrlInfo *info) {
    igObjectDispatchView *data = (igObjectDispatchView *)info->_data;
    igMetaObject *demoMeta = g_beCameraDemoData_metaObject;
    return demoMeta == data->GetMeta();
}

void beCameraCtrl_EnableDebugZoom(beCameraCtrl *self, beBaseInfoRam *ram, int on)
{
}

/* Follows the players with the box camera: the average player position picks the box (geometry 1..n) that
 * holds it, and the eye and interest transforms blend from the previous box's camera over 120 frames. */
void beCameraCtrl_UpdateBoxCamera(beCameraCtrl *self, beBaseInfoRam *ram) {
    float pos[4];
    float boxMax[4];
    float boxMin[4];
    float fromPos[4];
    float toPos[4];
    float shakePos[4];
    float fromRot[4];
    float toRot[4];
    int matrix[16];
    int count;
    int offset;
    beCameraBoxData *box;
    float x, y, z;
    int n;
    int i;
    bool moved;
    int alloc;
    int camera;

    box = (beCameraBoxData *)((beCameraCtrlInfo *)ram->_parentInfo)->_data;
    switch (ram->_st0) {
    case 0:
        self->_avgPos[0] = -1.0f;
        self->_avgPos[1] = -1.0f;
        self->_avgPos[2] = -1.0f;
        self->_cameraNow = 0;
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        break;
    default:
        break;
    }
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    beMessenger_SendGroup((beMessenger *)self->_messenger, "PLAYER", "GETMATRIX");
    if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
        n = beMessenger_GetMatrixCount((beMessenger *)self->_messenger);
        for (i = 0; i < n; i++) {
            beMessenger_GetMatrix(matrix, (beMessenger *)self->_messenger, i);
            igMatrix44f_GetTranslation((const float *)matrix, pos);
            x += pos[0];
            y += pos[1];
            z += pos[2];
        }
        switch (n) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            x /= 2.0f; y /= 2.0f; z /= 2.0f;
            break;
        case 3:
            x /= 3.0f; y /= 3.0f; z /= 3.0f;
            break;
        case 4:
            x /= 4.0f; y /= 4.0f; z /= 4.0f;
            break;
        default:
            break;
        }
        { float *avg = self->_avgPos; moved = (avg[0] != x) || (avg[1] != y) || (avg[2] != z); }
        if (moved) {
            self->_avgPos[0] = x;
            self->_avgPos[1] = y;
            self->_avgPos[2] = z;
            self->_isPosChange = 1;
        } else {
            self->_isPosChange = 0;
        }
        if (ram->_dataList != 0) {
            ENSURE_DATA_LIST(ram)
            {
                beCameraCtrlInfoRamShake *shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "SHK");
                if (shake != 0) {
                    if (shake->_isFirst != 0) {
                        shake->_isFirst = 0;
                    } else {
                        igMatrix44f_SetTranslation(TRANSFORM_AT(box->_eyePosList, 0)->_m, shake->_svEyePos);
                        igMatrix44f_SetTranslation(TRANSFORM_AT(box->_intPosList, 0)->_m, shake->_svIntPos);
                    }
                }
            }
        }
        if (self->_isPosChange != 0) {
            camera = 0;
            igMatrix44f_SetTranslation(TRANSFORM_AT(box->_transformList, 0)->_m, self->_avgPos);
            self->_savePos[0] = self->_avgPos[0];
            self->_savePos[1] = self->_avgPos[1];
            self->_savePos[2] = self->_avgPos[2];
            x = self->_avgPos[0];
            y = self->_avgPos[1];
            z = self->_avgPos[2];
            count = OBJECT_LIST(box->_geometryList)->_count;
            i = 1;
            if (1 < count) {
                offset = 4;
                do {
                    char *geometries = (char *)OBJECT_LIST(box->_geometryList)->_data;
                    int at = offset;
                    void *bound = (void *)((igNode *)((void **)(geometries + at))[0])->_bound;
                    igAABox_GetCorner((const igAABox *)bound, 0, boxMax);
                    if (!(boxMax[0] < x) && !(boxMax[1] < y) && !(boxMax[2] < z)) {
                        igAABox_GetCorner((const igAABox *)bound, 7, boxMin);
                        if (boxMin[0] <= x && boxMin[1] <= y && boxMin[2] <= z) {
                            camera = i;
                            break;
                        }
                    }
                    i += 1;
                    offset += 4;
                } while (i < count);
            }
            if (camera != 0) {
                if (camera != self->_cameraNow) {
                    beCameraMode *mode;
                    self->_cameraOld = self->_cameraNow;
                    self->_cameraNow = camera;
                    igMatrix44f_Copy(self->_eyeMatrix, TRANSFORM_AT(box->_eyePosList, 0)->_m);
                    igMatrix44f_Copy(self->_intMatrix, TRANSFORM_AT(box->_intPosList, 0)->_m);
                    self->_cameraNowFrame = 0.0f;
                    if (self->_viewerMang == 0) {
                        igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
                        self->_viewerPara = viewer->_parameters;
                        self->_viewerMang = (int)viewer;
                    }
                    mode = (beCameraMode *)self->_cameraMode;
                    if (mode == 0) {
                        SELECT_ALLOCATOR(alloc, self)
                        CameraModeRef created(beCameraMode_Create(alloc));
                        igObject *r = created.p;
                        if (r != 0) r->_refCount = r->_refCount + 1;
                        { igObject *o = (igObject *)self->_cameraMode; RELEASE(o) }
                        self->_cameraMode = (int)r;
                        mode = (beCameraMode *)created.p;
                    }
                    beCameraMode_SetCameraPath(mode, (igObject *)(((void **)OBJECT_LIST(((igViewerParameters *)self->_viewerPara)->_cameras)->_data)[0]));
                    mode->_timeLength = 0;
                    mode->_insight = self->_insight;
                    mode->_isEnd = 0;
                    mode->_nowTimeL = 0;
                    mode->_svWorldTimeL = 0;
                    igViewManager_SetViewMode((igViewManager *)((igViewerSceneInfoManager *)self->_viewerMang)->_viewManager, (igViewMode *)mode);
                }
            }
        }
        if (self->_cameraNow != self->_cameraOld) {
            if (self->_cameraOld == 0 || !(self->_cameraNowFrame < 120.0f)) {
                self->_cameraOld = self->_cameraNow;
                igMatrix44f_Copy(TRANSFORM_AT(box->_eyePosList, 0)->_m, TRANSFORM_AT(box->_eyePosList, self->_cameraNow)->_m);
                igMatrix44f_Copy(TRANSFORM_AT(box->_intPosList, 0)->_m, TRANSFORM_AT(box->_intPosList, self->_cameraNow)->_m);
                beBaseInfoRam_RemoveTimer(ram, "CAMHOKAN");
            } else {
                float t = self->_cameraNowFrame / 120.0f;
                float *from;
                float *to;
                float *out;
                int j = 0;
                do {
                    switch (j) {
                    case 0:
                        from = self->_eyeMatrix;
                        to = TRANSFORM_AT(box->_eyePosList, self->_cameraNow)->_m;
                        out = TRANSFORM_AT(box->_eyePosList, 0)->_m;
                        break;
                    case 1:
                        from = self->_intMatrix;
                        to = TRANSFORM_AT(box->_intPosList, self->_cameraNow)->_m;
                        out = TRANSFORM_AT(box->_intPosList, 0)->_m;
                        break;
                    }
                    igMatrix44f_GetTranslation(from, fromPos);
                    igMatrix44f_GetTranslation(to, toPos);
                    Vec3_Lerp(fromPos, t, fromPos, toPos);
                    igMatrix44f_SetTranslation(out, fromPos);
                    igMatrix44f_GetQuaternion(fromRot, from);
                    igMatrix44f_GetQuaternion(toRot, to);
                    Quaternion_Lerp(fromRot, t, fromRot, toRot);
                    igMatrix44f_SetQuaternion(out, fromRot);
                    j += 1;
                } while (j < 2);
                if (beBaseInfoRam_HasTimer(ram, "CAMHOKAN") == 0) {
                    beBaseInfoRam_StartTimer(ram, "CAMHOKAN", 0);
                }
                if (self->_isPosChange == 0) {
                    float frame = self->_cameraNowFrame;
                    self->_cameraNowFrame = frame + 1.5f * beBaseInfoRam_GetTimerFrameDelta(ram, "CAMHOKAN");
                } else {
                    float frame = self->_cameraNowFrame;
                    self->_cameraNowFrame = frame + beBaseInfoRam_GetTimerFrameDelta(ram, "CAMHOKAN");
                }
            }
        }
        if (ram->_dataList != 0) {
            ENSURE_DATA_LIST(ram)
            {
                beCameraCtrlInfoRamShake *shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "SHK");
                if (shake != 0) {
                    float *matrix44;
                    int k = 0;
                    float *offsetX = &g_cameraShakeOffsetX[((char *)shake->_moveCode)[(int)shake->_movePoint] - '0'];
                    float *offsetY = &g_cameraShakeOffsetY[((char *)shake->_moveCode)[(int)shake->_movePoint] - '0'];
                    do {
                        if (k == 0) {
                            matrix44 = TRANSFORM_AT(box->_eyePosList, 0)->_m;
                            igMatrix44f_GetTranslation(matrix44, shakePos);
                            shake->_svEyePos[0] = shakePos[0];
                            shake->_svEyePos[1] = shakePos[1];
                            shake->_svEyePos[2] = shakePos[2];
                        } else {
                            matrix44 = TRANSFORM_AT(box->_intPosList, 0)->_m;
                            igMatrix44f_GetTranslation(matrix44, shakePos);
                            shake->_svIntPos[0] = shakePos[0];
                            shake->_svIntPos[1] = shakePos[1];
                            shake->_svIntPos[2] = shakePos[2];
                        }
                        AddShakeOffset(&shakePos[0], offsetX, shake->_value);
                        AddShakeOffset(&shakePos[1], offsetY, shake->_value);
                        igMatrix44f_SetTranslation(matrix44, shakePos);
                        k += 1;
                    } while (k < 2);
                    if (beBaseInfoRam_IsTimerExpired(ram, "SHAKEONE")) {
                        int next = shake->_movePoint + 1;
                        if (((char *)(next + shake->_moveCode))[0] == 0) next = 0;
                        shake->_movePoint = next;
                        beBaseInfoRam_StartTimer(ram, "SHAKEONE", FramesToTime(shake->_oneTime));
                    }
                    if (beBaseInfoRam_IsTimerExpired(ram, "SHAKEALL")) {
                        int removed;
                        igMatrix44f_SetTranslation(TRANSFORM_AT(box->_eyePosList, 0)->_m, shake->_svEyePos);
                        igMatrix44f_SetTranslation(TRANSFORM_AT(box->_intPosList, 0)->_m, shake->_svIntPos);
                        ObjectList_RemoveFirstRetained(&removed, ram->_dataList, shake, 0);
                        beBaseInfoRam_RemoveTimer(ram, "SHAKEALL");
                        beBaseInfoRam_RemoveTimer(ram, "SHAKEONE");
                    }
                }
            }
        }
    }
}

/* Starts the demo camera's path on the viewer once; the path then plays for the demo's end time. */
void beCameraCtrl_UpdateDemoCamera(beCameraCtrl *self, beBaseInfoRam *ram) {
    beCameraDemoData *demo = (beCameraDemoData *)((beCameraCtrlInfo *)ram->_parentInfo)->_data;
    switch (ram->_st0) {
    case 0: {
        if (self->_viewerMang == 0) {
            igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
            self->_viewerPara = viewer->_parameters;
            self->_viewerMang = (int)viewer;
        }
        beCameraMode *mode = (beCameraMode *)self->_cameraMode;
        if (mode == 0) {
            int alloc;
            SELECT_ALLOCATOR(alloc, self)
            CameraModeRef created(beCameraMode_Create(alloc));
            igObject *r = created.p;
            if (r != 0) r->_refCount = r->_refCount + 1;
            igObject *old = (igObject *)self->_cameraMode;
            if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
            self->_cameraMode = (int)r;
            mode = (beCameraMode *)created.p;
        }
        beCameraMode_SetCameraPath(mode, (igObject *)demo->_cameraPath);
        mode->_timeLength = demo->_endTime;
        mode->_insight = self->_insight;
        mode->_isEnd = 0;
        mode->_nowTimeL = 0;
        mode->_svWorldTimeL = 0;
        igViewManager_SetViewMode((igViewManager *)((igViewerSceneInfoManager *)self->_viewerMang)->_viewManager, (igViewMode *)mode);
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        break;
    }
    case 1:
        break;
    }
}

void beCameraCtrl_UpdateRam(beCameraCtrl *self, beBaseInfoRam *ram) {
    if (self->_isFirst != 0) {
        igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self);
        igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self);
        self->_isFirst = 0;
    }
    if (ram->_isRun != 0) {
        if (beCameraCtrl_IsBoxCamera(self, (beCameraCtrlInfo *)ram->_parentInfo) != 0) {
            beCameraCtrl_UpdateBoxCamera(self, ram);
        } else {
            beCameraCtrl_UpdateDemoCamera(self, ram);
        }
    }
}

int beCameraCtrl_OnMessageText(beCameraCtrl *self, beBaseInfoRam *ram, int message) {
    float pos[3];
    beCameraCtrlInfo *info = (beCameraCtrlInfo *)ram->_parentInfo;
    char *wanted;
    char *moveCode;
    beCameraCtrlInfoRamShake *shake;

    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beCameraCtrl_GetMessageEnum(), (const char *)message)) {
    case MSG_GETDEMONAME:
        if (beCameraCtrl_IsDemoCamera(self, info) != 0) {
            beMessenger_AppendString((beMessenger *)self->_messenger, NAME_OR_EMPTY((char *)info->_name));
        }
        return 1;
    case MSG_SETBOXCAMERA:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            ram->_isRun = 1;
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        } else {
            ram->_isRun = 0;
        }
        return 1;
    case MSG_SETDEMOCAMERA:
        wanted = (char *)beMessenger_GetString((beMessenger *)self->_messenger, 0);
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            beCameraCtrl *owner = (beCameraCtrl *)ram->_parentManager;
            bool found = false;
            int n = OBJECT_LIST(owner->_infoList)->_count;
            int i = 0;
            if (0 < n) {
                beCameraCtrlInfo *other;
                int offset = 0;
                do {
                    other = *(beCameraCtrlInfo **)((char *)OBJECT_LIST(owner->_infoList)->_data + offset);
                    if (beCameraCtrl_IsDemoCamera(self, other) != 0) {
                        if (strcmp(NAME_OR_EMPTY((char *)other->_name), wanted) == 0) {
                            found = true;
                            break;
                        }
                    }
                    i += 1;
                    offset += 4;
                } while (i < n);
            }
            if (found) {
                ram->_isRun = 0;
            } else {
                ram->_isRun = 1;
            }
        } else {
            if (strcmp(wanted, NAME_OR_EMPTY((char *)info->_name)) == 0) {
                ram->_isRun = 1;
                ram->_st0 = 0;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
            } else {
                ram->_isRun = 0;
            }
        }
        return 1;
    case MSG_ISDEMOCAMERA:
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) <= 0) {
            beMessenger_ResizeBool((beMessenger *)self->_messenger, 1);
            beMessenger_SetBool((beMessenger *)self->_messenger, 0, 0);
        } else if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 1) {
            return 1;
        }
        if (ram->_isRun == 1 && beCameraCtrl_IsDemoCamera(self, info) != 0) {
            switch (ram->_st0) {
            case 0:
                beMessenger_SetBool((beMessenger *)self->_messenger, 0, 1);
                break;
            case 1:
                if (((beCameraMode *)self->_cameraMode)->_isEnd == 0) {
                    beMessenger_SetBool((beMessenger *)self->_messenger, 0, 1);
                }
                break;
            }
        }
        return 1;
    case MSG_GETPOSITION:
        pos[0] = self->_avgPos[0];
        pos[1] = self->_avgPos[1];
        pos[2] = self->_avgPos[2];
        beMessenger_AppendVec3((beMessenger *)self->_messenger, pos);
        return 1;
    case MSG_SHOWPOLYGON:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            igBitMask_SetAll((igBitMask *)((igSwitch *)((beCameraBoxData *)info->_data)->_switch)->_childMask);
        }
        return 1;
    case MSG_HIDEPOLYGON:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            igBitMask_ClearAll((igBitMask *)((igSwitch *)((beCameraBoxData *)info->_data)->_switch)->_childMask);
        }
        return 1;
    case MSG_ENABLE:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            ram->_isRun = 1;
        }
        return 1;
    case MSG_DISABLE:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            ram->_isRun = 0;
        }
        return 1;
    case MSG_SHAKE:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            if (ram->_dataList == 0) {
                int alloc;
                SELECT_ALLOCATOR(alloc, self)
                DataListRef created(beBaseInfoDataList_Create(alloc));
                igObject *r = created.p;
                if (r != 0) r->_refCount = r->_refCount + 1;
                { igObject *o = (igObject *)ram->_dataList; RELEASE(o) }
                ram->_dataList = (int)r;
            }
            DataList::Ensure(ram, ram);
            shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "SHK");
            if (shake == 0) {
                int alloc;
                SELECT_ALLOCATOR(alloc, self)
                ShakeRef created(beCameraCtrlInfoRamShake_Create(alloc));
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)created.p);
                shake = (beCameraCtrlInfoRamShake *)created.p;
            }
            moveCode = (char *)beMessenger_GetString((beMessenger *)self->_messenger, 0);
            if (g_stringPool == 0) {
                StringPool *pool = (StringPool *)StringPool_Allocate(0x10);
                if (pool != 0) pool = StringPool_Construct(pool);
                g_stringPool = pool;
            }
            {
                char *interned = StringPool_Intern(g_stringPool, moveCode);
                char *old = (char *)shake->_moveCode;
                if (old != 0) {
                    int *header = (int *)old - 2;
                    int refs = ((int *)old)[-1] - 1;
                    ((int *)old)[-1] = refs;
                    if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
                shake->_moveCode = (int)interned;
            }
            shake->_value = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
            shake->_oneTime = beMessenger_GetFloat((beMessenger *)self->_messenger, 1);
            shake->_endTime = beMessenger_GetFloat((beMessenger *)self->_messenger, 2);
            shake->_movePoint = 0;
            beBaseInfoRam_StartTimer(ram, "SHAKEALL", FramesToTime(shake->_endTime));
            beBaseInfoRam_RemoveTimer(ram, "SHAKEONE");
            shake->_isFirst = 1;
        }
        return 1;
    case MSG_DBGZOOMCLEAR:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            beCameraCtrl_EnableDebugZoom(self, ram, 1);
            self->_debugZoom = 1.0f;
        }
        return 1;
    case MSG_DBGZOOMIN:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            float zoom;
            beCameraCtrl_EnableDebugZoom(self, ram, 1);
            zoom = self->_debugZoom - 0.2f;
            if (!(zoom <= 0.0f)) {
                self->_debugZoom = zoom;
            }
            beCameraCtrl_EnableDebugZoom(self, ram, 0);
        }
        return 1;
    case MSG_DBGZOOMOUT:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            beCameraCtrl_EnableDebugZoom(self, ram, 1);
            if (self->_debugZoom == 1.0f) {
                igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
                int k = 0;
                do {
                    igViewerSceneInfoManager_DebugZoomOut(viewer);
                    k += 1;
                } while (k < 6);
            }
            self->_debugZoom = 0.2f + (float)self->_debugZoom; /* matching construct: hand-written — the cast keeps retail's operand order */
            beCameraCtrl_EnableDebugZoom(self, ram, 0);
        }
        return 1;
    case MSG_ONFREEZE:
        if (ram->_isRun != 0 && beCameraCtrl_IsDemoCamera(self, info) != 0) {
            ((beCameraMode *)self->_cameraMode)->_isFreeze = 1;
        }
        return 1;
    case MSG_OFFREEZE:
        if (ram->_isRun != 0 && beCameraCtrl_IsDemoCamera(self, info) != 0) {
            ((beCameraMode *)self->_cameraMode)->_isFreeze = 0;
        }
        return 1;
    default:
        return 0;
    }
}

igMetaObject *beCameraCtrl_GetMeta(void)
{
    return g_beCameraCtrl_metaObject;
}

static inline igObject *AsCamera(igObject *o) { if (o != 0 && igObject_IsKindOf(o, g_igCamera_metaObject) != 0) { return o; } return 0; }

void beCameraMode_SetCameraPath(beCameraMode *mode, igObject *path) {
    igObject *camera;
    igObject *old;
    if (path != 0) {
        if (path != 0) {
            path->_refCount = path->_refCount + 1;
        }
        old = (igObject *)mode->_cameraPath;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(old);
            }
        }
        mode->_cameraPath = (int)path;
        camera = igGraphPath_GetTail((igGraphPath *)path);
        camera = AsCamera(camera);
        if (camera != 0) {
            camera->_refCount = camera->_refCount + 1;
        }
        old = (igObject *)mode->_camera;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(old);
            }
        }
        mode->_camera = (int)camera;
    }
}

#pragma pop

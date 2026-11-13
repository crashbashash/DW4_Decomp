#include "dw4/reflected.h"
#define SELECT_ALLOCATOR(var, owner) { var = igObject_GetAllocator(owner); var = g_useOwnerAllocator ? var : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define RELEASE(q) { igObject *o_ = (q); if (o_ != 0) { o_->_refCount = o_->_refCount - 1; if (((unsigned long long)((long long)(int)o_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o_); } } }
#define OBJECT_LIST(handle) ((igObjectList *)(handle))
#define TRANSFORM_AT(list, i) ((igTransform *)((int *)OBJECT_LIST(list)->_data)[i])
#define NAME_OR_EMPTY(n) ((n) != 0 ? (n) : emptyString)
#define ENSURE_DATA_LIST(ram) if ((ram)->_dataList == 0) { void *alloc; SELECT_ALLOCATOR(alloc, ram) DataList::Install(ram, DataListRef(beBaseInfoDataList_Create(alloc))); }

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

/* any igObject: slot 20 returns its meta object */
class igObjectSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int vfunc_20();
};

extern "C" {
int Gap__Bec__beCameraCtrl__vfunc_30(void);
int Gap__Bec__beCameraCtrl__vfunc_20(void);
void Gap__Bec__beCameraCtrl__vfunc_29(beCameraCtrl *self, int ram, char *unused);
void Gap__Bec__beCameraCtrl__vfunc_31(beCameraCtrl *self, beBaseInfoRam *ram);
void Gap__Bec__beCameraCtrl__vfunc_32(beCameraCtrl *self);
int Gap__Bec__beCameraCtrl__vfunc_33(beCameraCtrl *self, beBaseInfoRam *ram, int message);
int beCameraCtrl_IsBoxCamera(beCameraCtrl *self, beCameraCtrlInfo *info);
int beCameraCtrl_IsDemoCamera(beCameraCtrl *self, beCameraCtrlInfo *info);
void beCameraCtrl_EnableDebugZoom(beCameraCtrl *self, beBaseInfoRam *ram, int on);
void beCameraCtrl_UpdateBoxCamera(beCameraCtrl *self, beBaseInfoRam *ram);
void beCameraCtrl_UpdateDemoCamera(beCameraCtrl *self, beBaseInfoRam *ram);
void beCameraMode_SetCameraPath(beCameraMode *mode, igObject *path);

void beMessenger_RegisterReceiverFromInfo(int, int, char *);
int beMessenger_SendGroup(...);
int beMessenger_GetMatrixCount(...);
int beMessenger_GetMatrix(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_GetBool(...);
int beMessenger_GetBoolCount(...);
float beMessenger_GetFloat(...);
char *beMessenger_GetString(...);
int beMessenger_ResizeBool(...);
unsigned int beMessenger_ResolveEnumValue(...);
int beMessenger_SetBool(...);
int beCameraCtrl_GetMessageEnum(...);
void *beCameraMode_Create(...);
void *beCameraCtrlInfoRamShake_Create(...);
void *beBaseInfoDataList_Create(...);
unsigned char beBaseInfoRam_HasTimer(...);
int beBaseInfoRam_StartTimer(...);
float beBaseInfoRam_GetTimerFrameDelta(void *, void *);
int beBaseInfoRam_IsTimerExpired(...);
int beBaseInfoRam_RemoveTimer(...);
void igViewerSceneInfoManager_ResetOperationMode(int);
int igViewerSceneInfoManager_DebugZoomOut(...);
int igViewManager_SetViewMode(...);
void *igInsightCore_FindManager(...);
int igInsightCore_AddToScheduler(int, beCameraCtrl *);
int igInsightCore_RemoveFromScheduler(int, beCameraCtrl *);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int igObject_IsKindOf(igObject *, int);
void *Memory_GetAllocatorBySelector(...);
void *igProperty_FindByName(...);
int ObjectList_AppendRetained(...);
int ObjectList_RemoveFirstRetained(...);
igObject *igGraphPath_GetTail(igObject *);
int igBitMask_SetAll(...);
int igBitMask_ClearAll(...);
int igAABox_GetCorner(void *, int, float *);
int Matrix44_GetTranslation(void *, float *);
int Matrix44_SetTranslation(void *, void *);
int Matrix44_Copy(void *, void *);
int Matrix44_GetQuaternion(float *, void *);
int Matrix44_SetQuaternion(void *, float *);
void *Vec3_Lerp(float *, float, float *, float *);
void *Quaternion_Lerp(float *, float, float *, float *);
int StringPool_Allocate(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
int strcmp(...);

extern int g_beCameraCtrlInfo_metaObject[4];
extern int g_beCameraCtrl_metaObject[4];
extern int g_beCameraBoxData_metaObject[4];
extern int g_beCameraDemoData_metaObject[4];
extern int g_igCamera_metaObject[16];
extern int g_igViewerSceneInfoManager_metaObject[4];
extern int g_propertyNameField[4];
extern int g_defaultAllocatorSelector[4];
extern int g_stringPool[4];
extern unsigned char g_useOwnerAllocator;
extern char emptyString[];
extern char CAMERA[];
extern int PLAYER_6[4];
extern int GETMATRIX_7[4];
extern int SHK[4];
extern int CAMHOKAN[4];
extern int SHAKEONE[4];
extern int SHAKEALL[4];
/* per shake step: the eye and interest offsets along x and y, indexed by the move code digit */
extern float g_cameraShakeOffsetX[4];
extern float g_cameraShakeOffsetY[4];
}

/* Read-only parameters are const. b52 binds an inlined function's const parameter to its argument before the
 * body, so the field is loaded ahead of the body's other operands; a plain parameter is folded into the body. */
/* frames at 60 per second -> timer nanoseconds */
static inline long long FramesToTime(const float frames) { return (long long)(1e9f * frames / 60.0f); }
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
            void *alloc;
            SELECT_ALLOCATOR(alloc, owner)
            DataListRef created(beBaseInfoDataList_Create(alloc));
            igObject *r = created.p;
            if (r != 0) r->_refCount = r->_refCount + 1;
            { igObject *o = (igObject *)ram->_dataList; RELEASE(o) }
            ram->_dataList = (int)r;
        }
    }
};

int Gap__Bec__beCameraCtrl__vfunc_30(void)
{
    return g_beCameraCtrlInfo_metaObject[0];
}

void Gap__Bec__beCameraCtrl__vfunc_29(beCameraCtrl *self, int ram, char *unused)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, CAMERA);
}

void Gap__Bec__beCameraCtrl__vfunc_32(beCameraCtrl *self) {
    igObject *mode;

    self->_cameraNow = 0;
    self->_cameraOld = 0;
    if (self->_viewerMang != 0) {
        igViewerSceneInfoManager_ResetOperationMode(self->_viewerMang);
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
    igObjectSlots *data = (igObjectSlots *)info->_data;
    int boxMeta = g_beCameraBoxData_metaObject[0];
    return boxMeta == data->vfunc_20();
}

int beCameraCtrl_IsDemoCamera(beCameraCtrl *self, beCameraCtrlInfo *info) {
    igObjectSlots *data = (igObjectSlots *)info->_data;
    int demoMeta = g_beCameraDemoData_metaObject[0];
    return demoMeta == data->vfunc_20();
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
    void *alloc;
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
    beMessenger_SendGroup(self->_messenger, PLAYER_6, GETMATRIX_7);
    if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
        n = beMessenger_GetMatrixCount(self->_messenger);
        for (i = 0; i < n; i++) {
            beMessenger_GetMatrix(matrix, self->_messenger, i);
            Matrix44_GetTranslation(matrix, pos);
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
                beCameraCtrlInfoRamShake *shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], SHK);
                if (shake != 0) {
                    if (shake->_isFirst != 0) {
                        shake->_isFirst = 0;
                    } else {
                        Matrix44_SetTranslation(TRANSFORM_AT(box->_eyePosList, 0)->_m, shake->_svEyePos);
                        Matrix44_SetTranslation(TRANSFORM_AT(box->_intPosList, 0)->_m, shake->_svIntPos);
                    }
                }
            }
        }
        if (self->_isPosChange != 0) {
            camera = 0;
            Matrix44_SetTranslation(TRANSFORM_AT(box->_transformList, 0)->_m, self->_avgPos);
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
                    igAABox_GetCorner(bound, 0, boxMax);
                    if (!(boxMax[0] < x) && !(boxMax[1] < y) && !(boxMax[2] < z)) {
                        igAABox_GetCorner(bound, 7, boxMin);
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
                    Matrix44_Copy(self->_eyeMatrix, TRANSFORM_AT(box->_eyePosList, 0)->_m);
                    Matrix44_Copy(self->_intMatrix, TRANSFORM_AT(box->_intPosList, 0)->_m);
                    self->_cameraNowFrame = 0.0f;
                    if (self->_viewerMang == 0) {
                        igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
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
                    igViewManager_SetViewMode(((igViewerSceneInfoManager *)self->_viewerMang)->_viewManager, mode);
                }
            }
        }
        if (self->_cameraNow != self->_cameraOld) {
            if (self->_cameraOld == 0 || !(self->_cameraNowFrame < 120.0f)) {
                self->_cameraOld = self->_cameraNow;
                Matrix44_Copy(TRANSFORM_AT(box->_eyePosList, 0)->_m, TRANSFORM_AT(box->_eyePosList, self->_cameraNow)->_m);
                Matrix44_Copy(TRANSFORM_AT(box->_intPosList, 0)->_m, TRANSFORM_AT(box->_intPosList, self->_cameraNow)->_m);
                beBaseInfoRam_RemoveTimer(ram, CAMHOKAN);
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
                    Matrix44_GetTranslation(from, fromPos);
                    Matrix44_GetTranslation(to, toPos);
                    Vec3_Lerp(fromPos, t, fromPos, toPos);
                    Matrix44_SetTranslation(out, fromPos);
                    Matrix44_GetQuaternion(fromRot, from);
                    Matrix44_GetQuaternion(toRot, to);
                    Quaternion_Lerp(fromRot, t, fromRot, toRot);
                    Matrix44_SetQuaternion(out, fromRot);
                    j += 1;
                } while (j < 2);
                if (!(beBaseInfoRam_HasTimer(ram, CAMHOKAN) & 0xFF)) {
                    beBaseInfoRam_StartTimer(ram, CAMHOKAN, 0);
                }
                if (self->_isPosChange == 0) {
                    float frame = self->_cameraNowFrame;
                    self->_cameraNowFrame = frame + 1.5f * beBaseInfoRam_GetTimerFrameDelta(ram, CAMHOKAN);
                } else {
                    float frame = self->_cameraNowFrame;
                    self->_cameraNowFrame = frame + beBaseInfoRam_GetTimerFrameDelta(ram, CAMHOKAN);
                }
            }
        }
        if (ram->_dataList != 0) {
            ENSURE_DATA_LIST(ram)
            {
                beCameraCtrlInfoRamShake *shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName(ram->_dataList, g_propertyNameField[0], SHK);
                if (shake != 0) {
                    float *matrix44;
                    int k = 0;
                    float *offsetX = &g_cameraShakeOffsetX[((char *)shake->_moveCode)[(int)shake->_movePoint] - '0'];
                    float *offsetY = &g_cameraShakeOffsetY[((char *)shake->_moveCode)[(int)shake->_movePoint] - '0'];
                    do {
                        if (k == 0) {
                            matrix44 = TRANSFORM_AT(box->_eyePosList, 0)->_m;
                            Matrix44_GetTranslation(matrix44, shakePos);
                            shake->_svEyePos[0] = shakePos[0];
                            shake->_svEyePos[1] = shakePos[1];
                            shake->_svEyePos[2] = shakePos[2];
                        } else {
                            matrix44 = TRANSFORM_AT(box->_intPosList, 0)->_m;
                            Matrix44_GetTranslation(matrix44, shakePos);
                            shake->_svIntPos[0] = shakePos[0];
                            shake->_svIntPos[1] = shakePos[1];
                            shake->_svIntPos[2] = shakePos[2];
                        }
                        AddShakeOffset(&shakePos[0], offsetX, shake->_value);
                        AddShakeOffset(&shakePos[1], offsetY, shake->_value);
                        Matrix44_SetTranslation(matrix44, shakePos);
                        k += 1;
                    } while (k < 2);
                    if (beBaseInfoRam_IsTimerExpired(ram, SHAKEONE) != 0) {
                        int next = shake->_movePoint + 1;
                        if (((char *)(next + shake->_moveCode))[0] == 0) next = 0;
                        shake->_movePoint = next;
                        beBaseInfoRam_StartTimer(ram, SHAKEONE, FramesToTime(shake->_oneTime));
                    }
                    if (beBaseInfoRam_IsTimerExpired(ram, SHAKEALL) != 0) {
                        int removed;
                        Matrix44_SetTranslation(TRANSFORM_AT(box->_eyePosList, 0)->_m, shake->_svEyePos);
                        Matrix44_SetTranslation(TRANSFORM_AT(box->_intPosList, 0)->_m, shake->_svIntPos);
                        ObjectList_RemoveFirstRetained(&removed, ram->_dataList, shake, 0);
                        beBaseInfoRam_RemoveTimer(ram, SHAKEALL);
                        beBaseInfoRam_RemoveTimer(ram, SHAKEONE);
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
            igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
            self->_viewerPara = viewer->_parameters;
            self->_viewerMang = (int)viewer;
        }
        beCameraMode *mode = (beCameraMode *)self->_cameraMode;
        if (mode == 0) {
            void *alloc;
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
        igViewManager_SetViewMode(((igViewerSceneInfoManager *)self->_viewerMang)->_viewManager, mode);
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

void Gap__Bec__beCameraCtrl__vfunc_31(beCameraCtrl *self, beBaseInfoRam *ram) {
    if (self->_isFirst != 0) {
        igInsightCore_RemoveFromScheduler(self->_insight, self);
        igInsightCore_AddToScheduler(self->_insight, self);
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

int Gap__Bec__beCameraCtrl__vfunc_33(beCameraCtrl *self, beBaseInfoRam *ram, int message) {
    float pos[3];
    beCameraCtrlInfo *info = (beCameraCtrlInfo *)ram->_parentInfo;
    char *wanted;
    char *moveCode;
    beCameraCtrlInfoRamShake *shake;

    switch (beMessenger_ResolveEnumValue(self->_messenger, beCameraCtrl_GetMessageEnum(), message)) {
    case MSG_GETDEMONAME:
        if (beCameraCtrl_IsDemoCamera(self, info) != 0) {
            beMessenger_AppendString(self->_messenger, NAME_OR_EMPTY((char *)info->_name));
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
        wanted = beMessenger_GetString(self->_messenger, 0);
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
        if (beMessenger_GetBoolCount(self->_messenger) <= 0) {
            beMessenger_ResizeBool(self->_messenger, 1);
            beMessenger_SetBool(self->_messenger, 0, 0);
        } else if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) == 1) {
            return 1;
        }
        if (ram->_isRun == 1 && beCameraCtrl_IsDemoCamera(self, info) != 0) {
            switch (ram->_st0) {
            case 0:
                beMessenger_SetBool(self->_messenger, 0, 1);
                break;
            case 1:
                if (((beCameraMode *)self->_cameraMode)->_isEnd == 0) {
                    beMessenger_SetBool(self->_messenger, 0, 1);
                }
                break;
            }
        }
        return 1;
    case MSG_GETPOSITION:
        pos[0] = self->_avgPos[0];
        pos[1] = self->_avgPos[1];
        pos[2] = self->_avgPos[2];
        beMessenger_AppendVec3(self->_messenger, pos);
        return 1;
    case MSG_SHOWPOLYGON:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            igBitMask_SetAll(((igSwitch *)((beCameraBoxData *)info->_data)->_switch)->_childMask);
        }
        return 1;
    case MSG_HIDEPOLYGON:
        if (beCameraCtrl_IsBoxCamera(self, info) != 0) {
            igBitMask_ClearAll(((igSwitch *)((beCameraBoxData *)info->_data)->_switch)->_childMask);
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
                void *alloc;
                SELECT_ALLOCATOR(alloc, self)
                DataListRef created(beBaseInfoDataList_Create(alloc));
                igObject *r = created.p;
                if (r != 0) r->_refCount = r->_refCount + 1;
                { igObject *o = (igObject *)ram->_dataList; RELEASE(o) }
                ram->_dataList = (int)r;
            }
            DataList::Ensure(ram, ram);
            shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName((void *)ram->_dataList, g_propertyNameField[0], SHK);
            if (shake == 0) {
                void *alloc;
                SELECT_ALLOCATOR(alloc, self)
                ShakeRef created(beCameraCtrlInfoRamShake_Create(alloc));
                ObjectList_AppendRetained((void *)ram->_dataList, (void *)created.p);
                shake = (beCameraCtrlInfoRamShake *)created.p;
            }
            moveCode = beMessenger_GetString(self->_messenger, 0);
            if (g_stringPool[0] == 0) {
                int pool = StringPool_Allocate(0x10);
                if (pool != 0) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            {
                char *interned = StringPool_Intern(g_stringPool[0], moveCode);
                char *old = (char *)shake->_moveCode;
                if (old != 0) {
                    int *header = (int *)old - 2;
                    int refs = ((int *)old)[-1] - 1;
                    ((int *)old)[-1] = refs;
                    if (refs == 0) StringChunk_ReleaseHeader(*header, header);
                }
                shake->_moveCode = (int)interned;
            }
            shake->_value = beMessenger_GetFloat(self->_messenger, 0);
            shake->_oneTime = beMessenger_GetFloat(self->_messenger, 1);
            shake->_endTime = beMessenger_GetFloat(self->_messenger, 2);
            shake->_movePoint = 0;
            beBaseInfoRam_StartTimer(ram, SHAKEALL, FramesToTime(shake->_endTime));
            beBaseInfoRam_RemoveTimer(ram, SHAKEONE);
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
                int viewer = ((int)igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]));
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

int Gap__Bec__beCameraCtrl__vfunc_20(void)
{
    return g_beCameraCtrl_metaObject[0];
}

static inline igObject *AsCamera(igObject *o) { if (o != 0 && igObject_IsKindOf(o, g_igCamera_metaObject[0]) != 0) { return o; } return 0; }

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
        camera = igGraphPath_GetTail(path);
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

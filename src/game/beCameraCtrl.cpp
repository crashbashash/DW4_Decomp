#include "dw4/reflected.h"
#define ALLOC(a, o) { a = igObject_GetAllocator(o); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define F(x) (*(float *)&(x))
#define LIST(p) ((igObjectList *)(p))
#define XFORM(l, i) ((igTransform *)((int *)LIST(l)->_data)[i])
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define ENSURE_DATA_LIST(act) if ((act)->_dataList == 0) { void *alloc; ALLOC(alloc, act) DataListInstall::go(act, RPD(beBaseInfoDataList_Create(alloc))); }
#define ALLOC_OF(owner, a) { a = igObject_GetAllocator(owner); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define NAME_OR_EMPTY(n) ((n) != 0 ? (n) : emptyString)

extern "C" int Gap__Bec__beCameraCtrl__vfunc_30(void);
extern "C" int Gap__Bec__beCameraCtrl__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int FUN_00462dc0(int);
extern "C" int igObject_Destroy(...);
extern "C" int FUN_00378e40(void *arg0, void *arg1);
extern "C" int FUN_00378e80(int dummy0, void *arg1);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int Matrix44_GetTranslation(void *, float *);
extern "C" void * igObject_GetAllocator(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" void *beBaseInfoDataList_Create(...);
extern "C" void * FUN_003689f0(...);
extern "C" void *igProperty_FindByName(...);
extern "C" int Matrix44_SetTranslation(void *, void *);
extern "C" int FUN_0018ab70(void *, int, float *);
extern "C" int Matrix44_Copy(void *, void *);
extern "C" void * FUN_00236f80(...);
extern "C" int FUN_00463fd0(...);
extern "C" int FUN_003a8580(...);
extern "C" void *FUN_00192f00(float *, float, float *, float *);
extern "C" int FUN_001925f0(float *, void *);
extern "C" void *FUN_00192cc0(float *, float, float *, float *);
extern "C" int FUN_00191770(void *, float *);
extern "C" unsigned char FUN_003a7d80(...);
extern "C" int FUN_003a7a20(...);
extern "C" float FUN_003a8140(void *, void *);
extern "C" int FUN_003a7e90(...);
extern "C" int __fixsfdi(float);
extern "C" int ObjectList_RemoveFirstRetained(...);
extern "C" int FUN_001b1cf0(...);
extern "C" int FUN_001b1dc0(...);
extern "C" int FUN_002eb010(...);
extern "C" void *FUN_003694a0(...);
extern "C" int FUN_003697c0(...);
extern "C" int FUN_00462d20(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" char *StringPool_Intern(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_AppendVec3(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" float beMessenger_GetFloat(...);
extern "C" char *beMessenger_GetString(...);
extern "C" int beMessenger_ResizeBool(...);
extern "C" unsigned int beMessenger_ResolveEnumValue(...);
extern "C" int beMessenger_SetBool(...);
extern "C" int strcmp(...);
extern "C" int g_beCameraCtrlInfo_metaObject[4];
extern "C" int g_beCameraCtrl_metaObject[4];
extern "C" char DAT_0050e1f0[];
extern "C" void Gap__Bec__beCameraCtrl__vfunc_29(beCameraCtrl * p0, int p1, char * p2);
typedef struct RefCountedObject { char pad4[4]; int f4; } RefCountedObject;
extern "C" void Gap__Bec__beCameraCtrl__vfunc_32(beCameraCtrl *arg0);
extern "C" int g_beCameraBoxData_metaObject[4];
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" int g_beCameraDemoData_metaObject[4];
extern "C" void FUN_00378ec0(beCameraCtrl *self, beBaseInfoRam *ram, int on);
extern "C" int DAT_0050e1f8[4];
extern "C" int DAT_0050e200[4];
extern "C" int DAT_0050e210[4];
extern "C" int DAT_0050e218[4];
extern "C" int DAT_0050e228[4];
extern "C" int DAT_0050e238[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" float DAT_004c8820[4];
extern "C" float DAT_004c8850[4];
extern "C" unsigned char GPR_00554c14;
/* Arena handles (4-byte ints in the reflected structs) are followed with an explicit cast. */



struct Slot16 { int v; int pad[3]; };
/* The exception range starts where each holder is constructed (`RPD h(create(...))`), so only
 * calls after construction are covered; one class per destructor copy is needed. */
struct RPD { igObject *p; RPD(void *x) { p = (igObject *)x; } ~RPD() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
struct RPE { igObject *p; RPE(void *x) { p = (igObject *)x; } ~RPE() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
struct DataListInstall { static inline void go(beBaseInfoRam *act, const RPD &fresh) {
    igObject *r = fresh.p;
    if (r != 0) r->_refCount = r->_refCount + 1;
    { igObject *o = (igObject *)act->_dataList; REL(o) }
    act->_dataList = (int)r;
} };
extern "C" void FUN_00378ed0(beCameraCtrl *self, beBaseInfoRam *act);

extern "C" void FUN_00379a90(beCameraCtrl *self, beBaseInfoRam *act);
extern "C" int FUN_00236be0(int, beCameraCtrl *);
extern "C" int FUN_00236c40(int, beCameraCtrl *);
extern "C" void Gap__Bec__beCameraCtrl__vfunc_31(beCameraCtrl *arg0, beBaseInfoRam *arg1);
extern "C" char emptyString[];
extern "C" int g_stringPool[4];
/* the camera info's box data: +8 is the camera switch node whose +0x20 is the box handle */
struct SwitchNode { char pad[0x20]; int _handle; };
struct BoxData { int _vtable; unsigned int _refCount; SwitchNode *_switch; };
struct CamInfo { int _vtable; unsigned int _refCount; char *_name; char pad[0x10]; BoxData *_data; };
struct ModeFlags { char pad[0x70]; unsigned char _isEnd; unsigned char _isFreeze; };
struct CamOwner { char pad[0x18]; igObjectList *_ramList; };
struct CamInfoPtr { char pad[8]; char *_name; };
struct RPE_379ce0 { igObject *p; RPE_379ce0(void *x) { p = (igObject *)x; } ~RPE_379ce0() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
/* create the per-info data list on first use (same shape as the matched per-frame update FUN_00378ed0).
 * Matching construct: this one is an inline member, while the first and third holders in message 9 are written out
 * as blocks; that is what orders the three holder stack slots as retail has them (block locals before inline ones). */
struct UP { static inline void Ensure(void *owner, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        void *alloc;
        ALLOC_OF(owner, alloc)
        RPD h(beBaseInfoDataList_Create(alloc));
        igObject *r = h.p;
        if (r != 0) r->_refCount = r->_refCount + 1;
        { igObject *o = (igObject *)ram->_dataList; REL(o) }
        ram->_dataList = (int)r;
    } } };
extern "C" int Gap__Bec__beCameraCtrl__vfunc_33(beCameraCtrl *self, beBaseInfoRam *ram, int msg);
typedef struct Rc { int w0; int refs; } Rc;
typedef struct O { char p0[76]; Rc *f76; Rc *f80; } O;
extern "C" Rc *FUN_001c5990(Rc *);
extern "C" int igObject_IsKindOf(Rc *, int);
extern "C" int g_igCamera_metaObject[16];
extern "C" void FUN_0037a690(O *arg0, Rc *arg1);

int Gap__Bec__beCameraCtrl__vfunc_30(void)
{
    return g_beCameraCtrlInfo_metaObject[0];
}

void Gap__Bec__beCameraCtrl__vfunc_29(beCameraCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0050e1f0);
}

void Gap__Bec__beCameraCtrl__vfunc_32(beCameraCtrl *arg0) {
    RefCountedObject *t;

    arg0->_cameraNow = 0;
    arg0->_cameraOld = 0;
    if (arg0->_viewerMang != 0) {
        FUN_00462dc0(arg0->_viewerMang);
    }
    t = (RefCountedObject *)arg0->_cameraMode;
    if (t != 0) {
        t->f4 -= 1;
        if ((t->f4 & 0x7fffff) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_cameraMode = 0;
}

int FUN_00378e40(void *arg0, void *arg1) {
    int temp_s0;
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg1) + 28));
    temp_s0 = g_beCameraBoxData_metaObject[0];
    return temp_s0 == ((DW4VC_88_0 *)(temp_a0))->vX();
}

int FUN_00378e80(int dummy0, void *arg1) {
    int temp_s0;
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg1) + 28));
    temp_s0 = g_beCameraDemoData_metaObject[0];
    return temp_s0 == ((DW4VC_88_0 *)(temp_a0))->vX();
}

void FUN_00378ec0(beCameraCtrl *self, beBaseInfoRam *ram, int on)
{
}

void FUN_00378ed0(beCameraCtrl *self, beBaseInfoRam *act) {
    float av[4];
    float lo[4];
    float hi[4];
    float tA[4];
    float tB[4];
    float tmp[4];
    float q1[4];
    float q2[4];
    int mat[16];
    Slot16 vn;
    Slot16 voff;
    beCameraBoxData *sys;
    float fx, fy, fz;
    int n;
    int i;
    bool d;
    void *alloc;
    int cam;

    sys = (beCameraBoxData *)((beCameraCtrlInfo *)act->_parentInfo)->_data;
    switch (act->_st0) {
    case 0:
        self->_avgPos[0] = -1.0f;
        self->_avgPos[1] = -1.0f;
        self->_avgPos[2] = -1.0f;
        self->_cameraNow = 0;
        act->_st0 = act->_st0 + 1;
        act->_st3 = 0;
        act->_st2 = 0;
        act->_st1 = 0;
        break;
    default:
        break;
    }
    fx = 0.0f;
    fy = 0.0f;
    fz = 0.0f;
    beMessenger_SendGroup(self->_messenger, &DAT_0050e1f8[0], &DAT_0050e200[0]);
    if (beMessenger_GetMatrixCount(self->_messenger) != 0) {
        n = beMessenger_GetMatrixCount(self->_messenger);
        for (i = 0; i < n; i++) {
            beMessenger_GetMatrix(mat, self->_messenger, i);
            Matrix44_GetTranslation(mat, av);
            fx += av[0];
            fy += av[1];
            fz += av[2];
        }
        switch (n) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            fx /= 2.0f; fy /= 2.0f; fz /= 2.0f;
            break;
        case 3:
            fx /= 3.0f; fy /= 3.0f; fz /= 3.0f;
            break;
        case 4:
            fx /= 4.0f; fy /= 4.0f; fz /= 4.0f;
            break;
        default:
            break;
        }
        { float *ap = self->_avgPos; d = (ap[0] != fx) || (ap[1] != fy) || (ap[2] != fz); }
        if (d) {
            self->_avgPos[0] = fx;
            self->_avgPos[1] = fy;
            self->_avgPos[2] = fz;
            self->_isPosChange = 1;
        } else {
            self->_isPosChange = 0;
        }
        if (act->_dataList != 0) {
            ENSURE_DATA_LIST(act)
            {
                beCameraCtrlInfoRamShake *pr = (beCameraCtrlInfoRamShake *)igProperty_FindByName(act->_dataList, g_propertyNameField[0], &DAT_0050e210[0]);
                if (pr != 0) {
                    if (pr->_isFirst != 0) {
                        pr->_isFirst = 0;
                    } else {
                        Matrix44_SetTranslation(XFORM(sys->_eyePosList, 0)->_m, pr->_svEyePos);
                        Matrix44_SetTranslation(XFORM(sys->_intPosList, 0)->_m, pr->_svIntPos);
                    }
                }
            }
        }
        if (self->_isPosChange != 0) {
            cam = 0;
            Matrix44_SetTranslation(XFORM(sys->_transformList, 0)->_m, self->_avgPos);
            self->_savePos[0] = self->_avgPos[0];
            self->_savePos[1] = self->_avgPos[1];
            self->_savePos[2] = self->_avgPos[2];
            fx = self->_avgPos[0];
            fy = self->_avgPos[1];
            fz = self->_avgPos[2];
            vn.v = LIST(sys->_geometryList)->_count;
            i = 1;
            if (1 < vn.v) {
                voff.v = 4;
                do {
                    char *ba = (char *)LIST(sys->_geometryList)->_data;
                    int oo = voff.v;
                    void *bo = (void *)((igNode *)((void **)(ba + oo))[0])->_bound;
                    FUN_0018ab70(bo, 0, lo);
                    if (!(lo[0] < fx) && !(lo[1] < fy) && !(lo[2] < fz)) {
                        FUN_0018ab70(bo, 7, hi);
                        if (hi[0] <= fx && hi[1] <= fy && hi[2] <= fz) {
                            cam = i;
                            break;
                        }
                    }
                    i += 1;
                    voff.v += 4;
                } while (i < vn.v);
            }
            if (cam != 0) {
                if (cam != self->_cameraNow) {
                    beCameraMode *cm;
                    self->_cameraOld = self->_cameraNow;
                    self->_cameraNow = cam;
                    Matrix44_Copy(self->_eyeMatrix, XFORM(sys->_eyePosList, 0)->_m);
                    Matrix44_Copy(self->_intMatrix, XFORM(sys->_intPosList, 0)->_m);
                    F(self->_cameraNowFrame) = 0.0f;
                    if (self->_viewerMang == 0) {
                        igViewerSceneInfoManager *vm = (igViewerSceneInfoManager *)FUN_00236f80(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
                        self->_viewerPara = vm->_parameters;
                        self->_viewerMang = (int)vm;
                    }
                    cm = (beCameraMode *)self->_cameraMode;
                    if (cm == 0) {
                        ALLOC(alloc, self)
                        RPE h412(FUN_003689f0(alloc));
                        igObject *r = h412.p;
                        if (r != 0) r->_refCount = r->_refCount + 1;
                        { igObject *o = (igObject *)self->_cameraMode; REL(o) }
                        self->_cameraMode = (int)r;
                        cm = (beCameraMode *)h412.p;
                    }
                    FUN_0037a690((O *)cm, (Rc *)(((void **)LIST(((igViewerParameters *)self->_viewerPara)->_cameras)->_data)[0]));
                    cm->_timeLength = 0;
                    cm->_insight = self->_insight;
                    cm->_isEnd = 0;
                    cm->_nowTimeL = 0;
                    cm->_svWorldTimeL = 0;
                    FUN_00463fd0(((igViewerSceneInfoManager *)self->_viewerMang)->_viewManager, cm);
                }
            }
        }
        if (self->_cameraNow != self->_cameraOld) {
            if (self->_cameraOld == 0 || !(F(self->_cameraNowFrame) < 120.0f)) {
                self->_cameraOld = self->_cameraNow;
                Matrix44_Copy(XFORM(sys->_eyePosList, 0)->_m, XFORM(sys->_eyePosList, self->_cameraNow)->_m);
                Matrix44_Copy(XFORM(sys->_intPosList, 0)->_m, XFORM(sys->_intPosList, self->_cameraNow)->_m);
                FUN_003a8580(act, &DAT_0050e218[0]);
            } else {
                float t = F(self->_cameraNowFrame) / 120.0f;
                float *s1;
                float *s5;
                float *s6;
                int j = 0;
                do {
                    switch (j) {
                    case 0:
                        s1 = self->_eyeMatrix;
                        s5 = XFORM(sys->_eyePosList, self->_cameraNow)->_m;
                        s6 = XFORM(sys->_eyePosList, 0)->_m;
                        break;
                    case 1:
                        s1 = self->_intMatrix;
                        s5 = XFORM(sys->_intPosList, self->_cameraNow)->_m;
                        s6 = XFORM(sys->_intPosList, 0)->_m;
                        break;
                    }
                    Matrix44_GetTranslation(s1, tA);
                    Matrix44_GetTranslation(s5, tB);
                    FUN_00192f00(tA, t, tA, tB);
                    Matrix44_SetTranslation(s6, tA);
                    FUN_001925f0(q1, s1);
                    FUN_001925f0(q2, s5);
                    FUN_00192cc0(q1, t, q1, q2);
                    FUN_00191770(s6, q1);
                    j += 1;
                } while (j < 2);
                if (!(FUN_003a7d80(act, &DAT_0050e218[0]) & 0xFF)) {
                    FUN_003a7a20(act, &DAT_0050e218[0], 0);
                }
                if (self->_isPosChange == 0) {
                    float cur = F(self->_cameraNowFrame);
                    F(self->_cameraNowFrame) = cur + 1.5f * FUN_003a8140(act, &DAT_0050e218[0]);
                } else {
                    float cur2 = F(self->_cameraNowFrame);
                    F(self->_cameraNowFrame) = cur2 + FUN_003a8140(act, &DAT_0050e218[0]);
                }
            }
        }
        if (act->_dataList != 0) {
            ENSURE_DATA_LIST(act)
            {
                beCameraCtrlInfoRamShake *pr = (beCameraCtrlInfoRamShake *)igProperty_FindByName(act->_dataList, g_propertyNameField[0], &DAT_0050e210[0]);
                if (pr != 0) {
                    float *mp;
                    int k = 0;
                    float *c1 = &DAT_004c8820[((char *)pr->_moveCode)[(int)pr->_movePoint] - 0x30];
                    float *c2 = &DAT_004c8850[((char *)pr->_moveCode)[(int)pr->_movePoint] - 0x30];
                    do {
                        if (k == 0) {
                            mp = XFORM(sys->_eyePosList, 0)->_m;
                            Matrix44_GetTranslation(mp, tmp);
                            pr->_svEyePos[0] = tmp[0];
                            pr->_svEyePos[1] = tmp[1];
                            pr->_svEyePos[2] = tmp[2];
                        } else {
                            mp = XFORM(sys->_intPosList, 0)->_m;
                            Matrix44_GetTranslation(mp, tmp);
                            pr->_svIntPos[0] = tmp[0];
                            pr->_svIntPos[1] = tmp[1];
                            pr->_svIntPos[2] = tmp[2];
                        }
                        float sc = pr->_value;
                        sc = sc;
                        tmp[0] = *c1 * sc + tmp[0];
                        float sd = pr->_value;
                        sd = sd;
                        tmp[1] = *c2 * sd + tmp[1];
                        Matrix44_SetTranslation(mp, tmp);
                        k += 1;
                    } while (k < 2);
                    if (FUN_003a7e90(act, &DAT_0050e228[0]) != 0) {
                        int np = pr->_movePoint + 1;
                        if (((char *)(np + pr->_moveCode))[0] == 0) np = 0;
                        pr->_movePoint = np;
                        float w = pr->_oneTime; w = w; FUN_003a7a20(act, &DAT_0050e228[0], __fixsfdi((1e9f * w) / 60.0f));
                    }
                    if (FUN_003a7e90(act, &DAT_0050e238[0]) != 0) {
                        int h408;
                        Matrix44_SetTranslation(XFORM(sys->_eyePosList, 0)->_m, pr->_svEyePos);
                        Matrix44_SetTranslation(XFORM(sys->_intPosList, 0)->_m, pr->_svIntPos);
                        ObjectList_RemoveFirstRetained(&h408, act->_dataList, pr, 0);
                        FUN_003a8580(act, &DAT_0050e238[0]);
                        FUN_003a8580(act, &DAT_0050e228[0]);
                    }
                }
            }
        }
    }
}

void FUN_00379a90(beCameraCtrl *self, beBaseInfoRam *act) {
    beCameraDemoData *demo = (beCameraDemoData *)((beCameraCtrlInfo *)act->_parentInfo)->_data;
    switch (act->_st0) {
    case 0: {
        if (self->_viewerMang == 0) {
            igViewerSceneInfoManager *vm = (igViewerSceneInfoManager *)FUN_00236f80(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
            self->_viewerPara = vm->_parameters;
            self->_viewerMang = (int)vm;
        }
        beCameraMode *cm = (beCameraMode *)self->_cameraMode;
        if (cm == 0) {
            void *alloc = igObject_GetAllocator(self);
            alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            RPE created(((beCameraMode *)FUN_003689f0(alloc)));
            igObject *r = created.p;
            if (r != 0) r->_refCount = r->_refCount + 1;
            igObject *old = (igObject *)self->_cameraMode;
            if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
            self->_cameraMode = (int)r;
            cm = (beCameraMode *)created.p;
        }
        FUN_0037a690((O *)cm, (Rc *)demo->_cameraPath);
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

void Gap__Bec__beCameraCtrl__vfunc_31(beCameraCtrl *arg0, beBaseInfoRam *arg1) {
    if (arg0->_isFirst != 0) {
        FUN_00236c40(arg0->_insight, arg0);
        FUN_00236be0(arg0->_insight, arg0);
        arg0->_isFirst = 0;
    }
    if (arg1->_isRun != 0) {
        if (FUN_00378e40((void *)arg0, (void *)arg1->_parentInfo) != 0) {
            FUN_00378ed0(arg0, arg1);
        } else {
            FUN_00379a90(arg0, arg1);
        }
    }
}

int Gap__Bec__beCameraCtrl__vfunc_33(beCameraCtrl *self, beBaseInfoRam *ram, int msg) {
    float pos[3];
    CamInfo *info = (CamInfo *)ram->_parentInfo;
    char *wanted;
    char *nm;
    beCameraCtrlInfoRamShake *shake;

    switch (beMessenger_ResolveEnumValue(self->_messenger, FUN_003697c0(), msg)) {
    case 7:
        if (FUN_00378e80((int)self, (void *)info) != 0) {
            beMessenger_AppendString(self->_messenger, NAME_OR_EMPTY(info->_name));
        }
        return 1;
    case 5:
        if (FUN_00378e40(self, info) != 0) {
            ram->_isRun = 1;
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        } else {
            ram->_isRun = 0;
        }
        return 1;
    case 6:
        wanted = beMessenger_GetString(self->_messenger, 0);
        if (FUN_00378e40(self, info) != 0) {
            CamOwner *owner = (CamOwner *)ram->_parentManager;
            bool found = false;
            int n = owner->_ramList->_count;
            int i = 0;
            if (0 < n) {
                CamInfoPtr *other;
                int off = 0;
                do {
                    other = *(CamInfoPtr **)((char *)owner->_ramList->_data + off);
                    if (FUN_00378e80((int)self, (void *)other) != 0) {
                        if (strcmp(NAME_OR_EMPTY(other->_name), wanted) == 0) {
                            found = true;
                            break;
                        }
                    }
                    i += 1;
                    off += 4;
                } while (i < n);
            }
            if (found) {
                ram->_isRun = 0;
            } else {
                ram->_isRun = 1;
            }
        } else {
            if (strcmp(wanted, NAME_OR_EMPTY(info->_name)) == 0) {
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
    case 8:
        if (beMessenger_GetBoolCount(self->_messenger) <= 0) {
            beMessenger_ResizeBool(self->_messenger, 1);
            beMessenger_SetBool(self->_messenger, 0, 0);
        } else if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) == 1) {
            return 1;
        }
        if (ram->_isRun == 1 && FUN_00378e80((int)self, (void *)info) != 0) {
            switch (ram->_st0) {
            case 0:
                beMessenger_SetBool(self->_messenger, 0, 1);
                break;
            case 1:
                if (((ModeFlags *)self->_cameraMode)->_isEnd == 0) {
                    beMessenger_SetBool(self->_messenger, 0, 1);
                }
                break;
            }
        }
        return 1;
    case 2:
        pos[0] = *(float *)&self->_avgPos[0];
        pos[1] = *(float *)&self->_avgPos[1];
        pos[2] = *(float *)&self->_avgPos[2];
        beMessenger_AppendVec3(self->_messenger, pos);
        return 1;
    case 0:
        if (FUN_00378e40(self, info) != 0) {
            FUN_001b1cf0(info->_data->_switch->_handle);
        }
        return 1;
    case 1:
        if (FUN_00378e40(self, info) != 0) {
            FUN_001b1dc0(info->_data->_switch->_handle);
        }
        return 1;
    case 3:
        if (FUN_00378e40(self, info) != 0) {
            ram->_isRun = 1;
        }
        return 1;
    case 4:
        if (FUN_00378e40(self, info) != 0) {
            ram->_isRun = 0;
        }
        return 1;
    case 9:
        if (FUN_00378e40(self, info) != 0) {
            if (ram->_dataList == 0) {
                void *alloc;
                ALLOC_OF(self, alloc)
                RPD h(beBaseInfoDataList_Create(alloc));
                igObject *r = h.p;
                if (r != 0) r->_refCount = r->_refCount + 1;
                { igObject *o = (igObject *)ram->_dataList; REL(o) }
                ram->_dataList = (int)r;
            }
            UP::Ensure(ram, ram);
            shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName((void *)ram->_dataList, g_propertyNameField[0], &DAT_0050e210[0]);
            if (shake == 0) {
                void *alloc;
                ALLOC_OF(self, alloc)
                RPE_379ce0 created(FUN_003694a0(alloc));
                ObjectList_AppendRetained((void *)ram->_dataList, (void *)created.p);
                shake = (beCameraCtrlInfoRamShake *)created.p;
            }
            nm = beMessenger_GetString(self->_messenger, 0);
            if (g_stringPool[0] == 0) {
                int pool = FUN_002eb010(0x10);
                if (pool != 0) pool = StringPool_Construct(pool);
                g_stringPool[0] = pool;
            }
            {
                char *interned = StringPool_Intern(g_stringPool[0], nm);
                char *old = (char *)shake->_moveCode;
                if (old != 0) {
                    int *hd = (int *)old - 2;
                    int cnt = ((int *)old)[-1] - 1;
                    ((int *)old)[-1] = cnt;
                    if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                shake->_moveCode = (int)interned;
            }
            shake->_value = beMessenger_GetFloat(self->_messenger, 0);
            shake->_oneTime = beMessenger_GetFloat(self->_messenger, 1);
            shake->_endTime = beMessenger_GetFloat(self->_messenger, 2);
            shake->_movePoint = 0;
            /* matching construct: endTime goes through a local (as in FUN_00378ed0) to order the float loads; seconds -> ticks at 60 fps */
            { float w = shake->_endTime; w = w; FUN_003a7a20(ram, &DAT_0050e238[0], __fixsfdi((1e9f * w) / 60.0f)); w = 0.0f; }
            FUN_003a8580(ram, &DAT_0050e228[0]);
            shake->_isFirst = 1;
        }
        return 1;
    case 12:
        if (FUN_00378e40(self, info) != 0) {
            FUN_00378ec0(self, ram, 1);
            self->_debugZoom = 1.0f;
        }
        return 1;
    case 13:
        if (FUN_00378e40(self, info) != 0) {
            float z;
            FUN_00378ec0(self, ram, 1);
            z = self->_debugZoom - 0.2f;
            if (!(z <= 0.0f)) {
                self->_debugZoom = z;
            }
            FUN_00378ec0(self, ram, 0);
        }
        return 1;
    case 14:
        if (FUN_00378e40(self, info) != 0) {
            FUN_00378ec0(self, ram, 1);
            if (self->_debugZoom == 1.0f) {
                int snd = ((int)FUN_00236f80(self->_insight, g_igViewerSceneInfoManager_metaObject[0]));
                int k = 0;
                do {
                    FUN_00462d20(snd);
                    k += 1;
                } while (k < 6);
            }
            self->_debugZoom = 0.2f + (float)self->_debugZoom; /* matching construct: the cast keeps retail's operand order */
            FUN_00378ec0(self, ram, 0);
        }
        return 1;
    case 10:
        if (ram->_isRun != 0 && FUN_00378e80((int)self, (void *)info) != 0) {
            ((ModeFlags *)self->_cameraMode)->_isFreeze = 1;
        }
        return 1;
    case 11:
        if (ram->_isRun != 0 && FUN_00378e80((int)self, (void *)info) != 0) {
            ((ModeFlags *)self->_cameraMode)->_isFreeze = 0;
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

static inline Rc * cast0(Rc * o) { if (o != 0 && igObject_IsKindOf(o, g_igCamera_metaObject[0]) != 0) { return o; } return 0; }

void FUN_0037a690(O *arg0, Rc *arg1) {
    Rc *s0;
    Rc *a;
    if (arg1 != 0) {
        if (arg1 != 0) {
            arg1->refs = arg1->refs + 1;
        }
        a = arg0->f76;
        if (a != 0) {
            a->refs = a->refs - 1;
            if (((unsigned long long)(long long)a->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->f76 = arg1;
        s0 = FUN_001c5990(arg1);
        s0 = cast0(s0);
        if (s0 != 0) {
            s0->refs = s0->refs + 1;
        }
        a = arg0->f80;
        if (a != 0) {
            a->refs = a->refs - 1;
            if (((unsigned long long)(long long)a->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->f80 = s0;
    }
}


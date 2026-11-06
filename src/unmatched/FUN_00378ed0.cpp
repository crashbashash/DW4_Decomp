/* BeCameraCtrl per-frame update (receiver beCameraCtrl, argument a camera-owning actor) */
#include "dw4/reflected.h"
#pragma inline_depth(8)
extern "C" {
int beMessenger_SendGroup(...);
int beMessenger_GetMatrixCount(...);
int beMessenger_GetMatrix(...);
int Matrix44_GetTranslation(void *, float *);
void *igObject_GetAllocator(...);
void *Memory_GetAllocatorBySelector(...);
void *beBaseInfoDataList_Create(...);
void *FUN_003689f0(...);
void igObject_Destroy(void *);
void *igProperty_FindByName(...);
int Matrix44_SetTranslation(void *, void *);
int FUN_0018ab70(void *, int, float *);
int Matrix44_Copy(void *, void *);
void *FUN_00236f80(...);
int FUN_0037a690(...);
int FUN_00463fd0(...);
int FUN_003a8580(...);
void *FUN_00192f00(float *, float, float *, float *);
int FUN_001925f0(float *, void *);
void *FUN_00192cc0(float *, float, float *, float *);
int FUN_00191770(void *, float *);
unsigned char FUN_003a7d80(...);
int FUN_003a7a20(...);
float FUN_003a8140(void *, void *);
int FUN_003a7e90(...);
int FUN_00230110(float);
int ObjectList_RemoveFirstRetained(...);
extern int DAT_0050e1f8[4];
extern int DAT_0050e200[4];
extern int DAT_0050e210[4];
extern int DAT_0050e218[4];
extern int DAT_0050e228[4];
extern int DAT_0050e238[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_0058c790[4];
extern float DAT_004c8820[4];
extern float DAT_004c8850[4];
extern unsigned char GPR_00554c14;
void FUN_00378ed0(beCameraCtrl *self, beBaseInfoRam *act);
}

#define ALLOC(a, o) { a = igObject_GetAllocator(o); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }
#define F(x) (*(float *)&(x))

/* arena handles (4-byte ints in the reflected structs) are followed with an explicit cast */
#define LIST(p) ((igObjectList *)(p))
#define XFORM(l, i) ((igTransform *)((int *)LIST(l)->_data)[i])

struct Slot16 { int v; int pad[3]; };

/* Releasing holders: the range starts where each is constructed (`RPD h(create(...))`), so only calls after construction are covered; one class per retail dtor copy (RPD = 0x33e9c0, RPE = 0x3699a0). */
struct RPD { igObject *p; RPD(void *x) { p = (igObject *)x; } ~RPD() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
struct RPE { igObject *p; RPE(void *x) { p = (igObject *)x; } ~RPE() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }

struct UP { static inline void Ensure(beBaseInfoRam *act) {
    if (act->_dataList == 0) {
        void *alloc;
        ALLOC(alloc, act)
        RPD h(beBaseInfoDataList_Create(alloc));
        igObject *r = h.p;
        if (r != 0) r->_refCount = r->_refCount + 1;
        { igObject *o = (igObject *)act->_dataList; REL(o) }
        act->_dataList = (int)r;
    } } };

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
            UP::Ensure(act);
            {
                beCameraCtrlInfoRamShake *pr = (beCameraCtrlInfoRamShake *)igProperty_FindByName(act->_dataList, DAT_00585be0[0], &DAT_0050e210[0]);
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
                        igViewerSceneInfoManager *vm = (igViewerSceneInfoManager *)FUN_00236f80(self->_insight, DAT_0058c790[0]);
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
                    FUN_0037a690(cm, ((void **)LIST(((igViewerParameters *)self->_viewerPara)->_cameras)->_data)[0]);
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
            UP::Ensure(act);
            {
                beCameraCtrlInfoRamShake *pr = (beCameraCtrlInfoRamShake *)igProperty_FindByName(act->_dataList, DAT_00585be0[0], &DAT_0050e210[0]);
                if (pr != 0) {
                    float *mp;
                    int k = 0;
                    float *c1 = &DAT_004c8820[(*(char **)&pr->_moveCode)[pr->_movePoint] - 0x30];
                    float *c2 = &DAT_004c8850[(*(char **)&pr->_moveCode)[pr->_movePoint] - 0x30];
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
                        tmp[0] = *c1 * sc + tmp[0];
                        sc = pr->_value;
                        float sd = sc;
                        tmp[1] = *c2 * sd + tmp[1];
                        sc = sd;
                        Matrix44_SetTranslation(mp, tmp);
                        k += 1;
                    } while (k < 2);
                    if (FUN_003a7e90(act, &DAT_0050e228[0]) != 0) {
                        int np = pr->_movePoint + 1;
                        if (((char *)(np + pr->_moveCode))[0] == 0) np = 0;
                        pr->_movePoint = np;
                        float w = pr->_oneTime; w = w; FUN_003a7a20(act, &DAT_0050e228[0], FUN_00230110((1e9f * w) / 60.0f)); w = 0.0f;
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

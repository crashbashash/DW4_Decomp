#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/ViewerSetup.h"
#include "dw4/igViewManager.h"
#include "dw4/igVec3f.h"
#include "dw4/igDataLists.h"
#include "dw4/igViewerParameters.h"

#pragma push
#pragma readonly_strings on

#include "dw4/igViewerSceneInfoManager.h"
#include "dw4/igInsightCore.h"
#include "dw4/igView.h"
#include "dw4/igModel.h"
#include "dw4/ViewerOptions.h"
#include "dw4/StringPool.h"
#include "dw4/igViewModel.h"
#include "dw4/igReport.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igResult.h"
#include "dw4/igNamedObject.h"
#include <math.h>
extern "C" {

int FUN_002377c0(...);
int FUN_002370c0(...);

int FUN_00236ca0(int);
int FUN_002371f0(int);
int FUN_00237530(int);

int FUN_00236e80(int);
int FUN_00237280(int);
int FUN_002376b0(int);

/* The views ViewerSetup_Update reads members of the setup through: the window's slot 41, the scene-info
 * manager's quit flag (+44, +12, +180) and the logo renderer's display time (+16). */
struct Vobj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual int v41();
};
struct L4 { char pad[180]; unsigned char b180; };
struct L2 { char pad[12]; L4 *p12; };
struct L1 { char pad[44]; L2 *p44; };
struct B { char pad[16]; long long ll16; };
extern "C" void FUN_00237730(igInsightCore *);

typedef struct S2 { char pad[8]; igObject *obj; int f12; } S2;

class ViewerClock {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void setSeconds(float seconds);
};

extern int DAT_0058cd80[4];

int igViewManager_OnKeyEvent(void *arg0);
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };

igBoundingBoxesMaker *FUN_001a4830(int pool);
igAABox *FUN_001b2ed0(igBoundingBoxesMaker *maker, igNode *node);

/* The maker hands back a box that already holds one reference; the smart pointer takes its own. */
static inline void dropCreatedReference(igAABox *box) {
    box->_refCount = box->_refCount - 1;
    if ((box->_refCount & 0x7FFFFF) == 0) igObject_Destroy(box);
}
void FUN_00464170(igNode *scene, float *center, float *size, bool wholeAnimation, long long time);

typedef struct Obj { char p[80]; float f80; float f84; float f88; } Obj;
typedef struct Arg { char p[12]; Obj *o; } Arg;
typedef struct Rec { int t; int z; int v; } Rec;

int Gap__Viewer__igViewManager__vfunc_24(void *arg0);
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };

int Gap__Viewer__igViewManager__vfunc_25(void *arg0);
class DW4VC_108_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); };

typedef struct ViewModelEvent {
    int type;
    int arg;
    int data;
} ViewModelEvent;
extern int DAT_0058cd40;
extern unsigned char GPR_00554e7c;
extern unsigned char GPR_00554e80;
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int, int, float, float); };
struct O2 { char p[8]; V *o; };
class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };

igObject *FUN_00459340(int);
igObject *FUN_0045e230(int);
igObject *FUN_0045be30(int);
igObject *FUN_0045dbe0(int);

static inline void releaseString(void *p) {
    if (p != 0) {
        int *h = (int *)((char *)p - 8);
        int rc = *(int *)((char *)p - 4) - 1;
        *(int *)((char *)p - 4) = rc;
        if (rc == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
    }
}

static inline void *intern(const char *s) {
    if (s == 0) return 0;
    if (g_stringPool == 0) {
        StringPool *pool = (StringPool *)StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool = pool;
    }
    return StringPool_Intern(g_stringPool, s);
}

struct StringRef {
    void *p;
    ~StringRef() { releaseString(p); }
};

ViewerSetup::ViewerSetup(igObject *w)
    : core((InsightCore *)igInsightCore_CreateInstance(0), AdoptReference()), sceneInfo(FUN_00459340(0), AdoptReference()),
      actors(FUN_0045e230(0), AdoptReference()), dataPump(FUN_0045be30(0), AdoptReference()), showLogo(1),
      logo(FUN_0045dbe0(0), AdoptReference()), window(w, kRetainReference) {
    igObject *next = window.p;
    if (next != 0) {
        InsightCore *c = core.p;
        c->window = next;
        if (g_sharedViewerOptions == 0) {
            SharedViewerOptions *f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
            if (f != 0) f = ViewerOptions_Construct(f);
            g_sharedViewerOptions = f;
        }
        g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
        {
            SharedViewerOptions *g = g_sharedViewerOptions;
            showLogo = g->showLogo != 0 && !(g->benchmark != 0);
        }
        if (g_sharedViewerOptions != 0) {
            if (--g_sharedViewerOptions->useCount <= 0) {
                SharedViewerOptions *s1 = g_sharedViewerOptions;
                if (s1 != 0) {
                    if (&s1->internedString) releaseString((void *)s1->internedString);
                    if (s1 != 0) releaseString(s1->extraCommandLine);
                    operator delete(s1);
                }
                g_sharedViewerOptions = 0;
            }
        }
        if (showLogo) {
            StringRef scenes;
            StringRef overlays;
            scenes.p = intern("Scenes done");
            overlays.p = intern("Overlays done");
            igInsightCore_AddRendererOrder((igInsightCore *)core.p, (igObject *)scenes.p, logo.p);
            igInsightCore_AddRendererOrder((igInsightCore *)core.p, logo.p, (igObject *)overlays.p);
            igInsightCore_AddRenderer((igInsightCore *)core.p, logo.p);
        }
        igInsightCore_AddManager((igInsightCore *)core.p, sceneInfo.p);
        igInsightCore_AddManager((igInsightCore *)core.p, dataPump.p);
        igNamedObject_SetName((igNamedObject *)actors.p, "Actor manager");
        igInsightCore_AddManager((igInsightCore *)core.p, actors.p);
    }
}

ViewerSetup::~ViewerSetup() {
    if (window.p != 0) {
        igInsightCore_RemoveManager((igInsightCore *)core.p, dataPump.p);
        igInsightCore_RemoveManager((igInsightCore *)core.p, actors.p);
        igInsightCore_RemoveManager((igInsightCore *)core.p, sceneInfo.p);
        if (showLogo != 0) {
            igInsightCore_RemoveRenderer((igInsightCore *)core.p, logo.p);
        }
    }
}

void ViewerSetup_Open(ViewerSetup *setup) {
    FUN_00237530((int)setup->core.p);
    FUN_00236ca0((int)setup->core.p);
    FUN_002371f0((int)setup->core.p);
}

void ViewerSetup_Close(ViewerSetup *setup) {
    FUN_00237280((int)setup->core.p);
    FUN_00236e80((int)setup->core.p);
    FUN_002376b0((int)setup->core.p);
}

int ViewerSetup_RunFrame(ViewerSetup *setup)
{
    return FUN_002377c0((int)setup->core.p);
}

int ViewerSetup_Update(ViewerSetup *setup) {
    FUN_00237730((igInsightCore *)setup->core.p);
    if (setup->showLogo) {
        igInsightCore *t = (igInsightCore *)setup->core.p;
        long long v = t->_currentTime;
        if (v > 4000000000LL) {
            igInsightCore_RemoveRenderer(t, setup->logo.p);
            setup->showLogo = 0;
        } else {
            ((B *)setup->logo.p)->ll16 = v;
        }
    }
    int r = (((L1 *)setup->sceneInfo.p)->p44->p12->b180 != 0) ^ 1;
    if (r) {
        r = ((Vobj *)setup->window.p)->v41() != 0;
    }
    return r;
}

void ViewerSetup_ResetView(ViewerSetup *setup)
{
    igViewerSceneInfoManager_ResetView((igViewerSceneInfoManager *)setup->sceneInfo.p);
}

int ViewerSetup_ClearInfos(ViewerSetup *setup)
{
    return FUN_002370c0((int)setup->core.p);
}

igFieldSynchronizer *FUN_004509c0(int pool);
void FUN_004551f0(igFieldSynchronizer *synchronizer, igObject *model, igMetaField *field);

static inline void createSynchronizer(igSmartPointer<igFieldSynchronizer> &synchronizer, AdoptReference) {
    igRelease(synchronizer.p);
    synchronizer.p = FUN_004509c0(0);
}

/* Keeps each view-model field and the parameters' field of the same name equal. */
void igViewManager_SynchronizeParameters(igViewManager *manager, igViewerParameters *parameters) {
    igSmartPointer<igFieldSynchronizer> synchronizer;

    createSynchronizer(synchronizer, AdoptReference());
    FUN_004551f0(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_viewMatrixMetaField);
    FUN_004551f0(synchronizer, parameters, g_igViewerParameters_viewMatrixMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    FUN_004551f0(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_ratioMetaField);
    FUN_004551f0(synchronizer, parameters, g_igViewerParameters_ratioMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    FUN_004551f0(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_hfovMetaField);
    FUN_004551f0(synchronizer, parameters, g_igViewerParameters_hfovMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    FUN_004551f0(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_nearPlaneMetaField);
    FUN_004551f0(synchronizer, parameters, g_igViewerParameters_nearPlaneMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    FUN_004551f0(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_farPlaneMetaField);
    FUN_004551f0(synchronizer, parameters, g_igViewerParameters_farPlaneMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);

    createSynchronizer(synchronizer, AdoptReference());
    FUN_004551f0(synchronizer, (igObject *)manager->_viewModel, g_igViewModel_drawTimeMetaField);
    FUN_004551f0(synchronizer, parameters, g_igViewerParameters_drawTimeMetaField);
    ObjectList_AppendRetained((igObjectList *)manager->_synchronizers, synchronizer);
}

void igViewManager_SetViewMode(igViewManager *manager, igViewMode *mode) {
    S2 *arg0 = (S2 *)manager;
    igObject *arg1 = (igObject *)mode;
    igObject *temp_a0;
    igObject *temp_a0_2;

    temp_a0 = arg0->obj;
    if (temp_a0 != 0) {
        igView_SetModel((igView *)temp_a0, 0);
    }
    if (arg1 != 0) {
        arg1->_refCount = arg1->_refCount + 1;
    }
    temp_a0_2 = arg0->obj;
    if (temp_a0_2 != 0) {
        temp_a0_2->_refCount = temp_a0_2->_refCount - 1;
        if (((unsigned long long)((long long)(int)temp_a0_2->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->obj = arg1;
    if (arg1 != 0) {
        igView_SetModel((igView *)arg1, (igModel *)arg0->f12);
    }
}

void igViewManager_SetFrameTime(igViewManager *manager, long long frameTime) {
    int units = frameTime / 0x40000; ((ViewerClock *)manager->_viewMode)->setSeconds(262144.0f * (1e-9f * units));
}

void igViewMode_Update(void) {

}

void igViewManager_SetSceneUpVector(igViewManager *manager, const float *upVector) {
    int buf[3];
    void *temp_v1;

    temp_v1 = (void *)manager->_viewModel;
    *(float *)((char *)(temp_v1) + 140) = upVector[0];
    *(float *)((char *)(temp_v1) + 144) = upVector[1];
    *(float *)((char *)(temp_v1) + 148) = upVector[2];
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cd80[0];
    igModel_NotifyViews((igModel *)manager->_viewModel, (ModelChange *)buf);
}

/* Bounds at one time instead of over the whole animation. */
static inline void setMakerTime(igBoundingBoxesMaker *maker, long long time) {
    maker->_useWholeAnimation = 0;
    maker->_time = time;
}

/* The centre of `scene`'s bounding box and the length of its diagonal, over the whole animation or at `time`. */
void FUN_00464170(igNode *scene, float *center, float *size, bool wholeAnimation, long long time) {
    igSmartPointer<igBoundingBoxesMaker> maker(FUN_001a4830(0), AdoptReference());
    if (wholeAnimation) {
        maker->_useWholeAnimation = 1;
    } else {
        setMakerTime(maker, time);
    }
    igSmartPointer<igAABox> box(FUN_001b2ed0(maker, scene), kRetainReference);
    dropCreatedReference(box);
    const igAABox *bounds = box;
    float minX = bounds->_min[0];
    float maxX = bounds->_max[0];
    if (!(minX <= maxX)) {
        center[0] = 0.0f;
        center[1] = 0.0f;
        center[2] = 0.0f;
        *size = 0.0f;
    } else {
        center[0] = 0.5f * minX + 0.5f * maxX;
        center[1] = 0.5f * bounds->_min[1] + 0.5f * bounds->_max[1];
        center[2] = 0.5f * bounds->_min[2] + 0.5f * bounds->_max[2];
        float dx = box->_max[0] - box->_min[0];
        float dy = box->_max[1] - box->_min[1];
        float dz = box->_max[2] - box->_min[2];
        *size = sqrtf(dx * dx + dy * dy + dz * dz);
    }
}

int igViewManager_OnKeyEvent(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_100_0 *)(temp_a0))->vX();
    return 1;
}


/* Looks at `object` from one and a half of its sizes away, across the scene's up vector. */
void igViewManager_FrameObject(igViewManager *manager, igNode *object) {
    igVec3f center;
    float size;
    igVec3f eye;
    igVec3f up;
    ViewModelEvent event;

    center.set(0.0f, 0.0f, 0.0f);
    size = 0.0f;
    FUN_00464170(object, &center.x, &size, true, -1);
    if (size == 0.0f) {
        size = 1.0f;
    }
    size *= 1.5f;
    up.copy(((igViewModel *)manager->_viewModel)->_sceneUpVector);
    eye[0] = up[2];
    eye[1] = up[0];
    eye[2] = up[1];
    eye.scale(size);
    eye[0] += center[0];
    eye[1] += center[1];
    eye[2] += center[2];
    igMatrix44f_MakeLookAt(((igViewModel *)manager->_viewModel)->_viewMatrix, (const float *)&eye, (const float *)&center, (const float *)&up);
    event.type = 2;
    event.arg = 0;
    event.data = (int)g_igViewModel_viewMatrixMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, (ModelChange *)&event);
    igViewModel *model = (igViewModel *)manager->_viewModel;
    model->_selectedCenter[0] = center[0];
    model->_selectedCenter[1] = center[1];
    model->_selectedCenter[2] = center[2];
    ((igViewModel *)manager->_viewModel)->_selectedLength = size;
}

void igViewManager_ApplyOptions(igViewManager *manager, igObject *scene) {
    Arg *arg0 = (Arg *)manager;
    int sp60[3];
    float sp6C;
    Rec r1;
    Rec r2;
    Rec r3;
    SharedViewerOptions *s0;
    SharedViewerOptions *f;
    void *p;
    int *h;
    int rc;
    FUN_00464170((igNode *)scene, (float *)sp60, &sp6C, 1, -1);
    if (g_sharedViewerOptions == 0) {
        f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
        if (f != 0) f = ViewerOptions_Construct(f);
        g_sharedViewerOptions = f;
    }
    g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
    s0 = g_sharedViewerOptions;
    if (!(sp6C <= 0.0f) && s0->autoPlanes != 0) {
        arg0->o->f84 = sp6C / 100.0f;
        arg0->o->f88 = 3.0f * sp6C;
    } else {
        arg0->o->f84 = s0->defaultNearPlane;
        arg0->o->f88 = s0->defaultFarPlane;
    }
    r1.z = 0;
    r1.t = 2;
    r1.v = (int)g_igViewModel_nearPlaneMetaField;
    igModel_NotifyViews((igModel *)arg0->o, (ModelChange *)&r1);
    r2.t = 2;
    r2.z = 0;
    r2.v = (int)g_igViewModel_farPlaneMetaField;
    igModel_NotifyViews((igModel *)arg0->o, (ModelChange *)&r2);
    arg0->o->f80 = s0->horizontalFieldOfView;
    r3.t = 2;
    r3.z = 0;
    r3.v = (int)g_igViewModel_hfovMetaField;
    igModel_NotifyViews((igModel *)arg0->o, (ModelChange *)&r3);
    if (g_sharedViewerOptions != 0) {
        if (--g_sharedViewerOptions->useCount <= 0) {
            f = g_sharedViewerOptions;
            if (f != 0) {
                if (&f->internedString) {
                    p = (void *)f->internedString;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
                        }
                    }
                }
                if (f != 0) {
                    p = f->extraCommandLine;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
                        }
                    }
                }
                operator delete(f);
            }
            g_sharedViewerOptions = 0;
        }
    }
}

/* igViewModel's vector fields are igVec3f values (igVec3fMetaField). */
static inline const igVec3f &asVec3f(const float *v) { return *(const igVec3f *)v; }

/* Looks at the selection's centre: from the current eye, or (`resetEye`) from one and a half selection
 * lengths across the scene's up vector. */
void igViewManager_CenterSelection(igViewManager *manager, bool resetEye) {
    igVec3f center(asVec3f(((igViewModel *)manager->_viewModel)->_selectedCenter));
    igVec3f eye;
    igVec3f up;
    ViewModelEvent event;

    if (resetEye) {
        up.copy(((igViewModel *)manager->_viewModel)->_sceneUpVector);
        float distance = 1.5f * ((igViewModel *)manager->_viewModel)->_selectedLength;
        eye[0] = up[2];
        eye[1] = up[0];
        eye[2] = up[1];
        eye.scale(distance);
        eye.add(center);
        igMatrix44f_MakeLookAt(((igViewModel *)manager->_viewModel)->_viewMatrix, (const float *)&eye, (const float *)&center, (const float *)&up);
    } else {
        igViewModel *model = (igViewModel *)manager->_viewModel;
        igMatrix44f_MakeLookAt(model->_viewMatrix, model->_position, (const float *)&center, model->_viewUpVector);
    }
    event.type = 2;
    event.arg = 0;
    event.data = (int)g_igViewModel_viewMatrixMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, (ModelChange *)&event);
}

/* Moves the eye along its line to the selection's centre until the selection fills the view. */
void igViewManager_FitSelection(igViewManager *manager) {
    igVec3f center(asVec3f(((igViewModel *)manager->_viewModel)->_selectedCenter));
    igVec3f eye;
    ViewModelEvent event;

    eye.copy(((igViewModel *)manager->_viewModel)->_position);
    eye[0] -= center[0];
    eye[1] -= center[1];
    eye[2] -= center[2];
    float distance = sqrtf(eye.x * eye.x + eye.y * eye.y + eye.z * eye.z);
    if (distance == 0.0) {
        eye.copy(((igViewModel *)manager->_viewModel)->_direction);
        distance = 1.0f;
    }
    eye.scale(1.5f * ((igViewModel *)manager->_viewModel)->_selectedLength / distance);
    eye[0] += center[0];
    eye[1] += center[1];
    eye[2] += center[2];
    igViewModel *model = (igViewModel *)manager->_viewModel;
    igMatrix44f_MakeLookAt(model->_viewMatrix, (const float *)&eye, (const float *)&center, model->_viewUpVector);
    event.type = 2;
    event.arg = 0;
    event.data = (int)g_igViewModel_viewMatrixMetaField;
    igModel_NotifyViews((igModel *)manager->_viewModel, (ModelChange *)&event);
}

int Gap__Viewer__igViewManager__vfunc_24(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_104_0 *)(temp_a0))->vX();
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_25(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_108_0 *)(temp_a0))->vX();
    return 1;
}

static void FUN_00464af0(float *arg0, float *arg1, float fparg0) {
    float temp_f1;
    float temp_f1_2;

    temp_f1 = *arg0;
    if (!(temp_f1 <= fparg0)) {
        *arg0 = temp_f1 - fparg0;
    } else if (temp_f1 < -fparg0) {
        *arg0 = temp_f1 + fparg0;
    } else {
        *arg0 = 0.0f;
    }
    temp_f1_2 = *arg1;
    if (!(temp_f1_2 <= fparg0)) {
        *arg1 = temp_f1_2 - fparg0;
        return;
    }
    if (temp_f1_2 < -fparg0) {
        *arg1 = temp_f1_2 + fparg0;
        return;
    }
    *arg1 = 0.0f;
}

int Gap__Viewer__igViewManager__vfunc_26(O2 *self, int x, int y, float f0, float f1) {
    float sp1C;
    float sp18;
    sp18 = f0;
    sp1C = f1;
    FUN_00464af0(&sp18, &sp1C, 0.3f);
    self->o->vX(x, y, sp18, sp1C);
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_27(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_116_0 *)(temp_a0))->vX();
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_32(igViewManager *self, int width, int height)
{
    ViewModelEvent event;

    ((igViewModel *)self->_viewModel)->_ratio = (float)width / (float)height;
    event.type = 2;
    event.arg = 0;
    event.data = DAT_0058cd40;
    igModel_NotifyViews((igModel *)self->_viewModel, (ModelChange *)&event);
    return 0;
}

void igViewManager_PrintViewMatrix(igViewManager *self) {
    float inverse[16];
    float *m;
    int r;

    m = ((igViewModel *)self->_viewModel)->_viewMatrix;
    if (GPR_00554e7c == 0) {
        r = igReport_Info("current view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e7c = 1;
    }
    igMatrix44f_SetIdentity(inverse);
    igMatrix44f_Invert(inverse, ((igViewModel *)self->_viewModel)->_viewMatrix);
    m = inverse;
    if (GPR_00554e80 == 0) {
        r = igReport_Info("current inverse view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e80 = 1;
    }
}

void Gap__Viewer__igViewManager__vfunc_13(int *a) { igView_SetModel((igView *)a[2], (igModel *)a[3]); }

int Gap__Viewer__igViewManager__vfunc_22(void) {
    return (int)g_igViewManager_metaObject;
}

}
#pragma pop

#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
#include "dw4/igSmartPointer.h"

extern "C" {

extern int DAT_0058ca00[4];
extern int DAT_0058ca08[4];
extern int DAT_0058ca10[4];
extern int DAT_0058ca18[4];
extern int DAT_0058ca28[4];
extern int DAT_0058ca30[4];
extern int DAT_0058ca38[4];
extern int DAT_0058ca40[4];
extern int DAT_0058ca48[4];
extern int DAT_0058ca50[4];
extern int DAT_0058ca58[4];
extern int DAT_0058ca60[4];
extern int DAT_0058ca68[4];
extern int DAT_0058ca70[4];
extern int DAT_0058ca78[4];
extern int DAT_0058ca80[4];
extern int DAT_0058ca88[4];
extern int DAT_0058ca90[4];
extern int DAT_0058ca98[4];
extern int DAT_0058caa0[4];
extern int DAT_0058caa8[4];
extern int DAT_0058cab0[4];
extern int DAT_0058cab8[4];
extern int DAT_0058cac0[4];
extern int DAT_0058cac8[4];
extern int DAT_0058cad0[4];
extern int DAT_0058cad8[4];

extern int DAT_0058cae8[4];

extern int DAT_0058cb00[4];
extern int DAT_0058cb08[4];
extern int DAT_0058cb18[4];

int FUN_004601e0(...);
int FUN_00460260(...);
int FUN_004602c0(...);
int FUN_004608a0(...);
int FUN_00460ac0(...);

void FUN_004612a0(int arg0);
struct SceneSelection;
void FUN_004629c0(SceneSelection *arg0);
void FUN_00462a10(int *arg0);
void FUN_00462a20(int *arg0);
void FUN_00462a30(int *arg0);
void FUN_00462a40(int arg0);
void FUN_00462fa0(int arg0, int arg1);
struct ViewSelector;
void FUN_00462fb0(ViewSelector *self);
void FUN_00463400(int arg0);
struct ControllerMessage { int f0; int p4; int f8; int f12; };
struct ControllerLink { char p0[12]; int f12; int f16; };

typedef struct ViewerMessage { int kind; int arg; int id; } ViewerMessage;

int FUN_004578c0(...);

int Gap__Core__igObject__vfunc_11(...);

int FUN_00100610(...);
void **FUN_001007e0(...);

int FUN_001b1e50(...);

void **FUN_00238110(...);

int FUN_004573c0(...);
int FUN_004573d0(...);
int FUN_004573f0(...);
int FUN_00457e90(...);
int FUN_0045ec90(...);
int FUN_00463c90(...);

int StringChunk_ReleaseHeader(...);
void igObject_Destroy(void *);

void *memset(void *, int, unsigned int);
extern char DAT_004d1ac8[16];
extern char DAT_004d1ad8[16];
extern char DAT_004d1ae8[16];
extern char DAT_004d1af8[16];
extern char DAT_004d1b08[16];
extern char DAT_004d1b18[16];
extern char DAT_004d1b28[16];
extern char DAT_004d1b38[16];
extern char DAT_004d1b48[16];
extern char DAT_004d1b58[16];
extern char DAT_004d1b68[16];
extern char DAT_004d1b78[16];
extern char DAT_004d1b88[16];
struct Frame {
    void *f0;
    unsigned char f4;
    unsigned char f5;
    char pad6[54];
    unsigned char f60;
    char pad61[19];
    float f80;
    float f84;
    float f88;
    char pad92[122];
    unsigned char f214;
    char pad215[17];
    int f232;
    void *f236;
};

extern Frame *DAT_0056dc50[4];

void Gap__Viewer__igViewerSceneInfoManager__vfunc_13(igViewerSceneInfoManager *arg0);
/* igViewerRenderer-family objects: the shared parameters reference sits at +12 */
struct RendererLink {
    char pad[12];
    igObject *parameters;
};
#define BIND(setter, receiver, name, ...)                                                 \
    {                                                                                     \
        igObject *sp;                                                                     \
        FUN_0045ec90(&sp, arg0->_guiFactory, arg0, name);                                 \
        setter(receiver, __VA_ARGS__, sp);                                                \
        IG_OBJECT_RELEASE(sp);                                                                \
    }

typedef struct S0 { char pad12[12]; int fC; char pad24[8]; int f18; int f1C; int f20; int f24; } S0;

int igInsightCore_RemoveFromScheduler(...);
int FUN_00236f30(...);

typedef struct NodeList { char pad[8]; int f8; char pad2[4]; int *f10; } NodeList;
typedef struct NodeEntry { char pad[12]; NodeList *fc; } NodeEntry;

int igObject_IsKindOf(...);

extern int g_igParticleAttr_metaObject[4];
extern void *g_igGeometryAttr_metaObject[4];
extern int g_igDisplayListAttr_metaObject[4];

void FUN_00462d10(void *arg0);

int FUN_00464080(...);

typedef struct Obj { int w0; int references; } Obj;
typedef struct List { int pad0[2]; int count; int pad1; Obj **data; } List;
typedef struct Hold { char pad[28]; List *l28; } Hold;
typedef struct X { char pad[12]; Hold *f12; } X;
typedef struct Y { char pad[220]; List *f220; long long f224; long long f232; } Y;
typedef struct Q { int a; int b; int c; int d; } Q;
typedef struct A { char pad[20]; Y *f20; int f24; char pad2[152]; List *f180; } A;
int FUN_001c5eb0(Obj **, Hold *, int);

int FUN_00460330(...);
extern int DAT_0058c9f0[4];
extern int DAT_0058caf0[4];
extern int DAT_0058caf8[4];

#define CLEAR(src) { \
    List *l = (src); \
    int n = l->count; \
    int i; \
    int m; \
    int j; \
    Obj *o; \
    for (i = 0; i < n; i++) { \
        o = l->data[i]; \
        if (o != 0) { \
            o->references = o->references - 1; \
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->count; \
    for (j = 0; j < m; j++) { \
        l->data[j] = 0; \
    } \
    l->count = 0; }

int igGroup_AppendChild(...);
int FUN_001d65e0(...);
int FUN_001d6700(...);
int ObjectList_AppendRetainedList(...);
int igSceneInfo_GetMetaObject(...);

extern float g_vec3Zero[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern int DAT_0058c9f8[4];

struct T3 { int a; int b; int c; };

typedef struct SceneSelection { char pad12[12]; int fC; char pad44[28]; int f2C; char pad176[128]; int fB0; } SceneSelection;

int FUN_004542a0(...);
int FUN_00464110(...);
int FUN_004643a0(...);

typedef struct { int p0[3]; } ViewSyncMessage;
typedef struct { char p[12]; int f12; char q[196]; int f212; } ViewSyncParameters;
typedef struct { char p[20]; ViewSyncParameters *f20; char q[112]; int f136; } ViewSync;

int FUN_0045f930(...);

void FUN_00462cf0(igViewerSceneInfoManager *arg0);

int FUN_00464540(...);

struct S { int a; int b; int c; };

struct Y2 { char p[20]; struct YT *t; };
struct YT { char p[244]; int f244; };

struct ViewManagerLink { char pad[136]; int viewManager; };
void FUN_00464760(int, int);

void FUN_004648b0(int);

void FUN_00464c60(int);

typedef struct M { int a; int b; int c; } M;
typedef struct T { char p[208]; char f208; } T;
typedef struct S2 { char p0[20]; T *f20; char p1[28]; int f52; int f56; int f60; int pad; int f68; char p2[104]; int f176; } S2;
int FUN_00453a20(int, int);

struct Binding : igObject { char p0[68]; igObject *source; igObject *target; igObject *value; };
struct Camera : igObject { char p0[109]; char follow; char p1[18]; igObject *object; };
struct Effect : igObject { };
struct ViewSource { char p[20]; igObject *f20; char q[28]; int f52; };
struct ViewConfig { char p[16]; int *f16; };
struct ViewState : igObject { char p[204]; int f212; int f216; ViewConfig *f220; };
struct ViewSelector { char p0[12]; ViewSource *f12; int pad16; ViewState *f20; char p1[16]; int f40; igObject *f44; int f48; char p2[84]; int f136; };
struct Fetched { igObject *object; };
Binding *FUN_0045c170(int);
Camera *FUN_0045c5a0(int);
Camera *FUN_0045c8e0(int);
Effect *FUN_0045cc40(int);
Fetched FUN_0045eda0(int, int);
int igViewManager_SetViewMode(int, igObject *);
int FUN_00465260(Effect *, int);
struct Tag { };
static inline Binding *create45c170() {
    Tag tag = Tag();
    return FUN_0045c170(0);
}
static inline Camera *create45c8e0() {
    Tag tag = Tag();
    return FUN_0045c8e0(0);
}
static inline Camera *create45c5a0() {
    Tag tag = Tag();
    return FUN_0045c5a0(0);
}
static inline Effect *create45cc40() {
    Tag tag = Tag();
    return FUN_0045cc40(0);
}
static inline void takeValue(const igSmartPointer<Binding> &ref, const Fetched &fetched) {
    igObject *value = fetched.object;
    Binding *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->value;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->value = value;
    if (fetched.object != 0) {
        fetched.object->_refCount = fetched.object->_refCount - 1;
        if ((fetched.object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(fetched.object);
        }
    }
}
static inline void setSource(const igSmartPointer<Binding> &ref, igObject *value) {
    Binding *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->source;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->source = value;
}
static inline void setTarget(const igSmartPointer<Binding> &ref, igObject *value) {
    Binding *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->target;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->target = value;
}
static inline void setObject(const igSmartPointer<Camera> &ref, igObject *value) {
    Camera *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->object;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->object = value;
}

struct T2 { void f(); };
struct O { int p0, p1; T2 *t; void (T2::*pmf)(); };

extern int g_igViewerAction_metaObject[4];

extern int g_igViewerSceneInfoManager_metaObject[4];

extern int g_igViewerSceneInfoManagerController_metaObject[4];

extern int g_igViewerParameters_metaObject;

extern int g_igViewerStatisticsManager_metaObject[4];

extern int g_igStatisticsItem_metaObject[4];

int igOnOffModel_GetMetaObject(...);

void Gap__Viewer__igViewerSceneInfoManagerController__vfunc_24(struct ControllerLink *arg0, struct ControllerMessage *arg1)
{
  int a0 = arg0->f12;
  int v1;
  if (a0 == 0) return;
  v1 = arg1->f8;
  if (v1 == DAT_0058ca30[0]) return;
  if (v1 == DAT_0058ca00[0] || v1 == DAT_0058ca08[0] || v1 == DAT_0058ca10[0] || v1 == DAT_0058ca18[0]) { FUN_004601e0(arg0->f16); return; }
  if (v1 == DAT_0058ca28[0]) { FUN_00460260(arg0->f16); return; }
  if (v1 == DAT_0058ca38[0] || v1 == DAT_0058ca40[0] || v1 == DAT_0058ca48[0] || v1 == DAT_0058ca50[0]) { FUN_004602c0(arg0->f16); return; }
  if (v1 == DAT_0058ca58[0] || v1 == DAT_0058ca60[0] || v1 == DAT_0058ca68[0]) { FUN_004608a0(arg0->f16); return; }
  if (v1 == DAT_0058ca70[0] || v1 == DAT_0058ca78[0] || v1 == DAT_0058ca80[0] || v1 == DAT_0058ca88[0] || v1 == DAT_0058ca90[0] || v1 == DAT_0058ca98[0] || v1 == DAT_0058caa0[0] || v1 == DAT_0058caa8[0]) { FUN_00460ac0(arg0->f16); return; }
  if (v1 == DAT_0058cab0[0]) { FUN_00462fa0(a0, arg1->f12); return; }
  if (v1 == DAT_0058cab8[0]) { FUN_004629c0((SceneSelection *)a0); return; }
  if (v1 == DAT_0058cac0[0]) { FUN_00462a20((int *)a0); return; }
  if (v1 == DAT_0058cac8[0]) { FUN_00462a10((int *)a0); return; }
  if (v1 == DAT_0058cad0[0]) { FUN_00462a30((int *)a0); return; }
  if (v1 == DAT_0058cad8[0]) { FUN_00462fb0((ViewSelector *)a0); return; }
  if (v1 == DAT_0058cb18[0] || v1 == DAT_0058cb08[0]) { FUN_004612a0(a0); return; }
  if (v1 == DAT_0058cae8[0]) { FUN_00463400(a0); return; }
  if (arg1->f0 == 0) { FUN_00462fb0((ViewSelector *)a0); FUN_004612a0(arg0->f12); FUN_00463400(arg0->f12); return; }
  if (v1 == DAT_0058cb00[0]) { FUN_00462a40(a0); }
}

void FUN_004612a0(int arg0)
{
}

/* matching construct: 360 declaration and 120 statement orders */
void FUN_004612b0(igViewerSceneInfoManager *self) {
    ViewerMessage rising;
    ViewerMessage falling;
    ViewerMessage changed;
    int *operation;
    long long time;
    long long begin;
    long long end;
    long long length;
    igViewerParameters *parameters;
    parameters = (igViewerParameters *)self->_parameters;
    end = parameters->_endTime;
    begin = parameters->_beginTime;
    time = ((igInsightCore *)self->_insight)->_worldTime;
    length = end - begin;
    if (end != 0) {
        switch (parameters->_loopMode) {
        case 0:
            while (time > end) {
                time -= length;
            }
            while (time < begin) {
                time += length;
            }
            break;
        case 1:
            while (time > end + length) {
                time -= length * 2;
            }
            while (time < begin - length) {
                time += length * 2;
            }
            operation = &parameters->_timeOperation;
            if (*operation == 1 && time > end) {
                time = end * 2 - time;
                *operation = 2;
                rising.kind = 2;
                rising.arg = 0;
                rising.id = DAT_0058cb08[0];
                FUN_004578c0((igViewerParameters *)self->_parameters, &rising);
            }
            operation = &((igViewerParameters *)self->_parameters)->_timeOperation;
            if (*operation == 2 && time < begin) {
                time = begin * 2 - time;
                *operation = 1;
                falling.kind = 2;
                falling.arg = 0;
                falling.id = DAT_0058cb08[0];
                FUN_004578c0((igViewerParameters *)self->_parameters, &falling);
            }
            break;
        }
    }
    ((igViewerParameters *)self->_parameters)->_drawTime = time;
    changed.kind = 2;
    changed.arg = 0;
    changed.id = DAT_0058ca30[0];
    FUN_004578c0((igViewerParameters *)self->_parameters, &changed);
    ((igInsightCore *)self->_insight)->_worldTime = time;
}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_13(igViewerSceneInfoManager *arg0) {
    Gap__Core__igObject__vfunc_11(arg0);
    if (DAT_0056dc50[0] == 0) {
        void **v = FUN_001007e0(0xF0);
        if (v != 0) {
            v = FUN_00238110(v);
        }
        DAT_0056dc50[0] = (Frame *)v;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    {
        Frame *frame = DAT_0056dc50[0];
        ((igViewerParameters *)arg0->_parameters)->_showBoundingBox = frame->f4;
        ((igViewerParameters *)arg0->_parameters)->_showNormals = frame->f5;
        ((igViewerParameters *)arg0->_parameters)->_showGui = frame->f214;
        if (frame->f214 == 0) {
            arg0->_guiVisibility = 2;
        }
    }
    if (DAT_0056dc50[0] != 0) {
        int rc = DAT_0056dc50[0]->f232 - 1;
        DAT_0056dc50[0]->f232 = rc;
        if (rc <= 0) {
            Frame *f = DAT_0056dc50[0];
            if (f != 0) {
                if (&f->f236) {
                    void *p = f->f236;
                    if (p != 0) {
                        int *h = (int *)((char *)p - 8);
                        int r = *(int *)((char *)p - 4) - 1;
                        *(int *)((char *)p - 4) = r;
                        if (r == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (f != 0) {
                    void *p = f->f0;
                    if (p != 0) {
                        int *h = (int *)((char *)p - 8);
                        int r = *(int *)((char *)p - 4) - 1;
                        *(int *)((char *)p - 4) = r;
                        if (r == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                FUN_00100610(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
    FUN_00463c90(arg0->_viewManager, arg0->_parameters);
    {
        igObject *s2 = (igObject *)arg0->_parameters;
        RendererLink *s1 = (RendererLink *)arg0->_viewerRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)arg0->_parameters;
        RendererLink *s1 = (RendererLink *)arg0->_bboxRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    {
        igObject *s2 = (igObject *)arg0->_parameters;
        RendererLink *s1 = (RendererLink *)arg0->_normalsRenderer;
        if (s2 != 0) {
            s2->_refCount = (int)s2->_refCount + 1;
        }
        igObject *a0 = s1->parameters;
        IG_OBJECT_RELEASE(a0);
        s1->parameters = s2;
    }
    *(int *)((char *)arg0->_applicationController + 16) = arg0->_viewerRenderer;
    *(igViewerSceneInfoManager **)((char *)arg0->_applicationController + 12) = arg0;
    FUN_00457e90(arg0->_applicationController, arg0->_parameters);
    FUN_001b1e50(((igViewerParameters *)arg0->_parameters)->_disables, 0xC);
    {
        int *list = (int *)((igViewerParameters *)arg0->_parameters)->_disables;
        memset((void *)list[4], 0, list[2] * 4);
    }
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1ac8, 0x46)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1ad8, 0x44)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1ae8, 0x43, 0xF)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1af8, 0x48, 0xC)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b08, 3)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b18, 0)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1b28, 0x4D)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1b38, 0x57)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1b48, 0x52, 0xA)
    BIND(FUN_004573f0, arg0->_hotKeyReceiver, DAT_004d1b58, 0x54, 0xB)
    BIND(FUN_004573c0, arg0->_hotKeyReceiver, DAT_004d1b68, 0x50)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b78, 1)
    BIND(FUN_004573d0, arg0->_hotKeyReceiver, DAT_004d1b88, 2)
}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_24(S0 *arg0) {
    FUN_00236f30(arg0->fC, *(int *)((char *)(*(int *)((char *)(arg0) + 44)) + 8));
    FUN_00236f30(arg0->fC, arg0->f1C);
    FUN_00236f30(arg0->fC, arg0->f20);
    FUN_00236f30(arg0->fC, arg0->f18);
    FUN_00236f30(arg0->fC, arg0->f24);
    igInsightCore_RemoveFromScheduler(arg0->fC, arg0);
}

int FUN_00462100(NodeEntry *arg0) {
    int i;
    int n;
    int off;

    if (arg0 == 0) {
        return 0;
    }
    if (igObject_IsKindOf(arg0, g_igGeometryAttr_metaObject[0]) != 0) {
        return 1;
    }
    if (igObject_IsKindOf(arg0, g_igParticleAttr_metaObject[0]) != 0) {
        return 1;
    }
    if (igObject_IsKindOf(arg0, g_igDisplayListAttr_metaObject[0]) != 0) {
        n = arg0->fc->f8;
        i = 0;
        if (0 < n) {
            off = 0;
            do {
                if (!!FUN_00462100(*(NodeEntry **)((char *)arg0->fc->f10 + off))) {
                    return 1;
                }
                i += 1;
                off += 4;
            } while (i < n);
        }
    }
    return 0;
}

void FUN_00462200(void *arg0) {
    if (FUN_00462100(*(NodeEntry **)((char *)(*(int *)((char *)(arg0) + 24)) + 84)) == 0) {
        FUN_00462d10(arg0);
    }
}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_29(igViewerSceneInfoManager *arg0) {
    long long temp_s0;
    igInsightCore *temp_v0;

    FUN_004612b0(arg0);
    temp_v0 = (igInsightCore *)arg0->_insight;
    temp_s0 = temp_v0->_frameTime;
    if (arg0->_clippingCheckFrame == temp_v0->_frames) {
        FUN_00462200(arg0);
    }
    FUN_00464080(arg0->_viewManager, temp_s0);
}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_28(A *arg0) {
    Hold *s2;
    int s0;
    Obj *spAC;
    Obj *t;
    Q q1, q2, q3, q4;
    s2 = (Hold *)((X *)arg0->f20)->f12;
    s0 = (s2->l28 != 0 ? s2->l28->count : 0) - 1;
    while (s0 >= 0) {
        FUN_001c5eb0((Obj **)&spAC, s2, s0);
        t = spAC;
        if (t != 0) {
            t->references = t->references - 1;
            t = spAC;
            if (((unsigned long long)((long long)t->references << 0x29) >> 0x29) == 0) igObject_Destroy(t);
        }
        s0 -= 1;
    }
    q1.b = 0;
    q1.a = 2;
    q1.c = DAT_0058c9f0[0];
    FUN_004578c0(arg0->f20, &q1);
    FUN_00460330(arg0->f24);
    CLEAR(arg0->f20->f220)
    q2.a = 2;
    q2.b = 0;
    q2.c = DAT_0058cae8[0];
    FUN_004578c0(arg0->f20, &q2);
    arg0->f20->f224 = 0;
    q3.a = 2;
    q3.b = 0;
    q3.c = DAT_0058caf0[0];
    FUN_004578c0(arg0->f20, &q3);
    arg0->f20->f232 = 0;
    q4.a = 2;
    q4.b = 0;
    q4.c = DAT_0058caf8[0];
    FUN_004578c0(arg0->f20, &q4);
    CLEAR(arg0->f180)
}

int Gap__Viewer__igViewerSceneInfoManager__vfunc_27(igViewerSceneInfoManager *arg0, igSceneInfo *arg1) {
    T3 t0, t1, t2, t3, t4;
    Frame *s0;
    bool b;
    bool a;
    if (igObject_IsKindOf(arg1, igSceneInfo_GetMetaObject()) != 0) {
        if (arg1->_sceneGraph == 0) {
            return 0;
        }
        if (DAT_0056dc50[0] == 0) {
            void **v = FUN_001007e0(0xF0);
            if (v != 0) {
                v = FUN_00238110(v);
            }
            DAT_0056dc50[0] = (Frame *)v;
        }
        DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
        s0 = DAT_0056dc50[0];
        if (arg1 != 0 && arg1->_animationBegin == 0 && arg1->_animationEnd == 0) {
            FUN_001d6700(arg1);
        }
        if (arg1->_cameras == 0) {
            FUN_001d65e0(arg1);
        }
        igGroup_AppendChild(((igViewerParameters *)arg0->_parameters)->_scene, arg1->_sceneGraph);
        t0.a = 2;
        t0.b = 0;
        t0.c = DAT_0058c9f0[0];
        FUN_004578c0(arg0->_parameters, &t0);
        FUN_00460330(arg0->_viewerRenderer);
        b = false;
        float f2 = s0->f80;
        a = false;
        if (!(f2 != g_vec3Zero[0])) { if (!(s0->f84 != DAT_004e105c[0])) { a = true; } }
        if (a && s0->f88 == DAT_004e1060[0]) {
            b = true;
        }
        if (b) {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            *(float *)&o->_upVector[0] = *(float *)&arg1->_upVector[0];
            *(float *)&o->_upVector[1] = *(float *)&arg1->_upVector[1];
            *(float *)&o->_upVector[2] = *(float *)&arg1->_upVector[2];
        } else {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            *(float *)&o->_upVector[0] = f2;
            *(float *)&o->_upVector[1] = s0->f84;
            *(float *)&o->_upVector[2] = s0->f88;
        }
        t1.a = 2;
        t1.b = 0;
        t1.c = DAT_0058c9f8[0];
        FUN_004578c0(arg0->_parameters, &t1);
        ObjectList_AppendRetainedList(((igViewerParameters *)arg0->_parameters)->_cameras, arg1->_cameras);
        t2.a = 2;
        t2.b = 0;
        t2.c = DAT_0058cae8[0];
        FUN_004578c0(arg0->_parameters, &t2);
        {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            long long *q = &o->_beginTime;
            if (o->_beginTime == 0) {
                *q = arg1->_animationBegin;
            }
        }
        t3.a = 2;
        t3.b = 0;
        t3.c = DAT_0058caf0[0];
        FUN_004578c0(arg0->_parameters, &t3);
        {
            igViewerParameters *o = (igViewerParameters *)arg0->_parameters;
            long long *q = &o->_endTime;
            if (o->_endTime == 0) {
                *q = arg1->_animationEnd;
            }
        }
        t4.a = 2;
        t4.b = 0;
        t4.c = DAT_0058caf8[0];
        FUN_004578c0(arg0->_parameters, &t4);
        if (DAT_0056dc50[0] != 0) {
            int rc = DAT_0056dc50[0]->f232 - 1;
            DAT_0056dc50[0]->f232 = rc;
            if (rc <= 0) {
                Frame *f = DAT_0056dc50[0];
                if (f != 0) {
                    if (&f->f236) {
                        void *p = f->f236;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    if (f != 0) {
                        void *p = f->f0;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    FUN_00100610(f);
                }
                DAT_0056dc50[0] = 0;
            }
        }
        return 1;
    }
    return 0;
}

void FUN_004629c0(SceneSelection *arg0) {
    void *temp_a0;

    temp_a0 = (void *)(arg0->fC);
    if (temp_a0 != 0) {
        FUN_00236f30(temp_a0, *(int *)((char *)(*(int *)((char *)(arg0) + 44)) + 8));
        FUN_004542a0(*(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 32), arg0->f2C);
        arg0->fB0 = 2;
    }
}

void FUN_00462a10(int *arg0) {
    FUN_00236f30(arg0[3], arg0[8]);
}

void FUN_00462a20(int *arg0) {
    FUN_00236f30(arg0[3], arg0[7]);
}

void FUN_00462a30(int *arg0) {
    FUN_00236f30(arg0[3], arg0[9]);
}

void FUN_00462a40(int arg0)
{
}

void FUN_00462a50(ViewSync *arg0) {
    int buf[3];
    arg0->f20->f212 = 1;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cad8[0];
    FUN_004578c0(arg0->f20, buf, 1);
    FUN_00464110(arg0->f136, (int)arg0->f20 + 0x10);
    FUN_004643a0(arg0->f136, arg0->f20->f12);
}

void FUN_00462ac0(igViewerSceneInfoManager *arg0) {
    int sp50[3];
    int sp40[3];
    int sp30[3];
    Frame *f;
    Frame *g;
    Frame *s0;
    igViewerParameters *v;
    igObject *a;
    int *pp;
    void *p;
    int *h;
    int rc;
    FUN_00462a50((ViewSync *)arg0);
    FUN_00464540(arg0->_viewManager, ((igViewerParameters *)arg0->_parameters)->_scene);
    FUN_00462cf0(arg0);
    FUN_0045f930(arg0->_viewerRenderer);
    v = (igViewerParameters *)arg0->_parameters;
    pp = &v->_selectedObject;
    a = (igObject *)*pp;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    *pp = 0;
    sp50[0] = 2;
    sp50[1] = 0;
    sp50[2] = DAT_0058cb00[0];
    FUN_004578c0(arg0->_parameters, sp50);
    ((igViewerParameters *)arg0->_parameters)->_timeOperation = 1;
    sp40[0] = 2;
    sp40[1] = 0;
    sp40[2] = DAT_0058cb08[0];
    FUN_004578c0(arg0->_parameters, sp40);
    if (DAT_0056dc50[0] == 0) {
        f = (Frame *)FUN_001007e0(240);
        if (f != 0) f = (Frame *)FUN_00238110(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    v = (igViewerParameters *)arg0->_parameters;
    g = DAT_0056dc50[0];
    if (((igObjectList *)v->_cameras)->_count > 0 && g->f60 != 0) {
        v->_operationMode = v->_firstCameraMode;
    } else {
        v->_operationMode = 1;
    }
    sp30[1] = 0;
    sp30[0] = 2;
    sp30[2] = DAT_0058cad8[0];
    FUN_004578c0(arg0->_parameters, sp30);
    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->f232 <= 0) {
            f = DAT_0056dc50[0];
            if (f != 0) {
                if (&f->f236) {
                    p = f->f236;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (f != 0) {
                    p = f->f0;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                FUN_00100610(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
}

void FUN_00462cf0(igViewerSceneInfoManager *arg0)
{
}

void FUN_00462d00(void *arg0)
{
}

void FUN_00462d10(void *arg0)
{
}

void igViewerSceneInfoManager_DebugZoomOut(void)
{
}

void FUN_00462d30(void *arg0) {
    struct S s;
    *(int *)((char *)(*(int *)((char *)(arg0) + 20)) + 244) = 1;
    s.a = 2;
    s.b = 0;
    s.c = DAT_0058cb08[0];
    FUN_004578c0(*(void **)((char *)(arg0) + 20), &s);
}

void FUN_00462d80(struct Y2 *arg0) {
    int buf[3];

    arg0->t->f244 = 0;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cb08[0];
    FUN_004578c0(arg0->t, buf);
}

void igViewerSceneInfoManager_ResetOperationMode(void *arg0) {
    int buf[3];

    *(int *)((char *)(*(int *)((char *)(arg0) + 20)) + 212) = 1;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cad8[0];
    FUN_004578c0(*(int *)((char *)(arg0) + 20), buf, 1);
}

void FUN_00462e10(void *arg0)
{
}

void FUN_00462e20(void *arg0)
{
}

void FUN_00462e30(void *arg0)
{
}

void FUN_00462e40(void *arg0)
{
}

void FUN_00462e50(void *arg0)
{
}

void FUN_00462e60(struct ViewManagerLink *arg0) {
    FUN_00464760(arg0->viewManager, 0);
}

void FUN_00462e70(struct ViewManagerLink *arg0) {
    FUN_004648b0(arg0->viewManager);
}

void FUN_00462e80(struct ViewManagerLink *arg0) {
    FUN_00464c60(arg0->viewManager);
}

void FUN_00462e90(S2 *arg0) {
    switch (arg0->f176) {
    case 0: {
        M m;
        arg0->f20->f208 = 0;
        m.a = 2;
        m.b = 0;
        m.c = DAT_0058cab8[0];
        FUN_004578c0(arg0->f20, &m);
        break;
    }
    case 1: {
        M m;
        FUN_00453a20(arg0->f52, arg0->f60);
        FUN_00453a20(arg0->f52, arg0->f68);
        FUN_00453a20(arg0->f52, arg0->f56);
        arg0->f20->f208 = 0;
        m.a = 2;
        m.b = 0;
        m.c = DAT_0058cab8[0];
        FUN_004578c0(arg0->f20, &m);
        break;
    }
    case 2: {
        M m;
        arg0->f20->f208 = 1;
        m.a = 2;
        m.b = 0;
        m.c = DAT_0058cab8[0];
        FUN_004578c0(arg0->f20, &m);
        FUN_00462e50(arg0);
        break;
    }
    }
}

void FUN_00462fa0(int arg0, int arg1)
{
}

extern "C" void FUN_00462fb0(ViewSelector *self) {
    ViewState *s = self->f20;
    int mode = s->f212;
    switch (mode) {
    case 0: {
        igSmartPointer<Binding> binding(create45c170());
        takeValue(binding, FUN_0045eda0(self->f48, 1));
        setSource(binding, self->f20);
        setTarget(binding, self->f44);
        igViewManager_SetViewMode(self->f136, binding.p);
        break;
    }
    case 2: {
        igSmartPointer<Camera> camera(create45c8e0());
        setObject(camera, self->f12->f20);
        igViewManager_SetViewMode(self->f136, camera.p);
        break;
    }
    case 1: {
        igSmartPointer<Camera> camera(create45c5a0());
        igViewManager_SetViewMode(self->f136, camera.p);
        break;
    }
    case 3: {
        igSmartPointer<Camera> camera(create45c5a0());
        camera.p->follow = 1;
        igViewManager_SetViewMode(self->f136, camera.p);
        break;
    }
    default: {
        int first = s->f216;
        if (mode >= first) {
                first = mode - first;
            igSmartPointer<Effect> effect(create45cc40());
            FUN_00465260(effect.p, self->f20->f220->f16[first]);
            igViewManager_SetViewMode(self->f136, effect.p);
            self->f40 = self->f12->f52 + 1;
        }
        break;
    }
    }
}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_25(void) {

}

void Gap__Viewer__igViewerSceneInfoManager__vfunc_26(void) {

}

void FUN_004633f0(void)
{
}

void FUN_00463400(int arg0)
{
}

extern "C" void Gap__Viewer__igViewerAction__vfunc_23(O *o) {
    void (T2::*m)() = o->pmf;
    (o->t->*m)();
}

int Gap__Viewer__igViewerAction__vfunc_22(void) {
    return g_igViewerAction_metaObject[0];
}

int Gap__Viewer__igViewerSceneInfoManager__vfunc_22(void) {
    return g_igViewerSceneInfoManager_metaObject[0];
}

int Gap__Viewer__igViewerSceneInfoManagerController__vfunc_22(void) {
    return g_igViewerSceneInfoManagerController_metaObject[0];
}

void Gap__Viewer__igViewerSceneInfoManagerController__vfunc_23(int arg0, int arg1) {
    igObject_IsKindOf(arg1, g_igViewerParameters_metaObject);
}

void Gap__Viewer__igStatisticsItem__vfunc_24(void) {

}

void Gap__Viewer__igViewerStatisticsManager__vfunc_03(void) {

}

void Gap__Viewer__igViewerStatisticsManager__vfunc_04(void) {

}

float Gap__Viewer__igViewerStatisticsManager__vfunc_23(void) {
    return 0.0f;
}

float Gap__Viewer__igViewerStatisticsManager__vfunc_25(void) {
    return -1.0f;
}

void Gap__Viewer__igViewerStatisticsManager__vfunc_27(void) {

}

float Gap__Viewer__igViewerStatisticsManager__vfunc_24(void) {
    return 0.0f;
}

float Gap__Viewer__igViewerStatisticsManager__vfunc_26(void) {
    return -1.0f;
}

int Gap__Viewer__igViewerStatisticsManager__vfunc_22(void) {
    return g_igViewerStatisticsManager_metaObject[0];
}

int Gap__Viewer__igStatisticsItem__vfunc_22(void) {
    return g_igStatisticsItem_metaObject[0];
}

void Gap__Viewer__igStatisticsItem__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igOnOffModel_GetMetaObject());
}

}

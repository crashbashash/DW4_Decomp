#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" {

int igObject_IsKindOf(...);

extern int g_igViewModel_metaObject[4];

class C;
void FUN_004650a0(void *arg0);
struct Ob;
void FUN_004650d0(Ob *arg0);
struct CameraTargetLink;
void FUN_004651e0(struct CameraTargetLink *arg0);
extern int DAT_0058cd38[4];
extern int DAT_0058cd60[4];
extern int DAT_0058cd68[4];
extern int DAT_0058cd70[4];
void Gap__Bec__beCameraMode__vfunc_22(C *arg0, int *arg1);
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v124(); virtual void v128(); };

int FUN_00191f30(...);
int Vec3f_TransformDirection(...);
int igModel_NotifyViews(...);
int Matrix44_GetTranslation(...);

extern int g_vec3XAxis[4];
extern int g_vec3ZAxis[4];
extern int DAT_0058cd78[4];
typedef struct Ev { int id; void *obj; int data; } Ev;
typedef struct Tg { char pad[92]; float f92; float f96; float f100; float f104; float f108; float f112; } Tg;
typedef struct Mx { float m[16]; } Mx;
typedef struct Ob { char pad[8]; Tg *f8; Mx mat; } Ob;

int FUN_00191b10(...);

struct CameraTarget { char pad[92]; float f92; float f96; float f100; float f104; float f108; float f112; };
struct CameraTargetLink { char pad[8]; struct CameraTarget *f8; };

struct R { int w0; int references; };
struct O { char pad[76]; struct R *f76; struct R *f80; };

struct R* igGraphPath_GetTail(...);
void igObject_Destroy(void *);

extern int DAT_00561EA0[4];
static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00561EA0[0]) != 0) { return o; } return 0; }

void FUN_00465380(void *arg0);
class DW4VC_144_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int vX(); };

extern int DAT_0058cd48[4];
extern int DAT_0058cd50[4];
extern int DAT_0058cd58[4];
void FUN_004653c0(igCameraMode *arg0);
class DW4VC_140_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(); };

typedef struct ViewerMatrix { float m[16]; } ViewerMatrix;
typedef struct ViewerVector4 { float v[4]; } ViewerVector4;
typedef struct ViewerPickView { char pad[8]; struct ViewerPickTarget *f8; char pad2[64]; int f76; int f80; } ViewerPickView;
typedef struct ViewerPickTarget { char pad[12]; float f12; char p2[136]; long long f152; } ViewerPickTarget;
int igMatrix44f_SetIdentity(ViewerMatrix *);
int FUN_00190ed0(ViewerMatrix *, float, float, float);
int FUN_00191230(ViewerMatrix *, float *, float *, float *);
int FUN_00191e30(void *, void *, ViewerMatrix *);
int FUN_001c5b30(int, ViewerMatrix *, long long);
int Matrix44_SetTranslation(ViewerMatrix *, ViewerVector4 *);

typedef struct Ctl { char pad[76]; float a; float b; float c; char pad2[40]; float scale; unsigned char flag; } Ctl;
void FUN_004658c0(void *arg0);

typedef struct ViewerInput {
    char pad0[84];
    float zoom;
    char pad88[44];
    unsigned char toggled;
} ViewerInput;

typedef struct ViewerAxisState {
    char pad0[88];
    float f88;
    float f92;
    float f96;
    float f100;
    float f104;
} ViewerAxisState;

int FUN_004658d0(...);

int FUN_00465a40(char *, float);

int FUN_00465b90(...);

extern float sqrtf(float);
struct OrbitTarget { char pad[92]; float x; float y; float z; char pad104[56]; float tx; float ty; float tz; };
struct Orbit {
    char pad[8];
    struct OrbitTarget *target;
    char pad12[96];
    int f108; int f112; int f116; int f120; int f124;
    float distance;
    unsigned char f132;
    char pad133[15];
    int f148; int f152;
    unsigned char f156;
};

struct S465dc0 { char pad[132]; unsigned char f; };

typedef struct ViewerCameraTarget {
    char pad0[76];
    float aspect;
    char pad80[12];
    float f92;
    float f96;
    float f100;
    char pad104[56];
    float f160;
    float f164;
    float f168;
} ViewerCameraTarget;
typedef struct ViewerCameraState {
    char pad0[8];
    ViewerCameraTarget *target;
    char pad12[64];
    float distance;
    char pad80[8];
    unsigned char primaryButton;
    unsigned char secondaryButton;
    unsigned char tertiaryButton;
    char pad91[17];
    unsigned char f108;
    char pad109[3];
    int f112;
    unsigned char f116;
    unsigned char f117;
    char pad118[2];
    float yaw;
    float roll;
    float pitch;
    float zoom;
    float pan[3];
} ViewerCameraState;
static inline void setVec3(float *v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
static inline void scaleVec3(float *v, float s) {
    v[0] = v[0] * s;
    v[1] = v[1] * s;
    v[2] = v[2] * s;
}

struct S { char pad[92]; float f92; float f96; float f100; float f104; };

extern const float g_vec3Zero[4];
extern const float g_vec2Zero[2];
extern int g_igGuiSystemModelMousePositionField[4];
/* What igModel_NotifyViews tells a model's views: type 2 is a changed field, sent by `sender`. */
typedef struct ViewModelEvent { int type; int sender; int field; } ViewModelEvent;
enum { VIEW_MODEL_FIELD_CHANGED = 2 };

struct PickRecord;
struct Hit;
void FUN_00466a10(PickRecord *record, Hit *hit);

extern igPickMode *DAT_0058d240[4];

typedef struct R2 { int w0; int refs; } R2;
struct Y { char pad[240]; R2 *obj; };
struct X { char pad[76]; struct Y *y; };
struct Msg { int a; int b; int c; };
void FUN_00466b20(igPickMode *arg0);
extern int DAT_0058cb00[4];

int FUN_004569c0(int, unsigned char);
int FUN_00456a60(...);

int List_Resize(...);
int ObjectList_AppendRetained(...);
igProbe *FUN_0019e680(int);
static inline int count_of(const igIntList *list) { return list->_count; }
static inline void setProbe(igPickMode *pickMode, const igSmartPointer<igProbe> &probe) {
    igObject *retained = (igObject *)probe.get();
    igIntersectTraversal *traversal = (igIntersectTraversal *)pickMode->_intersectTraversal;
    igObject *previous;
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    previous = (igObject *)traversal->_probe;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    traversal->_probe = (int)retained;
}

struct S80 { char pad[80]; int f80; char pad2[4]; int f88; unsigned char f92; };

struct Marker : public igObject { };
struct Hit { char pad8[8]; int object; char pad12[8]; float distance; };
struct PickRecord { char pad[104]; float nearest; unsigned char found; char p109[3]; Marker *marker; };
Marker *FUN_0019f630(int);
int FUN_001c5790(Marker *, int);
static inline void setMarker(PickRecord *record, const igSmartPointer<Marker> &marker) {
    Marker *held = marker.get();
    Marker *previous;
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    previous = record->marker;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    record->marker = held;
}
static inline Marker *createMarker() { AdoptReference tag = AdoptReference(); return FUN_0019f630(0); }

int FUN_0018d2b0(...);
int FUN_0018d360(...);
int Vec3f_TransformProjective(...);
int FUN_001ce970(...);
/* matching construct: dummy virtual slots so v23()/v25() dispatch through the retail vtable offsets (igIntersectTraversal) */
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void v23(int); virtual void d24(); virtual void v25(long long); };

extern int g_igPickMode_metaObject[4];

extern int g_igRotateMode_metaObject[4];

extern int g_igFlyMode_metaObject[4];

extern int g_igCameraMode_metaObject[4];

extern int g_igViewMode_metaObject[4];

void Gap__Bec__beCameraMode__vfunc_21(int arg0, int arg1) {
    igObject_IsKindOf(arg1, g_igViewModel_metaObject[0]);
}

void Gap__Bec__beCameraMode__vfunc_22(C *arg0, int *arg1) {
    int t = arg1[2];
    int k;
    if (t == DAT_0058cd38[0]) { FUN_004650a0(arg0); FUN_004650d0((Ob *)arg0); return; }
    if (t == DAT_0058cd60[0] || t == DAT_0058cd68[0] || t == DAT_0058cd70[0]) { FUN_004651e0((CameraTargetLink *)arg0); return; }
    k = arg1[0];
    if (k == 0) { FUN_004650a0(arg0); FUN_004650d0((Ob *)arg0); arg0->v124(); }
    else if (k == 1) { arg0->v128(); }
}

void FUN_00465080(void) {

}

void FUN_00465090(void) {

}

void FUN_004650a0(void *arg0) {
    int sp1C;

    FUN_00191f30(&sp1C, (char *)arg0 + 0xC, *(int *)((char *)(arg0) + 8) + 0xC);
}

void FUN_004650d0(Ob *arg0) {
    float v[3];
    Ev e1;
    Ev e2;
    Ev e3;
    Tg *temp_s0;

    temp_s0 = arg0->f8;
    Matrix44_GetTranslation(&arg0->mat, v);
    temp_s0->f92 = v[0];
    temp_s0->f96 = v[1];
    temp_s0->f100 = v[2];
    e1.id = 2;
    e1.obj = arg0;
    e1.data = DAT_0058cd60[0];
    igModel_NotifyViews(temp_s0, &e1);
    Vec3f_TransformDirection((char *)temp_s0 + 0x68, &g_vec3ZAxis[0], &arg0->mat);
    temp_s0->f104 = -temp_s0->f104;
    temp_s0->f108 = -temp_s0->f108;
    temp_s0->f112 = -temp_s0->f112;
    e2.id = 2;
    e2.obj = arg0;
    e2.data = DAT_0058cd68[0];
    igModel_NotifyViews(temp_s0, &e2);
    Vec3f_TransformDirection((char *)temp_s0 + 0x80, &g_vec3XAxis[0], &arg0->mat);
    e3.id = 2;
    e3.obj = arg0;
    e3.data = DAT_0058cd78[0];
    igModel_NotifyViews(temp_s0, &e3);
}

void FUN_004651e0(struct CameraTargetLink *arg0) {
    float v[3];
    struct CameraTarget *t;

    t = arg0->f8;
    v[0] = t->f92;
    v[1] = t->f96;
    v[2] = t->f100;
    v[0] = v[0] + t->f104;
    v[1] += t->f108;
    v[2] += t->f112;
    FUN_00191b10((char *)t + 0xC, (char *)t + 0x5C, v, (char *)t + 0x74, t);
}

void FUN_00465260(struct O *self, struct R *arg1) {
    struct R *o;
    struct R *v;
    if (arg1 != 0) {
        if (arg1 != 0) {
            arg1->references = arg1->references + 1;
        }
        o = self->f76;
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        self->f76 = arg1;
        v = igGraphPath_GetTail(arg1);
        v = (struct R *)cast0(v);
        if (v != 0) {
            v->references = v->references + 1;
        }
        o = self->f80;
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        self->f80 = v;
    }
}

void FUN_00465380(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 80));
    if (temp_a0 != 0) {
        ((DW4VC_144_0 *)(temp_a0))->vX();
    }
}

void FUN_004653c0(igCameraMode *arg0) {
    int spA[4];
    int spB[4];
    int spC[4];
    float temp_f21;
    float var_f20;
    igCamera *temp_v1;
    igViewModel *temp_s0;

    if (arg0->_camera != 0) {
        ((DW4VC_140_0 *)arg0->_camera)->vX();
        temp_s0 = (igViewModel *)arg0->_model;
        temp_v1 = (igCamera *)arg0->_camera;
        temp_f21 = temp_v1->_farPlane;
        var_f20 = temp_v1->_nearPlane;
        temp_s0->_hfov = (float) temp_v1->_horizontalFieldOfView;
        spA[0] = 2;
        spA[1] = 0;
        spA[2] = DAT_0058cd48[0];
        igModel_NotifyViews(temp_s0, spA);
        temp_s0->_farPlane = temp_f21;
        spB[0] = 2;
        spB[1] = 0;
        spB[2] = DAT_0058cd58[0];
        igModel_NotifyViews(temp_s0, spB);
        var_f20 = (var_f20 == 0.0f) ? temp_f21 / 1000.0f : var_f20;
        temp_s0->_nearPlane = var_f20;
        spC[0] = 2;
        spC[1] = 0;
        spC[2] = DAT_0058cd50[0];
        igModel_NotifyViews(temp_s0, spC);
    }
}

void FUN_004654d0(ViewerPickView *arg0) {
    float a, b, c;
    int sp90;
    ViewerVector4 sp80;
    ViewerMatrix sp40;
    int sp30[4];
    ViewerPickTarget *d;
    if (arg0->f80 != 0) {
        igMatrix44f_SetIdentity(&sp40);
        d = arg0->f8;
        FUN_001c5b30(arg0->f76, &sp40, d->f152);
        a = 0; b = 0; c = 0;
        FUN_00191230(&sp40, &a, &b, &c);
        Matrix44_GetTranslation(&sp40, &sp80);
        FUN_00190ed0(&sp40, a, b, c);
        Matrix44_SetTranslation(&sp40, &sp80);
        FUN_00191e30(&sp90, (char *)d + 12, &sp40);
        sp30[0] = 2;
        sp30[1] = 0;
        sp30[2] = DAT_0058cd38[0];
        igModel_NotifyViews(d, sp30);
    }
}

void FUN_004655a0(Ctl *s, int key, int down) {
    float f;
    switch (key) {
    case 0x9C:
        if (down) s->scale *= 1.5f;
        break;    case 0x9D:
        if (down) s->scale /= 1.5f;
        break;
    case 0x98:
        if (down) f = 1.0f; else f = -1.0f;
        s->c += f;
        break;
    case 0x92:
        if (down) f = 1.0f; else f = -1.0f;
        s->c -= f;
        break;
    case 0x88:
        if (down) f = 1.0f; else f = -1.0f;
        s->b -= f;
        break;
    case 0x89:
        if (down) f = 1.0f; else f = -1.0f;
        s->b += f;
        break;
    case 0x94:
        if (down) f = 1.0f; else f = -1.0f;
        s->a += f;
        break;
    case 0x96:
        if (down) f = 1.0f; else f = -1.0f;
        s->a -= f;
        break;
    case 0x5A:
        if (down) s->flag = !s->flag;
        FUN_004658c0(s);
        break;
    }
}

void FUN_004657b0(ViewerInput *self, int button, int pressed) {
    switch (button) {
    case 0:
        self->zoom += pressed ? 1.0f : -1.0f;
        break;
    case 1:
        self->zoom -= pressed ? 1.0f : -1.0f;
        break;
    case 2:
        if (pressed) {
            self->toggled = !self->toggled;
            FUN_004658c0(self);
        }
        break;
    }
}

void FUN_00465870(void *arg0, float fparg0, float fparg1) {
    *(float *)((char *)(arg0) + 140) = fparg0;
    *(float *)((char *)(arg0) + 144) = fparg1;
}

void FUN_00465880(ViewerAxisState *s, int unused, unsigned short axis, float x, float y)
{
    if (axis == 0) {
        s->f100 = x;
        s->f104 = y;
    } else if (axis == 1) {
        s->f88 = -x;
        s->f92 = 0.0f;
        s->f96 = y;
    }
}

void FUN_004658c0(void *arg0)
{
}

void FUN_00465cc0(char *arg0, float fparg0) {
    int sp[3];
    int temp_s0;

    temp_s0 = *(int *)(arg0 + 8);
    FUN_004658d0(arg0);
    if (*(unsigned char *)(arg0 + 132) != 0) {
        FUN_00465b90(arg0);
    }
    FUN_00465a40(arg0, fparg0);
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = DAT_0058cd38[0];
    igModel_NotifyViews(temp_s0, sp);
}

void FUN_00465d40(struct Orbit *arg0) {
    struct OrbitTarget *t;
    float dx;
    float dy;
    float dz;
    arg0->f132 = 0;
    arg0->f148 = 0;
    arg0->f152 = 0;
    arg0->f108 = 0;
    arg0->f112 = 0;
    arg0->f116 = 0;
    arg0->f120 = 0;
    arg0->f124 = 0;
    arg0->f156 = 0;
    t = arg0->target;
    dx = t->tx;
    dy = t->ty;
    dz = t->tz;
    dx -= t->x;
    dy -= t->y;
    dz -= t->z;
    arg0->distance = 0.2f * sqrtf(dx * dx + dy * dy + dz * dz);
}

void FUN_00465dc0(struct S465dc0 *arg0) {
    if (arg0->f != 0) {
        arg0->f = 0;
        FUN_004658c0(arg0);
    }
}

void FUN_00465df0(void *arg0, int arg1, char arg2) {
    if ((*(unsigned char *)((char *)(arg0) + 117) != 0) && ((arg1 == 0xC8) || (arg1 == 0xC9))) {
        *(char *)((char *)(arg0) + 116) = arg2;
    }
    if (arg1 != 0xCA) {
        if (arg1 == 0xCB) {
            goto block_7;
        }
    } else {
block_7:
        *(char *)((char *)(arg0) + 108) = arg2;
        *(int *)((char *)(arg0) + 112) = 0;
    }
}

void FUN_00465e40(void *arg0, int arg1, char arg2) {
    switch (arg1) {
    case 0:
        *(char *)((char *)(arg0) + 88) = arg2;
        break;
    case 2:
        *(char *)((char *)(arg0) + 89) = arg2;
        break;
    case 1:
        *(char *)((char *)(arg0) + 90) = arg2;
        break;
    }
    *(int *)((char *)(arg0) + 112) = 0;
}

/* Applies a mouse drag of `delta` with the default button layout: the left button rotates, the
 * middle one pans and the right one rolls and zooms. */
void Gap__Viewer__igRotateMode__ApplyDrag(ViewerCameraState *state, const float *delta) {
    ViewerCameraTarget *target = state->target;

    if (state->primaryButton) {
        const float pi = 3.1415927f;
        state->yaw += pi * delta[0];
        state->pitch += pi * delta[1];
    }
    if (state->secondaryButton) {
        setVec3(state->pan, delta[0], delta[1] / target->aspect, 0.0f);
        scaleVec3(state->pan, state->distance / 2.0f);
    }
    if (state->tertiaryButton) {
        float dx = delta[0];
        float dy;
        state->roll += dx * 3.1415927f;
        dy = delta[1];
        state->zoom *= 1.0f + dy / 2.0f;
    }
}

void FUN_004660f0(ViewerCameraState *state, const float *delta) {
    ViewerCameraTarget *target = state->target;

    if (state->primaryButton) {
        if (state->secondaryButton) {
            float d = delta[0]; state->zoom *= 1.0f - d / 2.0f;
        } else {
            const float pi = 3.1415927f;
            state->yaw += pi * delta[0];
            state->pitch += pi * delta[1];
        }
    } else if (state->secondaryButton) {
        setVec3(state->pan, delta[0], delta[1] / target->aspect, 0.0f);
        scaleVec3(state->pan, state->distance / 2.0f);
    }
}

void FUN_004661e0(struct S *arg0, int arg1, int arg2, float fparg0, float fparg1) {
    int temp_a1;
    temp_a1 = arg2 & 0xFFFF;
    if (temp_a1 == 0) {
        arg0->f100 = fparg0;
        arg0->f104 = fparg1;
    } else if (temp_a1 == 1) {
        arg0->f92 = fparg0;
        arg0->f96 = fparg1;
    }
}

/* matching construct: compound-subtract variants */
void FUN_00466220(ViewerCameraState *state) {
    ViewerCameraTarget *target = state->target;
    float dx;
    float dy;
    float dz;

    state->f108 = 0;
    state->f112 = 0;
    state->f116 = !state->f117;
    state->yaw = 0.0f;
    state->roll = 0.0f;
    state->pitch = 0.0f;
    state->zoom = 1.0f;
    state->pan[0] = g_vec3Zero[0];
    state->pan[1] = g_vec3Zero[1];
    state->pan[2] = g_vec3Zero[2];
    dx = target->f160;
    dy = target->f164;
    dz = target->f168;
    dx -= target->f92;
    dy -= target->f96;
    dz -= target->f100;
    state->distance = sqrtf(dx * dx + dy * dy + dz * dz);
}

int FUN_004665e0(int arg0, int arg1, int arg2) {
    if (DAT_0058d240[0] != 0) {
        FUN_00466a10((PickRecord *)DAT_0058d240[0], (Hit *)arg2);
    }
    return 0;
}

/* Moves the GUI mouse cursor by the joystick's deflection over `seconds` and tells the GUI model's
 * views that the mouse position changed. */
void Gap__Viewer__igPickMode__MoveCursor(igPickMode *pickMode, float seconds) {
    igGuiSystemModel *model = (igGuiSystemModel *)((igGuiSystem *)pickMode->_guiSystem)->_model;
    float dx = pickMode->_joystickT[0];
    float dy = pickMode->_joystickT[1];
    ViewModelEvent event;
    bool moving = dx != g_vec2Zero[0] || dy != g_vec2Zero[1];

    if (moving) {
        dx *= seconds;
        dy *= seconds;
        model->_mousePosition[0] += dx;
        model->_mousePosition[1] += dy;
        event.type = VIEW_MODEL_FIELD_CHANGED;
        event.sender = 0;
        event.field = g_igGuiSystemModelMousePositionField[0];
        igModel_NotifyViews(model, &event);
    }
}

void FUN_004666c0(void *arg0, int arg1, int arg2, float fparg0, float fparg1) {
    if (!(arg2 & 0xFFFF)) {
        *(float *)((char *)(arg0) + 180) = fparg0;
        *(float *)((char *)(arg0) + 184) = fparg1;
    }
}

void FUN_004666e0(struct X *arg0, int arg1, int arg2) {
    struct Msg m;
    R2 **pp;
    R2 *p;
    if (arg2 != 0) {
        if (arg1 == 0) {
            FUN_00466b20((igPickMode *)arg0);
        } else if (arg1 == 1) {
            pp = &arg0->y->obj;
            p = *pp;
            if (p != 0) {
                p->refs = p->refs - 1;
                if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
            *pp = 0;
            m.a = 2;
            m.b = 0;
            m.c = DAT_0058cb00[0];
            igModel_NotifyViews(arg0->y, &m);
        }
    }
}

void FUN_004667a0(void *d0, void *d1, int arg2, int arg3) {
    if ((arg2 == 0xE) && (arg3 != 0)) {
        FUN_00466b20((igPickMode *)d0);
    }
}

void FUN_004667d0(igPickMode *pickMode) {
    struct { int pad; char b; int w; } unprojected;
    igProbe *created;
    igIntList *faceTypes;
    int top;
    igIntersectTraversal *traversal;
    igObject *previous;
    igObject *cursor;
    FUN_00191f30(&unprojected.w, pickMode->_inverseProjectionMatrix, pickMode->_parameters + 0x2C);
    unprojected.b = 0;
    igSmartPointer<igProbe> probe(FUN_0019e680(0));
    created = probe.get();
    ObjectList_AppendRetained(created->_rays, pickMode->_ray);
    faceTypes = (igIntList *)created->_intersectFaceType;
    top = count_of(faceTypes);
    if (top < faceTypes->_capacity) {
        faceTypes->_count = faceTypes->_count + 1;
    } else {
        List_Resize(faceTypes, top + 1, 4);
    }
    ((int *)faceTypes->_data)[top] = 2;
    setProbe(pickMode, probe);
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode = 0;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode = ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode | 4;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_hitProc = (int)&FUN_004665e0;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_userTimeState = 1;
    if (pickMode->_guiSystem != 0) {
        cursor = (igObject *)((igGuiSystem *)pickMode->_guiSystem)->_mouseCursor;
        if (cursor != 0) {
            cursor->_refCount = cursor->_refCount + 1;
        }
        previous = (igObject *)pickMode->_savedCursor;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        pickMode->_savedCursor = (int)cursor;
        pickMode->_savedCursorState = ((igGuiSystem *)pickMode->_guiSystem)->_mouseCursorVisible;
        FUN_00456a60(pickMode->_guiSystem, pickMode->_cursor);
        FUN_004569c0(pickMode->_guiSystem, 1);
    }
}

void FUN_004669d0(struct S80 *arg0) {
    if (arg0->f80 != 0) {
        FUN_00456a60(arg0->f80, arg0->f88);
        FUN_004569c0(arg0->f80, arg0->f92);
    }
}

extern "C" void FUN_00466a10(PickRecord *record, Hit *hit) {
    int object = hit->object;
    if (hit->distance <= record->nearest) {
        record->found = 1;
        record->nearest = hit->distance;
        setMarker(record, igSmartPointer<Marker>(createMarker()));
        FUN_001c5790(record->marker, object);
    }
}

void FUN_00466b20(igPickMode *arg0) {
    float v[3];
    int sp40[3];
    igViewModel *s0;
    int *s1;
    igObject *a0, *r0;
    s0 = (igViewModel *)arg0->_model;
    igGuiSystemModel *p = (igGuiSystemModel *)((igGuiSystem *)arg0->_guiSystem)->_model;
    float y = *(float *)&p->_mousePosition[1];
    v[0] = *(float *)&p->_mousePosition[0];
    v[1] = y;
    *(int *)&v[2] = 0x3F800000;
    Vec3f_TransformProjective(v, v, arg0->_inverseProjectionMatrix);
    FUN_0018d2b0(arg0->_ray, &g_vec3Zero[0], v);
    FUN_0018d360(arg0->_ray, arg0->_inverseMatrix);
    arg0->_impactLength = ((igRay *)arg0->_ray)->_len;
    arg0->_hit = 0;
    a0 = (igObject *)arg0->_hitPath;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if (((unsigned long long)(long long)(int)a0->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(a0);
    }
    arg0->_hitPath = 0;
    FUN_001ce970((VM *)arg0->_intersectTraversal);
    ((VM *)arg0->_intersectTraversal)->v25(s0->_drawTime);
    DAT_0058d240[0] = arg0;
    ((VM *)arg0->_intersectTraversal)->v23(((igViewerParameters *)arg0->_parameters)->_scene);
    DAT_0058d240[0] = 0;
    s1 = &((igViewerParameters *)arg0->_parameters)->_selectedObject;
    r0 = (igObject *)arg0->_hitPath;
    if (r0 != 0) {
        r0->_refCount = r0->_refCount + 1;
    }
    a0 = (igObject *)*s1;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if (((unsigned long long)(long long)(int)a0->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(a0);
    }
    *s1 = (int)r0;
    sp40[0] = 2;
    sp40[1] = 0;
    sp40[2] = DAT_0058cb00[0];
    igModel_NotifyViews((igViewerParameters *)arg0->_parameters, sp40);
}

/* Returns the metaobject handle of igPickMode, not of igViewManager. */
int FUN_00466cb0(void) {
    return g_igPickMode_metaObject[0];
}

int FUN_00466cc0(void) {
    return g_igRotateMode_metaObject[0];
}

int FUN_00466cd0(void) {
    return g_igFlyMode_metaObject[0];
}

int FUN_00466ce0(void) {
    return g_igCameraMode_metaObject[0];
}

int FUN_00466cf0(void) {
    return g_igViewMode_metaObject[0];
}

}

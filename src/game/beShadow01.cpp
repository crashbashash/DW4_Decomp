#include "dw4/reflected.h"
#include "dw4/igVec3f.h"

extern "C" void igObject_Destroy(...);
extern "C" int List_Reserve(...);
extern "C" int Gap__Bec__beShadow01__vfunc_30(void);
extern "C" int Gap__Bec__beShadow01__vfunc_20(void);
extern "C" int ObjectList_AppendRetained(...);
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beShadow01__vfunc_32(beShadow01 *arg0);
extern "C" int g_beShadow01Info_metaObject[4];
extern "C" int g_beShadow01_metaObject[4];
extern "C" int igGroup_AppendChild(igProjectiveShadowShader *group, int child);
extern "C" void beShadow01_AttachPendingInfos(beShadow01 *self, beShadow01Info *info);
extern "C" int igObject_IsKindOf(beShadow01Info *, int);
extern "C" int Gap__Core__igObject__vfunc_25(beShadow01 *, beShadow01Info *);
extern "C" int g_beShadow01Info_metaObject[4];
extern "C" int Gap__Bec__beShadow01__vfunc_25(beShadow01 *arg0, beShadow01Info *arg1);

void Gap__Bec__beShadow01__vfunc_32(beShadow01 *arg0) {
    /* matching construct: the int-indexed ((int *)...)[0] stores below spell the raw word stores of retail; they are list-backing-store writes, not game logic. */
    igDataList *l = (igDataList *)arg0->_svInfoList;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            ReleaseRef::go(((igObject **)((char *)l->_data + off))[0]);
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                ((int *)((char *)l->_data + off3))[0] = 0;
                ((int *)((char *)l->_data + off3 + 4))[0] = 0;
                ((int *)((char *)l->_data + off3 + 8))[0] = 0;
                ((int *)((char *)l->_data + off3 + 12))[0] = 0;
                ((int *)((char *)l->_data + off3 + 16))[0] = 0;
                ((int *)((char *)l->_data + off3 + 20))[0] = 0;
                ((int *)((char *)l->_data + off3 + 24))[0] = 0;
                ((int *)((char *)l->_data + off3 + 28))[0] = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                ((int *)((char *)l->_data + off4))[0] = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    if (!(0 < ((igDataList *)arg0->_svInfoList)->_count)) {
        List_Reserve((igDataList *)arg0->_svInfoList, 0, 4);
    }
    arg0->_savePos[0] = 0.0f;
    arg0->_savePos[1] = 0.0f;
    arg0->_savePos[2] = 0.0f;
}

int Gap__Bec__beShadow01__vfunc_30(void)
{
    return g_beShadow01Info_metaObject[0];
}

/* Adds the casters and receivers of the infos that arrived before a shader was there
 * (self->_svInfoList) to info's shader, then releases them and empties the list. */
void beShadow01_AttachPendingInfos(beShadow01 *self, beShadow01Info *info) {
    igObject *pending;
    beShadow01Info *it;
    igProjectiveShadowShader *shader;
    int n;
    int i;
    int off;
    beShadow01InfoList *list;
    int n2;
    int i2;
    int n3;
    int i3;
    i = 0;
    shader = (igProjectiveShadowShader *)info->_projShadowShader;
    n = ((beShadow01InfoList *)self->_svInfoList)->_count;
    if (0 < n) {
        off = 0;
        do {
            it = *(beShadow01Info **)((char *)((beShadow01InfoList *)self->_svInfoList)->_data + off);
            if (it->_casterNode != 0) ObjectList_AppendRetained(shader->_shadowCasters, it->_casterNode);
            if (it->_receiverNode != 0) igGroup_AppendChild(shader, it->_receiverNode);
            i += 1;
            off += 4;
        } while (i < n);
    }
    list = (beShadow01InfoList *)self->_svInfoList;
    n2 = list->_count;
    i2 = 0;
    if (0 < n2) {
        off = 0;
        do {
            pending = *(igObject **)((char *)list->_data + off);
            if (pending != 0) {
                pending->_refCount--;
                if (!(pending->_refCount & 0x7fffff)) igObject_Destroy(pending);
            }
            i2 += 1;
            off += 4;
        } while (i2 < n2);
    }
    n3 = list->_count;
    for (i3 = 0; i3 < n3; i3++) {
        ((igObject **)list->_data)[i3] = 0;
    }
    list->_count = 0;
    if (!(0 < ((beShadow01InfoList *)self->_svInfoList)->_count)) List_Reserve(self->_svInfoList, 0, 4);
}

int Gap__Bec__beShadow01__vfunc_25(beShadow01 *arg0, beShadow01Info *arg1) {
    igProjectiveShadowShader *t;

    if (igObject_IsKindOf(arg1, g_beShadow01Info_metaObject[0]) != 0) {
        t = (igProjectiveShadowShader *)arg1->_projShadowShader;
        if (t != 0) {
            t->_drawReceiver = 0;
            t->_useOrthographic = 1;
            t->_blurState = 0;
            t->_cutoff = 22.5f;
            if (t->_top == 5.0f) {
                t->_top = 100.0f;
                t->_bottom = -100.0f;
                t->_right = 100.0f;
                t->_left = -100.0f;
            }
            beShadow01_AttachPendingInfos(arg0, arg1);
            Gap__Core__igObject__vfunc_25(arg0, arg1);
        } else {
            ObjectList_AppendRetained(arg0->_svInfoList, arg1);
        }
        return 1;
    }
    return 0;
}

extern "C" void beShadow01_Update(beShadow01 *self, beBaseInfoRam *ram);
extern "C" int beTargetObj_GetPlayerCentre(float *out);
extern "C" void igProjectiveShadowShader_ConfigureSharedAttrs(void);
extern "C" void igProjectiveShadowShader_Initialize(igProjectiveShadowShader *shader);
/* The projective shadow pass's shared texture-function attribute for texture unit 0. */
extern "C" igTextureFunctionAttr *g_shadowTextureFunctionAttr0[4];
/* The igLightAttr meta-field of the light's direction; its _offset locates the field. */
extern "C" igMetaField *g_igLightAttr_directionMetaField[4];
/* igLightAttr with its vtable as a real vptr: slot 33 (vtable +140) sets the light position. */
class LightAttrVirtual {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32();
    virtual void setPosition(float *position);
};

/* True when the vectors differ in any component. */
static inline bool Vec3Differs(const igVec3f &a, const igVec3f &b) {
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

/* Copy a three-float vector; the source pointer shares &centre.y / &centre.z between the two copies. */
static inline void Vec3Copy(float *dst, const float *src) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

/* Per-frame update: on the first frame attach the shadow casters and initialise the shader,
 * then keep the shadow light 200 units above the players' centre. */
void beShadow01_Update(beShadow01 *self, beBaseInfoRam *ram) {
    beShadow01Info *info = (beShadow01Info *)ram->_parentInfo;
    igVec3f centre;

    switch (ram->_st0) { /* the step counter: one first-frame step (retail beqz/b pair of a switch) */
    case 0: {
        igProjectiveShadowShader *shader;
        beShadow01_AttachPendingInfos(self, info);
        shader = (igProjectiveShadowShader *)info->_projShadowShader;
        if (shader->_inited == 0) {
            igProjectiveShadowShader_ConfigureSharedAttrs();
            igProjectiveShadowShader_Initialize(shader);
            shader->_inited = 1;
        }
        g_shadowTextureFunctionAttr0[0]->_mode = 0;
        ram->_st0++;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        break;
    }
    }
    if (beTargetObj_GetPlayerCentre(&centre.x)) {
        centre.y += 200.0f;
        /* matching construct: fdiff — the saved-position reference is a variable of its own, so its address
         * (addiu a0,s2,36) is kept for the second and third compares. */
        igVec3f &saved = *(igVec3f *)self->_savePos;
        if (Vec3Differs(centre, saved)) {
            igLightAttr *light = (igLightAttr *)((igProjectiveShadowShader *)info->_projShadowShader)->_light;
            float *direction = (float *)((char *)light + g_igLightAttr_directionMetaField[0]->_offset);
            ((LightAttrVirtual *)light)->setPosition(&centre.x);
            Vec3Copy(light->_cachedPosition, &centre.x);
            Vec3Copy(light->_cachedDirection, direction);
            Vec3Copy(self->_savePos, &centre.x);
        }
    }
}

int Gap__Bec__beShadow01__vfunc_20(void)
{
    return g_beShadow01_metaObject[0];
}

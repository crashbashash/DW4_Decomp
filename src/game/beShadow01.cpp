#include "dw4/support/reflected.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/attrs/igLightAttrDispatchView.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beShadow01.h"
#include "dw4/game/beShadow01Info.h"
#include "dw4/game/beTargetObj.h"
#include "dw4/core/igDataLists.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/attrs/igLightAttr.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igProjectiveShadowShader.h"

extern "C" igMetaObject *beShadow01_GetInfoMeta(void);
extern "C" igMetaObject *beShadow01_GetMeta(void);
struct ReleaseRef { static inline void go(igObject *object) {
    igObject::release(object);
} };
extern "C" void beShadow01_Prepare(beShadow01 *self);
extern "C" void beShadow01_AttachPendingInfos(beShadow01 *self, beShadow01Info *info);
extern "C" int beShadow01_AddInfo(beShadow01 *self, beShadow01Info *info);

void beShadow01_Prepare(beShadow01 *self) {
    /* matching construct: the int-indexed ((int *)...)[0] stores below spell the raw word stores of retail; they are list-backing-store writes, not game logic. */
    igDataList *l = (igDataList *)self->_svInfoList;
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
    if (!(0 < ((igDataList *)self->_svInfoList)->_count)) {
        ((Gap::Core::igDataList *)self->_svInfoList)->setCapacity(0, 4);
    }
    self->_savePos[0] = 0.0f;
    self->_savePos[1] = 0.0f;
    self->_savePos[2] = 0.0f;
}

igMetaObject *beShadow01_GetInfoMeta(void)
{
    return g_beShadow01Info_metaObject;
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
            if (it->_casterNode != 0) ((Gap::Core::igObjectList *)shader->_shadowCasters)->append((Gap::Core::igObject *)it->_casterNode);
            if (it->_receiverNode != 0) ((Gap::Sg::igGroup *)shader)->appendChild((Gap::Sg::igNode *)it->_receiverNode);
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
    if (!(0 < ((beShadow01InfoList *)self->_svInfoList)->_count)) ((Gap::Core::igDataList *)self->_svInfoList)->setCapacity(0, 4);
}

int beShadow01_AddInfo(beShadow01 *self, beShadow01Info *info) {
    igProjectiveShadowShader *shader;

    if (((Gap::Core::igObject *)info)->isOfType(g_beShadow01Info_metaObject) != 0) {
        shader = (igProjectiveShadowShader *)info->_projShadowShader;
        if (shader != 0) {
            shader->_drawReceiver = 0;
            shader->_useOrthographic = 1;
            shader->_blurState = 0;
            shader->_cutoff = 22.5f;
            if (shader->_top == 5.0f) {
                shader->_top = 100.0f;
                shader->_bottom = -100.0f;
                shader->_right = 100.0f;
                shader->_left = -100.0f;
            }
            beShadow01_AttachPendingInfos(self, info);
            beBaseInfoManager_AddInfo((beBaseInfoManager *)self, (beBaseInfo *)info);
        } else {
            ((Gap::Core::igObjectList *)self->_svInfoList)->append((Gap::Core::igObject *)info);
        }
        return 1;
    }
    return 0;
}

extern "C" void beShadow01_UpdateRam(beShadow01 *self, beBaseInfoRam *ram);
extern "C" void igProjectiveShadowShader_Initialize(igProjectiveShadowShader *shader);
/* The projective shadow pass's shared texture-function attribute for texture unit 0. */
extern "C" igTextureFunctionAttr *g_shadowTextureFunctionAttr0[4];
/* The igLightAttr meta-field of the light's direction; its _offset locates the field. */
/* True when the vectors differ in any component. */
static inline bool Vec3Differs(const igVec3f &a, const igVec3f &b) {
    return a[0] != b[0] || a[1] != b[1] || a[2] != b[2];
}

/* Copy a three-float vector; the source pointer shares &centre.y / &centre.z between the two copies. */
static inline void Vec3Copy(float *dst, const float *src) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

/* Per-frame update: on the first frame attach the shadow casters and initialise the shader,
 * then keep the shadow light 200 units above the players' centre. */
void beShadow01_UpdateRam(beShadow01 *self, beBaseInfoRam *ram) {
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
    if (beTargetObj_GetPlayerCentre(centre.vec)) {
        centre[1] += 200.0f;
        /* matching construct: fdiff — the saved-position reference is a variable of its own, so its address
         * (addiu a0,s2,36) is kept for the second and third compares. */
        igVec3f &saved = self->_savePos;
        if (Vec3Differs(centre, saved)) {
            igLightAttr *light = (igLightAttr *)((igProjectiveShadowShader *)info->_projShadowShader)->_light;
            float *direction = (float *)((char *)light + g_igLightAttr_directionMetaField->_offset);
            ((igLightAttrDispatchView *)light)->setPosition(centre.vec);
            Vec3Copy(light->_cachedPosition, centre.vec);
            Vec3Copy(light->_cachedDirection, direction);
            Vec3Copy(self->_savePos.vec, centre.vec);
        }
    }
}

igMetaObject *beShadow01_GetMeta(void)
{
    return g_beShadow01_metaObject;
}

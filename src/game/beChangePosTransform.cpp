#include "dw4/reflected.h"
#pragma push
#pragma readonly_strings on
#include "dw4/igVec3f.h"
#include "dw4/beChangePosTransform.h"
#include "dw4/beChangePosTransformInfo.h"
#include "dw4/beMessenger.h"
#include "dw4/igMatrix44f.h"

extern "C" void beChangePosTransform_Prepare(void);
extern "C" igMetaObject *beChangePosTransform_GetInfoMeta(void);
extern "C" void beChangePosTransform_UpdateRam(beChangePosTransform *self, beChangePosTransformInfoRam *info);
extern "C" igMetaObject *beChangePosTransform_GetMeta(void);
extern "C" const igVec3f g_vec3Zero;

void beChangePosTransform_Prepare(void)
{
}

igMetaObject *beChangePosTransform_GetInfoMeta(void)
{
    return g_beChangePosTransformInfo_metaObject;
}

static inline void DivideByCount(igVec3f &v, int count)
{
    switch (count) {
    case 0:
    case 1:
        break;
    case 2:
        v.x /= 2.0f;
        v.y /= 2.0f;
        v.z /= 2.0f;
        break;
    case 3:
        v.x /= 3.0f;
        v.y /= 3.0f;
        v.z /= 3.0f;
        break;
    case 4:
        v.x /= 4.0f;
        v.y /= 4.0f;
        v.z /= 4.0f;
        break;
    }
}

static inline bool IsFar(const igVec3f &a, const igVec3f &b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z) >= 40.0f * 40.0f;
}

/* State 0 puts the transform at the players' centre. State 1 follows the centre while every player is within
 * 40 units of it on the ground plane, and otherwise holds the last position. */
void beChangePosTransform_UpdateRam(beChangePosTransform *self, beChangePosTransformInfoRam *info)
{
    igVec3f translations[4];
    switch (info->_st0) {
    case 0: {
        igVec3f centre = g_vec3Zero;
        beMessenger_SendGroup((beMessenger *)self->_messenger, "PLAYER", "GETMATRIX");
        if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
            int count = beMessenger_GetMatrixCount((beMessenger *)self->_messenger);
            for (int i = 0; i < count; i++) {
                float playerMatrix[16];
                igVec3f translation;
                beMessenger_GetMatrix(playerMatrix, (beMessenger *)self->_messenger, i);
                igMatrix44f_GetTranslation(playerMatrix, (float *)&translation);
                centre.x += translation.x;
                centre.y += translation.y;
                centre.z += translation.z;
            }
            DivideByCount(centre, count);
        }
        float *transformMatrix = ((igTransform *)info->_transform)->_m;
        *(igVec3f *)self->_oldPos = centre;
        igMatrix44f_SetTranslation(transformMatrix, &centre.x);
        info->_st0++;
        info->_st3 = 0;
        info->_st2 = 0;
        info->_st1 = 0;
        break;
    }
    case 1: {
        beMessenger_SendGroup((beMessenger *)self->_messenger, "PLAYER", "GETMATRIX");
        if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
            igVec3f centre = g_vec3Zero;
            int count = beMessenger_GetMatrixCount((beMessenger *)self->_messenger);
            for (int i = 0; i < count; i++) {
                float playerMatrix[16];
                beMessenger_GetMatrix(playerMatrix, (beMessenger *)self->_messenger, i);
                igMatrix44f_GetTranslation(playerMatrix, (float *)&translations[i]);
                centre.x += translations[i].x;
                centre.y += translations[i].y;
                centre.z += translations[i].z;
            }
            DivideByCount(centre, count);
            bool allNear = true;
            igVec3f flat = centre;
            flat.y = 0.0f;
            for (int i = 0; i < count; i++) {
                translations[i].y = 0.0f;
                if (IsFar(translations[i], flat)) {
                    allNear = false;
                    break;
                }
            }
            float *transformMatrix = ((igTransform *)info->_transform)->_m;
            /* matching construct: hand search — `== false` tests the flag as an int (andi 0xff); `!allNear` does not */
            if (allNear == false) {
                igMatrix44f_SetTranslation(transformMatrix, self->_oldPos);
            } else {
                *(igVec3f *)self->_oldPos = centre;
                igMatrix44f_SetTranslation(transformMatrix, &centre.x);
            }
        }
        break;
    }
    case 2:
    case 3:
        break;
    }
}

igMetaObject *beChangePosTransform_GetMeta(void)
{
    return g_beChangePosTransform_metaObject;
}

#pragma pop

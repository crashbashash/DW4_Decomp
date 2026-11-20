#include "dw4/support/reflected.h"
#pragma push
#pragma readonly_strings on
#include "dw4/maths/igVec3f.h"
#include "dw4/game/beChangePosTransform.h"
#include "dw4/game/beChangePosTransformInfo.h"
#include "dw4/game/beMessenger.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/maths/igMathConstants.h"

extern "C" void beChangePosTransform_Prepare(void);
extern "C" igMetaObject *beChangePosTransform_GetInfoMeta(void);
extern "C" void beChangePosTransform_UpdateRam(beChangePosTransform *self, beChangePosTransformInfoRam *info);
extern "C" igMetaObject *beChangePosTransform_GetMeta(void);

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
        v[0] /= 2.0f;
        v[1] /= 2.0f;
        v[2] /= 2.0f;
        break;
    case 3:
        v[0] /= 3.0f;
        v[1] /= 3.0f;
        v[2] /= 3.0f;
        break;
    case 4:
        v[0] /= 4.0f;
        v[1] /= 4.0f;
        v[2] /= 4.0f;
        break;
    }
}

static inline bool IsFar(const igVec3f &a, const igVec3f &b)
{
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]) >= 40.0f * 40.0f;
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
                centre[0] += translation[0];
                centre[1] += translation[1];
                centre[2] += translation[2];
            }
            DivideByCount(centre, count);
        }
        float *transformMatrix = ((igTransform *)info->_transform)->_m;
        self->_oldPos = centre;
        igMatrix44f_SetTranslation(transformMatrix, centre.vec);
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
                centre[0] += translations[i][0];
                centre[1] += translations[i][1];
                centre[2] += translations[i][2];
            }
            DivideByCount(centre, count);
            bool allNear = true;
            igVec3f flat = centre;
            flat[1] = 0.0f;
            for (int i = 0; i < count; i++) {
                translations[i][1] = 0.0f;
                if (IsFar(translations[i], flat)) {
                    allNear = false;
                    break;
                }
            }
            float *transformMatrix = ((igTransform *)info->_transform)->_m;
            /* matching construct: hand search — `== false` tests the flag as an int (andi 0xff); `!allNear` does not */
            if (allNear == false) {
                igMatrix44f_SetTranslation(transformMatrix, self->_oldPos.vec);
            } else {
                self->_oldPos = centre;
                igMatrix44f_SetTranslation(transformMatrix, centre.vec);
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

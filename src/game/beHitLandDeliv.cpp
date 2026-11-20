#include "dw4/support/reflected.h"
#pragma push
#pragma readonly_strings on
#include "dw4/maths/igVec3f.h"
#include "dw4/game/beHitLandDeliv.h"
#include "dw4/game/beHitLandDelivInfo.h"
#include "dw4/game/beMessenger.h"
#include "dw4/maths/igMatrix44f.h"
#include <math.h>

extern "C" void beHitLandDeliv_Prepare(void);
extern "C" igMetaObject *beHitLandDeliv_GetInfoMeta(void);
extern "C" void beHitLandDeliv_UpdateRam(void);
extern "C" igMetaObject *beHitLandDeliv_GetMeta(void);
extern "C" void beHitLandDeliv_OnAddRam(beHitLandDeliv *self, int ram, char *unused);
extern "C" int beHitLandDeliv_OnMessageText(beHitLandDeliv *self, beHitLandDelivInfoRam *ram, const char *message);

enum beHitLandDelivMessage {
    HITWALL,
    HITWALLFULL,
    HITFLOORCHECK,
    HITFLOORADJUST,
    HITFLOOR
};

void beHitLandDeliv_Prepare(void)
{
}

igMetaObject *beHitLandDeliv_GetInfoMeta(void)
{
    return g_beHitLandDelivInfo_metaObject;
}

void beHitLandDeliv_OnAddRam(beHitLandDeliv *self, int ram, char *unused)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)ram, "HITLANDDELIVER");
}

void beHitLandDeliv_UpdateRam(void)
{
}

static inline float *TransformMatrix(beHitLandDelivInfoRam *ram)
{
    return ((igTransform *)ram->_transform)->_m;
}

/* The ray settings every HITLANDMODEL check takes after its vectors. */
static inline void AppendRayRange(beHitLandDeliv *self, beHitLandDelivInfoRam *ram)
{
    beMessenger_AppendFloat((beMessenger *)self->_messenger, ram->_halfWidth);
    beMessenger_AppendFloat((beMessenger *)self->_messenger, ram->_upRange);
    beMessenger_AppendFloat((beMessenger *)self->_messenger, ram->_downRange);
    beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_checkFlag);
}

/* Whether the last wall check touched a wall, kept as 1 or 0 in _pos.x. */
static inline void AppendTouching(beHitLandDeliv *self, beHitLandDelivInfoRam *ram)
{
    if (ram->_pos[0] == 0.0f) {
        beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
    } else {
        beMessenger_AppendInt((beMessenger *)self->_messenger, 1);
    }
}

static inline void SetTouching(beHitLandDelivInfoRam *ram, unsigned char hitWall)
{
    igVec3f touching;
    if (hitWall == 1) {
        touching.set(1.0f, 0.0f, 0.0f);
    } else {
        touching.set(0.0f, 0.0f, 0.0f);
    }
    *(igVec3f *)ram->_pos = touching;
}

int beHitLandDeliv_OnMessageText(beHitLandDeliv *self, beHitLandDelivInfoRam *ram, const char *message)
{
    unsigned kind = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beHitLandDelivInfo_GetMessageEnum(), message);
    switch (kind) {
    case HITWALL: {
        unsigned char hitWall = 0;
        igVec3f position;
        igMatrix44f_GetTranslation(TransformMatrix(ram), (float *)&position);
        if (ram->_oldPos[0] != position[0] || ram->_oldPos[2] != position[2]) {
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "HITLANDMODEL");
            beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
            igVec3f direction(position[0] - ram->_oldPos[0], 0.0f, position[2] - ram->_oldPos[2]);
            float inv = 1.0f / sqrtf(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);
            direction[0] *= inv;
            direction[1] *= inv;
            direction[2] *= inv;
            beMessenger_AppendVec3((beMessenger *)self->_messenger, direction);
            AppendRayRange(self, ram);
            AppendTouching(self, ram);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "CHECKWALL");
            if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0) {
                hitWall = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
            } else {
                hitWall = 0;
            }
            SetTouching(ram, hitWall);
        }
        unsigned char moved = 0;
        unsigned char wallHit = 0;
        if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) != 0) {
            if (hitWall == 1) {
                moved = true;
                wallHit = moved;
                float *matrix = TransformMatrix(ram);
                igMatrix44f_SetTranslation(matrix, beMessenger_GetVec3((beMessenger *)self->_messenger, 0).vec);
            }
            *(igVec3f *)ram->_oldPos = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
        }
        beMessenger_ResizeBool((beMessenger *)self->_messenger, 3);
        beMessenger_SetBool((beMessenger *)self->_messenger, 0, moved);
        beMessenger_SetBool((beMessenger *)self->_messenger, 1, wallHit);
        beMessenger_SetBool((beMessenger *)self->_messenger, 2, 0);
        break;
    }
    case HITWALLFULL: {
        igVec3f position;
        igMatrix44f_GetTranslation(TransformMatrix(ram), (float *)&position);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "HITLANDMODEL");
        beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
        beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
        AppendRayRange(self, ram);
        AppendTouching(self, ram);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "CHECKWALLFULL");
        unsigned char hitWall;
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0) {
            hitWall = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
        } else {
            hitWall = 0;
        }
        SetTouching(ram, hitWall);
        unsigned char moved = 0;
        unsigned char wallHit = 0;
        if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) != 0) {
            if (hitWall == 1) {
                moved = true;
                wallHit = moved;
                float *matrix = TransformMatrix(ram);
                igMatrix44f_SetTranslation(matrix, beMessenger_GetVec3((beMessenger *)self->_messenger, 0).vec);
            }
            *(igVec3f *)ram->_oldPos = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
        }
        beMessenger_ResizeBool((beMessenger *)self->_messenger, 3);
        beMessenger_SetBool((beMessenger *)self->_messenger, 0, moved);
        beMessenger_SetBool((beMessenger *)self->_messenger, 1, wallHit);
        beMessenger_SetBool((beMessenger *)self->_messenger, 2, 0);
        break;
    }
    case HITFLOOR:
    case HITFLOORCHECK: {
        igVec3f position;
        igMatrix44f_GetTranslation(TransformMatrix(ram), (float *)&position);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "HITLANDMODEL");
        beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
        AppendRayRange(self, ram);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "CHECKLAND");
        unsigned char landed = 0;
        unsigned char floorHit = 0;
        unsigned char landPosOK = 0;
        igVec3f floor;
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) < 3 || beMessenger_GetVec3Count((beMessenger *)self->_messenger) < 1) {
            floor.set(0.0f, -1.0f, 0.0f);
        } else {
            floor = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
            landed = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
            floorHit = beMessenger_GetBool((beMessenger *)self->_messenger, 1);
            landPosOK = beMessenger_GetBool((beMessenger *)self->_messenger, 2);
        }
        if (floor[1] < 1.0f) {
            igVec3f current;
            igMatrix44f_GetTranslation(TransformMatrix(ram), (float *)&current);
            if (current[1] < 0.0f) {
                ((igVec3f *)ram->_landPos)->set(floor[0], 0.0f, floor[2]);
                ((igVec3f *)ram->_oldPos)->set(floor[0], 0.0f, floor[2]);
                ram->_landPosOK = 1;
                landed = 1;
                floorHit = 1;
            } else {
                ram->_landPosOK = 0;
                landed = 1;
                floorHit = 0;
            }
        } else {
            *(igVec3f *)ram->_landPos = floor;
            *(igVec3f *)ram->_oldPos = floor;
            ram->_landPosOK = landPosOK;
        }
        beMessenger_ResizeBool((beMessenger *)self->_messenger, 2);
        beMessenger_SetBool((beMessenger *)self->_messenger, 0, landed);
        beMessenger_SetBool((beMessenger *)self->_messenger, 1, floorHit);
        if (kind != HITFLOOR) {
            break;
        }
    }
    case HITFLOORADJUST:
        if (ram->_landPosOK) {
            igMatrix44f_SetTranslation(TransformMatrix(ram), ram->_landPos);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

igMetaObject *beHitLandDeliv_GetMeta(void)
{
    return g_beHitLandDeliv_metaObject;
}

#pragma pop

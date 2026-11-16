#include "dw4/reflected.h"
#pragma push
#pragma readonly_strings on
#include "dw4/igVec3f.h"

extern "C" void beHitLandDeliv_Prepare(void);
extern "C" int beHitLandDeliv_GetInfoMeta(void);
extern "C" void beHitLandDeliv_UpdateRam(void);
extern "C" int beHitLandDeliv_GetMeta(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int messenger, int ram, const char *category);
extern "C" int g_beHitLandDelivInfo_metaObject[4];
extern "C" int g_beHitLandDeliv_metaObject[4];
extern "C" void beHitLandDeliv_OnAddRam(beHitLandDeliv *self, int ram, char *unused);
extern "C" int beHitLandDeliv_OnMessageText(beHitLandDeliv *self, beHitLandDelivInfoRam *ram, const char *message);
extern "C" float sqrtf(float);
extern "C" igMetaEnum *beHitLandDelivInfo_GetMessageEnum(void);
extern "C" unsigned beMessenger_ResolveEnumValue(int messenger, igMetaEnum *values, const char *name);
extern "C" void beMessenger_SelectGroup(int messenger, const char *group);
extern "C" void beMessenger_DispatchSelected(int messenger, const char *message);
extern "C" void beMessenger_AppendVec3(int messenger, igVec3f value);
extern "C" void beMessenger_AppendFloat(int messenger, float value);
extern "C" void beMessenger_AppendInt(int messenger, int value);
extern "C" int beMessenger_GetBoolCount(int messenger);
extern "C" unsigned char beMessenger_GetBool(int messenger, int index);
extern "C" int beMessenger_GetVec3Count(int messenger);
extern "C" igVec3f beMessenger_GetVec3(int messenger, int index);
extern "C" void beMessenger_ResizeBool(int messenger, int count);
extern "C" void beMessenger_SetBool(int messenger, int index, unsigned char value);
extern "C" void igMatrix44f_GetTranslation(float *matrix, igVec3f *out);
extern "C" void igMatrix44f_SetTranslation(float *matrix, const igVec3f &translation);

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

int beHitLandDeliv_GetInfoMeta(void)
{
    return g_beHitLandDelivInfo_metaObject[0];
}

void beHitLandDeliv_OnAddRam(beHitLandDeliv *self, int ram, char *unused)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, "HITLANDDELIVER");
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
    beMessenger_AppendFloat(self->_messenger, ram->_halfWidth);
    beMessenger_AppendFloat(self->_messenger, ram->_upRange);
    beMessenger_AppendFloat(self->_messenger, ram->_downRange);
    beMessenger_AppendInt(self->_messenger, ram->_checkFlag);
}

/* Whether the last wall check touched a wall, kept as 1 or 0 in _pos.x. */
static inline void AppendTouching(beHitLandDeliv *self, beHitLandDelivInfoRam *ram)
{
    if (ram->_pos[0] == 0.0f) {
        beMessenger_AppendInt(self->_messenger, 0);
    } else {
        beMessenger_AppendInt(self->_messenger, 1);
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
    unsigned kind = beMessenger_ResolveEnumValue(self->_messenger, beHitLandDelivInfo_GetMessageEnum(), message);
    switch (kind) {
    case HITWALL: {
        unsigned char hitWall = 0;
        igVec3f position;
        igMatrix44f_GetTranslation(TransformMatrix(ram), &position);
        if (ram->_oldPos[0] != position.x || ram->_oldPos[2] != position.z) {
            beMessenger_SelectGroup(self->_messenger, "HITLANDMODEL");
            beMessenger_AppendVec3(self->_messenger, position);
            igVec3f direction(position.x - ram->_oldPos[0], 0.0f, position.z - ram->_oldPos[2]);
            float inv = 1.0f / sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
            direction.x *= inv;
            direction.y *= inv;
            direction.z *= inv;
            beMessenger_AppendVec3(self->_messenger, direction);
            AppendRayRange(self, ram);
            AppendTouching(self, ram);
            beMessenger_DispatchSelected(self->_messenger, "CHECKWALL");
            if (beMessenger_GetBoolCount(self->_messenger) != 0) {
                hitWall = beMessenger_GetBool(self->_messenger, 0);
            } else {
                hitWall = 0;
            }
            SetTouching(ram, hitWall);
        }
        unsigned char moved = 0;
        unsigned char wallHit = 0;
        if (beMessenger_GetVec3Count(self->_messenger) != 0) {
            if (hitWall == 1) {
                moved = true;
                wallHit = moved;
                igMatrix44f_SetTranslation(TransformMatrix(ram), beMessenger_GetVec3(self->_messenger, 0));
            }
            *(igVec3f *)ram->_oldPos = beMessenger_GetVec3(self->_messenger, 0);
        }
        beMessenger_ResizeBool(self->_messenger, 3);
        beMessenger_SetBool(self->_messenger, 0, moved);
        beMessenger_SetBool(self->_messenger, 1, wallHit);
        beMessenger_SetBool(self->_messenger, 2, 0);
        break;
    }
    case HITWALLFULL: {
        igVec3f position;
        igMatrix44f_GetTranslation(TransformMatrix(ram), &position);
        beMessenger_SelectGroup(self->_messenger, "HITLANDMODEL");
        beMessenger_AppendVec3(self->_messenger, position);
        beMessenger_AppendVec3(self->_messenger, position);
        AppendRayRange(self, ram);
        AppendTouching(self, ram);
        beMessenger_DispatchSelected(self->_messenger, "CHECKWALLFULL");
        unsigned char hitWall;
        if (beMessenger_GetBoolCount(self->_messenger) != 0) {
            hitWall = beMessenger_GetBool(self->_messenger, 0);
        } else {
            hitWall = 0;
        }
        SetTouching(ram, hitWall);
        unsigned char moved = 0;
        unsigned char wallHit = 0;
        if (beMessenger_GetVec3Count(self->_messenger) != 0) {
            if (hitWall == 1) {
                moved = true;
                wallHit = moved;
                igMatrix44f_SetTranslation(TransformMatrix(ram), beMessenger_GetVec3(self->_messenger, 0));
            }
            *(igVec3f *)ram->_oldPos = beMessenger_GetVec3(self->_messenger, 0);
        }
        beMessenger_ResizeBool(self->_messenger, 3);
        beMessenger_SetBool(self->_messenger, 0, moved);
        beMessenger_SetBool(self->_messenger, 1, wallHit);
        beMessenger_SetBool(self->_messenger, 2, 0);
        break;
    }
    case HITFLOOR:
    case HITFLOORCHECK: {
        igVec3f position;
        igMatrix44f_GetTranslation(TransformMatrix(ram), &position);
        beMessenger_SelectGroup(self->_messenger, "HITLANDMODEL");
        beMessenger_AppendVec3(self->_messenger, position);
        AppendRayRange(self, ram);
        beMessenger_DispatchSelected(self->_messenger, "CHECKLAND");
        unsigned char landed = 0;
        unsigned char floorHit = 0;
        unsigned char landPosOK = 0;
        igVec3f floor;
        if (beMessenger_GetBoolCount(self->_messenger) < 3 || beMessenger_GetVec3Count(self->_messenger) < 1) {
            floor.set(0.0f, -1.0f, 0.0f);
        } else {
            floor = beMessenger_GetVec3(self->_messenger, 0);
            landed = beMessenger_GetBool(self->_messenger, 0);
            floorHit = beMessenger_GetBool(self->_messenger, 1);
            landPosOK = beMessenger_GetBool(self->_messenger, 2);
        }
        if (floor.y < 1.0f) {
            igVec3f current;
            igMatrix44f_GetTranslation(TransformMatrix(ram), &current);
            if (current.y < 0.0f) {
                ((igVec3f *)ram->_landPos)->set(floor.x, 0.0f, floor.z);
                ((igVec3f *)ram->_oldPos)->set(floor.x, 0.0f, floor.z);
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
        beMessenger_ResizeBool(self->_messenger, 2);
        beMessenger_SetBool(self->_messenger, 0, landed);
        beMessenger_SetBool(self->_messenger, 1, floorHit);
        if (kind != HITFLOOR) {
            break;
        }
    }
    case HITFLOORADJUST:
        if (ram->_landPosOK) {
            igMatrix44f_SetTranslation(TransformMatrix(ram), *(igVec3f *)ram->_landPos);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

int beHitLandDeliv_GetMeta(void)
{
    return g_beHitLandDeliv_metaObject[0];
}

#pragma pop

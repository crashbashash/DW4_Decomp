#include "dw4/reflected.h"
#include "dw4/igVec3f.h"
#include "dw4/igMatrix44f.h"

extern "C" void igInsightCore_AddToScheduler(int insight, beTargetObj *object);
extern "C" void igInsightCore_RemoveFromScheduler(int insight, beTargetObj *object);
extern "C" int igInsightCore_FindManager(int insight, int metaObject);
extern "C" void Vec3f_TransformDirection(float *out, int *vector, float *matrix);
extern "C" int List_Reserve(void *list, int count, int elementSize);
extern "C" int List_Resize(void *list, int count, int elementSize);
extern "C" void Matrix44_GetTranslation(float *matrix, float *out);
extern "C" void Matrix44_Copy(float *dst, float *src);
extern "C" int beMessenger_GetInt(beMessenger *messenger, int index);
extern "C" void beMessenger_GetMatrix(float *out, beMessenger *messenger, int index);
extern "C" int beMessenger_GetMatrixCount(beMessenger *messenger);
extern "C" void beMessenger_SendGroup(beMessenger *messenger, char *group, char *message);
extern "C" float atan2f(float y, float x);
extern "C" int strcmp(const char *a, const char *b);
extern "C" int g_beTargetObj_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" float g_vec3Zero[4];
extern "C" int g_vec3ZAxis[4];
extern "C" char PLAYER_5[];
extern "C" char GETMATRIX_6[];
extern "C" char ENEMY_2[];
extern "C" char GETMATRIX_ACTIVE[];
extern "C" char NEAR_2[];

/* The scene's one target object, and the messenger it asks the actors through. */
extern "C" beTargetObj *g_targetObj;
extern "C" beMessenger *g_targetMessenger;

/* The last target query: where it was asked from, and what it found. */
extern "C" igVec3f g_targetOrigin;
extern "C" float g_targetOriginHeading;
extern "C" {
igMatrix44f g_targetOriginMatrix;
}
extern "C" igVec3f g_targetPosition;
extern "C" float g_targetDistanceSq;
extern "C" int g_targetRamNo;

#define TARGET_HEADING_UNSET -100.0f
#define TWO_PI 6.2831855f

extern "C" float beTargetObj_GetOriginHeading(beTargetObj *self);

extern "C" void Gap__Bec__beTargetObj__vfunc_21(beTargetObj *self, int unused)
{
    igInsightCore_AddToScheduler(self->_insight, self);
}

extern "C" void Gap__Bec__beTargetObj__vfunc_22(beTargetObj *self, int unused)
{
    igInsightCore_RemoveFromScheduler(self->_insight, self);
}

extern "C" void Gap__Bec__beTargetObj__vfunc_23(beTargetObj *self)
{
    g_targetObj = (beTargetObj *)igInsightCore_FindManager(self->_insight, g_beTargetObj_metaObject[0]);
    g_targetMessenger = (beMessenger *)igInsightCore_FindManager(self->_insight, g_beMessenger_metaObject[0]);
}

extern "C" void Gap__Bec__beTargetObj__vfunc_24(void)
{
}

extern "C" int Gap__Bec__beTargetObj__vfunc_25(void)
{
    return 0;
}

extern "C" void Gap__Bec__beTargetObj__vfunc_26(beTargetObj *self)
{
    igVec3fList *playerPositions;
    igIntList *playerRamNos;
    igVec3fList *enemyPositions;

    ((igVec3fList *)self->_playerPosList)->_count = 0;
    playerPositions = (igVec3fList *)self->_playerPosList;
    if (!(0 < playerPositions->_count)) {
        List_Reserve(playerPositions, 0, sizeof(igVec3f));
    }
    ((igIntList *)self->_playerRamNoList)->_count = 0;
    playerRamNos = (igIntList *)self->_playerRamNoList;
    if (!(0 < playerRamNos->_count)) {
        List_Reserve(playerRamNos, 0, sizeof(int));
    }
    ((igVec3fList *)self->_enemyPosList)->_count = 0;
    enemyPositions = (igVec3fList *)self->_enemyPosList;
    if (!(0 < enemyPositions->_count)) {
        List_Reserve(enemyPositions, 0, sizeof(igVec3f));
    }
}

extern "C" void Gap__Bec__beTargetObj__vfunc_27(beTargetObj *self)
{
    ((igVec3fList *)self->_playerPosList)->_count = 0;
    ((igIntList *)self->_playerRamNoList)->_count = 0;
    ((igVec3fList *)self->_enemyPosList)->_count = 0;
}

/* Sends `message` to the actor group and appends the translation of every matrix the actors answer
 * with to `positions`, and each actor's RAM number to `ramNos` when given. */
extern "C" void beTargetObj_GatherPositions(beTargetObj *self, igVec3fList *positions, igIntList *ramNos,
                                            char *group, char *message)
{
    const igIntList *ramNosView = ramNos;
    float position[3];
    float matrix[16];
    int count, i, n, ramNo;
    igVec3f *slot;

    beMessenger_SendGroup(g_targetMessenger, group, message);
    count = beMessenger_GetMatrixCount(g_targetMessenger);
    for (i = 0; i < count; i++) {
        beMessenger_GetMatrix(matrix, g_targetMessenger, i);
        Matrix44_GetTranslation(matrix, position);
        n = positions->_count;
        if (n < positions->_capacity) {
            positions->_count = n + 1;
        } else {
            List_Resize(positions, n + 1, sizeof(igVec3f));
        }
        slot = &((igVec3f *)positions->_data)[n];
        slot->x = position[0];
        slot->y = position[1];
        slot->z = position[2];
        if (ramNos != 0) {
            ramNo = beMessenger_GetInt(g_targetMessenger, i);
            n = ramNosView->_count;
            if (n < ramNos->_capacity) {
                ramNos->_count = ramNos->_count + 1;
            } else {
                List_Resize(ramNos, n + 1, sizeof(int));
            }
            ((int *)ramNos->_data)[n] = ramNo;
        }
    }
}

/* The candidate closest to `from`. */
extern "C" void beTargetObj_FindNearest(beTargetObj *self, igVec3fList *positions, igIntList *ramNos,
                                        igVec3f *from, igVec3f *outPosition, float *outDistanceSq,
                                        int *outRamNo)
{
    int ramNo;
    int count;
    int i;
    float dx, dy, dz, distanceSq, best, px, py, pz, bestX, bestY, bestZ;

    ramNo = 0;
    count = positions->_count;
    for (i = 0; i < count; i++) {
        igVec3f *p = &((igVec3f *)positions->_data)[i];
        px = p->x;
        py = p->y;
        pz = p->z;
        dy = from->y - py;
        dx = from->x - px;
        dz = from->z - pz;
        distanceSq = dx * dx + dy * dy + dz * dz;
        if (i == 0 || !(best <= distanceSq)) {
            best = distanceSq;
            bestX = px;
            bestY = py;
            bestZ = pz;
            if (ramNos) ramNo = ((int *)ramNos->_data)[i];
        }
    }
    outPosition->x = bestX;
    outPosition->y = bestY;
    outPosition->z = bestZ;
    *outDistanceSq = best;
    *outRamNo = ramNo;
}

/* The candidate whose bearing from `from` lies closest to the origin's heading. */
extern "C" void beTargetObj_FindFacing(beTargetObj *self, igVec3fList *positions, igIntList *ramNos,
                                       igVec3f *from, igVec3f *outPosition, float *outDistanceSq,
                                       int *outRamNo)
{
    int ramNo;
    int count;
    int i;
    float heading, best, px, py, pz, bestX, bestY, bestZ, turn, dx, dy, dz;

    heading = beTargetObj_GetOriginHeading(self);
    count = positions->_count;
    for (i = 0; i < count; i++) {
        igVec3f *p = &((igVec3f *)positions->_data)[i];
        px = p->x;
        py = p->y;
        pz = p->z;
        turn = atan2f(px - from->x, pz - from->z) - heading;
        if (turn < 0.0f) turn = -turn;
        while (turn > TWO_PI) turn -= TWO_PI;
        if (i == 0 || !(best <= turn)) {
            best = turn;
            bestX = px;
            bestY = py;
            bestZ = pz;
            ramNo = ((int *)ramNos->_data)[i];
        }
    }
    outPosition->x = bestX;
    outPosition->y = bestY;
    outPosition->z = bestZ;
    dy = from->y - bestY;
    dx = from->x - bestX;
    dz = from->z - bestZ;
    *outDistanceSq = dx * dx + dy * dy + dz * dz;
    *outRamNo = ramNo;
}

/* The mean position of the players, gathering them first if none are held. */
extern "C" int beTargetObj_GetPlayerCentre(float *out)
{
    int count, i;

    if (((igVec3fList *)g_targetObj->_playerPosList)->_count == 0) {
        beTargetObj_GatherPositions(g_targetObj, (igVec3fList *)g_targetObj->_playerPosList,
                                    (igIntList *)g_targetObj->_playerRamNoList, PLAYER_5, GETMATRIX_6);
        if (((igVec3fList *)g_targetObj->_playerPosList)->_count == 0) return 0;
    }
    out[0] = g_vec3Zero[0];
    out[1] = g_vec3Zero[1];
    out[2] = g_vec3Zero[2];
    count = ((igVec3fList *)g_targetObj->_playerPosList)->_count;
    for (i = 0; i < count; i++) {
        igVec3f *p = &((igVec3f *)((igVec3fList *)g_targetObj->_playerPosList)->_data)[i];
        out[0] += p->x;
        out[1] += p->y;
        out[2] += p->z;
    }
    switch (count) {
    case 0:
    case 1:
        break;
    case 2:
        out[0] /= 2.0f;
        out[1] /= 2.0f;
        out[2] /= 2.0f;
        break;
    case 3:
        out[0] /= 3.0f;
        out[1] /= 3.0f;
        out[2] /= 3.0f;
        break;
    case 4:
        out[0] /= 4.0f;
        out[1] /= 4.0f;
        out[2] /= 4.0f;
        break;
    }
    return 1;
}

extern "C" int beTargetObj_TargetPlayer(beTargetObj *self, float *from, int nearest)
{
    float nearFrom[3];
    float facingFrom[3];

    if (((igVec3fList *)self->_playerPosList)->_count == 0) {
        beTargetObj_GatherPositions(self, (igVec3fList *)self->_playerPosList,
                                    (igIntList *)self->_playerRamNoList, PLAYER_5, GETMATRIX_6);
        if (((igVec3fList *)self->_playerPosList)->_count == 0) {
            return 0;
        }
    }
    if (nearest != 0) {
        nearFrom[0] = from[0];
        nearFrom[1] = from[1];
        nearFrom[2] = from[2];
        beTargetObj_FindNearest(self, (igVec3fList *)self->_playerPosList, (igIntList *)self->_playerRamNoList,
                                (igVec3f *)nearFrom, &g_targetPosition, &g_targetDistanceSq, &g_targetRamNo);
    } else {
        facingFrom[0] = from[0];
        facingFrom[1] = from[1];
        facingFrom[2] = from[2];
        beTargetObj_FindFacing(self, (igVec3fList *)self->_playerPosList, (igIntList *)self->_playerRamNoList,
                               (igVec3f *)facingFrom, &g_targetPosition, &g_targetDistanceSq, &g_targetRamNo);
    }
    return 1;
}

extern "C" int beTargetObj_TargetEnemy(beTargetObj *self, float *from, int nearest)
{
    float nearFrom[4];
    float facingFrom[4];

    if (((igVec3fList *)self->_enemyPosList)->_count == 0) {
        beTargetObj_GatherPositions(self, (igVec3fList *)self->_enemyPosList, (igIntList *)0, ENEMY_2,
                                    GETMATRIX_ACTIVE);
        if (((igVec3fList *)self->_enemyPosList)->_count == 0) {
            return 0;
        }
    }
    if (nearest != 0) {
        nearFrom[0] = from[0];
        nearFrom[1] = from[1];
        nearFrom[2] = from[2];
        beTargetObj_FindNearest(self, (igVec3fList *)self->_enemyPosList, (igIntList *)0, (igVec3f *)nearFrom,
                                &g_targetPosition, &g_targetDistanceSq, &g_targetRamNo);
    } else {
        facingFrom[0] = from[0];
        facingFrom[1] = from[1];
        facingFrom[2] = from[2];
        beTargetObj_FindFacing(self, (igVec3fList *)self->_enemyPosList, (igIntList *)0, (igVec3f *)facingFrom,
                               &g_targetPosition, &g_targetDistanceSq, &g_targetRamNo);
    }
    return 1;
}

/* Targets a member of `group` ("PLAYER" or "ENEMY") as seen from `matrix`: the nearest one when
 * `mode` is "NEAR", otherwise the one most nearly ahead. */
extern "C" int beTargetObj_SelectTarget(float *matrix, const char *group, const char *mode)
{
    igVec3f origin;
    igVec3f playerFrom;
    igVec3f enemyFrom;
    int nearest;

    Matrix44_Copy(g_targetOriginMatrix.m, matrix);
    Matrix44_GetTranslation(matrix, (float *)&origin);
    g_targetOrigin.x = origin.x;
    g_targetOrigin.y = origin.y;
    g_targetOrigin.z = origin.z;
    g_targetOriginHeading = TARGET_HEADING_UNSET;
    nearest = strcmp(mode, NEAR_2) == 0;
    if (strcmp(group, PLAYER_5) == 0) {
        playerFrom.x = origin.x;
        playerFrom.y = origin.y;
        playerFrom.z = origin.z;
        return beTargetObj_TargetPlayer(g_targetObj, (float *)&playerFrom, nearest);
    }
    if (strcmp(group, ENEMY_2) == 0) {
        enemyFrom.x = origin.x;
        enemyFrom.y = origin.y;
        enemyFrom.z = origin.z;
        return beTargetObj_TargetEnemy(g_targetObj, (float *)&enemyFrom, nearest);
    }
    return 0;
}

/* Makes `position` the target as seen from `matrix`, with no RAM number. */
extern "C" int beTargetObj_SetTarget(float *matrix, float *position)
{
    float origin[3];
    float dx, dy, dz;

    Matrix44_GetTranslation(matrix, origin);
    g_targetOrigin.x = origin[0];
    g_targetOrigin.y = origin[1];
    g_targetOrigin.z = origin[2];
    Matrix44_Copy(g_targetOriginMatrix.m, matrix);
    g_targetOriginHeading = TARGET_HEADING_UNSET;
    g_targetPosition.x = position[0];
    g_targetPosition.y = position[1];
    g_targetPosition.z = position[2];
    dy = origin[1] - position[1];
    dx = origin[0] - position[0];
    dz = origin[2] - position[2];
    g_targetRamNo = 0;
    g_targetDistanceSq = dx * dx + dy * dy + dz * dz;
    return 1;
}

extern "C" igVec3f *beTargetObj_GetOrigin(void)
{
    return &g_targetOrigin;
}

/* The yaw of the origin matrix's forward axis, worked out on first use after each query. */
extern "C" float beTargetObj_GetOriginHeading(beTargetObj *self)
{
    float forward[4];

    if (g_targetOriginHeading == TARGET_HEADING_UNSET) {
        Vec3f_TransformDirection(forward, g_vec3ZAxis, g_targetOriginMatrix.m);
        g_targetOriginHeading = atan2f(forward[0], forward[2]);
    }
    return g_targetOriginHeading;
}

extern "C" igVec3f *beTargetObj_GetTargetPosition(void)
{
    return &g_targetPosition;
}

extern "C" float beTargetObj_GetTargetDistanceSq(void)
{
    return g_targetDistanceSq;
}

/* The target's bearing from the origin, plus `offset`. */
extern "C" float beTargetObj_GetTargetBearing(float offset)
{
    return offset + atan2f(g_targetPosition.x - g_targetOrigin.x, g_targetPosition.z - g_targetOrigin.z);
}

extern "C" int beTargetObj_GetTargetRamNo(void)
{
    return g_targetRamNo;
}

extern "C" int Gap__Bec__beTargetObj__vfunc_20(void)
{
    return g_beTargetObj_metaObject[0];
}

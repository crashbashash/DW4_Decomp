#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igobject_release.h"
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beHitLandModel.h"
#include "dw4/game/beHitLandModelInfo.h"
#include "dw4/game/beHitLandModelOrder.h"
#include "dw4/game/beHitLandModelTraversal.h"
#include "dw4/game/beHitLandResultData.h"
#include "dw4/game/beMessenger.h"
#include "dw4/core/igDataLists.h"
#include "dw4/scenegraph/igIntersectTraversal.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igProbe.h"
#include "dw4/scenegraph/igSwitch.h"
#include <math.h>
#include <string.h>
#include "dw4/core/igStringObj.h"
#include "dw4/support/emptyString.h"
#include "dw4/support/list-services.h"
#include "dw4/maths/igRay.h"
#include "dw4/core/igNamedObjectList.h"
#include "dw4/core/igStringObjList.h"

extern "C" igMetaObject *beHitLandModel_GetInfoMeta(void);
extern "C" void beHitLandModel_UpdateRam(void);
extern "C" igMetaObject *beHitLandModel_GetMeta(void);
extern "C" void beHitLandModel_UpdateBound(beHitLandModel *self, float *bound, float *value, int isMin);
extern "C" bool beHitLandModel_BoundsOverlapXZ(beHitLandModel *self, float *boundMax, float *rayMax, float *boundMin, float *rayMin);
extern "C" igMetaObject *beHitLandModelOrder_GetMeta(void);
extern "C" int beHitLandModel_OnMessage(beHitLandModel *self, beHitLandModelInfoRam *ram, beMessengerWork *work);
extern "C" void beHitLandModel_CheckWall(beHitLandModel *self);
extern "C" void beHitLandModel_CheckWallFull(beHitLandModel *self);
static void beHitLandModel_FindLand(beHitLandModel *self);

extern "C" void beHitLandModel_Prepare(beHitLandModel *self);
extern "C" char HITLANDMODEL[];
extern "C" void beHitLandModel_OnAddRam(beHitLandModel *self, int info, char *, int, int);
/* The intersect traversal's hit as the hit callback hands it over: the distance along the ray, the
 * hit point and the face normal (in the matrix's space until the order transforms it). */
struct HitRecord {
    int unknown0;
    int unknown4;
    int nodes;
    void *matrix;
    int unknown16;
    float distance;
    float point[3];
    float unknown36[3];
    igVec3f normal;
    int unknown60[3];
    HitRecord &operator=(const HitRecord &other);
};
struct ResultRecord { char header[16]; HitRecord hit; };
extern "C" void beHitLandModelOrder_AddHitResult(beHitLandModelOrder *self, HitRecord *hit);
extern "C" int beHitLandModel_HitProc(beHitLandModelTraversal *traversal, int unused, HitRecord *hit);
extern "C" void beHitLandModelOrder_AddRay(beHitLandModelOrder *self, int a1, int a2);
extern "C" void beHitLandModelOrder_Reset(beHitLandModelOrder *order);
extern "C" void beHitLandModel_TraceOrder(beHitLandModel *self, beHitLandModelOrder *order);


/* beHitLandModelOrder's virtual methods by vtable slot (slot 21 is beHitLandModelOrder_AddRay). */
class beHitLandModelOrderMethods {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20();
    virtual void AddRay(igVec3f *start, igVec3f *end);
    virtual void AddHitResult(HitRecord *hit);
};

/* beHitLandModelOrder::_hitdataList as the object list it is, with the list's inline accessors. */
struct HitResultList : igObjectList {
    int getCount() const { return _count; }
    beHitLandResultData *get(int index) const { return ((beHitLandResultData **)_data)[index]; }
};
typedef igSmartPointer<HitResultList> HitResultListRef;

int beHitLandModel_HitProc(beHitLandModelTraversal *traversal, int unused, HitRecord *hit) {
    ((beHitLandModelOrderMethods *)traversal->_order)->AddHitResult(hit);
    return 0;
}

void beHitLandModel_Prepare(beHitLandModel *self) {
    igObject *held;
    held = (igObject *)self->_order;
    if (held != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        IG_OBJECT_RELEASE(held);
        self->_order = 0;
    }
    held = (igObject *)self->_hitTraversal;
    if (held != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        IG_OBJECT_RELEASE(held);
        self->_hitTraversal = 0;
    }
    held = (igObject *)self->_probe;
    if (held != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        IG_OBJECT_RELEASE(held);
        self->_probe = 0;
    }
    self->_isHitWall = 1;
    igMatrix44f_MakeEulerRotation(self->_mat90, 0.0f, 1.5707964f, 0.0f);
}

igMetaObject *beHitLandModel_GetInfoMeta(void)
{
    return g_beHitLandModelInfo_metaObject;
}

void beHitLandModel_OnAddRam(beHitLandModel *self, int info, char *, int, int)
{
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, (beBaseInfoRam *)info, HITLANDMODEL, 0, -1);
}

void beHitLandModel_UpdateRam(void)
{
}

/* beMessenger_ResolveEnumValue values of the model's message names. */
enum HitLandModelMessage {
    MESSAGE_CHECKWALL, MESSAGE_CHECKWALLFULL, MESSAGE_CHECKLAND, MESSAGE_ONHIT, MESSAGE_OFFHIT
};

/* strcmp of a name against a string object's text, an unset string reading as empty. */
static inline int CompareStringObj(const char *name, igStringObj *string)
{
    const char *text = (const char *)string->_buffer;
    if (text == 0) text = g_stringObjEmptyText;
    return strcmp(name, text);
}

static inline const char *NamedObjectName(igNamedObject *object)
{
    return object->_name ? (const char *)object->_name : (const char *)emptyString;
}

/* Answers a message to one of the model's rams: the wall and land checks, or switching the check
 * switch's child of the sent name on or off. */
int beHitLandModel_OnMessage(beHitLandModel *self, beHitLandModelInfoRam *ram, beMessengerWork *work)
{
    beHitLandModelInfo *info;

    if (self->_order == 0) {
        int count = ((igObjectList *)self->_infoList)->_count;
        for (int i = 0; i < count; i++) {
            igObjectDispatchView *names = (igObjectDispatchView *)((beHitLandModelInfo **)((igObjectList *)self->_infoList)->_data)[i]->_nameList;
            if (names != 0) names->GetMeta();
        }
    }
    if (self->_order == 0) {
        int allocator = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igObject *old = (igObject *)self->_order;
        IG_OBJECT_RELEASE(old);
        self->_order = (int)beHitLandModelOrder_Create(allocator);
    }
    if (self->_hitTraversal == 0) {
        int allocator = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igObject *old = (igObject *)self->_hitTraversal;
        IG_OBJECT_RELEASE(old);
        self->_hitTraversal = (int)beHitLandModelTraversal_Create(allocator);
    }
    if (self->_probe == 0) {
        int allocator = (int)igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igObject *old = (igObject *)self->_probe;
        IG_OBJECT_RELEASE(old);
        self->_probe = (int)igProbe_Create(allocator);
    }
    info = (beHitLandModelInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beHitLandModel_GetMessageEnum(), (const char *)work->_message)) {
    case MESSAGE_CHECKWALL:
        if (self->_isHitWall) {
            beHitLandModel_CheckWall(self);
        } else {
            beMessenger_ClearBool((beMessenger *)self->_messenger);
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
        }
        break;
    case MESSAGE_CHECKWALLFULL:
        if (self->_isHitWall) {
            beHitLandModel_CheckWallFull(self);
        } else {
            beMessenger_ClearBool((beMessenger *)self->_messenger);
            beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
        }
        break;
    case MESSAGE_CHECKLAND:
        beHitLandModel_FindLand(self);
        break;
    /* matching construct: register-allocator tracer — i declared before count in each name loop gives retail's i and count registers */
    case MESSAGE_ONHIT:
        if (info->_nameList != 0) {
            if (g_igStringObjList_metaObject == ((igObjectDispatchView *)info->_nameList)->GetMeta()) {
                igStringObjList *names = (igStringObjList *)info->_nameList;
                int i;
                int count = names->_count;
                for (i = 0; i < count; i++) {
                    if (CompareStringObj((const char *)work->_infoName, ((igStringObj **)names->_data)[i]) == 0) {
                        igSwitch_EnableChild((igSwitch *)info->_checkSwitch, i);
                        break;
                    }
                }
            } else if (g_igNamedObjectList_metaObject == ((igObjectDispatchView *)info->_nameList)->GetMeta()) {
                igNamedObjectList *names = (igNamedObjectList *)info->_nameList;
                int i;
                int count = names->_count;
                for (i = 0; i < count; i++) {
                    if (strcmp((const char *)work->_infoName, NamedObjectName(((igNamedObject **)names->_data)[i])) == 0) {
                        igSwitch_EnableChild((igSwitch *)info->_checkSwitch, i);
                        break;
                    }
                }
            }
        }
        break;
    case MESSAGE_OFFHIT:
        if (info->_nameList != 0) {
            if (g_igStringObjList_metaObject == ((igObjectDispatchView *)info->_nameList)->GetMeta()) {
                igStringObjList *names = (igStringObjList *)info->_nameList;
                int i;
                int count = names->_count;
                for (i = 0; i < count; i++) {
                    if (CompareStringObj((const char *)work->_infoName, ((igStringObj **)names->_data)[i]) == 0) {
                        igSwitch_DisableChild((igSwitch *)info->_checkSwitch, i);
                        break;
                    }
                }
            } else if (g_igNamedObjectList_metaObject == ((igObjectDispatchView *)info->_nameList)->GetMeta()) {
                igNamedObjectList *names = (igNamedObjectList *)info->_nameList;
                int i;
                int count = names->_count;
                for (i = 0; i < count; i++) {
                    if (strcmp((const char *)work->_infoName, NamedObjectName(((igNamedObject **)names->_data)[i])) == 0) {
                        igSwitch_DisableChild((igSwitch *)info->_checkSwitch, i);
                        break;
                    }
                }
            }
        }
        break;
    default:
        beMessenger_ClearBool((beMessenger *)self->_messenger);
        beMessenger_AppendBool((beMessenger *)self->_messenger, 0);
        return 0;
    }
    return 1;
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static inline float Length(const igVec3f &v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/* Moves the point the distance along the direction. */
/* matching construct: hand search — the const distance makes each product load the direction before the point */
static inline void MoveAlong(igVec3f &point, const float distance, const igVec3f &direction)
{
    point.x += distance * direction.x;
    point.y += distance * direction.y;
    point.z += distance * direction.z;
}

static inline void Translate(igVec3f &point, const igVec3f &offset)
{
    point.x += offset.x;
    point.y += offset.y;
    point.z += offset.z;
}

/* Scales the vector to unit length. */
static inline void Normalize(igVec3f &v)
{
    float scale = 1.0f / Length(v);
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;
}

static inline float Dot(const igVec3f &a, const igVec3f &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/* The angle between two vectors. */
static inline float AngleBetween(const igVec3f &a, const igVec3f &b)
{
    float cosine = Dot(a, b) / (Length(a) * Length(b));
    return acosf(MIN(MAX(cosine, -1.0f), 1.0f));
}

static inline HitRecord *OrderHit(beHitLandModelOrder *order, int index)
{
    return &((ResultRecord *)((HitResultListRef &)order->_hitdataList)->get(index))->hit;
}

/* Checks the probe segment of 1.42 radii either side of the messenger's position along its direction
 * for walls, with two more segments beside it a radius away (int 1 set skips that check). On a hit it
 * moves the position back along the direction to the nearest wall the closer side probes find, then
 * probes sideways three quarters of the reach ahead and pushes the position off the nearest wall
 * along the wall's normal. Posts the hit's ram number and info name, the position and whether a wall
 * was hit. */
void beHitLandModel_CheckWall(beHitLandModel *self)
{
    float radius;
    float height;
    float reach;
    int kind;
    int skipPreCheck;
    bool hit;
    bool wallAhead;

    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0) return;
    if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) == 0) return;
    if (beMessenger_GetFloatCount((beMessenger *)self->_messenger) == 0) return;
    if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) return;
    igVec3f position = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
    igVec3f direction = beMessenger_GetVec3((beMessenger *)self->_messenger, 1);
    radius = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
    beMessenger_GetFloat((beMessenger *)self->_messenger, 1);
    height = beMessenger_GetFloat((beMessenger *)self->_messenger, 2);
    kind = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
    skipPreCheck = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
    beMessenger_ClearInt((beMessenger *)self->_messenger);
    hit = false;
    reach = 1.42f * radius;
    wallAhead = false;
    igVec3f start(position.x, height + position.y, position.z);
    igVec3f end(start);
    igVec3f side;
    Vec3f_TransformDirection(&side.x, &direction.x, self->_mat90);
    Normalize(side);
    {
        igVec3f offset(0.0f, 0.0f, 0.0f);
        MoveAlong(offset, reach, direction);
        Translate(end, offset);
    }
    {
        igVec3f offset(0.0f, 0.0f, 0.0f);
        MoveAlong(offset, -reach, direction);
        Translate(start, offset);
    }
    if (skipPreCheck == 0) {
        beHitLandModelOrder_Reset((beHitLandModelOrder *)self->_order);
        beHitLandModelOrder *order = (beHitLandModelOrder *)self->_order;
        order->_kind = kind & ~1;
        ((beHitLandModelOrderMethods *)order)->AddRay(&start, &end);
        igVec3f leftStart(start);
        igVec3f leftEnd(end);
        igVec3f rightStart(start);
        igVec3f rightEnd(end);
        {
            igVec3f offset(0.0f, 0.0f, 0.0f);
            MoveAlong(offset, reach, side);
            Translate(leftStart, offset);
            Translate(leftEnd, offset);
        }
        ((beHitLandModelOrderMethods *)order)->AddRay(&leftStart, &leftEnd);
        {
            igVec3f offset(0.0f, 0.0f, 0.0f);
            MoveAlong(offset, -reach, side);
            Translate(rightStart, offset);
            Translate(rightEnd, offset);
        }
        ((beHitLandModelOrderMethods *)order)->AddRay(&rightStart, &rightEnd);
        igVec3f max(leftStart);
        beHitLandModel_UpdateBound(self, &max.x, &rightStart.x, 0);
        beHitLandModel_UpdateBound(self, &max.x, &leftEnd.x, 0);
        beHitLandModel_UpdateBound(self, &max.x, &rightEnd.x, 0);
        beHitLandModel_UpdateBound(self, &max.z, &rightStart.z, 0);
        beHitLandModel_UpdateBound(self, &max.z, &leftEnd.z, 0);
        beHitLandModel_UpdateBound(self, &max.z, &rightEnd.z, 0);
        ((igVec3f *)order->_raymax)->set(max.x, position.y, max.z);
        igVec3f min(leftStart);
        beHitLandModel_UpdateBound(self, &min.x, &rightStart.x, 1);
        beHitLandModel_UpdateBound(self, &min.x, &leftEnd.x, 1);
        beHitLandModel_UpdateBound(self, &min.x, &rightEnd.x, 1);
        beHitLandModel_UpdateBound(self, &min.z, &rightStart.z, 1);
        beHitLandModel_UpdateBound(self, &min.z, &leftEnd.z, 1);
        beHitLandModel_UpdateBound(self, &min.z, &rightEnd.z, 1);
        ((igVec3f *)order->_raymin)->set(min.x, position.y, min.z);
        beHitLandModel_TraceOrder(self, order);
        if (order->_hitdataCount > 0) wallAhead = true;
    } else {
        wallAhead = true;
    }
    /* matching construct: hand search — the comparison with true is what keeps the andi/li/bne test */
    if (wallAhead == true) {
        beHitLandModelOrder_Reset((beHitLandModelOrder *)self->_order);
        beHitLandModelOrder *order = (beHitLandModelOrder *)self->_order;
        float probeLength = reach + reach;
        kind &= ~1;
        order->_kind = kind;
        ((beHitLandModelOrderMethods *)order)->AddRay(&start, &end);
        {
            igVec3f leftStart(start);
            igVec3f leftEnd(end);
            igVec3f rightStart(start);
            igVec3f rightEnd(end);
            float half = reach / 2.0f;
            {
                igVec3f offset(0.0f, 0.0f, 0.0f);
                MoveAlong(offset, half, side);
                Translate(leftStart, offset);
                Translate(leftEnd, offset);
            }
            ((beHitLandModelOrderMethods *)order)->AddRay(&leftStart, &leftEnd);
            {
                igVec3f offset(0.0f, 0.0f, 0.0f);
                MoveAlong(offset, -half, side);
                Translate(rightStart, offset);
                Translate(rightEnd, offset);
            }
            ((beHitLandModelOrderMethods *)order)->AddRay(&rightStart, &rightEnd);
            igVec3f max(leftStart);
            beHitLandModel_UpdateBound(self, &max.x, &rightStart.x, 0);
            beHitLandModel_UpdateBound(self, &max.x, &leftEnd.x, 0);
            beHitLandModel_UpdateBound(self, &max.x, &rightEnd.x, 0);
            beHitLandModel_UpdateBound(self, &max.z, &rightStart.z, 0);
            beHitLandModel_UpdateBound(self, &max.z, &leftEnd.z, 0);
            beHitLandModel_UpdateBound(self, &max.z, &rightEnd.z, 0);
            ((igVec3f *)order->_raymax)->set(max.x, position.y, max.z);
            igVec3f min(leftStart);
            beHitLandModel_UpdateBound(self, &min.x, &rightStart.x, 1);
            beHitLandModel_UpdateBound(self, &min.x, &leftEnd.x, 1);
            beHitLandModel_UpdateBound(self, &min.x, &rightEnd.x, 1);
            beHitLandModel_UpdateBound(self, &min.z, &rightStart.z, 1);
            beHitLandModel_UpdateBound(self, &min.z, &leftEnd.z, 1);
            beHitLandModel_UpdateBound(self, &min.z, &rightEnd.z, 1);
            ((igVec3f *)order->_raymin)->set(min.x, position.y, min.z);
            beHitLandModel_TraceOrder(self, order);
            int count = order->_hitdataCount;
            if (count > 0) {
                float nearest = 0.0f;
                int best = 0;
                for (int i = 0; i < count; i++) {
                    HitRecord *wall = OrderHit(order, i);
                    if (i == 0) {
                        nearest = wall->distance;
                    } else if (wall->distance < nearest) {
                        nearest = wall->distance;
                        best = i;
                    }
                }
                MoveAlong(position, -(probeLength - nearest), direction);
                beHitLandResultData *result = ((HitResultListRef &)order->_hitdataList)->get(best);
                const char *name = (const char *)result->_infoName;
                beMessenger_AppendInt((beMessenger *)self->_messenger, result->_ramNo);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)name);
                hit = true;
            }
        }
        /* matching construct: hand search — this probe's locals in their own scope give its order retail's register */
        {
            beHitLandModelOrder_Reset((beHitLandModelOrder *)self->_order);
            beHitLandModelOrder *order = (beHitLandModelOrder *)self->_order;
            order->_kind = kind;
            igVec3f centre(position.x, height + position.y, position.z);
            {
                igVec3f offset(0.0f, 0.0f, 0.0f);
                MoveAlong(offset, (3.0f * reach) / 4.0f, direction);
                Translate(centre, offset);
            }
            igVec3f left(centre);
            MoveAlong(left, reach, side);
            ((beHitLandModelOrderMethods *)order)->AddRay(&centre, &left);
            igVec3f right(centre);
            MoveAlong(right, -reach, side);
            ((beHitLandModelOrderMethods *)order)->AddRay(&centre, &right);
            igVec3f max(left);
            beHitLandModel_UpdateBound(self, &max.x, &right.x, 0);
            beHitLandModel_UpdateBound(self, &max.z, &right.z, 0);
            ((igVec3f *)order->_raymax)->set(max.x, position.y, max.z);
            igVec3f min(left);
            beHitLandModel_UpdateBound(self, &min.x, &right.x, 1);
            beHitLandModel_UpdateBound(self, &min.z, &right.z, 1);
            ((igVec3f *)order->_raymin)->set(min.x, position.y, min.z);
            beHitLandModel_TraceOrder(self, order);
            int count = order->_hitdataCount;
            int nearest = 0;
            if (count > 0) {
                for (int j = 1; j < count; j++) {
                    if (OrderHit(order, j)->distance < OrderHit(order, nearest)->distance) nearest = j;
                }
                HitRecord *wall = OrderHit(order, nearest);
                float push = (reach - wall->distance) * cosf(AngleBetween(wall->normal, wall->normal));
                MoveAlong(position, push, wall->normal);
                beHitLandResultData *result = ((HitResultListRef &)order->_hitdataList)->get(nearest);
                const char *name = (const char *)result->_infoName;
                beMessenger_AppendInt((beMessenger *)self->_messenger, result->_ramNo);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)name);
                hit = true;
            }
        }
    }
    beMessenger_ClearBool((beMessenger *)self->_messenger);
    beMessenger_ClearVec3((beMessenger *)self->_messenger);
    beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
    beMessenger_AppendBool((beMessenger *)self->_messenger, hit);
}

/* Casts eight horizontal rays 45 degrees apart, 3.5 radii long, from the messenger's position (2.15
 * radii when none hits), takes the nearest wall hit and pushes the position out of the wall along its
 * normal; posts the hit's ram number and info name, the position and whether a wall was hit. */
void beHitLandModel_CheckWallFull(beHitLandModel *self)
{
    float radius;
    float height;
    int kind;
    bool hit;

    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0) return;
    if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) == 0) return;
    if (beMessenger_GetFloatCount((beMessenger *)self->_messenger) == 0) return;
    if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) return;
    igVec3f position = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
    radius = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
    beMessenger_GetFloat((beMessenger *)self->_messenger, 1);
    height = beMessenger_GetFloat((beMessenger *)self->_messenger, 2);
    kind = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
    beMessenger_GetInt((beMessenger *)self->_messenger, 1);
    beMessenger_ClearInt((beMessenger *)self->_messenger);
    hit = false;
    {
        float reach = 3.5f * radius;
        beHitLandModelOrder_Reset((beHitLandModelOrder *)self->_order);
        beHitLandModelOrder *order = (beHitLandModelOrder *)self->_order;
        kind &= ~1;
        order->_kind = kind | 0x1000;
        igVec3f direction(1.0f, 0.0f, 0.0f);
        igMatrix44f rotation;
        igMatrix44f_MakeEulerRotation(&rotation, 0.0f, 0.7853982f, 0.0f);
        igVec3f centre(position.x, height + position.y, position.z);
        igVec3f max(centre);
        igVec3f min(centre);
        for (int i = 0; i < 8; i++) {
            igVec3f end(centre);
            MoveAlong(end, reach, direction);
            ((beHitLandModelOrderMethods *)order)->AddRay(&centre, &end);
            beHitLandModel_UpdateBound(self, &max.x, &end.x, 0);
            beHitLandModel_UpdateBound(self, &max.z, &end.z, 0);
            beHitLandModel_UpdateBound(self, &min.x, &end.x, 1);
            beHitLandModel_UpdateBound(self, &min.z, &end.z, 1);
            if (i >= 7) break;
            Vec3f_TransformDirection(&direction.x, (const float *)&direction.x, (const float *)&rotation);
            Normalize(direction);
        }
        ((igVec3f *)order->_raymax)->set(max.x, position.y, max.z);
        ((igVec3f *)order->_raymin)->set(min.x, position.y, min.z);
        beHitLandModel_TraceOrder(self, order);
        int count = order->_hitdataCount;
        int nearest = 0;
        if (count > 0) {
            for (int j = 1; j < count; j++) {
                if (OrderHit(order, j)->distance < OrderHit(order, nearest)->distance) nearest = j;
            }
            HitRecord *wall = OrderHit(order, nearest);
            float push = (reach - wall->distance) * cosf(AngleBetween(wall->normal, wall->normal));
            MoveAlong(position, push, wall->normal);
            beHitLandResultData *result = ((HitResultListRef &)order->_hitdataList)->get(nearest);
            const char *name = (const char *)result->_infoName;
            beMessenger_AppendInt((beMessenger *)self->_messenger, result->_ramNo);
            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)name);
            hit = true;
        }
    }
    /* matching construct: hand search — the comparison with false is what keeps the lbu/move test */
    if (hit == false) {
        float reach = 2.15f * radius;
        beHitLandModelOrder_Reset((beHitLandModelOrder *)self->_order);
        beHitLandModelOrder *order = (beHitLandModelOrder *)self->_order;
        order->_kind = kind;
        igVec3f direction(1.0f, 0.0f, 0.0f);
        igMatrix44f rotation;
        igMatrix44f_MakeEulerRotation(&rotation, 0.0f, 0.7853982f, 0.0f);
        igVec3f centre(position.x, height + position.y, position.z);
        igVec3f max(centre);
        igVec3f min(centre);
        for (int i = 0; i < 8; i++) {
            igVec3f end(centre);
            MoveAlong(end, reach, direction);
            ((beHitLandModelOrderMethods *)order)->AddRay(&centre, &end);
            beHitLandModel_UpdateBound(self, &max.x, &end.x, 0);
            beHitLandModel_UpdateBound(self, &max.z, &end.z, 0);
            beHitLandModel_UpdateBound(self, &min.x, &end.x, 1);
            beHitLandModel_UpdateBound(self, &min.z, &end.z, 1);
            if (i >= 7) break;
            Vec3f_TransformDirection(&direction.x, (const float *)&direction.x, (const float *)&rotation);
            Normalize(direction);
        }
        ((igVec3f *)order->_raymax)->set(max.x, position.y, max.z);
        ((igVec3f *)order->_raymin)->set(min.x, position.y, min.z);
        beHitLandModel_TraceOrder(self, order);
        int count = order->_hitdataCount;
        int nearest = 0;
        if (count > 0) {
            for (int j = 1; j < count; j++) {
                if (OrderHit(order, j)->distance < OrderHit(order, nearest)->distance) nearest = j;
            }
            HitRecord *wall = OrderHit(order, nearest);
            float push = (reach - wall->distance) * cosf(AngleBetween(wall->normal, wall->normal));
            MoveAlong(position, push, wall->normal);
            beHitLandResultData *result = ((HitResultListRef &)order->_hitdataList)->get(nearest);
            const char *name = (const char *)result->_infoName;
            beMessenger_AppendInt((beMessenger *)self->_messenger, result->_ramNo);
            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)name);
            hit = true;
        }
    }
    beMessenger_ClearBool((beMessenger *)self->_messenger);
    beMessenger_ClearVec3((beMessenger *)self->_messenger);
    beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
    beMessenger_AppendBool((beMessenger *)self->_messenger, hit);
}

/* Height of the landing point of the order's index-th hit. */
static inline float HitHeight(beHitLandModelOrder *order, int index)
{
    return ((ResultRecord *)((HitResultListRef &)order->_hitdataList)->get(index))->hit.point[1];
}

/* Casts four vertical probe rays at the corners of the square of half-width radius around the
 * messenger's position, picks the landing hit (the highest one inside the up/down window, else the
 * highest below, else the lowest) and posts the result back to the messenger. */
static void beHitLandModel_FindLand(beHitLandModel *self)
{
    bool inWindow;
    bool grounded;
    bool found;
    float radius;
    float up;
    float down;
    float maxX;
    float minX;
    float maxZ;
    float minZ;
    beHitLandModelOrder *order;
    int count;

    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0) return;
    if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) == 0) return;
    if (beMessenger_GetFloatCount((beMessenger *)self->_messenger) == 0) return;
    igVec3f position = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
    igVec3f start;
    igVec3f end;
    radius = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
    up = beMessenger_GetFloat((beMessenger *)self->_messenger, 1);
    down = beMessenger_GetFloat((beMessenger *)self->_messenger, 2);
    inWindow = false;
    grounded = false;
    beHitLandModelOrder_Reset((beHitLandModelOrder *)self->_order);
    order = (beHitLandModelOrder *)self->_order;
    maxX = radius + position.x;
    maxZ = radius + position.z;
    minX = position.x - radius;
    minZ = position.z - radius;

    start.x = maxX; start.y = 1000.0f; start.z = maxZ;
    end.x = maxX; end.y = -100.0f; end.z = maxZ;
    ((beHitLandModelOrderMethods *)order)->AddRay(&start, &end);
    start.x = minX; start.y = 1000.0f; start.z = maxZ;
    end.x = minX; end.y = -100.0f; end.z = maxZ;
    ((beHitLandModelOrderMethods *)order)->AddRay(&start, &end);
    start.x = maxX; start.y = 1000.0f; start.z = minZ;
    end.x = maxX; end.y = -100.0f; end.z = minZ;
    ((beHitLandModelOrderMethods *)order)->AddRay(&start, &end);
    start.x = minX; start.y = 1000.0f; start.z = minZ;
    end.x = minX; end.y = -100.0f; end.z = minZ;
    ((beHitLandModelOrderMethods *)order)->AddRay(&start, &end);

    start.x = maxX; start.y = 1000.0f; start.z = maxZ;
    *(igVec3f *)order->_raymax = start;
    end.x = minX; end.y = -100.0f; end.z = minZ;
    *(igVec3f *)order->_raymin = end;
    order->_kind = 1;
    beHitLandModel_TraceOrder(self, order);

    count = order->_hitdataCount;
    if (count > 0) {
        bool first = true;
        int best = 0;
        float bestHeight = 0.0f;
        float bestDistance = bestHeight;
        beHitLandResultData *result;
        const char *name;

        for (int i = 0; i < count; i++) {
            if (up + HitHeight(order, i) > position.y && HitHeight(order, i) - down < position.y) {
                if (first) {
                    bestDistance = HitHeight(order, i) - position.y;
                    first = false;
                    best = i;
                    bestHeight = HitHeight(order, i);
                } else {
                    float distance = HitHeight(order, i) - position.y;
                    if (distance > bestDistance) {
                        bestHeight = HitHeight(order, i);
                        best = i;
                        bestDistance = distance;
                    }
                }
            }
        }
        if (first) {
            for (int i = 0; i < count; i++) {
                if (HitHeight(order, i) < position.y) {
                    if (first) {
                        bestDistance = position.y - HitHeight(order, i);
                        first = false;
                        best = i;
                        bestHeight = HitHeight(order, i);
                    } else if (position.y - HitHeight(order, i) < bestDistance) {
                        bestHeight = HitHeight(order, i);
                        best = i;
                        bestDistance = position.y - HitHeight(order, i);
                    }
                }
            }
            if (first) {
                for (int i = 0; i < count; i++) {
                    HitRecord *hit = &((ResultRecord *)((HitResultListRef &)order->_hitdataList)->get(i))->hit;
                    if (i == 0) {
                        bestHeight = hit->point[1];
                        best = i;
                        bestDistance = bestHeight;
                    } else if (hit->point[1] <= bestDistance) {
                        bestHeight = hit->point[1];
                        best = i;
                        bestDistance = hit->point[1];
                    }
                }
            }
        }
        if (bestHeight + up > position.y && bestHeight - down < position.y) {
            inWindow = true;
        } else {
            inWindow = false;
        }
        if (position.y - bestHeight <= 0.0f) {
            grounded = true;
        } else {
            grounded = false;
        }
        position.y = bestHeight;
        beMessenger_ClearInt((beMessenger *)self->_messenger);
        result = ((HitResultListRef &)order->_hitdataList)->get(best);
        name = (const char *)result->_infoName;
        beMessenger_AppendInt((beMessenger *)self->_messenger, result->_ramNo);
        beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)name);
        found = true;
    } else {
        position.y = -1.0f;
        found = false;
    }
    beMessenger_ClearBool((beMessenger *)self->_messenger);
    beMessenger_ClearVec3((beMessenger *)self->_messenger);
    beMessenger_AppendBool((beMessenger *)self->_messenger, inWindow);
    beMessenger_AppendBool((beMessenger *)self->_messenger, grounded);
    beMessenger_AppendBool((beMessenger *)self->_messenger, found);
    beMessenger_AppendVec3((beMessenger *)self->_messenger, position);
}

void beHitLandModel_UpdateBound(beHitLandModel *self, float *bound, float *value, int isMin) {
    float b;
    float a;
    b = *value;
    a = *bound;
    if (a < b) {
        if (isMin == 0) {
            *bound = b;
        }
    } else if (!(a <= b) && (isMin == 1)) {
        *bound = b;
    }
}

bool beHitLandModel_BoundsOverlapXZ(beHitLandModel *self, float *boundMax, float *rayMax, float *boundMin, float *rayMin) {
    bool overlaps = false;
    if (!(boundMax[0] < rayMin[0]) && (boundMin[0] <= rayMax[0]) && !(boundMax[2] < rayMin[2]) && (boundMin[2] <= rayMax[2])) {
        overlaps = true;
    }
    return overlaps;
}

/* An int list with its inline count. */
struct IntList : igIntList {
    int getCount() const { return _count; }
    void setCount(int count) {
        if (count <= _capacity) {
            _count = count;
        } else {
            List_Resize(this, count, 4);
        }
    }
};

/* Whether the switch's index-th child is on. */
static inline bool IsChildOn(igSwitch *node, int index)
{
    /* matching construct: hand search — `? true : false` keeps the bool (sltu) ahead of the branch; `!= 0` folds it */
    return ((1 << (index & 31)) & ((unsigned *)((igBitMask *)node->_childMask)->_data)[(unsigned)index >> 5]) ? true : false;
}

/* The model's check-switch children as the hit-land traversal visits them (slot 23 of its vtable). */
class TraversalMethods {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual void traverse(void *node);
};

/* Runs the order's rays through the check switch of every info whose kind the order asks for,
 * visiting only the children whose bounds overlap the rays' XZ extent; the hit callback records
 * the hits into the order. */
void beHitLandModel_TraceOrder(beHitLandModel *self, beHitLandModelOrder *order)
{
    int rayCount = order->_rayCount;
    if (rayCount > 0) {
        igProbe *probe = (igProbe *)self->_probe;
        ObjectList_ResizeRetained((igTDataList<igObject *> *)probe->_rays, 0);
        ((IntList *)probe->_intersectFaceType)->setCount(0);
        for (int i = 0; i < rayCount; i++) {
            igProbe *target = (igProbe *)self->_probe;
            ObjectList_AppendRetained((igObjectList *)target->_rays, (igObject *)(((igRay **)((igObjectList *)order->_rayList)->_data)[i]));
            /* matching construct: register-allocator tracer — n declared before faces gives faces s1 and n s2 */
            int n;
            IntList *faces = (IntList *)target->_intersectFaceType;
            n = faces->_count;
            if (n < faces->_capacity) {
                faces->_count = faces->getCount() + 1;
            } else {
                List_Resize(faces, n + 1, 4);
            }
            ((int *)faces->_data)[n] = 0;
        }
        igIntersectTraversal_ResetStacks((igIntersectTraversal *)self->_hitTraversal);
        ((beHitLandModelTraversal *)self->_hitTraversal)->_mode = 0;
        {
            beHitLandModelTraversal *traversal = (beHitLandModelTraversal *)self->_hitTraversal;
            igObject *old;
            if (order != 0) order->_refCount = order->_refCount + 1;
            old = (igObject *)traversal->_order;
            IG_OBJECT_RELEASE(old);
            traversal->_order = (int)order;
        }
        {
            igProbe *probe = (igProbe *)self->_probe;
            beHitLandModelTraversal *traversal = (beHitLandModelTraversal *)self->_hitTraversal;
            igObject *old;
            if (probe != 0) probe->_refCount = probe->_refCount + 1;
            old = (igObject *)traversal->_probe;
            IG_OBJECT_RELEASE(old);
            traversal->_probe = (int)probe;
        }
        ((beHitLandModelTraversal *)self->_hitTraversal)->_hitProc = (int)beHitLandModel_HitProc;
        ((beHitLandModelTraversal *)self->_hitTraversal)->_mode |= 4;
        igVec3f rayMax(*(igVec3f *)order->_raymax);
        igVec3f rayMin(*(igVec3f *)order->_raymin);
        /* matching construct: hand search — kinds declared before infoCount orders their two spill slots */
        int kinds;
        int infoCount = ((igObjectList *)self->_infoList)->_count;
        kinds = order->_kind & 0x1FF;
        for (int i = 0; i < infoCount; i++) {
            beHitLandModelInfo *info = ((beHitLandModelInfo **)((igObjectList *)self->_infoList)->_data)[i];
            const char *name = info->_name ? (const char *)info->_name : (const char *)emptyString;
            const char *token;
            const char *old;
            if (g_stringPool == 0) {
                void *pool = StringPool_Allocate(16);
                if (pool != 0) pool = StringPool_Construct((StringPool *)pool);
                g_stringPool = (StringPool *)pool;
            }
            token = StringPool_Intern(g_stringPool, name);
            old = (const char *)order->_infoName;
            if (old != 0) {
                int *header = (int *)old - 2;
                int count = ((int *)old)[-1] - 1;
                ((int *)old)[-1] = count;
                if (count == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
            }
            order->_infoName = (int)token;
            int kind = info->_kind;
            if ((kinds & kind) && (!(kind & 0x800) || !(order->_kind & 0x800)) && (!(order->_kind & 0x1000) || (kind & 0x1000))) {
                igSwitch *parts = (igSwitch *)info->_checkSwitch;
                int partCount = parts->_childList ? ((igObjectList *)parts->_childList)->_count : 0;
                if (kind & 0x400) {
                    for (int j = 0; j < partCount; j++) {
                        if (IsChildOn(parts, j)) {
                            order->_ramNo = j;
                            beCopyTransform *part = ((beCopyTransform **)((igObjectList *)parts->_childList)->_data)[j];
                            igVec3f boundMax;
                            igVec3f boundMin;
                            igVec3f translation;
                            igMatrix44f_Copy(part->_m, ((igTransform *)part->_srcTransform)->_m);
                            igMatrix44f_GetTranslation(part->_m, (float *)&translation);
                            igAABox *bound = (igAABox *)((igNode **)((igObjectList *)part->_childList)->_data)[0]->_bound;
                            boundMax = *(igVec3f *)bound->_max;
                            boundMin = *(igVec3f *)bound->_min;
                            Translate(boundMax, translation);
                            Translate(boundMin, translation);
                            if (beHitLandModel_BoundsOverlapXZ(self, (float *)&boundMax, (float *)&rayMax, (float *)&boundMin, (float *)&rayMin)) {
                                ((TraversalMethods *)self->_hitTraversal)->traverse(part);
                            }
                        }
                    }
                } else {
                    for (int j = 0; j < partCount; j++) {
                        if (IsChildOn(parts, j)) {
                            order->_ramNo = j;
                            igNode *part = ((igNode **)((igObjectList *)parts->_childList)->_data)[j];
                            igAABox *bound = (igAABox *)part->_bound;
                            if (bound != 0) {
                                if (beHitLandModel_BoundsOverlapXZ(self, bound->_max, (float *)&rayMax, bound->_min, (float *)&rayMin)) {
                                    ((TraversalMethods *)self->_hitTraversal)->traverse(((igNode **)((igObjectList *)parts->_childList)->_data)[j]);
                                }
                            } else {
                                ((TraversalMethods *)self->_hitTraversal)->traverse(part);
                            }
                        }
                    }
                }
            }
        }
    }
}

void beHitLandModelOrder_AddHitResult(beHitLandModelOrder *self, HitRecord *hit) {
    /* matching construct: declaration-order sweep (24 orders) — this order puts self in s1 and the result in s2 */
    const char *name;
    const char *token;
    beHitLandResultData *result;
    const char *old;
    if (self->_hitdataCount >= ((igObjectList *)self->_hitdataList)->_count) {
        void *alloc = igObject_GetAllocator(self);
        alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igSmartPointer<beHitLandResultData> created(beHitLandResultData_Create((int)alloc));
        ObjectList_AppendRetained((igObjectList *)self->_hitdataList, (igObject *)created);
    }
    Vec3f_TransformDirection(&hit->normal.x, (const float *)&hit->normal.x, (const float *)hit->matrix);
    ((ResultRecord *)((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount])->hit = *hit;
    result = ((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount];
    name = (const char *)self->_infoName;
    if (g_stringPool == 0) {
        void *pool = StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct((StringPool *)pool);
        g_stringPool = (StringPool *)pool;
    }
    token = StringPool_Intern(g_stringPool, name);
    old = (const char *)result->_infoName;
    if (old != 0) {
        int *header = (int *)old - 2;
        int count = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = count;
        if (count == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
    }
    result->_infoName = (int)token;
    ((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount]->_ramNo = self->_ramNo;
    self->_hitdataCount++;
}

HitRecord &HitRecord::operator=(const HitRecord &other) {
    unknown0 = other.unknown0;
    unknown4 = other.unknown4;
    nodes = other.nodes;
    matrix = other.matrix;
    unknown16 = other.unknown16;
    distance = other.distance;
    point[0] = other.point[0];
    point[1] = other.point[1];
    point[2] = other.point[2];
    unknown36[0] = other.unknown36[0];
    unknown36[1] = other.unknown36[1];
    unknown36[2] = other.unknown36[2];
    normal.x = other.normal.x;
    normal.y = other.normal.y;
    normal.z = other.normal.z;
    unknown60[0] = other.unknown60[0];
    unknown60[1] = other.unknown60[1];
    unknown60[2] = other.unknown60[2];
    return *this;
}

/* Owning stack reference to the newly created ray, released on scope exit (reference count in the
 * low 23 bits of _refCount). */

void beHitLandModelOrder_AddRay(beHitLandModelOrder *self, int a1, int a2) {
    if (self->_rayCount >= ((igRayList *)self->_rayList)->_count) {
        int a = ((int)igObject_GetAllocator(self));
        igSmartPointer<igObject> ray(igRay_CreateInstance(g_useOwnerAllocator != 0 ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1))));
        /* matching construct: the (void *)(long) cast fixes the argument evaluation order of the append */
        ObjectList_AppendRetained((igObjectList *)((void *)(long)self->_rayList), ray.p);
    }
    igRay_SetFromPoints((igRay *)(((int *)((igRayList *)self->_rayList)->_data)[self->_rayCount]), (const float *)a1, (const float *)a2);
    self->_rayCount = self->_rayCount + 1;
}

void beHitLandModelOrder_Reset(beHitLandModelOrder *order) {
    order->_kind = 0;
    order->_rayCount = 0;
    order->_hitdataCount = 0;
}

igMetaObject *beHitLandModelOrder_GetMeta(void)
{
    return g_beHitLandModelOrder_metaObject;
}

igMetaObject *beHitLandModel_GetMeta(void)
{
    return g_beHitLandModel_metaObject;
}

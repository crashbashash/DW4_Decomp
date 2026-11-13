#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int FUN_00386030(void *arg0, int arg1, int arg2);
extern "C" int igMatrix44f_MakeEulerRotation(void *, float, float, float);
extern "C" int Gap__Bec__beHitLandModel__vfunc_30(void);
extern "C" void Gap__Bec__beHitLandModel__vfunc_31(void);
extern "C" int Gap__Bec__beHitLandModel__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" void FUN_00388590(int arg0, float *arg1, float *arg2, int arg3);
extern "C" bool FUN_003885e0(int arg0, float *arg1, float *arg2, float *arg3, float *arg4);
extern "C" void Vec3f_TransformDirection(float *, float *, void *);
extern "C" void *StringPool_Allocate(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" void ObjectList_AppendRetained(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" void * igObject_GetAllocator(...);
extern "C" void *FUN_00388e60(void *arg0, void *arg1);
extern "C" int igRay_SetFromPoints(int, int, int);
extern "C" int Gap__Bec__beHitLandModelOrder__vfunc_20(void);
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
typedef struct { char vtable[4]; int refs; } RefCountedObject;
extern "C" void Gap__Bec__beHitLandModel__vfunc_32(beHitLandModel *arg0);
extern "C" int g_beHitLandModelInfo_metaObject[4];
extern "C" int g_beHitLandModel_metaObject[4];
extern "C" char HITLANDMODEL[];
extern "C" void Gap__Bec__beHitLandModel__vfunc_29(beHitLandModel * p0, int p1, char * p2, int p3, int p4);
extern "C" beHitLandResultData *FUN_0035e400(void *);
extern "C" void *g_stringPool[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
struct HitRecord { char pad[12]; void *matrix; char pad16[8]; float point[3]; char pad36[12]; float position[3]; char pad60[12]; };
struct ResultRecord { char header[16]; HitRecord hit; };
extern "C" void Gap__Bec__beHitLandModelOrder__vfunc_22(beHitLandModelOrder *self, HitRecord *hit);
extern "C" igObject *FUN_00188220(int);
extern "C" void Gap__Bec__beHitLandModelOrder__vfunc_21(beHitLandModelOrder *self, int a1, int a2);
extern "C" void beHitLandModelOrder_Reset(beHitLandModelOrder *order);
extern "C" int g_beHitLandModelOrder_metaObject[4];
#include "dw4/igVec3f.h"
extern "C" int beMessenger_GetBoolCount(int messenger);
extern "C" int beMessenger_GetVec3Count(int messenger);
extern "C" int beMessenger_GetFloatCount(int messenger);
extern "C" void beMessenger_GetVec3(igVec3f *out, int messenger, int index);
extern "C" float beMessenger_GetFloat(int messenger, int index);
extern "C" void beMessenger_ClearInt(int messenger);
extern "C" void beMessenger_ClearBool(int messenger);
extern "C" void beMessenger_ClearVec3(int messenger);
extern "C" void beMessenger_AppendInt(int messenger, int value);
extern "C" void beMessenger_AppendString(int messenger, int text);
extern "C" void beMessenger_AppendBool(int messenger, unsigned char value);
extern "C" void beMessenger_AppendVec3(int messenger, igVec3f value);
extern "C" void beHitLandModel_TraceOrder(beHitLandModel *self, beHitLandModelOrder *order);

/* beHitLandModelOrder's virtual methods by vtable slot (slot 21 is Gap__Bec__beHitLandModelOrder__vfunc_21). */
class beHitLandModelOrderMethods {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20();
    virtual void AddRay(igVec3f *start, igVec3f *end);
};

/* beHitLandModelOrder::_hitdataList as the object list it is, with the list's inline accessors. */
struct HitResultList : igObjectList {
    int getCount() const { return _count; }
    beHitLandResultData *get(int index) const { return ((beHitLandResultData **)_data)[index]; }
};
typedef igSmartPointer<HitResultList> HitResultListRef;

int FUN_00386030(void *arg0, int arg1, int arg2) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 64));
    ((DW4VC_96_1 *)(temp_a0))->vX((int)(arg2));
    return 0;
}

void Gap__Bec__beHitLandModel__vfunc_32(beHitLandModel *arg0) {
    RefCountedObject *t;
    t = (RefCountedObject *)arg0->_order;
    if (t != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_order = 0;
    }
    t = (RefCountedObject *)arg0->_hitTraversal;
    if (t != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_hitTraversal = 0;
    }
    t = (RefCountedObject *)arg0->_probe;
    if (t != 0) {
        /* matching construct: redundant inner null test is present in the retail code */
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_probe = 0;
    }
    arg0->_isHitWall = 1;
    igMatrix44f_MakeEulerRotation((char *)arg0 + 0x30, 0.0f, 1.5707964f, 0.0f);
}

int Gap__Bec__beHitLandModel__vfunc_30(void)
{
    return g_beHitLandModelInfo_metaObject[0];
}

void Gap__Bec__beHitLandModel__vfunc_29(beHitLandModel * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, HITLANDMODEL, 0, -1);
}

void Gap__Bec__beHitLandModel__vfunc_31(void)
{
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
    igVec3f position;
    igVec3f start;
    igVec3f end;
    float radius;
    float up;
    float down;
    float maxX;
    float minX;
    float maxZ;
    float minZ;
    beHitLandModelOrder *order;
    int count;

    if (beMessenger_GetBoolCount(self->_messenger) != 0) return;
    if (beMessenger_GetVec3Count(self->_messenger) == 0) return;
    if (beMessenger_GetFloatCount(self->_messenger) == 0) return;
    beMessenger_GetVec3(&position, self->_messenger, 0);
    radius = beMessenger_GetFloat(self->_messenger, 0);
    up = beMessenger_GetFloat(self->_messenger, 1);
    down = beMessenger_GetFloat(self->_messenger, 2);
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
        beMessenger_ClearInt(self->_messenger);
        result = ((HitResultListRef &)order->_hitdataList)->get(best);
        name = (const char *)result->_infoName;
        beMessenger_AppendInt(self->_messenger, result->_ramNo);
        beMessenger_AppendString(self->_messenger, (int)name);
        found = true;
    } else {
        position.y = -1.0f;
        found = false;
    }
    beMessenger_ClearBool(self->_messenger);
    beMessenger_ClearVec3(self->_messenger);
    beMessenger_AppendBool(self->_messenger, inWindow);
    beMessenger_AppendBool(self->_messenger, grounded);
    beMessenger_AppendBool(self->_messenger, found);
    beMessenger_AppendVec3(self->_messenger, position);
}

void FUN_00388590(int arg0, float *arg1, float *arg2, int arg3) {
    float b;
    float a;
    b = *arg2;
    a = *arg1;
    if (a < b) {
        if (arg3 == 0) {
            *arg1 = b;
        }
    } else if (!(a <= b) && (arg3 == 1)) {
        *arg1 = b;
    }
}

bool FUN_003885e0(int arg0, float *arg1, float *arg2, float *arg3, float *arg4) {
    bool r = false;
    if (!(arg1[0] < arg4[0]) && (arg3[0] <= arg2[0]) && !(arg1[2] < arg4[2]) && (arg3[2] <= arg2[2])) {
        r = true;
    }
    return r;
}

void Gap__Bec__beHitLandModelOrder__vfunc_22(beHitLandModelOrder *self, HitRecord *hit) {
    /* matching construct: declaration-order sweep (24 orders) — this order puts self in s1 and the result in s2 */
    const char *name;
    const char *token;
    beHitLandResultData *result;
    const char *old;
    if (self->_hitdataCount >= ((igObjectList *)self->_hitdataList)->_count) {
        void *alloc = igObject_GetAllocator(self);
        alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igSmartPointer<beHitLandResultData> created(FUN_0035e400(alloc));
        ObjectList_AppendRetained(self->_hitdataList, (beHitLandResultData *)created);
    }
    Vec3f_TransformDirection(hit->position, hit->position, hit->matrix);
    FUN_00388e60(&((ResultRecord *)((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount])->hit, hit);
    result = ((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount];
    name = (const char *)self->_infoName;
    if (g_stringPool[0] == 0) {
        void *pool = StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    token = StringPool_Intern(g_stringPool[0], name);
    old = (const char *)result->_infoName;
    if (old != 0) {
        int *header = (int *)old - 2;
        int count = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = count;
        if (count == 0) StringChunk_ReleaseHeader(*header, header);
    }
    result->_infoName = (int)token;
    ((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount]->_ramNo = self->_ramNo;
    self->_hitdataCount++;
}

void *FUN_00388e60(void *arg0, void *arg1) {
    *(int *)((char *)(arg0) + 0) = (int)((int) *(int *)((char *)(arg1) + 0));
    *(int *)((char *)(arg0) + 4) = (int)((int) *(int *)((char *)(arg1) + 4));
    *(int *)((char *)(arg0) + 8) = (int)((int) *(int *)((char *)(arg1) + 8));
    *(int *)((char *)(arg0) + 12) = (int)((int) *(int *)((char *)(arg1) + 12));
    *(int *)((char *)(arg0) + 16) = (int)((int) *(int *)((char *)(arg1) + 16));
    *(float *)((char *)(arg0) + 20) = (float) *(float *)((char *)(arg1) + 20);
    *(float *)((char *)(arg0) + 24) = (float) *(float *)((char *)(arg1) + 24);
    *(float *)((char *)(arg0) + 28) = (float) *(float *)((char *)(arg1) + 28);
    *(float *)((char *)(arg0) + 32) = (float) *(float *)((char *)(arg1) + 32);
    *(float *)((char *)(arg0) + 36) = (float) *(float *)((char *)(arg1) + 36);
    *(float *)((char *)(arg0) + 40) = (float) *(float *)((char *)(arg1) + 40);
    *(float *)((char *)(arg0) + 44) = (float) *(float *)((char *)(arg1) + 44);
    *(float *)((char *)(arg0) + 48) = (float) *(float *)((char *)(arg1) + 48);
    *(float *)((char *)(arg0) + 52) = (float) *(float *)((char *)(arg1) + 52);
    *(float *)((char *)(arg0) + 56) = (float) *(float *)((char *)(arg1) + 56);
    *(int *)((char *)(arg0) + 60) = (int)((int) *(int *)((char *)(arg1) + 60));
    *(int *)((char *)(arg0) + 64) = (int)((int) *(int *)((char *)(arg1) + 64));
    *(int *)((char *)(arg0) + 68) = (int)((int) *(int *)((char *)(arg1) + 68));
    return arg0;
}

/* Owning stack reference to the newly created ray, released on scope exit (reference count in the
 * low 23 bits of _refCount). */

void Gap__Bec__beHitLandModelOrder__vfunc_21(beHitLandModelOrder *self, int a1, int a2) {
    if (self->_rayCount >= ((igRayList *)self->_rayList)->_count) {
        int a = ((int)igObject_GetAllocator(self));
        igSmartPointer<igObject> ray(FUN_00188220(g_useOwnerAllocator != 0 ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]))));
        /* matching construct: the (void *)(long) cast fixes the argument evaluation order of the append */
        ObjectList_AppendRetained((void *)(long)self->_rayList, ray.p);
    }
    igRay_SetFromPoints(((int *)((igRayList *)self->_rayList)->_data)[self->_rayCount], a1, a2);
    self->_rayCount = self->_rayCount + 1;
}

void beHitLandModelOrder_Reset(beHitLandModelOrder *order) {
    order->_kind = 0;
    order->_rayCount = 0;
    order->_hitdataCount = 0;
}

int Gap__Bec__beHitLandModelOrder__vfunc_20(void)
{
    return g_beHitLandModelOrder_metaObject[0];
}

int Gap__Bec__beHitLandModel__vfunc_20(void)
{
    return g_beHitLandModel_metaObject[0];
}


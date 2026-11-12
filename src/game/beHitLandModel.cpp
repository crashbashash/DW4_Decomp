#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int FUN_00386030(void *arg0, int arg1, int arg2);
extern "C" int FUN_00190ed0(void *, float, float, float);
extern "C" int Gap__Bec__beHitLandModel__vfunc_30(void);
extern "C" void Gap__Bec__beHitLandModel__vfunc_31(void);
extern "C" int Gap__Bec__beHitLandModel__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" void FUN_00388590(int arg0, float *arg1, float *arg2, int arg3);
extern "C" bool FUN_003885e0(int arg0, float *arg1, float *arg2, float *arg3, float *arg4);
extern "C" void FUN_00192f50(float *, float *, void *);
extern "C" void *FUN_002eb010(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void StringChunk_ReleaseHeader(int, int *);
extern "C" void ObjectList_AppendRetained(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" void * igObject_GetAllocator(...);
extern "C" void *FUN_00388e60(void *arg0, void *arg1);
extern "C" int FUN_0018d2b0(int, int, int);
extern "C" int Gap__Bec__beHitLandModelOrder__vfunc_20(void);
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
typedef struct { char vtable[4]; int refs; } RefCountedObject;
extern "C" void Gap__Bec__beHitLandModel__vfunc_32(beHitLandModel *arg0);
extern "C" int g_beHitLandModelInfo_metaObject[4];
extern "C" int g_beHitLandModel_metaObject[4];
extern "C" char DAT_0050eae0[];
extern "C" void Gap__Bec__beHitLandModel__vfunc_29(beHitLandModel * p0, int p1, char * p2, int p3, int p4);
extern "C" beHitLandResultData *FUN_0035e400(void *);
extern "C" void *DAT_00586f20[4];
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
struct HitRecord { char pad[12]; void *matrix; char pad16[32]; float position[3]; };
struct ResultRecord { char header[16]; char hit[72]; };
extern "C" void Gap__Bec__beHitLandModelOrder__vfunc_22(beHitLandModelOrder *self, HitRecord *hit);
extern "C" igObject *FUN_00188220(int);
extern "C" void Gap__Bec__beHitLandModelOrder__vfunc_21(beHitLandModelOrder *self, int a1, int a2);
extern "C" void FUN_00388ff0(beHitLandModelOrder *arg0);
extern "C" int g_beHitLandModelOrder_metaObject[4];

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
    FUN_00190ed0((char *)arg0 + 0x30, 0.0f, 1.5707964f, 0.0f);
}

int Gap__Bec__beHitLandModel__vfunc_30(void)
{
    return g_beHitLandModelInfo_metaObject[0];
}

void Gap__Bec__beHitLandModel__vfunc_29(beHitLandModel * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, DAT_0050eae0, 0, -1);
}

void Gap__Bec__beHitLandModel__vfunc_31(void)
{
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
        alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<beHitLandResultData> created(FUN_0035e400(alloc));
        ObjectList_AppendRetained(self->_hitdataList, (beHitLandResultData *)created);
    }
    FUN_00192f50(hit->position, hit->position, hit->matrix);
    FUN_00388e60(((ResultRecord *)((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount])->hit, hit);
    result = ((beHitLandResultData **)((igObjectList *)self->_hitdataList)->_data)[self->_hitdataCount];
    name = (const char *)self->_infoName;
    if (DAT_00586f20[0] == 0) {
        void *pool = FUN_002eb010(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    token = StringPool_Intern(DAT_00586f20[0], name);
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
        igSmartPointer<igObject> ray(FUN_00188220(GPR_00554c14 != 0 ? a : ((int)Memory_GetAllocatorBySelector(DAT_00587110[0]))));
        /* matching construct: the (void *)(long) cast fixes the argument evaluation order of the append */
        ObjectList_AppendRetained((void *)(long)self->_rayList, ray.p);
    }
    FUN_0018d2b0(((int *)((igRayList *)self->_rayList)->_data)[self->_rayCount], a1, a2);
    self->_rayCount = self->_rayCount + 1;
}

void FUN_00388ff0(beHitLandModelOrder *arg0) {
    arg0->_kind = 0;
    arg0->_rayCount = 0;
    arg0->_hitdataCount = 0;
}

int Gap__Bec__beHitLandModelOrder__vfunc_20(void)
{
    return g_beHitLandModelOrder_metaObject[0];
}

int Gap__Bec__beHitLandModel__vfunc_20(void)
{
    return g_beHitLandModel_metaObject[0];
}


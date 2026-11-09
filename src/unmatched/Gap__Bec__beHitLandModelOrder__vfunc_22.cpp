#include "dw4/igSmartPointer.h"
extern "C" {
beHitLandResultData *FUN_0035e400(void *);
void FUN_00192f50(float *, float *, void *);
void FUN_00388e60(void *, void *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
void ObjectList_AppendRetained(int, beHitLandResultData *);
void *Memory_GetAllocatorBySelector(int);
void *igObject_GetAllocator(void *);
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct HitRecord { char pad[12]; void *matrix; char pad16[32]; float position[3]; };
struct ResultRecord { char header[16]; char hit[72]; };

extern "C" void Gap__Bec__beHitLandModelOrder__vfunc_22(beHitLandModelOrder *self, HitRecord *hit) {
    /* matching construct: declaration-order sweep (24 orders) — this order puts self in s1 and the result in s2 */
    const char *name;
    const char *token;
    beHitLandResultData *result;
    const char *old;
    if (self->_hitdataCount >= ((igObjectList *)self->_hitdataList)->_count) {
        void *alloc = igObject_GetAllocator(self);
        alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<beHitLandResultData> created(FUN_0035e400(alloc));
        ObjectList_AppendRetained(self->_hitdataList, created);
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

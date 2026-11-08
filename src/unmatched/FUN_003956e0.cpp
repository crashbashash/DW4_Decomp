/* Steps the model's direction toward its target (per-axis rate limit, wrapping at 2*pi), then
 * writes the new rotation into the ram object's transform. The ram object's data list is created
 * on first use. */
#include "dw4/reflected.h"
extern "C" {
struct Ref { int w0; int references; };
struct V3 { float x, y, z; };
struct Prop { char pad[16]; int f16; };
float FUN_003a8140(beBaseInfoRam *, int *);
extern int DAT_0050f0b8[4];
extern int DAT_0050ef60[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int igObject_GetAllocator(beBaseInfoRam *);
int Memory_GetAllocatorBySelector(int);
Ref *beBaseInfoDataList_Create(int);
void igObject_Destroy(Ref *);
Prop *igProperty_FindByName(Ref *, int, int *);
int Matrix44_GetTranslation(int, float *);
int Matrix44_SetTranslation(int, float *);
int FUN_00190ed0(int, float, float, float);
}
/* Owning stack reference to the freshly created data list, released on scope exit (reference count
 * in the low 23 bits of references). */
class ObjectRef {
public:
    Ref *p;
    ObjectRef(Ref *o) : p(o) {}
    ~ObjectRef() { Ref *o = p; if (o != 0) { --o->references; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_003956e0(int a0, int a1, beBaseInfoRam *obj, beModelCtrlInfoWork *st, int force) {
    V3 v;
    float tmp[4];
    int i;
    float *pt;
    float *pc;
    float *spp;
    int off;
    float *pv;
    float *cp;
    int m;
    float step;
    float c;
    float t;
    float d2;
    float d1;
    float e;
    pt = (float *)&st->_targetDirection[0];
    ((float*)&v)[0] = *(float *)&st->_targetDirection[0];
    ((float*)&v)[1] = *(float *)&st->_targetDirection[1];
    ((float*)&v)[2] = *(float *)&st->_targetDirection[2];
    if (!(force & 0xff)) {
        i = 0;
        goto pre;
    body:
        if (*pc != *pt) {
            spp = (float *)((char *)&st->_directionLimiter[0] + off);
            if (*spp == 0.0f) {
                *pv = *(float *)((char *)&st->_direction[0] + off);
            } else {
                step = *spp * FUN_003a8140(obj, &DAT_0050f0b8[0]);
                c = *(float *)((char *)&st->_direction[0] + off);
                t = *(float *)((char *)&st->_targetDirection[0] + off);
                while (c < 0.0f) c += 6.2831855f;
                while (c >= 6.2831855f) c -= 6.2831855f;
                while (t < 0.0f) t += 6.2831855f;
                while (t >= 6.2831855f) t -= 6.2831855f;
                if (c <= t) {
                    d2 = t - c;
                    d1 = c - (t - 6.2831855f);
                } else {
                    d1 = c - t;
                    e = t; e += 6.2831855f; d2 = e - c;
                }
                if (d2 < d1) {
                    if (d2 > step) t = c + step;
                    else t = t;
                } else if (d1 > step) {
                    t = c - step;
                } else t = t;
                *pv = t;
            }
        }
        pt++; pc++; off += 4; pv++; i++;
    test:
        if (i < 3) goto body;
    }
    if (force == 0) {
        bool diff;
        cp = (float *)&st->_direction[0];
        diff = v.x != cp[0] || v.y != cp[1] || v.z != cp[2];
        if (!diff) goto done;
    }
    if (((Ref *)obj->_dataList) == 0) {
        int alloc = igObject_GetAllocator(obj);
        int a2;
        if (GPR_00554c14 != 0) a2 = alloc; else a2 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ObjectRef created(beBaseInfoDataList_Create(a2));
        Ref *r = created.p;
        if (r != 0) r->references = r->references + 1;
        Ref *old = ((Ref *)obj->_dataList);
        if (old != 0) {
            old->references = old->references - 1;
            if ((old->references & 0x7fffff) == 0) igObject_Destroy(old);
        }
        obj->_dataList = (int)r;
    }
    m = igProperty_FindByName(((Ref *)obj->_dataList), DAT_00585be0[0], &DAT_0050ef60[0])->f16 + 32;
    Matrix44_GetTranslation(m, tmp);
    FUN_00190ed0(m, v.x, ((float*)&v)[1], ((float*)&v)[2]);
    Matrix44_SetTranslation(m, tmp);
    *(float *)&st->_direction[0] = v.x;
    *(float *)&st->_direction[1] = v.y;
    *(float *)&st->_direction[2] = v.z;
done:
    return;
pre:
    pc = (float *)&st->_direction[0];
    off = 0;
    pv = &v.x;
    goto test;
}

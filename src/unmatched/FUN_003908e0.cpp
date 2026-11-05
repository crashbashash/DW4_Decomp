#include "dw4/reflected.h"
/* FUN_003908e0 is beModelCtrlInfoHitBody's per-frame box builder; receiver evidence: +8 bool, +16 long, +24 count, +28..+40 the four lists.
 * arg1 is a beBaseInfoRam (+12 parent info, whose +20 is its data list); the "HIT" record is a beModelCtrlInfoDataHit (+20 AABox list).
 * igAABox's _min / _max are the reflected igVec3f fields (float[3] in include/dw4/reflected.h), read and written as floats here.
 * matching construct: the first-loop minuend is spelled `*(float *)&pc[0]`; other spellings change MWCC's operand/load order and swap the arg0 and i registers.
 * Arena refs stay 4-byte handles in the reflected structs, so each list is reached through a cast of the handle to its list class. */
struct V3 { float x, y, z; };
extern "C" {
void igObject_Destroy(igAABox *);
igAABox *FUN_0018a660(int);
void FUN_0018b990(igAABox *, float *);
int thunk_FUN_0018ac80(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
int List_Resize(...);
int ObjectList_AppendRetained(...);
beModelCtrlInfoDataHit *igProperty_FindByName(...);
extern int DAT_00585be0[4];
extern int DAT_0050ef10[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the per-slot working box: constructed from the freshly created box and released on scope
 * exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception table names is the
 * retail body 0x00198190 (config/SLUS-20836/unit-objects.json, duplicate __dt__8AABoxRefFv). */
class AABoxRef {
public:
    igAABox *p;
    AABoxRef(igAABox *o) : p(o) {}
    ~AABoxRef() { igAABox *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct PP { static inline float *At(float *b, int i) { return &b[i]; } };
extern "C" igAABoxList *FUN_003908e0(beModelCtrlInfoHitBody *arg0, beBaseInfoRam *arg1, int arg2, long long arg3);
igAABoxList *FUN_003908e0(beModelCtrlInfoHitBody *arg0, beBaseInfoRam *arg1, int arg2, long long arg3) {
    if (arg0->_isFirst != 0) {
        beModelCtrlInfoDataHit *pr = igProperty_FindByName(((beBaseInfo *)arg1->_parentInfo)->_dataList, DAT_00585be0[0], DAT_0050ef10);
        igAABoxList *q = (igAABoxList *)pr->_hitBulletAABoxList;
        arg0->_orgAABoxList = (int)q;
        arg0->_count = q->_count;
        int n = arg0->_count;
        int i;
        for (i = 0; i < n; i++) {
            igAABox *b = ((igAABox **)((igAABoxList *)arg0->_orgAABoxList)->_data)[i];
            float c[3];
            float e1[3];
            float e2[3];
            int j;
            FUN_0018b990(b, (float *)c);
            j = 0;
            {
                float *pc = c, *p1 = e1, *p2 = e2; igAABox *pb = b;
                for (; j < 3; j++) {
                    float d = *(float *)&pc[0] - pb->_min[0];
                    *p1 = d < 0.0f ? -d : d;
                    d = pb->_max[0] - *pc;
                    *p2 = d < 0.0f ? -d : d;
                    pb = (igAABox *)((char *)pb + 4); pc++; p1++; p2++;
                }
            }
            {
                int k;
                igDataList *l = (igDataList *)arg0->_AABoxMinList;
                k = l->_count;
                if (k < l->_capacity) l->_count = k + 1; else List_Resize(l, k + 1, 12);
                V3 *p = &((V3 *)l->_data)[k];
                p->x = e1[0]; p->y = e1[1]; p->z = e1[2];
            }
            {
                int k;
                igDataList *l = (igDataList *)arg0->_AABoxMaxList;
                k = l->_count;
                if (k < l->_capacity) l->_count = k + 1; else List_Resize(l, k + 1, 12);
                V3 *p = &((V3 *)l->_data)[k];
                p->x = e2[0]; p->y = e2[1]; p->z = e2[2];
            }
            {
                int alloc = igObject_GetAllocator(arg0);
                int a;
                if (GPR_00554c14 != 0) a = alloc; else a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                AABoxRef ob(FUN_0018a660(a));
                { igAABox *t = ob.p; igAABoxList *ol = (igAABoxList *)*(volatile int *)&arg0->_AABoxList; ObjectList_AppendRetained(ol, t); }
            }
        }
        arg0->_isFirst = 0;
    }
    if (arg3 != arg0->_calcTime) {
        int n;
        int i;
        arg0->_calcTime = arg3;
        n = arg0->_count;
        for (i = 0; i < n; i++) {
            igAABox *src = ((igAABox **)((igAABoxList *)arg0->_orgAABoxList)->_data)[i];
            igAABox *dst = ((igAABox **)((igAABoxList *)arg0->_AABoxList)->_data)[i];
            float c[3];
            float e1[3];
            float e2[3];
            int k;
            for (k = 0; k < 3; k++) { float *a = PP::At(dst->_min, k); float *b = PP::At(dst->_max, k); *a = src->_min[k]; *b = src->_max[k]; }
            thunk_FUN_0018ac80(dst, arg2);
            c[0] = (dst->_min[0]) * 0.5f + (dst->_max[0]) * 0.5f;
            c[1] = (dst->_min[1]) * 0.5f + (dst->_max[1]) * 0.5f;
            c[2] = (dst->_min[2]) * 0.5f + (dst->_max[2]) * 0.5f;
            *(V3 *)e1 = ((V3 *)((igDataList *)arg0->_AABoxMinList)->_data)[i];
            *(V3 *)e2 = ((V3 *)((igDataList *)arg0->_AABoxMaxList)->_data)[i];
            k = 0;
            { float *a = PP::At(dst->_min, k); float *b = PP::At(dst->_max, k); *a = c[0] - e1[0]; *b = c[0] + e2[0]; }
            for (k = 1; k < 3; k++) { float *a = PP::At(dst->_min, k); float *b = PP::At(dst->_max, k); *a = c[k] - e1[k]; *b = c[k] + e2[k]; }
        }
    }
    return (igAABoxList *)arg0->_AABoxList;
}

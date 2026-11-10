#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/typecast.h"

class A162b50;
struct VertexArrayFormat;

extern "C" {
void *FUN_0014a780(...);
void *FUN_0014b390(...);
void *FUN_00189e40(...);
void *FUN_0018a060(...);
void *FUN_0018a2d0(...);
void *FUN_002c9740(...);
void *FUN_002c99b0(...);
int List_Resize(...);
int ObjectList_AppendRetained(...);
int igObject_GetAllocator(void *object);
int igObject_IsKindOf(void *object, int meta);
igVertexData *igVertexArray2__FindVertexData(...);
VertexArrayFormat *FUN_0014adc0(int allocator);
int FUN_001931b0(...);
int FUN_00193540(...);
int FUN_00162b50(A162b50 *arg0);
int FUN_00162ca0(void *arg0);
extern int DAT_00561098[4];
extern int DAT_005610a8[4];
extern int DAT_005610b0[4];
extern int DAT_005610b8[4];
extern int DAT_005610c8[4];
extern int DAT_00586808[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586858[4];
extern int DAT_00586898[4];
}

/* Builds the stream objects of a new vertex array. When the helper has no igVertexArray2 yet (+12
 * == 0) it creates one and, for every stream kind requested in the layout word *arg1, creates a
 * data list of `arg2` elements and wraps it in a stream record (kind in +16) appended to the
 * array's stream list (+16): bit 0 / bit 1 / bit 2 give kinds 1 / 3 / 2 (12 / 12 / 4 byte
 * elements); bits 16..19 (count) kind 4, one record per index (8 byte elements, index in +20);
 * bits 4..7 (count) kind 5, arg2 * count 4-byte elements, count in +24; bits 8..11 (count) kind 6,
 * arg2 * count 1-byte elements, count in +24; bits 20..21 (mode) kind 9, mode 1 = 4-byte list,
 * mode 2 = 8-byte list; bit 22 / bit 23 kinds 7 / 8 (12 byte elements). */

/* reference-counted engine object header: refcount (low 23 bits) at +4 */
struct RC { int vt; int rc; };
/* data list header: element count at +8, capacity at +12 */
struct DataList { int vt; int rc; int count; int cap; };
/* stream record: list at +12, kind at +16, index/count at +20/+24 */
struct StreamRec { int vt; int rc; int pad8; DataList *list; int kind; int index; int count; };
/* matching construct: stack smart-pointer slot (empty destructor) */
struct RP { RC *p; ~RP() {} };

#define REL(x) { RC *q_ = (x); if (q_ != 0) { q_->rc = q_->rc - 1; if (((unsigned long long)((long long)q_->rc << 0x29) >> 0x29) == 0) igObject_Destroy(q_); } }
#define SIZE_LIST(lst, n, esz) { DataList *dl_ = (lst); if ((n) >= 0) { if ((n) <= dl_->cap) { dl_->count = (n); } else { List_Resize(dl_, (n), (esz)); } } }
#define ATTACH(rec, lst) { RC *l_ = (RC *)(lst); StreamRec *r_ = (rec); if (l_ != 0) l_->rc = l_->rc + 1; REL((RC *)r_->list) r_->list = (DataList *)l_; }

extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_23(igVertexArray2Helper *arg0, unsigned int *arg1, int arg2) {
    RP array;
    RP record;
    if (arg0->_vertexArray != 0) { return 0; }
    array.p = (RC *)FUN_0014a780(igObject_GetAllocator(arg0));
    {
        RC *a_ = array.p;
        if (a_ != 0) a_->rc = a_->rc + 1;
        REL((RC *)arg0->_vertexArray)
        arg0->_vertexArray = (int)a_;
    }
    record.p = 0;
    if (*arg1 & 1) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 1;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if (*arg1 & 2) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 3;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if (*arg1 & 4) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_00189e40(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 4)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 2;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if ((*arg1 & 0xF0000) >> 16 & 0xFF) {
        unsigned int index;
        for (index = 0; index < ((*arg1 & 0xF0000) >> 16 & 0xFF); index++) {
            RP list;
            int alloc;
            list.p = (RC *)FUN_0018a2d0(igObject_GetAllocator(arg0));
            SIZE_LIST((DataList *)list.p, arg2, 8)
            alloc = igObject_GetAllocator(arg0);
            REL(record.p)
            record.p = (RC *)FUN_0014b390(alloc);
            ATTACH((StreamRec *)record.p, list.p)
            ((StreamRec *)record.p)->kind = 4;
            ((StreamRec *)record.p)->index = index;
            ObjectList_AppendRetained(((int *)array.p)[4], record.p);
            REL(list.p)
        }
    }
    if ((*arg1 & 0xF0) >> 4 & 0xFF) {
        RP list;
        int alloc;
        int total;
        list.p = (RC *)FUN_002c9740(igObject_GetAllocator(arg0));
        total = arg2 * ((*arg1 & 0xF0) >> 4 & 0xFF);
        SIZE_LIST((DataList *)list.p, total, 4)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 5;
        ((StreamRec *)record.p)->count = (*arg1 & 0xF0) >> 4 & 0xFF;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if ((*arg1 & 0xF00) >> 8 & 0xFF) {
        RP list;
        int alloc;
        int total;
        list.p = (RC *)FUN_002c99b0(igObject_GetAllocator(arg0));
        total = arg2 * ((*arg1 & 0xF00) >> 8 & 0xFF);
        SIZE_LIST((DataList *)list.p, total, 1)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 6;
        ((StreamRec *)record.p)->count = (*arg1 & 0xF00) >> 8 & 0xFF;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    {
        unsigned int mode = (*arg1 & 0x300000) >> 0x14;
        unsigned char field = mode;
        if (field != 0) {
            int modeInt = field & 0xFF;
            int alloc = igObject_GetAllocator(arg0);
            REL(record.p)
            record.p = (RC *)FUN_0014b390(alloc);
            ((StreamRec *)record.p)->kind = 9;
            if (modeInt == 1) {
                RP list;
                list.p = (RC *)FUN_002c9740(igObject_GetAllocator(arg0));
                SIZE_LIST((DataList *)list.p, arg2, 4)
                ATTACH((StreamRec *)record.p, list.p)
                REL(list.p)
            } else if (modeInt == 2) {
                RP list;
                list.p = (RC *)FUN_0018a2d0(igObject_GetAllocator(arg0));
                SIZE_LIST((DataList *)list.p, arg2, 8)
                ATTACH((StreamRec *)record.p, list.p)
                REL(list.p)
            }
            ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        }
    }
    if (*arg1 & 0x400000) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 7;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    if (*arg1 & 0x800000) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 8;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL(list.p)
    }
    REL(record.p)
    REL(array.p)
    return arg2;
}

struct VertexArrayFormat : igObject {
    char pad8[16];
    int primitiveMode;
};

struct VertexFormatOwner : igObject {
    char pad8[12];
    VertexArrayFormat *format;

    void setFormat(const igSmartPointer<VertexArrayFormat> &next) {
        VertexArrayFormat *object = next.p;
        VertexArrayFormat *previous;

        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
        previous = format;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        format = object;
    }
};


extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_26(igVertexArray2Helper *helper, unsigned int flags) {
    int mode = 0;
    VertexFormatOwner *array;

    if (flags & 1) {
        mode = 2;
    }
    array = (VertexFormatOwner *)helper->_vertexArray;
    if (array == 0) {
        return;
    }
    if (array->format != 0) {
        array->format->primitiveMode = mode;
        return;
    }
    {
        igSmartPointer<VertexArrayFormat> format(FUN_0014adc0(igObject_GetAllocator(helper)));
        if (format != 0) {
            format->primitiveMode = mode;
            array = (VertexFormatOwner *)helper->_vertexArray;
            array->setFormat(format);
        }
    }
}

/* Predicate on the bound vertex array: true when its igVertexStream exists and that stream's
 * _accessMode is 2. The enum behind _accessMode is not named in the reflection data, so the value
 * stays a literal. */
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_27(igVertexArray2Helper *self) {
    int result;
    igVertexArray2 *vertexArray;
    igVertexStream *stream;

    vertexArray = (igVertexArray2 *)(self->_vertexArray);
    result = 0;
    if (vertexArray != 0) {
        stream = (igVertexStream *)(vertexArray->_vertexStream);
        if ((stream != 0) && (stream->_accessMode == 2)) {
            result = 1;
        }
    }
    return result;
}

struct V { float x, y, z; };
struct A28 {
    char pad[8]; int f8; char pad2[4]; V *f16;
    static inline A28 *Cast(A28 *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_005610b8[0]) != 0) {
            return p;
        }
        return 0;
    }
};
struct H { char pad[12]; void *f12; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_28(H *arg0, int arg1, V *arg2) {
    A28 *a = A28::Cast((A28 *)igVertexArray2__FindVertexData(arg0->f12, 1, 0)->_data);
    int n = a->f8;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        V *p = &a->f16[arg1];
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
    }
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_29(igVertexArray2Helper *arg0, int arg1, float *arg2) {
    igVec3fList *var_s0;
    float *temp_v1;

    var_s0 = (igVec3fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData(arg0->_vertexArray, 1, 0))->_data), DAT_005610b8);
    temp_v1 = (float *)(var_s0->_data + (arg1 * 0xC));
    arg2[0] = temp_v1[0];
    arg2[1] = temp_v1[1];
    arg2[2] = temp_v1[2];
}

struct A30 { int a,b,c,d; };
struct B { int a,b,c,d,e; };
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_30(struct A30 *arg0, int arg1) {
    struct B *p = (struct B *)igVertexArray2__FindVertexData(arg0->d, 1, 0)->_data;
    if (p != 0 && igObject_IsKindOf(p, DAT_005610b8[0]) != 0) {
        p = (struct B *)p;
    } else {
        p = 0;
    }
    return p->e + arg1 * 12;
}

struct A { char pad[12]; int f12; };
struct M { char pad[8]; int cnt; char p2[4]; char *data; };
struct H31 { char pad[12]; struct A *a; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_31(struct H31 *arg0, int arg1, float *arg2) {
    struct M *m = (struct M *)igVertexArray2__FindVertexData(arg0->a, 3, 0)->_data;
    int n;
    float *p;
    if (m != 0 && igObject_IsKindOf(m, DAT_005610b8[0]) != 0) { m = (struct M*)m; } else { m = 0; }
    n = m->cnt;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        p = (float *)(m->data + arg1 * 12);
        p[0] = arg2[0];
        p[1] = arg2[1];
        p[2] = arg2[2];
    }
}

typedef struct O { char pad[12]; void *f12; } O;
typedef struct Q { char pad[16]; V *f16; } Q;

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_32(A *arg0, int arg1, V *arg2) {
    V *temp_v1;
    Q *var_s0;
    Q *t;

    t = (Q *)((O *)igVertexArray2__FindVertexData(arg0->f12, 3, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_005610b8[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    temp_v1 = var_s0->f16 + arg1;
    arg2->x = temp_v1->x;
    arg2->y = temp_v1->y;
    arg2->z = temp_v1->z;
}

extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_33(igVertexArray2Helper *arg0, int arg1) {
    void *var_s0;
    void *r;
    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 3, 0)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610b8[0]) != 0)) {
        r = var_s0;
    } else {
        r = (void *)(0);
    }
    return *(int *)((char *)(r) + 16) + (arg1 * 0xC);
}

typedef struct Q34 { char pad[8]; int f8; char pad2[4]; V *f16; } Q34;

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_34(A *arg0, int arg1, V *arg2) {
    Q34 *var_s1;
    Q34 *t;
    int n;
    V *p;

    t = (Q34 *)((O *)igVertexArray2__FindVertexData(arg0->f12, 7, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_005610b8[0]) != 0)) {
        var_s1 = t;
    } else {
        var_s1 = 0;
    }
    n = var_s1->f8;
    if ((n != 0) && (arg1 >= 0) && (arg1 < n)) {
        p = var_s1->f16 + arg1;
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
    }
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_35(igVertexArray2Helper *arg0, int arg1, float *arg2) {
    void *temp_v1;
    igVec3fList *var_s0;

    var_s0 = (igVec3fList *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 7, 0)->_data);
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610b8[0]) != 0)) {
        var_s0 = (igVec3fList *)var_s0;

    } else {
        var_s0 = (igVec3fList *)(0);
    }
    temp_v1 = (void *)(var_s0->_data + (arg1 * 0xC));
    arg2[0] = ((float *)temp_v1)[0];
    arg2[1] = ((float *)temp_v1)[1];
    arg2[2] = ((float *)temp_v1)[2];
}

extern "C" V *Gap__Gfx__igVertexArray2Helper__vfunc_36(A *arg0, int arg1) {
    Q *var_s0;
    Q *t;

    t = (Q *)((O *)igVertexArray2__FindVertexData(arg0->f12, 7, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_005610b8[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16 + arg1;
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_37(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    int temp_v1;
    void *temp_v1_2;
    igVec3fList *var_s1;

    var_s1 = (igVec3fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData(arg0->_vertexArray, 8, 0))->_data), DAT_005610b8);
    temp_v1 = var_s1->_count;
    if ((temp_v1 != 0) && (arg1 >= 0) && (arg1 < temp_v1)) {
        temp_v1_2 = (void *)(var_s1->_data + (arg1 * 0xC));
        *(float *)((char *)(temp_v1_2) + 0) = (float) *(float *)((char *)(arg2) + 0);
        *(float *)((char *)(temp_v1_2) + 4) = (float) *(float *)((char *)(arg2) + 4);
        *(float *)((char *)(temp_v1_2) + 8) = (float) *(float *)((char *)(arg2) + 8);
    }
}

/* The cast-or-null result is kept in a separate variable (t = s0 / t = 0): the then arm survives
 * as a jump and the join load is copied into its delay slot. */
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_38(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    void *temp_v1;
    void *var_s0;
    igVec3fList *t;

    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 8, 0)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610b8[0]) != 0)) {
        t = (igVec3fList *)var_s0;
    } else {
        t = (igVec3fList *)(0);
    }
    temp_v1 = (void *)(t->_data + (arg1 * 0xC));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 8);
}

extern "C" V *Gap__Gfx__igVertexArray2Helper__vfunc_39(A *arg0, int arg1) {
    Q *var_s0;
    Q *t;

    t = (Q *)((O *)igVertexArray2__FindVertexData(arg0->f12, 8, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_005610b8[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16 + arg1;
}

struct B4 { unsigned char b[4]; };
union U { int i; B4 b; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct T : VC { int f4; int f8; int f12; int *f16; };
struct S { char pad[12]; T *f12; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_40(igVertexArray2Helper *arg0, int arg1, U arg2) {
    int temp_s1;
    S *temp_v0;
    int temp_s1_2;
    temp_v0 = (S *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 2, 0));
    temp_s1 = DAT_00586858[0];
    if (temp_s1 == temp_v0->f12->vX()) {
        T *a = temp_v0->f12;
        int v1 = a->f8;
        if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
            a->f16[arg1] = arg2.i;
        }
    } else {
        temp_s1_2 = DAT_00561098[0];
        if (temp_s1_2 == temp_v0->f12->vX()) {
            T *a = temp_v0->f12;
            int v1 = a->f8;
            if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
                unsigned char *d = (unsigned char *)(a->f16 + arg1);
                d[0] = arg2.b.b[0];
                d[1] = arg2.b.b[1];
                d[2] = arg2.b.b[2];
                d[3] = arg2.b.b[3];
            }
        }
    }
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_41(igVertexArray2Helper *arg0, int arg1, int arg2) {
    int temp_s1;
    S *temp_v0;
    int temp_s1_2;
    U sp5C;
    temp_v0 = (S *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 2, 0));
    temp_s1 = DAT_00586858[0];
    if (temp_s1 == temp_v0->f12->vX()) {
        T *a = temp_v0->f12;
        int r = FUN_001931b0(arg2, 1);
        int v1 = a->f8;
        if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
            a->f16[arg1] = r;
        }
    } else {
        temp_s1_2 = DAT_00561098[0];
        if (temp_s1_2 == temp_v0->f12->vX()) {
            T *a = temp_v0->f12;
            sp5C.i = FUN_001931b0(arg2, 1);
            int v1 = a->f8;
            if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
                unsigned char *d = (unsigned char *)(a->f16 + arg1);
                d[0] = sp5C.b.b[0];
                d[1] = sp5C.b.b[1];
                d[2] = sp5C.b.b[2];
                d[3] = sp5C.b.b[3];
            }
        }
    }
}

class Y { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); char pad[12]; int *f16; };
struct X { char pad[12]; Y *f12; };
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_42(A *arg0, int arg1) {
    int temp_s0;
    Y *temp_a0;
    Y *temp_a0_2;
    X *temp_v0;
    int temp_s0_2;

    temp_v0 = (X *)igVertexArray2__FindVertexData(arg0->f12, 2, 0);
    temp_a0 = temp_v0->f12;
    temp_s0 = DAT_00586858[0];
    if (temp_s0 == temp_a0->vX()) {
        return temp_v0->f12->f16[arg1];
    }
    temp_a0_2 = temp_v0->f12;
    temp_s0_2 = DAT_00561098[0];
    if (temp_s0_2 == temp_a0_2->vX()) {
        return temp_v0->f12->f16[arg1];
    }
    return 0;
}

struct T43 { char pad[16]; int *f16; };
struct S43 { char pad[12]; T43 *f12; };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_43(igVertexArray2Helper *arg0, int arg1, int arg2) {
    int temp_s1;
    S43 *temp_v0;
    int temp_s1_2;

    temp_v0 = (S43 *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 2, 0));
    temp_s1 = DAT_00586858[0];
    if (temp_s1 == ((DW4VC_88_0 *)(temp_v0->f12))->vX()) {
        FUN_00193540(arg2, 1, temp_v0->f12->f16[arg1]);
        return;
    }
    temp_s1_2 = DAT_00561098[0];
    if (temp_s1_2 == ((DW4VC_88_0 *)(temp_v0->f12))->vX()) {
        FUN_00193540(arg2, 1, temp_v0->f12->f16[arg1]);
    }
}

struct T44 : VC { int f4; int f8; int f12; float *f16; };
struct S44 { char pad[12]; T44 *f12; int f16; int f20; int f24; };
struct V2 { float f[2]; V2(){} V2(const V2 &o){ f[0]=o.f[0]; f[1]=o.f[1]; } V2 &operator=(const V2 &o){ f[0]=o.f[0]; f[1]=o.f[1]; return *this; } float &operator[](int i){ return f[i]; } };
struct V3 { float f[3]; V3(){} V3(const V3 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; } V3 &operator=(const V3 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; return *this; } float &operator[](int i){ return f[i]; } };
struct V4 { float f[4]; V4(){} V4(const V4 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; f[3]=o.f[3]; } V4 &operator=(const V4 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; f[3]=o.f[3]; return *this; } float &operator[](int i){ return f[i]; } };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_44(igVertexArray2Helper *arg0, int arg1, int arg2, float arg3) {
    S44 *v;
    int s3;
    T44 *c;
    v = (S44 *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 5, 0));
    s3 = DAT_00586808[0];
    if (s3 == v->f12->vX()) {
        int idx;
        c = v->f12;
        idx = arg1 + arg2 * v->f24;
        if (c->f8 != 0 && idx >= 0 && idx < c->f8) {
            c->f16[idx] = arg3;
        }
    } else {
    s3 = DAT_005610c8[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V2 *q = (V2 *)c->f16 + arg2;
        V2 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    } else {
    s3 = DAT_005610b8[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V3 *q = (V3 *)c->f16 + arg2;
        V3 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    } else {
    s3 = DAT_005610a8[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V4 *q = (V4 *)c->f16 + arg2;
        V4 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    }
    }
    }
    }
}

extern "C" float Gap__Gfx__igVertexArray2Helper__vfunc_45(igVertexArray2Helper *arg0, int arg1, int arg2) {
    S44 *v;
    int s3;
    float sp2[2];
    float sp3[3];
    float sp4[4];
    float *p;
    int idx;
    v = (S44 *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 5, 0));
    s3 = DAT_00586808[0];
    if (s3 == v->f12->vX()) {
        idx = arg1 + arg2 * v->f24;
        return *(float *)((char *)v->f12->f16 + idx * 4);
    }
    s3 = DAT_005610c8[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 2;
        sp2[0] = p[0];
        sp2[1] = p[1];
        return sp2[arg1];
    }
    s3 = DAT_005610b8[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 3;
        sp3[0] = p[0];
        sp3[1] = p[1];
        sp3[2] = p[2];
        return sp3[arg1];
    }
    s3 = DAT_005610a8[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 4;
        sp4[0] = p[0];
        sp4[1] = p[1];
        sp4[2] = p[2];
        sp4[3] = p[3];
        return sp4[arg1];
    }
    return 0.0f;
}

class ByteList {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19();
    virtual int getMeta();
    int _refCount;
    int _count;
    int _capacity;
    int _data;
};
struct VertexData { char pad[12]; ByteList *list; int f16; int f20; int stride; };
struct Byte3 { unsigned char c[3]; Byte3() {} Byte3(const Byte3 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; } Byte3 &operator=(const Byte3 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; return *this; } unsigned char &operator[](int i) { return c[i]; } };
struct Byte4 { unsigned char c[4]; Byte4() {} Byte4(const Byte4 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3]; } Byte4 &operator=(const Byte4 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3]; return *this; } unsigned char &operator[](int i) { return c[i]; } };
/* matching construct: a small sweep of spellings */
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_46(igVertexArray2Helper *helper, int component, int index, unsigned char value) {
    VertexData *v;
    int meta;
    ByteList *l;
    v = (VertexData *)igVertexArray2__FindVertexData(helper->_vertexArray, 6, 0);
    meta = DAT_00586818[0];
    if (meta == v->list->getMeta()) {
        int i;
        l = v->list;
        i = component + index * v->stride;
        if (l->_count != 0 && i >= 0 && i < l->_count) {
            ((unsigned char *)l->_data)[i] = value;
        }
    } else {
        meta = DAT_005610b0[0];
        if (meta == v->list->getMeta()) {
            l = v->list;
            Byte3 *q = (Byte3 *)l->_data + index;
            Byte3 t(*q);
            t[component] = value;
            if (l->_count != 0 && index >= 0 && index < l->_count) {
                *q = t;
            }
        } else {
            meta = DAT_00561098[0];
            if (meta == v->list->getMeta()) {
                l = v->list;
                Byte4 *q = (Byte4 *)l->_data + index;
                Byte4 t(*q);
                t[component] = value;
                if (l->_count != 0 && index >= 0 && index < l->_count) {
                    *q = t;
                }
            }
        }
    }
}

struct B3 { unsigned char b[3]; };
struct T47 : VC { int f4; int f8; int f12; unsigned char *f16; };
struct S47 { char pad[12]; T47 *f12; int f16; int f20; int f24; };
extern "C" unsigned char Gap__Gfx__igVertexArray2Helper__vfunc_47(igVertexArray2Helper *arg0, int arg1, int arg2) {
    S47 *v;
    int s3;
    unsigned char sp3[3];
    unsigned char sp4[4];
    unsigned char *p;
    int idx;
    T47 *t;
    v = (S47 *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 6, 0));
    s3 = DAT_00586818[0];
    if (s3 == v->f12->vX()) {
        idx = arg1 + arg2 * v->f24;
        return v->f12->f16[idx];
    }
    s3 = DAT_005610b0[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 3;
        sp3[0] = p[0];
        sp3[1] = p[1];
        sp3[2] = p[2];
        return sp3[arg1];
    }
    s3 = DAT_00561098[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 4;
        sp4[0] = p[0];
        sp4[1] = p[1];
        sp4[2] = p[2];
        sp4[3] = p[3];
        return sp4[arg1];
    }
    return 0;
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_48(igVertexArray2Helper *arg0, int arg1, int arg2, void *arg3) {
    int temp_v1;
    void *temp_v1_2;
    void *var_s0;
    igVec2fList *p;

    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 4, arg1)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610c8[0]) != 0)) {
        p = (igVec2fList *)var_s0;
    } else {
        p = (igVec2fList *)(0);
    }
    temp_v1 = p->_count;
    if ((temp_v1 != 0) && (arg2 >= 0) && (arg2 < temp_v1)) {
        temp_v1_2 = (void *)(p->_data + (arg2 * 8));
        *(float *)((char *)(temp_v1_2) + 0) = (float) *(float *)((char *)(arg3) + 0);
        *(float *)((char *)(temp_v1_2) + 4) = (float) *(float *)((char *)(arg3) + 4);
    }
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_49(igVertexArray2Helper *arg0, int arg1, int arg2, float *arg3) {
    float *temp_v1;
    igVec2fList *var_s0;
    igVec2fList *r;

    var_s0 = (igVec2fList *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 4, arg1)->_data);
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610c8[0]) != 0)) {

        r = var_s0;
    } else {
        r = (igVec2fList *)(0);
    }
    temp_v1 = (float *)(r->_data + (arg2 * 8));
    arg3[0] = temp_v1[0];
    arg3[1] = temp_v1[1];
}

extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_50(igVertexArray2Helper *arg0, int arg1, int arg2) {
    char *var_s0; char *p;
    var_s0 = (char *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 4, arg1)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610c8[0]) != 0)) {
        p = var_s0;
    } else {
        p = 0;
    }
    return *(int *)(p + 16) + (arg2 * 8);
}

typedef struct Q51 { char pad[16]; float *f16; } Q51;

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_51(A *arg0, int arg1, float fparg0) {
    Q51 *var_s0;
    Q51 *t;

    t = (Q51 *)((O *)igVertexArray2__FindVertexData(arg0->f12, 9, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_00586808[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    { int n = *(int *)((char *)var_s0 + 8); if (n != 0 && arg1 >= 0 && arg1 < n) { var_s0->f16[arg1] = fparg0; } }
}

extern "C" float Gap__Gfx__igVertexArray2Helper__vfunc_52(A *arg0, int arg1) {
    Q51 *var_s0;
    Q51 *t;

    t = (Q51 *)((O *)igVertexArray2__FindVertexData(arg0->f12, 9, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_00586808[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16[arg1];
}

struct V53 { float x, y; };
struct A53 {
    char pad[8]; int f8; char pad2[4]; V53 *f16;
    static inline A53 *Cast(A53 *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_005610c8[0]) != 0) {
            return p;
        }
        return 0;
    }
};
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_53(H *arg0, int arg1, V53 *arg2) {
    A53 *a = A53::Cast((A53 *)igVertexArray2__FindVertexData(arg0->f12, 9, 0)->_data);
    int n = a->f8;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        V53 *p = &a->f16[arg1];
        p->x = arg2->x;
        p->y = arg2->y;
    }
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_54(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    igVec2fList *var_s0;
    char *temp_v1;

    var_s0 = (igVec2fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData(arg0->_vertexArray, 9, 0))->_data), DAT_005610c8);
    temp_v1 = (char *)(var_s0->_data + (arg1 * 8));
    *(float *)((char *)(arg2) + 0) = *(float *)(temp_v1 + 0);
    *(float *)((char *)(arg2) + 4) = *(float *)(temp_v1 + 4);
}

/* Looks up the bound vertex array's stream with component type 5, index 0
 * (igVertexArray2__FindVertexData) and passes it to FUN_00162b50, which switches on the class of
 * the stream's data list and leaves its component count in v0. The declared return type is void. */

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_24(igVertexArray2Helper *self) {
    FUN_00162b50((A162b50 *)igVertexArray2__FindVertexData(self->_vertexArray, 5, 0));
}

/* Same as slot 24 for the stream with component type 6, index 0: looks it up with
 * igVertexArray2__FindVertexData and passes it to FUN_00162ca0 (same shape as FUN_00162b50 with
 * fewer data-list classes), whose component count is left in v0. The declared return type is void. */

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_25(igVertexArray2Helper *self) {
    FUN_00162ca0(igVertexArray2__FindVertexData(self->_vertexArray, 6, 0));
}

class S124 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int); };
class S136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(int); };
class S148 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(int); };
class S160 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual int vX(int); };
class S172 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual int vX(int); };
class S184 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual float vX(int, int); };
class S196 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual int vX(int, int); };
class S216 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual float vX(int); };
class S224 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void vX(int, void *); };
class S208 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
class D112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vY(int, int); };
class D124 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vY(int, int); };
class D136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vY(int, int); };
class D148 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vY(int, int); };
class D160 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void vY(int, int); };
class D176 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void vY(int, int, float); };
class D184 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void vY(int, int, int); };
class D204 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void vY(int, float); };
class D212 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void vY(int, void *); };
class D192 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void vY(int, int, int); };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_56(void **arg0, int arg1, void **arg2, int arg3, int *arg4) {
    int sp88[2];
    unsigned int c1;
    unsigned int c2;
    unsigned int c3;
    unsigned int c4;
    unsigned int i;

    if (*arg4 & 1) {
        ((D112 *)arg0)->vY(arg1, ((S124 *)arg2)->vX(arg3));
    }
    if (*arg4 & 2) {
        ((D124 *)arg0)->vY(arg1, ((S136 *)arg2)->vX(arg3));
    }
    if (*arg4 & 0x400000) {
        ((D136 *)arg0)->vY(arg1, ((S148 *)arg2)->vX(arg3));
    }
    if (*arg4 & 0x800000) {
        ((D148 *)arg0)->vY(arg1, ((S160 *)arg2)->vX(arg3));
    }
    if (*arg4 & 4) {
        ((D160 *)arg0)->vY(arg1, ((S172 *)arg2)->vX(arg3));
    }
    c1 = ((unsigned int)(*arg4 & 0xF0) >> 4) & 0xFF;
    if (c1 != 0) {
        for (i = 0; i < (c1 & 0xFF); i++) {
            ((D176 *)arg0)->vY(i, arg1, ((S184 *)arg2)->vX(i, arg3));
        }
    }
    c2 = ((unsigned int)(*arg4 & 0xF00) >> 8) & 0xFF;
    if (c2 != 0) {
        for (i = 0; i < (c2 & 0xFF); i++) {
            ((D184 *)arg0)->vY(i, arg1, (((S196 *)arg2)->vX(i, arg3) & 0xFF));
        }
    }
    c3 = ((unsigned int)(*arg4 & 0x300000) >> 0x14) & 0xFF;
    if (c3 != 0) {
        if ((c3 & 0xFF) == 1) {
            ((D204 *)arg0)->vY(arg1, ((S216 *)arg2)->vX(arg3));
        } else if ((c3 & 0xFF) == 2) {
            ((S224 *)arg2)->vX(arg3, sp88);
            ((D212 *)arg0)->vY(arg1, sp88);
        }
    }
    c4 = ((unsigned int)(*arg4 & 0xF0000) >> 0x10) & 0xFF;
    if (c4 != 0) {
        for (i = 0; i < (c4 & 0xFF); i++) {
            ((D192 *)arg0)->vY(i, arg1, ((S208 *)arg2)->vX(i, arg3));
        }
    }
}

extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_57(void) {
    return 0;
}

class H58 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(); virtual int v100(); int pad4[2]; void *f12; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_58(H58 *arg0, unsigned int *arg1) {
    igVertexData *s3, *s2, *s1, *s6, *s7, *s8, *spAC, *s0;
    void *x;
    void *y;
    unsigned int v;
    int n;
    unsigned char sel;
    s3 = igVertexArray2__FindVertexData(arg0->f12, 1, 0);
    s2 = igVertexArray2__FindVertexData(arg0->f12, 3, 0);
    s1 = igVertexArray2__FindVertexData(arg0->f12, 2, 0);
    s6 = igVertexArray2__FindVertexData(arg0->f12, 5, 0);
    s7 = igVertexArray2__FindVertexData(arg0->f12, 6, 0);
    s8 = igVertexArray2__FindVertexData(arg0->f12, 8, 0);
    spAC = igVertexArray2__FindVertexData(arg0->f12, 7, 0);
    s0 = igVertexArray2__FindVertexData(arg0->f12, 9, 0);
    if (s3 != 0) {
        *arg1 |= 1;
    }
    if (s2 != 0) {
        *arg1 |= 2;
    }
    if (s1 != 0) {
        *arg1 |= 4;
    }
    if (s6 != 0) {
        v = arg0->v96() & 0xFF;
        *arg1 &= ~0xF0;
        *arg1 |= v << 4;
    }
    if (s7 != 0) {
        v = arg0->v100() & 0xFF;
        *arg1 &= ~0xF00;
        *arg1 |= v << 8;
    }
    if (s8 != 0) {
        *arg1 |= 0x800000;
    }
    if (spAC != 0) {
        *arg1 |= 0x400000;
    }
    if (s0 != 0) {
        x = (void *)s0->_data;
        if (x != 0 && igObject_IsKindOf(x, DAT_00586808[0]) != 0) {
            y = x;
        } else {
            y = 0;
        }
        if (((y != 0) ? 1 : 2) & 0xFF) {
            *arg1 &= 0xFFCFFFFF;
            *arg1 = *arg1 | ((((y != 0) ? 1 : 2) & 0xFF) << 0x14);
        } else {
            *arg1 = *arg1 & 0xFFCFFFFF;
        }
    }
    n = 0;
    while (igVertexArray2__FindVertexData(arg0->f12, 4, n) != 0) {
        n += 1;
    }
    *arg1 &= 0xFFF0FFFF;
    *arg1 |= (n & 0xFF) << 0x10;
}

class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); };
class A162b50 { public: int pad[3]; C *f12; int pad2[2]; int f24; };
extern "C" int FUN_00162b50(A162b50 *arg0) {
    if (DAT_00586808[0] == arg0->f12->v88() || DAT_00586898[0] == arg0->f12->v88() || DAT_00586818[0] == arg0->f12->v88() || DAT_00586830[0] == arg0->f12->v88() || DAT_00586840[0] == arg0->f12->v88()) {
        return arg0->f24;
    }
    if (DAT_005610c8[0] == arg0->f12->v88()) {
        return 2;
    }
    if (DAT_005610b8[0] == arg0->f12->v88()) {
        return 3;
    }
    if (DAT_005610a8[0] == arg0->f12->v88()) {
        return 4;
    }
    return 0;
}

struct O162ca0 { int p0; int p4; int p8; DW4VC_88_0 *obj; int p10; int p14; int f18; };
extern "C" int FUN_00162ca0(void *a0) {
    O162ca0 *arg0 = (O162ca0 *)a0;
    if (DAT_00586818[0] == arg0->obj->vX()) {
        return arg0->f18;
    }
    if (DAT_005610b0[0] == arg0->obj->vX()) {
        return 3;
    }
    if (DAT_00561098[0] == arg0->obj->vX()) {
        return 4;
    }
    return 0;
}

struct FloatList { int vt; int rc; int count; int cap; float *data; };
struct VData { char pad[12]; FloatList *list; };

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_59(igVertexArray2Helper *self, int type, float *out, int index) {
    VData *vd;
    FloatList *list;
    FloatList *scalars;
    FloatList *pairs;
    FloatList *triples;
    FloatList *quads;
    int i;
    int n;
    /* matching construct: hand sweep — function-scope x, y, z here and block-local accumulators in
     * the pair (case 4) and quad blocks set the float register order */
    float x, y, z;

    vd = (VData *)igVertexArray2__FindVertexData(self->_vertexArray, type, index);
    *out = 1e23f;
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_00586808[0]) != 0)) { scalars = list; } else { scalars = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610c8[0]) != 0)) { pairs = list; } else { pairs = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610b8[0]) != 0)) { triples = list; } else { triples = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610a8[0]) != 0)) { quads = list; } else { quads = 0; }
    switch (type) {
    case 1:
    case 3:
    case 7:
    case 8:
        if (triples != 0) {
            x = 1e23f; y = 1e23f; z = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
                if (z > p[2]) z = p[2];
            }
            *out = (x < y) ? x : y;
            *out = (*out < z) ? *out : z;
        }
        break;
    case 4:
        if (pairs != 0) {
            float x = 1e23f, y = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
            }
            *out = (x < y) ? x : y;
        }
        break;
    case 5:
    case 9:
        if (scalars != 0) {
            float m = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                m = (m < scalars->data[i]) ? m : scalars->data[i];
            }
            *out = m;
        } else if (pairs != 0) {
            x = 1e23f; y = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
            }
            *out = (x < y) ? x : y;
        } else if (triples != 0) {
            x = 1e23f; y = 1e23f; z = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
                if (z > p[2]) z = p[2];
            }
            *out = (x < y) ? x : y;
            *out = (*out < z) ? *out : z;
        } else if (quads != 0) {
            float x = 1e23f, y = 1e23f, z = 1e23f, w = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = quads->data + i * 4;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
                if (z > p[2]) z = p[2];
                if (w > p[3]) w = p[3];
            }
            *out = (x < y) ? x : y;
            *out = (*out < z) ? *out : z;
            *out = (*out < w) ? *out : w;
        }
        break;
    }
}

extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_60(igVertexArray2Helper *self, int type, float *out, int index) {
    VData *vd;
    FloatList *list;
    FloatList *scalars;
    FloatList *pairs;
    FloatList *triples;
    FloatList *quads;
    int i;
    int n;
    /* matching construct: hand sweep — function-scope x, y, z here and block-local accumulators in
     * the pair (case 4) and quad blocks set the float register order */
    float x, y, z;

    vd = (VData *)igVertexArray2__FindVertexData(self->_vertexArray, type, index);
    *out = -1e23f;
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_00586808[0]) != 0)) { scalars = list; } else { scalars = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610c8[0]) != 0)) { pairs = list; } else { pairs = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610b8[0]) != 0)) { triples = list; } else { triples = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610a8[0]) != 0)) { quads = list; } else { quads = 0; }
    switch (type) {
    case 1:
    case 3:
    case 7:
    case 8:
        if (triples != 0) {
            x = -1e23f; y = -1e23f; z = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
                if (z < p[2]) z = p[2];
            }
            *out = (x > y) ? x : y;
            *out = (*out > z) ? *out : z;
        }
        break;
    case 4:
        if (pairs != 0) {
            float x = -1e23f, y = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
            }
            *out = (x > y) ? x : y;
        }
        break;
    case 5:
    case 9:
        if (scalars != 0) {
            float m = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                m = (m > scalars->data[i]) ? m : scalars->data[i];
            }
            *out = m;
        } else if (pairs != 0) {
            x = -1e23f; y = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
            }
            *out = (x > y) ? x : y;
        } else if (triples != 0) {
            x = -1e23f; y = -1e23f; z = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
                if (z < p[2]) z = p[2];
            }
            *out = (x > y) ? x : y;
            *out = (*out > z) ? *out : z;
        } else if (quads != 0) {
            float x = -1e23f, y = -1e23f, z = -1e23f, w = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = quads->data + i * 4;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
                if (z < p[2]) z = p[2];
                if (w < p[3]) w = p[3];
            }
            *out = (x > y) ? x : y;
            *out = (*out > z) ? *out : z;
            *out = (*out > w) ? *out : w;
        }
        break;
    }
}

/* Union read-back through the stack; the exponent bias is subtracted after the join, not inside
 * the condition. */
extern "C" int FUN_00163770(unsigned int arg0, float fparg0) {
    union { float f; unsigned u; struct { unsigned frac:23; } b; } x;
    int e, v;
    unsigned int s, t, r, m;
    int iv;
    x.f = fparg0;
    e = (x.u >> 23) & 0xFF;
    m = x.b.frac;
    if (m != 0 || e != 0) {
        m |= 0x800000;
    }
    v = e - 0x7F;
    s = 0x17;
    if (v != 0) {
        s -= v;
    } else {
        s += v;
    }
    t = m & ((1 << s) - 1);
    iv = (int)x.f;
    if (arg0 < s) {
        r = t >> (s - arg0);
    } else {
        r = t << (arg0 - s);
    }
    return r | (iv << arg0);
}

extern "C" float FUN_00163800(int arg0, int arg1) {
    return (float) (arg0 >> arg1);
}

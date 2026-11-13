#include "dw4/reflected.h"

extern "C" void igObject_Destroy(...);
extern "C" int List_Reserve(...);
extern "C" int Gap__Bec__beShadow01__vfunc_30(void);
extern "C" int Gap__Bec__beShadow01__vfunc_20(void);
extern "C" int ObjectList_AppendRetained(...);
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beShadow01__vfunc_32(beShadow01 *arg0);
extern "C" int g_beShadow01Info_metaObject[4];
extern "C" int g_beShadow01_metaObject[4];
typedef struct RC { int p0; unsigned refs; } RC;
typedef struct Item { char p[28]; int f28; int f32; } Item;
typedef struct OL { char p[8]; int count; int cap; Item **data; } OL;
typedef struct OL2 { char p[8]; int count; int cap; RC **data; } OL2;
typedef struct T { char p[60]; int f60; } T;
typedef struct A { char p[32]; OL *l; } A;
typedef struct B { char p[36]; T *t; } B;
extern "C" int igGroup_AppendChild(T *, int);
extern "C" void FUN_0039e090(A *arg0, B *arg1);
extern "C" int igObject_IsKindOf(beShadow01Info *, int);
extern "C" int Gap__Core__igObject__vfunc_25(beShadow01 *, beShadow01Info *);
extern "C" int g_beShadow01Info_metaObject[4];
extern "C" int Gap__Bec__beShadow01__vfunc_25(beShadow01 *arg0, beShadow01Info *arg1);

void Gap__Bec__beShadow01__vfunc_32(beShadow01 *arg0) {
    /* matching construct: the int-indexed ((int *)...)[0] stores below spell the raw word stores of retail; they are list-backing-store writes, not game logic. */
    igDataList *l = (igDataList *)arg0->_svInfoList;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            ReleaseRef::go(((igObject **)((char *)l->_data + off))[0]);
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                ((int *)((char *)l->_data + off3))[0] = 0;
                ((int *)((char *)l->_data + off3 + 4))[0] = 0;
                ((int *)((char *)l->_data + off3 + 8))[0] = 0;
                ((int *)((char *)l->_data + off3 + 12))[0] = 0;
                ((int *)((char *)l->_data + off3 + 16))[0] = 0;
                ((int *)((char *)l->_data + off3 + 20))[0] = 0;
                ((int *)((char *)l->_data + off3 + 24))[0] = 0;
                ((int *)((char *)l->_data + off3 + 28))[0] = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                ((int *)((char *)l->_data + off4))[0] = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    if (!(0 < ((igDataList *)arg0->_svInfoList)->_count)) {
        List_Reserve((igDataList *)arg0->_svInfoList, 0, 4);
    }
    arg0->_savePos[0] = 0.0f;
    arg0->_savePos[1] = 0.0f;
    arg0->_savePos[2] = 0.0f;
}

int Gap__Bec__beShadow01__vfunc_30(void)
{
    return g_beShadow01Info_metaObject[0];
}

void FUN_0039e090(A *arg0, B *arg1) {
    RC *r;
    Item *it;
    T *t;
    int n;
    int i;
    int off;
    OL2 *l;
    int n2;
    int i2;
    int n3;
    int i3;
    i = 0;
    t = arg1->t;
    n = arg0->l->count;
    if (0 < n) {
        off = 0;
        do {
            it = *(Item **)((char *)arg0->l->data + off);
            if (it->f32 != 0) ObjectList_AppendRetained(t->f60, it->f32);
            if (it->f28 != 0) igGroup_AppendChild(t, it->f28);
            i += 1;
            off += 4;
        } while (i < n);
    }
    l = (OL2 *)arg0->l;
    n2 = l->count;
    i2 = 0;
    if (0 < n2) {
        off = 0;
        do {
            r = *(RC **)((char *)l->data + off);
            if (r != 0) {
                r->refs--;
                if (!(r->refs & 0x7fffff)) igObject_Destroy(r);
            }
            i2 += 1;
            off += 4;
        } while (i2 < n2);
    }
    n3 = l->count;
    for (i3 = 0; i3 < n3; i3++) {
        l->data[i3] = 0;
    }
    l->count = 0;
    if (!(0 < arg0->l->count)) List_Reserve(arg0->l, 0, 4);
}

int Gap__Bec__beShadow01__vfunc_25(beShadow01 *arg0, beShadow01Info *arg1) {
    igProjectiveShadowShader *t;

    if (igObject_IsKindOf(arg1, g_beShadow01Info_metaObject[0]) != 0) {
        t = (igProjectiveShadowShader *)arg1->_projShadowShader;
        if (t != 0) {
            t->_drawReceiver = 0;
            t->_useOrthographic = 1;
            t->_blurState = 0;
            t->_cutoff = 22.5f;
            if (t->_top == 5.0f) {
                t->_top = 100.0f;
                t->_bottom = -100.0f;
                t->_right = 100.0f;
                t->_left = -100.0f;
            }
            FUN_0039e090((A *)arg0, (B *)arg1);
            Gap__Core__igObject__vfunc_25(arg0, arg1);
        } else {
            ObjectList_AppendRetained(arg0->_svInfoList, arg1);
        }
        return 1;
    }
    return 0;
}

int Gap__Bec__beShadow01__vfunc_20(void)
{
    return g_beShadow01_metaObject[0];
}

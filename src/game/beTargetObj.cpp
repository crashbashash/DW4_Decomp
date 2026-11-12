#include "dw4/reflected.h"

extern "C" void FUN_00236be0(int insight, char *object);
extern "C" void FUN_00236c40(int insight, char *object);
extern "C" int FUN_00236f80(int, int);
extern "C" void Gap__Bec__beTargetObj__vfunc_24(void);
extern "C" int Gap__Bec__beTargetObj__vfunc_25(void);
extern "C" int Gap__Bec__beTargetObj__vfunc_20(void);
extern "C" int List_Reserve(void *, int, int);
extern "C" int List_Resize(void *, int, int);
extern "C" int Matrix44_GetTranslation(void *, float *);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_GetMatrix(void *, int, int);
extern "C" int beMessenger_GetMatrixCount(int);
extern "C" int beMessenger_SendGroup(int, int, int);
extern "C" float atan2f(float, float);
extern "C" int FUN_003a5f60(float *out);
extern "C" int Matrix44_Copy(...);
extern "C" int strcmp(int, char *);
extern "C" int FUN_003a65f0(int arg0, int arg1, int arg2);
extern "C" int FUN_003a6750(void *m, float *p);
extern "C" int *FUN_003a6840(void);
extern "C" int FUN_00192f50(float *, int *, int *);
extern "C" float FUN_003a6850(void *);
extern "C" int *FUN_003a68c0(void);
extern "C" float FUN_003a68d0(void);
extern "C" float FUN_003a68e0(float fparg0);
extern "C" int FUN_003a6930(void);
extern "C" void Gap__Bec__beTargetObj__vfunc_21(beTargetObj * self, int unused);
extern "C" void Gap__Bec__beTargetObj__vfunc_22(beTargetObj * self, int unused);
extern "C" int g_beTargetObj_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" int DAT_0058a578[4];
extern "C" void Gap__Bec__beTargetObj__vfunc_23(beTargetObj *arg0);
extern "C" int g_beTargetObj_metaObject[4];
extern "C" void Gap__Bec__beTargetObj__vfunc_27(beTargetObj *self);
extern "C" void Gap__Bec__beTargetObj__vfunc_26(beTargetObj *arg0);
extern "C" void FUN_003a5b40(void *arg0, igVec3fList *arg1, igIntList *arg2, int *arg3, int *arg4);
typedef struct V3 { float x, y, z; } V3;
typedef struct A { char p[8]; int n; char q[4]; V3 *pts; } A;
typedef struct B { char p[16]; int *idx; } B;
extern "C" void FUN_003a5cc0(void *arg0, A *a, B *b, V3 *q, V3 *outv, float *outd, int *outi);
extern "C" void FUN_003a5d70(void *arg0, A *a, B *b, V3 *q, V3 *outv, float *outd, int *outi);
struct V3_3a5f60 { float x, y, z; };
struct Arr { int pad0; int pad1; int n; int pad3; struct V3_3a5f60 *v; };
struct Mid { int p0, p1, p2, p3; struct Arr *a; int p5; };
struct Top { int p0, p1, p2, p3; struct Arr *arr; int p5; };
extern "C" struct Top *DAT_0058a570[4];
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int DAT_0050ffd0[4];
extern "C" int DAT_0050ffd8[4];
extern "C" int DAT_0058a5e0[4];
extern "C" int DAT_0058a5f0[4];
extern "C" int DAT_0058a5f8[4];
extern "C" int FUN_003a63b0(beTargetObj *arg0, float *arg1, int arg2);
typedef struct T { char p[8]; int f8; } T;
typedef struct O { char p[24]; T *f24; } O;
extern "C" int DAT_0050ffe8[4];
extern "C" int DAT_0050fff0[4];
extern "C" int FUN_003a64d0(O *arg0, float *arg1, int arg2);
extern "C" char DAT_00510008[];
extern "C" float DAT_0058a580[4];
extern "C" float DAT_0058a584[4];
extern "C" float DAT_0058a588[4];
extern "C" int DAT_0058a590[4];
extern "C" int DAT_0058a5a0[4];
extern "C" float DAT_0058a5e4[4];
extern "C" float DAT_0058a5e8[4];
extern "C" int DAT_004e1098[4];

void Gap__Bec__beTargetObj__vfunc_21(beTargetObj * self, int unused)
{
    FUN_00236be0(self->_insight, (char *)self);
}

void Gap__Bec__beTargetObj__vfunc_22(beTargetObj * self, int unused)
{
    FUN_00236c40(self->_insight, (char *)self);
}

void Gap__Bec__beTargetObj__vfunc_23(beTargetObj *arg0) {
    ((int *)DAT_0058a570)[0] = FUN_00236f80(arg0->_insight, g_beTargetObj_metaObject[0]);
    DAT_0058a578[0] = FUN_00236f80(arg0->_insight, g_beMessenger_metaObject[0]);
}

/* Slot 24, empty override. */
void Gap__Bec__beTargetObj__vfunc_24(void)
{
}

/* Slot 25, empty override returning 0. */
int Gap__Bec__beTargetObj__vfunc_25(void) {
    return 0;
}

void Gap__Bec__beTargetObj__vfunc_26(beTargetObj *arg0) {
    igVec3fList *temp_a0;
    igIntList *temp_a0_2;
    igVec3fList *temp_a0_3;

    ((igVec3fList *)arg0->_playerPosList)->_count = 0;
    temp_a0 = (igVec3fList *)arg0->_playerPosList;
    if (!(0 < temp_a0->_count)) {
        List_Reserve(temp_a0, 0, 0xC);
    }
    ((igIntList *)arg0->_playerRamNoList)->_count = 0;
    temp_a0_2 = (igIntList *)arg0->_playerRamNoList;
    if (!(0 < temp_a0_2->_count)) {
        List_Reserve(temp_a0_2, 0, 4);
    }
    ((igVec3fList *)arg0->_enemyPosList)->_count = 0;
    temp_a0_3 = (igVec3fList *)arg0->_enemyPosList;
    if (!(0 < temp_a0_3->_count)) {
        List_Reserve(temp_a0_3, 0, 0xC);
    }
}

void Gap__Bec__beTargetObj__vfunc_27(beTargetObj *self) {
    ((igVec3fList *)self->_playerPosList)->_count = 0;
    ((igIntList *)self->_playerRamNoList)->_count = 0;
    ((igVec3fList *)self->_enemyPosList)->_count = 0;
}

void FUN_003a5b40(void *arg0, igVec3fList *arg1, igIntList *arg2, int *arg3, int *arg4) {
    const igIntList *view = arg2;
    float v[3];
    int mat[16];
    int cnt, i, s0, s1;
    float *e;
    beMessenger_SendGroup(DAT_0058a578[0], (int)arg3, (int)arg4);
    cnt = beMessenger_GetMatrixCount(DAT_0058a578[0]);
    i = 0;
    if (0 < cnt) {
        do {
            beMessenger_GetMatrix(mat, DAT_0058a578[0], i);
            Matrix44_GetTranslation(mat, v);
            s0 = arg1->_count;
            if (s0 < arg1->_capacity) {
                arg1->_count = s0 + 1;
            } else {
                List_Resize(arg1, s0 + 1, 12);
            }
            e = (float *)(arg1->_data + s0 * 12);
            e[0] = v[0];
            e[1] = v[1];
            e[2] = v[2];
            if (arg2 != 0) {
                s1 = beMessenger_GetInt(DAT_0058a578[0], i);
                s0 = view->_count;
                if (s0 < arg2->_capacity) {
                    arg2->_count = arg2->_count + 1;
                } else {
                    List_Resize(arg2, s0 + 1, 4);
                }
                ((int *)arg2->_data)[s0] = s1;
            }
            i++;
        } while (i < cnt);
    }
}

void FUN_003a5cc0(void *arg0, A *a, B *b, V3 *q, V3 *outv, float *outd, int *outi) {
    int bi; int n; int i; float dx, dy, dz, d, best, px, py, pz, bx, by, bz;
    bi = 0; n = a->n;
    for (i = 0; i < n; i++) {
        V3 *p = &a->pts[i];
        px = p->x; py = p->y; pz = p->z;
        dy = q->y - py; dx = q->x - px; dz = q->z - pz;
        d = dx*dx + dy*dy + dz*dz;
        if (i == 0 || !(best <= d)) {
            best = d; bx = px; by = py; bz = pz;
            if (b) bi = b->idx[i];
        }
    }
    outv->x = bx; outv->y = by; outv->z = bz;
    *outd = best;
    *outi = bi;
}

void FUN_003a5d70(void *arg0, A *a, B *b, V3 *q, V3 *outv, float *outd, int *outi) {
    int bi; int n; int i;
    float ref, best, px, py, pz, bx, by, bz, ang, dx, dy, dz;
    ref = FUN_003a6850(arg0);
    n = a->n;
    for (i = 0; i < n; i++) {
        V3 *p = &a->pts[i];
        px = p->x; py = p->y; pz = p->z;
        ang = atan2f(px - q->x, pz - q->z) - ref;
        if (ang < 0.0f) ang = -ang;
        while (ang > 6.2831855f) ang -= 6.2831855f;
        if (i == 0 || !(best <= ang)) {
            best = ang; bx = px; by = py; bz = pz;
            bi = b->idx[i];
        }
    }
    outv->x = bx; outv->y = by; outv->z = bz;
    dy = q->y - by; dx = q->x - bx; dz = q->z - bz;
    *outd = dx*dx + dy*dy + dz*dz;
    *outi = bi;
}

int FUN_003a5f60(float *out) {
    int n, i;
    if (DAT_0058a570[0]->arr->n == 0) {
        FUN_003a5b40((void *)DAT_0058a570[0], (igVec3fList *)(DAT_0058a570[0]->arr), (igIntList *)(DAT_0058a570[0]->p5), DAT_0050ffd0, DAT_0050ffd8);
        if (DAT_0058a570[0]->arr->n == 0) return 0;
    }
    out[0] = g_vec3Zero[0];
    out[1] = DAT_004e105c[0];
    out[2] = DAT_004e1060[0];
    n = DAT_0058a570[0]->arr->n;
    for (i = 0; i < n; i++) {
        struct V3_3a5f60 *p = &DAT_0058a570[0]->arr->v[i];
        out[0] += p->x; out[1] += p->y; out[2] += p->z;
    }
    switch (n) {
    case 0: case 1: break;
    case 2: out[0] /= 2.0f; out[1] /= 2.0f; out[2] /= 2.0f; break;
    case 3: out[0] /= 3.0f; out[1] /= 3.0f; out[2] /= 3.0f; break;
    case 4: out[0] /= 4.0f; out[1] /= 4.0f; out[2] /= 4.0f; break;
    }
    return 1;
}

int FUN_003a63b0(beTargetObj *arg0, float *arg1, int arg2) {
    float a[3];
    float b[3];

    if (((igVec3fList *)arg0->_playerPosList)->_count == 0) {
        FUN_003a5b40((void *)arg0, (igVec3fList *)arg0->_playerPosList, (igIntList *)arg0->_playerRamNoList, &DAT_0050ffd0[0], &DAT_0050ffd8[0]);
        if (((igVec3fList *)arg0->_playerPosList)->_count == 0) {
            return 0;
        }
    }
    if (arg2 != 0) {
        a[0] = arg1[0];
        a[1] = arg1[1];
        a[2] = arg1[2];
        FUN_003a5cc0((void *)arg0, (A *)arg0->_playerPosList, (B *)arg0->_playerRamNoList, (V3 *)a, (V3 *)(&DAT_0058a5e0[0]), (float *)(&DAT_0058a5f0[0]), &DAT_0058a5f8[0]);
    } else {
        b[0] = arg1[0];
        b[1] = arg1[1];
        b[2] = arg1[2];
        FUN_003a5d70((void *)arg0, (A *)arg0->_playerPosList, (B *)arg0->_playerRamNoList, (V3 *)b, (V3 *)(&DAT_0058a5e0[0]), (float *)(&DAT_0058a5f0[0]), &DAT_0058a5f8[0]);
    }
    return 1;
}

int FUN_003a64d0(O *arg0, float *arg1, int arg2) {
    float va[4];
    float vb[4];
    if (arg0->f24->f8 == 0) {
        FUN_003a5b40((void *)arg0, (igVec3fList *)arg0->f24, (igIntList *)0, &DAT_0050ffe8[0], &DAT_0050fff0[0]);
        if (arg0->f24->f8 == 0) {
            return 0;
        }
    }
    if (arg2 != 0) {
        va[0] = arg1[0];
        va[1] = arg1[1];
        va[2] = arg1[2];
        FUN_003a5cc0((void *)arg0, (A *)arg0->f24, (B *)0, (V3 *)va, (V3 *)(&DAT_0058a5e0[0]), (float *)(&DAT_0058a5f0[0]), &DAT_0058a5f8[0]);
    } else {
        vb[0] = arg1[0];
        vb[1] = arg1[1];
        vb[2] = arg1[2];
        FUN_003a5d70((void *)arg0, (A *)arg0->f24, (B *)0, (V3 *)vb, (V3 *)(&DAT_0058a5e0[0]), (float *)(&DAT_0058a5f0[0]), &DAT_0058a5f8[0]);
    }
    return 1;
}

int FUN_003a65f0(int arg0, int arg1, int arg2) {
    V3 p;
    V3 q1;
    V3 q2;
    int e;
    Matrix44_Copy(((char *)DAT_0058a5a0), arg0);
    Matrix44_GetTranslation((void *)arg0, (float *)&p);
    DAT_0058a580[0] = p.x;
    DAT_0058a584[0] = p.y;
    DAT_0058a588[0] = p.z;
    DAT_0058a590[0] = 0xC2C80000;
    e = strcmp(arg2, DAT_00510008) == 0;
    if (strcmp(arg1, ((char *)DAT_0050ffd0)) == 0) {
        q1.x = p.x; q1.y = p.y; q1.z = p.z;
        return FUN_003a63b0((beTargetObj *)(((int *)DAT_0058a570)[0]), (float *)&q1, e);
    }
    if (strcmp(arg1, ((char *)DAT_0050ffe8)) == 0) {
        q2.x = p.x; q2.y = p.y; q2.z = p.z;
        return FUN_003a64d0((O *)(((int *)DAT_0058a570)[0]), (float *)&q2, e);
    }
    return 0;
}

int FUN_003a6750(void *m, float *p) {
    float v[3];
    float dx, dy, dz;
    Matrix44_GetTranslation(m, v);
    DAT_0058a580[0] = v[0];
    DAT_0058a584[0] = v[1];
    DAT_0058a588[0] = v[2];
    Matrix44_Copy(&DAT_0058a5a0[0], m);
    DAT_0058a590[0] = 0xC2C80000;
    ((float *)DAT_0058a5e0)[0] = p[0];
    DAT_0058a5e4[0] = p[1];
    DAT_0058a5e8[0] = p[2];
    dy = v[1] - p[1];
    dx = v[0] - p[0];
    dz = v[2] - p[2];
    DAT_0058a5f8[0] = 0;
    ((float *)DAT_0058a5f0)[0] = dx*dx + dy*dy + dz*dz;
    return 1;
}

int *FUN_003a6840(void) {
    return &((int *)DAT_0058a580)[0];
}

float FUN_003a6850(void *) {
    float sp[4];
    if (((float *)DAT_0058a590)[0] == -100.0f) {
        FUN_00192f50(sp, &DAT_004e1098[0], &DAT_0058a5a0[0]);
        ((float *)DAT_0058a590)[0] = atan2f(sp[0], sp[2]);
    }
    return ((float *)DAT_0058a590)[0];
}

int *FUN_003a68c0(void) {
    return &DAT_0058a5e0[0];
}

float FUN_003a68d0(void) {
    return *(float *)0x58A5F0;
}

float FUN_003a68e0(float fparg0) {
    return fparg0 + atan2f(((float *)DAT_0058a5e0)[0] - DAT_0058a580[0], DAT_0058a5e8[0] - DAT_0058a588[0]);
}

int FUN_003a6930(void)
{
    return *(int *)0x0058a5f8;
}

int Gap__Bec__beTargetObj__vfunc_20(void)
{
    return g_beTargetObj_metaObject[0];
}

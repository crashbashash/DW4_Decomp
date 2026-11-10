#include "dw4/reflected.h"

struct Mx { float f[16]; };
struct T { char p[44]; float f[16]; };
struct O { char p[12]; int f12; };
struct igVec3f { float _v[3]; float operator[](int i) const { return _v[i]; } };

extern "C" {
void *FUN_00236f80(int, int);
int igMatrix44f_SetIdentity(Mx *);
int FUN_001906d0(Mx *, void *);
int FUN_001c51b0(int, int, Mx *);
extern int DAT_0058c790[4];
extern char DAT_0050fb88[];
extern int g_beWaterPlainInfo_metaObject[4];
extern int g_beWaterPlain_metaObject[4];
int FUN_00340c60(void);
int FUN_003a0c20(beWaterPlain *, beWaterPlainInfoRam *, void *, float *, float);
void beMessenger_GetVec3(float *, int, int);
int beMessenger_GetVec3Count(int);
unsigned int beMessenger_ResolveEnumValue(int, int, int);
void beMessenger_RegisterReceiver(int, int, char *, int, int);

bool FUN_003a0570(O *o, int a1, int a2);
void FUN_003a0bc0(int arg0, void *arg1, void *arg2, int arg3, int arg4, float fparg0);
bool FUN_003a0d40(beWaterPlain *self, beWaterPlainInfoRam *ram, float *p);
void Gap__Bec__beWaterPlain__vfunc_32(void);
int Gap__Bec__beWaterPlain__vfunc_30(void);
void Gap__Bec__beWaterPlain__vfunc_29(beWaterPlain *, int, char *, int, int);
int Gap__Bec__beWaterPlain__vfunc_34(beWaterPlain *self, beWaterPlainInfoRam *ram, beMessengerWork *work);
int Gap__Bec__beWaterPlain__vfunc_20(void);
}

bool FUN_003a0570(O *o, int a1, int a2) {
    bool r = false;
    T *t = (T *)(((int *)FUN_00236f80(o->f12, DAT_0058c790[0]))[5]);
    Mx m;
    igMatrix44f_SetIdentity(&m);
    Mx *q = &m;
    float *p = (float *)q;
    p[0] = t->f[0];
    p[1] = t->f[1];
    p[2] = t->f[2];
    p[3] = t->f[3];
    p[4] = t->f[4];
    p[5] = t->f[5];
    p[6] = t->f[6];
    p[7] = t->f[7];
    p[8] = t->f[8];
    p[9] = t->f[9];
    p[10] = t->f[10];
    p[11] = t->f[11];
    p[12] = t->f[12];
    p[13] = t->f[13];
    p[14] = t->f[14];
    p[15] = t->f[15];

    FUN_001906d0(&m, (char *)t + 108);
    switch (FUN_001c51b0(a1, a2, &m)) {
    case 1: case 3: case 4: case 5: r = true; break;
    case 2: break;
    }
    return r;
}

void FUN_003a0bc0(int arg0, void *arg1, void *arg2, int arg3, int arg4, float fparg0) {
    int temp_a0;
    int temp_v1;

    temp_a0 = *(int *)(*(int *)((char *)(*(int *)((char *)(arg1) + 92)) + 16) + (arg4 * 4));
    if (temp_a0 != -1) {
        temp_v1 = *(int *)((char *)(arg2) + 8);
        if ((temp_v1 != 0) && (temp_a0 >= 0) && (temp_a0 < temp_v1)) {
            *(float *)(*(int *)((char *)(arg2) + 16) + (temp_a0 * 4)) = fparg0;
        }
    }
}

bool FUN_003a0d40(beWaterPlain *self, beWaterPlainInfoRam *ram, float *p) {
    const igVec3f &areaMax = *(const igVec3f *)ram->_areaMax;
    bool res = false;
    float r = ram->_cellSize;
    float y = p[1];
    float ax = ram->_pos[0];
    float x1 = ax + (ram->_areaMin[0] + r);
    float x2 = ax + (areaMax[0] - r);
    float z1 = ram->_pos[2] + (ram->_areaMin[2] + r);
    float z2 = ram->_pos[2] + (areaMax[2] - r);
    if ((!(ram->_pos[1] + ram->_shallmin < y) && (ram->_pos[1] + ram->_shallmax < y)) || (!(ram->_pos[1] + ram->_deepmin < y) && (ram->_pos[1] + ram->_deepmax < y))) {
        if (x1 <= p[0] && !(x2 < p[0])) {
            if (z1 <= p[2] && !(z2 < p[2])) res = true;
        }
    }
    return res;
}

void Gap__Bec__beWaterPlain__vfunc_32(void)
{
}

int Gap__Bec__beWaterPlain__vfunc_30(void)
{
    return g_beWaterPlainInfo_metaObject[0];
}

void Gap__Bec__beWaterPlain__vfunc_29(beWaterPlain *p0, int p1, char *p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, DAT_0050fb88, 0, -1);
}

int Gap__Bec__beWaterPlain__vfunc_34(beWaterPlain *self, beWaterPlainInfoRam *ram, beMessengerWork *work) {
    switch (beMessenger_ResolveEnumValue(self->_messenger, FUN_00340c60(), work->_message)) {
    case 0:
        if (beMessenger_GetVec3Count(self->_messenger) > 0 && ram->_st0 == 1) {
            float pos[3];
            beMessenger_GetVec3(pos, self->_messenger, 0);
            if (FUN_003a0d40(self, ram, pos))
                FUN_003a0c20(self, ram, ((void **)((igObjectList *)ram->_gridLists)->_data)[0], pos, 1.0f);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

int Gap__Bec__beWaterPlain__vfunc_20(void)
{
    return g_beWaterPlain_metaObject[0];
}

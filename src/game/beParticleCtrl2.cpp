#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igVec3f.h"
#include "dw4/igTransformVirtuals.h"
#include "dw4/igRandomNumberDispatch.h"

extern "C" void igSwitch_DisableAllChildren(int);
extern "C" void igSwitch_EnableChild(void *, unsigned int);
extern "C" void igSwitch_DisableChild(void *, unsigned int);
extern "C" void igMatrix44f_Copy(void *, void *);
extern "C" void igObject_Destroy(void *);
extern "C" int beParticleCtrl2_GetInfoMeta(void);
extern "C" int beParticleCtrl2_GetMeta(void);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" void igMatrix44f_PreRotateAxisAngle(void *, void *, float);
extern "C" void *beParticleCtrl2InfoWork_Create(...);
extern "C" int beParticleCtrl2_GetMessageEnum(...);
extern "C" void igMatrix44f_TranslateLocal(void *, void *);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int beMessenger_AppendBool(int, unsigned char);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" void beMessenger_GetMatrix(void *, int, int);
extern "C" void *beMessenger_GetObject(int, int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_GetStringCount(int);
extern "C" void beMessenger_GetVec3(void *, int, int);
extern "C" int beMessenger_GetVec3Count(int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, void *);
extern "C" int beMessenger_SendNamed(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void beParticleCtrl2_UpdateRam(beParticleCtrl2 *self, beParticleCtrl2InfoRam *ram);
extern "C" void beParticleCtrl2_Prepare(beParticleCtrl2 *self);
extern "C" int g_beParticleCtrl2Info_metaObject[4];
extern "C" int g_beParticleCtrl2_metaObject[4];
extern "C" int beMessenger_RegisterReceiver(int messenger, beParticleCtrl2InfoRam *ram, int *receiver, int *name, int ramNo);
extern "C" int emptyString[4];
extern "C" int MODELCTRL_12[4];
extern "C" void beParticleCtrl2_OnAddRam(beParticleCtrl2 *self, beParticleCtrl2InfoRam *ram);
extern "C" float g_vec3Zero[4];
extern "C" int g_vec3XAxis[4];
extern "C" int g_vec3YAxis[4];
extern "C" int g_vec3ZAxis[4];
extern "C" int GETMATRIX_5[4];
extern "C" int GENERATE_9[4];
extern "C" int SQ_ERAS_3[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" int beParticleCtrl2_OnMessage(beParticleCtrl2 *self, beParticleCtrl2InfoRam *ram, beMessengerWork *work);

void beParticleCtrl2_Prepare(beParticleCtrl2 *self) {
    int infoCount;
    int i;
    int ramCount;
    int j;
    beParticleCtrl2InfoRam *ram;
    beParticleCtrl2Info *info;
    int infoOffset;
    int ramOffset;
    igObject *work;
    infoCount = ((igObjectList *)self->_infoList)->_count;
    i = 0;
    if (0 < infoCount) {
        infoOffset = 0;
        do {
            info = *(beParticleCtrl2Info **)((char *)((igObjectList *)self->_infoList)->_data + infoOffset);
            igSwitch_DisableAllChildren(info->_mainSwitch);
            igSwitch_DisableAllChildren(info->_subSwitch);
            ramCount = ((igObjectList *)info->_ramList)->_count;
            j = 0;
            if (0 < ramCount) {
                ramOffset = 0;
                do {
                    ram = *(beParticleCtrl2InfoRam **)((char *)((igObjectList *)info->_ramList)->_data + ramOffset);
                    ram->_isRun = 0;
                    work = (igObject *)ram->_work;
                    if (work != 0) {
                        --work->_refCount;
                        if (((unsigned long long)(long long)work->_refCount & 0x7fffffULL) == 0) {
                            igObject_Destroy((void *)work);
                        }
                    }
                    ram->_work = 0;
                    j++;
                    ramOffset += 4;
                    ((ParticleTimer *)ram->_particleTimer)->_timeRunning = 0;
                } while (j < ramCount);
            }
            i++;
            infoOffset += 4;
        } while (i < infoCount);
    }
}

/* beParticleCtrl2InfoRam::_st0: a ram shows its switch children, runs until its end time and then hides them. */
enum ParticleState { PARTICLE_START, PARTICLE_RUN, PARTICLE_STOP };

static inline ParticleTimer *TimerOf(beParticleCtrl2InfoRam *ram) {
    return (ParticleTimer *)ram->_particleTimer;
}

static inline int StateOf(const beParticleCtrl2InfoRam *ram) {
    return ram->_st0;
}

static inline void AdvanceState(beParticleCtrl2InfoRam *ram) {
    ram->_st0 = ram->_st0 + 1;
    ram->_st3 = 0;
    ram->_st2 = 0;
    ram->_st1 = 0;
}

/* Follows the lock node's position, then steps the ram through its start, run and stop states. */
void beParticleCtrl2_UpdateRam(beParticleCtrl2 *self, beParticleCtrl2InfoRam *ram) {
    beParticleCtrl2Info *info = (beParticleCtrl2Info *)ram->_parentInfo;
    if (ram->_isRun != 0) {
        beParticleCtrl2InfoWork *work = (beParticleCtrl2InfoWork *)ram->_work;
        if (work != 0) {
            float matrix[16];
            igMatrix44f_SetIdentity(matrix);
            igMatrix44f_Copy(matrix, ((igTransform *)work->_positionLockNode)->_m);
            igMatrix44f_TranslateLocal(matrix, work->_positionLockOffset);
            ((igTransformVirtuals *)ram->_transform)->setMatrix(matrix);
        }
        switch (StateOf(ram)) {
        case PARTICLE_START:
            igSwitch_EnableChild((void *)info->_mainSwitch, 0);
            igSwitch_EnableChild((void *)info->_subSwitch, ram->_ramNo);
            TimerOf(ram)->_time = -1;
            TimerOf(ram)->_timeRunning = 1;
            ((igParticleAttr **)((igAttrList *)TimerOf(ram)->_attributes)->_data)[0]->_bUseCurrentTime = 1;
            AdvanceState(ram);
            break;
        case PARTICLE_RUN:
            if (((igInsightCore *)self->_insight)->_worldTime - TimerOf(ram)->_timeBias < info->_endTimeLong) {
                break;
            }
            AdvanceState(ram);
        case PARTICLE_STOP: {
            TimerOf(ram)->_timeRunning = 0;
            igSwitch_DisableChild((void *)info->_subSwitch, ram->_ramNo);
            ram->_isRun = 0;
            igRelease((igObject *)ram->_work);
            ram->_work = 0;
            igObjectList *children = (igObjectList *)((igSwitch *)info->_subSwitch)->_childList;
            int count = children != 0 ? children->_count : 0;
            igBitMask *shown = (igBitMask *)((igSwitch *)info->_subSwitch)->_childMask;
            unsigned char anyShown = 0;
            for (int i = 0; i < count; i++) {
                if (((1 << (i & 31)) & ((unsigned *)shown->_data)[(unsigned)i >> 5]) != 0) {
                    anyShown = 1;
                    break;
                }
            }
            if (anyShown == 0) {
                igSwitch_DisableChild((void *)info->_mainSwitch, 0);
            }
            break;
        }
        }
    }
}

int beParticleCtrl2_GetInfoMeta(void)
{
    return g_beParticleCtrl2Info_metaObject[0];
}

void beParticleCtrl2_OnAddRam(beParticleCtrl2 *self, beParticleCtrl2InfoRam *ram) {
    int *name;
    int ramNo;
    igObject *work;

    ramNo = ram->_ramNo;
    name = (int *)((beParticleCtrl2Info *)ram->_parentInfo)->_name;
    name = (name != 0) ? name : (int *)(&emptyString[0]);
    beMessenger_RegisterReceiver(self->_messenger, ram, &MODELCTRL_12[0], name, ramNo);
    ram->_isRun = 0;
    work = (igObject *)ram->_work;
    if (work != 0) {
        work->_refCount = (int)work->_refCount - 1;
        if (((unsigned long long) ((long long) (int)work->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)work);
        }
    }
    ram->_work = 0;
}

int beParticleCtrl2_OnMessage(beParticleCtrl2 *self, beParticleCtrl2InfoRam *ram, beMessengerWork *work) {
    switch (beMessenger_ResolveEnumValue(self->_messenger, beParticleCtrl2_GetMessageEnum(), (void *)work->_message)) {
    case 0:
        if (beMessenger_GetStringCount(self->_messenger) != 0) {
            igVec3f offset;
            igVec3f rotation;
            float matrix[16];
            float rotationX, rotationY, rotationZ;
            int modelName = beMessenger_GetString(self->_messenger, 0);
            int ramNo = beMessenger_GetInt(self->_messenger, 0);
            beMessenger_GetVec3(&offset, self->_messenger, 0);
            unsigned char lockToNode = beMessenger_GetBool(self->_messenger, 0);
            if (beMessenger_GetVec3Count(self->_messenger) == 2) {
                beMessenger_GetVec3(&rotation, self->_messenger, 1);
                rotationY = rotation.y;
                rotationX = rotation.x;
                rotationZ = rotation.z;
                if (!(rotationY <= 6.2831855f)) {
                    rotationY = (float)(((RandomNumberDispatch *)((beSystem *)self->_system)->_random)->genrand() % 6144U) / 1000.0f;
                }
            } else {
                rotationX = g_vec3Zero[0];
                rotationY = g_vec3Zero[1];
                rotationZ = g_vec3Zero[2];
            }
            beMessenger_SendNamed(self->_messenger, MODELCTRL_12, modelName, ramNo, GETMATRIX_5);
            beMessenger_GetMatrix(matrix, self->_messenger, 0);
            if (lockToNode) {
                int alloc = igObject_GetAllocator(self);
                int a;
                if (g_useOwnerAllocator != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
                }
                igSmartPointer<beParticleCtrl2InfoWork> lockWork((beParticleCtrl2InfoWork *)beParticleCtrl2InfoWork_Create(a));
                igObject *node = (igObject *)beMessenger_GetObject(self->_messenger, 0);
                beParticleCtrl2InfoWork *held = lockWork.p;
                if (node != 0) {
                    node->_refCount = node->_refCount + 1;
                }
                Rel::go((igObject *)held->_positionLockNode);
                held->_positionLockNode = (int)node;
                beParticleCtrl2InfoWork *target = lockWork.p;
                igVec3f *lockOffset = (igVec3f *)&target->_positionLockOffset;
                lockOffset->x = offset.x;
                lockOffset->y = offset.y;
                lockOffset->z = offset.z;
                held = lockWork.p;
                if (held != 0) {
                    held->_refCount = held->_refCount + 1;
                }
                Rel::go((igObject *)ram->_work);
                ram->_work = (int)held;
            }
            igMatrix44f_TranslateLocal(matrix, &offset);
            if (rotationX != 0.0f) {
                igMatrix44f_PreRotateAxisAngle(matrix, g_vec3XAxis, rotationX);
            }
            if (rotationY != 0.0f) {
                igMatrix44f_PreRotateAxisAngle(matrix, g_vec3YAxis, rotationY);
            }
            if (rotationZ != 0.0f) {
                igMatrix44f_PreRotateAxisAngle(matrix, g_vec3ZAxis, rotationZ);
            }
            ((igTransformVirtuals *)ram->_transform)->setMatrix(matrix);
        } else {
            float identity[16];
            igMatrix44f_SetIdentity(identity);
            ((igTransformVirtuals *)ram->_transform)->setMatrix(identity);
        }
        ram->_isRun = 1;
        ram->_st0 = 0;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        break;
    case 2:
        ram->_st0 = 2;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        break;
    case 1:
        beMessenger_AppendBool(self->_messenger, ram->_isRun);
        break;
    case 6:
        if (ram->_isRun != 0) {
            ((ParticleTimer *)ram->_particleTimer)->_timeRunning = 0;
        }
        break;
    case 7:
        if (ram->_isRun != 0) {
            ((ParticleTimer *)ram->_particleTimer)->_timeRunning = 1;
        }
        break;
    case 3:
        beMessenger_AppendString(self->_messenger, GENERATE_9);
        beMessenger_AppendString(self->_messenger, GENERATE_9);
        beMessenger_AppendString(self->_messenger, SQ_ERAS_3);
        break;
    }
    return 1;
}

int beParticleCtrl2_GetMeta(void)
{
    return g_beParticleCtrl2_metaObject[0];
}

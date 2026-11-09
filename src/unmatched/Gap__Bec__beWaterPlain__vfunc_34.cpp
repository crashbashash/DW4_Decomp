#include "dw4/reflected.h"
extern "C" {
int FUN_00340c60(void);
int FUN_003a0c20(beWaterPlain *, beWaterPlainInfoRam *, void *, float *, float);
bool FUN_003a0d40(beWaterPlain *, beWaterPlainInfoRam *, float *);
void beMessenger_GetVec3(float *, int, int);
int beMessenger_GetVec3Count(int);
unsigned int beMessenger_ResolveEnumValue(int, int, int);
int Gap__Bec__beWaterPlain__vfunc_34(beWaterPlain *self, beWaterPlainInfoRam *ram, beMessengerWork *work);
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

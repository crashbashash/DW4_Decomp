/* Vfunc_31, the beAction2 per-frame Update driver. Runs only while the info's _isRun flag is set
 * and its work block is not frozen (_isFreeze). It then calls the Update handler of each component
 * whose "started" state slot is non-zero, in the fixed type order MOTIONSET, JOINTSET, FADESET,
 * WAITCHECK, FLASHSET. The state slots (_motionSt0 ... _flashSt0) are the ones the matching
 * *_Start handlers set when StartComponents launches a component. */
#include "dw4/reflected.h"
extern "C" {
void beAction2MOTIONSET_Update(void *self, void *info);
void beAction2JOINTSET_Update(void *self, void *info);
void beAction2FADESET_Update(void *self, void *info);
void beAction2WAITCHECK_Update(void *self, void *info);
void beAction2FLASHSET_Update(void *self, void *info);
void Gap__Bec__beAction2__vfunc_31(void *self, beAction2InfoRam *info);
}

void Gap__Bec__beAction2__vfunc_31(void *self, beAction2InfoRam *info) {
    beAction2InfoWork *work;

    if (info->_isRun == 0) {
        return;
    }
    work = (beAction2InfoWork *)info->_work;
    if (work->_isFreeze != 0) {
        return;
    }
    if (work->_motionSt0 != 0) {
        beAction2MOTIONSET_Update(self, info);
    }
    /* The asm nops below are matching constructs: retail's post-call scheduler padding. */
    if (work->_jointSt0 != 0) {
        beAction2JOINTSET_Update(self, info);
        asm { nop }
    }
    if (work->_fadeSt0 != 0) {
        beAction2FADESET_Update(self, info);
        asm { nop }
    }
    if (work->_waitSt0 != 0) {
        beAction2WAITCHECK_Update(self, info);
        asm { nop }
    }
    if (work->_flashSt0 != 0) {
        beAction2FLASHSET_Update(self, info);
        asm { nop }
    }
}

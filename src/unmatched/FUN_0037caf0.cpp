#include "dw4/reflected.h"
extern "C" {
int FUN_003a6e00(beCriAudio *);
int FUN_003a6f70(beCriAudio *, int);
int igNamedObject_SetName(beCriHandle *, int);
void FUN_0037caf0(void *arg0, beCriHandle *arg1);
}

void FUN_0037caf0(void *arg0, beCriHandle *arg1) {
    beCriAudio *temp_s0;
    beCriVolume *temp_v1;

    temp_s0 = (beCriAudio *)arg1->_audio;
    temp_v1 = (beCriVolume *)arg1->_volume;
    arg1->_playID = 0;
    arg1->_type = 0;
    temp_v1->_isExec = 0;
    temp_v1->_max = 0;
    temp_v1->_current = 0;
    temp_v1->_sta = 0;
    temp_v1->_end = 0;
    if (temp_s0->_audioType == 3) {
        FUN_003a6f70(temp_s0, 0);
    } else {
        FUN_003a6f70(temp_s0, -0x3E7);
    }
    FUN_003a6e00(temp_s0);
    igNamedObject_SetName(arg1, 0);
}

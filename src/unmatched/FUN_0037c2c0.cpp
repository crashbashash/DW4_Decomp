/* The retail stream player: handles a music (type 1) or ambience (type 2) request whose memory
 * index is -1 (an ADX file), taking the BGM or ambience handle of the beCri; types 3 and 4 are
 * ignored. If the handle's voice is still playing it arms the 1.0 -> 0.0 over 10.0 ramp (only when
 * none runs) and returns 0; otherwise it sets the level to volume + base, starts the file named by
 * the sound pack's file list and, on success, returns the new request id. Alternate compiler,
 * -O3,p. Receivers by the matched beSound::vfunc_34. */
#include "dw4/reflected.h"
extern "C" {
int FUN_003a6c00(int, int *);
int FUN_003a6f70(int, int);
int FUN_003a70c0(int);
int FUN_003a7260(int, int);
int igNamedObject_SetName(beCriHandle *, int *);
extern int DAT_004e0858[4];
void FUN_003a7590(beCriVolume *, int, float, float, float);
long long FUN_0037c2c0(beCri *self, igObjectList *table, beSoundData *ev);
}

long long FUN_0037c2c0(beCri *self, igObjectList *table, beSoundData *ev) {
    beCriHandle *slot;
    int voice;
    beCriVolume *handle;
    int *name;
    long long seq;
    if (ev->_memoryIdx != -1) return 0;
    slot = 0; voice = 0; handle = 0;
    switch (ev->_type) {
    case 4:
    case 3:
        return 0;
    case 1:
        slot = (beCriHandle *)self->_hdBGM;
        voice = slot->_audio;
        handle = (beCriVolume *)slot->_volume;
        break;
    case 2:
        slot = (beCriHandle *)self->_hdENV;
        voice = slot->_audio;
        handle = (beCriVolume *)slot->_volume;
        break;
    }
    if (FUN_003a70c0(voice) == 1) {
        if (handle->_isExec == 0) FUN_003a7590(handle, self->_baseVolume, 1.0f, 0.0f, 10.0f);
        return 0;
    }
    handle->_max = ev->_volume;
    name = (int *)((igNamedObject **)table->_data)[ev->_fnameIdx]->_name;
    name = name != 0 ? name : &DAT_004e0858[0];
    FUN_003a7260(voice, 1);
    FUN_003a6f70(voice, handle->_max + self->_baseVolume);
    if (FUN_003a6c00(voice, name) & 0xff) {
        if (self->_pauseOnetime != 0) self->_pauseOnetime = 0; else FUN_003a7260(voice, 0);
        seq = self->_request + 1;
        self->_request = seq;
        slot->_playID = seq;
        slot->_type = ev->_type;
        name = (int *)ev->_name;
        name = name != 0 ? name : &DAT_004e0858[0];
        igNamedObject_SetName(slot, name);
        return seq;
    }
    return 0;
}

/* The request record is the cue's beSoundData: _type, _fnameIdx, _memoryIdx (-1 for an ADX file),
 * _volume, _priority. */

#include "dw4/igSmartPointer.h"
#define SLOTS ((igObjectList *)self->_hdSEs)
#define ENTS ((igObjectList *)self->_lsBinObjs)
extern "C" {
int FUN_0037c130(beCri *, int, int);
int FUN_003a7260(beCriAudio *, int);
int FUN_003a6f70(beCriAudio *, int);
int FUN_003a6c00(beCriAudio *, char *);
int FUN_003a6c80(beCriAudio *, void *, int);
int FUN_003a6ce0(beCriAudio *, int, int);
int FUN_0030b3c0(igNamedObject *, char *);
int FUN_0030ba20(igNamedObject *);
int FUN_0030b5c0(igNamedObject *);
int strcmp(char *, char *);
void igNamedObject_SetName(void *, char *);
extern char DAT_004e0858[16];
extern char *DAT_004c22f0[4];
long long FUN_0037c4c0(beCri *self, igObjectList *lst, beSoundData *req);
}

long long FUN_0037c4c0(beCri *self, igObjectList *lst, beSoundData *req) {
    beCriSfpData *e0;
    beCriAudio *vc0;
    unsigned char ok;
    beCriAudio *vf;
    char *src;
    beCriHandle *slot;
    beCriVolume *df;
    int found;
    long long id;
    int i;
    beCriVolume *dc0;
    beCriAudio *vc1;
    int idx;
    int off;
    char *nm;
    char *cur;
    beCriSfpData *e;
    if (SLOTS->_count <= 0) return -1;
    switch (req->_type) {
    case 1: return 0;
    case 2: return 0;
    default: break;
    }
    ok = 0;
    slot = 0;
    if (req->_memoryIdx == -1) {
        idx = FUN_0037c130(self, 1, req->_priority);
        if (idx < 0 || idx >= SLOTS->_count) return 0;
        slot = ((beCriHandle **)SLOTS->_data)[idx];
        vf = (beCriAudio *)slot->_audio;
        df = (beCriVolume *)slot->_volume;
        df->_max = req->_volume;
        src = (char *)((igNamedObject **)lst->_data)[req->_fnameIdx]->_name;
        nm = src != 0 ? src : DAT_004e0858;
        vf->_audioType = 1;
        FUN_003a7260(vf, 1);
        FUN_003a6f70(vf, df->_max + self->_baseVolume);
        ok = FUN_003a6c00(vf, nm);
        if (ok) {
            if (self->_pauseOnetime) self->_pauseOnetime = 0; else FUN_003a7260(vf, 0);
        }
    } else {
        if (ENTS->_count <= 0) return 0;
        src = (char *)((igNamedObject **)lst->_data)[req->_fnameIdx]->_name;
        nm = src != 0 ? src : DAT_004e0858;
        igSmartPointer<igNamedObject> h((igNamedObject *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
        FUN_0030b3c0(h.p, nm);
        FUN_0030ba20(h.p);
        FUN_0030b5c0(h.p);
        found = -1;
        i = 0;
        if (0 < ENTS->_count) {
            off = 0;
            do {
                e = *(beCriSfpData **)((char *)ENTS->_data + off);
                src = (char *)e->_name;
                nm = src != 0 ? src : DAT_004e0858;
                cur = (char *)h.p->_name;
                cur = (cur == 0) ? DAT_004c22f0[0] : cur;
                if (strcmp(cur, nm) == 0) { found = i; break; }
                i += 1;
                off += 4;
            } while (i < ENTS->_count);
        }
        if (found == -1) {
            return 0;
        }
        switch (self->_dataType) {
        case 0:
            e0 = ((beCriSfpData **)ENTS->_data)[found];
            if (e0->_dataBuffer != 0) {
                idx = FUN_0037c130(self, 1, req->_priority);
                if (idx < 0 || idx >= SLOTS->_count) {
                    return 0;
                }
                slot = ((beCriHandle **)SLOTS->_data)[idx];
                vc0 = (beCriAudio *)slot->_audio;
                dc0 = (beCriVolume *)slot->_volume;
                dc0->_max = req->_volume;
                vc0->_audioType = 2;
                FUN_003a7260(vc0, 1);
                FUN_003a6f70(vc0, dc0->_max + self->_baseVolume);
                ok = FUN_003a6c80(vc0, (void *)e0->_dataBuffer, req->_memoryIdx);
                if (self->_pauseOnetime) self->_pauseOnetime = 0;
                FUN_003a7260(vc0, 0);
            } else {
                return 0;
            }
            break;
        case 1:
            if (((beCriSfpData **)ENTS->_data)[found]->_isTransfer != 0) {
                idx = FUN_0037c130(self, 0, req->_priority);
                if (idx < 0 || idx >= SLOTS->_count) {
                    return 0;
                }
                slot = ((beCriHandle **)SLOTS->_data)[idx];
                vc1 = (beCriAudio *)slot->_audio;
                ((beCriVolume *)slot->_volume)->_max = req->_volume;
                ok = FUN_003a6ce0(vc1, idx, req->_memoryIdx);
                if (ok) FUN_003a6f70(vc1, 127);
                if (self->_pauseOnetime) self->_pauseOnetime = 0;
            } else {
                return 0;
            }
            break;
        default:
            break;
        }
    }
    if (ok) {
        id = self->_request + 1;
        self->_request = id;
        slot->_playID = id;
        slot->_type = req->_type;
        src = (char *)req->_name;
        nm = src != 0 ? src : DAT_004e0858;
        igNamedObject_SetName(slot, nm);
        slot->_priority = req->_priority;
        return id;
    }
    return 0;
}

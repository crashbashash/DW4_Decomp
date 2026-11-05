#include "dw4/reflected.h"
extern "C" {
int FUN_00281bb8(int, unsigned char, long long);
void FUN_003a7580(void *, int, void *);
extern int DAT_00510060[4];
extern int DAT_00510080[4];
extern int DAT_005100a0[4];
int FUN_003a6ce0(beCriAudio *o, int id, long long value) {
    int ok = o->_sndf != 0;
    if (ok) ok = o->_audioType == 3;
    if (ok) {
        if (id < 1 || id > 255) { FUN_003a7580(o, id, DAT_00510060); return 0; }
        if (FUN_00281bb8(1, id, (int)value)) { FUN_003a7580(o, id, DAT_00510080); return 0; }
        if (FUN_00281bb8(2, id, 0)) { FUN_003a7580(o, id, DAT_005100a0); return 0; }
        ((beCriSndf *)o->_sndf)->_req = id;
        ((beCriSndf *)o->_sndf)->_seq = value;
        ((beCriSndf *)o->_sndf)->_isPlaying = 0;
        return 1;
    }
    return 0;
}
}

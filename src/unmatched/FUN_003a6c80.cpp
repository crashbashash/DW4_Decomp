#include "dw4/reflected.h"
extern "C" {
struct DispatchTarget;
int FUN_00332160(DispatchTarget *, int, int);
int FUN_003a6c80(beCriAudio *self, int arg1, int arg2) {
    bool ready = false;
    DispatchTarget *t = (DispatchTarget *)self->_adxt;
    if (t != 0) {
        if (self->_audioType == 2) ready = true;
    }
    if (ready) {
        int r = FUN_00332160(t, arg1, arg2);
        return r;
    }
    return 0;
}
}

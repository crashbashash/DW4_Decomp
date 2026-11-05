#include "dw4/reflected.h"
extern "C" {
int FUN_00332370(...);
int FUN_00332430(int, int, bool);
void FUN_003a74b0(void *arg0);
}
/* matching construct: inline bool predicates as members of a view over the reflected beCriAudio (_adxt, _sndf, _audioType, _errVolume) */
struct O : beCriAudio {
    bool A() { return _sndf != 0 && _audioType == 3; }
    bool B() { return _adxt != 0 && _audioType == 1; }
    bool C() { return _adxt != 0 && _audioType == 2; }
};
void FUN_003a74b0(void *arg0) {
    O *o = (O *)arg0;
    bool b;
    if (o->A()) {
        o->_errVolume = -999;
        return;
    }
    b = o->B();
    if (b || o->C()) {
        if (o->_errVolume != -999) {
            FUN_00332430(o->_adxt, o->_errVolume, b);
            FUN_00332370(o->_adxt, 0);
            o->_errVolume = -999;
        }
    }
}

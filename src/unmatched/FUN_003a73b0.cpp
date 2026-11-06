#include "dw4/reflected.h"
extern "C" {
int FUN_00332370(int, int);
int FUN_003323a0(int);
int FUN_00332430(int, int);
int FUN_00332460(int, int, bool);
void FUN_003a73b0(void *arg0, int arg1);
}
/* matching construct: inline bool predicates as members of a view over the reflected beCriAudio (_adxt, _sndf, _audioType, _errVolume) */
struct O : beCriAudio {
    bool A() { return _sndf != 0 && _audioType == 3; }
    bool B() { return _adxt != 0 && _audioType == 1; }
    bool C() { return _adxt != 0 && _audioType == 2; }
};
void FUN_003a73b0(void *arg0, int arg1) {
    O *o = (O *)arg0;
    bool b;
    int r;
    int t;
    if (o->A()) {
        o->_errVolume = 127;
        return;
    }
    t = arg1;
    b = false;
    if (o->_adxt != 0) {
        t = o->_audioType;
        if (t == 1) {
            b = true;
        }
    }
    if (b || o->C()) {
        r = FUN_00332460(o->_adxt, t, b);
        if (r != -999) {
            if (FUN_003323a0(o->_adxt) == 0) {
                o->_errVolume = r;
                FUN_00332430(o->_adxt, -999);
                FUN_00332370(o->_adxt, 1);
            }
        } else {
            o->_errVolume = -999;
        }
    }
}

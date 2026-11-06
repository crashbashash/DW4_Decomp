#include "dw4/reflected.h"
extern "C" {
int FUN_003323a0(int, int, bool);
int FUN_003a7300(void *arg0);
}
/* matching construct: inline bool predicates as members of a view over the reflected beCriAudio (_adxt, _sndf, _audioType, _errVolume) */
struct O : beCriAudio {
    bool A() { return _sndf != 0 && _audioType == 3; }
    bool B() { return _adxt != 0 && _audioType == 1; }
    bool C() { return _adxt != 0 && _audioType == 2; }
};
int FUN_003a7300(void *arg0) {
    O *o = (O *)arg0;
    bool b;
    if (o->A()) {
        return 0;
    }
    b = o->B();
    if (b || o->C()) {
        return FUN_003323a0(o->_adxt, o->_adxt, b);
    }
    return 0;
}

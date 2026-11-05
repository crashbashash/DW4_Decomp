#include "dw4/reflected.h"
extern "C" void FUN_00332370(int, int);
struct S {
    static bool A(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == 3; }
    static bool B(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 1; }
    static bool C(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 2; }
};
extern "C" void FUN_003a7260(beCriAudio *s, unsigned char a1) {
    if (!S::A(s)) {
        bool b = S::B(s);
        if (b || S::C(s)) FUN_00332370(s->_adxt, a1);
    }
}

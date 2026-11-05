#include "dw4/reflected.h"
extern "C" void FUN_00332430(void*, int);
extern "C" int FUN_00281bb8(int, int, int);
extern "C" void FUN_003a7580(void*, int, void*);
extern "C" char DAT_00510120[], DAT_00510140[], DAT_00510170[];
/* the beCriAudio::_sndf target (CRI sound-file handle); not a reflected class, so its +8 word stays local */
struct Q { int p0, p4; int f8; };
/* matching construct: static bool helper members (the retail shape) over the reflected receiver */
struct H {
    static bool A(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == 3; }
    static bool B(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 1; }
    static bool C(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 2; }
};
extern "C" void FUN_003a6f70(beCriAudio *s, int a1);
void FUN_003a6f70(beCriAudio *s, int a1) {
    if (H::A(s)) {
        int n = ((Q *)s->_sndf)->f8;
        if (n != 0) {
            if (n <= 0 || n > 255) {
                FUN_003a7580(s, n, DAT_00510120);
            } else {
                int r = FUN_00281bb8(7, n & 0xFF, 0);
                if (r < 0) {
                    FUN_003a7580(s, r, DAT_00510140);
                    return;
                }
                r = FUN_00281bb8(4, ((Q *)s->_sndf)->f8 & 0xFF, a1);
                if (r < 0) FUN_003a7580(s, r, DAT_00510170);
            }
        }
    } else {
        bool b = H::B(s);
        if (b || H::C(s)) FUN_00332430((void *)s->_adxt, a1);
    }
}

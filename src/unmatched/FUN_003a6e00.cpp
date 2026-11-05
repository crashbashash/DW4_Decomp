#include "dw4/reflected.h"
extern "C" void FUN_00332430(void*, int, unsigned char);
extern "C" void FUN_00332370(void*, int);
extern "C" void FUN_00332340(void*);
extern "C" int FUN_00281bb8(int, int, int);
extern "C" void FUN_003a7580(void*, int, void*);
extern "C" char DAT_005100c0[], DAT_005100e0[], DAT_00510100[];
struct H {
    static bool A(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == 3; }
    static bool B(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 1; }
    static bool C(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 2; }
};
extern "C" void FUN_003a6e00(beCriAudio *s);
void FUN_003a6e00(beCriAudio *s) {
    if (H::A(s)) {
        int n = ((beCriSndf *)s->_sndf)->_req;
        if (n != 0) {
            if (n <= 0 || n > 255) {
                FUN_003a7580(s, n, DAT_005100c0);
            } else {
                int r = FUN_00281bb8(7, n & 0xFF, 0);
                if (r < 0) {
                    FUN_003a7580(s, r, DAT_005100e0);
                    return;
                }
                if (r > 0) {
                    r = FUN_00281bb8(3, ((beCriSndf *)s->_sndf)->_req & 0xFF, 0);
                    if (r < 0) FUN_003a7580(s, r, DAT_00510100);
                }
                ((beCriSndf *)s->_sndf)->_req = 0;
                ((beCriSndf *)s->_sndf)->_seq = 0;
            }
        }
    } else {
        bool b = H::B(s);
        if (b || H::C(s)) {
            FUN_00332430((void *)s->_adxt, -999, b);
            FUN_00332370((void *)s->_adxt, 1);
            FUN_00332340((void *)s->_adxt);
        }
    }
}

#include "dw4/reflected.h"
extern "C" {
int FUN_00281bb8(int, int, int);
unsigned int FUN_00332490(void *, bool);
int FUN_003a7580(void *, int, int *);
extern int DAT_00510190[4];
extern int DAT_005101b0[4];
}
/* matching construct: predicate helpers as static members, as in the sibling FUN_003a7260 */
struct Pred {
    static bool A(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == 3; }
    static bool B(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 1; }
    static bool C(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 2; }
};
extern "C" int FUN_003a70c0(beCriAudio *s) {
    if (Pred::A(s)) {
        int n = ((beCriSndf *)s->_sndf)->_req;
        if (n == 0) return 0;
        if (n < 1 || n > 255) {
            FUN_003a7580(s, n, &DAT_00510190[0]);
            return -1;
        }
        int r = FUN_00281bb8(7, n & 0xff, 0);
        if (r < 0) {
            FUN_003a7580(s, r, &DAT_005101b0[0]);
            return -1;
        }
        switch (r) {
        case 1: case 2:
            ((beCriSndf *)s->_sndf)->_isPlaying = 1;
            return 1;
        default:
            return ((beCriSndf *)s->_sndf)->_isPlaying == 0;
        }
    }
    bool b = Pred::B(s);
    if (b || Pred::C(s)) {
        switch (FUN_00332490((void *)s->_adxt, b)) {
        case 0: return 0;
        case 1: case 2: case 3: case 4: return 1;
        case 5: return 0;
        case 6: default: return -1;
        }
    }
    return -1;
}

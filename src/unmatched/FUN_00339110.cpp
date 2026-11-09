/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 128 */
#include "dw4/igSmartPointer.h"
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual int vX(void *, igSmartPointer<igObject>); };
extern "C" {
void FUN_00339110(igMovieManager *arg0, igObject **arg1);
}
/* Retained share of an engine object held across the codec call. */

void FUN_00339110(igMovieManager *arg0, igObject **arg1) {
    int var_s1; int var_s0; igMovieInfoList *var_a0; igMovieInfo *temp_a1;

    var_a0 = (igMovieInfoList *)arg0->_movieList;
    var_s1 = 0;
    if (0 < var_a0->_count) {
        var_s0 = 0;
        do {
            temp_a1 = *(igMovieInfo **)(var_a0->_data + var_s0);
            {
            ((VC *)temp_a1->_codec)->vX(temp_a1, igSmartPointer<igObject>(*arg1, kRetainReference));
            }
            var_a0 = (igMovieInfoList *)arg0->_movieList;
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < var_a0->_count);
    }
}

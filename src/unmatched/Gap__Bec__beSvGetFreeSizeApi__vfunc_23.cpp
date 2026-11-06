#include "dw4/reflected.h"
struct UnidentifiedFreeSizeGlobal { char pad[20]; unsigned int f20; };
struct beSvGetFreeSizeApiTail { char pad[84]; int f84; }; /* word past the reflected beSvGetFreeSizeApi layout */
struct UnidentifiedResultObject {  /* arg1; class not identified */
  char pad[24]; int f24; char pad2[4]; unsigned int f32; int f36; unsigned char b40; unsigned char b41; unsigned char b42; unsigned char b43; unsigned char b44; };
extern "C" {
extern UnidentifiedFreeSizeGlobal *DAT_0058a600[4];
void Gap__Bec__beSvGetFreeSizeApi__vfunc_23(beSvGetFreeSizeApi *arg0, UnidentifiedResultObject *arg1);
}
void Gap__Bec__beSvGetFreeSizeApi__vfunc_23(beSvGetFreeSizeApi *arg0, UnidentifiedResultObject *arg1) {
    UnidentifiedFreeSizeGlobal *g = DAT_0058a600[0];

    arg1->f24 = arg0->_result;
    arg1->b44 = 1;
    if (((beSvGetFreeSizeApiTail *)arg0)->f84 == 1) {
        arg1->f32 = (unsigned int)arg0->_memCapa;
    } else {
        arg1->f32 = 0x04E00000;
    }
    arg1->f36 = arg0->_fileCapa;
    if (!(g->f20 > (unsigned int)arg0->_memCapa)) {
        arg1->b42 = 1;
    } else {
        arg1->b42 = 0;
    }
    arg1->b43 = 1;
}
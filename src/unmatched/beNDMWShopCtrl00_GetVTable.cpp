#include "dw4/reflected.h"
extern "C" {
int igObject_InitHeader(void *);
beNDMWWindowCtrl *beNDMWWindowCtrl_Destroy(beNDMWWindowCtrl *, int);
extern int DAT_0053feb0[4];
extern void *DAT_00586dc8[4];
int beNDMWShopCtrl00_GetVTable(void) {
    beNDMWWindowCtrl o;
    int r;
    igObject_InitHeader(&o);
    o._subWindow = 0;
    o._mother = 0;
    o._textCloseTypeList = 0;
    o._textCloseNameList = 0;
    o._modelCloseInfoNameList = 0;
    o._modelCloseRamNoList = 0;
    o._modelCloseSeqNameList = 0;
    o._vtable = (int)&DAT_0053feb0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o._vtable = (int)&DAT_0053feb0[0];
    beNDMWWindowCtrl_Destroy(&o, 0);
    return r;
}
}

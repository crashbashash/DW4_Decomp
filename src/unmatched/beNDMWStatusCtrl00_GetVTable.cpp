/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
beNDMWWindowCtrl *beNDMWWindowCtrl_Destroy(beNDMWStatusCtrl00 *, int);
int igObject_InitHeader(beNDMWStatusCtrl00 *);
extern int DAT_0053f260[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusCtrl00_GetVTable(void);
}
int beNDMWStatusCtrl00_GetVTable(void) {
    beNDMWStatusCtrl00 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    obj._vtable = (int)(&DAT_0053f260[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)(&DAT_0053f260[0]);
    beNDMWWindowCtrl_Destroy(&obj, 0);
    return temp_s0;
}

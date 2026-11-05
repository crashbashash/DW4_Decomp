/* 0x001510e0 — FUN_001510e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_00100400();
int igMatrix44f_SetIdentity();
int igObject_InitHeader();
void FUN_00151190(void);  /* code at 0x151190, passed by address (was DAT_151190; docs/engine/function-inventory.md) */
extern int DAT_00525e50[4];
extern int DAT_00530a10[4];
int FUN_00137360();

void *FUN_001510e0(igVisualContext *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_00530a10[0]);
    arg0->_pExtList = 0;
    arg0->_pExtInstances = 0;
    arg0->_vtable = (int)(&DAT_00525e50[0]);
    arg0->_driverDataMemoryPool = 0;
    arg0->_vertexMemoryPool = 0;
    arg0->_internalMemoryPool = 0;
    arg0->_temporaryMemoryPool = 0;
    arg0->_imageMemoryPool = 0;
    arg0->_textureMemoryPool = 0;
    arg0->_statisticsMemoryPool = 0;
    arg0->_listMemoryPool = 0;
    arg0->_timer = 0;
    igMatrix44f_SetIdentity(&arg0->_viewMatrixHint[0]);
    igMatrix44f_SetIdentity(&arg0->_viewMatrixInverse[0]);
    FUN_00100400(&arg0->_vertexArray2[0], FUN_00151190, &FUN_00137360, 4, 0x10);
    arg0->_customStates = 0;
    arg0->_customFields = 0;
    return arg0;
}

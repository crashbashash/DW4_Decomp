/* 0x0019c380 — FUN_0019c380. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObject_InitHeader();
extern int DAT_00524950[4];
extern int DAT_00528a90[4];
extern int DAT_00528dd0[4];
extern int DAT_005294b0[4];
void *FUN_0019c380(void *arg0) {
    igAttrSet *self = (igAttrSet *)arg0;
    igObject_InitHeader();
    self->_vtable = (int)(&DAT_00524950[0]);
    self->_name = 0;
    self->_vtable = (int)(&DAT_00528a90[0]);
    self->_bound = 0;
    self->_parentList = 0;
    self->_vtable = (int)(&DAT_00528dd0[0]);
    self->_childList = 0;
    self->_vtable = (int)(&DAT_005294b0[0]);
    self->_attributes = 0;
    return arg0;
}

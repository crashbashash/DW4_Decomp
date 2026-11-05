/* 0x00320af0 — FUN_00320af0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int memset();
int Gap__Core__igProgramFile__vfunc_23();

/* igElfFile vtable slot 23 (reset): receiver is igElfFile. */
void FUN_00320af0(igElfFile *arg0) {
    Gap__Core__igProgramFile__vfunc_23();
    memset(arg0->_header, 0, 0x34);
    arg0->_sectionHeaderStringTableSize = 0;
    arg0->_sectionHeaderStringTable = 0;
    arg0->_sectionHeaderCount = 0;
    arg0->_sectionHeaders = 0;
    arg0->_symbolStringTableSize = 0;
    arg0->_symbolStringTable = 0;
    arg0->_symbolCount = 0;
    arg0->_symbols = 0;
}

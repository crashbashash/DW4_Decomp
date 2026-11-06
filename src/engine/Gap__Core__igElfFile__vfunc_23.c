#include "dw4/reflected.h"
int memset();
int Gap__Core__igProgramFile__vfunc_23();

void Gap__Core__igElfFile__vfunc_23(igElfFile *arg0) {
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

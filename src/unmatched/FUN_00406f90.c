/* Reads the value field of a beDataObjInt record (callers pass igProperty_GetRecord results and
 * store into beDataObjInt::_data). */
#include "dw4/reflected.h"
int FUN_00406f90(beDataObjInt *p)
{
    return p->_data;
}

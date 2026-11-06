#include "dw4/reflected.h"
/* Receiver: an igUnsignedCharList (igDataList base, _count +8, _data +16); callers index the
 * returned pointer as bytes. */
int FUN_00406f00(igUnsignedCharList *p)
{
    return p->_data;
}

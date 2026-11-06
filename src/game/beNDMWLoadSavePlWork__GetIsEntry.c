/* Receiver: a beNDMWLoadSavePlWork element of the beNDMWLoadSave _flagWork list (+12 is _isEntry;
 * its sibling beNDMWLoadSavePlWork__GetIsRdy reads +13 _isRdy). */
#include "dw4/reflected.h"
unsigned char beNDMWLoadSavePlWork__GetIsEntry(beNDMWLoadSavePlWork *p)
{
    return p->_isEntry;
}

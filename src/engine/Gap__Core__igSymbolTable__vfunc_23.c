/* Number of symbols in the table. The symbols list stores four ints per symbol, so the count is
 * the list length divided by four (the resize sibling vfunc_24 sets the length to count << 2). */
#include "dw4/reflected.h"
int Gap__Core__igSymbolTable__vfunc_23(igSymbolTable *self) {
    return ((igDataList *)(self->_symbols))->_count / 4;
}

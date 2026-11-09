#include "dw4/reflected.h"

#include "dw4/igTDataList.h"

struct AttrObjectStack : igTDataList<igObject *> {
    int _default;
    int _cachedOverride;
    void (*_popProc)(igObject *, int);
};
extern "C" int FUN_001b1490(igAttrStackManager *, AttrObjectStack *, int);
extern "C" void FUN_001b1030(igAttrStackManager *self, igAttr *attr) {
    AttrObjectStack *stack = (AttrObjectStack *)self->_attrStacks;
    int slot = attr->_cachedAttrIndex;
    slot = attr->_cachedUnitID + ((int *)self->_attrStackIndexTable)[slot];
    stack = (AttrObjectStack *)stack->_data[slot];
    stack->append((igObject *)attr);
    FUN_001b1490(self, stack, slot);
}

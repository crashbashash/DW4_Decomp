/* 0x001af860 — igAttrStack reset (receiver evidence: FUN_001af890 walks
 * igAttrStackManager::_attrStacks (+16, count at +12) and calls this on each
 * element; the offsets match igAttrStack: _count, _cachedOverride,
 * _default -> _lastIncrementalFlushedAttr, the two Bool flags, _cachedRenderPackage). */
#include "dw4/reflected.h"
void FUN_001af860(igAttrStack *arg0) {
    arg0->_count = 0;
    arg0->_cachedOverride = -1;
    arg0->_lastIncrementalFlushedAttr = arg0->_default;
    arg0->_hasChangedFromLastIncrementalFlush = 0;
    arg0->_hasChangedFromRoot = 0;
    arg0->_cachedRenderPackage = 0;
}

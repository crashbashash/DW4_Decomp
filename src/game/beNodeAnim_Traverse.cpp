#include "dw4/support/reflected.h"
#include "dw4/core/igTDataList.h"
#include "dw4/scenegraph/igCommonTraversalDispatchView.h"
#include "dw4/game/beNodeAnim.h"
#include "dw4/scenegraph/igAttrStackManager.h"
#include "dw4/scenegraph/igObjectPool.h"
#include "dw4/attrs/igTimeAttr.h"
#include "dw4/scenegraph/igTraversal.h"
/* The attribute list of one stack: count and storage of the pushed attributes. */
typedef igTDataList<igAttr *> AttrList;
/* matching construct: the 4-byte reference fields (_attrStack, _timePool, _attrStacks, _data, _popProc, ...) are viewed through pointer casts; no layout effect */
extern "C" int beNodeAnim_Traverse(beNodeAnim *node, igCommonTraversal *traversal)
{
    igAttr *pushed;
    long long now;
    long long time;
    igObjectPool *timePool;
    igTimeAttr *timeAttr;
    int count;
    igAttrStackManager *attrs;
    int slot;
    igAttrStack *stack;
    int index;
    int result;
    short *timeAttrIndex;
    short *timeUnitID;

    attrs = (igAttrStackManager *)traversal->_attrStack;
    now = ((igCommonTraversalDispatchView *)traversal)->getTime();
    if (node->_isFirstTime != 0) {
        beNodeAnim_SetTime(node, node->_startTime, now);
        node->_beforeTime = now;
        node->_isFirstTime = 0;
    }
    time = beNodeAnim_UpdateTime(node, now);
    timePool = (igObjectPool *)traversal->_timePool;
    if (timePool->_freeIndex >= timePool->_count) {
        igObjectPool_Grow(timePool, (igObject *(*)(int))Gap::Attrs::igTimeAttr::_instantiateFromPool);
    }
    slot = timePool->_freeIndex;
    timePool->_freeIndex = slot + 1;
    timeAttr = ((igTimeAttr **)timePool->_data)[slot];
    timeAttr->_time = time;
    ((igCommonTraversalDispatchView *)traversal)->pushTime(time);
    timeAttrIndex = &timeAttr->_cachedAttrIndex;
    timeUnitID = &timeAttr->_cachedUnitID;
    index = *timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex];
    stack = ((igAttrStack **)((igAttrStackList *)attrs->_attrStacks)->_data)[index];
    pushed = (igAttr *)timeAttr;
    count = ((AttrList *)stack)->getCount();
    if (count < stack->_capacity) {
        stack->_count = stack->_count + 1;
    } else {
        ((Gap::Core::igDataList *)stack)->resizeAndSetCount(count + 1, 4);
    }
    ((AttrList *)stack)->set(count, &pushed);
    igAttrStackManager_MarkStackChanged(attrs, stack, index);
    result = igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)node);
    ((Gap::Sg::igAttrStackManager *)attrs)->fastPopAttr(*timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex]);
    ((igCommonTraversalDispatchView *)traversal)->popTime();
    if (result == 2) {
        return 2;
    }
    return 0;
}

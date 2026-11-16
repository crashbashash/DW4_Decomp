#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igCommonTraversalDispatchView.h"
#include "dw4/beNodeAnim.h"
extern "C" {
void igAttrStackManager_MarkStackChanged(igAttrStackManager *manager, igAttrStack *stack, int index);
int igTraversal_TraverseChildren(igCommonTraversal *traversal, beNodeAnim *node);
void igObjectPool_Grow(igObjectPool *pool, void *create);
void igTimeAttr_CreateInstance();
}
typedef void (*AttrPopProc)(void *attr, int data);
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
    int popIndex;
    igAttrStack *top;
    AttrPopProc pop;
    void *popped;
    int last;
    void **entries;
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
        igObjectPool_Grow(timePool, (void *)&igTimeAttr_CreateInstance);
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
        List_Resize(stack, count + 1, 4);
    }
    ((AttrList *)stack)->set(count, &pushed);
    igAttrStackManager_MarkStackChanged(attrs, stack, index);
    result = igTraversal_TraverseChildren(traversal, node);
    popIndex = *timeUnitID + ((int *)attrs->_attrStackIndexTable)[*timeAttrIndex];
    top = ((igAttrStack **)((igAttrStackList *)attrs->_attrStacks)->_data)[popIndex];
    last = top->_count - 1;
    entries = (void **)top->_data;
    pop = (AttrPopProc)top->_popProc;
    popped = entries[last];
    if (pop != 0) {
        pop(popped, attrs->_popProcData);
    }
    top->_count = top->_count - 1;
    igAttrStackManager_MarkStackChanged(attrs, top, popIndex);
    ((igCommonTraversalDispatchView *)traversal)->popTime();
    if (result == 2) {
        return 2;
    }
    return 0;
}

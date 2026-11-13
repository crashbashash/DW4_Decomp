#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
extern "C" {
void igAttrStackManager_MarkStackChanged(igAttrStackManager *manager, igAttrStack *stack, int index);
int igTraversal_TraverseChildren(igCommonTraversal *traversal, beNodeAnim *node);
void igObjectPool_Grow(igObjectPool *pool, void *create);
void igTimeAttr_CreateInstance();
void beNodeAnim_SetTime(beNodeAnim *node, long long startTime, long long now);
long long beNodeAnim_UpdateTime(beNodeAnim *node, long long now);
}
typedef void (*AttrPopProc)(void *attr, int data);
/* vtable view of the traversal context (igCommonTraversal): slots 24/30/31 only */
class TraversalTimeOps { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual long long getTime();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void pushTime(long long time);
    virtual void popTime();
};
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
    now = ((TraversalTimeOps *)traversal)->getTime();
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
    ((TraversalTimeOps *)traversal)->pushTime(time);
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
    ((TraversalTimeOps *)traversal)->popTime();
    if (result == 2) {
        return 2;
    }
    return 0;
}

struct AttrView { char _pad0[8]; short _stackIndex; short _subIndex; };
typedef void (*AttrPopCallback)(AttrView *, int);
struct AttrStack { int _pad0[2]; volatile int _count; int _capacity; AttrView **_data; int _pad14; int _base; AttrPopCallback _onPop; };
struct AttrStackList { int _pad0[4]; AttrStack **_data; };
struct AttrState { char _pad0[16]; AttrStackList *_stacks; char _pad14[28]; int _time; char _pad34[16]; int *_slotOfIndex; };
struct AttrViewList { int _pad0[2]; int _count; int _pad0c; AttrView **_data; };
struct AttrSetView { char _pad0[32]; AttrViewList *_attrs; unsigned char _dirty; };
struct DirtyList { int _pad0[2]; int _count; int _pad0c; int _data; };
struct CommandSinkView { char _pad0[12]; int _queue; };
struct CommandHolderView { int _pad0[2]; CommandSinkView *_sink; };
struct AttrTraversalView { char _pad0[52]; AttrState *_state; char _pad38[8]; DirtyList *_dirty; CommandHolderView *_holder; };
extern "C" {
void List_Resize(AttrStack *, int, int);
void igAttrStackManager_MarkStackChanged(AttrState *, AttrStack *, int);
void FUN_001b0440(AttrState *, DirtyList *);
void FUN_002d6c60(int, int, int);
int igTraversal_TraverseChildren(AttrTraversalView *, AttrSetView *);
}
static inline AttrView *attrAt(AttrStack *l, int i) { return l->_data[i]; }
static inline void pushAttr(AttrStack *l, AttrView *&v) {
    int n = l->_count;
    if (n < l->_capacity) {
        l->_count++;
    } else {
        List_Resize(l, n + 1, 4);
    }
    l->_data[n] = v;
}
extern "C" int FUN_001b90e0(AttrTraversalView *o, AttrSetView *set) {
    AttrState *state;
    int r;
    AttrView **p;
    int n;
    int index;
    AttrViewList *list;
    AttrView **end;
    int index2;
    AttrStack *stack;
    AttrStack *stack2;
    AttrView **begin;
    list = set->_attrs;
    state = o->_state;
    p = list->_data;
    end = p + list->_count;
    for (; p < end; p++) {
        AttrView *attr = *p;
        index = attr->_subIndex + state->_slotOfIndex[attr->_stackIndex];
        stack = state->_stacks->_data[index];
        if (stack->_base < 0) {
            stack->_base = stack->_count;
        }
        {
            AttrView *volatile held = attr;
            n = stack->_count;
            if (n < stack->_capacity) {
                stack->_count++;
            } else {
                List_Resize(stack, n + 1, 4);
            }
            stack->_data[n] = held;
        }
        igAttrStackManager_MarkStackChanged(state, stack, index);
    }
    if (set->_dirty) {
        FUN_001b0440(o->_state, o->_dirty);
        FUN_002d6c60(o->_holder->_sink->_queue, o->_dirty->_count, o->_dirty->_data);
    }
    r = igTraversal_TraverseChildren(o, set);
    if (p != 0) {
        begin = list->_data;
        for (p--; p >= begin; p--) {
            AttrView *attr = *p;
            AttrView *top;
            AttrPopCallback cb;
            index2 = attr->_subIndex + state->_slotOfIndex[attr->_stackIndex];
            stack2 = state->_stacks->_data[index2];
            top = attrAt(stack2, stack2->_count - 1);
            cb = stack2->_onPop;
            if (cb != 0 && top == attr) {
                cb(top, state->_time);
            }
            stack2->_count--;
            if (stack2->_count == stack2->_base) {
                stack2->_base = -1;
            }
            igAttrStackManager_MarkStackChanged(state, stack2, index2);
        }
    }
    if (r == 2) {
        return 2;
    }
    return 0;
}

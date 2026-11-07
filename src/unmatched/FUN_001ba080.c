typedef struct { float x, y, z; } CullVec3;
typedef struct CullMatrixEntry { char _pad0[12]; float _matrix[16]; } CullMatrixEntry;
typedef struct CullMatrixStack { int _pad0[2]; int _count; int _pad0c; CullMatrixEntry **_data; CullMatrixEntry *_default; int _current; } CullMatrixStack;
typedef struct CullStackList { int _pad0[4]; CullMatrixStack **_data; } CullStackList;
typedef struct CullAttrState { char _pad0[16]; CullStackList *_stacks; char _pad14[48]; int *_slotOfIndex; } CullAttrState;
typedef struct CullMeta { int _pad0[2]; int _index; } CullMeta;
typedef struct CullTraversalView { char _pad0[52]; CullAttrState *_state; } CullTraversalView;
typedef struct CullNodeView { char _pad0[52]; CullVec3 _center; } CullNodeView;
extern CullMeta *DAT_0055efe8[4];
void FUN_00192fc0(CullVec3 *, CullVec3 *, float *);
int FUN_001d0520(CullNodeView *, float);
int FUN_001e04c0(CullTraversalView *, int);
static inline CullMatrixEntry *entryAt(CullMatrixStack *s, int i) { return s->_data[i]; }
static inline CullMatrixEntry *currentEntry(CullMatrixStack *s) {
    int cur = s->_current;
    int n;
    if (cur >= 0) return entryAt(s, cur);
    n = s->_count;
    if (n != 0) return entryAt(s, n - 1);
    return s->_default;
}
int FUN_001ba080(CullTraversalView *o, CullNodeView *node) {
    CullVec3 out;
    CullVec3 center;
    CullAttrState *st;
    CullMatrixStack *stack;
    int child;
    center.x = node->_center.x;
    center.y = node->_center.y;
    center.z = node->_center.z;
    st = o->_state;
    stack = st->_stacks->_data[st->_slotOfIndex[DAT_0055efe8[0]->_index]];
    FUN_00192fc0(&out, &center, currentEntry(stack)->_matrix);
    child = FUN_001d0520(node, out.x * out.x + out.y * out.y + out.z * out.z);
    if (child != 0) {
        if (FUN_001e04c0(o, child) == 2) return 2;
        return 0;
    }
    return 0;
}

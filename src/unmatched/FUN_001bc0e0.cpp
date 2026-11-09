struct AttrIntList { int _pad0[2]; int _count; int _pad0c; int *_data; };
struct AttrStackList { int _pad0[2]; int _count; int _pad0c; AttrIntList **_data; };
struct AttrStackState { char _pad0[16]; AttrStackList *_stacks; char _pad14[48]; int *_slotOfIndex; };
struct AttrMeta { int _pad0[2]; int _index; };
struct CompileTraversalView {
    char _pad0[52]; AttrStackState *_state; char _pad38[416]; AttrIntList *_known; char _pad1dc[32]; int _depth; int _currentIndex;
};
extern AttrMeta *DAT_0055efe8[4];
extern "C" int FUN_001bbae0(CompileTraversalView *, int);
struct AttrKey {
    int value;
    AttrKey(int v) { value = v; }
    AttrKey(const AttrKey &o) { value = o.value; }
};
static inline int at(AttrIntList *l, int i) { return l->_data[i]; }
static inline int lastOf(AttrIntList *l) {
    int n = l->_count;
    if (n == 0) return 0;
    return at(l, n - 1);
}
static inline int indexOf(AttrIntList *l, const AttrKey &v) {
    int n = l->_count;
    int key = (*(int const *)&v.value);
    int i;
    for (i = 0; i < n; i++) {
        if (key == l->_data[i]) return i;
    }
    return -1;
}
extern "C" int FUN_001bc0e0(CompileTraversalView *o, int a) {
    int r;
    CompileTraversalView *self = (CompileTraversalView *)(int)o;
    o->_depth++;
    if (o->_depth == 1) {
        AttrStackState *s = self->_state;
        int last = lastOf(s->_stacks->_data[s->_slotOfIndex[DAT_0055efe8[0]->_index]]);
        AttrIntList *known = self->_known;
        AttrKey key(last);
        self->_currentIndex = indexOf(known, key);
    }
    r = FUN_001bbae0(o, a);
    self->_depth--;
    return r;
}

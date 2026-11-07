extern "C" {
void igObject_Destroy(void *);
void FUN_001c5d10(void *, void *);
void FUN_001c6050(void *, void *);
}
struct NodeParentListView { int _vtable; unsigned int _refCount; int _count; int _capacity; void **_data; };
class NodeSlots {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual int getChildCount();
    virtual class GroupChild *getChild(int);
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32();
    virtual void replaceChild(int index, void *with);
    int _refCount;
};
class GroupChild : public NodeSlots { public: char pad[20]; NodeParentListView *_parents; };
static inline int findParent(NodeParentListView *l, int *x) {
    int n = l->_count;
    for (int i = 0; i < n; i++) {
        if (x[0] == (int)l->_data[i]) { return i; }
    }
    return -1;
}
static inline void retain(int *slot) {
    NodeSlots *x = (NodeSlots *)*slot;
    if (x != 0) { x->_refCount = x->_refCount + 1; }
}
static inline void release(int *slot) {
    if (*slot != 0) {
        ((NodeSlots *)*slot)->_refCount = ((NodeSlots *)*slot)->_refCount - 1;
        if ((((NodeSlots *)*slot)->_refCount & 0x7fffff) == 0) { igObject_Destroy((NodeSlots *)*slot); }
    }
}
extern "C" void FUN_001d3410(NodeSlots *o, void *with) {
    NodeSlots *held = o;
    int i;
    retain((int *)&held);
    i = o->getChildCount() - 1;
    while (i >= 0) {
        GroupChild *c = o->getChild(i);
        NodeParentListView *l = c->_parents;
        NodeSlots *self = o;
        c->replaceChild(findParent(l, (int *)&self), with);
        FUN_001c6050(c, o);
        i--;
    }
    FUN_001c5d10(with, o);
    release((int *)&held);
}

struct TransformAttrView { char _pad0[12]; char _matrix[64]; };
struct TransformStackView { int _pad0[2]; int _count; int _pad0c; TransformAttrView **_data; TransformAttrView *_default; int _base; };
struct TransformStackList { int _pad0[4]; TransformStackView **_data; };
struct TransformStateView { char _pad0[16]; TransformStackList *_stacks; char _pad14[48]; int *_slotOfIndex; };
struct AttrClassView { int _pad0[2]; int _stackIndex; };
struct RefList { int _pad0[2]; int _count; int _pad0c; void **_data; };
struct AttrSetList { int _pad0[2]; int _count; int _pad0c; RefList **_data; };
class ModelViewAttrView {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void setMatrix(void *);
};
struct SwitchGroupView { char _pad0[28]; RefList *_children; AttrSetList *_attrSets; int _pad24; unsigned char _nested; char _pad29[15]; int _mode; };
struct TraversalStateHolder { char _pad0[52]; TransformStateView *_state; };
struct DrawTraversalView { char _pad0[52]; TransformStateView *_state; char _pad38[176]; void *_baseAttr; };
extern AttrClassView *DAT_0055efe8;
extern "C" {
void FUN_001b1030(TransformStateView *, void *);
void FUN_001b1100(TransformStateView *, void *);
void *FUN_001d82f0(SwitchGroupView *, int);
ModelViewAttrView *FUN_001d8310(SwitchGroupView *, int);
int FUN_001d8330(SwitchGroupView *, int);
void FUN_001e04c0(DrawTraversalView *, void *);
void igMatrix44f_SetIdentity(void *);
void FUN_001904f0(void *, void *, void *);
}
static inline TransformAttrView *attrAt(TransformStackView *s, int i) { return s->_data[i]; }
static inline TransformAttrView *topOf(TransformStackView *s) {
    if (s->_base >= 0) {
        return attrAt(s, s->_base);
    }
    if (s->_count != 0) {
        return attrAt(s, s->_count - 1);
    }
    return s->_default;
}
static inline TransformStackView *stackOf(TransformStateView *st) {
    return st->_stacks->_data[st->_slotOfIndex[DAT_0055efe8->_stackIndex]];
}
extern "C" int FUN_001b99d0(DrawTraversalView *o, SwitchGroupView *g) {
    char m[64];
    RefList *set;
    int n;
    int nChild;
    void *src;
    char *base;
    int j;
    int i;
    ModelViewAttrView *attr;
    int count;
    RefList *set2;
    nChild = g->_children != 0 ? g->_children->_count : 0;
    if (nChild == 0) {
        return 0;
    }
        base = topOf(stackOf(((TraversalStateHolder *)o)->_state))->_matrix;
    FUN_001b1030(o->_state, o->_baseAttr);
    count = g->_attrSets->_count;
    for (i = 0; i < count; i++) {
        if (FUN_001d8330(g, i) == 0) {
            continue;
        }
        attr = FUN_001d8310(g, i);
        if (attr != 0) {
            src = FUN_001d82f0(g, i);
            if (base != 0) {
                igMatrix44f_SetIdentity(m);
                FUN_001904f0(m, src, base);
                attr->setMatrix(m);
            } else {
                attr->setMatrix(src);
            }
            FUN_001b1030(o->_state, attr);
        }
        set = g->_attrSets->_data[i];
        n = set->_count;
        for (j = 0; j < n; j++) {
            FUN_001b1030(o->_state, set->_data[j]);
        }
        switch (g->_mode) {
        case 0:
            FUN_001e04c0(o, g->_children->_data[i % nChild]);
            break;
        case 1:
            for (j = 0; j < nChild; j++) {
                FUN_001e04c0(o, g->_children->_data[j]);
            }
            break;
        }
        if (!g->_nested) {
            for (j = n - 1; j >= 0; j--) {
                FUN_001b1100(o->_state, set->_data[j]);
            }
            if (attr != 0) {
                FUN_001b1100(o->_state, attr);
            }
        }
    }
    if (g->_nested) {
        for (i = count - 1; i >= 0; i--) {
            if (FUN_001d8330(g, i) != 0) {
                set2 = g->_attrSets->_data[i];
                for (j = set2->_count - 1; j >= 0; j--) {
                    FUN_001b1100(o->_state, set2->_data[j]);
                }
                attr = FUN_001d8310(g, i);
                if (attr != 0) {
                    FUN_001b1100(o->_state, attr);
                }
            }
        }
    }
    FUN_001b1100(o->_state, o->_baseAttr);
    return 0;
}

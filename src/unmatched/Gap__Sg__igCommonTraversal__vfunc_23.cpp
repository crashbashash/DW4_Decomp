#include "dw4/reflected.h"
struct AttrSlotList { char pad8[8]; volatile int _count; int _capacity; igObject **_data; };
struct igAttrDefaultsView;
class igAttrStackOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void push(int attr);
};
struct AttrStackView { char pad[20]; igAttrStackOps *_ops; };
struct AttrStackListView { char pad[16]; AttrStackView **_data; };
struct AttrManagerView { char pad[16]; AttrStackListView *_attrStacks; char pad2[48]; int *_firstUnit; };
class igCommonTraversalOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long getTime();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void setTime(long long t);
    char head[12];
    long long _timeLong;
    unsigned char _userTimeState;
    char pad25[27];
    AttrManagerView *_attrStack;
    char pad56[4];
    int _vc;
    char pad64[36];
    float _viewMat[16];
    char pad164[172];
    igClearAttr *_defaultTimeAttr;
};
static inline void pushAttr(AttrManagerView *m, igMetaObject *meta, int attr) {
    m->_attrStacks->_data[m->_firstUnit[meta->_id]]->_ops->push(attr);
}
extern "C" {
void FUN_001b1490(AttrManagerView *, AttrSlotList *, int, igClearAttr *);
int List_Resize(AttrSlotList *, int, int);
}
static inline void pushAttrSlot(igCommonTraversalOps *t, igClearAttr *attr) {
    int n;
    AttrManagerView *m;
    AttrSlotList *list;
    int unit;
    m = t->_attrStack;
    unit = attr->_cachedUnitID + m->_firstUnit[attr->_cachedAttrIndex];
    list = (AttrSlotList *)m->_attrStacks->_data[unit];
    igClearAttr *volatile held = attr;
    n = list->_count;
    if (n < list->_capacity) {
        list->_count = list->_count + 1;
    } else {
        List_Resize(list, n + 1, 4);
    }
    {
        igClearAttr *value = held;
        list->_data[n] = (igObject *)value;
        FUN_001b1490(m, list, unit, value);
    }
}
extern "C" {
igMetaObject *igClearAttr_GetMetaObject(void);
igMetaObject *igProjectionMatrixAttr_GetMetaObject(void);
void FUN_001b7330(igCommonTraversalOps *, float *);
void Gap__Sg__igTraversal__vfunc_23(igCommonTraversalOps *, int);
void Gap__Sg__igCommonTraversal__vfunc_23(igCommonTraversalOps *t, int root);
}
void Gap__Sg__igCommonTraversal__vfunc_23(igCommonTraversalOps *t, int root) {
    igClearAttr *attr;
    int vc = t->_vc;
    if (vc != 0) {
        pushAttr(t->_attrStack, igClearAttr_GetMetaObject(), vc);
        vc = t->_vc;
        pushAttr(t->_attrStack, igProjectionMatrixAttr_GetMetaObject(), vc);
    }
    FUN_001b7330(t, t->_viewMat);
    if (t->_userTimeState) {
        t->setTime(t->_timeLong);
    }
    ((long long *)t->_defaultTimeAttr)[2] = t->getTime();
    attr = t->_defaultTimeAttr;
    pushAttrSlot(t, attr);
    Gap__Sg__igTraversal__vfunc_23(t, root);
}

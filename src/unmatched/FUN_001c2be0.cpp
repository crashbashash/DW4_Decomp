struct EnvAttr { char _pad0[8]; short _attrIndex; short _unitOffset; };
struct EnvAttrList { char _pad0[8]; int _count; int _capacity; EnvAttr **_data; };
struct EnvSlot { char _pad0[8]; volatile int _count; int _capacity; EnvAttr **_data; char _pad14[4]; int _mark; void (*_onPop)(EnvAttr *, int); };
struct EnvSlotTable { char _pad0[16]; EnvSlot **_data; };
struct EnvAttrStack { char _pad0[16]; EnvSlotTable *_slots; char _pad14[28]; int _popArg; char _pad34[16]; int *_unitOfAttr; };
struct EnvListList { char _pad0[8]; int _count; int _capacity; EnvAttrList **_data; };
struct EnvTraversalView { char _pad0[32]; int _arg32; char _pad24[16]; EnvAttrStack *_attrStack; char _pad38[12]; int _context; };
class EnvMapShaderView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42();
    virtual void prepare(EnvTraversalView *);
    virtual void d44(); virtual void d45();
    virtual void configure(int);
    char _pad4[44];
    unsigned char _unit;
    char _pad31[11];
    unsigned char _configured;
    char _pad3d[3];
    EnvListList *_pushLists;
    EnvListList *_popLists;
    unsigned char _useContext;
};
extern "C" {
void FUN_001e07a0(EnvTraversalView *, EnvMapShaderView *);
void FUN_001dc500(int, unsigned char, int);
void FUN_001dc610(int);
void FUN_001b1490(EnvAttrStack *, EnvSlot *, int, ...);
void List_Resize(void *, int, int);
}
static inline void pushAttr(EnvAttrStack *s, EnvAttr *a) {
    EnvAttr *volatile held;
    int idx = a->_unitOffset + s->_unitOfAttr[a->_attrIndex];
    EnvSlot *l = s->_slots->_data[idx];
    int n;
    EnvAttr *t;
    if (l->_mark < 0) l->_mark = l->_count;
    held = a;
    n = l->_count;
    if (n < l->_capacity) {
        l->_count = l->_count + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    t = held;
    l->_data[n] = t;
    FUN_001b1490(s, l, idx, t);
}
static inline void popAttr(EnvAttrStack *s, EnvAttr *a) {
    int idx = a->_unitOffset + s->_unitOfAttr[a->_attrIndex];
    EnvSlot *l = s->_slots->_data[idx];
    int last = l->_count - 1;
    EnvAttr **d = l->_data;
    EnvAttr *top = d[last];
    void (*cb)(EnvAttr *, int) = l->_onPop;
    if (cb != 0 && top == a) cb(top, s->_popArg);
    l->_count = l->_count - 1;
    if (l->_count == l->_mark) l->_mark = -1;
    FUN_001b1490(s, l, idx);
}
extern "C" void FUN_001c2be0(EnvMapShaderView *self, EnvTraversalView *t) {
    EnvAttrStack *s = t->_attrStack;
    int n;
    int i;
    if (!self->_configured) self->configure(t->_arg32);
    self->prepare(t);
    n = self->_pushLists->_count;
    if (n == 0) {
        FUN_001e07a0(t, self);
        return;
    }
    if (self->_useContext) FUN_001dc500(t->_context, self->_unit, 0);
    for (i = 0; i < n; i++) {
        EnvAttrList *p = self->_pushLists->_data[i];
        int m = p->_count;
        int j;
        for (j = 0; j < m; j++) pushAttr(s, p->_data[j]);
        FUN_001e07a0(t, self);
        {
            EnvAttrList *q = self->_popLists->_data[i];
            for (j = q->_count - 1; j >= 0; j--) popAttr(s, q->_data[j]);
        }
    }
    if (self->_useContext) FUN_001dc610(t->_context);
}

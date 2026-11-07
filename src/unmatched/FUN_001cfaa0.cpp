class TraversalNode {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int getMeta();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual void setContext(int);
    char pad0[28];
    float transform[16];
};
struct TraversalMatrix { float m[16]; };
struct MatrixStack { char pad0[8]; int count; char pad1[4]; TraversalMatrix *data; };
struct NodeRefObject { int pad0; int _refCount; };
struct NodeStack { char pad0[8]; int count; char pad1[4]; NodeRefObject **data; };
class ModelTraversal;
typedef int (*TraversalCallback)(ModelTraversal *, TraversalNode *);
class ModelTraversal {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int context();
    int pad0;
    unsigned char enabled;
    TraversalCallback callback;
    char pad1[16];
    MatrixStack *matrices;
    NodeStack *nodes;
};
extern "C" {
int FUN_001ceab0(ModelTraversal *, TraversalNode *);
int FUN_001e07a0(ModelTraversal *, TraversalNode *);
void FUN_001e68e0(MatrixStack *, float *);
void List_RemoveWordAt(NodeStack *, int);
void Matrix44_Copy(TraversalMatrix *, TraversalMatrix *);
void ObjectList_AppendRetained(NodeStack *, TraversalNode *);
void igObject_Destroy(void *);
extern int DAT_00561838[4];
}
static inline int passStop(int r) {
    if (r == 2) {
        return 2;
    }
    return 0;
}
static inline TraversalMatrix popMatrix(MatrixStack *s) {
    s->count = s->count - 1;
    return s->data[s->count];
}
extern "C" int FUN_001cfaa0(ModelTraversal *self, TraversalNode *node) {
    int result;
    if (self->enabled != 0) {
        int r = self->callback(self, node);
        if (r == 1) {
            return 0;
        }
        if (r == 2) {
            int meta = DAT_00561838[0];
            int got = node->getMeta();
            if (got != meta) {
                return passStop(FUN_001e07a0(self, node));
            }
        }
    }
    node->setContext(self->context());
    ObjectList_AppendRetained(self->nodes, node);
    result = FUN_001ceab0(self, node);
    if (result == 0) {
        FUN_001e68e0(self->matrices, node->transform);
        result = FUN_001e07a0(self, node);
        {
            MatrixStack *s = self->matrices;
            TraversalMatrix m;
            s->count = s->count - 1;
            Matrix44_Copy(&m, &s->data[s->count]);
        }
    }
    {
        int last;
        NodeStack *s = self->nodes;
        NodeRefObject *o;
        last = s->count - 1;
        o = s->data[last];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(s, last);
        s->data[s->count] = 0;
    }
    return passStop(result);
}

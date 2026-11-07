struct HitMetaView { char pad0[8]; int index; };
struct HitMatrix { float m[16]; };
struct HitVector { float x, y, z; };
class HitBound {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();
    virtual HitMetaView *getMeta();
};
struct HitBoundList { char pad0[16]; HitBound **data; };
struct HitMatrixStack { char pad0[8]; int count; char pad1[4]; HitMatrix *data; };
struct HitSegment { char pad0[8]; float x, y, z; };
struct HitSegmentList { char pad0[8]; unsigned int count; char pad1[4]; HitSegment **data; };
struct HitPointerList { char pad0[16]; void **data; };
struct HitQuery { char pad0[8]; void *volume; HitSegmentList *segments; HitPointerList *aux; };
struct HitAttr;
struct HitAttrList { char pad0[8]; unsigned int count; char pad1[4]; HitAttr **data; };
struct HitNode { char pad0[12]; HitBound *bound; char pad1[16]; HitAttrList *attrs; };
struct HitReport {
    int type;
    HitQuery *query;
    int context;
    HitMatrix *matrix;
    void *object;
    float distance;
    HitVector local;
    HitVector point;
    HitVector normal;
    int index;
    int first;
    int second;
    int pad0;
};
struct HitTraversal;
typedef int (*HitCallback)(HitTraversal *, HitNode *, HitReport *);
struct HitTraversal {
    char pad0[32];
    HitMatrixStack *matrices;
    int context;
    HitQuery *query;
    unsigned int flags;
    HitCallback callback;
    HitBoundList *cache;
    HitBound *scratch;
};
extern "C" {
void FUN_0018d360(HitBound *, HitMatrix *);
int FUN_0018ffa0(void *, HitBound *);
int FUN_00190010(HitBound *, HitSegment *);
void FUN_001901b0(HitBound *, HitMatrix *);
void FUN_00191f30(float *, HitMatrix *, HitMatrix *);
void FUN_00192fc0(HitVector *, HitVector *, HitMatrix *);
int FUN_001cef70(HitTraversal *, HitAttr *, HitBound *, HitVector *, HitVector *, int *, int *, void *, long long);
void FUN_00300c00(HitBound *, HitBound *, int);
int igObject_IsKindOf(void *, void *);
float sqrtf(float);
extern void *DAT_0055f158[4];
extern void *DAT_0055f170[4];
extern void *DAT_00561a38[4];
extern void *DAT_00561ca0[4];
}
static inline HitMatrix *topMatrix(HitTraversal *self) {
    HitMatrixStack *s = self->matrices;
    return &s->data[s->count - 1];
}
extern "C" int FUN_001ceab0(HitTraversal *self, HitNode *node) {
    float determinant;
    HitReport volumeReport;
    HitReport segmentReport;
    HitMatrix inverse;
    HitReport pointReport;
    HitBound *bound = node->bound;
    if (bound == 0) {
        return 0;
    }
    if (self->matrices->count > 1) {
        HitBound *previous = bound;
        HitMetaView *m = bound->getMeta();
        HitBoundList *cache = self->cache;
        bound = cache->data[m->index];
        FUN_00300c00(bound, previous, 1);
        FUN_001901b0(bound, topMatrix(self));
    }
    if (self->flags & 1) {
        if (FUN_0018ffa0(self->query->volume, bound) != 0) {
            int r;
            HitMatrix *m;
            volumeReport.type = 1;
            volumeReport.context = self->context;
            m = topMatrix(self);
            volumeReport.object = 0;
            volumeReport.matrix = m;
            volumeReport.query = self->query;
            r = self->callback(self, node, &volumeReport);
            if (r != 0) {
                return r;
            }
        } else {
            return 1;
        }
    }
    if (self->flags & 2) {
        if (igObject_IsKindOf(node, DAT_00561a38[0]) != 0 || igObject_IsKindOf(node, DAT_00561ca0[0]) != 0) {
            bool hit;
            unsigned int i;
            HitSegmentList *segments;
            unsigned int count;
            segments = self->query->segments;
            hit = false;
            count = segments->count;
            for (i = 0; i < count; i++) {
                HitSegment *segment = segments->data[i];
                if (FUN_00190010(bound, segment) != 0) {
                    int r;
                    HitMatrix *m;
                    segmentReport.type = 2;
                    segmentReport.context = self->context;
                    m = topMatrix(self);
                    segmentReport.object = segment;
                    segmentReport.matrix = m;
                    segmentReport.query = self->query;
                    hit = true;
                    r = self->callback(self, node, &segmentReport);
                    if (r != 0) {
                        return r;
                    }
                }
            }
            if (!hit) {
                return 1;
            }
        }
    }
    if (self->flags & 4) {
        if (igObject_IsKindOf(node, DAT_00561a38[0]) != 0) {
            HitMatrix *matrix;
            unsigned int attrCount;
            unsigned int segmentCount;
            void *aux;
            HitAttrList *attrs;
            HitSegmentList *segments;
            unsigned int s;
            HitMatrixStack *stack = self->matrices;
            int n = stack->count;
            matrix = &stack->data[n - 1];
            if (n > 1) {
                FUN_00191f30(&determinant, &inverse, matrix);
            }
            attrs = node->attrs;
            attrCount = attrs->count;
            segments = self->query->segments;
            segmentCount = segments->count;
            for (s = 0; s < segmentCount; s++) {
                HitBound *volume = (HitBound *)segments->data[s];
                aux = self->query->aux->data[s];
                unsigned int a;
                if (self->matrices->count > 1) {
                    FUN_00300c00(self->scratch, volume, 1);
                    FUN_0018d360(self->scratch, &inverse);
                    volume = self->scratch;
                }
                for (a = 0; a < attrCount; a++) {
                    HitAttr *attr = attrs->data[a];
                    if (igObject_IsKindOf(attr, DAT_0055f170[0]) != 0 || igObject_IsKindOf(attr, DAT_0055f158[0]) != 0) {
                        int *f = &pointReport.first;
                        int *g = &pointReport.second;
                        *f = -1;
                        *g = -1;
                        while (FUN_001cef70(self, attr, volume, &pointReport.point, &pointReport.normal, &pointReport.first, &pointReport.second, aux, 1) != 0) {
                            HitSegment *segment = segments->data[s];
                            int r;
                            pointReport.type = 4;
                            pointReport.context = self->context;
                            pointReport.index = a;
                            pointReport.matrix = matrix;
                            pointReport.object = segment;
                            pointReport.query = self->query;
                            FUN_00192fc0(&pointReport.local, &pointReport.point, matrix);
                            {
                                float dx = segment->x - pointReport.local.x;
                                float dy = segment->y - pointReport.local.y;
                                float dz = segment->z - pointReport.local.z;
                                pointReport.distance = sqrtf(dx * dx + dy * dy + dz * dz);
                            }
                            r = self->callback(self, node, &pointReport);
                            if (r != 0) {
                                return r;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

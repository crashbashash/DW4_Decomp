struct MatrixAttrBase;
class MatrixAttrOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void setUnit(int unit);
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void setMatrix(float *m);
    unsigned int _refCount;
    short _cachedAttrIndex;
    short _cachedUnitID;
    float _matrix[1];
};
struct MatrixMetaField { char pad[8]; int _offset; };
struct AttrMetaRec { char pad[8]; int _id; };
struct AttrStackSlots { char pad[8]; volatile int _count; int _capacity; char **_data; };
struct AttrStackTable { char pad[16]; AttrStackSlots **_data; };
struct AttrMgr { char pad[16]; AttrStackTable *_attrStacks; char pad20[48]; int *_firstUnit; };
struct AttrPool { char pad[8]; int _capacity; int pad12; MatrixAttrOps **_data; int _used; };
class TraversalOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual int getTime();
    char pad4[48];
    AttrMgr *_attrStack;
    char pad56[16];
    AttrPool *_matrixPool;
    AttrPool *_timePool;
    AttrPool *_blendPool;
    AttrPool *_texPool;
};
class MatrixOwner {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual void update(int t);
    char pad4[28];
    float _matrix[16];
    int _unit;
    MatrixAttrOps *_cached;
};
extern AttrMetaRec *DAT_0055efe8;
extern AttrMetaRec *DAT_0055ecd8;
extern AttrMetaRec *DAT_0055ec68;
extern MatrixMetaField *DAT_0055ece0;
extern MatrixMetaField *DAT_0055ec70;
extern "C" {
void List_Resize(AttrStackSlots *, int, int);
void igObjectPool_Grow(AttrPool *, void *);
void FUN_001356b0(void);
void FUN_001317c0(void);
void FUN_00130c10(void);
void FUN_001904f0(void *, float *, float *);
void igAttrStackManager_MarkStackChanged(AttrMgr *, AttrStackSlots *, int, MatrixAttrOps *);
int igObject_Destroy(void *);
float *FUN_001b7f50(MatrixOwner *o, TraversalOps *arg);
}
static inline char *topAttr(AttrMgr *m, int slot) {
    int i;
    AttrStackSlots *l = m->_attrStacks->_data[slot];
    int n = l->_count;
    i = n - 1;
    if (n == 0) {
        return 0;
    }
    return l->_data[i];
}
static inline char *topAttrLate(AttrMgr *m, int slot) {
    AttrStackSlots *l = m->_attrStacks->_data[slot];
    int n = l->_count;
    int i;
    if (n == 0) {
        return 0;
    }
    i = n - 1;
    return l->_data[i];
}
static inline MatrixAttrOps *take(AttrPool *pool, void *ctor) {
    int i;
    if (pool->_used >= pool->_capacity) {
        igObjectPool_Grow(pool, ctor);
    }
    i = pool->_used;
    pool->_used = i + 1;
    return pool->_data[i];
}
static inline void pushOn(AttrMgr *m, MatrixAttrOps *attr) {
    int n;
    AttrStackSlots *list;
    int unit;
    unit = attr->_cachedUnitID + m->_firstUnit[attr->_cachedAttrIndex];
    list = m->_attrStacks->_data[unit];
    MatrixAttrOps *volatile held = attr;
    n = list->_count;
    if (n < list->_capacity) {
        list->_count = list->_count + 1;
    } else {
        List_Resize(list, n + 1, 4);
    }
    {
        MatrixAttrOps *value = held;
        list->_data[n] = (char *)value;
        igAttrStackManager_MarkStackChanged(m, list, unit, value);
    }
}
static inline void cacheAttr(MatrixOwner *o, MatrixAttrOps *a) {
    if (a != 0) {
        a->_refCount = a->_refCount + 1;
    }
    {
        MatrixAttrOps *old = o->_cached;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
            }
        }
    }
    o->_cached = a;
}
float *FUN_001b7f50(MatrixOwner *o, TraversalOps *arg) {
    int unit;
    float *parent;
    int other;
    char *top;
    TraversalOps *t;
    AttrMgr *m;
    int v;
#define attr ((MatrixAttrOps *)t)
    t = arg;
    o->update(t->getTime());
    v = o->_unit;
    parent = 0;
    m = t->_attrStack;
    switch (v) {
    case 0:
        top = topAttr(m, m->_firstUnit[DAT_0055efe8->_id]);
        if (top != 0) {
            parent = (float *)(top + 12);
        }
        t = (TraversalOps *)take(t->_matrixPool, (void *)FUN_001356b0);
        if (parent != 0) {
            FUN_001904f0((char *)attr + 12, o->_matrix, parent);
        } else {
            attr->setMatrix(o->_matrix);
        }
        pushOn(m, attr);
        cacheAttr(o, attr);
        return attr->_matrix;
    case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
        unit = v - 9;
        top = topAttrLate(m, unit + m->_firstUnit[DAT_0055ecd8->_id]);
        if (top != 0) {
            parent = (float *)(top + 12);
        }
        t = (TraversalOps *)take(t->_texPool, (void *)FUN_001317c0);
        *(short *)((char *)attr + 80) = -1;
        *(char *)((char *)attr + 82) = 0;
        attr->setUnit((short)unit);
        if (parent != 0) {
            FUN_001904f0((char *)attr + DAT_0055ece0->_offset, o->_matrix, parent);
        } else {
            attr->setMatrix(o->_matrix);
        }
        pushOn(m, attr);
        cacheAttr(o, attr);
        return (float *)((char *)attr + DAT_0055ece0->_offset);
    default:
        other = v - 1;
        top = topAttrLate(m, other + m->_firstUnit[DAT_0055ec68->_id]);
        if (top != 0) {
            parent = (float *)(top + DAT_0055ec70->_offset);
        }
        t = (TraversalOps *)take(t->_blendPool, (void *)FUN_00130c10);
        attr->setUnit((short)other);
        if (parent != 0) {
            FUN_001904f0((char *)attr + DAT_0055ec70->_offset, o->_matrix, parent);
        } else {
            attr->setMatrix(o->_matrix);
        }
        pushOn(m, attr);
        cacheAttr(o, attr);
        return (float *)((char *)attr + DAT_0055ec70->_offset);
    }
}

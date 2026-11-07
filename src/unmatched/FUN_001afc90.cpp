#include "dw4/reflected.h"
struct AttrObj { void **_vtable; unsigned int _refCount; int _id; };
struct AttrVolatileRef {
    AttrObj *volatile p;
    AttrVolatileRef(const AttrVolatileRef &o);
};
struct AttrStackRec;
struct AttrStackHolder { AttrStackRec *volatile p; };
struct AttrRef {
    AttrObj *p;
    AttrRef(const AttrRef &o);
};
class AttrDefaultManager {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual AttrVolatileRef getDefault(void *meta, int unit);
};
class AttrCaps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual int unitCount(void *capabilities);
    virtual void s30();
    virtual void onDefault(int v);
};
struct AttrStackRec { void **_vtable; unsigned int _refCount; int _count; int _capacity; int _data; AttrObj *_default; int _cachedOverride; int _popProc; int pad32; AttrObj *_lastIncrementalFlushedAttr; };
struct AttrList { char pad[8]; int _count; int _capacity; AttrObj **_data; };
struct AttrManagerRec {
    void **_vtable; unsigned int _refCount; int pad8;
    int _numAttrStacks;
    AttrList *_attrStacks;
    AttrList *_attrDefaults;
    char pad24[28];
    int _capabilityManager;
    AttrDefaultManager *_defaultManager;
    char pad60[8];
    int *_attrStackIndexTable;
    int _attrStackIndexTableSize;
};
extern "C" {
int igObject_Destroy(void *);
}
static inline void attrRelease(AttrObj *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
}
static inline void attrRetain(AttrObj *o) {
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
}
static inline void attrListSet(AttrList *l, int i, AttrObj *o) {
    attrRetain(o);
    attrRelease(l->_data[i]);
    {
        int n = l->_count;
        if (n != 0 && i >= 0 && i < n) {
            l->_data[i] = o;
        }
    }
}
static inline void attrFieldSet(AttrObj **slot, AttrObj *v) {
    attrRetain(v);
    attrRelease(*slot);
    *slot = v;
}
extern "C" {
int *FUN_00300e50(void *, int *, int);
int FUN_001d8270(AttrObj *);
int igObject_GetAllocator(void *);
AttrObj *FUN_001a5a70(int);
void ObjectList_ResizeRetained(AttrList *, int);
void FUN_001afc90(AttrManagerRec *m, AttrObj *meta);
}
void FUN_001afc90(AttrManagerRec *m, AttrObj *meta) {
    if (m->_defaultManager != 0 && m->_capabilityManager != 0) {
        int units;
        int end;
        int first;
        int i;
        int id;
        id = meta->_id;
        if (id >= m->_attrStackIndexTableSize) {
            m->_attrStackIndexTableSize = id + 4;
            m->_attrStackIndexTable = FUN_00300e50(m, m->_attrStackIndexTable, m->_attrStackIndexTableSize * 4);
        }
        units = FUN_001d8270(meta);
        if (units <= 0) {
            AttrVolatileRef def = m->_defaultManager->getDefault(meta, 0);
            units = ((AttrCaps *)def.p)->unitCount((void *)m->_capabilityManager);
            if (units <= 0) {
                units = 1;
            }
            { AttrObj *held = def.p; attrRelease(held); }
        }
        first = m->_numAttrStacks;
        end = first + units;
        ObjectList_ResizeRetained(m->_attrDefaults, end);
        ObjectList_ResizeRetained(m->_attrStacks, end);
        m->_attrStackIndexTable[id] = first;
        m->_numAttrStacks = end;
        for (i = 0; i < units;) {
            AttrVolatileRef def = m->_defaultManager->getDefault(meta, i);
            AttrStackHolder stack;
            AttrObj **slot;
            AttrObj *value;
            stack.p = (AttrStackRec *)FUN_001a5a70(igObject_GetAllocator(m));
            slot = &stack.p->_default;
            value = def.p;
            attrFieldSet(slot, value);
            stack.p->_popProc = 0;
            {
                AttrObj *d = def.p;
                stack.p->_lastIncrementalFlushedAttr = d;
            }
            value = (AttrObj *)stack.p;
            attrListSet(m->_attrStacks, first, value);
            value = def.p;
            attrListSet(m->_attrDefaults, first, value);
            { AttrObj *held = (AttrObj *)stack.p; attrRelease(held); }
            { AttrObj *held = def.p; attrRelease(held); }
            i++;
            first++;
        }
    }
}

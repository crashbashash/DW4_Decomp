
struct AttrRec { void **_vtable; unsigned int _refCount; short _cachedAttrIndex; short _cachedUnitID; int pad12; unsigned int _key; unsigned char _enabled; };
class LightDisableOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void setEnabled(int on);
    unsigned int _refCount;
    int pad8; int pad12;
    AttrRec *_light;
};
typedef void (*AttrPopProc)(AttrRec *, int);
struct LightKeyList { char pad[8]; int _count; int _capacity; unsigned int *_data; };
struct LightSlotList { char pad[8]; volatile int _count; int _capacity; AttrRec **_data; int pad20; int _cachedOverride; AttrPopProc _popProc; };
struct IntWordList { char pad[8]; int _count; int _capacity; int *_data; };
struct LightStackList { char pad[16]; LightSlotList **_data; };
struct LightPool { char pad[8]; int _capacity; int pad12; LightDisableOps **_data; int _used; };
struct LightManagerRec {
    char pad0[16];
    LightStackList *_attrStacks;
    char pad20[16];
    LightKeyList *_lightAttrAddrs;
    IntWordList *_lightAttrStackAddrs;
    LightSlotList *_updateLightAttrs;
    int _popProcData;
    char pad52[8];
    unsigned char _simpleLightMgr;
    char pad61[3];
    LightPool *_lightDisableAttrPool;
    int *_attrStackIndexTable;
};
extern "C" {
void List_Resize(LightSlotList *, int, int);
void FUN_001dca40(LightPool *, void *);
void FUN_001361b0(void);
int igObject_Destroy(void *);
void FUN_001b1490(LightManagerRec *, LightSlotList *, int);
void FUN_001b0aa0(LightManagerRec *m, AttrRec *attr, int pushed);
}
static inline int findKey(LightKeyList *list, unsigned int key0) {
    int lo;
    int hi;
    unsigned int k;
    int n;
    volatile unsigned int key;
    lo = 0;
    key = key0;
    n = list->_count;
    k = key;
    hi = n - 1;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        unsigned int v;
        v = list->_data[mid];
        if (v < k) {
            lo = mid + 1;
        } else if (k < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (n == 0) {
        return -1;
    }
    {
        unsigned int k2 = key;
        unsigned int v = list->_data[lo];
        if (k2 < v || v < k2) {
            return -1;
        }
        return lo;
    }
}
void FUN_001b0aa0(LightManagerRec *m, AttrRec *attr, int pushed) {
    volatile unsigned int keyCopy;
    int slot;
    LightSlotList *list;
    int index;
    unsigned int key = attr->_key;
    if (key == 0) {
        return;
    }
    if (m->_simpleLightMgr == 1) {
        LightPool *pool = m->_lightDisableAttrPool;
        LightDisableOps *o;
        AttrRec *light;
        int i;
        if (pool->_used >= pool->_capacity) {
            FUN_001dca40(pool, (void *)FUN_001361b0);
        }
        i = pool->_used;
        pool->_used = i + 1;
        o = pool->_data[i];
        light = (AttrRec *)attr->_key;
        if (light != 0) {
            light->_refCount = light->_refCount + 1;
        }
        if (o->_light != 0) {
            AttrRec *old = o->_light;
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
            }
        }
        o->_light = light;
        o->setEnabled((attr->_enabled != 0) ^ 1);
        {
            int n;
            LightSlotList *l;
            l = m->_updateLightAttrs;
            n = l->_count;
            if (n < l->_capacity) {
                l->_count = l->_count + 1;
            } else {
                List_Resize(l, n + 1, 4);
            }
            l->_data[n] = (AttrRec *)o;
        }
        return;
    }
    keyCopy = key;
    {
        LightKeyList *keys = m->_lightAttrAddrs;
        index = findKey(keys, keyCopy);
    }
    if (index == -1) {
        return;
    }
    slot = m->_lightAttrStackAddrs->_data[index] + m->_attrStackIndexTable[attr->_cachedAttrIndex];
    if (pushed != 0) {
        AttrRec *top;
        AttrPopProc proc;
        int i;
        list = m->_attrStacks->_data[slot];
        i = list->_count - 1;
        top = list->_data[i];
        proc = list->_popProc;
        if (proc != 0 && top == attr) {
            proc(top, m->_popProcData);
        }
        list->_count = list->_count - 1;
        if (list->_count == list->_cachedOverride) {
            list->_cachedOverride = -1;
        }
        FUN_001b1490(m, list, slot);
    } else {
        AttrRec *top;
        AttrPopProc proc;
        int i;
        LightSlotList *other = m->_attrStacks->_data[slot];
        i = other->_count - 1;
        top = other->_data[i];
        proc = other->_popProc;
        if (proc != 0) {
            proc(top, m->_popProcData);
        }
        other->_count = other->_count - 1;
        FUN_001b1490(m, other, slot);
    }
}

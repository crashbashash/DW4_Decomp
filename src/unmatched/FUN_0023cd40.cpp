struct SortedIntList {
    int _vtable;
    unsigned int _refCount;
    int _count;
    int _capacity;
    int *_data;
    int indexOf(int key) const {
        int lo = 0;
        int hi = _count - 1;
        int mid;
        int e;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            e = _data[mid];
            if (e < key) {
                lo = mid + 1;
            } else if (key < e) {
                hi = mid - 1;
            } else {
                return mid;
            }
        }
        if (_count == 0) {
            return -1;
        }
        e = _data[lo];
        if (key < e || e < key) {
            return -1;
        }
        return lo;
    }
};

struct BoundClass {
    char pad0[56];
    BoundClass *next;
};

class BoundObject {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19();
    virtual BoundClass *getClass();
};

struct ScriptMeta {
    char pad0[84];
    ScriptMeta *base;
};

struct ScriptType {
    int pad0;
    BoundClass *boundClass;
    ScriptMeta *meta;
};

extern "C" {
extern int DAT_00498668[4];
extern SortedIntList *DAT_0056de38[4];
int FUN_00242430(ScriptMeta *meta, int tag, int *depth);
/* matching construct: a small sweep of spellings */
int FUN_0023cd40(ScriptType *type, int tag, BoundObject *object, int *depth);
}

int FUN_0023cd40(ScriptType *type, int tag, BoundObject *object, int *depth) {
    if (type->boundClass) {
        BoundClass *c;
        bool known = tag == DAT_00498668[0] || DAT_0056de38[0]->indexOf(tag) >= 0;
        if (!known) {
            return 0;
        }
        *depth = 0;
        for (c = object->getClass(); c; c = c->next) {
            if (c == type->boundClass) {
                return 1;
            }
            (*depth)++;
        }
        return 0;
    }
    if (type->meta) {
        *depth = 0;
        if (FUN_00242430(type->meta, tag, depth) || (type->meta->base && FUN_00242430(type->meta->base, tag, depth))) {
            return 1;
        }
        return 0;
    }
    return 1;
}

struct FieldBindMeta;
class FieldBindTarget { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual FieldBindMeta *GetMeta();
    virtual void Assign(void *value);
};
struct FieldBindRefCounted { int vt; unsigned int _refCount; };
struct FieldBindSlotList { int vt; int rc; int count; int capacity; FieldBindTarget **data; };
struct FieldBindSet { int vt; int rc; int count; int pad12; FieldBindTarget **targets; char pad20[24]; FieldBindSlotList *overrides; };
struct FieldBindItem { int pad0; int pad4; int offset; char pad12[12]; FieldBindTarget *source; };
extern "C" {
FieldBindTarget *FUN_002d7d60(FieldBindSet *, int);
FieldBindItem *FUN_002d7e90(FieldBindSet *, int);
int igObject_IsKindOf(void *, int);
int igMetaObject_GetFieldCount(FieldBindMeta *);
FieldBindItem *igMetaObject_GetFieldAt(FieldBindMeta *, int);
void igObjectRefMetaField_Assign(FieldBindItem *, FieldBindTarget *, void *);
void igObject_Destroy(void *);
extern int DAT_00585b70;
extern int DAT_00585b20;
int FUN_002d7f10(FieldBindSet *self, FieldBindRefCounted **field, FieldBindRefCounted **value);
}
static inline void releaseBound(FieldBindRefCounted *o) {
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
}
static inline FieldBindItem *castBinding(FieldBindItem *o) {
    if (o != 0 && igObject_IsKindOf(o, DAT_00585b70) != 0) {
        return o;
    }
    return 0;
}
static inline FieldBindItem *castRefField(FieldBindItem *o) {
    if (o != 0 && igObject_IsKindOf(o, DAT_00585b20) != 0) {
        return o;
    }
    return 0;
}
static inline void setSlot(FieldBindSlotList *l, int i, FieldBindRefCounted *v) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = (FieldBindTarget *)v;
    }
}
int FUN_002d7f10(FieldBindSet *self, FieldBindRefCounted **field, FieldBindRefCounted **value) {
    int changed = 0;
    int i;
    int j;
    int n;
    FieldBindRefCounted *current;
    FieldBindItem *item;
    FieldBindTarget * volatile source;
    FieldBindTarget *held;
    for (i = 0; i < self->count; i++) {
        current = *field;
        if (FUN_002d7d60(self, i) == (FieldBindTarget *)current) {
            if (self->overrides != 0) {
                releaseBound(*field);
                if (*value != 0) {
                    (*value)->_refCount = (*value)->_refCount + 1;
                }
                setSlot(self->overrides, i, *value);
            } else {
                self->targets[i]->Assign(*value);
            }
            changed++;
        }
        item = castBinding(FUN_002d7e90(self, i));
        if (item != 0) {
            source = item->source;
            held = source;
            if (held != 0) {
                ((FieldBindRefCounted *)held)->_refCount = ((FieldBindRefCounted *)held)->_refCount + 1;
            }
            held = source;
            if (held == 0) {
                held = source;
                releaseBound((FieldBindRefCounted *)held);
                continue;
            }
            n = igMetaObject_GetFieldCount(held->GetMeta());
            for (j = 0; j < n; j++) {
                FieldBindItem *f;
                held = source;
                f = castRefField(igMetaObject_GetFieldAt(held->GetMeta(), j));
                if (f != 0) {
                    held = source;
                    if (*(FieldBindRefCounted **)((char *)held + f->offset) == *field) {
                        igObjectRefMetaField_Assign(f, held, *value);
                        changed++;
                    }
                }
            }
            held = source;
            releaseBound((FieldBindRefCounted *)held);
        }
    }
    return changed;
}

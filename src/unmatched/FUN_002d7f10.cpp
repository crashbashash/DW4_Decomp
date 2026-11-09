#include "dw4/igSmartPointer.h"
struct FieldBindMeta;
class FieldBindObject : public igVirtualObject { public:
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
struct FieldBindSlotList : public igObject { int count; int capacity; FieldBindObject **data; };
struct FieldBindSet : public igObject { int count; int pad12; FieldBindObject **targets; char pad20[24]; FieldBindSlotList *overrides; };
struct FieldBindItem { int pad0; int pad4; int offset; char pad12[12]; FieldBindObject *source; };
extern "C" {
FieldBindObject *FUN_002d7d60(FieldBindSet *, int);
FieldBindItem *FUN_002d7e90(FieldBindSet *, int);
int igObject_IsKindOf(void *, int);
int igMetaObject_GetFieldCount(FieldBindMeta *);
FieldBindItem *igMetaObject_GetFieldAt(FieldBindMeta *, int);
void igObjectRefMetaField_Assign(FieldBindItem *, igVirtualObject *, void *);
extern int DAT_00585b70;
extern int DAT_00585b20;
int FUN_002d7f10(FieldBindSet *self, FieldBindObject **field, FieldBindObject **value);
}
static inline void releaseBound(FieldBindObject *o) {
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
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
static inline void setSlot(FieldBindSlotList *l, int i, FieldBindObject *v) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = (FieldBindObject *)v;
    }
}

int FUN_002d7f10(FieldBindSet *self, FieldBindObject **field, FieldBindObject **value) {
    int changed = 0;
    int i;
    int j;
    int n;
    FieldBindObject *current;
    FieldBindItem *item;
    for (i = 0; i < self->count; i++) {
        current = *field;
        if (FUN_002d7d60(self, i) == (FieldBindObject *)current) {
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
            igSmartPointer<igVirtualObject> source(item->source, kRetainReference);
            if (source.get() == 0) {
                continue;
            }
            n = igMetaObject_GetFieldCount(((FieldBindObject *)source.get())->GetMeta());
            for (j = 0; j < n; j++) {
                FieldBindItem *f;
                f = castRefField(igMetaObject_GetFieldAt(((FieldBindObject *)source.get())->GetMeta(), j));
                if (f != 0) {
                    if (*(FieldBindObject **)((char *)source.get() + f->offset) == *field) {
                        igObjectRefMetaField_Assign(f, source.get(), *value);
                        changed++;
                    }
                }
            }
        }
    }
    return changed;
}

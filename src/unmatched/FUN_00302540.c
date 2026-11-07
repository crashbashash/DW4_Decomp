int igObject_Destroy();
typedef struct Obj { char pad[4]; int _refCount; } Obj;
typedef struct Field { char pad[8]; int _offset; } Field;
typedef struct L { char pad[8]; int count; int cap; Obj **data; } L;
static inline void retain(Obj *o) { if (o != 0) { o->_refCount = o->_refCount + 1; } }
static inline void release(Obj *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
}
static inline void setAt(L *l, int i, Obj *v, int off) {
    int n = l->count;
    if (n != 0 && i >= 0 && i < n) {
        *(Obj **)((char *)l->data + off) = v;
    }
}
static inline void setPrev(L *l, int i, Obj *v, int off) {
    int n = l->count;
    if (n != 0 && i >= 0 && i < n) {
        ((Obj **)((char *)l->data + off))[-1] = v;
    }
}
void FUN_00302540(L *self, Field *field) {
int i; int n; Obj *a; Obj *b; int off; int swapped; unsigned int prev; unsigned int cur; Obj **p;

    if (field == 0) {
        return;
    }
    n = self->count;
    swapped = 1;
    if (n < 2) { return; }
    while (swapped > 0) {
        swapped = 0;
        prev = *(unsigned int *)((char *)self->data[0] + field->_offset);
        for (i = 1; i < n; i++) {
            off = i * 4;
            p = (Obj **)((char *)self->data + off);
            b = p[0];
            cur = *(unsigned int *)((char *)b + field->_offset);
            if (cur < prev) {
                a = p[-1];
                retain(a);
                release(*(Obj **)((char *)self->data + off));
                setAt(self, i, a, off);
                retain(b);
                release(*(Obj **)((char *)self->data + off - 4));
                setPrev(self, i - 1, b, off);
                swapped = 1;
            } 
            prev = cur;
        }
    }
}

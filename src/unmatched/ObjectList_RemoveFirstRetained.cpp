struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } };
extern "C" {
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
int List_RemoveWordAt(...);
int igObject_Destroy(...);
}
struct ObjectListItem { int vt; int _refCount; };
struct ObjectListView { char pad[8]; int count; int cap; ObjectListItem **data; };
static inline int find(ObjectListView *l, ObjectListItem **vp, int i) {
    int n = l->count;
    ObjectListItem *v = *vp;
    for (; i < n; i++) {
        if (v == l->data[i]) {
            return i;
        }
    }
    return -1;
}
static inline void release(ObjectListItem *o) { if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } } }
extern "C" igResult ObjectList_RemoveFirstRetained(ObjectListView *self, ObjectListItem *value, int start) {
    ObjectListItem *v;
    int i;
    *(ObjectListItem **)&v = value;
    i = find(self, &v, start);
    if (i >= 0) {
        ObjectListItem *o = self->data[i];
        unsigned int k = i;
        if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } }
        List_RemoveWordAt(self, k);
        self->data[self->count] = 0;
        return DAT_004fb410;
    }
    return DAT_004fb418;
}

struct Counted { int vtable; int references; };
extern "C" {
void igObject_Destroy(Counted *);
int igObject_GetAllocator(void *);
}
struct Entry : Counted { int a; int b; Counted *value; };
extern "C" {
Entry *FUN_0044dc20(int);
int ObjectList_AppendRetained(int, Entry *);
}
struct AttrEntryOwner { char pad[8]; int entries; };
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        Counted *object = p;
        if (object != 0) {
            object->references = object->references - 1;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    T *operator->() const { return p; }
    operator T *() const { return p; }
};
static inline void assign(Counted **slot, Counted *value) {
    Counted *old;
    if (value != 0) {
        value->references = value->references + 1;
    }
    old = *slot;
    if (old != 0) {
        old->references = old->references - 1;
        if ((old->references & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = value;
}
extern "C" void FUN_004573f0(AttrEntryOwner *owner, int a, int b, Counted *value) {
    igSmartPointer<Entry> entry(FUN_0044dc20(igObject_GetAllocator(owner)));
    entry->a = a;
    entry->b = b;
    assign(&entry->value, value);
    ObjectList_AppendRetained(owner->entries, entry);
}

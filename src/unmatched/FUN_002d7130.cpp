struct Counted { int vtable; int references; };
struct ObjectList : Counted { int count; int capacity; Counted **data; };
struct Owner { char pad[8]; ObjectList *children; };
extern "C" {
ObjectList *FUN_002bd680(int);
int FUN_002d6f50(Owner *, Counted *, int);
int ObjectList_AppendRetainedList(ObjectList *, ObjectList *);
void igObject_Destroy(Counted *);
int igObject_GetAllocator(Owner *);
}
struct ListRef {
    ObjectList *p;
    ListRef(ObjectList *list) : p(list) {}
    ~ListRef() {
        Counted *object = p;
        if (object != 0) {
            object->references = object->references - 1;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    ObjectList *operator->() const { return p; }
    operator ObjectList *() const { return p; }
};
extern "C" void FUN_002d7130(Owner *owner) {
    ListRef copy(FUN_002bd680(igObject_GetAllocator(owner)));
    ObjectList_AppendRetainedList(copy, owner->children);
    ObjectList *children = owner->children;
    int count = children->count;
    int i;
    for (i = 0; i < count; i++) {
        Counted *child = children->data[i];
        if (child != 0) {
            child->references = child->references - 1;
            if ((child->references & 0x7FFFFF) == 0) {
                igObject_Destroy(child);
            }
        }
    }
    int end = children->count;
    int j;
    for (j = 0; j < end; j++) {
        children->data[j] = 0;
    }
    children->count = 0;
    for (i = 0; i < copy->count; i++) {
        FUN_002d6f50(owner, copy->data[i], 0);
    }
}

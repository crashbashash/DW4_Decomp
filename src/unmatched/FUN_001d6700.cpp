extern "C" {
struct ChildOwner { char pad[20]; int f20; };
struct ChildObject { int word0; int references; };
int FUN_001d6790(...);
ChildObject *FUN_002c72c0(...);
int FUN_002d8620(...);
void igObject_Destroy(ChildObject *);
int igObject_GetAllocator(...);
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *object = p;
        if (object != 0) {
            --object->references;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    T *get() const { return p; }
};
void FUN_001d6700(ChildOwner *self) {
    igSmartPointer<ChildObject> created(FUN_002c72c0(igObject_GetAllocator(self)));
    FUN_002d8620(created.get(), self->f20, 0, 0);
    FUN_001d6790(self, created.get());
}
}

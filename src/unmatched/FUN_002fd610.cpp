struct Instance { int vtable; int references; };
extern "C" {
Instance *igMetaObject_CreateInstanceDefault(int);
void igObject_Destroy(Instance *);
}
static inline void retain(Instance *object) {
    if (object != 0) {
        object->references = object->references + 1;
    }
}
static inline void release(Instance *object) {
    if (object != 0) {
        object->references = object->references - 1;
        if ((object->references & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) { retain(p); }
    ~igSmartPointer() { release(p); }
};
extern "C" int FUN_002fd610(Instance **out, int meta) {
    igSmartPointer<Instance> created(igMetaObject_CreateInstanceDefault(meta));
    release(created.p);
    *out = created.p;
    retain(*out);
    return 0;
}

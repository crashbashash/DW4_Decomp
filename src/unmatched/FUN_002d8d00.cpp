class R { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); int rc; int f8; int f12; int f16; int f20; };
struct Lst { char pad[8]; int n; };
extern "C" {
void *FUN_002c77e0(...);
int FUN_002d7d60(...);
int FUN_002d86b0(...);
int List_InsertWords(...);
int igNamedObject_SetName(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00586730[4];
int FUN_002d8d00(Lst *list, int key, int name, int val);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    T *get() const { return p; }
};
struct Retained {
    R *p;
    Retained(R *object) : p(object) {
        if (p != 0) {
            p->rc = p->rc + 1;
        }
    }
};
int FUN_002d8d00(Lst *list, int key, int name, int val) {
    int idx, cnt;
    if (key == 0) {
        return -1;
    }
    idx = FUN_002d86b0(list, DAT_00586730[0], key);
    cnt = list->n;
    if (cnt > 0) {
        if (idx < cnt) {
            int f = FUN_002d7d60(list, idx);
            if (f == key) return -1;
        }
    }
    igSmartPointer<R> entry((R *)FUN_002c77e0(igObject_GetAllocator(list)));
    igNamedObject_SetName(entry.get(), name);
    entry.get()->f16 = val;
    entry.get()->f20 = 2;
    entry.get()->vX(key);
    entry.get()->f12 = idx;
    Retained retained(entry.get());
    List_InsertWords(list, idx, 1, &retained);
    return entry.get()->f12;
}

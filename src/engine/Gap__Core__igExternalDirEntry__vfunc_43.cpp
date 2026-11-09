struct Obj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(int); virtual void v22(); virtual void v23(void*); unsigned rc; int f8; int f12; int p16; int f20; };
struct Arg { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual Obj* v19(int); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(void*); int p4[5]; int f24; int f28; int f32; };
struct G { char p[64]; int f64; };
extern "C" {
Obj *FUN_002c72c0(int);
int FUN_002d8fe0(Obj*, int);

int FUN_00308850(int, Obj*);
int ObjectList_AppendRetained(Obj*, Obj*);
int igNamedObject_SetName(Obj*, int);
void igObject_Destroy(Obj*);

int igObject_GetAllocator(Arg*);
extern G *DAT_00586dc8[4];
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {
        T *o = p;
        if (o != 0) {
            o->rc = o->rc + 1;
        }
    }
    igSmartPointer(const igSmartPointer &other) : p(other.p) {
        T *o = p;
        if (o != 0) {
            o->rc = o->rc + 1;
        }
    }
    ~igSmartPointer() {
        T *o = p;
        if (o != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    void clear() {
        T *o = p;
        if (o != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    T *get() const { return p; }
};
extern "C" igSmartPointer<Obj> FUN_003087a0(int, int);
static inline void releaseObject(Obj *object) {
    object->rc = object->rc - 1;
    if ((object->rc & 0x7FFFFF) == 0) {
        igObject_Destroy(object);
    }
}
extern "C" int Gap__Core__igExternalDirEntry__vfunc_43(Arg *arg0, void (*arg1)(Arg *));
int Gap__Core__igExternalDirEntry__vfunc_43(Arg *arg0, void (*arg1)(Arg *)) {
    int allocator;
    int directory = DAT_00586dc8[0]->f64;
    igSmartPointer<Obj> list = FUN_003087a0(directory, arg0->f28);
    if (list.get() == 0) {
        allocator = igObject_GetAllocator(arg0);
        list.clear();
        list.p = FUN_002c72c0(allocator);
        FUN_002d8fe0(list.get(), arg0->f28);
        FUN_00308850(directory, list.get());
    }
    list.get()->v23(arg0);
    if (arg0->f24 == 0) arg0->v42((void *)arg1);
    if (arg0->f24 == 0 && arg1 != 0) arg1(arg0);
    if (arg0->f24 != 0) {
        igSmartPointer<Obj> entry(arg0->v19(1));
        releaseObject(entry.get());
        igNamedObject_SetName(entry.get(), arg0->f32);
        entry.get()->f20 = 0;
        entry.get()->v21(arg0->f24);
        entry.get()->f12 = list.get()->f8;
        ObjectList_AppendRetained(list.get(), entry.get());
        return 1;
    }
    return 0;
}

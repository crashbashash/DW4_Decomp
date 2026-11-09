extern "C" {
int strcat(...);
int strcpy(...);
int strlen(...);
class Obj *FUN_002c37e0(...);
void *FUN_002d8e70(...);
int FUN_00300f50(...);
int igObject_AllocateStorage(...);
int igObject_Destroy(class Obj *);
int igObject_GetAllocator(...);
extern int DAT_004f9a48[4];
extern int DAT_004f9a50[4];
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void vX(void *); unsigned _refCount; int f8; char pad[148]; int f160; };
class Ent { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vY(void *); int pad[5]; int f24; char *f28; void *f32; int pad2[1]; char *f40; };
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    T *get() const { return p; }
};
extern "C" int Gap__Core__igExternalDirEntry__vfunc_44(Ent *arg0, int arg1) {
    igSmartPointer<Obj> stream(FUN_002c37e0(igObject_GetAllocator(arg0)));
    char *s1;
    int len;
    int c;
    char *buf;
    stream.get()->f160 = arg1;
    stream.get()->vX(arg0->f28);
    if (stream.get()->f8 == 0) {
        s1 = arg0->f28;
        len = strlen(arg0->f40);
        len = len + strlen(s1);
        c = strlen(&DAT_004f9a48[0]);
        buf = (char *)igObject_AllocateStorage(arg0, c + len + 1);
        strcpy(buf, arg0->f40);
        strcat(buf, &DAT_004f9a48[0]);
        strcat(buf, arg0->f28);
        stream.get()->vX(buf);
        FUN_00300f50(arg0, buf);
    }
    arg0->vY(FUN_002d8e70(stream.get(), arg0->f32));
    if (arg0->f24 == 0) {
        arg0->vY(FUN_002d8e70(stream.get(), &DAT_004f9a50[0]));
    }
    return arg0->f24 != 0;
}

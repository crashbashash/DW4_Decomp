extern "C" {
int FUN_001c66c0(void *, int);
int FUN_00306770(int, int, int, void *, int *, int);
int igObject_Destroy(void *);
extern int DAT_004e4660[4];
}
struct ShaderObject { int w0; int refs; };
struct Factory { char pad32[32]; int f32; int f36; int f40; };
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {
        if (p != 0) {
            p->refs = p->refs + 1;
        }
    }
    igSmartPointer(const igSmartPointer &other) : p(other.p) {
        if (p != 0) {
            p->refs = p->refs + 1;
        }
    }
    ~igSmartPointer() {
        T *o = p;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
};
extern "C" igSmartPointer<ShaderObject> Gap__Sg__igIniShaderFactory__vfunc_24(Factory *self, int name) {
    igSmartPointer<ShaderObject> shader(0);
    if (FUN_001c66c0(self, 0) == 0) {
        return igSmartPointer<ShaderObject>(0);
    }
    if (FUN_00306770(self->f32, self->f40, name, &shader.p, &DAT_004e4660[0], 0) == 0) {
        return igSmartPointer<ShaderObject>(0);
    }
    return shader;
}

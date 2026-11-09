#include "dw4/igSmartPointer.h"
struct Obj : public igObject { int f8; };
struct E { int p0, p4, p8; Obj *f12; int f16; };
struct P { int pad[5]; int f20; int pad2[1]; int f28; };
extern "C" {
void StringChunk_ReleaseHeader(int, int *);
}

struct StringRef {
    char *s;
    StringRef(const StringRef &other) : s(other.s) {
        if (s != 0) {
            *(int *)(s - 4) = *(int *)(s - 4) + 1;
        }
    }
    ~StringRef() {
        if (s != 0) {
            int *header = (int *)(s - 8);
            if (--header[1] == 0) {
                StringChunk_ReleaseHeader(header[0], header);
            }
        }
    }
};
extern "C" {
int FUN_001c6520(P *, int);
int FUN_001c66c0(P *, int);
StringRef FUN_001c6fa0(P *);
int FUN_001ccd10(P *, int);
igSmartPointer<Obj> FUN_001cd9f0(P *, char *);
igSmartPointer<Obj> FUN_001cdbb0(P *, int);
int FUN_002da780(Obj *);
int FUN_002da850(Obj *, int);
E *FUN_00307630(int, int);
int FUN_00307650(int);
int FUN_0030ba90(int, void *);
extern int DAT_004c22f0[4];
extern int DAT_004e46e0[4];
void Gap__Sg__igIniShaderFactory__vfunc_27(P *self) {
    if (self->f20 != 0) {
        FUN_001c6520(self, 0);
        FUN_001c66c0(self, 0);
        StringRef name = FUN_001c6fa0(self);
        if (name.s != 0) {
            igSmartPointer<Obj> shader((Obj *)0, kRetainReference);
            shader = FUN_001cd9f0(self, name.s);
            if (shader.get() != 0) {
                int v = FUN_002da780(shader.get());
                FUN_001ccd10(self, v);
                FUN_002da850(shader.get(), v);
            }
        }
        for (int i = 0; i < FUN_00307650(self->f28); i++) {
            E *e = FUN_00307630(self->f28, i);
            if (e != 0 && e->f16 != 0 && e->f12 != 0 && FUN_0030ba90(e->f16, &DAT_004e46e0[0]) != 0) {
                int a2;
                if (e->f12->f8 == 0) a2 = DAT_004c22f0[0]; else a2 = e->f12->f8;
                FUN_001cdbb0(self, a2);
            }
        }
    }
}
}

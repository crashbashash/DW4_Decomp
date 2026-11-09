#include "dw4/igSmartPointer.h"
extern "C" {
void *FUN_00131390(int);
void *FUN_00139600(int);
int Gap__Core__igObject__vfunc_11(void *);
int ObjectList_AppendRetained(unsigned, void *);
int igObject_GetAllocator(void *);
}
class Layer : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setEnabled(int);
  };
class FillLayer : public Layer {};
class OutlineLayer : public Layer {};
struct FontImage { char pad[20]; int layers; int state; char pad3[4]; int base; };

extern "C" void Gap__Bec__beFontImage__vfunc_11(FontImage *self, int enable) {
    Gap__Core__igObject__vfunc_11(self);
    if (enable != 0) {
        ObjectList_AppendRetained((unsigned)self->layers, (void *)self->base);
        igSmartPointer<FillLayer> first((FillLayer *)FUN_00139600(igObject_GetAllocator(self)));
        first.get()->setEnabled(1);
        ObjectList_AppendRetained((unsigned)self->layers, first.get());
        igSmartPointer<OutlineLayer> second((OutlineLayer *)FUN_00131390(igObject_GetAllocator(self)));
        second.get()->setEnabled(1);
        ObjectList_AppendRetained((unsigned)self->layers, second.get());
        self->state = 0x10001;
    }
}

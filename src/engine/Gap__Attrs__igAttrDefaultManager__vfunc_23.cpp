#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"

typedef igSmartPointer<igObject> igObjectPointer;
class DefaultSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual igObjectPointer create(); };
extern "C" {
igObjectPointer FUN_0013ba30(int, igObjectPointer);
int FUN_0013c060();
igObjectPointer Gap__Attrs__igAttrDefaultManager__vfunc_23(DefaultSource *source) {
    igObjectPointer created = source->create();
    igObjectPointer wrapped = FUN_0013ba30(FUN_0013c060(), igObjectPointer(created.get(), kRetainReference));
    return wrapped;
}
}

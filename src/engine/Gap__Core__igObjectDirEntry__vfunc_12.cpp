/* 0x003010f0 — Gap__Core__igObjectDirEntry__vfunc_12
 * Drop the entry's object reference: virtual slot 92 (vfunc_23) is the setter of
 * _ref (+24) that retains the new value and releases the old one (0x003016f0), so
 * calling it with 0 releases the held object; the igObject default of this slot
 * (an empty stub) then runs. */
#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_10(...);
void Gap__Core__igObjectDirEntry__vfunc_12(igObjectDirEntry *self);
}
/* ABI dispatch view of virtual slot 92 (21 leading virtuals); never instantiated. */
class DirEntryRefSetterView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int SetRef(int);
};

void Gap__Core__igObjectDirEntry__vfunc_12(igObjectDirEntry *self) {
    ((DirEntryRefSetterView *)self)->SetRef((int)(0));
    Gap__Core__igObject__vfunc_10(self);
}

#include "dw4/reflected.h"
/* Refcount field as a 23+9 bit-field (read-modify-write with a 64-bit constant) and a 43-slot
 * virtual call. */
extern "C" {
int memset(...);
int igObject_InitHeader(...);
extern int DAT_0052f510[4];
}
struct Ref { int pad0; int f4; };
struct BF { unsigned lo : 23; unsigned hi : 9; };
/* dispatch-only view of the object: 43 vtable slots then the init slot (no fields) */
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void vX(); };
/* matching construct: the word at +16 is stored/loaded as a reference pointer (the reflected _resolveState is a 1-byte bool there; code wins); the vtable is the reflected int _vtable, called through slot 45 */
extern "C" igMemoryPoolContextInfo *igMemoryPoolContextInfo_Construct(igMemoryPoolContextInfo *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)&DAT_0052f510[0];
    arg0->_name = 0x1E;
    arg0->_directory = 0;
    *(Ref **)&arg0->_resolveState = 0;
    if (*(Ref **)&arg0->_resolveState != 0) {
        (*(Ref **)&arg0->_resolveState)->f4 += 1;
    }
    arg0->_refCount = 0;
    ((BF *)&arg0->_refCount)->lo = 1;
    memset(&arg0->_memoryPoolInfos, 0, 0x19E0);
    ((Obj *)arg0)->vX();
    return arg0;
}

/* 0x002e2c30 — Gap__Core__igExternalIndexedEntry__vfunc_32. Banked by tools/retype_struct_member.py (shape: base):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002d7d60(...);
int FUN_002d7da0(...);
void Gap__Core__igExternalIndexedEntry__vfunc_32(igExternalIndexedEntry *arg0, void *arg1);
}
class DW4VC_92_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
void Gap__Core__igExternalIndexedEntry__vfunc_32(igExternalIndexedEntry *arg0, void *arg1) {
    ((DW4VC_92_1 *)(((char *)(arg0) + 0)))->vX((int)(FUN_002d7d60(*(int *)(*(int *)((char *)(*(int *)((char *)(arg1) + 24)) + 16) + (arg0->_directoryIndex * 4)), arg0->_entryIndex)));
    FUN_002d7da0(arg1, arg0->_index, arg0->_ref);
}

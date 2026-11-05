#include "dw4/reflected.h"
extern "C" {
int igObject_WritePersistentFields(int, int, void *, int, unsigned char);
void Gap__Core__igObjectDirEntry__vfunc_40(igObjectDirEntry *arg0, void *arg1);
}
class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
class DW4VC_108_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); };
void Gap__Core__igObjectDirEntry__vfunc_40(igObjectDirEntry *arg0, void *arg1) {
    int temp_v0;

    temp_v0 = ((DW4VC_108_0 *)(((char *)(arg1) + 0)))->vX();
    ((DW4VC_104_1 *)(((char *)(arg1) + 0)))->vX((int)(temp_v0 + igObject_WritePersistentFields(arg0->_ref, temp_v0, arg1, *(int *)((char *)(arg1) + 192), *(unsigned char *)((char *)(arg1) + 168))));
}

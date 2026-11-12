#include "dw4/reflected.h"

extern "C" int Gap__Core__igObject__vfunc_07(...);
extern "C" int igMetaObject_CountInstances(...);
extern "C" int Gap__igAdxAudio__vfunc_20(void);
extern "C" void Gap__Core__igObject__vfunc_08__002ff0f0(void);
extern "C" void Gap__igAdxAudio__vfunc_08(void);
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" void Gap__igAdxAudio__vfunc_07(igAdxAudio *arg0);
extern "C" int g_igAdxAudio_metaObject[4];

void Gap__igAdxAudio__vfunc_07(igAdxAudio *arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    arg0->_bIsInitialized = 0;
    *(int *)((char *)(arg0) + 44) = 0;
}

int Gap__igAdxAudio__vfunc_20(void)
{
    return g_igAdxAudio_metaObject[0];
}

void Gap__igAdxAudio__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

#include "dw4/reflected.h"
extern "C" {
int igObject_IsKindOf(int, int);
int Memory_DuplicateBuffer(int);
void Memory_FreeOwnedBufferUnchecked(int);
unsigned int Memory_GetBufferSize(int);
void igMemoryRefMetaField_ReleaseElementRefs(igMemoryRefMetaField *, int, int);
extern int DAT_00585b20[4];
extern int DAT_00585d80[4];
void igMemoryRefMetaField_DeepCopy(igMemoryRefMetaField *arg0, int arg1, int arg2);
}
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int v19(int); };
void igMemoryRefMetaField_DeepCopy(igMemoryRefMetaField *m, int arg1, int arg2) {
    int a;
    igMemoryRefMetaField_ReleaseElementRefs(m, arg1, arg2);
    if (m->_releaseOnCopy != 0) {
        int p = *(int *)(arg1 + m->_offset);
        if (p != 0) Memory_FreeOwnedBufferUnchecked(p);
    }
    {
        int s = *(int *)(arg2 + m->_offset);
        if (s != 0) a = Memory_DuplicateBuffer(s); else a = 0;
        *(int *)(arg1 + m->_offset) = a;
    }
    if (m->_memType != 0) {
        if (igObject_IsKindOf(m->_memType, DAT_00585b20[0]) != 0) {
            int src = *(int *)(arg2 + m->_offset);
            int dst = *(int *)(arg1 + m->_offset);
            if (src != 0 && dst != 0) {
                unsigned n = Memory_GetBufferSize(src) >> 2;
                int i;
                for (i = 0; i < (int)n; i++) {
                    V *e = *(V **)(src + i * 4);
                    int r = 0;
                    if (e != 0) r = e->v19(1);
                    *(int *)(dst + i * 4) = r;
                }
            }
        } else if (igObject_IsKindOf(m->_memType, DAT_00585d80[0]) != 0) {
            int src = *(int *)(arg2 + m->_offset);
            int dst = *(int *)(arg1 + m->_offset);
            unsigned n = Memory_GetBufferSize(src) >> 2;
            int i;
            for (i = 0; i < (int)n; i++) {
                int e = *(int *)(src + i * 4);
                int r;
                if (e != 0) r = Memory_DuplicateBuffer(e); else r = 0;
                *(int *)(dst + i * 4) = r;
            }
        }
    }
}

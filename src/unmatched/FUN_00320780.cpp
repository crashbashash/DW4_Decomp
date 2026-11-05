#include "dw4/reflected.h"
extern "C" {
extern void ** DAT_00587218[4];
unsigned int FUN_00320780(igArenaMemoryPool *arg0, int arg1, int arg2);
}
class DW4VC_68_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual int vX(); };
unsigned int FUN_00320780(igArenaMemoryPool *arg0, int arg1, int arg2) {
    unsigned int temp_a1;
    unsigned int temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    if (arg0->_size != 0) {
        return -1U;
    }
    temp_v0 = ((DW4VC_68_0 *)(DAT_00587218[0]))->vX();
    if (temp_v0 != -1U) {
        arg0->_systemAllocated = arg0->_systemAllocated + arg2;
        temp_v1 = (void *)(arg0->_arenaState);
        if (temp_v0 < (unsigned int) *(int *)((char *)(temp_v1) + 2060)) {
            *(int *)((char *)(temp_v1) + 2060) = temp_v0;
        }
        temp_v1_2 = (void *)(arg0->_arenaState);
        temp_a1 = temp_v0 + arg2;
        if ((unsigned int) *(int *)((char *)(temp_v1_2) + 2064) < temp_a1) {
            *(int *)((char *)(temp_v1_2) + 2064) = temp_a1;
        }
    }
    return temp_v0;
}

/* 0x0039b880 - beParticleCtrl2 vfunc 32. Resets every particle of every group (clears a flag byte, releases the shared object at +52, clears a byte of the linked record); alternate compiler -O3,p; guarded do-while loops with a byte offset beside each counter, `0 < n` for the slt/beqz guard, counters and bounds declared in the order that gives retail's registers. */
#include "dw4/reflected.h"
extern "C" {
void FUN_001dc8d0(int);
void igObject_Destroy(igObject *);
void Gap__Bec__beParticleCtrl2__vfunc_32(beParticleCtrl2 *arg0);
}
void Gap__Bec__beParticleCtrl2__vfunc_32(beParticleCtrl2 *arg0) {
    int n1;
    int i;
    int n2;
    int j;
    beParticleCtrl2InfoRam *it;
    beParticleCtrl2Info *g;
    int o1;
    int o2;
    igObject *r;
    n1 = ((igObjectList *)arg0->_infoList)->_count;
    i = 0;
    if (0 < n1) {
        o1 = 0;
        do {
            g = *(beParticleCtrl2Info **)((char *)((igObjectList *)arg0->_infoList)->_data + o1);
            FUN_001dc8d0(g->_mainSwitch);
            FUN_001dc8d0(g->_subSwitch);
            n2 = ((igObjectList *)g->_ramList)->_count;
            j = 0;
            if (0 < n2) {
                o2 = 0;
                do {
                    it = *(beParticleCtrl2InfoRam **)((char *)((igObjectList *)g->_ramList)->_data + o2);
                    it->_isRun = 0;
                    r = (igObject *)it->_work;
                    if (r != 0) {
                        --r->_refCount;
                        if (((unsigned long long)(long long)r->_refCount & 0x7fffffULL) == 0) {
                            igObject_Destroy(r);
                        }
                    }
                    it->_work = 0;
                    j++;
                    o2 += 4;
                    ((ParticleTimer *)it->_particleTimer)->_timeRunning = 0;
                } while (j < n2);
            }
            i++;
            o1 += 4;
        } while (i < n1);
    }
}
